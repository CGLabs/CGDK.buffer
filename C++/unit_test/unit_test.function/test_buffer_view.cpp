#include "pch.h"

// definitions) 
#define	_TEST_COUNT	1

#if defined(_MSC_VER)
	#pragma warning(disable:4566)
#endif

template <class T>
void test_buffer_view_extract_string(const T& _source)
{
	// declare) static memory
	char buf_array[2048];
	CGDK::buffer temp(buf_array);

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
void test_buffer_view_front_string(const T& _source)
{
	// declare) static memory
	char buf_array[2048];
	CGDK::buffer temp(buf_array);

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
	TEST(CGDK_buffer_view, buffer_timepoint)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		{
			// declare) static memory
			char buf_array[2048];

			// - buffer
			CGDK::buffer buf_temp(buf_array);

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
			// declare) static memory
			char buf_array[2048];

			// - buffer
			CGDK::buffer buf_temp(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_general)
	{
		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
		for(int i=0; i<_TEST_COUNT;++i)
		{
			CGDK::buffer buf_temp_inner(buf_temp);

			function_append_general(buf_temp_inner);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_general)
	{
		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_extract_GENERAL(buf_temp);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_general)
	{
		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_GENERAL(buf_temp);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_general_with_pos)
	{
		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
		function_append_general(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_with_pos_general(buf_temp);
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// Defintions)
		std::string_view str_test{ "Test String" };

		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_test = (CGDK::buffer(buf_array) ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(str_test);

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK_buffer_view, buffer_prepend_const_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// declare) static memory
		char buf_array[2048];

		// - Buffer 할당
		CGDK::buffer buf_alloc = (CGDK::buffer(buf_array) ^ OFFSET);

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

	TEST(CGDK_buffer_view, buffer_prepend_string_format)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// defintions)
		std::string_view strTest1 = "Test String";
		std::string_view strTest3 = "Test End of String ";

		// declare) static memory
		char buf_array[2048];

		// - buffer 할당
		CGDK::buffer buf_test = (CGDK::buffer(buf_array) ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(strTest1);
	#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		buf_test.prepend_string(std::string_view{ "Test {} {}" }, 10, 20);
	#endif
		buf_test.prepend_string(strTest3);

		// - 값 읽기
		[[maybe_unused]] auto str_read_3 = buf_test.extract<std::string_view>();
	#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		[[maybe_unused]] auto str_read_2 = buf_test.extract<std::string_view>();
	#endif
		[[maybe_unused]] auto str_read_1 = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(strTest1 == str_read_1);
		EXPECT_TRUE(strTest3 == str_read_3);
	}

	TEST(CGDK_buffer_view, buffer_append_string)
	{
		// Defintions)
		std::string_view str_test{ "Test String" };

		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_test(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_string_view)
	{
		// Defintions)
		std::string	str_test{ "Test String" };

		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_string_format)
	{
		// declare) static memory
		char buf_array[2048];

		// - buffer
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
	#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		buf_temp.append(std::string_view{ "Test {} {}" }, 10, 20);
	#endif
		buf_temp.append(std::string_view{ "Test" });

		// - 값 읽기
	#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		[[maybe_unused]] auto str_read_1 = buf_temp.extract<std::string_view>();
	#endif
		[[maybe_unused]] auto str_read_2 = buf_temp.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == 0);
		EXPECT_TRUE(str_read_2 == std::string_view("Test"));
	}

	TEST(CGDK_buffer_view, buffer_append_const_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

		// - 값 써넣기
		buf_temp.append(std::string_view("Test XX"));

		// check) 
		EXPECT_TRUE(buf_temp.size() == get_size_of(std::string_view("Test XX")));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_temp.extract<char*>();

		// check) 
		EXPECT_TRUE(buf_temp.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_String2)
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
		// X) Memory Alloc
		// - alloc buffer
		char buf_temp_1[2048];
		char buf_temp_2[2048];
		
		// Case A) 메모리 할당 (Allocating Memory)
		CGDK::buffer buf_write(buf_temp_1);

		// 2) 문자열 리스트 통채로 추가 (appending string list)
		buf_write.append(list_test);

		// check) 
		EXPECT_TRUE(buf_write.size() == get_size_of(list_test));

		// Case B) 메모리 할당 (Allocation Memory)
		CGDK::buffer temp_memory(buf_temp_2);

		// 3) Iterator를 사용해 특정 범위의 데이터만 써넣을 수도 있다.(ranged appending using iterator)
		temp_memory.append(list_test.begin(), list_test.end());

		// check) 
		EXPECT_TRUE(temp_memory.size() == get_size_of(list_test));


		//-----------------------------------------------------------------
		// 설명) 배열에 저장된 String 읽어들이기 (2)
		//-----------------------------------------------------------------
		{
			// 1) Buffer...
			buffer_view buf_read = buf_write;

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
			buffer_view buf_read = buf_write;

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
			buffer_view buf_read = buf_write;

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
			buffer_view temp_read = buf_write;

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

	TEST(CGDK_buffer_view, buffer_append_text)
	{
		// Defintions)
		const char*	str_test = "Test String";

		// declare) static memory
		char buf_array[2048];

		// - 
		CGDK::buffer buf_test(buf_array);

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
		EXPECT_TRUE(memcmp("Test String", buf_array, std::char_traits<char>::length(str_test) * sizeof(char)) == 0);
		EXPECT_TRUE(memcmp("Test Temp", buf_array + std::char_traits<char>::length(str_test) * sizeof(char), std::char_traits<char>::length("Test Temp")*sizeof(char)) == 0);
	}

	TEST(CGDK_buffer_view, buffer_append_Initializer_list)
	{
		// declare) static memory
		char buf_array[2048];
		CGDK::buffer buf_test(buf_array);

		// 2) 추가한다
		buf_test.append({ 1,2,3,4,5,6,7 });
	}

	TEST(CGDK_buffer_view, buffer_iostream)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

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
			buffer_view bufferTempRead = buf_temp;
				
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

	TEST(CGDK_buffer_view, buffer_append_front_STRUCT_1)
	{
		struct TESTSTRUCT
		{
   			int			iValue;
   			uint32_t	dwValue;
   			char		chValue;
		};

		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_front_to_STRUCT_1)
	{
		struct TESTSTRUCT
		{
			int			iValue;
			uint32_t	dwValue;
			char		chValue;
		};

		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_front_STRUCT_2)
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
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_front_to_STRUCT_2)
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
		char buf_array[2048];
		CGDK::buffer buf_temp(buf_array);

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
	TEST(CGDK_buffer_view, buffer_string_extract_char)					{ test_buffer_view_extract_string(array_string_char); }
	TEST(CGDK_buffer_view, buffer_string_extract_wchar_t)				{ test_buffer_view_extract_string(array_string_wchar_t); }
	TEST(CGDK_buffer_view, buffer_string_extract_char16_t)				{ test_buffer_view_extract_string(array_string_char16_t); }
	TEST(CGDK_buffer_view, buffer_string_extract_char32_t)				{ test_buffer_view_extract_string(array_string_char32_t); }
	// 2) string(std::basic_string_view<T> type) append/extract
	TEST(CGDK_buffer_view, buffer_string_extract_std_string_view)		{ test_buffer_view_extract_string(array_string_std_string_view); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_wstring_view)		{ test_buffer_view_extract_string(array_string_std_wstring_view); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_u16string_view)	{ test_buffer_view_extract_string(array_string_std_u16string_view); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_u32string_view)	{ test_buffer_view_extract_string(array_string_std_u32string_view); }
	// 3) string(std::basic_string<T> type) append/extract
	TEST(CGDK_buffer_view, buffer_string_extract_std_string)			{ test_buffer_view_extract_string(array_string_std_string); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_wstring)			{ test_buffer_view_extract_string(array_string_std_wstring); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_u16string)			{ test_buffer_view_extract_string(array_string_std_u16string); }
	TEST(CGDK_buffer_view, buffer_string_extract_std_u32string)			{ test_buffer_view_extract_string(array_string_std_u32string); }

	// 4) string(pointer type) append/front
	TEST(CGDK_buffer_view, buffer_front_string_char)					{ test_buffer_view_front_string(array_string_char); }
	TEST(CGDK_buffer_view, buffer_front_string_wchar_t)					{ test_buffer_view_front_string(array_string_wchar_t); }
	TEST(CGDK_buffer_view, buffer_front_string_char16_t)				{ test_buffer_view_front_string(array_string_char16_t); }
	TEST(CGDK_buffer_view, buffer_front_string_char32_t)				{ test_buffer_view_front_string(array_string_char32_t); }
	// 5) string(std::basic_string_view<T> type) append/front
	TEST(CGDK_buffer_view, buffer_front_string_std_string_view)			{ test_buffer_view_front_string(array_string_std_string_view); }
	TEST(CGDK_buffer_view, buffer_front_string_std_wstring_view)		{ test_buffer_view_front_string(array_string_std_wstring_view); }
	TEST(CGDK_buffer_view, buffer_front_string_std_u16string_view)		{ test_buffer_view_front_string(array_string_std_u16string_view); }
	TEST(CGDK_buffer_view, buffer_front_string_std_u32string_view)		{ test_buffer_view_front_string(array_string_std_u32string_view); }
	// 6) string(std::basic_string<T> type) append/front
	TEST(CGDK_buffer_view, buffer_front_string_std_string)				{ test_buffer_view_front_string(array_string_std_string); }
	TEST(CGDK_buffer_view, buffer_front_string_std_wstring)				{ test_buffer_view_front_string(array_string_std_wstring); }
	TEST(CGDK_buffer_view, buffer_front_string_std_u16string)			{ test_buffer_view_front_string(array_string_std_u16string); }
	TEST(CGDK_buffer_view, buffer_front_string_std_u32string)			{ test_buffer_view_front_string(array_string_std_u32string); }

	// 7) bound check test
	TEST(CGDK_buffer_view, buffer_string_append_bound_check)
	{
		// Defintions)
		std::string_view str_test = "Test String";

		char buf_array[get_size_of("Test String")];

		// - alloc shared_buffer
		CGDK::buffer buf_alloc(buf_array);

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
			CGDK::buffer buf_test = buf_alloc;

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

	TEST(CGDK_buffer_view, buffer_string_prepend_bound_check)
	{
		// Defintions)
		std::string_view str_test = "Test String";

		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - overflow test
		{
			// - 
			CGDK::buffer buf_test = buf_alloc + offset(get_size_of(str_test) - 1);

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
			CGDK::buffer buf_test = buf_alloc + offset(get_size_of(str_test));

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
	}


	//-----------------------------------------------------------------
	// Test) array
	//-----------------------------------------------------------------
	// 1) array
	//char*										array_string_char[];
	//wchar_t*									array_string_wchar_t[];
	//std::string								array_std_string_stdstring[];
	//std::wstring								array_std_string_stdwstring[];
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for(int i=0;i<_TEST_COUNT;++i)
		{
			CGDK::buffer buf_write = buf_alloc;

			buf_write.append(array_string_wchar_t);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(array_string_wchar_t));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_array_wchar_t)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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
	//std::vector<int>			vector_int;
	//std::vector<std::string>	std_vector_std_string;
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_vector_int)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_write = buf_alloc;

			buf_write.append(vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(vector_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_vector_int)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(vector_int)>();

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_vector_int)
	{
		// 1) alloc buffer 
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for(int i=0; i<_TEST_COUNT; ++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(vector_int)>();

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(vector_int);

			// declare) 
			decltype(vector_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_append_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for(int i=0;i<_TEST_COUNT;++i)
		{
			CGDK::buffer buf_write = buf_alloc;

			buf_write.append(std_vector_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_vector_std_string));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_vector_std_string)>();

			// check) 
			EXPECT_TRUE(temp==std_vector_std_string); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			decltype(std_vector_std_string) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	TEST(CGDK_buffer_view, buffer_front_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_vector_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_vector_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_vector_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(std_vector_std_string) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_vector_std_string); // L"Fail to vector<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_std_string);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_vector_std_string)>();

			// check) 
			EXPECT_TRUE(temp==std_vector_std_string); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_vector_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			CGDK::buffer buf_temp = buf_alloc + offset(2048);

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
	TEST(CGDK_buffer_view, buffer_std_array_append_extract)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<int, 10>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_to)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

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

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_char)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_char);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(array_string_char));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<decltype(array_string_char)>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_to_char)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_wchar_t)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

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

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_to_wchar_t)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

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

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_std_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<std::string, 4> temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_to_std_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<std::string, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

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

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_std_string_view)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string_view, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_std_array_append_extract_to_std_string_view)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		CGDK::buffer buf_test = buf_alloc;

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
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_write = buf_alloc;

			buf_write.append(std_list_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			decltype(std_list_int) temp;
						
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_list_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append 
		buf_alloc.append(std_list_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(std_list_int) temp;
			
			// - front~
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_int); // L"Fail to list<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_list_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_std_string);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_std_string)>();

			// check) 
			EXPECT_TRUE(temp == std_list_std_string);
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			// declare) 
			decltype(std_list_std_string) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string);
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_list_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list<string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			decltype(std_list_std_string) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_std_string); // L"Fail to list<string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_list_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	// 3) std::list<std::vector<int>>		std_list_vector_int;
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_vector_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_list_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append string
		buf_alloc.append(std_list_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_list_vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_list_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_list_vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_list_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_list_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(std_list_vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_list_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_list_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_list_vector_int);

			// declare) 
			decltype(std_list_vector_int) temp;
			
			// - pop front!
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_list_vector_int); // L"Fail to list<vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}


	//-----------------------------------------------------------------
	// Test) Container-set
	//-----------------------------------------------------------------
	// 1) std::set<int>			std_set_int;
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_set_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_set_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(std_set_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_int); // L"Fail to set<int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_set_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_append_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_std_string));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_set_std_string)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_set_std_string);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_set_std_string));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			// declare) 
			decltype(std_set_std_string) temp;
						
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_set_std_string); // L"Fail to set<std::string> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_set_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_int_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_int_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_map_int_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_int_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_int_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			decltype(std_map_int_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_int_int); // L"Fail to map<int,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_map_int_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_string_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_map_std_string_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			decltype(std_map_std_string_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_int); // L"Fail to map<string,int> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}
	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_map_string_int_push)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	// 3) std::map<std::string, std::vector<int>>		std_map_std_string_std_vector_int;
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - ....
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_string_std_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_string_std_vector_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;

			auto temp = buf_temp.extract<decltype(std_map_std_string_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_std_vector_int); // L"Fail to map<string,vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;

			decltype(std_map_std_string_std_vector_int) temp;
			
			buf_temp.extract_to(temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_std_vector_int); // L"Fail to map<string,vector<int>> append/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_std_vector_int));

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			auto temp = buf_temp.front<decltype(std_map_std_string_std_vector_int)>(pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_std_vector_int); // L"Fail to map<string,vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		buf_alloc.append(std_map_std_string_std_vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(std_map_std_string_std_vector_int));

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			buffer_view buf_temp = buf_alloc;
			POS pos_temp;

			decltype(std_map_std_string_std_vector_int) temp;
			
			buf_temp.front_to(temp, pos_temp);

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_std_vector_int); // L"Fail to map<string,vector<int>> append/front"
			EXPECT_TRUE(static_cast<int64_t>(buf_temp.size()) == pos_temp.get_pos());
		}
	}


	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_map_string_vector_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_map_std_string_std_vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_map_std_string_std_vector_int)>();

			// check) 
			EXPECT_TRUE(temp == std_map_std_string_std_vector_int); // L"Fail to map<string,vector<int>> prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	// 4) std::map<std::string, std::vector<std::string_view>>	std_map_std_vector_std_string_view;
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_vector_std_string_view);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_vector_std_string_view));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array) ^ 2048;

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
	TEST(CGDK_buffer_view, buffer_append_CONTAINER_unoredered_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_unordered_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_unordered_map_std_string_int));
		}
	}

	TEST(CGDK_buffer_view, buffer_extract_CONTAINER_unoredered_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_extract_to_CONTAINER_unoredered_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_front_CONTAINER_unoredered_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_prepend_extract_CONTAINER_unoredered_map_string_int)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer temp_memory = CGDK::buffer(buf_array);

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			auto buf_temp = temp_memory ^ 2048;

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
	TEST(CGDK_buffer_view, buffer_VariableLength)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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
	TEST(CGDK_buffer_view, buffer_buffer)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		char buf_array_A[2048];
		CGDK::buffer bufA(buf_array_A);
		bufA.resize(100);

		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		buf_alloc.append(bufA);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int) + get_size_of(bufA));

		// - extract
		[[maybe_unused]] auto a = buf_alloc.extract<decltype(vector_int)>();
		[[maybe_unused]] auto b = buf_alloc.extract<buffer_view>();

		// check) 
		EXPECT_TRUE(buf_alloc.size() == 0);
	}
	TEST(CGDK_buffer_view, buffer_buffer_to)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		char buf_array_A[2048];
		CGDK::buffer bufA(buf_array_A);
		bufA.resize(100);

		buf_alloc.append(vector_int);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int));

		buf_alloc.append(bufA);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == get_size_of(vector_int) + get_size_of(bufA));

		// - extract
		[[maybe_unused]] decltype(vector_int) a;
		buf_alloc.extract_to(a);
		[[maybe_unused]] buffer_view b;
		buf_alloc.extract_to(b);

		// check) 
		EXPECT_TRUE(buf_alloc.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_map_tuple01)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple02)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple03)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple04)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple05)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple06)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple07)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_map_tuple08)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_source = CGDK::buffer(buf_array);

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
			std::tie<int, std::string_view, float>(dest_a, dest_b, dest_c)	 = buf_read.extract<std::tuple<int, std::string_view, float>>();

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

	TEST(CGDK_buffer_view, test_buffer_map_tuple09)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp = TUPPLE_B(0, TUPPLE_A(0, 0, 1.0f, "Test"), "Value");

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, test_buffer_map_tuple10)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp = TUPPLE_B(0, TUPPLE_A(0, 0, 1.0f, "Test"), "Value");

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_time_1)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_time_2)
	{
	#if defined(CGDK_SYSTEM_OBJECT)
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_web)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_extract_serializable)
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

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_append_extract_serializable_1)
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

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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
	TEST(CGDK_buffer_view, buffer_append_extract_serializable_2)
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

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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

	TEST(CGDK_buffer_view, buffer_constructor_1)
	{
		//// 1) costructor
		//constexpr _buffer_view() noexcept {}
		//constexpr _buffer_view(_element_void_t<element_t>* _ptr, size_type _size = 0) noexcept : base_t{ _size, reinterpret_cast<element_t*>(_ptr) } {}
		//constexpr _buffer_view(const self_t& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
		//constexpr _buffer_view(self_t&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}

		//template <class T>
		//constexpr _buffer_view(const _buffer_view<T>& _buffer) noexcept : base_t{ _buffer.size(), const_cast<std::remove_const_t<T>*>(_buffer.data()) } {}
		//template <class T>
		//constexpr _buffer_view(_buffer_view<T>&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}

		//constexpr _buffer_view(const base_t& _buffer) noexcept : base_t{ _buffer.size_, _buffer.data_ } {}
		//template <class T>
		//constexpr _buffer_view(const buffer_base<T>& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
		//constexpr _buffer_view(base_t&& _buffer) noexcept : base_t{ _buffer.size_, _buffer.data_ } {}
		//template <class T>
		//constexpr _buffer_view(buffer_base<T>&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}

		//template <class T>
		//constexpr _buffer_view(std::basic_string_view<T> _string) noexcept : base_t{ _string.length(), reinterpret_cast<ELEM_T*>(const_cast<T*>(_string.data())) } {}
	}

	TEST(CGDK_buffer_view, buffer_constructor_2)
	{
	}

	TEST(CGDK_buffer_view, buffer_operation_1_1)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		{
			CGDK::buffer buf_test_source = buf_alloc;
			buf_test_source.append<int>(4);
			buf_test_source.append<uint64_t>(4);

			CGDK::buffer buf_test;

			EXPECT_TRUE(buf_test.exist() == false);
			EXPECT_TRUE(buf_test.empty() == true);

			buf_test = buf_test_source;

			EXPECT_TRUE(buf_test.exist() == true);
			EXPECT_TRUE(buf_test.empty() == false);

			EXPECT_TRUE(buf_test.data() == buf_test_source.data());
			EXPECT_TRUE(buf_test.size() == buf_test_source.size());
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_1_2)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		{
			CGDK::buffer buf_test;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test = buf_alloc;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test.append<uint32_t>();

			EXPECT_TRUE(buf_test.size() == sizeof(uint32_t));
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_2)
	{
		//// - alloc buffer
		//char buf_array[2048];
		//CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		//{
		//	CGDK::buffer buf_test;

		//	EXPECT_TRUE(buf_test.exist() == false);
		//	EXPECT_TRUE(buf_test.empty() == true);

		//	buf_test = buf_alloc;

		//	EXPECT_TRUE(buf_test.exist() == true);
		//	EXPECT_TRUE(buf_test.empty() == false);
		//}
	}

	TEST(CGDK_buffer_view, buffer_operation_3)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		{
			CGDK::buffer buf_test;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test = buf_alloc;
			EXPECT_TRUE(buf_test.size() == 0);

			buf_test.append<uint32_t>();
			EXPECT_TRUE(buf_test.size() == sizeof(uint32_t));

			// - set_size
			buf_test.set_size(100);
			EXPECT_TRUE(buf_test.size() == 100);

			// - add_size
			buf_test.add_size(100);
			EXPECT_TRUE(buf_test.size() == 200);

			// - inc_size
			buf_test.inc_size();
			EXPECT_TRUE(buf_test.size() == 201);

			// - dec_size
			buf_test.dec_size();
			EXPECT_TRUE(buf_test.size() == 200);

			// - sub_size
			buf_test.sub_size(100);
			EXPECT_TRUE(buf_test.size() == 100);

			buf_test.sub_size(100);
			EXPECT_TRUE(buf_test.size() == 0);

			// - clear
			buf_test.append<int>(100);
			EXPECT_TRUE(buf_test.size() == sizeof(int));
			buf_test.clear();
			EXPECT_TRUE(buf_test.data() == nullptr);
			EXPECT_TRUE(buf_test.size() == 0);
			EXPECT_TRUE(buf_test.exist() == false);
			EXPECT_TRUE(buf_test.empty() == true);

			//{
			//	bool result = false;
			//	try
			//	{
			//		buf_test.sub_size(100);
			//	}
			//	catch (...)
			//	{
			//		result = true;
			//	}

			//	EXPECT_TRUE(result == true);
			//}

			//{
			//	buf_test.set_size(0);

			//	bool result = false;
			//	try
			//	{
			//		buf_test.dec_size();
			//	}
			//	catch (...)
			//	{
			//		result = true;
			//	}

			//	EXPECT_TRUE(result == true);
			//}
		}

		//constexpr CAST_SIZE_T		size() const noexcept { CGDK_ASSERT(this->size_ == static_cast<size_type>(static_cast<CAST_SIZE_T>(this->size_))); return static_cast<CAST_SIZE_T>(this->size_); }
		//constexpr size_type			size_bytes() const noexcept { return this->size_ * sizeof(element_t); }
		//template <class CAST_SIZE_T>
		//constexpr CAST_SIZE_T		size_bytes() const noexcept { auto bytes = size_bytes(); CGDK_ASSERT(bytes == static_cast<size_type>(static_cast<CAST_SIZE_T>(bytes))); return static_cast<CAST_SIZE_T>(bytes); }

		//constexpr void				set_size(size_type _new_size) noexcept { this->size_ = _new_size; }
		//constexpr void				add_size(size_type _size) noexcept { this->size_ += _size; }
		//constexpr void				sub_size(size_type _size) noexcept { this->size_ -= _size; }
		//constexpr void				inc_size() noexcept { ++this->size_; }
		//constexpr void				dec_size() noexcept { --this->size_; }
		//constexpr void				clear() noexcept { this->size_ = 0; this->data_ = nullptr; }
	}

	TEST(CGDK_buffer_view, buffer_operation_4_1)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - operator + CGDK::offset
		{
			CGDK::buffer buf_test = buf_alloc ^ 100;

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 100);

			auto buf_test2 = buf_test + offset(100);

			EXPECT_TRUE(buf_test.data(100) == buf_test2.data());
			EXPECT_TRUE(buf_test.size() == 100);
			EXPECT_TRUE(buf_test2.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_4_2)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - operator += CGDK::offset
		{
			CGDK::buffer buf_test = buf_alloc ^ 100;

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 100);

			buf_test += CGDK::offset(100);

			EXPECT_TRUE(buf_test.data() == buf_alloc.data(100));
			EXPECT_TRUE(buf_test.size() == 0);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_4_3)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - operator + CGDK::size
		{
			CGDK::buffer buf_test = buf_alloc;

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 0);

			auto buf_test2 = buf_test + size(100);

			EXPECT_TRUE(buf_test.data() == buf_test2.data());
			EXPECT_TRUE(buf_test.size() == 0);
			EXPECT_TRUE(buf_test2.size() == 100);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_4_4)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// - operator += CGDK::size
		{
			CGDK::buffer buf_test = buf_alloc;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test += CGDK::size(100);

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 100);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_5_1)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// operator ^ int
		{
			CGDK::buffer buf_test;

			EXPECT_TRUE(buf_alloc.size() == 0);

			buf_test = buf_alloc ^ 100;

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 100);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_5_2)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// operator ^= int
		{
			CGDK::buffer buf_test = buf_alloc;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test ^= 100;

			EXPECT_TRUE(buf_test.size() == 100);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_5_3)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		// operator ^ CGDK::buffer_view
		{
			CGDK::buffer buf_test;

			EXPECT_TRUE(buf_test.size() == 0);

			buf_test = buf_alloc ^ CGDK::buffer_view{ buf_alloc.data(), 100 };

			EXPECT_TRUE(buf_test.data() == buf_alloc.data());
			EXPECT_TRUE(buf_test.size() == 100);
		}
	}
	TEST(CGDK_buffer_view, buffer_operation_5_4)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		buf_alloc[10] = 100;

		auto v = buf_alloc[10];

		EXPECT_TRUE(v == 100);
	}

	TEST(CGDK_buffer_view, buffer_operation_to_string)
	{
		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

		{
			CGDK::buffer buf_test = buf_alloc;

			const auto str_test = "test string";

			// - append text
			buf_test.append_text<char>(str_test);

			// - to string
			auto str_temp = buf_test.to_string<char>();

			// check) 
			EXPECT_TRUE(str_temp == str_test);
		}

		{
			CGDK::buffer buf_test = buf_alloc;

			const auto str_test = L"test string";

			// - append text
			buf_test.append_text<wchar_t>(str_test);

			// - to string
			auto str_temp = buf_test.to_string<wchar_t>();

			// check) 
			EXPECT_TRUE(str_temp == str_test);
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_datag)
	{
		//constexpr element_t* data() const noexcept { return this->data_; }
		//constexpr element_t* data(int64_t _offset) const { return this->data_ + _offset; }
		//template <class T = element_t>
		//constexpr auto				data() const noexcept { return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_); }
		//template <class T = element_t>
		//constexpr auto				data(int64_t _offset) const { return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_ + _offset); }
		//constexpr void				set_data(element_t * _data) noexcept { this->data_ = _data; }
		//constexpr void				add_data(size_type _size) noexcept { this->data_ += _size; }
		//constexpr void				sub_data(size_type _size) noexcept { this->data_ -= _size; }

	}

	TEST(CGDK_buffer_view, buffer_operation_resize)
	{
		//constexpr void				resize(size_type _new_size) { if (_new_size > this->size_) throw std::length_error("resize operation of _buffer_view<T>' is allowed only for deminishing size 'resize(size_t)'. use operator '^' instead"); this->size_ = _new_size; }
	}

	TEST(CGDK_buffer_view, buffer_operation_swap)
	{
		// - alloc buffer
		char buf_array_1[2048];
		CGDK::buffer buf_alloc_1 = CGDK::buffer(buf_array_1);

		// - alloc buffer
		char buf_array_2[2048];
		CGDK::buffer buf_alloc_2 = CGDK::buffer(buf_array_2);

		{
			CGDK::buffer buf_test1 = buf_alloc_1;
			buf_test1.append<int32_t>(100);
			buf_test1.append<int64_t>(10000);

			// check) 
			EXPECT_TRUE(buf_test1.data() == buf_alloc_1.data());
			EXPECT_TRUE(buf_test1.size() == (sizeof(int32_t) + sizeof(int64_t)));

			CGDK::buffer buf_test2 = buf_alloc_2;
			buf_test2.append<char>(1);
			buf_test2.append<char>(2);
			buf_test2.append<char>(3);

			// check) 
			EXPECT_TRUE(buf_test2.data() == buf_alloc_2.data());
			EXPECT_TRUE(buf_test2.size() == (sizeof(char) + sizeof(char) + sizeof(char)));

			buf_test1.swap(buf_test2);

			// check) 
			EXPECT_TRUE(buf_test1.data() == buf_alloc_2.data());
			EXPECT_TRUE(buf_test1.size() == (sizeof(char) + sizeof(char) + sizeof(char)));
			EXPECT_TRUE(buf_test2.data() == buf_alloc_1.data());
			EXPECT_TRUE(buf_test2.size() == (sizeof(int32_t) + sizeof(int64_t)));
		}
	}

	TEST(CGDK_buffer_view, buffer_operation_copy)
	{
		// - alloc buffer
		char buf_array_source[2048];
		CGDK::buffer buf_alloc_source = CGDK::buffer(buf_array_source);

		buf_alloc_source.append<int32_t>(100);
		buf_alloc_source.append<int64_t>(100);
		buf_alloc_source.append<std::string_view>("test_view");

		// - alloc buffer
		char buf_array_dest[2048];
		CGDK::buffer buf_alloc_dest = CGDK::buffer(buf_array_dest);

		// - copy from
		buf_alloc_dest.copy_from(buf_alloc_source);

		EXPECT_TRUE(buf_alloc_source.size() == buf_alloc_dest.size());

		auto a1 = buf_alloc_source.extract<int32_t>();
		auto b1 = buf_alloc_dest.extract<int32_t>();
		EXPECT_TRUE(a1 == b1);

		auto a2 = buf_alloc_source.extract<int64_t>();
		auto b2 = buf_alloc_dest.extract<int64_t>();
		EXPECT_TRUE(a2 == b2);

		auto a3 = buf_alloc_source.extract<std::string_view>();
		auto b3 = buf_alloc_dest.extract<std::string_view>();
		EXPECT_TRUE(a3 == b3);
		EXPECT_TRUE(buf_alloc_source.size() == 0);
		EXPECT_TRUE(buf_alloc_dest.size() == 0);
	}

	TEST(CGDK_buffer_view, buffer_operation_split_head)
	{
		//// - alloc buffer
		//char buf_array_1[2048];
		//CGDK::buffer buf_alloc_1 = CGDK::buffer(buf_array_1);

		//// - append
		//buf_alloc_1.append<int32_t>(100);
		//buf_alloc_1.append<int64_t>(100);
		//buf_alloc_1.append<std::string_view>("test_view");

		//// - store size
		//auto size_pre = buf_alloc_1.size();

		//// - split
		//auto result = buf_alloc_1.split_head(12);

		//EXPECT_TRUE(buf_alloc_1.size() == size_pre - 12);
		//EXPECT_TRUE(result.size() == 12);
		//EXPECT_TRUE(result.data() + 12 == buf_alloc_1.data());
	}

	TEST(CGDK_buffer_view, buffer_operation_split_tail)
	{
	}

	//-----------------------------------------------------------------
	// Test) Object Serialize
	//-----------------------------------------------------------------
	TEST(CGDK_buffer_view, buffer_test_01)
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

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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
	
	TEST(CGDK_buffer_view, buffer_test_02)
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

		// - alloc buffer
		char buf_array[2048];
		CGDK::buffer buf_alloc = CGDK::buffer(buf_array);

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