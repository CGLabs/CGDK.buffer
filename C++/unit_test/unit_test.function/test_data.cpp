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
const char8_t* array_string_char8_t[8] =
{
	u8"Please Let test this",
	u8"이것 좀 테스트하게 해주세요.",
	u8"这件事 试验",
	u8"これを試ためさせてください",
	u8"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	u8"Please 这件事 試ためさせてください 합시다.",
	u8"Test What ever",
	u8"1234"
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
const char32_t* array_string_char32_t[8] =
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


std::string_view array_std_string_view[8] =
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
std::wstring_view array_std_wstring_view[8] =
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
std::u8string_view array_std_u8string_view[8] =
{
	u8"Please Let test this",
	u8"이것 좀 테스트하게 해주세요.",
	u8"这件事 试验",
	u8"これを試ためさせてください",
	u8"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
	u8"Please 这件事 試ためさせてください 합시다.",
	u8"Test What ever",
	u8"1234"
};
std::u16string_view array_std_u16string_view[8] =
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
std::u32string_view array_std_u32string_view[8] =
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

std::string array_std_string[8] =
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
std::wstring array_std_wstring[8] =
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

std::u16string array_std_u16string[8] =
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

std::u32string array_std_u32string[8] =
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
std::vector<int> std_vector_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) vector<string>
std::vector<std::string> std_vector_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) vector<string>
std::vector<std::vector<int>> std_vector_std_vector_int
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};

// Declare ) list<ing>
std::list<int> std_list_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) list<string>
std::list<std::string> std_list_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) list<string>
std::list<std::vector<int>>	std_list_std_vector_int
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};


// Declare ) set<ing>
std::set<int> std_set_int
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) set<string>
std::set<std::string> std_set_std_string
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) map<string, ing>
std::map<int, int> std_map_int_int
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) map<string, ing>
std::map<std::string, int> std_map_std_string_int
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
std::map<std::wstring, std::vector<int>> std_map_std_wstring_std_vector_int
{
	{L"zero",	{0,1,2,4}},
	{L"two",	{3,1,22,4}},
	{L"tree",	{4,1,12,4}},
	{L"fifteen",{5,1,82,4}},
	{L"five",	{7,1,22,4}},
	{L"eleven",	{10,21,12,34}}
};

// Declare ) map<string, ing>
std::map<std::string, std::vector<std::string_view>> std_map_std_vector_std_string_view
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<int, int> std_unordered_map_int_int
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, int> std_unordered_map_std_string_int
{
	{"zero",	0},
	{"two",		2},
	{"tree",	3},
	{"fifteen",	14},
	{"five",	5},
	{"eleven",	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<int>> std_unordered_map_std_string_std_vector_int
{
	{"zero",	{0,1,2,4}},
	{"two",		{3,1,22,4}},
	{"tree",	{4,1,12,4}},
	{"fifteen",	{5,1,82,4}},
	{"five",	{7,1,22,4}},
	{"eleven",	{10,21,12,34}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<std::string_view>> std_unordered_map_std_vector_std_string_view
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};

size_t pos_general[]{
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
