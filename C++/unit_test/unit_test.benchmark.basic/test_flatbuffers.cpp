#include "pch.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/messages_test_1_generated.h"
#include "flatbuffers/messages_test_2_generated.h"
#include "flatbuffers/messages_test_3_generated.h"
#include "flatbuffers/messages_test_4_generated.h"
#include "flatbuffers/messages_test_5_generated.h"


namespace flatbuffers
{
	TEST(CGDK_buffer_benchmakr_basic, fb_append_extract_primitive)
	{
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 직렬화
			flatbuffers::FlatBufferBuilder builder;

			// 직렬화 된 버퍼를 가져온다. 직렬화된 곧바로 네트워크로 보내거나, 저장할 수 있다.
			int32_t value_1{ 1 };
			uint32_t value_2{ 101 };
			int64_t value_3{ -12345 };
			uint64_t value_4{ 123456 };
			float value_5{ 1.0f };
			double value_6{ 10.0 };
			builder.Finish(Createflatbufers_message_GENERAL(builder, value_1, value_2, value_3, value_4, value_5, value_6)); // 직렬화 되었다!

			const uint8_t* data = builder.GetBufferPointer();

			// 역직렬화
			auto deserialized = Getflatbufers_message_GENERAL(data);
			[[maybe_unused]] auto de_value_1 = deserialized->value_1();
			[[maybe_unused]] auto de_value_2 = deserialized->value_2();
			[[maybe_unused]] auto de_value_3 = deserialized->value_3();
			[[maybe_unused]] auto de_value_4 = deserialized->value_4();
			[[maybe_unused]] auto de_value_5 = deserialized->value_5();
			[[maybe_unused]] auto de_value_6 = deserialized->value_6();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, fb_append_extract_string)
	{
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 1) builder
			flatbuffers::FlatBufferBuilder builder;

			// 2) 직렬화
			auto value_1 = builder.CreateString(array_string_char[0]);
			auto value_2 = builder.CreateString(array_string_char[1]);
			auto value_3 = builder.CreateString(array_string_char[2]);
			auto value_4 = builder.CreateString(array_string_char[3]);
			auto value_5 = builder.CreateString(array_string_char[4]);
			auto value_6 = builder.CreateString(array_string_char[5]);
			auto value_7 = builder.CreateString(array_string_char[6]);
			auto value_8 = builder.CreateString(array_string_char[7]);
			builder.Finish(Createflatbuffers_message_string(builder, value_1, value_2, value_3, value_4, value_5, value_6,value_7,value_8));

			const uint8_t* data = builder.GetBufferPointer();

			// 3) 역직렬화 
			auto deserialized = Getflatbuffers_message_string(data);
			[[maybe_unused]] std::string_view de_value_1 = deserialized->value_1()->string_view();
			[[maybe_unused]] std::string_view de_value_2 = deserialized->value_2()->string_view();
			[[maybe_unused]] std::string_view de_value_3 = deserialized->value_3()->string_view();
			[[maybe_unused]] std::string_view de_value_4 = deserialized->value_4()->string_view();
			[[maybe_unused]] std::string_view de_value_5 = deserialized->value_5()->string_view();
			[[maybe_unused]] std::string_view de_value_6 = deserialized->value_6()->string_view();
			[[maybe_unused]] std::string_view de_value_7 = deserialized->value_7()->string_view();
			[[maybe_unused]] std::string_view de_value_8 = deserialized->value_8()->string_view();
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, fb_append_extract_std_list_int)
	{
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 1) builder
			flatbuffers::FlatBufferBuilder builder;

			// 2) 직렬화
			std::vector<int32_t> temp_vector;
			for(auto iter:array_int) temp_vector.push_back(iter);
			auto temp_pos_list = builder.CreateVector(temp_vector);
			builder.Finish(Createmessage_list_int(builder, temp_pos_list));

			const uint8_t* data = builder.GetBufferPointer();

			// 3) 역직렬화 
			auto deserialized = Getmessage_list_int(data);
			[[maybe_unused]] std::vector<int32_t> de_value_1;
			de_value_1.reserve(deserialized->a()->size());
			for(auto iter: *deserialized->a()) de_value_1.push_back(iter);
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, fb_append_extract_std_map_std_string_int)
	{
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 1) builder
			flatbuffers::FlatBufferBuilder builder;

			// 2) 직렬화
			std::vector<::flatbuffers::Offset<map_node_string_int>> vector_map_node_string_int;
			for (auto& iter : std_map_std_string_int)
			{
				vector_map_node_string_int.push_back(Createmap_node_string_int(builder, builder.CreateString(iter.first), iter.second));
			}
			auto temp_pos_list = builder.CreateVector(vector_map_node_string_int);
			builder.Finish(Createmessage_map_std_string_int(builder, temp_pos_list));

			const uint8_t* data = builder.GetBufferPointer();

			// 3) 역직렬화 
			auto deserialized = Getmessage_map_std_string_int(data);
			[[maybe_unused]] std::map<std::string, int32_t> de_value_1;
			for (auto iter : *deserialized->a()) de_value_1.insert({ iter->key()->c_str(),iter->value()});
		}
	}

	TEST(CGDK_buffer_benchmakr_basic, fb_append_extract_struct)
	{
		FOO foo;
		foo.v1 = 100;
		foo.v2 = std::string("test_string");
		foo.v3 = std::list<int>{ 1,2,3,4,5 };
		foo.v4 = 10000;
		foo.v5 = std::map<std::string, int>{ {"a", 1}, {"b", 2}, {"c", 3} };

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// 1) builder
			flatbuffers::FlatBufferBuilder builder;

			// 2) 직렬화
			auto temp_pos_v2 = builder.CreateString(foo.v2);
			std::vector<int> vector_v3; 
			for (auto iter : foo.v3) vector_v3.push_back(iter);
			auto temp_pos_v3 = builder.CreateVector(vector_v3);
			std::vector<::flatbuffers::Offset<map_data>> vector_map_data;
			for (auto& iter : foo.v5)
			{
				vector_map_data.push_back(Createmap_data(builder, builder.CreateString(iter.first), iter.second));
			}
			auto temp_pos_v5 = builder.CreateVector(vector_map_data);
			builder.Finish(Createmessage_message_struct(builder, foo.v1, temp_pos_v2, temp_pos_v3, foo.v4, temp_pos_v5));

			const uint8_t* data = builder.GetBufferPointer();

			// 3) 역직렬화 
			auto deserialized = Getmessage_message_struct(data);
			[[maybe_unused]] FOO dest;
			dest.v1 = deserialized->v1();
			dest.v2 = deserialized->v2()->c_str();
			for (auto iter : *deserialized->v3()) dest.v3.push_back(iter);
			dest.v4 = deserialized->v4();
			for (auto iter : *deserialized->v5()) dest.v5.insert({iter->key()->c_str(), iter->value()});
		}
	}
}
