//*****************************************************************************
//*                                                                           *
//*                               CGDK::buffer                                *
//*                       ver 3.03 / release 2023.10.17                       *
//*                                                                           *
//*                  tutorials buffer (6) - static buffer                     *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  programmed by Cho SangHyun. sangduck@cgcii.com                           *
//*                                                                           *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
// 1) standard header file
#include <vector>
#include <list>
#include <map>
#include <string>
#if defined(_WIN32)
	#include <conio.h>
#endif
#include <iostream>
#include <array>

// 2) CGDK.buffer header file
#include "cgdk/shared_buffer"

// 3) using namespace 
using namespace CGDK;

enum class eMESSAGE_TYPE : int32_t
{
	NONE = 0,
	A = 1,
	B = 2
};

int main()
{
	// ------------------------------------------------------------------
	//
	// 1. 배열을 buffer 메모리로 사용하기
	//
	//    배열이나 std::araay와 같은 변수도 buffer 메모리로 활용할 수 있다.
	//    CGDK::buffer_view 혹은 CGDK::buffer로만 사용 가능하다.
	//    동적할당을 하지 않아 성능에 많은 이점이 있다. 
	//    하지만 메모리의 소멸을 유의할 필요가 있다.
	//    
	// ------------------------------------------------------------------
	{
		// 1) 배열!! 이것을 buffer의 메모리로 사용한다.
		char temp[64];

		// 2) 배열을 buffer로 활용하기 
		buffer bar{ temp };

		// 설명) 베열을 넣게 되면 배열의 크기 안에서 append가 가능하다.
		//       위의 예제에서는 64byte만큼 append할 수 있다.

		// 3) append한다.
		{
			bar.append<int>(1);
			bar.append<float>(10.0f);
			bar.append<std::string>("test_string");
			bar.append<std::vector<int>>();

			// - bar의 size_값을 출력한다. 
			std::cout << "bar.size " << bar.size() << " bytes\n";
		}

		// 4) extract하기.
		{
			// - extract
			auto v1 = bar.extract<int>();
			auto v2 = bar.extract<float>();
			auto v3 = bar.extract<std::string>();
			auto v4 = bar.extract<std::vector<int>>();

			// - foo를 출력한다.
			std::cout << "v1: " << v1 << std::endl;
			std::cout << "v2: " << static_cast<int32_t>(v2) << std::endl;
			std::cout << "v3: " << v3 << std::endl;
			std::cout << "v4: "; for (auto iter : v4) std::cout << iter << " "; std::cout << std::endl;
		}
	}

	// ------------------------------------------------------------------
	//
	// 2. std::array<T,N>을 buffer 메모리로 사용하기
	//
	//    배열이나 std::araay와 같은 메모리르 buffer의 메모리로 활용할수 있다.
	//    CGDK::buffer_view 혹은 CGDK::buffer로만 사용 가능하다.
	//    기능과 동작은 배열과 동일하다. 
	//    
	// ------------------------------------------------------------------
	{
		// 1) std:!! 이것을 buffer의 메모리로 사용한다.
		std::array<char, 64> temp;

		// 설명) std::array도 배열과 같은 방법으로 사용 가능ㅎ다.
		// *2) 배열을 buffer로 활용하기
		buffer bar{ temp };

		// 3) append한다.
		{
			bar.append<int>(1);
			bar.append<float>(10.0f);
			bar.append<std::string>("test_string");
			bar.append<std::vector<int>>();

			// - bar의 size_값을 출력한다. 
			std::cout << "bar.size " << bar.size() << " bytes\n";
		}

		// 4) extract하기.
		{
			// - extract
			auto v1 = bar.extract<int>();
			auto v2 = bar.extract<float>();
			auto v3 = bar.extract<std::string>();
			auto v4 = bar.extract<std::vector<int>>();

			// - foo를 출력한다.
			std::cout << "v1: " << v1 << std::endl;
			std::cout << "v2: " << static_cast<int32_t>(v2) << std::endl;
			std::cout << "v3: " << v3 << std::endl;
			std::cout << "v4: "; for (auto iter : v4) std::cout << iter << " "; std::cout << std::endl;
		}
	}


	// ------------------------------------------------------------------
	//
	// 3. 정적 메모리 버퍼 append 중 오버플로우가 발생하면?
	//
	//    정적 메모리 크기 이상으로 쓸 경우 예외를 던진다.
	// 
	//    1) debug에서는 ASSERT에 걸리도록 되어 있다.
	//       overflow가 발생한 위치를 확인 할수 있도록 ASSERT를 건다.
	//    2) release에서만 그냥 exception을 던진다.
	//    3) 만약 debug에서 ASSERT 안 걸리게 하고 싶다면 
	// 
	//       #define CGDK_DISABLE_ASSERT
	// 
	//		을 buffer 파일을 include하기 전에 넣어준다.
	//    
	// ------------------------------------------------------------------
	{
		// 1) 배열!! 이것을 buffer의 메모리로 사용한다.
		char temp[32];

		// 2) 배열을 buffer로 활용하기
		buffer bar{ temp };

		// 3) append한다.
		try
		{
			bar.append<int>(1);
			bar.append<float>(10.0f);
			bar.append<std::string>("this is overflow test!!! it occure overflow exception!");
			
			// - bar의 size_값을 출력한다. 
			std::cout << "bar.size " << bar.size() << " bytes\n";
		}
		catch (...)
		{
			std::cout << "exception!! buffer overflow!!!" << std::endl;
		}
	}
}
