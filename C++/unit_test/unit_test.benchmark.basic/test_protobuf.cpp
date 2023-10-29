#include "pch.h"
#include "protobuf/messages_test.pb.h"


namespace protobuf
{
	TEST(CGDK_buffer_benchmakr_basic, pb_append_extract_primitive)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_GENERAL source_message;
			source_message.set_value_1(1);
			source_message.set_value_2(101);
			source_message.set_value_3(-12345);
			source_message.set_value_4(123456);
			source_message.set_value_5(1.0f);
			source_message.set_value_6(10.0);
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_GENERAL message;
			message.ParseFromArray(buf_array, size_serialize);
			[[maybe_unused]] auto value_1 = message.value_1();
			[[maybe_unused]] auto value_2 = message.value_2();
			[[maybe_unused]] auto value_3 = message.value_3();
			[[maybe_unused]] auto value_4 = message.value_4();
			[[maybe_unused]] auto value_5 = message.value_5();
			[[maybe_unused]] auto value_6 = message.value_6();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_append_extract_string)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_string source_message;
			source_message.set_value_1(array_string_char[0]);
			source_message.set_value_2(array_string_char[1]);
			source_message.set_value_3(array_string_char[2]);
			source_message.set_value_4(array_string_char[3]);
			source_message.set_value_5(array_string_char[4]);
			source_message.set_value_6(array_string_char[5]);
			source_message.set_value_7(array_string_char[6]);
			source_message.set_value_8(array_string_char[7]);
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_string message;
			auto result = message.ParseFromArray(buf_array, size_serialize);
			EXPECT_TRUE(result);

			[[maybe_unused]] std::string_view value_1 = message.value_1();
			[[maybe_unused]] std::string_view value_2 = message.value_2();
			[[maybe_unused]] std::string_view value_3 = message.value_3();
			[[maybe_unused]] std::string_view value_4 = message.value_4();
			[[maybe_unused]] std::string_view value_5 = message.value_5();
			[[maybe_unused]] std::string_view value_6 = message.value_6();
			[[maybe_unused]] std::string_view value_7 = message.value_7();
			[[maybe_unused]] std::string_view value_8 = message.value_8();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_append_extract_std_list_int)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_list_int source_message;

			for(auto& iter: array_int)
				source_message.add_value_1(iter);
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_list_int message;
			std::vector<int> value_1;
			message.ParseFromArray(buf_array, size_serialize);
			auto temp_1 = message.value_1();
			value_1.reserve(temp_1.size());
			for (int i = 0; i < temp_1.size(); ++i)
				value_1.push_back(temp_1.Get(i));
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_append_extract_std_map_std_string_int)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_map_std_string_int source_message;
			auto temp_value_1 = source_message.mutable_value_1();
			for(auto& iter: std_map_std_string_int)
				(*temp_value_1)[iter.first] = iter.second;
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_map_std_string_int message;
			std::map<std::string, int> value_1;
			message.ParseFromArray(buf_array, size_serialize);
			auto& temp_1 = message.value_1();
			for (auto& iter : temp_1)
			{
				value_1.insert({ iter.first, iter.second });
			}
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_append_extract_struct)
	{
		char buf_array[4096];

		FOO foo;
		foo.v1 = 100;
		foo.v2 = std::string("test_string");
		foo.v3 = std::list<int>{ 1,2,3,4,5 };
		foo.v4 = 10000;
		foo.v5 = std::map<std::string, int>{ {"a", 1}, {"b", 2}, {"c", 3} };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_struct source_message;
			source_message.set_value_1(foo.v1);
			source_message.set_value_2(foo.v2);
			for (auto& iter : foo.v3)
				source_message.add_value_3(iter);
			source_message.set_value_4(foo.v4);
			auto temp_value_5 = source_message.mutable_value_5();
			for (auto& iter : foo.v5)
				(*temp_value_5)[iter.first] = iter.second;
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_struct message;
			message.ParseFromArray(buf_array, size_serialize);
			FOO dest;
			dest.v1 = message.value_1();
			dest.v2 = message.value_2();
			auto temp_3 = message.value_3();
			for (int i = 0; i < temp_3.size(); ++i)
				dest.v3.push_back(temp_3.Get(i));
			dest.v4 = message.value_4();
			for (auto& iter : message.value_5())
				dest.v5.insert({ iter.first, iter.second });
		}
	}
}