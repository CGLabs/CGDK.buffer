//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                  tutorials buffer (4) - buffer serialize                  *
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
	NONE = 0,
	A = 1,
	B = 2
};

int main()
{
	// ------------------------------------------------------------------
	//
	// 1. Ibuffer_serializable을 사용한 직렬화
	//
	//    Ibuffer_serializable을 상속받아 직렬화를 직접 정의할 수 있다.
	//    Ibuffer_serializable을 상속받은 후 다음 3개의 virtual 함수를 정의한다.
	//    
	//    (v) process_serialize_in
	//        - extract할 때 호출되는 함수로 전달되어오는 _buffer로부터 값을 
	//          읽어내어 값을 저장하도록 한다.
	//
	//    (v) process_serialize_out
	//        - append를 할 때 호출되는 함수로 전달된 _buffer에 데이터를 써넣
	//          것을 정의한다.
	//
	//    (v) process_serialize_in
	//        - get_size_of()가 호출되었을 때 호출되는 함수로 append시 필요한
	//          크기를 리턴한다.
	// 
	// ------------------------------------------------------------------
	{
		struct foo : public Ibuffer_serializable
		{
			int					a = 0;
			eMESSAGE_TYPE		b = eMESSAGE_TYPE::NONE;
			std::string			c;
			short				d = 0;
			std::vector<int>	e;

			virtual	void		process_serialize_in(buffer_view& _buffer) override
			{
				a = _buffer.extract<int>();
				b = _buffer.extract<eMESSAGE_TYPE>();
				c = _buffer.extract<std::string>();
				d = _buffer.extract<short>();
				e = _buffer.extract<std::vector<int>>();
			}
			virtual	void		process_serialize_out(buffer& _buffer) override
			{
				_buffer.append<int>(a);
				_buffer.append<eMESSAGE_TYPE>(b);
				_buffer.append<std::string>(c);
				_buffer.append<short>(d);
				_buffer.append<std::vector<int>>(e);
			}
			virtual std::size_t	process_size_of() const override
			{
				size_t temp = 0;

				temp += get_size_of(a);
				temp += get_size_of(b);
				temp += get_size_of(c);
				temp += get_size_of(d);
				temp += get_size_of(e);

				return temp;
			}
		};

		// - DATA형 변수 s1
		foo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string";
		s1.d = 12;
		s1.e = std::vector{ 10,20,30 };

		// *1) get_size_of<T>(...)직렬화시의 데이터 크기를 얻을 수 있다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is " << size << " bytes\n";

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "foo.size_ " << bar.size() << " bytes\n";

		// *3) foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: " << v1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: " << v1.c << '\n';
		std::cout << "d: " << v1.d << '\n';
		std::cout << "e: ";
		for(auto iter: v1.e)
			std::cout << iter << " ";
		std::cout << '\n' << '\n';
	}


	// ------------------------------------------------------------------
	// 2. 구조체를 사용한 hetrogenous append/extract (1)
	//
	//    Ibuffer_serializable 관련 함수를 'DEFINE_BUFFER_SERIALIZE'를 사용해
	//    간단히 정의할 수 있다.
	//
	//    get_size_of<T>(...) 함수를 사용해 직렬화 크기르르 얻을 수 있다.
	//
	// ------------------------------------------------------------------

	// Ibuffer_serialzable을 정의한다!
	// - DEFINE_BUFFER_SERIALIZE를 사용하면 손쉽게 정의가 가능하다.
	struct foo : public Ibuffer_serializable
	{
	public:
		int					a = 0;
		eMESSAGE_TYPE		b = eMESSAGE_TYPE::NONE;
		std::string			c;
		short				d = 0;
		std::vector<int>	e;

		DEFINE_BUFFER_SERIALIZE(a,b,c,d,e); // (!) 이거!!
	};

	{
		// - DATA형 변수 s1
		foo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string";
		s1.d = 12;
		s1.e = std::vector{ 10,20,30 };

		// *1) get_size_of<T>(...)직렬화시의 데이터 크기를 얻을 수 있다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is " << size << " bytes\n";

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "foo.size_ " << bar.size() << '\n';

		// *3) foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: " << v1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: " << v1.c << '\n';
		std::cout << "d: " << v1.d << '\n';
		std::cout << "e: "; for (auto iter : v1.e) std::cout << iter << " ";
		std::cout << '\n' << '\n';
	}

	// ------------------------------------------------------------------
	// 3. 구조체를 사용한 hetrogenous append/extract (2)
	//
	//    역시 make_shared_buffer<T>(...)를 사용할 수 있다.
	//
	// ------------------------------------------------------------------
	{
		// - DATA형 변수 s1
		foo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string";
		s1.d = 12;
		s1.e = std::vector{ 10,20,30 };

		// *1) make_shared_buffer를 사용해 바로 직렬화한 버퍼를 얻는다.
		auto bar = make_shared_buffer(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "foo.size_ " << bar.size() << " bytes\n";

		// - foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: " << v1.a << '\n';
		std::cout << "b: " << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: " << v1.c << '\n';
		std::cout << "d: " << v1.d << '\n';
		std::cout << "e: "; for (auto iter : v1.e) std::cout << iter << " ";
		std::cout << '\n' << '\n';
	}
}
