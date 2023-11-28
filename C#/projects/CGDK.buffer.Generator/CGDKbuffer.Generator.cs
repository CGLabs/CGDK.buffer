using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
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
	//	  이 Source Generator를 포함한 프로젝트가 컴파일된 후
	//	  이 Execute()함수가 호출된다.
	//    이때 컴파일 결과를 context 인자로 전달해 오는데
	//    이 context 인자 중에 contex의 SyntaxTree를 뒤져서
	//
	//    1) class Declaration를 찾아 정보를 추출해 낸다.
	//    2) struct Declartaion을 찾아 정보를 추출해 낸다.
	//    3) 추출한 clss와 struct의 serializer 소스를 작성해 등록한다.
	//       이 작업 내역은
	//		 - 일단 source를 작성해 놓을 임시 string builder를 생성한다.
	//       - class별 Serializer class를 정의한 source를 작성한다.
	//       - struct별 Serializer class를 정의한 source를 작성한다.
	//       - Serializer class는 IBast<T>와 IBast<object>를 인터페이스로
	//         가진 것 두가지를 생성해서 추가한다.
	//       - AddSource() 함수로 등록한다.
	//    4) 그 이후 이 Serializable들을 등록할 class를 만든다.
	//       이 작업 내역은
	//       - 소스를 작성해 넣을 임시 string builder를 생성해
	//         'CGDK.BufferSerializer.Generator' 클래스를 정의하고
	//         멤버 할수로 Initialize()를 정의한다. 여기서...
	//		 - class용 Serializer를 등록하는 처리를 작성하고
	//		 - struct용 Serializer를 등록하는 처리를 작성한다.
	//		 - 마지막으로 작성한 source를 AddSource()함수로 등록한다.
	//
	//------------------------------------------------------------------
	public void Execute(GeneratorExecutionContext context)
	{
		//------------------------------------------------------------------
		//
		// 3. class & struct 정보 추출해 내기
		//
		//       일반적으로 compile의 몇단계의 과정을 거친다.
		//       (lexical analysis -> syntax analysis -> semantic analysis -> optimization -> objective)
		//        이중에서 Roslyn을 통해 받을 수 있는 필요 정보는 
		//
		//       1) Syntax Analysis		문법해석(구문허석) 단계로 Token들을 Syntax Tree로 구성하며 문법과 맞게 작성되었는지 검사를 하는 과정이다.
		//								context.Compilation.SyntaxTrees 를 통해 얻을 수 있다.
		//		 2) Semantic Analysis	구문분석(의미분석) 단계로 의미를 부여하고 목적 코드로 만들기 전 각종 정보들를 생성한다.
		//								context.Compilation.GetSemanticModel(syntaxTree)를 통해 얻을 수 있다.
		//
		//       제대로 처리를 하기 위해서 Syntax Analysis 정보를 가진 Syntax Tree와 그것의 의미정보를 가진 Semantic_model 정보가 필요하다.
		// 
		//------------------------------------------------------------------
		// declare) 
		List<OBJECT_INFO> list_class_declaration = [];
		List<OBJECT_INFO> list_struct_declaration = [];

		foreach (var syntaxTree in context.Compilation.SyntaxTrees)
		{
			// - symantic model을 얻음
			var symantic_model = context.Compilation.GetSemanticModel(syntaxTree);

			// - get class declaration
			GetClassDeclarationInfo(ref list_class_declaration, syntaxTree, symantic_model);

			// - get struct declaration
			GetStructDeclarationInfo(ref list_struct_declaration, syntaxTree, symantic_model);
		}

		//------------------------------------------------------------------
		// .4 Source generation
		// 
		//      얻어진 class와 struct 정보를 바탕으로 
		//		Serializer class source를 작성한다.
		// 
		//------------------------------------------------------------------
		{
			// - struct Info
			var sb_source_code = new StringBuilder();

			sb_source_code.AppendLine("using System;");
			sb_source_code.AppendLine("using System.Diagnostics;");
			sb_source_code.AppendLine("using CGDK.BufferSerializer;");

			// - build souce for class
			foreach (var iter in list_class_declaration)
			{
				MakeClassSerializaerSource(ref sb_source_code, iter);   // IBase<T>
				MakeSerializaerSource_object(ref sb_source_code, iter); // IBaset<object>
			}

			// - build souce for struct 
			foreach (var iter in list_struct_declaration)
			{
				MakeStructSerializaerSource(ref sb_source_code, iter);  // IBase<T>
				MakeSerializaerSource_object(ref sb_source_code, iter); // IBaset<object>
			}

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder.generated.cs", sb_source_code.ToString());
		}

		//------------------------------------------------------------------
		// 5. 최종 등록을 위한 class 생성
		//
		//		생성한 Serializer 객체를 생성하고 등록할 init()함수를 정의한다.
		//
		//------------------------------------------------------------------
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
			{
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.type_name}>(new {iter.identifier}_serializer());");
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.type_name}>(new {iter.identifier}_object_serializer());");
			}

			// - build souce for registering struct serializer
			foreach (var iter in list_struct_declaration)
			{
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.type_name}>(new {iter.identifier}_serializer());");
				sb_source_code.AppendLine($"		CGDK.BufferSerializer.Custom.RegisterSerializer<{iter.type_name}>(new {iter.identifier}_object_serializer());");
			}

			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("	}");
			sb_source_code.AppendLine("}");
			sb_source_code.AppendLine("}");

			// - add source
			context.AddSource("CGDKbuffer.BufferBuilder_initialize.generated.cs", sb_source_code.ToString());
		}
	}

	//------------------------------------------------------------------
	// 6. definitions (struct)
	//------------------------------------------------------------------
	// 1) MEMBER에 대한 정보입니다. (CLASS_INFO에서 사용됩니다.)
	private struct MEMBER_INFO
	{
		public int type;			// MEBER의 type 정보.(1:primitive type, 2:others
		public string type_name;	// type의 문자열 이름(int, char, long, string, ...)
		public string identifier;   // 멤버 변수명
	}

	// 2) class 정보
	private struct OBJECT_INFO
	{
		public string type_name;	// 클래스의 type 문자열 이름(namespace까지 포함)
		public string identifier;	// serializer class의 이름으로 사용될 이름(.없이 _로 연결)
		public List<MEMBER_INFO> list_member_node_info;
	}


	//------------------------------------------------------------------
	// 7. functions
	//------------------------------------------------------------------
	// 1) primitive type인가?
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

	// 2) Member info
	private static MEMBER_INFO GetMembeInfo(ISymbol _member)
	{
		// 1) create member_node_info
		var member_node_info = new MEMBER_INFO();

		// 2) 
		if (_member is IFieldSymbol x)
		{
			member_node_info.type_name = x.Type.ToString();
			member_node_info.type = IsPrimitive(member_node_info.type_name);
			member_node_info.identifier = x.Name.ToString();
		}
		else if (_member is IPropertySymbol y)
		{
			member_node_info.type_name = y.Type.ToString();
			member_node_info.type = IsPrimitive(member_node_info.type_name);
			member_node_info.identifier = y.Name.ToString();
		}

		// return) 
		return member_node_info;
	}


	//------------------------------------------------------------------
	// 8. class 추축해 내기
	//
	//    Serialier로 생성할 class 정보를 추출해 낸다.
	//
	//    1) class 정보를 담을 CLASS_INFO를 생성한다.
	//	  2) type info를 semantic_model에서 얻어낸다.
	//    3) class info를 설정한다.
	//       - type_name => .로 연결된 full type_name (ex) CGDK.foo.bar.tee
	//       - identifier => serializer class의 이름으로 사용할 것이다.
	//	  4) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  5) type name 문자열과 serializer class에 사용될 이름을 만든다.
	//	  6) class의 MEMBER_INFO들을 얻어낸다. 
	//       class의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//    7) 이렇게 만들어진 CLASS_INFO를 list에 등록한다.
	//	  r) 최종적으로 만들어진 OBJECT_INFO list을 리턴한다.
	//
	//------------------------------------------------------------------
	private static  void GetClassDeclarationInfo(ref List<OBJECT_INFO> _output, in SyntaxTree _syntax_tree, in SemanticModel _semantic_model)
	{
		foreach (var iter in _syntax_tree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
							.Where(node => node.IsKind(SyntaxKind.ClassDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
							.Cast<ClassDeclarationSyntax>() // (4) ClassDeclarationSyntax 캐스팅해서
							.Where(x => (x.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
								.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any()))
							.ToList()) // (5) 리스트로~
		{
			// 1) alloc OBJECT_INFO
			var class_info = new OBJECT_INFO();

			// 2) temp) get type info
			var type_info = _semantic_model.GetDeclaredSymbol(iter);

			// check) must having type_info
			Debug.Assert(type_info != null);

			// check) throw exception if type_info is null!
			if (type_info == null)
				throw new Exception();

			// check) must be 'public' accessbility
			Debug.Assert(type_info.DeclaredAccessibility == Accessibility.Public);

			// check) must be 'public' accessbility
			if (type_info.DeclaredAccessibility != Accessibility.Public)
				throw new Exception($"class '{iter.Identifier.ToString()}' is Not public");

			// 3) make full typ name string and identifier name
			class_info.type_name = type_info.ToString();
			class_info.identifier = iter.Identifier.ToString();

			// 4) make 'member_node_info' list
			class_info.list_member_node_info = [];

			// 5) gatter members info
			foreach (var member in type_info.GetMembers()
								.Where(x => x.Kind == SymbolKind.Field || x.Kind == SymbolKind.Property) // 1) Field(변수) 혹은 Property 만 얻어서
								.Where(x => (x.GetAttributes() // (2) Attribute 중에 "CGDK.Field"을 가진 것만 골라낸다!
									.Where(y => y.ToString() == "CGDK.Attribute.Field(true)").Any()))
								.ToList()) // (3) 리스트로~
			{
				// - create member_node_info
				var member_node_info = new MEMBER_INFO();

				// check)
				if (member.DeclaredAccessibility != Accessibility.Public)
					throw new Exception($"class 'struct_info.type_name' is Not public");

				member_node_info = GetMembeInfo(member);

				// - add member_node_info
				class_info.list_member_node_info.Add(member_node_info);
			}

			// 7) add struct info
			_output.Add(class_info);
		}
	}

	//------------------------------------------------------------------
	// 9. struct 추축해 내기
	//
	//    Serialier로 생성할 struct 정보를 추출해 낸다.
	//
	//    1) struct 정보를 담을 CLASS_INFO를 생성한다.
	//    2) type info를 semantic_model에서 얻어낸다.
	//	  3) struct info를 설정한다.
	//       - type_name => .로 연결된 full type_name (ex) CGDK.foo.bar.tee
	//       - identifier => serializer struct의 이름으로 사용할 것이다.
	//	  4) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  5) struct의 MEMBER_INFO들을 얻어낸다. 
	//       struct의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//       얻은 멤버들의 자료형 이름(type_name),변수명(identifier)을 얻어낸다.
	//	  6) 최종적으로 만들어진 OBJECT_INFO list를 리턴한다.
	//
	//------------------------------------------------------------------
	private static void GetStructDeclarationInfo(ref List<OBJECT_INFO> _output, in SyntaxTree _syntax_tree, in SemanticModel _semantic_model)
	{
		foreach (var iter in _syntax_tree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
							.Where(node => node.IsKind(SyntaxKind.StructDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
							.Cast<StructDeclarationSyntax>() // (4) StructDeclarationSyntax로 캐스팅해서
							.Where(x => (x as StructDeclarationSyntax)?.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
								.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any() ?? false)
							.ToList()) // (5) List로...
		{
			// 1) alloc OBJECT_INFO
			var struct_info = new OBJECT_INFO();

			// 2) temp) get type info
			var type_info = _semantic_model.GetDeclaredSymbol(iter);

			// check) must having type_info
			Debug.Assert(type_info != null);

			// check) throw exception if type_info is null!
			if (type_info == null)
				throw new Exception();

			// check) must be 'public' accessbility
			Debug.Assert(type_info.DeclaredAccessibility == Accessibility.Public);

			// check) must be 'public' accessbility
			if (type_info.DeclaredAccessibility != Accessibility.Public)
				throw new Exception($"class '{iter.Identifier.ToString()}' is Not public");

			// 3) make full typ name string and identifier name
			struct_info.type_name = type_info.ToString();
			struct_info.identifier = iter.Identifier.ToString();

			// 4) make 'member_node_info' list
			struct_info.list_member_node_info = [];

			// 5) gatter members info
			foreach (var member in type_info.GetMembers()
								.Where(x => x.Kind == SymbolKind.Field || x.Kind == SymbolKind.Property) // 1) Field(변수) 혹은 Property 만 얻어서
								.Where(x => !(x.GetAttributes() // (2) Attribute 중에 "CGDK.Field"을 가진 것만 골라낸다!
									.Where(y => y.ToString() == "CGDK.Attribute.Field(false)").Any()))
								.ToList()) // (3) 리스트로~
			{
				// - create member_node_info
				var member_node_info = new MEMBER_INFO();

				// check)
				if (member.DeclaredAccessibility != Accessibility.Public)
					throw new Exception($"class 'struct_info.type_name' is Not public");

				member_node_info = GetMembeInfo(member);

				// - add member_node_info
				struct_info.list_member_node_info.Add(member_node_info);
			}

			// 6) add struct info
			_output.Add(struct_info);
		}
	}


	//------------------------------------------------------------------
	// 10.  Source Generation (Serializer Class)
	//
	//------------------------------------------------------------------
	// class용 'serializer class' source 작성하기
	private static void MakeClassSerializaerSource(ref StringBuilder _out, in OBJECT_INFO _class_info)
	{
		// 1) serializer class header
		_out.AppendLine($"public class {_class_info.identifier}_serializer : CGDK.BufferSerializer.IBase<{_class_info.type_name}>");
		_out.AppendLine("{");
		_out.AppendLine("#nullable enable");

		// 2) member fucntion 'ProcessAppend'
		_out.AppendLine($"	public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, {_class_info.type_name}? _object)");
		_out.AppendLine("	{");

		// - null object check
		_out.AppendLine("		if(_object == null)");
		_out.AppendLine("		{");
		_out.AppendLine("			*(int*)_ptr = -1;");
		_out.AppendLine("			_ptr += sizeof(int);");
		_out.AppendLine("			return;");
		_out.AppendLine("		}");
		_out.AppendLine("");

		// - append members
		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
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

		// 3) member fucntion 'ProcessExtract'
		_out.AppendLine($"	public unsafe {_class_info.type_name}? ProcessExtract(ref byte* _ptr, ref int _count)");
		_out.AppendLine("	{");

		// - create object
		_out.AppendLine($"		var temp = new {_class_info.type_name}();");

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

		_out.AppendLine("		return temp;");
		_out.AppendLine("	}");

		// 4) member fucntion 'ProcessGetSizeOf'
		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_class_info.type_name}? _object)");
		_out.AppendLine("	{");
		if (_class_info.list_member_node_info.Count != 0)
		{
			_out.AppendLine("		if(_object == null)");
			_out.AppendLine("			return sizeof(int);");
			_out.AppendLine("");
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

		// 5) member vvriable 'serializer for member'
		foreach (var iter_member in _class_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type != 1)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}> serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}

		_out.AppendLine("#nullable disable");
		_out.AppendLine("}");
	}

	// struct용 'serializer class' source 작성하기
	private static void MakeStructSerializaerSource(ref StringBuilder _out, in OBJECT_INFO _struct_info)
	{
		// 1) serializer class header
		_out.AppendLine($"public class {_struct_info.identifier}_serializer : CGDK.BufferSerializer.IBase<{_struct_info.type_name}>");
		_out.AppendLine("{");

		// 2) member fucntion 'ProcessAppend'
		_out.AppendLine($"	public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, {_struct_info.type_name} _object)");
		_out.AppendLine("	{");

		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type == 1)
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

		// 3) member fucntion 'ProcessExtract'
		_out.AppendLine($"	public unsafe {_struct_info.type_name} ProcessExtract(ref byte* _ptr, ref int _count)");
		_out.AppendLine("	{");
		_out.AppendLine($"		var temp = new {_struct_info.type_name}();");

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

		_out.AppendLine("		return temp;");
		_out.AppendLine("	}");

		// 4) member fucntion 'ProcessGetSizeOf'
		_out.AppendLine($"	public unsafe int ProcessGetSizeOf({_struct_info.type_name} _object)");
		_out.AppendLine("	{");

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

		// 5) member vvriable 'serializer for member'
		_out.AppendLine("#nullable enable");
		foreach (var iter_member in _struct_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type != 1)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}> serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}
		_out.AppendLine("#nullable disable");

		_out.AppendLine("}");
	}

	// class/struct용 'serializer object class' source 작성하기
	private static void MakeSerializaerSource_object(ref StringBuilder _out, in OBJECT_INFO _object_info)
	{
		// 1) serializer class header
		_out.AppendLine($"public class {_object_info.identifier}_object_serializer : CGDK.BufferSerializer.IBase<object>");
		_out.AppendLine("{");
		_out.AppendLine("#nullable enable");

		// 2) member fucntion 'ProcessAppend'
		_out.AppendLine($"	public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)");
		_out.AppendLine("	{");

		// - null object check
		_out.AppendLine( "		if(_object == null)");
		_out.AppendLine( "		{");
		_out.AppendLine( "			*(int*)_ptr = -1;");
		_out.AppendLine( "			_ptr += sizeof(int);");
		_out.AppendLine( "			return;");
		_out.AppendLine( "		}");
		_out.AppendLine( "");
		_out.AppendLine($"		var temp = ({_object_info.type_name})_object;");
		_out.AppendLine( "");

		foreach (var iter_member in _object_info.list_member_node_info)
		{
			if (iter_member.type == 1)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = temp.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// - non primitive type
			else
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, temp.{iter_member.identifier});");
			}
		}
		_out.AppendLine("	}");

		// 3) member fucntion 'ProcessExtract'
		_out.AppendLine($"	public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)");
		_out.AppendLine("	{");
		_out.AppendLine($"		var temp = new {_object_info.type_name}();");
		_out.AppendLine("");

		_out.AppendLine("	#pragma warning disable 8601");
		int count_primitive = 0;
		int count_object= 0;
		foreach (var iter_member in _object_info.list_member_node_info)
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
				
				++count_object;

			}
		}
		_out.AppendLine("	#pragma warning restore 8601");

		if (count_primitive != 0)
		{
			_out.AppendLine("");
			_out.Append("		_count += ");
			foreach (var iter_member in _object_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}

		_out.AppendLine("		return temp;");
		_out.AppendLine("	}");

		// 4) member fucntion 'ProcessGetSizeOf'
		_out.AppendLine($"	public unsafe int ProcessGetSizeOf(object? _object)");
		_out.AppendLine("	{");
		_out.AppendLine("		if(_object == null)");
		_out.AppendLine("			return sizeof(int);");
		_out.AppendLine("");

		if (count_object != 0)
		{
			_out.AppendLine($"		var temp = ({_object_info.type_name})_object;");
			_out.AppendLine("");
		}

		if (_object_info.list_member_node_info.Count != 0)
		{
			_out.Append("		return ");
			foreach (var iter_member in _object_info.list_member_node_info)
			{
				if (iter_member.type == 1)
					_out.Append($"sizeof({iter_member.type_name})+");
				else
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(temp.{iter_member.identifier})+");
			}
			_out.Remove(_out.Length - 1, 1);
			_out.AppendLine(";");
		}
		else
		{
			_out.AppendLine("		return 0;");
		}
		_out.AppendLine("	}");

		// 5) member vvriable 'serializer for member'
		foreach (var iter_member in _object_info.list_member_node_info)
		{
			// - primitive type
			if (iter_member.type != 1)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}> serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}

		_out.AppendLine("#nullable disable");
		_out.AppendLine("}");
	}
}