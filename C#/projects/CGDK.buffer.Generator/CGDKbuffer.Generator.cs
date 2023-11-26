using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace CGDK.BufferGenerator.Generator;


[Generator(LanguageNames.CSharp)]
public partial class CGDKbufferGenerator : ISourceGenerator
{
	public void Initialize(GeneratorInitializationContext context)
	{
	}

	private struct MEMBER_NODE_INFO
	{
		public int type;
		public string type_name;
		public string identifier;
	}

	private struct CLASS_INFO
	{
		public string name;
		public string name_sub;
		public List<MEMBER_NODE_INFO> list_member_node_info;
	}

	private struct STRUCT_INFO
	{
		public string name;
		public string name_sub;
		public List<MEMBER_NODE_INFO> list_member_node_info;
	}

	private static int IsPrimitive(in string _type_name)
	{
		if(_type_name == "char"
		|| _type_name == "byte"
		|| _type_name == "sbyte"
		|| _type_name == "Int8"
		|| _type_name == "UInt8"
		|| _type_name == "short"
		|| _type_name == "ushort"
		|| _type_name == "Int16"
		|| _type_name == "UInt16"
		|| _type_name == "int"
		|| _type_name == "uint"
		|| _type_name == "Int32"
		|| _type_name == "UInt32"
		|| _type_name == "long"
		|| _type_name == "ulong"
		|| _type_name == "Int64"
		|| _type_name == "UInt64"
		|| _type_name == "float"
		|| _type_name == "double")
		{
			return 1;
		}

		// return) 
		return 0;
	}

	private static string MakeName(List<string> _namespace, string _name)
	{
		var temp = new StringBuilder();
		foreach (var iter in _namespace.Reverse<string>())
		{
			temp.Append(iter);
			temp.Append(".");
		}
		temp.Append(_name);

		return temp.ToString();
	}
	private static string MakeSubame(List<string> _namespace, string _name)
	{
		var temp = new StringBuilder();
		foreach (var iter in _namespace.Reverse<string>())
		{
			temp.Append(iter);
			temp.Append("_");
		}
		temp.Append(_name);

		return temp.ToString();
	}


	private static  List<CLASS_INFO> GetClassDeclarationInfo(in IEnumerable<SyntaxTree> _syntax_nodes)
	{
		// 1) alloc list
		var list_class_info = new List<CLASS_INFO>();

		// 2) query out
		foreach (var syntaxTree in _syntax_nodes)
		{
			foreach (var iter in syntaxTree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
								.Where(node => node.IsKind(SyntaxKind.ClassDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
								.Cast<ClassDeclarationSyntax>() // (4) ClassDeclarationSyntax 캐스팅해서
								.Where(x => (x.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
									.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any()))
								.ToList()) // (5) 리스트로~
			{
				// - get name
				var str_name = iter.Identifier.ToString();

				// check)
				if (iter.GetType().IsNotPublic)
					throw new Exception($"class '{str_name}' is Not public");

				// - alloc CLASS_INFO
				var class_info = new CLASS_INFO();

				var list_namespace = new List<string>();
				foreach (var ancestors in iter.Ancestors())
				{
					if(ancestors.IsKind(SyntaxKind.NamespaceDeclaration) || ancestors.IsKind(SyntaxKind.FileScopedNamespaceDeclaration))
						list_namespace.Add(((BaseNamespaceDeclarationSyntax)ancestors).Name.ToString());
					else if(ancestors.IsKind(SyntaxKind.ClassDeclaration))
						list_namespace.Add(((ClassDeclarationSyntax)ancestors).Identifier.ToString());
					else if (ancestors.IsKind(SyntaxKind.StructDeclaration))
						list_namespace.Add(((StructDeclarationSyntax)ancestors).Identifier.ToString());
				}
				class_info.name = MakeName(list_namespace, str_name);
				class_info.name_sub = MakeSubame(list_namespace, str_name);
				class_info.list_member_node_info = new List<MEMBER_NODE_INFO>();

				// - gather members info
				foreach (var member in iter.Members
									.Where(x => x.IsKind(SyntaxKind.FieldDeclaration) || x.IsKind(SyntaxKind.PropertyDeclaration)) // FIELDDeclaration을 얻어서(너무 당연하지만...)
									.Where(x => (x.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
										.Where(y => y.ToString() == "[CGDK.Attribute.Field]").Any()))
									.ToList())
				{
					// - create member_node_info
					var member_node_info = new MEMBER_NODE_INFO();

					//// check)
					//if (member.Declaration.IsNotPublic)
					//	throw new Exception($"class '{str_name}' is Not public");

					if (member is FieldDeclarationSyntax x)
					{
						// - ommit first
						var iter_member = x.Declaration.ChildNodes().GetEnumerator();
						iter_member.MoveNext();

						// - get type name
						member_node_info.type_name = iter_member.Current.ToString();
						member_node_info.type = IsPrimitive(member_node_info.type_name);
						iter_member.MoveNext();

						// - get identifier
						member_node_info.identifier = iter_member.Current.ToString();
					}
					else if(member is PropertyDeclarationSyntax y)
					{
						// - get type name
						member_node_info.type_name = y.Type.ToString();
						member_node_info.type = IsPrimitive(member_node_info.type_name);

						// - get identifier
						member_node_info.identifier = y.Identifier.ToString();
					}

					// - add member_node_info
					class_info.list_member_node_info.Add(member_node_info);
				}

				// - add struct info
				list_class_info.Add(class_info);
			}
		}

		// return)
		return list_class_info;
	}

	private static void MakeClassSerializaerSource(ref StringBuilder _out, in CLASS_INFO _class_info)
	{
		_out.AppendLine($"public class {_class_info.name_sub}_serializer : CGDK.BufferSerializer.IBase<{_class_info.name}>"		);
		_out.AppendLine( "{"																									);
		_out.AppendLine($"	public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, {_class_info.name} _object)"		);
		_out.AppendLine( "	{"																									);

		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if(iter_member.type == 1)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = _object.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, _object.{iter_member.identifier});");
			}
		}
		_out.AppendLine("	}");

		_out.AppendLine($"	public unsafe {_class_info.name} ProcessExtract(ref byte* _ptr, ref int _count)"					);
		_out.AppendLine( "	{"																									);
		_out.AppendLine($"		var temp = new {_class_info.name}();"															);

		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
				
			}
		}

		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		_count += sizeof({iter_member.type_name});");
			}
		}
		_out.AppendLine( "		return temp;");
		_out.AppendLine( "	}");

		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_class_info.name} _object)"										);
		_out.AppendLine( "	{"																									);
		_out.AppendLine("		int size = 0;");


		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		size += sizeof({iter_member.type_name});");
			}
			else
			{
				_out.AppendLine($"		size += serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier});");
			}
		}
		_out.AppendLine("		return size;");
		_out.AppendLine("	}");

		_out.AppendLine("#nullable enable");
		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type != 1)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}>? serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}
		_out.AppendLine("#nullable disable");

		_out.AppendLine("}");
	}

	private static List<STRUCT_INFO> GetStructDeclarationInfo(in IEnumerable<SyntaxTree> _syntax_nodes)
	{
		// 1) alloc list
		var list_struct_info = new List<STRUCT_INFO>();

		// 2) query out
		foreach (var syntaxTree in _syntax_nodes)
		{
			foreach (var iter in syntaxTree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
								.Where(node => node.IsKind(SyntaxKind.StructDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
								.Cast<StructDeclarationSyntax>() // (4) StructDeclarationSyntax로 캐스팅해서
								.Where(x => (x as StructDeclarationSyntax)?.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
									.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any() ?? false)
								.ToList()) // (5) List로...
			{
				// - get name
				var str_name = iter.Identifier.ToString();

				// - alloc STRUCT_INFO
				var struct_info = new STRUCT_INFO();

				// - namespace
				var list_namespace = new List<string>();
				foreach (var ancestors in iter.Ancestors())
				{
					// declare) 
					string? x = null;

					// - get name
					if (ancestors.IsKind(SyntaxKind.NamespaceDeclaration) || ancestors.IsKind(SyntaxKind.FileScopedNamespaceDeclaration))
						x = ((BaseNamespaceDeclarationSyntax)ancestors).Name.ToString();
					else if(ancestors.IsKind(SyntaxKind.ClassDeclaration))
						x = ((ClassDeclarationSyntax)ancestors).Identifier.ToString();
					else if (ancestors.IsKind(SyntaxKind.StructDeclaration))
						x = ((StructDeclarationSyntax)ancestors).Identifier.ToString();

					// check)
					if (x == null)
						continue;

					if (x == "IBase<>")
						throw new Exception("FAil");

					// - add
					list_namespace.Add(x);
				}
				struct_info.name = MakeName(list_namespace, str_name);
				struct_info.name_sub = MakeSubame(list_namespace, str_name);
				struct_info.list_member_node_info = new List<MEMBER_NODE_INFO>();

				// - gather members info
				foreach (var member in iter.Members.Where(x => x.IsKind(SyntaxKind.FieldDeclaration)).ToList())
				{
					// - create member_node_info
					var member_node_info = new MEMBER_NODE_INFO();

					// - ommit first
					var iter_member = ((FieldDeclarationSyntax)member).Declaration.ChildNodes().GetEnumerator();
					iter_member.MoveNext();

					// - get type name
					member_node_info.type_name = iter_member.Current.ToString();
					member_node_info.type = IsPrimitive(member_node_info.type_name);
					iter_member.MoveNext();

					// - get identifier
					member_node_info.identifier = iter_member.Current.ToString();

					// - add member_node_info
					struct_info.list_member_node_info.Add(member_node_info);
				}

				// - add struct info
				list_struct_info.Add(struct_info);
			}
		}

		// return)
		return list_struct_info;
	}

	private static void MakeStructSerializaerSource(ref StringBuilder _out, in STRUCT_INFO _struct_info)
	{
		_out.AppendLine($"public class {_struct_info.name_sub}_serializer : CGDK.BufferSerializer.IBase<{_struct_info.name}>"	);
		_out.AppendLine( "{"																									);
		_out.AppendLine($"	public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, {_struct_info.name} _object)"	);
		_out.AppendLine( "	{"																									);

		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if(iter_member.type == 1)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = _object.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, _object.{iter_member.identifier});");
			}
		}
		_out.AppendLine("	}");

		_out.AppendLine($"	public unsafe {_struct_info.name} ProcessExtract(ref byte* _ptr, ref int _count)"					);
		_out.AppendLine( "	{"																									);
		_out.AppendLine($"		var temp = new {_struct_info.name}();"															);

		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
				
			}
		}

		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		_count += sizeof({iter_member.type_name});");
			}
		}
		_out.AppendLine( "		return temp;");
		_out.AppendLine( "	}");

		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_struct_info.name} _object)"										);
		_out.AppendLine( "	{"																										);
		_out.AppendLine("		int size = 0;");


		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		size += sizeof({iter_member.type_name});");
			}
			else
			{
				_out.AppendLine($"		size += serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier});");
			}
		}
		_out.AppendLine("		return size;");
		_out.AppendLine("	}");

		_out.AppendLine("#nullable enable");
		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type != 1)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}>? serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}
		_out.AppendLine("#nullable disable");

		_out.AppendLine("}");
	}

	public void Execute(GeneratorExecutionContext context)
	{
		// 1) get class declaration
		var list_class_declaration = GetClassDeclarationInfo(context.Compilation.SyntaxTrees);

		// 2) get struct declaration
		var list_struct_declaration = GetStructDeclarationInfo(context.Compilation.SyntaxTrees);

		// 3) defintion serializer
		{
			// - struct Info
			var sb_source_code = new StringBuilder();

			
			sb_source_code.AppendLine( "using System;");
			sb_source_code.AppendLine( "using System.Diagnostics;");
			sb_source_code.AppendLine( "using CGDK.BufferSerializer;");

			// - build souce for class
			foreach (var iter in list_class_declaration)
				MakeClassSerializaerSource(ref sb_source_code, iter);

			// - build souce for struct 
			foreach (var iter in list_struct_declaration)
				MakeStructSerializaerSource(ref sb_source_code, iter);

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder.generated.cs", sb_source_code.ToString());
		}

		// 4) start-up!
		{
			// - struct Info
			var sb_source_code = new StringBuilder();

			sb_source_code.AppendLine("namespace CGDK");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("namespace BufferSerializer");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("public class Generator");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("	public static void Initialize()");
			sb_source_code.AppendLine("	{");

			// - build souce for class
			foreach (var iter in list_class_declaration)
				sb_source_code.AppendLine($"CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.name}>(new {iter.name_sub}_serializer());");

			// - build souce for struct 
			foreach (var iter in list_struct_declaration)
				sb_source_code.AppendLine($"CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.name}>(new {iter.name_sub}_serializer());");

			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("	}");

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder_initialize.generated.cs", sb_source_code.ToString());
		}
	}
}