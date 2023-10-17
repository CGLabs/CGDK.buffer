//*****************************************************************************
//*                                                                           *
//*                               CGDK::buffer                                *
//*                       ver 4.0 / release 2021.11.01                        *
//*                                                                           *
//*                    tutorials buffer (1) - basic buffer                    *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
// 1) standard header file
#include <vector>
#include <list>
#include <map>
#include <array>
#if defined(_WIN32)
	#include <conio.h>
#endif
#include <iostream>
#include <chrono>

#if __cpp_lib_span
	#include <span>
#endif

// 2) CGDK.buffer header file
#include "cgdk/shared_buffer"

// 3) using namespace 
using namespace CGDK;

int main()
{
	// ------------------------------------------------------------------
	// 
	//                          CGDK.buffer.C++
	// 
	// 마법과 같이 동작하는 직렬화 기능을 가진 가벼운 버퍼 시스템입니다.
	// 복잡한 데이터의 직렬화와 역직렬화도 아주 간단히 작성할 수 있습니다.
	// 
	// * CGDK.buffer.C++ 특징
	//    1) 손쉬운 데이터 직렬화와 역직렬화를 제공합니다.
	//    2) template으로 제작되어 header파일의 include만으로 사용 가능합니다.
	//    3) 매우 빠릅니다.
	//    4) 대규모 다양하고 복잡한 형태의 데이터도 직렬화를 제공합니다.
	//    5) 직렬화와 역직렬화의 커스터마이즈가 가능합니다.
	// 
	// 
	// 게임 혹은 어플리케이션의 네트워크 송수신을 위해 최초 개발되었으나
	// 파일입출력, 화면입출력, 인자전달 등 다양한 용도로도 사용됩니다.
	// template으로 제작되어 헤더파일의 lib링크없이 include만으로 사용할 
	// 수 있습니다.
	// 즉 C++17이상만 지원하는 모든 플랫폼에서 사용가능합니다.
	// 따라서 일반적인 서버 뿐만 아니라 unreal 3d와 같은 플랫폼에서도 사용
	// 가능합니다.
	// 또 msvc, gcc, clang 등의 주요 c++ 컴파일러를 지원합니다.
	// 
	// ------------------------------------------------------------------

	// ------------------------------------------------------------------
	// 1. 간단한 사용법
	//    핵심 함수 2개만 알면 모든 직렬화와 역직렬화가 가능합니다.
	// 
	//     append<T>(...) 는 직렬화 함수로 버퍼에 데이터를 써넣는 함수.
	//     extract<T>() 는 역직렬화 버퍼에서 데이터를 읽어내는 함수.
	// 
	//    간단한 예제를 보자면.. int64_t형 값 100과 문자열 "test"를 직렬화
	//    하려면?
	//    먼저 버퍼에 메모리를 할당해야겠죠.
	// 
	//      foo.append(100);
	//      foo.append("test"sv);
	//     
	//    이라고만 하면 됩니다. 
	//    이렇게 직렬화한 데이터를 다시 역직렬화 하고 싶다면
	// 
	//      v1 = foo.extract<uint64_t>();
	//      v2 = foo.extract<std::string>();
	//    
	//    이라고만 하시면 됩니다. 간단하죠?
	//    근데 한가지 직렬화를 할 동적 버퍼를 할당 받고 싶다면?
	// 
	//      auto foo = alloc_shared_buffer(100); // 100byte 할당받음.     
	//      
	//      foo.append(100);
	//      foo.append("test"sv);
	// 
	// 2. buffer의 종류
	//    
	//     buffer_view    읽기 기능만 가능
	//                    extract<T>, front<T> 함수
	//                    data,size 두개의 변수로 구성되어 16byte 크기
	// 					  
	//     buffer         buffer_view를 상속 받아 쓰기기능을 추가
	//                    append<T> 함수
	//                    data와 size에 더해 bound정보(lower, upper) 추가
	//                    32byte의 크기
	// 
	//     shared_buffer  할당 받은 메모리를 스마트포이터로 관리하는 기능
	//                    32byte + shared_ptr<T> 크기를 가짐
	//                    alloc_buffer를 사용해 동적 할당
	// 
	// ------------------------------------------------------------------

	// ------------------------------------------------------------------
	// 1. shared_buffer와 메모리 할당
	// ------------------------------------------------------------------
	{
		std::cout << "1. alloc buffer " << '\n';

		// 1) shared_buffer에 alloc_shared_buffer()함수를 사용해 메모리를 할당받습니다.
		//    - 1000 byte의 메모리를 할당받는다.
		//    - 그리고 data_값에 할당받은 메모리의 포인터를 넣는다.
		//    - size_(버퍼의 길이)는 0으로 초기화 한다.
		shared_buffer baz = alloc_shared_buffer(1000);

		// 2) data()는 버퍼의 버퍼의 포인터 size()는 쓰여진 버퍼의 크기를 의미한다.(여기서는 0이 된다.)
		std::cout << "data_ " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// 설명) shared_buffer는 스마트 포인터의 기능을 가지고 있어서
		//       이 블럭이 끝나면 baz에 할당받은 버퍼는 자동적으로 소멸된다.
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 2. append<T>와 extract<T>
	// ------------------------------------------------------------------
	{
		std::cout << "2. append/extract" << '\n';

		// 1) shared_buffer에 1000 byte할당받기
		auto baz = alloc_shared_buffer(1000);

		// trace) 먼저 baz의 data_값과 len값을 출력한다.
		std::cout << "mem allocated>  "<< "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// 2) append()함수를 사용해 baz에 값을 써넣는다.
		baz.append<int>(100);		// int형으로 100을 써넣는다.
		baz.append<float>(3.14f);	// float형으로 3.14f을 써넣는다.
		baz.append<uint64_t>(1234);	// uint64_t형으로 123을 써넣는다.

		// check) 이렇게 append를 사용해 int(100)-4byte, float(3.14f)-4byte, uint64_t(123)-8byte을 써넣으면
		//   총 크기인 16byte만큼 size_값이 늘어나게 된다.
		std::cout << "data appended>  "<< "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// 3) extract()함수를 사용해 baz에서 값을 읽어낸다.
		//    써넣은 순서와 자료형 대로 값을 일어낸다.
		auto v1 = baz.extract<int>();
		auto v2 = baz.extract<float>();
		auto v3 = baz.extract<uint64_t>();

		// check) extract()함수를 사용해 써넣은 대로 값을 읽어내면 
		///  총크기인 16byte만큼 size_는 줄어들게 되며 포인터인 data값은 읽어낸 크기(16byte)만큼 증가하게 된다.
		std::cout << "data extracted> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// check) 읽어낸 값 출력
		std::cout << "v1: " << v1 << "  v2: " << v2 << "  v3: " << v3 << '\n';
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 3. 문자열 직렬화와 역직렬화
	// ------------------------------------------------------------------
	{
		std::cout << "3. string" << '\n';

		// 1) 1000 byte할당아 buffer를 생성한다.
		auto baz = alloc_shared_buffer(1000);

		// 2) append<T>함수로 문자열을 직렬화한다.
	#ifdef __cpp_lib_string_view
		baz.append<std::string_view>("how are you?");
	#endif
		baz.append<std::string>("i'm fine, thank you and you?");
		baz.append<std::wstring_view>(L"dou you know kimchi?");
		baz.append<std::wstring>(L"yes, i know psi too");
		baz.append<std::wstring_view>(L"이것 좀 테스트하게 해주세요.");
	#ifdef __cpp_char8_t
		baz.append<std::u8string_view>(u8"이것 좀 테스트하게 해주세요.");
	#endif
		baz.append<std::u16string_view>(u"これを試ためさせてください");
		baz.append<std::u32string_view>(U"これを試ためさせてください");

		// check)
		std::cout << "data appended>  " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';


		// 3) extract<T>()함수를 사용해 역직렬화한다.
		auto v1 = baz.extract<std::string>();
	#ifdef __cpp_lib_string_view
		auto v2 = baz.extract<std::string_view>();
	#endif
		auto v3 = baz.extract<std::wstring>();
		auto v4 = baz.extract<std::wstring_view>();
		auto v5 = baz.extract<std::wstring_view>();
	#ifdef __cpp_char8_t
		[[maybe_unused]] auto v6 = baz.extract<std::u8string_view>();
	#endif
		[[maybe_unused]] auto v7 = baz.extract<std::u16string_view>();
		[[maybe_unused]] auto v8 = baz.extract<std::u32string_view>();

		// check) 
		std::cout << "data extracted> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// check) extract한 문자열을 출력해본다.
		std::cout << "v1 " << v1 << std::endl;
		std::cout << "v2 " << v2 << std::endl;
		std::wcout << L"v3 " << v3 << std::endl;
		std::wcout << L"v4 " << v4 << std::endl;
		std::wcout << L"v5 " << v5 << std::endl;
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 4. 집합형 데이터 직렬화와 역직렬화 (1) 
	//    - std::vector<T>, std::list<T>, std::map<T>와 같은 데이터의 직렬화
	//    
	// ------------------------------------------------------------------
	{
		std::cout << "4. aggregration" << '\n';

		// declare)
		std::vector<int>              s1{ 10, 20, 30 };
		std::list<std::string>        s2{ "a", "b", "c" };
		std::vector<std::vector<int>> s3{{1,2},{3,4},{5,6}};
		std::map<std::string, int>    s4{ {"x",10},{"y",20},{"z",30}};

		// 1) 1000 byte할당아 buffer를 생성한다.
		auto baz = alloc_shared_buffer(1000);

		// 2) 데이터들을 써넣는다. (append시 템플릿의 자료형 인자를 생략하면 데이터 형을 그대로 인식한다.)
		baz.append(s1);
		baz.append(s2);
		baz.append(s3);
		baz.append(s4);
	#ifdef __cpp_lib_string_view
		baz.append<std::string_view>("ok");
	#endif

		// check)
		std::cout << "data appended>  " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// 3) extract<T>()함수를 사용해 값을 읽어낸다.
		auto v1 = baz.extract<std::vector<int>>();
		auto v2 = baz.extract<std::list<std::string>>();
		auto v3 = baz.extract<std::vector<std::vector<int>>>();
		auto v4 = baz.extract<std::map<std::string, int>>();
	#ifdef __cpp_lib_string_view
		auto v5 = baz.extract<std::string>();
	#endif

		// check) 
		std::cout << "data extracted> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// check) extract한 데이터들을 출력해본다.
		std::cout << "v1 "; for (auto& iter : v1) std::cout << iter << " "; std::cout << std::endl;
		std::cout << "v2 "; for (auto& iter : v2) std::cout << iter << " "; std::cout << std::endl;
		std::cout << "v3 "; for (auto& iter : v3) { std::cout << "{"; for (auto& iter2 : iter) std::cout << iter2; std::cout << "} "; }; std::cout << std::endl;
		std::cout << "v4 "; for (auto& iter : v4) std::cout << "{"<< iter.first << ", " << iter.second << "} " ; std::cout << std::endl;
		std::cout << "v5 " << v5 << std::endl;

#if __cpp_lib_span
		// declare) 
		std::span<int> s5{s1.begin(), s1.end()};
		std::span<std::vector<int>> s6{s3.begin(), s3.end()};

		// 4) 1000 byte할당아 buffer를 생성한다.
		auto bak = alloc_shared_buffer(1000);

		// 5) append std::span
		baz.append(s5);
		baz.append(s6);

		// 6) extact std::span
		//    - std::span<T>는 기본형 자료형혹은 기본형 자료형으로 구성된 자료형만 extract<T>, front<T>를 할수 있다.
		//    - 복합형 자료형의 경우 일반적인 선형 자료형(std::vector<T>, std::list<T>, ...)을 사용 해야 한다.
		auto v6 = baz.extract<std::span<int>>(); // 기본형이라 가능하다.
		auto v7 = baz.extract<std::vector<std::vector<int>>>(); // 복합형이라 std::span<T>로는 extract할수 없다.

		std::cout << "v6 "; for (auto& iter : v6) std::cout << iter << " "; std::cout << std::endl;
		std::cout << "v7 "; for (auto& iter : v7) { std::cout << "{"; for (auto& iter2 : iter) { std::cout << iter2 << " "; } std::cout << "} "; }; std::cout << std::endl;
#endif
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 5. 배열
	// ------------------------------------------------------------------
	{
		std::cout << "5. array" << '\n';

		// 설명)
		//   C의 전통적인 배열 변수의 직렬화도 지원한다.
		//   std::array나 std::vector와 같이 직렬화를 처리하기 때문에 상호
		//   호환이 가능하다.

		// - append할 배열 데이터
		int s1[4]{ 1,2,3,4 };
		std::string s2[2]{ "first", "second" };
		const char* s3[2]{ "first", "second" };

		// - 1000byte 버퍼를 할당 받음.
		auto baz = alloc_shared_buffer(1000);

		// 1) 배열을 buffer에 append함.
		baz.append(s1);
		baz.append(s2);
		baz.append(s3);
		baz.append(s3);
		baz.append(s3);

		// 설명) 배열은 내부적으로 다른 선형 컨테이너들과 동일하게 직렬화된다.
		//       따라서 배열로 append한 것을 std::vector나 std::array로 역직렬화 해낼 수 있다.
		//       배열 변수로 역직렬화는 불가능하다.

		// 2) 벼을을 extaact한다.
		std::array<int, 4>				v1 = baz.extract<std::array<int, 4>>();
		std::array<std::string, 2>		v2 = baz.extract<std::array<std::string, 2>>();
	#ifdef __cpp_lib_string_view
		std::array<std::string_view, 2> v3 = baz.extract<std::array<std::string_view, 2>>();
		std::vector<std::string_view>   v4 = baz.extract<std::vector<std::string_view>>();
		std::vector<std::string_view>   v5 = baz.extract<char* []>();
	#endif

		// 설명)
		//   배열인 const char* s3[2]를 append한 것을 std::array<std::string_view, 2>로도 extract해내고
		//   char*[]나 std::vector<std::string_view>로도 extract해냈다.
		//   이것은 선형 컨테이너끼리는 buffer에 저장되는 구조가 동일해 서로 호환되기 때문이다.
		//   즉, std::vector<T>로 append 한 것은 std::list<T>로 extract해 낼수 있다.
		//   std::array<T,N>로 append한 것 역시 std::vector<T>로 extract해 낼수 있다.
		//   std::vector<T>로 append한 것 역시 std::array<T,N>로 extract해 낼수 있으나
		//   extract해낼 std::array<T,N>가 append한 크기보다 작을 경우 exception을 던진다.

		// 출력)
		std::cout << "v1: {"; for (auto& iter : v1) std::cout << iter << ","; std::cout << "}" << '\n';
		std::cout << "v2: {"; for (auto& iter : v2) std::cout << iter << ","; std::cout << "}" << '\n';
	#ifdef __cpp_lib_string_view
		std::cout << "v3: {"; for (auto& iter : v3) std::cout << iter << ","; std::cout << "}" << '\n';
		std::cout << "v4: {"; for (auto& iter : v4) std::cout << iter << ","; std::cout << "}" << '\n';
		std::cout << "v5: {"; for (auto& iter : v5) std::cout << iter << ","; std::cout << "}" << '\n';
	#endif
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 6. front<T>로 읽기(peek)
	// ------------------------------------------------------------------
	{
		std::cout << "6. front<T>" << '\n';

		// - baz
		auto baz = alloc_shared_buffer(1000);
		baz.append<int>(100);
		baz.append<float>(3.14f);
		baz.append<uint64_t>(123);

		// - data()와 size()값을 출력한다.
		std::cout << "before> " << "data_: " << baz.data() << "  size_: " << baz.size() << '\n';

		// 1) front()함수를 사용하면 그냥 값을 읽어만 오고 data_와 size_값을 변경시키지 않는다.
		//    front()함수는 offset값을 넣어주면 그 위치에서 값을 일어온다.
		auto v1 = baz.front<int>(0);
		auto v2 = baz.front<float>(4);
		auto v3 = baz.front<uint64_t>(8);

		// - 읽어낸 값 출력
		std::cout << "v1: " << v1 << "  v2: " << v2 << "  v3: " << v3 << '\n';

		// - front()함수는 size_값을 변경시키지 않으므로  size_값은 front()함수 변경되지 않는다.
		std::cout << "after>  " << "data_: " << baz.data() << "  size_: " << baz.size() << '\n';
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 7. enum형 자료형
	//
	// ------------------------------------------------------------------
	{
		enum class eTEST : int32_t
		{
			A = 1,
			B = 2
		};

		// - 1000byte 버퍼를 생성함.
		auto baz = alloc_shared_buffer(1000);

		// - enum형 데이터를 써넣는다.
		baz.append<eTEST>(eTEST::A);
		baz.append<eTEST>(eTEST::B);

		// - enum형 데이터를 읽어온다.
		/*auto value1 =*/ baz.extract<eTEST>();
		/*auto value2 =*/ baz.extract<eTEST>();
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 8. 시간 자료형 (tm, std::chrono::time_point)
	//
	// ------------------------------------------------------------------
	{
		std::cout << "8. chrono" << '\n';

		// - 임시로 time을 얻는다.
		auto t1 = std::chrono::system_clock::now(); // std::chrono::system_clock::time_point
		auto t2 = std::chrono::system_clock::to_time_t(t1); // std::time_t

		// - 1000byte 버퍼 할당
		auto baz = alloc_shared_buffer(1000);

		// *1) buf에 std::vector와 std::map을 append함.
		baz.append(t1);
		baz.append(t2);

		// - baz의 size_값을 출력한다. 
		std::cout << "size_: " << baz.size() << '\n';

		// *2) 이것을 extract해냄
		/*auto v1 =*/ baz.extract<std::chrono::system_clock::time_point>();
		/*auto v2 =*/ baz.extract<time_t>();
	}
	std::cout << std::endl;

 	// ------------------------------------------------------------------
	// 9. std::tuple과 std::tie (1)
	//
	//    - tuple/tie은 데이터를 묶어서 전송하거나 분리해서 전송할 때 아주 유용하다.
	//    - 구조체 등과의 처리에서도 매우 유용하게 쓸수 있다. (추후 설명)
	//
	// ------------------------------------------------------------------
	{
		std::cout << "9. std::tuple/std::tie (1)" << '\n';

		int s1 = 10;
		std::string s2 = "test string";
		float s3 = 1.0f;

		// - 1000byte 버퍼 할당
		auto baz = alloc_shared_buffer(1000);

		// 1) std::tuple로 값을 append한다.
		baz.append(std::tuple{ s1, s2, s3 });

		int v1;
		std::string v2;
		float v3;

		// 2) std::tie를 사용해 값을 얻어온다.
		std::tie ( v1, v2, v3 ) = baz.extract<std::tuple<int, std::string, float>>();

		// 출력)
		std::cout << "v1: " << v1 << ", v2: " << v2 << "v3: " << v3 << '\n';
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 10. std::tuple과 structred binding 문법(2)
	//
	//    - structed binding과 함께 사용하면 일일이 변수선언하는 것을 피할수 있다.
	//    - 이 역시 tuple과 보다는 구조체를 사용한 extract에 더 많이 사용된다.
	//
	// ------------------------------------------------------------------
	{
		std::cout << "10. std::tuple (2)" << '\n';

		int s1 = 10;
		std::string s2 = "test string";
		float s3 = 1.0f;

		// - 1000byte 버퍼 할당
		auto baz = alloc_shared_buffer(1000);

		// 1) std::tuple로 값을 append한다.
		baz.append(std::tuple{ s1, s2, s3 });

		// 2) structred binding을 사용해서 extract한 값을 받는다.
		auto [ v1, v2, v3 ] = baz.extract<std::tuple<int, std::string, float>>();

		// 출력)
		std::cout << "v1: " << v1 << ", v2: " << v2 << "v3: " << v3 << '\n';
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 11. 버퍼
	//
	// ------------------------------------------------------------------
	{
		std::cout << "11. buffer" << '\n';

		// - append할 buffer 데이터
		auto buf_temp = alloc_shared_buffer(32);
		buf_temp.append<int>(32);
	#ifdef __cpp_lib_string_view
		buf_temp.append<std::string_view>("test");
	#endif

		// - 1000byte 버퍼 할당
		auto baz = alloc_shared_buffer(1000);

		// 1) buffer를 추가함
		baz.append(buf_temp);

		// 2) extaact한다.
		/*auto v1 =*/ baz.extract<buffer_view>();
	}
	std::cout << std::endl;

	// ------------------------------------------------------------------
	// 12. 단순 구조체 직렬화
	//    - 단순 구조체를 직렬화 하는 것이다.
	//    - 단순한 메모리 복사만을 하는 처리를 말하는 것이며
	//      (Herogeouns 구조체의 직렬화는 tutorial03,04,05를 참조)
	// ------------------------------------------------------------------
	{
		std::cout << "12. structure serialization" << '\n';

		// declare) 구조체
		struct STEMP
		{
			int x;
			float y;
			uint64_t z;
		};

		// 1) 구조체에 값 설정
		STEMP temp;
		temp.x = 10;
		temp.y = 3.14f;
		temp.z = 123;

		// 1) shared_buffer에 1000 byte할당받기
		auto baz = alloc_shared_buffer(1000);

		// 3) 데이터들을 써넣는다. (append시 템플릿의 자료형 인자를 생략하면 데이터 형을 그대로 인식한다.)
		baz.append(temp);

		// check)
		std::cout << "data appended>  " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// 4) extract<T>()함수를 사용해 값을 읽어낸다.
		auto v1 = baz.extract<STEMP>();

		// check) 
		std::cout << "data extracted> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';

		// check) extract한 데이터들을 출력해본다.
		std::cout << "v1.x " << v1.x << std::endl;
		std::cout << "v1.y " << v1.y << std::endl;
		std::cout << "v1.z " << v1.z << std::endl;
	}
	std::cout << std::endl;

	[[maybe_unused]] auto ch =  _getch();
}
