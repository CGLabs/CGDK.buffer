//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                   tutorials buffer (2) - append/extract                   *
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

#ifdef _WIN32
	#pragma warning(disable:4189)
#endif

int main()
{
	// - baz
	shared_buffer baz = alloc_shared_buffer(1000);
	baz.append<int>(100);
	baz.append<float>(3.14f);
	baz.append<uint64_t>(123);


	// ------------------------------------------------------------------
	// 1. CGDK::shared_buffer 복사하기
	// ------------------------------------------------------------------
	{
		// 1) baz값을 복사하면? 버퍼는 스마트포인터로 공유되며 얕은 복사가 수행된다.
		//    qux와 baz는 버퍼를 공유한테 data_와 size_가 동일한 값을 가진다.
		shared_buffer qux = baz;

		// 2) qux의 값을 변경시키면?
		//    qux와 baz는 버퍼를 공유하고 있기 때문에 baz의 해당 값 역시 변경된다.
		qux.front<int>(0) = 33;

		//// check) qux와 baz의 제일 앞 int값 출력
		//std::cout << "baz: " << baz.front<int>(0) << "  qux: " << qux.front<int>(0) << '\n';

		// 3) qux에 extract를 수행하면? qux의 data_값과 size_값만 변경되며
		//    baz의 data_와 size_값은 변경되지 않는다.
		qux.extract<int>();

		// 4) baz에 append를 하면 baz의 size_값은 변경되지만 qux의 값은 변하지 않는다.
		baz.append<int>(100);

		// 설명) 즉 CGDK::shared_buffer를 복사하게 되면 data_와  size_는 독립적인 값을 가지며
		//      메모리 버퍼 자체는 공유한다는 것이다.

		// check) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "qux> " << "data_: " << (uint64_t)qux.data() << "  size_: " << qux.size() << '\n';

		// 5) clone을 하면 깊은 복사를 할 수 있다.
		//    clon을 하면 버퍼를 신규 할당받아 복사하기 때문에 버퍼를 완전히 분리한다.
		auto zoo = baz.clone();
	}


	// ------------------------------------------------------------------
	// 2. CGDK::buffer_view
	// ------------------------------------------------------------------
	{
		// 1) CGDK::shared_buffer에서 CGDK::buffer_view로 대입이 가능하다.
		buffer_view kiv = baz;

		// 2) CGDK::buffer_view는 extract<T>()나 front<T>()만 된다.
		auto value1 = kiv.front<float>(4); // Ok
		auto value2 = kiv.extract<int>(); // Ok

		// 3) CGDK::buffer_view는 append는 불가능하다
		//kiv.append<int>(100); // error

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "value1: " << value1 << "  value2: " << value2 << '\n';
	}


	// ------------------------------------------------------------------
	// 3. CGDK::buffer
	// ------------------------------------------------------------------
	{
		// 1) CGDK::buffer
		buffer val = baz;

		// 2) CGDK::buffer_view는 extract<T>()나 front<T>()와 append<T>()까지 된다.
		val.append<int>(100);

		// 3) CGDK::buffer_view로도 대입이 된다.
		buffer_view kiv = val;

		// 4) CGDK::buffer_view에서 CGDK::basic_view로는 대입될수 없다.(^연산을 사용해야 한다.)
		val = kiv; // error
	}

	{
		// 1) CGDK::shared_buffer에서 부분 버퍼를 할당받아 합치는 용도로 많이 사용된다.
		buffer kal = baz;

		// 2) kal에 append<T>등 버퍼 조작을 수행한다.
		kal.append<int>(100);
		kal.append<float>(100);

		// 3) 처리를 끝낸 후 baz에 적용한다.
		baz ^= kal;
	}


	// ------------------------------------------------------------------
	// 4. basic operator 
	// ------------------------------------------------------------------
	// 1) CGDK::buffer + CGDK::offset(VALUE) 연산
	{

		// 1) offset 8byte를 줘서 얕은 복사를 한다.
		//    - baz에서 offset(8byte) 만큼 extract 후 qux에 넣는다.
		auto qux = baz + offset(8);

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "qux> " << "data_: " << (uint64_t)qux.data() << "  size_: " << qux.size() << '\n';
	}

	// 2) CGDK::buffer + CGDK::size(VALUE) 연산
	{
		// 2) size()를 사용하면 길이를 변경할 수 있다.
		auto tie = baz + size(4);

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "tie> " << "data_: " << (uint64_t)tie.data() << "  size_: " << tie.size() << '\n';
	}

	// 3) CGDK::buffer ^ [int] 연산
	{
		// 3) 길이값만 변경하기 ^ 연산자를 사용하면 size_값만 4로 변경하게 된다.
		auto koo = baz ^ 4;

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "koo> " << "data_: " << (uint64_t)koo.data() << "  size_: " << koo.size() << '\n';
	}

	// 4) CGDK::buffer + CGDK::offset 연산과 buffer ^ [int] 연산 같이 사용하기
	{
		// 4) ^ 연산자를 사용해 data_는 data_ + 2, 길이는 4로 변경 (주의! 연산자의 우선순위에 주의 ^가 + 보다 우선이다)
		auto hoo = (baz + offset(2)) ^ 4;

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "hoo> " << "data_: " << (uint64_t)hoo.data() << "  size_: " << hoo.size() << '\n';
	}

	// 5) CGDK::buffer ^ CGDK::buffer_view() 연산
	{
		// 5) 4)과 같은 처리를 이렇게 할수도 있다.
		auto hol = baz ^ buffer_view{ baz.data() + 2, 4 };

		// trace) baz의 data_와 size_값을 출력한다.
		std::cout << "baz> " << "data_: " << (uint64_t)baz.data() << "  size_: " << baz.size() << '\n';
		std::cout << "hol> " << "data_: " << (uint64_t)hol.data() << "  size_: " << hol.size() << '\n';
	}
}
