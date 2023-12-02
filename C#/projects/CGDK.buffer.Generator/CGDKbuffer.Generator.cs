//*****************************************************************************
//*                                                                           *
//*                                CGDK.buffer                                *
//*                        Ver 3.2 / Release 2023.12.1                        *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                    (C) 2008 CGLabs All right reserved.                    *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
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
//  - 컴파일된 정보를 받아 source를 생성한다.
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
	//	  아래 Execute()함수가 호출된다.
	//    이때 컴파일 결과를 context 인자로 전달해 오는데
	//    contex의 SyntaxTree를 뒤져서
	//
	//    1) class Declaration과 struct Declartaion를 찾아 정보를 추출해 낸다.
	//    2) 추출한 clss와 struct의 serializer 소스를 작성해 등록한다.
	//       이 작업 내역은
	//		 - 일단 source를 작성해 놓을 임시 string builder를 생성한다.
	//       - class별 Serializer class를 정의한 source를 작성한다.
	//       - struct별 Serializer class를 정의한 source를 작성한다.
	//       - Serializer class는 IBast<T>와 IBast<object>를 인터페이스로
	//         가진 것 두가지를 생성해서 추가한다.
	//       - AddSource() 함수로 생성한 source를 등록한다.
	//    3) 그 이후 이 Serializable들을 등록할 class를 만든다.
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
		// 1) class & struct 정보 추출해 내기
		//
		//       일반적으로 compile의 몇단계의 과정을 거친다.
		//       (lexical analysis -> syntax analysis -> semantic analysis -> optimization -> objective code)
		//        이중에서 Roslyn을 통해 받을 수 있는 필요 정보는 
		//
		//       1) Syntax Analysis		문법해석(구문허석) 단계로 lexical Analysis로 도출된 Token들로 Syntax Tree로 구성하며 문법과 맞게 작성되었는지 검사를 하는 과정이다.
		//								- context.Compilation.SyntaxTrees 를 통해 얻을 수 있다.
		//								- 이 단계에서는 각 Syntax에 노드에 어떤 종류의 Keyward가 있는 지가지는 알 수 있습니다.
		//							      하지만 구문상 어떤 의미를 가지는 지는 확인할 수 없다.
		//								- 예들들어 설명하자면 'class X'라는 구문이 있다면 'class'는 클래스 선언 예약어며 'X'는 클래스명이란 것까지는 알수 있지만
		//								  'X'가 어떤 존재인지에 대한 정보는 알수 없다. 진짜 존재는 하긴 하는지 어디에 어떤 namespace에 존재하는 지 등등의 정보는 포함하고 있지 없다.
		//								- 구문해석 정보는 SyntaxNode를 상속받은 다양한 구조체를 트리 모양으로 구성한 SyntaxTree로 제공된다.
		//								  따라서 원하는 SyntaxNode를 찾은 후 그 SyntaxNode의 종류가 무엇인지 Kind()함수로 확인하여 그에 맞는 SyntaXNode 구조체로 unboxing(Casting)한 후 사용한다.
		//
		//		 2) Semantic Analysis	의미분석(구문분석) 단계로 의미를 부여하고 목적 코드로 만들기 전 각종 정보들를 생성한다.
		//								- 의미분석 정보를 이용하면 좀 더 구체적인 정보들을 얻을 수 있다.
		//								- 예들들어 'class X'를 구문해석하면 'X' 클래스가 진짜 존재하긴 하는지 어느 namespace에 존재하고 어떤 클래스를 상속받았는 지 등등 
		//								  의미적 정보들을 얻을 수 있다.
		//								- 여기서는 주로 이 Semantic 정보를 사용해 구현했다.
		//								- semantic 정보를 얻기 위해서는 먼저 SyntaxTree로 SemanticModel을 먼저 생성해야 하는데...
		//
		//								   var semantic_model = context.Compilation.GetSemanticModel(syntaxTree);
		//
		//								  를 수행하면 Semantic Model을 얻을 수 있는데
		//								  SynTaxTree에서 원하는 Node를 먼저 찾은 후 그걸 semantic_model에서 GetDeclaredSymbol() 함수로 Semantic 정보를 얻을 수 있다.
		//							      (물론 바로 찾을 수도 있긴 하지만... )
		//		
		//		이렇게 찾아낸 Semantic 정보를 활용해 CLASS_INFO들을 생성한다.
		//		
		//------------------------------------------------------------------
		// declare) 
		List<OBJECT_INFO> list_class_declaration = [];
		List<OBJECT_INFO> list_struct_declaration = [];

		foreach (var syntaxTree in context.Compilation.SyntaxTrees)
		{
			// - get symantic model
			var symantic_model = context.Compilation.GetSemanticModel(syntaxTree);

			// - extract class declaration info
			GetClassDeclarationInfo(ref list_class_declaration, context, syntaxTree, symantic_model);

			// - extract struct declaration info
			GetStructDeclarationInfo(ref list_struct_declaration, context, syntaxTree, symantic_model);
		}

		//------------------------------------------------------------------
		// 2) Source generation
		// 
		//      앞에서 얻어진 CLASS_INFO를 바탕으로 Serailizer class를 생성하는 단계다.
		//      클래스 명과 멤버 변수와 property 정보로 문자열을 짜집기해서
		//      Serializser class를 정의하는 Source를 작성한다.
		//      그리고...
		//
		//		context.AddSource(...);
		//		
		//		함수를 사용해 생성한 Source를 등록한다.
		// 
		//------------------------------------------------------------------
		{
			// - struct Info
			var sb_source_code = new StringBuilder();

			// - source header 
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

			// - add source!
			context.AddSource("CGDKbuffer.BufferBuilder.generated.cs", sb_source_code.ToString());
		}

		//------------------------------------------------------------------
		// 3) 초기화를 위한 class와 함수 정의
		//
		//		이렇게 정의한 Serializer class를 객체화해서 등록하는 처리를 할
		//		class와 함수를 정의한다.
		//
		//		public static class CGDK.BufferSerializer.Generator
		//
		//		가 그런 역할을 할 클래스이다.
		//		이 클래스의 멤버 함수로 Initialize()함수를 정의한다.
		//
		//		Initialize() 함수에서는 
		//		Seriazer 객체를 생성해 등록하는 소스를 넣는다.
		//
		//		이 Initialize()함수를 호출함으로써 생성된 Serializer들을 사용할 수 있게 된다.
		//	    만약 Initialize()함수를 호출하지 힘들게 생겅한 Serializer가 아니라
		//	    그냥 느린 기존의 방법으로 Serializer를 생성한다.
		//		하지만 .NET framework 버전이나 Roslyn을 쓸 수 없는 곳에서도 동작하기 위해
		//		두가지 방법 모두 지원하는 것이다.
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
	// 3. definitions (struct)
	//------------------------------------------------------------------
	// 1) MEMBER에 대한 정보 (CLASS_INFO에서 사용)
	private struct MEMBER_INFO
	{
		public int type;			// MEBER의 type 정보.(0:not_assigned, 1:value_type, 2:value_type_but_assign, 3:reference type)
		public string type_name;	// type의 문자열 이름(int, char, long, string, ...)
		public string identifier;   // 멤버 변수명
	}

	// 2) class 정보
	private struct OBJECT_INFO
	{
		public string type_name;	// 클래스의 type 문자열 이름(namespace까지 포함)
		public string identifier;	// serializer class의 이름으로 사용될 별명(클래스명인 만큼 고유할 필요가 있다.)
		public List<MEMBER_INFO> list_member_node_info;
	}


	//------------------------------------------------------------------
	// 4. functions
	//------------------------------------------------------------------
	// 1) primitive type인가? (문자열로 primitive type여부를 확인한다.)
	private static readonly string[] primitive_types = { "char","byte","sbyte","Int8","UInt8","short","ushort","Int16","UInt16","int","uint","Int32","UInt32","long","ulong","Int64","UInt64","float","double"};
	private static int get_field_type(ITypeSymbol _type_symbol)
	{
		// 0:reference type
		// 1:value_type
		// 2:primitive_type

		// check)
		Debug.Assert(_type_symbol != null);

		// check)
		if (_type_symbol == null)
			throw new ArgumentNullException("type synbml is null");

		// 1) is primitive type?
		if (primitive_types.Where(x => x == _type_symbol.ToString()).Any())
			return 2;

		// 2) is value type?
		if (_type_symbol.IsValueType)
			return 1;

		// return) others;
		return 0;
	}

	private static bool IsSerialzable(ITypeSymbol _type_synbol)
	{
		return true;
	}

	// 3) Member info
	//    - ISymbol 정보로 MEMER_INFO를 생성해 리턴한다.
	//    - Member는 Field형(일반 변수)와 progerty형 두가지 종료다.
	private static MEMBER_INFO GetMembeInfo(GeneratorExecutionContext _context, ISymbol _member)
	{
		// 1) create member_node_info
		var member_node_info = new MEMBER_INFO();

		// 2-1) 일반 변수형일 경우
		if (_member is IFieldSymbol x)
		{
			// check) readonly면 안된다.
			if (x.IsReadOnly == true)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0002",
					"error",
					$"class '{x.ToString()}' is read-only.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				x.Locations.FirstOrDefault(),
				null));
			}

			// check) const type이면 안된다.
			if (x.IsConst == true)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0003",
					"error",
					$"class '{x.ToString()}' is const.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				x.Locations.FirstOrDefault(),
				null));
			}

			// check) temp) get type info
			if(IsSerialzable(x.Type) == false)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0005",
					"error",
					$"class '{x.ToString()}' have no [CGDK.serializable]", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				"",
				null));
			}

			// - write member info
			member_node_info.type_name = x.Type.ToString();
			member_node_info.type = get_field_type(x.Type);
			member_node_info.identifier = x.Name;
		}
		// 2-2) property형일 경우
		else if (_member is IPropertySymbol y)
		{
			// check) read_only or write_only면 안된다.
			if (y.IsReadOnly == true)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0002",
					"error",
					$"class '{y.ToString()}' is read-olny.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				y.Locations.FirstOrDefault(),
				null));
			}

			// check) read_only or write_only면 안된다.
			if (y.IsWriteOnly == true)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0004",
					"error",
					$"class '{y.ToString()}' is write-olny.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				y.Locations.FirstOrDefault(),
				null));
			}

			// check) temp) get type info
			if (IsSerialzable(y.Type) == false)
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0005",
					"error",
					$"class '{y.ToString()}' have no [CGDK.serializable]", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				y.Locations.FirstOrDefault(),
				null));
			}

			// - write member info
			member_node_info.type_name = y.Type.ToString();
			member_node_info.type = get_field_type(y.Type);
			member_node_info.identifier = y.Name;
		}

		// return) 
		return member_node_info;
	}

	//------------------------------------------------------------------
	// 5. class 추축해 내기
	//
	//    Serialier로 생성할 class 정보를 추출해 낸다.
	//    SyntaxTree에서 [CGDK.Attributes,Serializable]를 가진 class 정의들을
	//    찾아낸 후 그것으로 Semantic 정보를 얻어
	//	  최종적으로는 OBJECT_INFO정보를 만들어 추가해 준다.
	//
	//    1) 먼저 SyntaxTree로 부터 class declation 정보를 추출해 낸다.
	//       당연히 [CGDK.Attribute.Serializable] 속성(attribute)를 가진 class만골라낸다.
	//    2) class 정보를 담을 OBJECT_INFO정보를 생성한다.
	//	  3) 얻어낸 class의 syntax node로 semantic_model에서 semantic 정보를 얻어낸다.
	//    4) 얻어낸 semantic 정보로 class info를 생성한다.
	//       - type_name => namespace를 포함한 full name
	//       - identifier => serializer class 명으로 사용
	//	  6) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  7) class의 MEMBER_INFO들을 얻어내 등록한다.
	//       class의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//    8) 만들어진 OBJECT_INFO를 list에 등록한다.
	//
	//------------------------------------------------------------------
	private static  void GetClassDeclarationInfo(ref List<OBJECT_INFO> _output, GeneratorExecutionContext _context, in SyntaxTree _syntax_tree, in SemanticModel _semantic_model)
	{
		// 1) find class declation
		foreach (var iter in _syntax_tree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
							.Where(node => node.IsKind(SyntaxKind.ClassDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
							.Cast<ClassDeclarationSyntax>() // (4) ClassDeclarationSyntax 캐스팅해서
							.Where(x => (x.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
								.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any()))
							.ToList()) // (5) 리스트로~
		{
			// 2) alloc OBJECT_INFO
			var class_info = new OBJECT_INFO();

			// 3) temp) get type info
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
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0001",
					"error",
					$"class '{type_info.ToString()}' has has not public accessibitity.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				type_info.Locations.FirstOrDefault(),
				null));
			}

			// 5) make full typ name string and identifier name
			class_info.type_name = type_info.ToString();
			class_info.identifier = iter.Identifier.ToString() + iter.GetHashCode().ToString();

			// 6) make 'member_node_info' list
			class_info.list_member_node_info = [];

			// 7) gatter members info
			foreach (var member in type_info.GetMembers()
								.Where(x => x.Kind == SymbolKind.Field || x.Kind == SymbolKind.Property) // 1) Field(변수) 혹은 Property 만 얻어서
								.Where(x => (x.GetAttributes() // (2) Attribute 중에 "CGDK.Field"을 가진 것만 골라낸다!
									.Where(y => y.ToString() == "CGDK.Attribute.Field(true)").Any()))
								.ToList()) // (3) 리스트로~
			{
				// check)
				if (member.DeclaredAccessibility != Accessibility.Public)
				{
					_context.ReportDiagnostic(Diagnostic.Create(
					new DiagnosticDescriptor(
						"CBE0001",
						"error",
						$"member '{type_info.ToString()}.{member.Name}' has has not public accessibitity.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
					null,
					type_info.Locations.FirstOrDefault(),
					null));
				}

				// - get member mode info
				var member_node_info = GetMembeInfo(_context, member);

				// - add member_node_info
				class_info.list_member_node_info.Add(member_node_info);
			}

			// 8) add struct info
			_output.Add(class_info);
		}
	}

	//------------------------------------------------------------------
	// 6. struct 추축해 내기
	//
	//    Serialier로 생성할 struct 정보를 추출해 낸다.
	//
	//    1) 먼저 SyntaxTree로 부터 struct declation 정보를 추출해 낸다.
	//    2) struct 정보를 담을 OBJECT_INFO를 생성한다.
	//    3) type info를 semantic_model에서 얻어낸다.
	//	  4) struct info를 설정한다.
	//       - type_name => .로 연결된 full type_name (ex) CGDK.foo.bar.tee
	//       - identifier => serializer struct의 이름으로 사용할 것이다.
	//	  5) member_info를 담을 MEMBER_INFO의 list를 생성한다.
	//	  6) struct의 MEMBER_INFO들을 얻어내 등록한다.
	//       struct의 MEMBER 중에서 '[CGDK.Attribute.Field]' Attribute를 가진 멤버 변수나 멤버 Property 얻는다.
	//       얻은 멤버들의 자료형 이름(type_name),변수명(identifier)을 얻어낸다.
	//	  7) 만들어진 OBJECT_INFO를 list에 등록한다.
	//
	//------------------------------------------------------------------
	private static void GetStructDeclarationInfo(ref List<OBJECT_INFO> _output, GeneratorExecutionContext _context, in SyntaxTree _syntax_tree, in SemanticModel _semantic_model)
	{
		// 1) find struct class declation
		foreach (var iter in _syntax_tree.GetRoot().DescendantNodes() // (1) 모든 자손들 노드 중에
							.Where(node => node.IsKind(SyntaxKind.StructDeclaration)) // (2) Node Kind가 'class 선언'인 것만 골라서
							.Cast<StructDeclarationSyntax>() // (4) StructDeclarationSyntax로 캐스팅해서
							.Where(x => (x as StructDeclarationSyntax)?.AttributeLists // (3) Attribute 중에 "CGDK.Attribute.Serializable"을 가진 것만 골라낸다!
								.Where(x => x.ToString() == "[CGDK.Attribute.Serializable]").Any() ?? false)
							.ToList()) // (5) List로...
		{
			// 2) alloc OBJECT_INFO
			var struct_info = new OBJECT_INFO();

			// 3) temp) get type info
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
			{
				_context.ReportDiagnostic(Diagnostic.Create(
				new DiagnosticDescriptor(
					"CBE0001",
					"error",
					$"class '{type_info.ToString()}' has has not public accessibitity.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
				null,
				type_info.Locations.FirstOrDefault(),
				null));
			}

			// 4) make full typ name string and identifier name
			struct_info.type_name = type_info.ToString();
			struct_info.identifier = iter.Identifier.ToString() + iter.GetHashCode().ToString();

			// 5) make 'member_node_info' list
			struct_info.list_member_node_info = [];

			// 6) gatter members info
			foreach (var member in type_info.GetMembers()
								.Where(x => x.Kind == SymbolKind.Field || x.Kind == SymbolKind.Property) // 1) Field(변수) 혹은 Property 만 얻어서
								.Where(x => !(x.GetAttributes() // (2) Attribute 중에 "CGDK.Field"을 가진 것만 골라낸다!
									.Where(y => y.ToString() == "CGDK.Attribute.Field(false)").Any()))
								.ToList()) // (3) 리스트로~
			{
				// check)
				if (member.DeclaredAccessibility != Accessibility.Public)
				{
					_context.ReportDiagnostic(Diagnostic.Create(
					new DiagnosticDescriptor(
						"CBE0001",
						"error",
						$"member '{type_info.ToString()}.{member.Name}' has has not public accessibitity.", "CGDK.buffer.type", DiagnosticSeverity.Error, true),
					null,
					type_info.Locations.FirstOrDefault(),
					null));
				}

				// - get member mode info
				var member_node_info = GetMembeInfo(_context, member);

				// - add member_node_info
				struct_info.list_member_node_info.Add(member_node_info);
			}

			// 7) add struct info
			_output.Add(struct_info);
		}
	}


	//------------------------------------------------------------------
	// 7.  Source Generation (Serializer Class)
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
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = _object.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// -  value type
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, _object.{iter_member.identifier});");
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
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
				++count_primitive;
			}
			// -  value type
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
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
				if (iter_member.type == 2)
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
				if (iter_member.type == 2)
					_out.Append($"sizeof({iter_member.type_name})+");
				else if (iter_member.type == 1)
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier})+");
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
			if (iter_member.type != 2)
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
			// - value type
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = _object.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// -  value type
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, _object.{iter_member.identifier});");
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
			// -  value type
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
				++count_primitive;
			}
			// -  value type but assign
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
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
				if (iter_member.type == 2)
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
				if (iter_member.type == 2)
					_out.Append($"sizeof({iter_member.type_name})+");
				else if (iter_member.type == 1)
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(_object.{iter_member.identifier})+");
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
			if (iter_member.type != 2)
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
			// -  value type
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		*({iter_member.type_name}*)_ptr = temp.{iter_member.identifier}; _ptr += sizeof({iter_member.type_name});");
			}
			// -  value type but assign
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		serializer_{iter_member.identifier}.ProcessAppend(ref _ptr, _ptr_bound, temp.{iter_member.identifier});");
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
			// -  value type
			if (iter_member.type == 2)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = *({iter_member.type_name}*)_ptr; _ptr += sizeof({iter_member.type_name});");
				++count_primitive;
			}
			// -  value type but assign
			else if (iter_member.type == 1)
			{
				_out.AppendLine($"		temp.{iter_member.identifier} = serializer_{iter_member.identifier}.ProcessExtract(ref _ptr, ref _count);");
				++count_object;
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
				if (iter_member.type == 2)
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
				if (iter_member.type == 2)
					_out.Append($"sizeof({iter_member.type_name})+");
				else if (iter_member.type == 1)
					_out.Append($"serializer_{iter_member.identifier}.ProcessGetSizeOf(temp.{iter_member.identifier})+");
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
			if (iter_member.type != 2)
			{
				_out.AppendLine($"	 private readonly IBase<{iter_member.type_name}> serializer_{iter_member.identifier} = Get<{iter_member.type_name}>.instance;");
			}
		}

		_out.AppendLine("#nullable disable");
		_out.AppendLine("}");
	}
}