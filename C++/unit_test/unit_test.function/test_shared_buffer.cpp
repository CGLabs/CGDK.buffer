#include "pch.h"

// definitions) 
#define	_TEST_COUNT	1

#if defined(_MSC_VER)
	#pragma warning(disable:4566)
#endif

template <class T>
void test_shared_buffer_extract_string(const T& _source)
{
	// declare) static memory
	auto temp = alloc_shared_buffer(2048);

	// 1) append string
	function_string_append(temp, _source);

	for (int i = 0; i < _TEST_COUNT; ++i)
	{
		// 2) copy buffer_view
		CGDK::buffer_view buf_read = temp;

		// 3) extract
		function_string_extract(buf_read, _source);

		// check) 
		EXPECT_TRUE(buf_read.size() == 0);
	}
}
template <class T>
void test_shared_buffer_front_string(const T& _source)
{
	// declare) static memory
	auto temp = alloc_shared_buffer(2048);

	// 1) append string
	function_string_append(temp, _source);

	for (int i = 0; i < _TEST_COUNT; ++i)
	{
		// 2) copy buffer_view
		CGDK::buffer_view buf_read = temp;

		// 3) extract
		function_string_front(buf_read, _source);

		// check) 
		EXPECT_TRUE(buf_read.size() == temp.size());
	}
}

namespace CGDK
{
	TEST(CGDK_shared_buffer, buffer_timepoint)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		{
			// - alloc shared buffer
			auto buf_temp = alloc_shared_buffer(2048);

			// - timepoint 설정
			auto dtA = chrono::from_date_time<chrono::time::local::time_point>({ 2017,12,11,5,10,20,1000 });;

			// - 값 써넣기
			buf_temp.append<chrono::time::local::time_point>(dtA);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(dtA));

			auto dtB = buf_temp.extract<chrono::time::local::time_point>();

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			// check) 
			EXPECT_TRUE(dtB.time_since_epoch() == dtA.time_since_epoch());
		}

		{
			// - alloc shared buffer
			auto buf_temp = alloc_shared_buffer(2048);

			// - timepoint 설정
			auto dtA = chrono::from_date_time<chrono::time::utc::time_point>({ 2017,12,11,5,10,20,1000 });;

			// - 
			auto epoch_a = dtA.time_since_epoch().count();

			// - 값 써넣기
			buf_temp.append<chrono::time::local::time_point>(dtA);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(dtA));

			auto dtB = buf_temp.extract<chrono::time::local::time_point>();

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			chrono::time::utc::time_point dtC = dtB;

			auto epoch_c = dtC.time_since_epoch().count();

			// check) 
			EXPECT_TRUE(epoch_a == epoch_c);
		}
	#endif
	}

	TEST(CGDK_shared_buffer, buffer_append_general)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - ...
		for(int i=0; i<_TEST_COUNT;++i)
		{
			CGDK::buffer buf_temp_inner(buf_temp);

			function_append_general(buf_temp_inner);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_general)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_extract_GENERAL(buf_temp);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_general)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_GENERAL(buf_temp);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_general_with_pos)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_with_pos_general(buf_temp);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// Defintions)
		std::string_view str_test{ "Test String" };

		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - buffer
		auto buf_test = (buf_temp ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(str_test);

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK_shared_buffer, buffer_prepend_const_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// - alloc shared buffer
		auto buf_alloc = alloc_shared_buffer(2048) ^ OFFSET;

		// Defintions)
		std::string_view str_test{ "Test String" };

		// - buffer 할당
		CGDK::buffer buf_test = buf_alloc + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(str_test);

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK_shared_buffer, buffer_prepend_string_format)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// defintions)
		std::string_view strTest1 = "Test String";
		std::string_view strTest3 = "Test End of String ";

		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - buffer 할당
		auto buf_test = (buf_temp ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(strTest3);
	#if defined(__cpp_lib_format)
		buf_test.prepend(std::format("Test {} {}", 10, 20));
	#endif
		buf_test.prepend(strTest1);

		// - 값 읽기
		[[maybe_unused]] auto str_read_1 = buf_test.extract<std::string_view>();
	#if defined(__cpp_lib_format)
		[[maybe_unused]] auto str_read_2 = buf_test.extract<std::string_view>();
	#endif
		[[maybe_unused]] auto str_read_3 = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(strTest1 == str_read_1);
		EXPECT_TRUE(strTest3 == str_read_3);
	}

	TEST(CGDK_shared_buffer, buffer_append_string)
	{
		// Defintions)
		std::string_view str_test{ "Test String" };

		// - alloc shared buffer
		auto buf_test = alloc_shared_buffer(2048);

		// - 값 써넣기
		buf_test.append(str_test);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(str_test));

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK_shared_buffer, buffer_append_string_view)
	{
		// Defintions)
		std::string	str_test{ "Test String" };

		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
		buf_temp.append(str_test);

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(str_test));

		// - 값 읽기
		auto str_read = buf_temp.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == 0);
		EXPECT_TRUE(std::char_traits<char>::compare(str_test.data(), str_read.data(), 0)==0);
	}

	TEST(CGDK_shared_buffer, buffer_append_string_format)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
	#if defined(__cpp_lib_format)
		buf_temp.append(std::format( "Test {} {}", 10, 20) );
	#endif
		buf_temp.append(std::string_view{ "Test" });

		// - 값 읽기
	#if defined(__cpp_lib_format)
		[[maybe_unused]] auto str_read_1 = buf_temp.extract<std::string_view>();
	#endif
		[[maybe_unused]] auto str_read_2 = buf_temp.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == 0);
		EXPECT_TRUE(str_read_2 == std::string_view("Test"));
	}

	TEST(CGDK_shared_buffer, buffer_append_const_string)
	{
		// - alloc shared buffer
		auto buf_temp = alloc_shared_buffer(2048);

		// - 값 써넣기
		buf_temp.append(std::string_view("Test XX"));

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(std::string_view("Test XX")));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_temp.extract<char*>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_String2)
	{
		// 1) 임시 문자열 list<std::string> 만듬(Create temporary string list)
		std::list<std::string> list_test;

		list_test.emplace_back("This");
		list_test.emplace_back("is a");
		list_test.emplace_back("Simple");
		list_test.emplace_back("Example!!");


		//-----------------------------------------------------------------
		// 설명) 배열에 저장된 String 읽어들이기 (2)
		//-----------------------------------------------------------------
		// Case A) 메모리 할당 (Allocating Memory)
		// - alloc shared buffer
		auto buf_write = alloc_shared_buffer(2048);

		// 2) 문자열 리스트 통채로 추가 (appending string list)
		buf_write.append(list_test);

		// check) 
		EXPECT_TRUE(buf_write.size() == get_size_of(list_test));

		// Case B) 메모리 할당 (Allocation Memory)
		auto temp_memory = alloc_shared_buffer(2048);

		// 3) Iterator를 사용해 특정 범위의 데이터만 써넣을 수도 있다.(ranged appending using iterator)
		temp_memory.append(list_test.begin(), list_test.end());

		// check) 
		EXPECT_TRUE(temp_memory.size() == get_size_of(list_test));


		//-----------------------------------------------------------------
		// 설명) 배열에 저장된 String 읽어들이기 (2)
		//-----------------------------------------------------------------
		{
			// 1) Buffer...
			auto buf_read = buf_write;

			// 1) 
			std::list<std::string> list_read;

			// 2) 읽어오기
			list_read = buf_read.extract<std::list<std::string>>();
	
			// check) 
			EXPECT_TRUE(list_test==list_read);
			EXPECT_TRUE(buf_read.size() == 0);
		}

		//-----------------------------------------------------------------
		// 설명) 배열에 저장된 String 읽어들이기 (2)
		//-----------------------------------------------------------------
		{
			// 1) Buffer...
			auto buf_read = buf_write;

			// declare) 데이터를 읽어올 vector<T>
			std::vector<std::string> vector_read;

			// 2) 읽어오기
			vector_read = buf_read.extract<std::vector<std::string>>();
	
			// check) 
			int	i=0;
			for(auto& iter:list_test)
			{
				EXPECT_TRUE(vector_read[i]==iter);
				++i;
			}

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);
		}

		//-----------------------------------------------------------------
		//
		//-----------------------------------------------------------------
		{
			// 1) Buffer를 Swallow복사 (버퍼 내용을 복사하는 것이 아니라 포인터만 복사한다.)
			auto buf_read = buf_write;

			// declare) 데이터를 읽어올 list<T>
			std::list<std::string_view> list_read;

			// 2) 읽어오기
			list_read = buf_read.extract<std::list<std::string_view>>();

			// check) 
			auto iter_compare=list_read.begin();
			for(auto& iter:list_test)
			{
				EXPECT_TRUE(iter == *iter_compare);
				++iter_compare;
			}

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);
		}

		//-----------------------------------------------------------------
		//
		//-----------------------------------------------------------------
		{
			// declare) 데이터를 읽어올 list<T>
			std::list<std::string_view> list_read;

			// 2) 읽어오기
			list_read  = buf_write.front<std::list<std::string_view>>();

			// check) 
			auto iter_compare=list_read.begin();
			for(auto& iter:list_test)
			{
				EXPECT_TRUE(iter == *iter_compare);
				++iter_compare;
			}
		}

		//-----------------------------------------------------------------
		//
		//-----------------------------------------------------------------
		{
			// 1) buffer_view을 사용해서 읽도록 했다.(CCD:buffer_view나 buffer_view를 사용해도 된다.)
			auto temp_read = buf_write;

			// 2) 갯수를 읽어온다.
			int	iCount = temp_read.extract<COUNT_T>();

			// check) 
			auto iter = list_test.begin();
			for(int i=0; i<iCount;++i, ++iter)
			{
				// - String들을 읽어낸다.
				auto strItem = temp_read.extract<char*>();

				// check) 
				EXPECT_TRUE((*iter).c_str() == strItem);
			}

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_append_text)
	{
		// Defintions)
		const char*	str_test = "Test String";

		// - alloc shared buffer
		auto buf_array = alloc_shared_buffer(2048);
		auto buf_test = buf_array;

		// - 값 써 넣기
		auto result_a = buf_test.append(_text(str_test));

		// check) 
		EXPECT_TRUE(std::char_traits<char>::length(str_test) == result_a.size());
		EXPECT_TRUE(buf_test.size() == get_size_of(_text(str_test)));

		auto result_b = buf_test.append(_text("Test Temp"));

		// check) 
		EXPECT_TRUE(std::char_traits<char>::length("Test Temp") == result_b.size());

		// check) 
		EXPECT_TRUE(buf_test.size() == result_a.size() + result_b.size());

		// Chec) String 내용 검사			
		EXPECT_TRUE(memcmp("Test String", buf_array.data<char>(), std::char_traits<char>::length(str_test) * sizeof(char)) == 0);
		EXPECT_TRUE(memcmp("Test Temp", buf_array.data<char>() + std::char_traits<char>::length(str_test) * sizeof(char), std::char_traits<char>::length("Test Temp")*sizeof(char)) == 0);
	}

	TEST(CGDK_shared_buffer, buffer_append_Initializer_list)
	{
		// declare) static memory
		// - alloc shared buffer
		auto buf_test = alloc_shared_buffer(2048);

		// 2) 추가한다
		buf_test.append({ 1,2,3,4,5,6,7 });
	}

	TEST(CGDK_shared_buffer, buffer_iostream)
	{
		// 1) alloc buffer 
		auto buf_temp = alloc_shared_buffer(2048);

		// declare) 
		const	int					iValue_Write		 = 3;
		const	float				fValue_Write		 = 4.0f;
		const	std::string_view	strValue1_Write		 = "Test1";
		const	std::wstring_view	strValue2_Write		 = L"Test2";
		const	std::string			strValue3_Write		 = "Test3";
		std::vector<int>			vectorValue_Write	 = {1, 2, 4, 3, 6, 7, 5};

		// 2) 버퍼에 값 써넣기 (Streadm-In)
		{
			buf_temp <<iValue_Write <<fValue_Write <<strValue1_Write <<strValue2_Write <<strValue3_Write <<vectorValue_Write;
		}

		// 3) 버퍼에서 값 읽어오기 (Streadm-Out)
		{
			// - 읽기 용 임시 버퍼
			auto bufferTempRead = buf_temp;
				
			// declare) 
			int					iValue_Read;
			float				fValue_Read;
			//char*				strValue1_Read;	// 여기
			std::string_view	strValue1_Read;
			std::wstring_view	strValue2_Read;
			std::string			strValue3_Read;
			std::vector<int>	vectorValue_Read;

			// - 읽어낸다.
			bufferTempRead >>iValue_Read >>fValue_Read >>strValue1_Read >>strValue2_Read >>strValue3_Read >>vectorValue_Read;

			// check) 
			EXPECT_TRUE(iValue_Read==iValue_Write);
			EXPECT_TRUE(fValue_Read==fValue_Write);
			EXPECT_TRUE(strValue1_Read == strValue1_Write);
			EXPECT_TRUE(strValue2_Write == strValue2_Write);
			EXPECT_TRUE(strValue3_Write == strValue3_Read);
			EXPECT_TRUE(vectorValue_Write == vectorValue_Read);
		}
	}

	TEST(CGDK_shared_buffer, buffer_append_front_STRUCT_1)
	{
		struct TESTSTRUCT
		{
   			int			iValue;
   			uint32_t	dwValue;
   			char		chValue;
		};

		// 1) alloc buffer 
		auto buf_temp = alloc_shared_buffer(2048);

		// 2) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
		TESTSTRUCT&	temp = buf_temp.append<TESTSTRUCT>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		// 3) 이렇게 먼저 추가해 놓고 쓰게 되면 실질적으로는 Buffer내에 해당 위치에 쓰여진다.
   		temp.iValue	 = 10;
   		temp.dwValue = 100;
   		temp.chValue = 2;

		// 4) 값을 읽어온다.
		TESTSTRUCT&	temp_read = buf_temp.front<TESTSTRUCT&>(0);

		// check) 
		EXPECT_TRUE(temp.iValue==temp_read.iValue);
		EXPECT_TRUE(temp.dwValue==temp_read.dwValue);
		EXPECT_TRUE(temp.chValue==temp_read.chValue);
	}

	TEST(CGDK_shared_buffer, buffer_append_front_to_STRUCT_1)
	{
		struct TESTSTRUCT
		{
			int			iValue;
			uint32_t	dwValue;
			char		chValue;
		};

		// 1) alloc buffer 
		auto buf_temp = alloc_shared_buffer(2048);

		// 2) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
		TESTSTRUCT& temp = buf_temp.append<TESTSTRUCT>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		// 3) 이렇게 먼저 추가해 놓고 쓰게 되면 실질적으로는 Buffer내에 해당 위치에 쓰여진다.
		temp.iValue = 10;
		temp.dwValue = 100;
		temp.chValue = 2;

		// declare) 
		TESTSTRUCT temp_read;
		
		// 4) 값을 읽어온다.
		buf_temp.front_to(temp_read, 0);

		// check) 
		EXPECT_TRUE(temp.iValue == temp_read.iValue);
		EXPECT_TRUE(temp.dwValue == temp_read.dwValue);
		EXPECT_TRUE(temp.chValue == temp_read.chValue);
	}

	TEST(CGDK_shared_buffer, buffer_append_front_STRUCT_2)
	{
		#define	VALUE1	1
		#define	VALUE2	12
		#define	VALUE3	4322
		#define	VALUE4	12.3f
		#define	VALUE5	1244.123

		struct TESTSTRUCT
		{
		public:
   			char		chValue;
   			int			iValue;
   			uint32_t	dwValue;
   			float		fchValue;
   			double		dchValue;
		public:
			TESTSTRUCT():chValue(VALUE1),iValue(VALUE2),dwValue(VALUE3),fchValue(VALUE4),dchValue(VALUE5) {}
		};


		// 1) alloc buffer 
		auto buf_temp = alloc_shared_buffer(2048);

		// 2) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
		TESTSTRUCT&	temp = buf_temp.append<TESTSTRUCT&>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		// 3) 값을 읽어온다.
		TESTSTRUCT&	temp_read = buf_temp.front<TESTSTRUCT&>(0);

		// check) 
		EXPECT_EQ(temp.chValue,  temp_read.chValue);
		EXPECT_EQ(temp.iValue,   temp_read.iValue);
		EXPECT_EQ(temp.dwValue,  temp_read.dwValue);
		EXPECT_EQ(temp.fchValue, temp_read.fchValue);
		EXPECT_EQ(temp.dchValue, temp_read.dchValue);
	}

	TEST(CGDK_shared_buffer, buffer_append_front_to_STRUCT_2)
	{
		#define	VALUE1	1
		#define	VALUE2	12
		#define	VALUE3	4322
		#define	VALUE4	12.3f
		#define	VALUE5	1244.123

		struct TESTSTRUCT
		{
		public:
   			char		chValue;
   			int			iValue;
   			uint32_t	dwValue;
   			float		fchValue;
   			double		dchValue;
		public:
			TESTSTRUCT():chValue(VALUE1),iValue(VALUE2),dwValue(VALUE3),fchValue(VALUE4),dchValue(VALUE5) {}
		};

		// 1) alloc buffer 
		auto buf_temp = alloc_shared_buffer(2048);

		// 2) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
		TESTSTRUCT&	temp = buf_temp.append<TESTSTRUCT&>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		// 3) 값을 읽어온다.
		TESTSTRUCT temp_read;
		
		buf_temp.front_to<TESTSTRUCT>(temp_read);

		// check) 
		EXPECT_EQ(temp.chValue,  temp_read.chValue);
		EXPECT_EQ(temp.iValue,   temp_read.iValue);
		EXPECT_EQ(temp.dwValue,  temp_read.dwValue);
		EXPECT_EQ(temp.fchValue, temp_read.fchValue);
		EXPECT_EQ(temp.dchValue, temp_read.dchValue);
	}

	//-----------------------------------------------------------------
	// Test) string append / front 
	//-----------------------------------------------------------------
	// 1) string(pointer type) append/extract
	TEST(CGDK_shared_buffer, buffer_string_extract_char)				{ test_shared_buffer_extract_string(array_string_char); }
	TEST(CGDK_shared_buffer, buffer_string_extract_wchar_t)				{ test_shared_buffer_extract_string(array_string_wchar_t); }
	TEST(CGDK_shared_buffer, buffer_string_extract_char16_t)			{ test_shared_buffer_extract_string(array_string_char16_t); }
	TEST(CGDK_shared_buffer, buffer_string_extract_char32_t)			{ test_shared_buffer_extract_string(array_std_u32string_view); }
	// 2) string(std::basic_string_view<T> type) append/extract
	TEST(CGDK_shared_buffer, buffer_string_extract_std_string_view)		{ test_shared_buffer_extract_string(array_std_string_view); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_wstring_view)	{ test_shared_buffer_extract_string(array_std_wstring_view); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_u16string_view)	{ test_shared_buffer_extract_string(array_std_u16string_view); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_u32string_view)	{ test_shared_buffer_extract_string(array_std_u32string_view); }
	// 3) string(std::basic_string<T> type) append/extract
	TEST(CGDK_shared_buffer, buffer_string_extract_std_string)			{ test_shared_buffer_extract_string(array_std_string); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_wstring)			{ test_shared_buffer_extract_string(array_std_wstring); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_u16string)		{ test_shared_buffer_extract_string(array_std_u16string); }
	TEST(CGDK_shared_buffer, buffer_string_extract_std_u32string)		{ test_shared_buffer_extract_string(array_std_u32string); }

	// 4) string(pointer type) append/front
	TEST(CGDK_shared_buffer, buffer_front_string_char)					{ test_shared_buffer_front_string(array_string_char); }
	TEST(CGDK_shared_buffer, buffer_front_string_wchar_t)				{ test_shared_buffer_front_string(array_string_wchar_t); }
	TEST(CGDK_shared_buffer, buffer_front_string_char16_t)				{ test_shared_buffer_front_string(array_string_char16_t); }
	TEST(CGDK_shared_buffer, buffer_front_string_char32_t)				{ test_shared_buffer_front_string(array_std_u32string_view); }
	// 5) string(std::basic_string_view<T> type) append/front
	TEST(CGDK_shared_buffer, buffer_front_string_std_string_view)		{ test_shared_buffer_front_string(array_std_string_view); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_wstring_view)		{ test_shared_buffer_front_string(array_std_wstring_view); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_u16string_view)	{ test_shared_buffer_front_string(array_std_u16string_view); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_u32string_view)	{ test_shared_buffer_front_string(array_std_u32string_view); }
	// 6) string(std::basic_string<T> type) append/front
	TEST(CGDK_shared_buffer, buffer_front_string_std_string)			{ test_shared_buffer_front_string(array_std_string); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_wstring)			{ test_shared_buffer_front_string(array_std_wstring); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_u16string)			{ test_shared_buffer_front_string(array_std_u16string); }
	TEST(CGDK_shared_buffer, buffer_front_string_std_u32string)			{ test_shared_buffer_front_string(array_std_u32string); }

	// 7) bound check test
	TEST(CGDK_shared_buffer, buffer_string_append_bound_check)
	{
		// Defintions)
		std::string_view str_test = "Test String";

		char buf_array[get_size_of("Test String")];

		// - alloc shared_buffer
		CGDK::buffer buf_alloc{ buf_array };

		// - overflow test - pass
		{
			// - 
			auto buf_test = buf_alloc;

			// declare)
			bool result = true;

			try
			{
				buf_test.append(str_test);

			}
			catch (...)
			{
				result = false;
			}

			// check) 
			EXPECT_TRUE(result);
		}
		// - overflow test - fail
		{
			// - 
			auto buf_test = buf_alloc;

			// - overflow를 위해 1byte 써넣기
			buf_test.append<char>(1);

			// declare)
			bool result = false;

			try
			{
				buf_test.append(str_test);

			}
			catch (...)
			{
				result = true;
			}

			// check) 
			EXPECT_TRUE(result);
		}

		// - fit
		{
			// - 
			CGDK::buffer buf_test = buf_alloc;

			// declare)
			bool result = true;

			try
			{
				buf_test.append(str_test);

			}
			catch (...)
			{
				result = false;
			}

			// check) 
			EXPECT_TRUE(result);
		}
	}

	TEST(CGDK_shared_buffer, buffer_string_prepend_bound_check)
	{
	#define CGDK_DISABLE_ASSERT // for test

		// Defintions)
		std::string_view str_test = "Test String";

		// 1) alloc buffer 
		shared_buffer buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - overflow test
		{
			// - 
			buffer buf_test = buf_alloc + offset(get_size_of(str_test) - 1);

			// declare)
			bool result = false;

			try
			{
				// - prepend
				buf_test.prepend(str_test);
			}
			catch (...)
			{
				result = true;
			}

			// check) 
			EXPECT_TRUE(result);
		}

		// - fit
		{
			// - 
			auto buf_test = buf_alloc + offset(get_size_of(str_test));

			// declare)
			bool result = true;

			try
			{
				// - prepend
				buf_test.prepend(str_test);
			}
			catch (...)
			{
				result = false;
			}

			// check) 
			EXPECT_TRUE(result);
		}
	#undef CGDK_DISABLE_ASSERT // for test
	}


	//-----------------------------------------------------------------
	// Test) array
	//-----------------------------------------------------------------
	// 1) array
	//const char*								array_string_char[];
	//const wchar_t*							array_string_wchar_t[];
	//std::string								array_std_string[];
	//std::wstring								array_std_wstring[];
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer buf_write = buf_alloc;

			buf_write.append(array_string_wchar_t);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(array_string_wchar_t));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_array_wchar_t)
	{
		// - alloc buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		buf_alloc.append(array_string_wchar_t);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(array_string_wchar_t));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(array_string_wchar_t)>();

			// check) 
			for(int j=0; j<8; ++j)
			{
				EXPECT_TRUE(temp[j] == array_string_wchar_t[j]);
			}
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_array_wchar_t)
	{
		// - alloc buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		buf_alloc.append(array_string_wchar_t);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(array_string_wchar_t));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			std::array<std::wstring_view, 8> temp;

			// - extract to
			buf_temp.extract_to(temp);

			// check) 
			for (int j = 0; j < 8; ++j)
			{
				EXPECT_TRUE(temp[j] == array_string_wchar_t[j]);
			}
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_array_wchar_t)
	{
		// - alloc buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append
		buf_alloc.append(array_string_wchar_t);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(array_string_wchar_t));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.front<decltype(array_string_wchar_t)>(0);

			// check) 
			for(int j=0; j<8; ++j)
			{
				EXPECT_TRUE(temp[j] == array_string_wchar_t[j]);
			}
			EXPECT_TRUE(buf_temp.data() == buf_alloc.data());
			EXPECT_TRUE(buf_temp.size() == buf_alloc.size());
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append
		buf_alloc.append(array_string_wchar_t);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(array_string_wchar_t));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			std::array<std::wstring_view, 8> temp;
			
			buf_temp.front_to(temp, 0);

			// check) 
			for (int j = 0; j < 8; ++j)
			{
				EXPECT_TRUE(temp[j] == array_string_wchar_t[j]);
			}
			EXPECT_TRUE(buf_temp.data() == buf_alloc.data());
			EXPECT_TRUE(buf_temp.size() == buf_alloc.size());
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(array_string_wchar_t);

			// - pop front!
			auto temp = buf_temp.extract<decltype(array_string_wchar_t)>();

			// check) 
			EXPECT_TRUE(compare_array_string<wchar_t>(temp, array_string_wchar_t)); // L"Fail to array[wchar_t] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(array_string_wchar_t);

			// declare) 
			std::array<std::wstring_view, 8> temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(compare_array_string<wchar_t>(temp, array_string_wchar_t)); // L"Fail to array[wchar_t] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) Container-vector
	//-----------------------------------------------------------------
	// 2) vector
	//std::vector<int>			std_vector_int;
	//std::vector<std::string>	std_vector_std_string;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_vector_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;

			decltype(std_vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0; i<_TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_int);

			// declare) 
			decltype(std_vector_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_int); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_vector_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_vector_std_string));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_vector_std_string)>();

			// check) 
			EXPECT_TRUE(temp==std_vector_std_string); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;

			// declare) 
			decltype(std_vector_std_string) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_vector_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_vector_std_string) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_std_string);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_vector_std_string)>();

			// check) 
			EXPECT_TRUE(temp==std_vector_std_string); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_vector_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_std_string);

			// declare) 
			decltype(std_vector_std_string) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) std::array
	//-----------------------------------------------------------------
	TEST(CGDK_shared_buffer, buffer_std_array_append_extract)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<int, 10>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_to)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// declare) 
		[[maybe_unused]] std::array<int, 10> str_read;
		
		// - 값 읽기
		buf_test.extract_to(str_read);

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_char)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_char);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(array_string_char));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<decltype(array_string_char)>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_to_char)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc{ buf_array };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_char);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(array_string_char));

		// declare) 
		[[maybe_unused]] std::array<std::string_view, 8> str_read;

		// - 값 읽기
		buf_test.extract_to(str_read);

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_wchar_t)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_wchar_t);

		// check) 
		auto size_temp = get_size_of(array_string_wchar_t);
		EXPECT_TRUE(buf_test.size() == size_temp);

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<decltype(array_string_wchar_t)>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_to_wchar_t)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_wchar_t);

		// check) 
		auto size_temp = get_size_of(array_string_wchar_t);
		EXPECT_TRUE(buf_test.size() == size_temp);

		// declare) 
		[[maybe_unused]] std::array<std::wstring_view, 8> str_read;

		// - 값 읽기
		buf_test.extract_to(str_read);

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_std_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<std::string, 4> temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_to_std_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<std::string, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// declare) 
		[[maybe_unused]] std::array<std::string, 4> str_read;
		
		// - 값 읽기
		buf_test.extract_to(str_read);

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_std_string_view)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string_view, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_std_array_append_extract_to_std_string_view)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		auto buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// declare) 
		[[maybe_unused]] std::array<std::string_view, 4> str_read;
		
		// - 값 읽기
		buf_test.extract_to(str_read);

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	//-----------------------------------------------------------------
	// Test) Container-list
	//-----------------------------------------------------------------
	// 1) std::list<int>					std_list_int;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;

			// declare) 
			decltype(std_list_int) temp;
						
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_list_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_list_int) temp;
			
			// - front~
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_list_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_int);

			// declare) 
			decltype(std_list_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 2) std::list<std::string>			std_list_std_string;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_std_string);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_std_string)>();

			// check) 
			EXPECT_TRUE(temp == std_list_std_string);
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;

			// declare) 
			decltype(std_list_std_string) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string);
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_list_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list<string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			decltype(std_list_std_string) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list<string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_std_string);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_list_std_string)>();

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list[string] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_list_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_std_string);

			// declare) 
			decltype(std_list_std_string) temp;
			
			// - extract
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list[string] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 3) std::list<std::vector<int>>		std_list_std_vector_int;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_std_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_std_vector_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append string
		buf_alloc.append(std_list_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;

			decltype(std_list_std_vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_list_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_list_std_vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_list_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_list_std_vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_std_vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_list_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_std_vector_int);

			// declare) 
			decltype(std_list_std_vector_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_vector_int); // L"Fail to list<vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) Container-set
	//-----------------------------------------------------------------
	// 1) std::set<int>			std_set_int;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		for(int i=0; i<_TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_set_int)>();

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			decltype(std_set_int) temp;
			
			// - ...
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_set_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_set_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_set_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_set_int)>();

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_set_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_set_int);

			// declare) 
			decltype(std_set_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_std_string));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_set_std_string)>();

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_set_std_string) temp;
						
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_set_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			// declare) 
			decltype(std_set_std_string) temp;
						
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_set_std_string);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_set_std_string)>();

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_set_string)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_set_std_string);

			// declare) 
			decltype(std_set_std_string) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	//-----------------------------------------------------------------
	// Test) Container-map
	//-----------------------------------------------------------------
	// 1) std::map<int, int>							;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_int_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_int_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_map_int_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_int_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_map_int_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			decltype(std_map_int_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_int_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_map_int_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 2) std::map<std::string, int>
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_string_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_map_std_string_int)>();

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/extract"
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_std_string_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/extract"
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_map_std_string_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			decltype(std_map_std_string_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}
	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_map_string_int_push)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_std_string_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_map_std_string_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 3) std::map<std::string, std::vector<int>>		std_map_std_wstring_std_vector_int;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - ....
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_wstring_std_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_wstring_std_vector_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_wstring_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_wstring_std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_map_std_wstring_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_std_wstring_std_vector_int); // L"Fail to map<string,vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_wstring_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_wstring_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_std_wstring_std_vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_wstring_std_vector_int); // L"Fail to map<string,vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_wstring_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_wstring_std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			auto temp = buf_temp.front<decltype(std_map_std_wstring_std_vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_wstring_std_vector_int); // L"Fail to map<string,vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_wstring_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_wstring_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			offset pos_temp;

			decltype(std_map_std_wstring_std_vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_wstring_std_vector_int); // L"Fail to map<string,vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.amount);
		}
	}


	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_std_wstring_std_vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_map_std_wstring_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_std_wstring_std_vector_int); // L"Fail to map<string,vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 4) std::map<std::string, std::vector<std::string_view>>	std_map_std_vector_std_string_view;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_vector_std_string_view);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_vector_std_string_view));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_vector_std_string_view);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_vector_std_string_view));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_map_std_vector_std_string_view)>();

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp, std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_vector_std_string_view);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_vector_std_string_view));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_std_vector_std_string_view) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp, std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_vector_std_string_view);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_vector_std_string_view));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.front<decltype(std_map_std_vector_std_string_view)>(0);

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp, std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> append/front"
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_map_std_vector_std_string_view);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_vector_std_string_view));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_std_vector_std_string_view) temp;
			
			buf_temp.front_to(temp, 0);

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp, std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> append/front"
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_std_vector_std_string_view);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_map_std_vector_std_string_view)>();

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp,std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_std_vector_std_string_view);

			// declare) 
			decltype(std_map_std_vector_std_string_view) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(compare_map_std_vector_string(temp, std_map_std_vector_std_string_view)); // L"Fail to map<string,vector<char*>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) Container-unordered_map
	//-----------------------------------------------------------------
	// 1) unordered_map
	// 2) std::unordered_map<int, int>						std_unordered_map_int_int;
	// 3) std::unordered_map<std::string, int>				std_unordered_map_std_string_int;
	// 4) std::unordered_map<std::string, std::vector<int>>	std_unordered_map_std_string_std_vector_int;
	// 5) std::unordered_map<std::string, std::vector<char*>>	std_unordered_map_std_vector_std_string_view;
	TEST(CGDK_shared_buffer, buffer_append_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_unordered_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_unordered_map_std_string_int));
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_unordered_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_unordered_map_std_string_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_unordered_map_std_string_int)>();

			// check) 
			EXPECT_TRUE(temp == std_unordered_map_std_string_int); // L"Fail to unordered_map<std::string,int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_extract_to_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_unordered_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_unordered_map_std_string_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_unordered_map_std_string_int) temp;

			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_unordered_map_std_string_int); // L"Fail to unordered_map<std::string,int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_shared_buffer, buffer_front_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append data
		buf_alloc.append(std_unordered_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_unordered_map_std_string_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;


			decltype(std_unordered_map_std_string_int) temp;

			buf_temp.front_to<decltype(std_unordered_map_std_string_int)>(temp, 0);

			// check) 
			EXPECT_TRUE(temp == std_unordered_map_std_string_int); // L"Fail to unordered_map<std::string,int> append/front"
		}
	}

	TEST(CGDK_shared_buffer, buffer_prepend_extract_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc ^ 2048;

			buf_temp += offset(2048);

			// - 
			buf_temp.prepend(std_unordered_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(std_unordered_map_std_string_int)); // L"Fail to unordered_map<std::string,int> prepend/extract"

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_unordered_map_std_string_int)>();

			// check) 
			EXPECT_TRUE(get_size_of(temp) == get_size_of(std_unordered_map_std_string_int)); // L"Fail to unordered_map<std::string,int> prepend/extract"
			EXPECT_TRUE(temp == std_unordered_map_std_string_int); // L"Fail to unordered_map<std::string,int> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) int append / front 
	//-----------------------------------------------------------------
	TEST(CGDK_shared_buffer, buffer_VariableLength)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 2) 테스트를 위해 0~9 중 임의의 데이터 갯수를 구한다.
		int iCount = rand()%10;

		// 3) 먼저 갯수를 써넣는다.
		buf_alloc.append<int>(iCount);

		// 4) 갯수만큼 데이터를 써넣는다.
		for(int i=0; i<iCount; ++i)
		{
			buf_alloc.append<int>(i);
		}

		// 5) ...
		{
			// - 값을 읽어온다.
			buffer_view buf_read = buf_alloc;

			// - 먼저 데이터의 값을 읽어온다.
			int	iCountX	 = buf_read.extract<int>();

			// - 갯수만큼 데이터를읽어들인다.
			for(int i=0; i<iCountX; ++i)
			{
				int	value = buf_read.extract<int>();

				// check) 
				EXPECT_EQ(i, value); // L"Fail to [int] append/extract "
			}
		}
	}

	//-----------------------------------------------------------------
	// Test) int append / front 
	//-----------------------------------------------------------------
	TEST(CGDK_shared_buffer, buffer_buffer)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		char buf_array_A[2048];
		CGDK::buffer bufA{ buf_array_A };
		bufA.set_size(100);

		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		buf_alloc.append(bufA);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int) + get_size_of(bufA));

		// - extract
		[[maybe_unused]] auto a = buf_alloc.extract<decltype(std_vector_int)>();
		[[maybe_unused]] auto b = buf_alloc.extract<buffer_view>();

		// check) 
		EXPECT_TRUE(buf_alloc.size() == 0);
	}
	TEST(CGDK_shared_buffer, buffer_buffer_to)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		char buf_array_A[2048];
		CGDK::buffer bufA{ buf_array_A };
		bufA.set_size(100);

		buf_alloc.append(std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int));

		buf_alloc.append(bufA);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_int) + get_size_of(bufA));

		// - extract
		[[maybe_unused]] decltype(std_vector_int) a;
		buf_alloc.extract_to(a);
		[[maybe_unused]] buffer_view b;
		buf_alloc.extract_to(b);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == 0);
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple01)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// 2) 값 읽기
			auto dest_a = buf_read.extract<int>();
			auto dest_b = buf_read.extract<std::string_view>();
			auto dest_c = buf_read.extract<float>();

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);

			// check) 
			EXPECT_TRUE(dest_a == source_a);
			EXPECT_TRUE(get_size_of(dest_a) == get_size_of(source_a));
			EXPECT_TRUE(dest_b == source_b);
			EXPECT_TRUE(get_size_of(dest_b) == get_size_of(source_b));
			EXPECT_TRUE(dest_c == source_c);
			EXPECT_TRUE(get_size_of(dest_c) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple02)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// 2) 값 읽기
			int dest_a;
			std::string_view dest_b;
			float dest_c;

			// 2) 값 읽기
			buf_read.extract_to(dest_a);
			buf_read.extract_to(dest_b);
			buf_read.extract_to(dest_c);

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);

			// check) 
			EXPECT_TRUE(dest_a == source_a);
			EXPECT_TRUE(get_size_of(dest_a) == get_size_of(source_a));
			EXPECT_TRUE(dest_b == source_b);
			EXPECT_TRUE(get_size_of(dest_b) == get_size_of(source_b));
			EXPECT_TRUE(dest_c == source_c);
			EXPECT_TRUE(get_size_of(dest_c) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple03)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// 2) 값 읽기
			auto dest = buf_read.extract<std::tuple<int, std::string_view, float>>();

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);

			// check) 
			EXPECT_TRUE(std::get<0>(dest) == source_a);
			EXPECT_TRUE(get_size_of(std::get<0>(dest)) == get_size_of(source_a));
			EXPECT_TRUE(std::get<1>(dest) == source_b);
			EXPECT_TRUE(get_size_of(std::get<1>(dest)) == get_size_of(source_b));
			EXPECT_TRUE(std::get<2>(dest) == source_c);
			EXPECT_TRUE(get_size_of(std::get<2>(dest)) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple04)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// declare) 
			std::tuple<int, std::string_view, float> dest;
			
			// 2) 값 읽기
			buf_read.extract_to(dest);

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);

			// check) 
			EXPECT_TRUE(std::get<0>(dest) == source_a);
			EXPECT_TRUE(get_size_of(std::get<0>(dest)) == get_size_of(source_a));
			EXPECT_TRUE(std::get<1>(dest) == source_b);
			EXPECT_TRUE(get_size_of(std::get<1>(dest)) == get_size_of(source_b));
			EXPECT_TRUE(std::get<2>(dest) == source_c);
			EXPECT_TRUE(get_size_of(std::get<2>(dest)) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple05)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// 2) 값 읽기
			auto dest = buf_read.front<std::tuple<int, std::string_view, float>>();

			// check) 
			EXPECT_TRUE(buf_read.size() == buf_source.size());

			// check) 
			EXPECT_TRUE(std::get<0>(dest) == source_a);
			EXPECT_TRUE(get_size_of(std::get<0>(dest)) == get_size_of(source_a));
			EXPECT_TRUE(std::get<1>(dest) == source_b);
			EXPECT_TRUE(get_size_of(std::get<1>(dest)) == get_size_of(source_b));
			EXPECT_TRUE(std::get<2>(dest) == source_c);
			EXPECT_TRUE(get_size_of(std::get<2>(dest)) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple06)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// declare) 
			std::tuple<int, std::string_view, float> dest;
			
			// 2) 값 읽기
			buf_read.front_to(dest);

			// check) 
			EXPECT_TRUE(buf_read.size() == buf_source.size());

			// check) 
			EXPECT_TRUE(std::get<0>(dest) == source_a);
			EXPECT_TRUE(get_size_of(std::get<0>(dest)) == get_size_of(source_a));
			EXPECT_TRUE(std::get<1>(dest) == source_b);
			EXPECT_TRUE(get_size_of(std::get<1>(dest)) == get_size_of(source_b));
			EXPECT_TRUE(std::get<2>(dest) == source_c);
			EXPECT_TRUE(get_size_of(std::get<2>(dest)) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple07)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// declare) 
			std::tuple<int, std::string_view, float> dest;

			// 2) 값 읽기
			buf_read.front_to(dest);

			// check) 
			EXPECT_TRUE(buf_read.size() == buf_source.size());

			// check) 
			EXPECT_TRUE(std::get<0>(dest) == source_a);
			EXPECT_TRUE(get_size_of(std::get<0>(dest)) == get_size_of(source_a));
			EXPECT_TRUE(std::get<1>(dest) == source_b);
			EXPECT_TRUE(get_size_of(std::get<1>(dest)) == get_size_of(source_b));
			EXPECT_TRUE(std::get<2>(dest) == source_c);
			EXPECT_TRUE(get_size_of(std::get<2>(dest)) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, buffer_map_tuple08)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer 
		auto buf_source = alloc_shared_buffer(2048);

		{
			// 3) vector를 append하면 각 개체가 통채로 들어간다.
			buf_source.append(std::tuple<int, const std::string_view, float>(source_a, source_b, source_c));

			// check) 
			EXPECT_TRUE(buf_source.size() == get_size_of(std::tuple<int, std::string_view, float>(source_a, source_b, source_c)));
		}

		{
			// 1) 값을 읽어온다.
			const_buffer_view buf_read(buf_source);

			// 2) 값 읽기
			int					dest_a;
			std::string_view	dest_b;
			float				dest_c;

			// 3) std::tie<...>를 사용해서 값을 대입하기
			std::tie<int, std::string_view, float>(dest_a, dest_b, dest_c) = buf_read.extract<std::tuple<int, std::string_view, float>>();

			// check) 
			EXPECT_TRUE(buf_read.size() == 0);

			// check) 
			EXPECT_TRUE(dest_a == source_a);
			EXPECT_TRUE(get_size_of(dest_a) == get_size_of(source_a));
			EXPECT_TRUE(dest_b == source_b);
			EXPECT_TRUE(get_size_of(dest_b) == get_size_of(source_b));
			EXPECT_TRUE(dest_c == source_c);
			EXPECT_TRUE(get_size_of(dest_c) == get_size_of(source_c));
		}
	}

	TEST(CGDK_shared_buffer, test_buffer_map_tuple09)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp{ 0, {0, 0, 1.0f, "Test"}, "Value" };

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 2) Buffer를 할당한다. (최소 64Byte를 할당받는다.)
		auto buf_temp = buf_alloc;

		// 3) 
		buf_temp.append(temp);

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		{
			// 1) 값을 읽어온다.
			buffer_view temp_read = buf_temp;

			// 2) 일어 값을 저장할 Tupple
			TUPPLE_B tupple_read = temp_read.extract<TUPPLE_B>();

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(std::get<0>(temp)==std::get<0>(tupple_read)); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<0>(std::get<1>(temp)) == std::get<0>(std::get<1>(tupple_read))); // , L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<1>(std::get<1>(temp)) == std::get<1>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<2>(std::get<1>(temp)) == std::get<2>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<3>(std::get<1>(temp)) == std::get<3>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<2>(temp) == std::get<2>(tupple_read)); // L"Fail! Tupple 2"
		}
	}

	TEST(CGDK_shared_buffer, test_buffer_map_tuple10)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp{ 0, TUPPLE_A{0, 0, 1.0f, "Test"}, "Value" };

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 2) Buffer를 할당한다. (최소 64Byte를 할당받는다.)
		auto buf_temp = buf_alloc;

		// 3) 
		buf_temp.append(temp);

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		{
			// 1) 값을 읽어온다.
			buffer_view temp_read = buf_temp;

			// declare)
			TUPPLE_B tupple_read;
			
			// 2) 일어 값을 저장할 Tupple
			temp_read.extract_to(tupple_read);

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(std::get<0>(temp) == std::get<0>(tupple_read)); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<0>(std::get<1>(temp)) == std::get<0>(std::get<1>(tupple_read))); // , L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<1>(std::get<1>(temp)) == std::get<1>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<2>(std::get<1>(temp)) == std::get<2>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<3>(std::get<1>(temp)) == std::get<3>(std::get<1>(tupple_read))); // L"Fail! Tupple 2"
			EXPECT_TRUE(std::get<2>(temp) == std::get<2>(tupple_read)); // L"Fail! Tupple 2"
		}
	}

	TEST(CGDK_shared_buffer, test_buffer_map_tuple11)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;

		// 1) 써넣은 예제 Tupple
		auto temp = TUPPLE_A{ 0, 0, 1.0f, "Test" };

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) Buffer를 할당한다. (최소 64Byte를 할당받는다.)
		auto buf_temp = buf_alloc;

		// 2) 
		buf_temp.append(std::tuple{0, 0, 1.0f, "Test"});

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(temp));

		{
			// 1) 값을 읽어온다.
			buffer_view temp_read = buf_temp;

			// 2) 일어 값을 저장할 Tupple
			auto [v1, v2, v3, v4] = temp_read.extract < std::tuple<int, int, float, std::string_view> > ();

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(std::get<0>(temp) == v1);
			EXPECT_TRUE(std::get<1>(temp) == v2);
			EXPECT_TRUE(std::get<2>(temp) == v3);
			EXPECT_TRUE(std::get<3>(temp) == v4);
	}
	}


	TEST(CGDK_shared_buffer, buffer_time_1)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append
		tm time_now = chrono::to_tm(chrono::time::local::now());

		{
			// - assign
			auto buf_temp = buf_alloc;

			// - ...
			buf_temp.append<tm>(time_now);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(time_now));

			[[maybe_unused]] auto temp = buf_temp.extract<tm>();

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			// check) 
			//EXPECT_TRUE(temp == time_now); // L"Fail! Tupple 2"
		}
	#endif
	}

	TEST(CGDK_shared_buffer, buffer_time_2)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - append
		tm time_now = chrono::to_tm(chrono::time::local::now());

		{
			// - assign
			auto buf_temp = buf_alloc;

			// - ...
			buf_temp.append<tm>(time_now);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(time_now));

			[[maybe_unused]] tm temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(buf_temp.size() == 0);

			// check) 
			//EXPECT_TRUE(temp == time_now); // L"Fail! Tupple 2"
		}
	#endif
	}

	TEST(CGDK_shared_buffer, buffer_web)
	{
		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// - ...
		auto buf_temp = buf_alloc;

		// 2) Append
		buf_temp.append_text("Test");
	#if defined(FMT_FORMAT_H_)
		buf_temp.append_text("Test {} {} {}\n", 100, "Test", 0.1f);
	#endif
	}


	//-----------------------------------------------------------------
	// Test) Object Serialize
	//-----------------------------------------------------------------

	TEST(CGDK_shared_buffer, buffer_append_extract_serializable)
	{
		struct TEMP_OBJECT : public Ibuffer_serializable
		{
		public:
			int			m_ix = 0;
			float		m_fy = 0.0f;
			std::string	m_strZ;

		public:
			virtual	void	process_serialize_in(buffer_view& _Buffer) override
			{
				m_ix	 = _Buffer.extract<int>();
				m_fy	 = _Buffer.extract<float>();
				m_strZ	 = _Buffer.extract<std::string>();
			}

			virtual	void	process_serialize_out(buffer& _Buffer) override
			{
				_Buffer.append(m_ix);
				_Buffer.append(m_fy);
				_Buffer.append(m_strZ);
			}

			virtual std::size_t	process_size_of() const override
			{
				std::size_t	size = 0;

				size += get_size_of(m_ix);
				size += get_size_of(m_fy);
				size += get_size_of(m_strZ);

				return	size;
			}
		};

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// declare) 임시 객체
		TEMP_OBJECT	a;

		// 3) Object를 작성
		{
			// - 값을 집어 넣음
			a.m_ix	 = 10;
			a.m_fy	 = 2.0;
			a.m_strZ = "Test Value";

			// - 객체 append
			buf_temp.append(a);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(a));
		}

		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 임시 객체를 생성
			TEMP_OBJECT	b;

			// - 객체 extract!
			b = temp_read.extract<TEMP_OBJECT>();

			// check) 
			EXPECT_TRUE(a.m_ix==b.m_ix); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_fy==b.m_fy); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_strZ==b.m_strZ); // L"Fail to Object Serialize"
		}

		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 임시 객체를 생성
			TEMP_OBJECT	b;

			// - 객체 extract!
			temp_read.extract_to(b);

			// check) 
			EXPECT_TRUE(a.m_ix == b.m_ix); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_fy == b.m_fy); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_strZ == b.m_strZ); // L"Fail to Object Serialize"
		}
	}

	TEST(CGDK_shared_buffer, buffer_append_extract_serializable_1)
	{
		struct TEMP_OBJECT : public Ibuffer_serializable
		{
		public:
			int			m_ix = 0;
			float		m_fy = 0.0f;
			std::string	m_strZ;

		public:
			virtual	void	process_serialize_in(buffer_view& _Buffer) override
			{
				m_ix	 = _Buffer.extract<int>();
				m_fy	 = _Buffer.extract<float>();
				m_strZ	 = _Buffer.extract<std::string>();
			}

			virtual	void	process_serialize_out(buffer& _Buffer) override
			{
				_Buffer.append(m_ix);
				_Buffer.append(m_fy);
				_Buffer.append(m_strZ);
			}

			virtual std::size_t	process_size_of() const override
			{
				std::size_t	size = 0;

				size += get_size_of(m_ix);
				size += get_size_of(m_fy);
				size += get_size_of(m_strZ);

				return	size;
			}
		};

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// declare) 임시 객체
		TEMP_OBJECT	a;

		// 3) Object를 작성
		{
			// - 값을 집어 넣음
			a.m_ix	 = 10;
			a.m_fy	 = 2.0;
			a.m_strZ = "Test Value";

			// - 객체 append
			buf_temp.append(a);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(a));
		}

		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 임시 객체를 생성
			TEMP_OBJECT	b;

			// - 객체 extract!
			b = temp_read.front<TEMP_OBJECT>();

			// check) 
			EXPECT_TRUE(a.m_ix==b.m_ix); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_fy==b.m_fy); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_strZ==b.m_strZ); // L"Fail to Object Serialize"
		}

		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 임시 객체를 생성
			TEMP_OBJECT	b;

			// - 객체 extract!
			temp_read.front_to(b);

			// check) 
			EXPECT_TRUE(a.m_ix == b.m_ix); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_fy == b.m_fy); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_strZ == b.m_strZ); // L"Fail to Object Serialize"
		}
	}


	//-----------------------------------------------------------------
	// Test) Object Serialize 2
	//-----------------------------------------------------------------
	TEST(CGDK_shared_buffer, buffer_append_extract_serializable_2)
	{
		struct TEMP_OBJECT : public Ibuffer_serializable
		{
		public:
			int			m_ix = 0;
			float		m_fy = 0.0f;
			std::string	m_strZ;

		public:
			DEFINE_BUFFER_SERIALIZE
			(
				m_ix,
				m_fy,
				m_strZ
			)
		};

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// declare) 임시 객체
		TEMP_OBJECT	a;

		// 3) Object를 작성
		{
			// - 값을 집어 넣음
			a.m_ix	 = 10;
			a.m_fy	 = 2.0;
			a.m_strZ = "Test Value";

			// - 객체 append
			buf_temp.append(a);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(a));
		}

		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 임시 객체를 생성
			TEMP_OBJECT	b;

			// - 객체 extract!
			b = temp_read.extract<TEMP_OBJECT>();

			// check) 
			EXPECT_TRUE(a.m_ix==b.m_ix); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_fy==b.m_fy); // L"Fail to Object Serialize"
			EXPECT_TRUE(a.m_strZ==b.m_strZ); // L"Fail to Object Serialize"
		}
	}


	//-----------------------------------------------------------------
	// Test) Object Serialize
	//-----------------------------------------------------------------
	TEST(CGDK_shared_buffer, buffer_test_01)
	{
		class sTEST_MESSAGE_HEADER
		{
		public:
			int32_t			size = 0;
			int32_t			message = 0;
		};

		class sTEST_MESSAGE :public sTEST_MESSAGE_HEADER, public Ibuffer_serializable
		{
		public:
		DEFINE_BUFFER_SERIALIZE(
				(sTEST_MESSAGE_HEADER&)(*this),
				name,
				value_a,
				value_b,
				value_c
				)
		public:
			std::wstring	name;
			int32_t			value_a = 0;
			int32_t			value_b = 0;
			std::vector<int32_t> value_c;
		};

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// 2) set value
		sTEST_MESSAGE	a;
		a.size		 = 10;
		a.message	 = 10;
		a.name		 = L"TTEESS";
		a.value_a	 = 10;
		a.value_b	 = 100;
		a.value_c	 = {10, 20, 30,100, 100};

		// 3) append
		{
			// - 객체 append
			buf_temp.append(a);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(a));
		}

		// 4) extract
		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - 객체 extract!
			auto b = temp_read.extract<sTEST_MESSAGE>();

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(a.size == b.size);
			EXPECT_TRUE(a.message == b.message);
			EXPECT_TRUE(a.name == b.name);
			EXPECT_TRUE(a.value_a == b.value_a);
			EXPECT_TRUE(a.value_b == b.value_b);
			EXPECT_TRUE(a.value_c == b.value_c);
		}

		// 5) extract_to
		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// declare) 
			sTEST_MESSAGE b;
			
			// - 객체 extract!
			temp_read.extract_to(b);

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(a.size == b.size);
			EXPECT_TRUE(a.message == b.message);
			EXPECT_TRUE(a.name == b.name);
			EXPECT_TRUE(a.value_a == b.value_a);
			EXPECT_TRUE(a.value_b == b.value_b);
			EXPECT_TRUE(a.value_c == b.value_c);
		}
	}
	
	TEST(CGDK_shared_buffer, buffer_test_02)
	{
		class sTEST_MESSAGE_HEADER
		{
		public:
			int32_t			size = 0;
			int32_t			message = 0;
		};

		class sTEST_MESSAGE : public sTEST_MESSAGE_HEADER
		{
		public: 
			std::wstring	name;
			int32_t			value_a = 0;
			int32_t			value_b = 0;
			std::vector<int32_t> value_c;

			ENABLE_STRUCT_SERIALIZABLE
		};

		// - alloc shared_buffer 
		auto buf_alloc = alloc_shared_buffer(2048);

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// 2) 객체
		sTEST_MESSAGE a;
		a.size		 = 10;
		a.message	 = 10;
		a.name		 = L"TTEESS";
		a.value_a	 = 10;
		a.value_b	 = 100;
		a.value_c	 = {10, 20, 30,100, 100};

		// 3) append
		{
			// - append
			buf_temp.append(a);

			// check) 
			EXPECT_TRUE(buf_temp.size() == get_size_of(a));
		}

		// 4) extract
		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - extract
			auto b = temp_read.extract<sTEST_MESSAGE>();

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(a.size == b.size);
			EXPECT_TRUE(a.message == b.message);
			EXPECT_TRUE(a.name == b.name);
			EXPECT_TRUE(a.value_a == b.value_a);
			EXPECT_TRUE(a.value_b == b.value_b);
		}

		// 5) extract_to
		{
			// - 값을 읽을 버퍼
			buffer_view temp_read = buf_temp;

			// - extract
			sTEST_MESSAGE b;
			
			temp_read.extract_to(b);

			// check) 
			EXPECT_TRUE(temp_read.size() == 0);

			// check) 
			EXPECT_TRUE(a.size == b.size);
			EXPECT_TRUE(a.message == b.message);
			EXPECT_TRUE(a.name == b.name);
			EXPECT_TRUE(a.value_a == b.value_a);
			EXPECT_TRUE(a.value_b == b.value_b);
		}
	}
}