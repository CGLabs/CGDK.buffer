#include "pch.h"

namespace CGDK
{
	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_01_primitive)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append<int32_t>(1);
			buf_temp.append<uint32_t>(101);
			buf_temp.append<int64_t>(-12345);
			buf_temp.append<uint64_t>(123456);
			buf_temp.append<float>(1.0f);
			buf_temp.append<double>(10.0);

			// 역직렬화
			[[maybe_unused]] auto value_1 = buf_temp.extract<int32_t>();
			[[maybe_unused]] auto value_2 = buf_temp.extract<uint32_t>();
			[[maybe_unused]] auto value_3 = buf_temp.extract<int64_t>();
			[[maybe_unused]] auto value_4 = buf_temp.extract<uint64_t>();
			[[maybe_unused]] auto value_5 = buf_temp.extract<float>();
			[[maybe_unused]] auto value_6 = buf_temp.extract<double>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_02_list_int)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append(array_int);

			// 역직렬화
			[[maybe_unused]] auto temp = buf_temp.extract<std::vector<int>>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_03_string)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append<std::string_view>(array_string_char[0]);
			buf_temp.append<std::string_view>(array_string_char[1]);
			buf_temp.append<std::string_view>(array_string_char[2]);
			buf_temp.append<std::string_view>(array_string_char[3]);
			buf_temp.append<std::string_view>(array_string_char[4]);
			buf_temp.append<std::string_view>(array_string_char[5]);
			buf_temp.append<std::string_view>(array_string_char[6]);
			buf_temp.append<std::string_view>(array_string_char[7]);

			// 역직렬화
			[[maybe_unused]] auto value_1 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_2 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_3 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_4 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_5 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_6 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_7 = buf_temp.extract<std::string_view>();
			[[maybe_unused]] auto value_8 = buf_temp.extract<std::string_view>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_04_list_string)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append(array_std_string);

			// 역직렬화
			[[maybe_unused]] auto temp = buf_temp.extract<std::vector<std::string_view>>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_05_key_value_string_int)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append(std_map_std_string_int);

			// 역직렬화
			[[maybe_unused]] auto temp = buf_temp.extract<std::map<std::string, int>>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_06_struct_primitive)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };

		TEST_PRIMITIVE test_struct;
		test_struct.value_1 = 1;
		test_struct.value_2 = 101;
		test_struct.value_3 = -12345;
		test_struct.value_4 = 123456;
		test_struct.value_5 = 1.0f;
		test_struct.value_6 = 10.0;

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append(test_struct);

			// 역직렬화
			[[maybe_unused]] auto dest = buf_temp.extract<TEST_PRIMITIVE>();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, cb_benchmark_07_struct_complex)
	{
		char buf_array[4096];

		CGDK::buffer buf_create{ buf_array };
		
		FOO foo;
		foo.v1 = 100;
		foo.v2 = std::string("test_string");
		foo.v3 = std::list<int>{1,2,3,4,5};
		foo.v4 = 10000;
		foo.v5 = std::map<std::string, int>{ {"a", 1}, {"b", 2}, {"c", 3} };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			CGDK::buffer buf_temp = buf_create;

			// 직렬화
			buf_temp.append(foo);

			// 역직렬화
			[[maybe_unused]] auto dest = buf_temp.extract<FOO>();
		}
	}
}