#include "pch.h"

#ifdef _WIN32
	#pragma warning(disable:4566)
#endif

// Declare) Test String
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

// Declare) Test String
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

// Declare) Test String
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


// Declare) Test String
std::string	array_std_string[8] = 
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

// Declare) Test String
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

// Declare ) vector<ing>
std::vector<int> std_vector_int = 
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) vector<string>
std::vector<std::string> std_vector_std_string = 
{
	"zero",
	"one",
	"two",
	"tree",
	"hundred",
	"fifteen",
	"five",
	"eleven"
};

std::vector<std::wstring> std_vector_std_wstring
{
	L"zero",
	L"one",
	L"two",
	L"tree",
	L"hundred",
	L"fifteen",
	L"five",
	L"eleven"
};

// Declare ) vector<string>
std::vector<std::vector<int>> std_vector_std_vector_int = 
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};

// Declare ) list<ing>
std::list<int> std_list_int = 
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) list<string>
std::list<std::string> std_list_std_string = 
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) list<string>
std::list<std::vector<int>>	std_list_std_vector_int	 = 
{
	{0, 0, 3},
	{3, 2, 64},
	{5, 3, 11},
	{6, 14, 13},
	{7, 5, 200, 400, 12, 33},
	{10, 11, 12,900}
};


// Declare ) set<ing>
std::set<int> std_set_int = 
{
	0,
	2,
	3,
	14,
	5,
	11
};

// Declare ) set<string>
std::set<std::string> std_set_std_string = 
{
	"zero",
	"two",
	"tree",
	"fifteen",
	"five",
	"eleven"
};

// Declare ) map<string, ing>
std::map<int, int> std_map_int_int = 
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) map<string, ing>
std::map<std::string, int> std_map_std_string_int = 
{
	{"zero",	0},
	{"two",		2},
	{"tree",	3},
	{"fifteen",	14},
	{"five",	5},
	{"eleven",	11}
};

// Declare ) map<string, ing>
std::map<std::string, std::vector<int>>	std_map_std_string_std_vector_int = 
{
	{"zero",	{0,1,2,4}},
	{"two",		{3,1,22,4}},
	{"tree",	{4,1,12,4}},
	{"fifteen",	{5,1,82,4}},
	{"five",	{7,1,22,4}},
	{"eleven",	{10,21,12,34}}
};

std::map<std::wstring, std::vector<int>> std_map_std_wstring_std_vector_int = 
{
	{L"zero",	{0,1,2,4}},
	{L"two",	{3,1,22,4}},
	{L"tree",	{4,1,12,4}},
	{L"fifteen",{5,1,82,4}},
	{L"five",	{7,1,22,4}},
	{L"eleven",	{10,21,12,34}}
};

// Declare ) map<string, ing>
std::map<std::string, std::vector<const char*>> std_map_std_vector_string = 
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<int, int> std_unordered_map_int_int = 
{
	{0,		0},
	{3,		2},
	{5,		3},
	{6,		14},
	{7,		5},
	{10,	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, int> std_unordered_map_std_string_int = 
{
	{"zero",	0},
	{"two",		2},
	{"tree",	3},
	{"fifteen",	14},
	{"five",	5},
	{"eleven",	11}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<int>> std_unordered_map_std_string_std_vector_int = 
{
	{"zero",	{0,1,2,4}},
	{"two",		{3,1,22,4}},
	{"tree",	{4,1,12,4}},
	{"fifteen",	{5,1,82,4}},
	{"five",	{7,1,22,4}},
	{"eleven",	{10,21,12,34}}
};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<const char*>> std_unordered_map_std_vector_std_string = 
{
	{"zero",	{"zero", "zero", "zero", "zero"}},
	{"two",		{"zero", "zero", "zero", "zero"}},
	{"tree",	{"zero", "zero", "zero", "zero"}},
	{"fifteen",	{"zero", "zero", "zero", "zero"}},
	{"five",	{"zero", "zero", "zero", "zero"}},
	{"eleven",	{"zero", "zero", "zero", "zero"}}
};


void init_containers()
{
	// Declare ) vector<ing>
	std_vector_int.clear();
	std_vector_int.push_back(0);
	std_vector_int.push_back(2);
	std_vector_int.push_back(3);
	std_vector_int.push_back(14);
	std_vector_int.push_back(5);
	std_vector_int.push_back(11);

	// Declare ) vector<string>
	std_vector_std_string.clear();
	std_vector_std_string.push_back("zero");
	std_vector_std_string.push_back("two");
	std_vector_std_string.push_back("tree");
	std_vector_std_string.push_back("fifteen");
	std_vector_std_string.push_back("five");
	std_vector_std_string.push_back("eleven");

	// Declare ) vector<string>
	std_vector_std_vector_int.clear();
	{ std::vector<int> temp; temp.push_back(0); temp.push_back(0); temp.push_back(3);  std_vector_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(3); temp.push_back(2); temp.push_back(64); std_vector_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(5); temp.push_back(3); temp.push_back(11); std_vector_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(6); temp.push_back(14);temp.push_back(13); std_vector_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(70);temp.push_back(5); temp.push_back(200);temp.push_back(400); temp.push_back(12); temp.push_back(33); std_vector_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(10);temp.push_back(11);temp.push_back(12); temp.push_back(900); std_vector_std_vector_int.push_back(temp);}

	// Declare ) list<ing>
	std_list_int.clear();
	std_list_int.push_back(0);
	std_list_int.push_back(2);
	std_list_int.push_back(3);
	std_list_int.push_back(14);
	std_list_int.push_back(5);
	std_list_int.push_back(11);

	// Declare ) list<string>
	std_list_std_string.clear();
	std_list_std_string.push_back("zero");
	std_list_std_string.push_back("two");
	std_list_std_string.push_back("tree");
	std_list_std_string.push_back("fifteen");
	std_list_std_string.push_back("five");
	std_list_std_string.push_back("eleven");

	// Declare ) list<string>
	std_list_std_vector_int.clear();
	{ std::vector<int> temp; temp.push_back(0); temp.push_back(0); temp.push_back(3);  std_list_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(3); temp.push_back(2); temp.push_back(64); std_list_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(5); temp.push_back(3); temp.push_back(11); std_list_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(6); temp.push_back(14);temp.push_back(13); std_list_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(70);temp.push_back(5); temp.push_back(200);temp.push_back(400); temp.push_back(12); temp.push_back(33); std_list_std_vector_int.push_back(temp);}
	{ std::vector<int> temp; temp.push_back(10);temp.push_back(11);temp.push_back(12); temp.push_back(900); std_list_std_vector_int.push_back(temp);}


	// Declare ) set<ing>
	std_set_int.clear();
	std_set_int.insert(0);
	std_set_int.insert(2);
	std_set_int.insert(3);
	std_set_int.insert(14);
	std_set_int.insert(5);
	std_set_int.insert(11);

	// Declare ) set<string>
	std_set_std_string.clear();
	std_set_std_string.insert("zero");
	std_set_std_string.insert("two");
	std_set_std_string.insert("tree");
	std_set_std_string.insert("fifteen");
	std_set_std_string.insert("five");
	std_set_std_string.insert("eleven");

	// Declare ) map<int, ing>
	std_map_int_int.clear();
	std_map_int_int.insert(std::make_pair(0, 0));
	std_map_int_int.insert(std::make_pair(3, 2));
	std_map_int_int.insert(std::make_pair(5, 3));
	std_map_int_int.insert(std::make_pair(6, 14));
	std_map_int_int.insert(std::make_pair(7, 5 ));
	std_map_int_int.insert(std::make_pair(10, 11));

	// Declare ) map<string, ing>
	std_map_std_string_int.clear();
	std_map_std_string_int.insert(std::make_pair("zero", 0));
	std_map_std_string_int.insert(std::make_pair("two", 2));
	std_map_std_string_int.insert(std::make_pair("tree", 3));
	std_map_std_string_int.insert(std::make_pair("fifteen", 14));
	std_map_std_string_int.insert(std::make_pair("five", 5 ));
	std_map_std_string_int.insert(std::make_pair("eleven", 11));

	// Declare ) map<string, ing>
	std_map_std_string_std_vector_int.clear();
	{ std::vector<int> temp; temp.push_back(0); temp.push_back(1); temp.push_back(2);  temp.push_back(4); std_map_std_string_std_vector_int.insert(std::make_pair("zero", temp));}
	{ std::vector<int> temp; temp.push_back(3); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_map_std_string_std_vector_int.insert(std::make_pair("two", temp));}
	{ std::vector<int> temp; temp.push_back(4); temp.push_back(1); temp.push_back(12); temp.push_back(4); std_map_std_string_std_vector_int.insert(std::make_pair("tree", temp));}
	{ std::vector<int> temp; temp.push_back(5); temp.push_back(1); temp.push_back(82); temp.push_back(4); std_map_std_string_std_vector_int.insert(std::make_pair("fifteen", temp));}
	{ std::vector<int> temp; temp.push_back(7); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_map_std_string_std_vector_int.insert(std::make_pair("five", temp));}
	{ std::vector<int> temp; temp.push_back(10);temp.push_back(21);temp.push_back(12); temp.push_back(34);std_map_std_string_std_vector_int.insert(std::make_pair("eleven", temp));}

	// Declare ) std::map<std::wstring, std::vector<int>>
	std_map_std_wstring_std_vector_int.clear();
	{ std::vector<int> temp; temp.push_back(0); temp.push_back(1); temp.push_back(2);  temp.push_back(4); std_map_std_wstring_std_vector_int.insert(std::make_pair(L"zero", temp));}
	{ std::vector<int> temp; temp.push_back(3); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_map_std_wstring_std_vector_int.insert(std::make_pair(L"two", temp));}
	{ std::vector<int> temp; temp.push_back(4); temp.push_back(1); temp.push_back(12); temp.push_back(4); std_map_std_wstring_std_vector_int.insert(std::make_pair(L"tree", temp));}
	{ std::vector<int> temp; temp.push_back(5); temp.push_back(1); temp.push_back(82); temp.push_back(4); std_map_std_wstring_std_vector_int.insert(std::make_pair(L"fifteen", temp));}
	{ std::vector<int> temp; temp.push_back(7); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_map_std_wstring_std_vector_int.insert(std::make_pair(L"five", temp));}
	{ std::vector<int> temp; temp.push_back(10);temp.push_back(21);temp.push_back(12); temp.push_back(34);std_map_std_wstring_std_vector_int.insert(std::make_pair(L"eleven", temp));}

	// Declare ) map<string, ing>
	std_map_std_vector_string.clear();
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("zero", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("two", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("tree", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("fifteen", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("five", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_map_std_vector_string.insert(std::make_pair("eleven", temp));}

	// Declare ) unordered_map<string, ing>
	std_unordered_map_int_int.clear();
	std_unordered_map_int_int.insert(std::make_pair(0,  0));
	std_unordered_map_int_int.insert(std::make_pair(3,  2));
	std_unordered_map_int_int.insert(std::make_pair(5,  3));
	std_unordered_map_int_int.insert(std::make_pair(6, 14));
	std_unordered_map_int_int.insert(std::make_pair(7,  5));
	std_unordered_map_int_int.insert(std::make_pair(10,11));

	// Declare ) unordered_map<string, ing>
	std_unordered_map_std_string_int.clear();
	std_unordered_map_std_string_int.insert(std::make_pair("zero",  0));
	std_unordered_map_std_string_int.insert(std::make_pair("two",  2));
	std_unordered_map_std_string_int.insert(std::make_pair("tree",  3));
	std_unordered_map_std_string_int.insert(std::make_pair("fifteen", 14));
	std_unordered_map_std_string_int.insert(std::make_pair("five",  5));
	std_unordered_map_std_string_int.insert(std::make_pair("eleven",11));

	// Declare ) unordered_map<string, ing>
	std_unordered_map_std_string_std_vector_int.clear();
	{ std::vector<int> temp; temp.push_back(0); temp.push_back(1); temp.push_back(2);  temp.push_back(4); std_unordered_map_std_string_std_vector_int.insert(std::make_pair("zero", temp));}
	{ std::vector<int> temp; temp.push_back(3); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_unordered_map_std_string_std_vector_int.insert(std::make_pair("two", temp));}
	{ std::vector<int> temp; temp.push_back(4); temp.push_back(1); temp.push_back(12); temp.push_back(4); std_unordered_map_std_string_std_vector_int.insert(std::make_pair("tree", temp));}
	{ std::vector<int> temp; temp.push_back(5); temp.push_back(1); temp.push_back(82); temp.push_back(4); std_unordered_map_std_string_std_vector_int.insert(std::make_pair("fifteen", temp));}
	{ std::vector<int> temp; temp.push_back(7); temp.push_back(1); temp.push_back(22); temp.push_back(4); std_unordered_map_std_string_std_vector_int.insert(std::make_pair("five", temp));}
	{ std::vector<int> temp; temp.push_back(10);temp.push_back(21);temp.push_back(12); temp.push_back(34);std_unordered_map_std_string_std_vector_int.insert(std::make_pair("eleven", temp));}

	// Declare ) unordered_map<string, ing>
	std_unordered_map_std_vector_std_string.clear();
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("zero", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("two", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("tree", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("fifteen", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("five", temp));}
	{ std::vector<const char*> temp; temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); temp.push_back("zero"); std_unordered_map_std_vector_std_string.insert(std::make_pair("eleven", temp));}
}