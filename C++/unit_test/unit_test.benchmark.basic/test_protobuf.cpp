#include "pch.h"
#include "protobuf/messages_test.pb.h"


namespace protobuf
{
	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_01_primitive)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			size_t size_serialize[6]{ 0,0,0,0,0,0 };

			// 직렬화
			{
				size_t pos_serialize = 0;

				test::protobuf_message_primitive_sint32 source_message_1;
				source_message_1.set_value(1);
				source_message_1.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[0] = source_message_1.ByteSizeLong();

				test::protobuf_message_primitive_uint32 source_message_2;
				source_message_2.set_value(1);
				source_message_2.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[1] = source_message_2.ByteSizeLong();

				test::protobuf_message_primitive_sint64 source_message_3;
				source_message_3.set_value(1);
				source_message_3.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[2] = source_message_3.ByteSizeLong();

				test::protobuf_message_primitive_uint64 source_message_4;
				source_message_4.set_value(1);
				source_message_4.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[3] = source_message_4.ByteSizeLong();

				test::protobuf_message_primitive_float source_message_5;
				source_message_5.set_value(1);
				source_message_5.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[4] = source_message_5.ByteSizeLong();

				test::protobuf_message_primitive_double source_message_6;
				source_message_6.set_value(1);
				source_message_6.SerializeToArray(buf_array + pos_serialize, 4096 - pos_serialize);
				pos_serialize += size_serialize[5] = source_message_6.ByteSizeLong();
			}

			// 역직렬화
			{
				size_t pos_deserialize = 0;

				test::protobuf_message_primitive_sint32 message_1;
				message_1.ParseFromArray(buf_array + pos_deserialize, size_serialize[0]);
				pos_deserialize += size_serialize[0];
				[[maybe_unused]] auto value_1 = message_1.value();

				test::protobuf_message_primitive_sint64 message_2;
				message_2.ParseFromArray(buf_array + pos_deserialize, size_serialize[1]);
				pos_deserialize += size_serialize[1];
				[[maybe_unused]] auto value_2 = message_2.value();

				test::protobuf_message_primitive_sint64 message_3;
				message_3.ParseFromArray(buf_array + pos_deserialize, size_serialize[2]);
				pos_deserialize += size_serialize[2];
				[[maybe_unused]] auto value_3 = message_3.value();

				test::protobuf_message_primitive_uint64 message_4;
				message_4.ParseFromArray(buf_array + pos_deserialize, size_serialize[3]);
				pos_deserialize += size_serialize[3];
				[[maybe_unused]] auto value_4 = message_4.value();

				test::protobuf_message_primitive_float message_5;
				message_5.ParseFromArray(buf_array + pos_deserialize, size_serialize[4]);
				pos_deserialize += size_serialize[4];
				[[maybe_unused]] auto value_5 = message_5.value();

				test::protobuf_message_primitive_double message_6;
				message_6.ParseFromArray(buf_array + pos_deserialize, size_serialize[5]);
				pos_deserialize += size_serialize[5];
				[[maybe_unused]] auto value_6 = message_6.value();
			}
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_02_list_int)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_list_int source_message;

			for (auto& iter : array_int)
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

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_03_string)
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

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_04_list_string)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_list_string source_message;
			for(const auto& iter: array_string_char)
				source_message.add_value_1(iter);
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_list_string message;
			auto result = message.ParseFromArray(buf_array, size_serialize);
			EXPECT_TRUE(result);

			std::vector<std::string> list_result;
			for (const auto& iter : message.value_1())
				list_result.push_back(iter);
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_05_key_value_string_int)
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

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_06_struct_primitive)
	{
		char buf_array[4096];

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			test::protobuf_message_struct_primitive source_message;
			source_message.set_value_1(1);
			source_message.set_value_2(101);
			source_message.set_value_3(-12345);
			source_message.set_value_4(123456);
			source_message.set_value_5(1.0f);
			source_message.set_value_6(10.0);
			source_message.SerializeToArray(buf_array, 4096);
			auto size_serialize = source_message.ByteSizeLong();

			// 역직렬화
			test::protobuf_message_struct_primitive message;
			message.ParseFromArray(buf_array, size_serialize);
			FOO dest;
			[[maybe_unused]] auto v1 = message.value_1();
			[[maybe_unused]] auto v2 = message.value_2();
			[[maybe_unused]] auto v3 = message.value_3();
			[[maybe_unused]] auto v4 = message.value_4();
			[[maybe_unused]] auto v5 = message.value_5();
			[[maybe_unused]] auto v6 = message.value_6();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, pb_benchmark_07_struct_complex)
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
			test::protobuf_message_struct_complex source_message;
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
			test::protobuf_message_struct_complex message;
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