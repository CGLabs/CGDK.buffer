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


//------------------------------------------------------------------
//
//  1. CGDKbufferGenerator!
//
//  - ISourceGenerator를 상속 받아 CGDKbufferGenerator를 정의한다.
//  - 이 class로 컴파일된 정보를 받아 source를 생성한다.
//  - 시작은'CGDKbufferGenerator.Execute(...)'함수가 가 호출되면서다.
//    
//------------------------------------------------------------------
[Generator(LanguageNames.CSharp)]
public partial class CGDKbufferGenerator : ISourceGenerator
{
	public void Initialize(GeneratorInitializationContext context)
	{
	}

	//------------------------------------------------------------------
	// 2. Execute 함수 (여기가 시작!!!)
	//
	//    인자로 전달 받은 contex 중에 Conpilation.SyntaxTrees를 뒤져서
	//
	//    1) class Declaration를 찾아 정보를 추출해 낸다.
	//    2) struct Declartaion을 찾아 정보를 추출해 낸다.
	//    3) 추출한 clss와 struct의 serializer를 정의한 source를 작성해 등록한다.
	//		 - 일단 source를 작성해 놓을 임시 string builder를 생성한다.
	//       - class별 Serializer class를 정의한 source를 작성한다.
	//       - struct별 Serializer class를 정의한 source를 작성한다.
	//       - AddSource() 함수로 등록한다.
	//    4) 공용 class를 만든다.
	//       - source를 작성해 놓을 임시 string builder를 생성해
	//         'class CGDK.BufferSerializer.Generator'를 정의하고
	//         Initialize()함수를 정의해
	//		 - class용 Serializer를 등록하는 처리를 작성하고
	//		 - struct용 Serializer를 등록하는 처리를 작성한다.
	//		 - 작성한 source를 AddSource()함수로 등록한다.
	//
	//------------------------------------------------------------------
	public void Execute(GeneratorExecutionContext context)
	{

		// 1) get class declaration
		var list_class_declaration = GetClassDeclarationInfo(context.Compilation.SyntaxTrees);

		// 2) get struct declaration
		var list_struct_declaration = GetStructDeclarationInfo(context.Compilation.SyntaxTrees);

		// 3) generation source for define serializer classess
		{
			// - struct Info
			var sb_source_code = new StringBuilder();

			sb_source_code.AppendLine("using System;");
			sb_source_code.AppendLine("using System.Diagnostics;");
			sb_source_code.AppendLine("using CGDK.BufferSerializer;");

			// - build souce for class
			foreach (var iter in list_class_declaration)
				MakeClassSerializaerSource(ref sb_source_code, iter);

			// - build souce for struct 
			foreach (var iter in list_struct_declaration)
				MakeStructSerializaerSource(ref sb_source_code, iter);

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder.generated.cs", sb_source_code.ToString());
		}

		// 4) build 'CGDK.BufferSerializer.Generator' class를 정의한다.
		{
			// - create string builder for source generation
			var sb_source_code = new StringBuilder();

			sb_source_code.AppendLine("namespace CGDK");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("namespace BufferSerializer");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("public class Generator");
			sb_source_code.AppendLine("{");
			sb_source_code.AppendLine("	public static void Initialize()");
			sb_source_code.AppendLine("	{");

			// - build souce for registering class serializer
			foreach (var iter in list_class_declaration)
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.name}>(new {iter.name_sub}_serializer());");

			// - build souce for registering struct serializer
			foreach (var iter in list_struct_declaration)
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.name}>(new {iter.name_sub}_serializer());");

			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("}");
			sb_source_code.AppendLine("}");

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder_initialize.generated.cs", sb_source_code.ToString());
		}
	}

	//------------------------------------------------------------------
	// 3. definitions and functions
	//------------------------------------------------------------------
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
	private static readonly string[] primitive_types = { "char","byte","sbyte","Int8","UInt8","short","ushort","Int16","UInt16","int","uint","Int32","UInt32","long","ulong","Int64","UInt64","float","double"};
	private static int IsPrimitive(string _type_name)
	{
		// check)
		Debug.Assert(_type_name != null);

		// 1) is primitive type?
		if(primitive_types.Where(x => x == _type_name).Any())
			return 1;

		// return) others;
		return 0;
	}
	private static string MakeName(List<string> _namespace, string _name)
	{
		// 1) make full name 
		var temp = new StringBuilder();
		foreach (var iter in _namespace.Reverse<string>())
		{
			temp.Append(iter);
			temp.Append(".");
		}
		temp.Append(_name);

		// return)
		return temp.ToString();
	}
	private static string MakeSerializerClassName(List<string> _namespace, string _name)
	{
		// 1) make generate serializer class name
		var temp = new StringBuilder();
		foreach (var iter in _namespace.Reverse<string>())
		{
			temp.Append(iter);
			temp.Append("_");
		}
		temp.Append(_name);

		// return)
		return temp.ToString();
	}

	//------------------------------------------------------------------
	// 4. class 추축해 내기
	//
	//    Serialier로 생성할 class를 추축해 낸다.
	//
	//    1) class 정보들를 담은 List<CLASS_LINFO>를 생성한다.
	//    2) class 정보들을 추축해 낸다.
	//       - class Declaration이어야 하고!
	//       - '[CGDK.Attribute.Serializable]'를 Attribute로 가지고 있는 class
	//    3) 먼저 구조체의 이름을 얻어 놓는다.
	//    4) class 정보를 담을 CLASS_INFO를 생성한다.
	//    5) namespace와 부도 클래스가 있을 경우 이걸 얻어 full name을 생성한다.
	//       - name => .로 연결된 full name (ex) CGDK.foo.bar.tee
	//       - name_sub => _로 연경될 full name (ex) CGDK_foo_bar_tee
	//		   serializer class의 이름으로 사용할 것이다.
	//
	//	  6) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  7) class의 MEMBER_INFO들을 얻어낸다. 
	//       class의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//       얻은 멤버들의 자료형 이름(type_name),변수명(identifier)을 얻어낸다.
	//    8) 이렇게 만들어진 CLASS_INFO를 list에 등록한다.
	//	  r) 이렇게 만들어진 CLASS_INFO들을 리턴한다.
	//
	//------------------------------------------------------------------
	private static  List<CLASS_INFO> GetClassDeclarationInfo(in IEnumerable<SyntaxTree> _syntax_nodes)
	{
		// 1) alloc list
		var list_class_info = new List<CLASS_INFO>();

		foreach (var syntaxTree in _syntax_nodes)
		{
			// 2) query out
			foreach (var iter in syntaxTree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
								.Where(node => node.IsKind(SyntaxKind.ClassDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
								.Cast<ClassDeclarationSyntax>() // (4) ClassDeclarationSyntax 캐스팅해서
								.Where(x => (x.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
									.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any()))
								.ToList()) // (5) 리스트로~
			{
				// 3) get name
				var str_name = iter.Identifier.ToString();

				// check)
				if (iter.GetType().IsNotPublic)
					throw new Exception($"class '{str_name}' is Not public");

				// 4) alloc CLASS_INFO
				var class_info = new CLASS_INFO();

				// 5) alloc CLASS_INFO
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
				class_info.name_sub = MakeSerializerClassName(list_namespace, str_name);

				// 6) make 'member_node_info' list
				class_info.list_member_node_info = [];

				// 7) gather members info
				foreach (var member in iter.Members
									.Where(x => x.IsKind(SyntaxKind.FieldDeclaration) || x.IsKind(SyntaxKind.PropertyDeclaration)) // 1) Field(변수) 혹은 Property 만 얻어서
									.Where(x => (x.AttributeLists // (2) Attribute 중에 "CGDK.Field"을 가진 것만 골라낸다!
										.Where(y => y.ToString() == "[CGDK.Attribute.Field]").Any()))
									.ToList()) // (3) 리스트로~
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

				// 8) add struct info
				list_class_info.Add(class_info);
			}
		}

		// return)
		return list_class_info;
	}

	//------------------------------------------------------------------
	// 5. class용 'serializer class' source 작성하기
	//
	//------------------------------------------------------------------
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

		int count_primitive = 0;
		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
				++count_primitive;
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
				
			}
		}
		if (count_primitive != 0)
		{
			_out.AppendLine("");
			_out.Append("		_count += ");
			foreach (var iter_member in _class_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}

		_out.AppendLine( "		return temp;");
		_out.AppendLine( "	}");

		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_class_info.name} _object)"										);
		_out.AppendLine( "	{"																									);
		if (_class_info.list_member_node_info.Count != 0)
		{
			_out.Append("		return ");
			foreach (var iter_member in _class_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
				else
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}
		else
		{
			_out.AppendLine("		return 0;");
		}
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

	//------------------------------------------------------------------
	// 6. struct 추축해 내기
	//
	//    Serialier로 생성할 struct를 추축해 낸다.
	//
	//    1) struct 정보들를 담은 List<STRUCT_LINFO>를 생성한다.
	//    2) struct 정보들을 추축해 낸다.
	//       - struct Declaration이어야 하고!
	//       - '[CGDK.Attribute.Serializable]'를 Attribute로 가지고 있는 struct
	//    3) 먼저 구조체의 이름을 얻어 놓는다.
	//    4) struct 정보를 담을 STRUCT_INFO를 생성한다.
	//    5) namespace와 부도 클래스가 있을 경우 이걸 얻어 full name을 생성한다.
	//       - name => .로 연결된 full name (ex) CGDK.foo.bar.tee
	//       - name_sub => _로 연경될 full name (ex) CGDK_foo_bar_tee
	//		   serializer struct의 이름으로 사용할 것이다.
	//
	//	  6) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  7) struct의 MEMBER_INFO들을 얻어낸다. 
	//       struct의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//       얻은 멤버들의 자료형 이름(type_name),변수명(identifier)을 얻어낸다.
	//    8) 이렇게 만들어진 STRUCT_INFO를 list에 등록한다.
	//	  9) 이렇게 만들어진 STRUCT_INFO들을 리턴한다.
	//
	//------------------------------------------------------------------
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
				struct_info.name_sub = MakeSerializerClassName(list_namespace, str_name);
				struct_info.list_member_node_info = [];

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

	//------------------------------------------------------------------
	// 7. struct용 'serializer class' source 작성하기
	//
	//------------------------------------------------------------------
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

		int count_primitive = 0;
		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
				++count_primitive;
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
				
			}
		}
		if (count_primitive != 0)
		{
			_out.AppendLine("");
			_out.Append("		_count += ");
			foreach (var iter_member in _struct_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}

		_out.AppendLine( "		return temp;");
		_out.AppendLine( "	}");

		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_struct_info.name} _object)"										);
		_out.AppendLine( "	{"																										);
		if (_struct_info.list_member_node_info.Count != 0)
		{
			_out.Append("		return ");
			foreach (var iter_member in _struct_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
				else
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}
		else
		{
			_out.AppendLine("		return 0;");
		}
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
}