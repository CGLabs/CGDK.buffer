#pragma once

#define VALUE_00 12
#define VALUE_01 3
#define VALUE_02 4
#define VALUE_03 10
#define VALUE_04 22
#define VALUE_05 4100
#define VALUE_06 32210
#define VALUE_07 123310
#define VALUE_08 121234
#define VALUE_09 -1000443
#define VALUE_10 12233094310
#define VALUE_11 -5443
#define VALUE_12 65375	
#define VALUE_13 -12321321	
#define VALUE_14 12321321		
#define VALUE_15 1.0f
#define VALUE_16 2.0
extern size_t pos_general[];



extern int	array_int[8];
extern const char* array_string_char[8];
extern std::string_view array_string_std_string_view[8];
extern std::string array_string_std_string[8];
extern const wchar_t* array_string_wchar_t[8];
extern std::wstring_view array_string_std_wstring_view[8];
extern std::wstring array_string_std_wstring[8];
extern const char16_t* array_string_char16_t[8];
extern std::u16string_view array_string_std_u16string_view[8];
extern std::u16string array_string_std_u16string[8];
extern std::u32string_view array_string_char32_t[8];
extern std::u32string_view array_string_std_u32string_view[8];
extern std::u32string array_string_std_u32string[8];
extern std::vector<int> vector_int;
extern std::vector<std::string> std_vector_std_string;
extern std::vector<std::vector<int>> std_vector_vector_int;
extern std::list<int> std_list_int;
extern std::list<std::string> std_list_std_string;
extern std::list<std::vector<int>>	std_list_vector_int;
extern std::set<int> std_set_int;
extern std::set<std::string> std_set_std_string;
extern std::map<int, int> std_map_int_int;
extern std::map<std::string, int> std_map_std_string_int;
extern std::map<std::string, std::vector<int>>	std_map_std_string_std_vector_int;
extern std::map<std::string, std::vector<std::string_view>> std_map_std_vector_std_string_view;
extern std::unordered_map<int, int> std_unordered_map_int_int;
extern std::unordered_map<std::string, int> std_unordered_map_std_string_int;
extern std::unordered_map<std::string, std::vector<int>> std_unordered_map_std_string_std_vector_int;
extern std::unordered_map<std::string, std::vector<std::string_view>> std_unordered_map_std_vector_std_string_view;

template<class S, class T, std::size_t N>
void function_string_append(S& _buf_dest, const T(&_source)[N])
{
	// 1) append string
	for (std::size_t i = 0; i < N; ++i)
	{
		_buf_dest.template append<T>(_source[i]);
	}

	// check)
	EXPECT_TRUE(_buf_dest.size() == CGDK::get_size_of(_source) - sizeof(COUNT_T));
}
template<class S, class T, std::size_t N>
void function_string_extract(S& _buffer, const T(&_source)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		// - front value
		auto str_value = _buffer.template extract<T>();

		// - get size
		auto bytes_a = CGDK::get_size_of(str_value);
		auto bytes_b = CGDK::get_size_of(_source[i]);

		// check)
		EXPECT_TRUE(bytes_a == bytes_b);
		EXPECT_TRUE(str_value == _source[i]);
	}

	EXPECT_TRUE(_buffer.size() == 0);
}
template<class S, class T, std::size_t N>
void function_string_front(S& _buffer, const T(&_source)[N])
{
	// declare)
	CGDK::POS temp_pos;

	for (std::size_t i = 0; i < N; ++i)
	{
		// - front value
		auto str_value = _buffer.template front<T>(temp_pos);

		// - get size
		auto bytes_a = CGDK::get_size_of(str_value);
		auto bytes_b = CGDK::get_size_of(_source[i]);

		// check)
		EXPECT_TRUE(bytes_a == bytes_b);
		EXPECT_TRUE(str_value == _source[i]);
	}

	EXPECT_TRUE(static_cast<int64_t>(_buffer.size()) == temp_pos.offset);
}

template<class T, std::size_t N1, std::size_t N2>
bool compare_array_string(const std::array<std::basic_string_view<T>, N1>& _lhs, const T* (&_rhs)[N2])
{
	// check)
	if constexpr (N1 != N2)
		return false;

	for (std::size_t i = 0; i < N1; ++i)
	{
		if (_lhs[i] != _rhs[i])
		{
			return false;
		}
	}

	return true;
}

template <class T>
inline bool compare_map_std_vector_string(const std::map<std::string, std::vector<std::basic_string_view<T>>>& _lhs, const std::map<std::string, std::vector<std::basic_string_view<T>>>& _rhs)
{
	auto iterX = _lhs.begin();
	auto iterXEnd = _lhs.end();
	auto iterY = _rhs.begin();

	for (; iterX != iterXEnd; ++iterX, ++iterY)
	{
		auto iterA = iterX->second.begin();
		auto iterAEnd = iterX->second.end();
		auto iterB = iterY->second.begin();

		for (; iterA != iterAEnd; ++iterA, ++iterB)
		{
			if (*iterA != *iterB)
			{
				return false;
			}
		}

		if (iterB != iterY->second.end())
			return false;
	}

	return iterY == _rhs.end();
}

template <class T>
void function_append_general(T& _buffer)
{
	_buffer.template append<char>				(VALUE_00);
	_buffer.template append<unsigned char>		(VALUE_01);
	_buffer.template append<wchar_t>			(VALUE_02);
	_buffer.template append<char16_t>			(VALUE_03);
	_buffer.template append<char32_t>			(VALUE_04);
	_buffer.template append<int16_t>			(VALUE_05);
	_buffer.template append<uint16_t>			(VALUE_06);
	_buffer.template append<int32_t>			(VALUE_07);
	_buffer.template append<uint32_t>			(VALUE_08);
	_buffer.template append<int64_t>			(VALUE_09);
	_buffer.template append<uint64_t>			(VALUE_10);
	_buffer.template append<long>				(VALUE_11);
	_buffer.template append<unsigned long>		(VALUE_12);
	_buffer.template append<long long>			(VALUE_13);
	_buffer.template append<unsigned long long>	(VALUE_14);
	_buffer.template append<float>				(VALUE_15);
	_buffer.template append<double>				(VALUE_16);
}

template <class T>
void function_extract_GENERAL(T _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_general[16]);

	auto size = _buffer.size();

	auto& value0  = _buffer.template extract<char&>();
	size -= sizeof(char);
	EXPECT_TRUE(value0 == VALUE_00);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value1  = _buffer.template extract<unsigned char&>();
	size -= sizeof(unsigned char);
	EXPECT_TRUE(value1 == VALUE_01);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value2  = _buffer.template extract<wchar_t&>();
	size -= sizeof(wchar_t);
	EXPECT_TRUE(value2 == VALUE_02);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value3  = _buffer.template extract<char16_t&>();
	size -= sizeof(char16_t);
	EXPECT_TRUE(value3 == VALUE_03);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value4  = _buffer.template extract<char32_t&>();
	size -= sizeof(char32_t);
	EXPECT_TRUE(value4 == VALUE_04);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value5  = _buffer.template extract<int16_t&>();
	size -= sizeof(int16_t);
	EXPECT_TRUE(value5 == VALUE_05);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value6  = _buffer.template extract<uint16_t&>();
	size -= sizeof(uint16_t);
	EXPECT_TRUE(value6 == VALUE_06);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value7  = _buffer.template extract<int32_t&>();
	size -= sizeof(int32_t);
	EXPECT_TRUE(value7 == VALUE_07);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value8  = _buffer.template extract<uint32_t&>();
	size -= sizeof(uint32_t);
	EXPECT_TRUE(value8 == VALUE_08);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value09 = _buffer.template extract<int64_t&>();
	size -= sizeof(int64_t);
	EXPECT_TRUE(value09 == VALUE_09);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value10 = _buffer.template extract<uint64_t&>();
	size -= sizeof(uint64_t);
	EXPECT_TRUE(value10 == VALUE_10);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value11 = _buffer.template extract<long&>();
	size -= sizeof(long);
	EXPECT_TRUE(value11 == VALUE_11);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value12 = _buffer.template extract<unsigned long&>();
	size -= sizeof(unsigned long);
	EXPECT_TRUE(value12 == VALUE_12);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value13 = _buffer.template extract<long long&>();
	size -= sizeof(long long);
	EXPECT_TRUE(value13 == VALUE_13);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value14 = _buffer.template extract<unsigned long long&>();
	size -= sizeof(unsigned long long);
	EXPECT_TRUE(value14 == VALUE_14);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value15 = _buffer.template extract<float&>();
	size -= sizeof(float);
	EXPECT_TRUE(value15 == VALUE_15);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value16 = _buffer.template extract<double&>();
	size -= sizeof(double);
	EXPECT_TRUE(value16 == VALUE_16);
	EXPECT_TRUE(_buffer.size() == size);
}

template <class T>
void function_front_GENERAL(T _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_general[16]);

	size_t pos_now = 0;

	auto& value00  = _buffer.template front<char&>(pos_now);		pos_now += sizeof(char);
	EXPECT_TRUE(pos_now == pos_general[0]);
	EXPECT_TRUE(value00 == VALUE_00);

	auto& value01  = _buffer.template front<unsigned char&>(pos_now);pos_now += sizeof(unsigned char);
	EXPECT_TRUE(pos_now == pos_general[1]);
	EXPECT_TRUE(value01 == VALUE_01);

	auto& value02  = _buffer.template front<wchar_t&>(pos_now);		pos_now += sizeof(wchar_t);
	EXPECT_TRUE(pos_now == pos_general[2]);
	EXPECT_TRUE(value02 == VALUE_02);

	auto& value03  = _buffer.template front<char16_t&>(pos_now);	pos_now += sizeof(char16_t);
	EXPECT_TRUE(pos_now == pos_general[3]);
	EXPECT_TRUE(value03 == VALUE_03);

	auto& value04  = _buffer.template front<char32_t&>(pos_now);	pos_now += sizeof(char32_t);
	EXPECT_TRUE(pos_now == pos_general[4]);
	EXPECT_TRUE(value04 == VALUE_04);

	auto& value05  = _buffer.template front<int16_t&>(pos_now);		pos_now += sizeof(int16_t);
	EXPECT_TRUE(pos_now == pos_general[5]);
	EXPECT_TRUE(value05 == VALUE_05);

	auto& value06  = _buffer.template front<uint16_t&>(pos_now);	pos_now += sizeof(uint16_t);
	EXPECT_TRUE(value06 == VALUE_06);

	auto& value07  = _buffer.template front<int32_t&>(pos_now);		pos_now += sizeof(int32_t);
	EXPECT_TRUE(value07 == VALUE_07);

	auto& value08  = _buffer.template front<uint32_t&>(pos_now);	pos_now += sizeof(uint32_t);
	EXPECT_TRUE(value08 == VALUE_08);

	auto& value09 = _buffer.template front<int64_t&>(pos_now);		pos_now += sizeof(int64_t);
	EXPECT_TRUE(value09 == VALUE_09);

	auto& value10 = _buffer.template front<uint64_t&>(pos_now);		pos_now += sizeof(uint64_t);
	EXPECT_TRUE(value10 == VALUE_10);

	auto& value11  = _buffer.template front<int32_t&>(pos_now);		pos_now += sizeof(long);
	EXPECT_TRUE(value11 == VALUE_11);

	auto& value12  = _buffer.template front<uint32_t&>(pos_now);	pos_now += sizeof(unsigned long);
	EXPECT_TRUE(value12 == VALUE_12);

	auto& value13 = _buffer.template front<int64_t&>(pos_now);		pos_now += sizeof(long long);
	EXPECT_TRUE(value13 == VALUE_13);

	auto& value14 = _buffer.template front<uint64_t&>(pos_now);		pos_now += sizeof(unsigned long long);
	EXPECT_TRUE(value14 == VALUE_14);

	auto& value15 = _buffer.template front<float&>(pos_now);		pos_now += sizeof(float);
	EXPECT_TRUE(value15 == VALUE_15);

	auto& value16 = _buffer.template front<double&>(pos_now);		pos_now += sizeof(double);
	EXPECT_TRUE(value16 == VALUE_16);

	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_general[16]);
}

template <class T>
void function_front_with_pos_general(T _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_general[16]);

	CGDK::POS pos_now;

	auto& value00  = _buffer.template front<char&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[0]));
	EXPECT_TRUE(value00 == VALUE_00);

	auto& value01  = _buffer.template front<unsigned char&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[1]));
	EXPECT_TRUE(value01 == VALUE_01);

	auto& value02  = _buffer.template front<wchar_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[2]));
	EXPECT_TRUE(value02 == VALUE_02);

	auto& value03  = _buffer.template front<char16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[3]));
	EXPECT_TRUE(value03 == VALUE_03);

	auto& value04  = _buffer.template front<char32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[4]));
	EXPECT_TRUE(value04 == VALUE_04);

	auto& value05  = _buffer.template front<int16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[5]));
	EXPECT_TRUE(value05 == VALUE_05);

	auto& value06  = _buffer.template front<uint16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[6]));
	EXPECT_TRUE(value06 == VALUE_06);

	auto& value07  = _buffer.template front<int32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[7]));
	EXPECT_TRUE(value07 == VALUE_07);

	auto& value08  = _buffer.template front<uint32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[8]));
	EXPECT_TRUE(value08 == VALUE_08);

	auto& value09 = _buffer.template front<int64_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[9]));
	EXPECT_TRUE(value09 == VALUE_09);

	auto& value10 = _buffer.template front<uint64_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[10]));
	EXPECT_TRUE(value10 == VALUE_10);

	auto& value11 = _buffer.template front<long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[11]));
	EXPECT_TRUE(value11 == VALUE_11);

	auto& value12 = _buffer.template front<unsigned long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[12]));
	EXPECT_TRUE(value12 == VALUE_12);

	auto& value13 = _buffer.template front<long long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[13]));
	EXPECT_TRUE(value13 == VALUE_13);

	auto& value14 = _buffer.template front<unsigned long long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[14]));
	EXPECT_TRUE(value14 == VALUE_14);

	auto& value15 = _buffer.template front<float&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[15]));
	EXPECT_TRUE(value15 == VALUE_15);

	auto& value16 = _buffer.template front<double&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_general[16]));
	EXPECT_TRUE(value16 == VALUE_16);

	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_general[16]);
}
