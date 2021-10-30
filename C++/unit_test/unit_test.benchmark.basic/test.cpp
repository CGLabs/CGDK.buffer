#include "pch.h"

const int _TEST_COUNT = 1000000;

namespace CGDK
{
	template<class T>
	CGDK::buffer function_STRING_append(T* _List)
	{
		// 1) 
		CGDK::buffer buf_temp = malloc(2048);

		// 2) 
		buf_temp.append<T>(_List[0]);
		buf_temp.append<T>(_List[1]);
		buf_temp.append<T>(_List[2]);
		buf_temp.append<T>(_List[3]);
		buf_temp.append<T>(_List[4]);
		buf_temp.append<T>(_List[5]);
		buf_temp.append<T>(_List[6]);
		buf_temp.append<T>(_List[7]);

		// Return) 
		return	buf_temp;
	}

	template<class T>
	void function_extract_STRING(CGDK::buffer _buffer)
	{
		[[maybe_unused]] T str_value_1 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_2 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_3 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_4 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_5 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_6 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_7 = _buffer.extract<T>();
		[[maybe_unused]] T str_value_8 = _buffer.extract<T>();
	}

	template<class T>
	void function_front_STRING(CGDK::buffer _buffer)
	{
		// Declare)
		CGDK::POS temp_pos;

		[[maybe_unused]] T str_value_1 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_2 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_3 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_4 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_5 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_6 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_7 = _buffer.front<T>(temp_pos);
		[[maybe_unused]] T str_value_8 = _buffer.front<T>(temp_pos);
	}

	void function_append_GENERAL(CGDK::buffer& _buffer)
	{
		_buffer.append<char>(12);
		_buffer.append<unsigned char>(3);
		_buffer.append<wchar_t>(4);
		_buffer.append<char16_t>(10);
		_buffer.append<char32_t>(22);
		_buffer.append<int16_t>(4100);
		_buffer.append<uint16_t>(32210);
		_buffer.append<int32_t>(123310);
		_buffer.append<uint32_t>(121234);
		_buffer.append<int64_t>(-1000443);
		_buffer.append<uint64_t>(12233094310);
		_buffer.append<float>(1.0f);
		_buffer.append<double>(2.0);
	}

	void function_extract_GENERAL(CGDK::buffer _buffer)
	{
		[[maybe_unused]] auto value_01 = _buffer.extract<char>();
		[[maybe_unused]] auto value_02 = _buffer.extract<unsigned char>();
		[[maybe_unused]] auto value_03 = _buffer.extract<wchar_t>();
		[[maybe_unused]] auto value_04 = _buffer.extract<char16_t>();
		[[maybe_unused]] auto value_05 = _buffer.extract<char32_t>();
		[[maybe_unused]] auto value_06 = _buffer.extract<int16_t>();
		[[maybe_unused]] auto value_07 = _buffer.extract<uint16_t>();
		[[maybe_unused]] auto value_08 = _buffer.extract<int32_t>();
		[[maybe_unused]] auto value_09 = _buffer.extract<uint32_t>();
		[[maybe_unused]] auto value_10 = _buffer.extract<int64_t>();
		[[maybe_unused]] auto value_11 = _buffer.extract<uint64_t>();
		[[maybe_unused]] auto value_12 = _buffer.extract<float>();
		[[maybe_unused]] auto value_13 = _buffer.extract<double>();
	}

	void function_front_GENERAL(CGDK::buffer _buffer)
	{
		int	pos_now = 0;

		[[maybe_unused]] auto value_01 = _buffer.front<char>(pos_now);			pos_now += sizeof(char);
		[[maybe_unused]] auto value_02 = _buffer.front<unsigned char>(pos_now);	pos_now += sizeof(unsigned char);
		[[maybe_unused]] auto value_03 = _buffer.front<wchar_t>(pos_now);		pos_now += sizeof(wchar_t);
		[[maybe_unused]] auto value_04 = _buffer.front<char16_t>(pos_now);		pos_now += sizeof(char16_t);
		[[maybe_unused]] auto value_05 = _buffer.front<char32_t>(pos_now);		pos_now += sizeof(char32_t);
		[[maybe_unused]] auto value_06 = _buffer.front<int16_t>(pos_now);		pos_now += sizeof(int16_t);
		[[maybe_unused]] auto value_07 = _buffer.front<uint16_t>(pos_now);		pos_now += sizeof(uint16_t);
		[[maybe_unused]] auto value_08 = _buffer.front<int32_t>(pos_now);		pos_now += sizeof(int32_t);
		[[maybe_unused]] auto value_09 = _buffer.front<uint32_t>(pos_now);		pos_now += sizeof(uint32_t);
		[[maybe_unused]] auto value_10 = _buffer.front<int64_t>(pos_now);		pos_now += sizeof(int64_t);
		[[maybe_unused]] auto value_11 = _buffer.front<uint64_t>(pos_now);		pos_now += sizeof(uint64_t);
		[[maybe_unused]] auto value_12 = _buffer.front<float>(pos_now);			pos_now += sizeof(float);
		[[maybe_unused]] auto value_13 = _buffer.front<double>(pos_now);			pos_now += sizeof(double);
	}

	void function_front_with_pos_GENERAL(CGDK::buffer _buffer)
	{
		CGDK::POS pos_now;

		[[maybe_unused]] auto value_01 = _buffer.front<char>(pos_now);
		[[maybe_unused]] auto value_02 = _buffer.front<unsigned char>(pos_now);
		[[maybe_unused]] auto value_03 = _buffer.front<wchar_t>(pos_now);
		[[maybe_unused]] auto value_04 = _buffer.front<char16_t>(pos_now);
		[[maybe_unused]] auto value_05 = _buffer.front<char32_t>(pos_now);
		[[maybe_unused]] auto value_06 = _buffer.front<int16_t>(pos_now);
		[[maybe_unused]] auto value_07 = _buffer.front<uint16_t>(pos_now);
		[[maybe_unused]] auto value_08 = _buffer.front<int32_t>(pos_now);
		[[maybe_unused]] auto value_09 = _buffer.front<uint32_t>(pos_now);
		[[maybe_unused]] auto value_10 = _buffer.front<int64_t>(pos_now);
		[[maybe_unused]] auto value_11 = _buffer.front<uint64_t>(pos_now);
		[[maybe_unused]] auto value_12 = _buffer.front<float>(pos_now);
		[[maybe_unused]] auto value_13 = _buffer.front<double>(pos_now);
	}
	
	TEST(CGDK_buffer_benchmakr_basic, general_append_extract)
	{
		// X) Memory Alloc
		char buf_temp[2048];

		// 1) Buffer 할당
		CGDK::buffer buf_create(buf_temp);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 2) Buffer 대입
			CGDK::buffer buf_temp = buf_create;

			// 3) 값 써넣기
			buf_temp.append<char>(3);
			buf_temp.append<unsigned char>(4);
			buf_temp.append<int16_t>(4100);
			buf_temp.append<uint16_t>(32210);
			buf_temp.append<int32_t>(123310);
			buf_temp.append<uint32_t>(121234);
			buf_temp.append<int64_t>(-1000443);
			buf_temp.append<uint64_t>(12233094310);
			buf_temp.append<float>(1.0f);
			buf_temp.append<double>(2.0);

			// 4) 값 읽기
			auto value_01 = buf_temp.extract<char>();
			auto value_02 = buf_temp.extract<unsigned char>();
			auto value_06 = buf_temp.extract<int16_t>();
			auto value_07 = buf_temp.extract<uint16_t>();
			auto value_08 = buf_temp.extract<int32_t>();
			auto value_09 = buf_temp.extract<uint32_t>();
			auto value_10 = buf_temp.extract<int64_t>();
			auto value_11 = buf_temp.extract<uint64_t>();
			auto value_12 = buf_temp.extract<float>();
			auto value_13 = buf_temp.extract<double>();
		}
	}


	TEST(CGDK_buffer_benchmakr_basic, string_append_extract)
	{
		// X) Memory Alloc
		char buf_temp[2048];

		// 1) Buffer 할당
		CGDK::buffer buf_create(buf_temp);

		wchar_t* stringExtract[8];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 2) Buffer 대입
			CGDK::buffer buf_temp = buf_create;

			// 3) 값 써넣기
			buf_temp.append<wchar_t*>(array_string_wchar_t[0]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[1]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[2]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[3]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[4]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[5]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[6]);
			buf_temp.append<wchar_t*>(array_string_wchar_t[7]);

			// 4) 값 읽기
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
			stringExtract[0] = buf_temp.extract<wchar_t*>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, list_int_append_extract)
	{
		// X) Memory Alloc
		char buf_temp[2048];

		// 1) Buffer 할당
		CGDK::buffer buf_create(buf_temp);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 2) Buffer 대입
			CGDK::buffer buf_temp = buf_create;

			// 3) 값 써넣기
			buf_temp.append(array_int);

			// 4) 값 읽기
			auto temp = buf_temp.extract<std::vector<int>>();
		}
	}


	TEST(CGDK_buffer_benchmakr_basic, list_string_append_extract)
	{
		// X) Memory Alloc
		char buf_temp[2048];

		// 1) Buffer 할당
		CGDK::buffer buf_create(buf_temp);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 2) Buffer 대입
			CGDK::buffer buf_temp = buf_create;

			// 3) 값 써넣기
			buf_temp.append(array_std_string_stdwstring);

			// 4) 값 읽기
			auto temp = buf_temp.extract<std::vector<wchar_t*>>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, associated_string_list_int_append_extract)
	{
		// X) Memory Alloc
		char buf_temp[2048];

		// 1) Buffer 할당
		CGDK::buffer buf_create(buf_temp);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 2) Buffer 대입
			CGDK::buffer buf_temp = buf_create;

			// 3) 값 써넣기
			buf_temp.append(map_std_wstring_vector_int);

			// 4) 값 읽기
			auto temp = buf_temp.extract<std::map<wchar_t*, std::vector<int>>>();
		}
	}
}