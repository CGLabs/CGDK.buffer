//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                  tutorials buffer (3) - struct serialize                  *
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
#if defined(_WIN32)
	#include <conio.h>
#endif
#include <iostream>
#include <string>

// 2) CGDK.buffer header file
#include "cgdk/shared_buffer"

// 3) using namespace 
using namespace CGDK;

enum class eMESSAGE_TYPE : int32_t
{
	A = 1, 
	B = 2
};

int main()
{
	// ------------------------------------------------------------------
	// 1. 단순 구조체를 사용한 append/extract
	//    기본 자료형을 구조체로 묶어서 append<T>와 extract<T>를 할 수 있다.
	//    char, int, float와 같은 기본형 데이터만 구성된 경우에만 사용가능하다는 한계가 있다.
	//    또 구조체의 정렬(allign)에 따라 다른 동작을 할 수 있다.
	// ------------------------------------------------------------------
	{
		// - 모두 기본 자료형으로만 구성된 구조체
		struct foo
		{
			int				a;
			eMESSAGE_TYPE	b;
			float			c;
			uint64_t		d;
		};

		// - DATA형 변수 s1
		foo s1{ 10, eMESSAGE_TYPE::A, 1.4f, 123 };

		// *1) get_size_of<T>(...)직렬화시의 데이터 크기를 얻을 수 있다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is " << size << " bytes\n";

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "bar.size_: " << bar.size() << " bytes\n";

		// *3) foo형을 extract해서 읽어낸다.
		/*auto v1 =*/ bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: " << s1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(s1.b) << '\n';
		std::cout << "c: " << s1.c << '\n';
		std::cout << "d: " << s1.d << '\n';
		std::cout << '\n';
	}


	// ------------------------------------------------------------------
	// 2. 구조체를 사용한 hetrogenous append/extract
	//
	//    int, float, uint64_t같은 기본 자료형이 아니라 std::vector, std:string
	//    다중 구조체 등과 같은 복합 자료형을 struct를 사용해 append/extract할 수 있다.
	//
	//    hetrogenous(복합) 자료형를 사용하기 위해서는 'ENABLE_STRUCT_SERIALIZABLE'만 선언해주면 된다.
	//    위치는 어디든 구조체 내에만 'ENABLE_STRUCT_SERIALIZABLE'만 선언 해주면 된다.
	//    또 이 구조체를 상속받은 모든 구조체는 구조체 직렬화를 수행한다.
	//	 
	//    (!주의) 'ENABLE_STRUCT_SERIALIZABLE'를 선언한 구조체는 생성자를 정의하면 안됀다는 것이다.
	//    반드시 기본 생성자를 유지해야 한다.
	//    만약 Ibuffer_serailzable을 상속받았다면 Ibuffer_serializable이 우선한다.
	// ------------------------------------------------------------------

	// heterogenouse struct!
	struct goo
	{
		ENABLE_STRUCT_SERIALIZABLE	// {!} 이것이 넣어준다! 

		int					a;
		eMESSAGE_TYPE		b;
		std::string			c;
		short				d;
		std::vector<int>	e;
	};

	{
		// - goo형 변수 s1
		goo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string";
		s1.d = 12;
		s1.e = { 10,20,30 };

		// *1) get_size_of<T>(...)로 직렬화시 데이터 크기를 얻는다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is " << size << " bytes\n";

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append<goo>(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "bar.size_: " << bar.size() << " bytes\n";

		// *3) goo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<goo>();

		// - goo를 출력한다.
		std::cout << "a: " << v1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: " << v1.c << '\n';
		std::cout << "d: " << v1.d << '\n';
		std::cout << "e: "; for(auto iter: v1.e) std::cout << iter << " "; std::cout << '\n';
		std::cout << '\n' << '\n';
	}


	// ------------------------------------------------------------------
	// 3. 구조체를 사용한 hetrogenous append/extract (2)
	//
	//    make_shared_buffer<T>(...);
	//
	//    'DEFINE_BUFFER_SERIALIZE'를 사용하면 make_shared_buffer를 사용해
	//    한번에 버퍼를 할당해 직렬화한 버퍼를 바로 생성할 수 있다.
	//
	//    즉, get_size_of() + alloc_shared_buffer() + append() 가 합쳐진
	//    것이다.
	//
	// ------------------------------------------------------------------
	{
		// - goo형 변수 s1
		goo s1{ 1, eMESSAGE_TYPE::A, "test string", 12, {10,20,30} };

		// *1) make_shared_buffer를 사용해 바로 직렬화한 버퍼를 얻는다.
		auto bar = make_shared_buffer(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "bar.size: " << bar.size() << " bytes\n";

		// - foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<goo>();

		// - foo를 출력한다.
		std::cout << "a: " << v1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: " << v1.c << '\n';
		std::cout << "d: " << v1.d << '\n';
		std::cout << "e: "; for (auto iter : v1.e) std::cout << iter << " ";
		std::cout << '\n' << '\n';
	}

}
