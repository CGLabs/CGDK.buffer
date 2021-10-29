#include "pch.h"

// definitions) 
#define	_TEST_COUNT	1

#if defined(_MSC_VER)
	#pragma warning(disable:4566)
#endif

// declare) Test String
int	array_int[8] =
{
	3,
	2,
	9,
	10,
	11,
	22,
	44,
	22
};

// declare) Test String
const char* array_string_char[8] =
{
	"Please Let test this",
	"이것 좀 테스트하게 해주세요.",
	"这件事 试验",
	"これを試ためさせてください",
	"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	"Please 这件事 試ためさせてください 합시다.",
	"Test What ever",
	"1234"
};
std::string_view array_string_std_string_view[8] =
{
	"Please Let test this",
	"이것 좀 테스트하게 해주세요.",
	"这件事 试验",
	"これを試ためさせてください",
	"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	"Please 这件事 試ためさせてください 합시다.",
	"Test What ever",
	"1234"
};
std::string array_string_std_string[8] =
{
	"Please Let test this",
	"이것 좀 테스트하게 해주세요.",
	"这件事 试验",
	"これを試ためさせてください",
	"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	"Please 这件事 試ためさせてください 합시다.",
	"Test What ever",
	"1234"
};


// declare) Test String
const wchar_t* array_string_wchar_t[8] =
{
	L"Please Let test this",
	L"이것 좀 테스트하게 해주세요.",
	L"这件事 试验",
	L"これを試ためさせてください",
	L"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	L"Please 这件事 試ためさせてください 합시다.",
	L"Test What ever",
	L"1234"
};
std::wstring_view array_string_std_wstring_view[8] =
{
	L"Please Let test this",
	L"이것 좀 테스트하게 해주세요.",
	L"这件事 试验",
	L"これを試ためさせてください",
	L"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	L"Please 这件事 試ためさせてください 합시다.",
	L"Test What ever",
	L"1234"
};
std::wstring array_string_std_wstring[8] =
{
	L"Please Let test this",
	L"이것 좀 테스트하게 해주세요.",
	L"这件事 试验",
	L"これを試ためさせてください",
	L"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	L"Please 这件事 試ためさせてください 합시다.",
	L"Test What ever",
	L"1234"
};


const char16_t* array_string_char16_t[8] =
{
	u"Please Let test this",
	u"이것 좀 테스트하게 해주세요.",
	u"这件事 试验",
	u"これを試ためさせてください",
	u"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	u"Please 这件事 試ためさせてください 합시다.",
	u"Test What ever",
	u"1234"
};
std::u16string_view array_string_std_u16string_view[8] =
{
	u"Please Let test this",
	u"이것 좀 테스트하게 해주세요.",
	u"这件事 试验",
	u"これを試ためさせてください",
	u"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	u"Please 这件事 試ためさせてください 합시다.",
	u"Test What ever",
	u"1234"
};
std::u16string array_string_std_u16string[8] =
{
	u"Please Let test this",
	u"이것 좀 테스트하게 해주세요.",
	u"这件事 试验",
	u"これを試ためさせてください",
	u"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	u"Please 这件事 試ためさせてください 합시다.",
	u"Test What ever",
	u"1234"
};


std::u32string_view array_string_char32_t[8] =
{
	U"Please Let test this",
	U"이것 좀 테스트하게 해주세요.",
	U"这件事 试验",
	U"これを試ためさせてください",
	U"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	U"Please 这件事 試ためさせてください 합시다.",
	U"Test What ever",
	U"1234"
};
std::u32string_view array_string_std_u32string_view[8] =
{
	U"Please Let test this",
	U"이것 좀 테스트하게 해주세요.",
	U"这件事 试验",
	U"これを試ためさせてください",
	U"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	U"Please 这件事 試ためさせてください 합시다.",
	U"Test What ever",
	U"1234"
};
std::u32string array_string_std_u32string[8] =
{
	U"Please Let test this",
	U"이것 좀 테스트하게 해주세요.",
	U"这件事 试验",
	U"これを試ためさせてください",
	U"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	U"Please 这件事 試ためさせてください 합시다.",
	U"Test What ever",
	U"1234"
};

// Declare ) vector<ing>
std::vector<int>	vector_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) vector<string>
std::vector<std::string>	std_vector_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) vector<string>
std::vector<std::vector<int>>	std_vector_vector_int
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};

// Declare ) list<ing>
std::list<int>	std_list_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) list<string>
std::list<std::string>	std_list_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) list<string>
std::list<std::vector<int>>	std_list_vector_int
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};


// Declare ) set<ing>
std::set<int>	std_set_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) set<string>
std::set<std::string>	std_set_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) map<string, ing>
std::map<int, int>	std_map_int_int
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) map<string, ing>
std::map<std::string, int>	std_map_std_string_int
{
	{"zero",	0},
	{"two",		2},
	{"tree",	3},
	{"fifteen",	14},
	{"five",	5},
	{"eleven",	11}
};

// Declare ) map<string, ing>
std::map<std::string, std::vector<int>>	std_map_std_string_std_vector_int
{
	{"zero",	{0,1,2,4}},
	{"two",		{3,1,22,4}},
	{"tree",	{4,1,12,4}},
	{"fifteen",	{5,1,82,4}},
	{"five",	{7,1,22,4}},
	{"eleven",	{10,21,12,34}}
};

// Declare ) map<string, ing>
std::map<std::string, std::vector<std::string_view>>	std_map_std_vector_std_string_view
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<int, int>	std_unordered_map_int_int
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, int>	std_unordered_map_std_string_int
{
	{"zero",	0},
	{"two",		2},
	{"tree",	3},
	{"fifteen",	14},
	{"five",	5},
	{"eleven",	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<int>>	std_unordered_map_std_string_std_vector_int
{
	{"zero",	{0,1,2,4}},
	{"two",		{3,1,22,4}},
	{"tree",	{4,1,12,4}},
	{"fifteen",	{5,1,82,4}},
	{"five",	{7,1,22,4}},
	{"eleven",	{10,21,12,34}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<std::string_view>>	std_unordered_map_std_vector_std_string_view
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};

template<class T, std::size_t N>
CGDK::shared_buffer function_string_append(const T(&_source)[N])
{
	// 1) alloc shared_buffer
	auto buf_temp = alloc_shared_buffer(2048);

	// 2) append string
	for (std::size_t i = 0; i < N; ++i)
	{
		buf_temp.append<T>(_source[i]);
	}

	// check)
	EXPECT_TRUE(buf_temp.size() == CGDK::get_size_of(_source) - sizeof(COUNT_T));

	// Return) 
	return buf_temp;
}
template<class T, std::size_t N>
void function_string_extract(CGDK::buffer_view& _buffer, const T(&_source)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		// - front value
		auto str_value = _buffer.extract<T>();

		// - get size
		auto bytes_a = CGDK::get_size_of(str_value);
		auto bytes_b = CGDK::get_size_of(_source[i]);

		// check)
		EXPECT_TRUE(bytes_a == bytes_b);
		EXPECT_TRUE(str_value == _source[i]);
	}

	EXPECT_TRUE(_buffer.size() == 0);
}
template<class T, std::size_t N>
void function_string_front(CGDK::buffer_view& _buffer, const T(&_source)[N])
{
	// declare)
	CGDK::POS temp_pos;

	for (std::size_t i = 0; i < N; ++i)
	{
		// - front value
		auto str_value = _buffer.front<T>(temp_pos);

		// - get size
		auto bytes_a = CGDK::get_size_of(str_value);
		auto bytes_b = CGDK::get_size_of(_source[i]);

		// check)
		EXPECT_TRUE(bytes_a == bytes_b);
		EXPECT_TRUE(str_value == _source[i]);
	}

	EXPECT_TRUE(static_cast<int64_t>(_buffer.size()) == temp_pos.offset);
}

template <class T>
void test_extract_string(const T& _source)
{
	// 1) append string
	auto temp = function_string_append(_source);

	for (int i = 0; i < _TEST_COUNT; ++i)
	{
		// 2) copy shared_buffer
		CGDK::buffer_view buf_read = temp;

		// 3) extract
		function_string_extract(buf_read, _source);

		// check) 
		EXPECT_TRUE(buf_read.size() == 0);
	}
}
template <class T>
void test_front_string(const T& _source)
{
	// 1) append string
	auto temp = function_string_append(_source);

	for (int i = 0; i < _TEST_COUNT; ++i)
	{
		// 2) copy shared_buffer
		CGDK::buffer_view buf_read = temp;

		// 3) extract
		function_string_front(buf_read, _source);

		// check) 
		EXPECT_TRUE(buf_read.size() == temp.size());
	}
}

#define VALUE_00		12
#define VALUE_01		3
#define VALUE_02		4
#define VALUE_03		10
#define VALUE_04		22
#define VALUE_05		4100
#define VALUE_06		32210
#define VALUE_07		123310
#define VALUE_08		121234
#define VALUE_09		-1000443
#define VALUE_10		12233094310
#define VALUE_11		-5443
#define VALUE_12		65375	
#define VALUE_13		-12321321	
#define VALUE_14		12321321		
#define VALUE_15		1.0f
#define VALUE_16		2.0

size_t pos_GENERAL[] {
/*00*/	sizeof(char),
/*01*/	sizeof(char) + sizeof(unsigned char),
/*02*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t),
/*03*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t),
/*04*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t),
/*05*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t),
/*06*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t),
/*07*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t),
/*08*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t),
/*09*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t),
/*10*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t),
/*11*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long),
/*12*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long) + sizeof(unsigned long),
/*13*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long) + sizeof(unsigned long) + sizeof(long long),
/*14*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long) + sizeof(unsigned long) + sizeof(long long) + sizeof(unsigned long long),
/*15*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long) + sizeof(unsigned long) + sizeof(long long) + sizeof(unsigned long long) + sizeof(float),
/*16*/	sizeof(char) + sizeof(unsigned char) + sizeof(wchar_t) + sizeof(char16_t) + sizeof(char32_t) + sizeof(int16_t) + sizeof(uint16_t) + sizeof(int32_t) + sizeof(uint32_t) + sizeof(int64_t) + sizeof(uint64_t) + sizeof(long) + sizeof(unsigned long) + sizeof(long long) + sizeof(unsigned long long) + sizeof(float) + sizeof(double)
};

void function_append_GENERAL(CGDK::shared_buffer& _buffer)
{
	_buffer.append<char>				(VALUE_00);
	_buffer.append<unsigned char>		(VALUE_01);
	_buffer.append<wchar_t>				(VALUE_02);
	_buffer.append<char16_t>			(VALUE_03);
	_buffer.append<char32_t>			(VALUE_04);
	_buffer.append<int16_t>				(VALUE_05);
	_buffer.append<uint16_t>			(VALUE_06);
	_buffer.append<int32_t>				(VALUE_07);
	_buffer.append<uint32_t>			(VALUE_08);
	_buffer.append<int64_t>				(VALUE_09);
	_buffer.append<uint64_t>			(VALUE_10);
	_buffer.append<long>				(VALUE_11);
	_buffer.append<unsigned long>		(VALUE_12);
	_buffer.append<long long>			(VALUE_13);
	_buffer.append<unsigned long long>	(VALUE_14);
	_buffer.append<float>				(VALUE_15);
	_buffer.append<double>				(VALUE_16);
}

void function_extract_GENERAL(CGDK::buffer_view _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_GENERAL[16]);

	auto size = _buffer.size();

	auto& value0  = _buffer.extract<char&>();
	size -= sizeof(char);
	EXPECT_TRUE(value0 == VALUE_00);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value1  = _buffer.extract<unsigned char&>();
	size -= sizeof(unsigned char);
	EXPECT_TRUE(value1 == VALUE_01);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value2  = _buffer.extract<wchar_t&>();
	size -= sizeof(wchar_t);
	EXPECT_TRUE(value2 == VALUE_02);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value3  = _buffer.extract<char16_t&>();
	size -= sizeof(char16_t);
	EXPECT_TRUE(value3 == VALUE_03);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value4  = _buffer.extract<char32_t&>();
	size -= sizeof(char32_t);
	EXPECT_TRUE(value4 == VALUE_04);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value5  = _buffer.extract<int16_t&>();
	size -= sizeof(int16_t);
	EXPECT_TRUE(value5 == VALUE_05);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value6  = _buffer.extract<uint16_t&>();
	size -= sizeof(uint16_t);
	EXPECT_TRUE(value6 == VALUE_06);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value7  = _buffer.extract<int32_t&>();
	size -= sizeof(int32_t);
	EXPECT_TRUE(value7 == VALUE_07);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value8  = _buffer.extract<uint32_t&>();
	size -= sizeof(uint32_t);
	EXPECT_TRUE(value8 == VALUE_08);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value09 = _buffer.extract<int64_t&>();
	size -= sizeof(int64_t);
	EXPECT_TRUE(value09 == VALUE_09);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value10 = _buffer.extract<uint64_t&>();
	size -= sizeof(uint64_t);
	EXPECT_TRUE(value10 == VALUE_10);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value11 = _buffer.extract<long&>();
	size -= sizeof(long);
	EXPECT_TRUE(value11 == VALUE_11);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value12 = _buffer.extract<unsigned long&>();
	size -= sizeof(unsigned long);
	EXPECT_TRUE(value12 == VALUE_12);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value13 = _buffer.extract<long long&>();
	size -= sizeof(long long);
	EXPECT_TRUE(value13 == VALUE_13);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value14 = _buffer.extract<unsigned long long&>();
	size -= sizeof(unsigned long long);
	EXPECT_TRUE(value14 == VALUE_14);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value15 = _buffer.extract<float&>();
	size -= sizeof(float);
	EXPECT_TRUE(value15 == VALUE_15);
	EXPECT_TRUE(_buffer.size() == size);

	auto& value16 = _buffer.extract<double&>();
	size -= sizeof(double);
	EXPECT_TRUE(value16 == VALUE_16);
	EXPECT_TRUE(_buffer.size() == size);
}

void function_front_GENERAL(CGDK::buffer_view _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_GENERAL[16]);

	size_t pos_now = 0;

	auto& value00  = _buffer.front<char&>(pos_now);			pos_now+=sizeof(char);
	EXPECT_TRUE(pos_now == pos_GENERAL[0]);
	EXPECT_TRUE(value00 == VALUE_00);

	auto& value01  = _buffer.front<unsigned char&>(pos_now);pos_now+=sizeof(unsigned char);
	EXPECT_TRUE(pos_now == pos_GENERAL[1]);
	EXPECT_TRUE(value01 == VALUE_01);

	auto& value02  = _buffer.front<wchar_t&>(pos_now);		pos_now+=sizeof(wchar_t);
	EXPECT_TRUE(pos_now == pos_GENERAL[2]);
	EXPECT_TRUE(value02 == VALUE_02);

	auto& value03  = _buffer.front<char16_t&>(pos_now);		pos_now+=sizeof(char16_t);
	EXPECT_TRUE(pos_now == pos_GENERAL[3]);
	EXPECT_TRUE(value03 == VALUE_03);

	auto& value04  = _buffer.front<char32_t&>(pos_now);		pos_now+=sizeof(char32_t);
	EXPECT_TRUE(pos_now == pos_GENERAL[4]);
	EXPECT_TRUE(value04 == VALUE_04);

	auto& value05  = _buffer.front<int16_t&>(pos_now);		pos_now+=sizeof(int16_t);
	EXPECT_TRUE(pos_now == pos_GENERAL[5]);
	EXPECT_TRUE(value05 == VALUE_05);

	auto& value06  = _buffer.front<uint16_t&>(pos_now);		pos_now+=sizeof(uint16_t);
	EXPECT_TRUE(value06 == VALUE_06);

	auto& value07  = _buffer.front<int32_t&>(pos_now);		pos_now+=sizeof(int32_t);
	EXPECT_TRUE(value07 == VALUE_07);

	auto& value08  = _buffer.front<uint32_t&>(pos_now);		pos_now+=sizeof(uint32_t);
	EXPECT_TRUE(value08 == VALUE_08);

	auto& value09 = _buffer.front<int64_t&>(pos_now);		pos_now+=sizeof(int64_t);
	EXPECT_TRUE(value09 == VALUE_09);

	auto& value10 = _buffer.front<uint64_t&>(pos_now);		pos_now+=sizeof(uint64_t);
	EXPECT_TRUE(value10 == VALUE_10);

	auto& value11  = _buffer.front<int32_t&>(pos_now);		pos_now+=sizeof(long);
	EXPECT_TRUE(value11 == VALUE_11);

	auto& value12  = _buffer.front<uint32_t&>(pos_now);		pos_now+=sizeof(unsigned long);
	EXPECT_TRUE(value12 == VALUE_12);

	auto& value13 = _buffer.front<int64_t&>(pos_now);		pos_now+=sizeof(long long);
	EXPECT_TRUE(value13 == VALUE_13);

	auto& value14 = _buffer.front<uint64_t&>(pos_now);		pos_now+=sizeof(unsigned long long);
	EXPECT_TRUE(value14 == VALUE_14);

	auto& value15 = _buffer.front<float&>(pos_now);			pos_now+=sizeof(float);
	EXPECT_TRUE(value15 == VALUE_15);

	auto& value16 = _buffer.front<double&>(pos_now);		pos_now+=sizeof(double);
	EXPECT_TRUE(value16 == VALUE_16);

	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_GENERAL[16]);
}

void function_front_with_pos_GENERAL(CGDK::buffer_view _buffer)
{
	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_GENERAL[16]);

	CGDK::POS pos_now;

	auto& value00  = _buffer.front<char&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[0]));
	EXPECT_TRUE(value00 == VALUE_00);

	auto& value01  = _buffer.front<unsigned char&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[1]));
	EXPECT_TRUE(value01 == VALUE_01);

	auto& value02  = _buffer.front<wchar_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[2]));
	EXPECT_TRUE(value02 == VALUE_02);

	auto& value03  = _buffer.front<char16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[3]));
	EXPECT_TRUE(value03 == VALUE_03);

	auto& value04  = _buffer.front<char32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[4]));
	EXPECT_TRUE(value04 == VALUE_04);

	auto& value05  = _buffer.front<int16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[5]));
	EXPECT_TRUE(value05 == VALUE_05);

	auto& value06  = _buffer.front<uint16_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[6]));
	EXPECT_TRUE(value06 == VALUE_06);

	auto& value07  = _buffer.front<int32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[7]));
	EXPECT_TRUE(value07 == VALUE_07);

	auto& value08  = _buffer.front<uint32_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[8]));
	EXPECT_TRUE(value08 == VALUE_08);

	auto& value09 = _buffer.front<int64_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[9]));
	EXPECT_TRUE(value09 == VALUE_09);

	auto& value10 = _buffer.front<uint64_t&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[10]));
	EXPECT_TRUE(value10 == VALUE_10);

	auto& value11 = _buffer.front<long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[11]));
	EXPECT_TRUE(value11 == VALUE_11);

	auto& value12 = _buffer.front<unsigned long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[12]));
	EXPECT_TRUE(value12 == VALUE_12);

	auto& value13 = _buffer.front<long long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[13]));
	EXPECT_TRUE(value13 == VALUE_13);

	auto& value14 = _buffer.front<unsigned long long&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[14]));
	EXPECT_TRUE(value14 == VALUE_14);

	auto& value15 = _buffer.front<float&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[15]));
	EXPECT_TRUE(value15 == VALUE_15);

	auto& value16 = _buffer.front<double&>(pos_now);
	EXPECT_TRUE(pos_now.offset == static_cast<int64_t>(pos_GENERAL[16]));
	EXPECT_TRUE(value16 == VALUE_16);

	EXPECT_TRUE(static_cast<size_t>(_buffer.size()) == pos_GENERAL[16]);
}

template<class T, std::size_t N1, std::size_t N2>
bool compare_array_string(const std::array<std::basic_string_view<T>, N1>& _lhs, const T*(&_rhs)[N2])
{
	// check)
	if constexpr (N1 != N2)
		return	false;

	for(std::size_t i=0; i<N1; ++i)
	{
		if(_lhs[i] != _rhs[i])
		{
			return	false;
		}
	}

	return true;
}

template <class T>
inline bool compare_map_std_vector_string(const std::map<std::string, std::vector<std::basic_string_view<T>>>& _lhs, const std::map<std::string, std::vector<std::basic_string_view<T>>>& _rhs)
{
	auto iterX	  = _lhs.begin();
	auto iterXEnd = _lhs.end();
	auto iterY	  = _rhs.begin();

	for(; iterX!=iterXEnd; ++iterX, ++iterY)
	{
		auto iterA	  = iterX->second.begin();
		auto iterAEnd = iterX->second.end();
		auto iterB	  = iterY->second.begin();

		for(; iterA!=iterAEnd; ++iterA, ++iterB)
		{
			if(*iterA != *iterB)
			{
				return false;
			}
		}

		if(iterB!=iterY->second.end())
			return false;
	}

	return iterY == _rhs.end();
}


namespace CGDK
{
	TEST(CGDK10_object_buffer, buffer_timepoint)
	{
		{
			// - alloc shared_buffer
			shared_buffer buf_temp = alloc_shared_buffer(2048);

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
			// - alloc shared_buffer
			shared_buffer buf_temp = alloc_shared_buffer(2048);

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
	}

	TEST(CGDK10_object_buffer, buffer_append_general)
	{
		// - alloc shared_buffer
		shared_buffer buf_temp = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		for(int i=0; i<_TEST_COUNT;++i)
		{
			shared_buffer buf_temp_inner(buf_temp);

			function_append_GENERAL(buf_temp_inner);
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_general)
	{
		// - alloc shared_buffer
		shared_buffer buf_temp = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		function_append_GENERAL(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_extract_GENERAL(buf_temp);
		}
	}

	TEST(CGDK10_object_buffer, buffer_front_general)
	{
		// - alloc shared_buffer
		shared_buffer buf_temp = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		function_append_GENERAL(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_GENERAL(buf_temp);
		}
	}

	TEST(CGDK10_object_buffer, buffer_front_general_with_pos)
	{
		// - alloc shared_buffer
		shared_buffer buf_temp = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		function_append_GENERAL(buf_temp);

		for(int i=0; i<_TEST_COUNT;++i)
		{
			function_front_with_pos_GENERAL(buf_temp);
		}
	}

	TEST(CGDK10_object_buffer, buffer_prepend_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// Defintions)
		std::string_view str_test{ "Test String" };

		// - buffer 할당
		shared_buffer buf_test = (alloc_shared_buffer(2048) ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(str_test);

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK10_object_buffer, buffer_prepend_const_string)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// - Buffer 할당
		shared_buffer buf_alloc = (alloc_shared_buffer(2048) ^ OFFSET);

		// Defintions)
		std::string_view str_test{ "Test String" };

		// - buffer 할당
		shared_buffer buf_test = buf_alloc + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(str_test);

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_test == str_read);
	}

	TEST(CGDK10_object_buffer, buffer_prepend_string_format)
	{
		// declare) 
		const std::size_t OFFSET = 256;

		// defintions)
		std::string_view strTest1 = "Test String";
		std::string_view strTest3 = "Test End of String ";

		// - buffer 할당
		shared_buffer buf_test = (alloc_shared_buffer(2048) ^ OFFSET) + offset(OFFSET);

		// - 값 써넣기
		buf_test.prepend(strTest1);
		buf_test.prepend_string(std::string_view{ "Test %d %d" }, 10, 20);
		buf_test.prepend_string(strTest3);

		// - 값 읽기
		[[maybe_unused]] auto str_read_3 = buf_test.extract<std::string_view>();
		[[maybe_unused]] auto str_read_2 = buf_test.extract<std::string_view>();
		[[maybe_unused]] auto str_read_1 = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(strTest1 == str_read_1);
		EXPECT_TRUE(strTest3 == str_read_3);
	}

	TEST(CGDK10_object_buffer, buffer_append_string)
	{
		// Defintions)
		std::string_view str_test{ "Test String" };

		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - Buffer 할당
		shared_buffer buf_alloc(temp_memory);

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_append_string_view)
	{
		// Defintions)
		std::string	str_test{ "Test String" };

		// - alloc shared_buffer
		shared_buffer buf_test = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		buf_test.append(str_test);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(str_test));

		// - 값 읽기
		auto str_read = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(std::char_traits<char>::compare(str_test.data(), str_read.data(), 0)==0);
	}

	TEST(CGDK10_object_buffer, buffer_append_string_format)
	{
		// - alloc shared_buffer
		shared_buffer buf_test = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		buf_test.append(std::string_view{ "Test %d %d" }, 10, 20);
		buf_test.append(std::string_view{ "Test" });

		// - 값 읽기
		[[maybe_unused]] auto str_read_1 = buf_test.extract<std::string_view>();
		[[maybe_unused]] auto str_read_2 = buf_test.extract<std::string_view>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
		EXPECT_TRUE(str_read_2 == std::string_view("Test"));
	}

	TEST(CGDK10_object_buffer, buffer_append_const_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_test = alloc_shared_buffer(2048);
		//static_buffer buf_temp<2048>();

		// - 값 써넣기
		buf_test.append(std::string_view("Test XX"));

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(std::string_view("Test XX")));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<char*>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK10_object_buffer, buffer_String2)
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
		auto buf_temp_1 = alloc_shared_buffer(2048);
		auto buf_temp_2 = alloc_shared_buffer(2048);
		
		// Case A) 메모리 할당 (Allocating Memory)
		shared_buffer buf_write(buf_temp_1);

		// 2) 문자열 리스트 통채로 추가 (appending string list)
		buf_write.append(list_test);

		// check) 
		EXPECT_TRUE(buf_write.size() == get_size_of(list_test));

		// Case B) 메모리 할당 (Allocation Memory)
		shared_buffer temp_memory(buf_temp_2);

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
			std::list<std::string>	list_read;

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
			// 1) shared_buffer을 사용해서 읽도록 했다.(CCD:buffer_view나 buffer_view를 사용해도 된다.)
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

	TEST(CGDK10_object_buffer, buffer_append_text)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		const char*	str_test = "Test String";

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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
		EXPECT_TRUE(memcmp("Test String", buf_alloc.data(), std::char_traits<char>::length(str_test)*sizeof(char)) == 0);
		EXPECT_TRUE(memcmp("Test Temp", buf_alloc.data() + std::char_traits<char>::length(str_test)*sizeof(char), std::char_traits<char>::length("Test Temp")*sizeof(char)) == 0);
	}

	TEST(CGDK10_object_buffer, buffer_append_Initializer_list)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
		shared_buffer buf_temp(temp_memory);

		// 2) 추가한다
		buf_temp.append({ 1,2,3,4,5,6,7 });
	}

	TEST(CGDK10_object_buffer, buffer_iostream)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
		shared_buffer buf_temp(temp_memory);

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

	TEST(CGDK10_object_buffer, buffer_append_front_STRUCT_1)
	{
		struct TESTSTRUCT
		{
   			int			iValue;
   			uint32_t	dwValue;
   			char		chValue;
		};

		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
		shared_buffer buf_temp(temp_memory);

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

	TEST(CGDK10_object_buffer, buffer_append_front_to_STRUCT_1)
	{
		struct TESTSTRUCT
		{
			int			iValue;
			uint32_t	dwValue;
			char		chValue;
		};

		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
		shared_buffer buf_temp(temp_memory);

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

	TEST(CGDK10_object_buffer, buffer_append_front_STRUCT_2)
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


		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer
		shared_buffer buf_temp(temp_memory);

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

	TEST(CGDK10_object_buffer, buffer_append_front_to_STRUCT_2)
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


		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// 1) Buffer
		shared_buffer buf_temp(temp_memory);

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
	TEST(CGDK10_object_buffer, buffer_string_extract_char)					{ test_extract_string(array_string_char); }
	TEST(CGDK10_object_buffer, buffer_string_extract_wchar_t)				{ test_extract_string(array_string_wchar_t); }
	TEST(CGDK10_object_buffer, buffer_string_extract_char16_t)				{ test_extract_string(array_string_char16_t); }
	TEST(CGDK10_object_buffer, buffer_string_extract_char32_t)				{ test_extract_string(array_string_char32_t); }
	// 2) string(std::basic_string_view<T> type) append/extract
	TEST(CGDK10_object_buffer, buffer_string_extract_std_string_view)		{ test_extract_string(array_string_std_string_view); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_wstring_view)		{ test_extract_string(array_string_std_wstring_view); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_u16string_view)	{ test_extract_string(array_string_std_u16string_view); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_u32string_view)	{ test_extract_string(array_string_std_u32string_view); }
	// 3) string(std::basic_string<T> type) append/extract
	TEST(CGDK10_object_buffer, buffer_string_extract_std_string)			{ test_extract_string(array_string_std_string); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_wstring)			{ test_extract_string(array_string_std_wstring); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_u16string)			{ test_extract_string(array_string_std_u16string); }
	TEST(CGDK10_object_buffer, buffer_string_extract_std_u32string)			{ test_extract_string(array_string_std_u32string); }

	// 4) string(pointer type) append/front
	TEST(CGDK10_object_buffer, buffer_front_string_char)					{ test_front_string(array_string_char); }
	TEST(CGDK10_object_buffer, buffer_front_string_wchar_t)					{ test_front_string(array_string_wchar_t); }
	TEST(CGDK10_object_buffer, buffer_front_string_char16_t)				{ test_front_string(array_string_char16_t); }
	TEST(CGDK10_object_buffer, buffer_front_string_char32_t)				{ test_front_string(array_string_char32_t); }
	// 5) string(std::basic_string_view<T> type) append/front
	TEST(CGDK10_object_buffer, buffer_front_string_std_string_view)			{ test_front_string(array_string_std_string_view); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_wstring_view)		{ test_front_string(array_string_std_wstring_view); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_u16string_view)		{ test_front_string(array_string_std_u16string_view); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_u32string_view)		{ test_front_string(array_string_std_u32string_view); }
	// 6) string(std::basic_string<T> type) append/front
	TEST(CGDK10_object_buffer, buffer_front_string_std_string)				{ test_front_string(array_string_std_string); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_wstring)				{ test_front_string(array_string_std_wstring); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_u16string)			{ test_front_string(array_string_std_u16string); }
	TEST(CGDK10_object_buffer, buffer_front_string_std_u32string)			{ test_front_string(array_string_std_u32string); }

	// 7) bound check test
	TEST(CGDK10_object_buffer, buffer_string_append_bound_check)
	{
		// Defintions)
		std::string_view str_test = "Test String";

		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(get_size_of(str_test));
		//static_buffer buf_alloc<2048>();

		// - overflow test - pass
		{
			// - 
			shared_buffer buf_test = buf_alloc;

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
			shared_buffer buf_test = buf_alloc;

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
			shared_buffer buf_test = buf_alloc;

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
	TEST(CGDK10_object_buffer, buffer_string_prepend_bound_check)
	{
		// Defintions)
		std::string_view str_test = "Test String";

		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048) ^ 2048;
		//static_buffer buf_alloc<2048>();

		// - overflow test
		{
			// - 
			shared_buffer buf_test = buf_alloc + offset(get_size_of(str_test) - 1);

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
			shared_buffer buf_test = buf_alloc + offset(get_size_of(str_test));

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for(int i=0;i<_TEST_COUNT;++i)
		{
			shared_buffer buf_write = buf_alloc;

			buf_write.append(array_string_wchar_t);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(array_string_wchar_t));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_array_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_array_wchar_t)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(array_string_wchar_t);

			// - pop front!
			auto temp = buf_temp.extract<decltype(array_string_wchar_t)>();

			// check) 
			EXPECT_TRUE(compare_array_string<wchar_t>(temp, array_string_wchar_t)); // L"Fail to array[wchar_t] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_array_wchar_t)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_vector_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			shared_buffer buf_write = buf_alloc;

			buf_write.append(vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(vector_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_vector_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_vector_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_vector_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_vector_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_vector_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for(int i=0; i<_TEST_COUNT; ++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(vector_int);

			// - pop front!
			auto temp = buf_temp.extract<decltype(vector_int)>();

			// check) 
			EXPECT_TRUE(temp == vector_int); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_vector_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

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

	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_vector_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for(int i=0;i<_TEST_COUNT;++i)
		{
			shared_buffer buf_write = buf_alloc;

			buf_write.append(std_vector_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_vector_std_string));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_vector_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_vector_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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


	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_vector_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_vector_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_vector_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for(int i=0;i<_TEST_COUNT;++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

			// - 
			buf_temp.prepend(std_vector_std_string);

			// - pop front!
			auto temp = buf_temp.extract<decltype(std_vector_std_string)>();

			// check) 
			EXPECT_TRUE(temp==std_vector_std_string); // L"Fail to vector[int] prepend/extract"
			EXPECT_TRUE(buf_temp.size() == 0);
		}
	}

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_vector_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		shared_buffer buf_alloc = temp_memory ^ 2048;

		// - extract
		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			// - 
			shared_buffer buf_temp = buf_alloc + offset(2048);

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
	TEST(CGDK10_object_buffer, buffer_std_array_append_extract)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<int, 10>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_to)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<int, 10>	temp_std_array = { 10, 11, 12, 13, 14, 15, };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_char)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(array_string_char);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(array_string_char));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<decltype(array_string_char)>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_to_char)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_to_wchar_t)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_std_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<std::string, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_to_std_string)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<std::string, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_std_string_view)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

		// - 값 써넣기
		buf_test.append(temp_std_array);

		// check) 
		EXPECT_TRUE(buf_test.size() == get_size_of(temp_std_array));

		// - 값 읽기
		[[maybe_unused]] auto str_read = buf_test.extract<std::array<std::string_view, 4>>();

		// check) 
		EXPECT_TRUE(buf_test.size() == 0);
	}

	TEST(CGDK10_object_buffer, buffer_std_array_append_extract_to_std_string_view)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// Defintions)
		std::array<std::string_view, 4>	temp_std_array = { "a", "bc", "def", "hijk" };

		// - 임시로...
		shared_buffer buf_test = buf_alloc;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		shared_buffer buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			shared_buffer buf_write = buf_alloc;

			buf_write.append(std_list_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_list_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048) ^ 2048;
		//static_buffer buf_alloc<2048>();

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_list_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_std_string);
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_list_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_list_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_list_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_list_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_list_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_list_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for (int i = 0; i < _TEST_COUNT; ++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_list_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_list_vector_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_list_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_list_vector_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_list_vector_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_set_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_set_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_set_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_set_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_set_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_set_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_set_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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

	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_set_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_set_std_string);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_set_std_string));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_set_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_set_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_set_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_set_string)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_set_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_set_string)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_int_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_int_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_map_int_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_map_int_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_string_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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
	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_map_string_int_push)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - ....
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_string_std_vector_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_string_std_vector_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_map_string_vector_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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


	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_map_string_vector_int)
	{
		// X) Memory Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

		// - String append
		auto buf_alloc = temp_memory ^ 2048;

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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - append data
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_map_std_vector_std_string_view);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_map_std_vector_std_string_view));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_to_CONTAINER_map_string_vector_charP)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_map_string_vector_charP)
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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_to_CONTAINER_map_string_vector_charP)
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
	TEST(CGDK10_object_buffer, buffer_append_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - ...
		for(int i=0;i<_TEST_COUNT;++i)
		{
			auto buf_write = buf_alloc;

			buf_write.append(std_unordered_map_std_string_int);

			// check) 
			EXPECT_TRUE(buf_write.size() == get_size_of(std_unordered_map_std_string_int));
		}
	}

	TEST(CGDK10_object_buffer, buffer_extract_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_extract_to_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_front_CONTAINER_unoredered_map_string_int)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_prepend_extract_CONTAINER_unoredered_map_string_int)
	{
		// X) Alloc
		auto temp_memory = alloc_shared_buffer(2048);
		//char temp_memory[2048];

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
	TEST(CGDK10_object_buffer, buffer_VariableLength)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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
	TEST(CGDK10_object_buffer, buffer_buffer)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		shared_buffer bufA;
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
	TEST(CGDK10_object_buffer, buffer_buffer_to)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		shared_buffer bufA;
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

	TEST(CGDK10_object_buffer, buffer_map_tuple01)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple02)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple03)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple04)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple05)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple06)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple07)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, buffer_map_tuple08)
	{
		// definitions) 
		const int				source_a = 3;
		const std::string_view	source_b = "Test";
		const float				source_c = 2.0f;

		// - alloc shared_buffer
		auto buf_source = alloc_shared_buffer(2048);
		//static_buffer buf_source<2048>();

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

	TEST(CGDK10_object_buffer, test_buffer_map_tuple09)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp = TUPPLE_B(0, TUPPLE_A(0, 0, 1.0f, "Test"), "Value");

		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, test_buffer_map_tuple10)
	{
		// definitions)
		using TUPPLE_A = std::tuple<int, int, float, std::string_view>;
		using TUPPLE_B = std::tuple<int, TUPPLE_A, std::string_view>;

		// 1) 써넣은 예제 Tupple
		TUPPLE_B temp = TUPPLE_B(0, TUPPLE_A(0, 0, 1.0f, "Test"), "Value");

		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_time_1)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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
	}

	TEST(CGDK10_object_buffer, buffer_time_2)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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
	}

	TEST(CGDK10_object_buffer, buffer_web)
	{
		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// - ...
		auto buf_temp = buf_alloc;

		// 2) Append
		buf_alloc.append_text("Test");
		buf_alloc.append_text("Test {} {} {}\n", 100, "Test", 0.1f);
	}


	//-----------------------------------------------------------------
	// Test) Object Serialize
	//-----------------------------------------------------------------

	TEST(CGDK10_object_buffer, buffer_append_extract_serializable)
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

			virtual	void	process_serialize_out(basic_buffer& _Buffer) override
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
		//static_buffer buf_alloc<2048>();

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

	TEST(CGDK10_object_buffer, buffer_append_extract_serializable_1)
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

			virtual	void	process_serialize_out(basic_buffer& _Buffer) override
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
		//static_buffer buf_alloc<2048>();

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
	TEST(CGDK10_object_buffer, buffer_append_extract_serializable_2)
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
		//static_buffer buf_alloc<2048>();

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
	TEST(CGDK10_object_buffer, buffer_test_01)
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
			vector<int32_t>	value_c;
		};

		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

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
	
	TEST(CGDK10_object_buffer, buffer_test_02)
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
			vector<int32_t>	value_c;

			ENABLE_STRUCT_SERIALIZABLE
		};

		// - alloc shared_buffer
		auto buf_alloc = alloc_shared_buffer(2048);
		//static_buffer buf_alloc<2048>();

		// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		auto buf_temp = buf_alloc;

		// 2) 객체
		sTEST_MESSAGE	a;
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