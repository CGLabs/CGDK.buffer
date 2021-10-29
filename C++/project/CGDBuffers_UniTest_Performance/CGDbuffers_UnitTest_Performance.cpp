#include "stdafx.h"
#include "CppUnitTest.h"

#if _MSC_VER>=1700
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif
const int _TEST_COUNT	= 1000000;

namespace CGDBuffers_UniTest
{		
	TEST_CLASS(CGDbuffer_Cpp_UnitTest_Performance)
	{
	public:
		template<class T>
		CGD::buffer function_STRING_append(T* _List)
		{
			// 1) 
			CGD::buffer	bufferTemp	 = malloc(2048);

			// 2) 
			bufferTemp.append<T>(_List[0]);
			bufferTemp.append<T>(_List[1]);
			bufferTemp.append<T>(_List[2]);
			bufferTemp.append<T>(_List[3]);
			bufferTemp.append<T>(_List[4]);
			bufferTemp.append<T>(_List[5]);
			bufferTemp.append<T>(_List[6]);
			bufferTemp.append<T>(_List[7]);

			// Return) 
			return	bufferTemp;
		}

		template<class T>
		void function_extract_STRING(CGD::buffer _Buffer)
		{
			// 1) extract TEST
			{
				T	strValue1	 = _Buffer.extract<T>();
				T	strValue2	 = _Buffer.extract<T>();
				T	strValue3	 = _Buffer.extract<T>();
				T	strValue4	 = _Buffer.extract<T>();
				T	strValue5	 = _Buffer.extract<T>();
				T	strValue6	 = _Buffer.extract<T>();
				T	strValue7	 = _Buffer.extract<T>();
				T	strValue8	 = _Buffer.extract<T>();
			}
		}

		template<class T>
		void function_front_STRING(CGD::buffer _Buffer)
		{
			{
				// Declare)
				CGD::POS	tempPos;

				// 3) Read
				T	strValue1	 = _Buffer.front<T>(tempPos);
				T	strValue2	 = _Buffer.front<T>(tempPos);
				T	strValue3	 = _Buffer.front<T>(tempPos);
				T	strValue4	 = _Buffer.front<T>(tempPos);
				T	strValue5	 = _Buffer.front<T>(tempPos);
				T	strValue6	 = _Buffer.front<T>(tempPos);
				T	strValue7	 = _Buffer.front<T>(tempPos);
				T	strValue8	 = _Buffer.front<T>(tempPos);
			}

		}

		void function_append_GENERAL(CGD::buffer& _Buffer)
		{
			_Buffer.append<char>(12);
			_Buffer.append<unsigned char>(3);
			_Buffer.append<wchar_t>(4);
			_Buffer.append<char16_t>(10);
			_Buffer.append<char32_t>(22);
			_Buffer.append<int16_t>(4100);
			_Buffer.append<uint16_t>(32210);
			_Buffer.append<int32_t>(123310);
			_Buffer.append<uint32_t>(121234);
			_Buffer.append<int64_t>(-1000443);
			_Buffer.append<uint64_t>(12233094310);
			_Buffer.append<float>(1.0f);
			_Buffer.append<double>(2.0);
		}

		void function_extract_GENERAL(CGD::buffer _Buffer)
		{
			auto	value1	 = _Buffer.extract<char>();
			auto	value2	 = _Buffer.extract<unsigned char>();
			auto	value3	 = _Buffer.extract<wchar_t>();
			auto	value4	 = _Buffer.extract<char16_t>();
			auto	value5	 = _Buffer.extract<char32_t>();
			auto	value6	 = _Buffer.extract<int16_t>();
			auto	value7	 = _Buffer.extract<uint16_t>();
			auto	value8	 = _Buffer.extract<int32_t>();
			auto	value9	 = _Buffer.extract<uint32_t>();
			auto	value10	 = _Buffer.extract<int64_t>();
			auto	value11	 = _Buffer.extract<uint64_t>();
			auto	value12	 = _Buffer.extract<float>();
			auto	value13	 = _Buffer.extract<double>();
		}

		void function_front_GENERAL(CGD::buffer _Buffer)
		{
			int	iPosNow	 = 0;

			auto	value1	 = _Buffer.front<char>(iPosNow);			iPosNow+=sizeof(char);
			auto	value2	 = _Buffer.front<unsigned char>(iPosNow);	iPosNow+=sizeof(unsigned char);
			auto	value3	 = _Buffer.front<wchar_t>(iPosNow);			iPosNow+=sizeof(wchar_t);
			auto	value4	 = _Buffer.front<char16_t>(iPosNow);		iPosNow+=sizeof(char16_t);
			auto	value5	 = _Buffer.front<char32_t>(iPosNow);		iPosNow+=sizeof(char32_t);
			auto	value6	 = _Buffer.front<int16_t>(iPosNow);			iPosNow+=sizeof(int16_t);
			auto	value7	 = _Buffer.front<uint16_t>(iPosNow);		iPosNow+=sizeof(uint16_t);
			auto	value8	 = _Buffer.front<int32_t>(iPosNow);			iPosNow+=sizeof(int32_t);
			auto	value9	 = _Buffer.front<uint32_t>(iPosNow);		iPosNow+=sizeof(uint32_t);
			auto	value10	 = _Buffer.front<int64_t>(iPosNow);			iPosNow+=sizeof(int64_t);
			auto	value11	 = _Buffer.front<uint64_t>(iPosNow);		iPosNow+=sizeof(uint64_t);
			auto	value12	 = _Buffer.front<float>(iPosNow);			iPosNow+=sizeof(float);
			auto	value13	 = _Buffer.front<double>(iPosNow);			iPosNow+=sizeof(double);
		}

		void function_front_with_pos_GENERAL(CGD::buffer _Buffer)
		{
			CGD::POS	posNow;

			auto	value1	 = _Buffer.front<char>(posNow);
			auto	value2	 = _Buffer.front<unsigned char>(posNow);
			auto	value3	 = _Buffer.front<wchar_t>(posNow);
			auto	value4	 = _Buffer.front<char16_t>(posNow);
			auto	value5	 = _Buffer.front<char32_t>(posNow);
			auto	value6	 = _Buffer.front<int16_t>(posNow);
			auto	value7	 = _Buffer.front<uint16_t>(posNow);
			auto	value8	 = _Buffer.front<int32_t>(posNow);
			auto	value9	 = _Buffer.front<uint32_t>(posNow);
			auto	value10	 = _Buffer.front<int64_t>(posNow);
			auto	value11	 = _Buffer.front<uint64_t>(posNow);
			auto	value12	 = _Buffer.front<float>(posNow);
			auto	value13	 = _Buffer.front<double>(posNow);
		}
		
		TEST_METHOD(TestMethod_General_append_extract)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer 할당
			CGD::buffer bufferCreate(tempBuffer);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 대입
				CGD::buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append<char>(3);
				bufferTemp.append<unsigned char>(4);
				bufferTemp.append<int16_t>(4100);
				bufferTemp.append<uint16_t>(32210);
				bufferTemp.append<int32_t>(123310);
				bufferTemp.append<uint32_t>(121234);
				bufferTemp.append<int64_t>(-1000443);
				bufferTemp.append<uint64_t>(12233094310);
				bufferTemp.append<float>(1.0f);
				bufferTemp.append<double>(2.0);

				// 4) 값 읽기
				auto	value1	 = bufferTemp.extract<char>();
				auto	value2	 = bufferTemp.extract<unsigned char>();
				auto	value6	 = bufferTemp.extract<int16_t>();
				auto	value7	 = bufferTemp.extract<uint16_t>();
				auto	value8	 = bufferTemp.extract<int32_t>();
				auto	value9	 = bufferTemp.extract<uint32_t>();
				auto	value10	 = bufferTemp.extract<int64_t>();
				auto	value11	 = bufferTemp.extract<uint64_t>();
				auto	value12	 = bufferTemp.extract<float>();
				auto	value13	 = bufferTemp.extract<double>();
			}
		}


		TEST_METHOD(TestMethod_String_append_extract)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer 할당
			CGD::buffer bufferCreate(tempBuffer);

			wchar_t*	stringExtract[8];

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 대입
				CGD::buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append<wchar_t*>(array_string_wchar_t[0]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[1]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[2]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[3]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[4]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[5]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[6]);
				bufferTemp.append<wchar_t*>(array_string_wchar_t[7]);

				// 4) 값 읽기
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
				stringExtract[0] = bufferTemp.extract<wchar_t*>();
			}
		}

		TEST_METHOD(TestMethod_List_int_append_extract)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer 할당
			CGD::buffer bufferCreate(tempBuffer);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 대입
				CGD::buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(array_int);

				// 4) 값 읽기
				auto	temp = bufferTemp.extract<std::vector<int>>();
			}
		}


		TEST_METHOD(TestMethod_List_string_append_extract)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer 할당
			CGD::buffer bufferCreate(tempBuffer);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 대입
				CGD::buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(array_std_string_stdwstring);

				// 4) 값 읽기
				auto	temp = bufferTemp.extract<std::vector<wchar_t*>>();
			}
		}

		TEST_METHOD(TestMethod_Associated_string_list_int_append_extract)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer 할당
			CGD::buffer bufferCreate(tempBuffer);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 대입
				CGD::buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(map_std_wstring_vector_int);

				// 4) 값 읽기
				auto	temp = bufferTemp.extract<std::map<wchar_t*, std::vector<int>>>();
			}
		}

	};
}