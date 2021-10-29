#include "stdafx.h"
#include "CGDBuffers_UnitTest_Performance_Definitions.h"


#pragma warning(disable:4566)

// Declare) Test String
int	array_int[8]	 = 
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
char*	array_string_char[8]	 = 
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
wchar_t*	array_string_wchar_t[8]	 = 
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
std::string	array_std_string_stdstring[8]	 = 
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
std::wstring	array_std_string_stdwstring[8]	 = 
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
std::vector<int>	vector_int;
//std::vector<int>	vector_int	 = 
//{
//	0,
//	2,
//	3,
//	14,
//	5,
//	11
//};

// Declare ) vector<string>
std::vector<std::string>	vector_std_string;
//std::vector<std::string>	vector_std_string	 = 
//{
//	"zero",
//	"two",
//	"tree",
//	"fifteen",
//	"five",
//	"eleven"
//};

// Declare ) vector<string>
std::vector<std::vector<int>>	vector_vector_int;
//std::vector<std::vector<int>>	vector_vector_int	 = 
//{
//	{0, 0, 3},
//	{3, 2, 64},
//	{5, 3, 11},
//	{6, 14, 13},
//	{7, 5, 200, 400, 12, 33},
//	{10, 11, 12,900}
//};

// Declare ) list<ing>
std::list<int>	list_int;
//std::list<int>	list_int	 = 
//{
//	0,
//	2,
//	3,
//	14,
//	5,
//	11
//};

// Declare ) list<string>
std::list<std::string>	list_std_string;
//std::list<std::string>	list_std_string	 = 
//{
//	"zero",
//	"two",
//	"tree",
//	"fifteen",
//	"five",
//	"eleven"
//};

// Declare ) list<string>
std::list<std::vector<int>>	list_vector_int;
//std::list<std::vector<int>>	list_vector_int	 = 
//{
//	{0, 0, 3},
//	{3, 2, 64},
//	{5, 3, 11},
//	{6, 14, 13},
//	{7, 5, 200, 400, 12, 33},
//	{10, 11, 12,900}
//};


// Declare ) set<ing>
std::set<int>	set_int;
//std::set<int>	set_int	 = 
//{
//	0,
//	2,
//	3,
//	14,
//	5,
//	11
//};

// Declare ) set<string>
std::set<std::string>	set_std_string;
//std::set<std::string>	set_std_string	 = 
//{
//	"zero",
//	"two",
//	"tree",
//	"fifteen",
//	"five",
//	"eleven"
//};

// Declare ) map<string, ing>
std::map<int, int>	map_std_int_int;
//std::map<int, int>	map_std_int_int	 = 
//{
//	{0,		0},
//	{3,		2},
//	{5,		3},
//	{6,		14},
//	{7,		5},
//	{10,	11}
//};

// Declare ) map<string, ing>
std::map<std::string, int>	map_std_string_int;
//std::map<std::string, int>	map_std_string_int	 = 
//{
//	{"zero",	0},
//	{"two",		2},
//	{"tree",	3},
//	{"fifteen",	14},
//	{"five",	5},
//	{"eleven",	11}
//};

// Declare ) map<string, ing>
std::map<std::string, std::vector<int>>	map_std_string_vector_int;
//std::map<std::string, std::vector<int>>	map_std_string_vector_int	 = 
//{
//	{"zero",	{0,1,2,4}},
//	{"two",		{3,1,22,4}},
//	{"tree",	{4,1,12,4}},
//	{"fifteen",	{5,1,82,4}},
//	{"five",	{7,1,22,4}},
//	{"eleven",	{10,21,12,34}}
//};

std::map<std::wstring, std::vector<int>>	map_std_wstring_vector_int;
//std::map<std::wstring, std::vector<int>>	map_std_wstring_vector_int	 = 
	//{
	//	{L"zero",	{0,1,2,4}},
	//	{L"two",	{3,1,22,4}},
	//	{L"tree",	{4,1,12,4}},
	//	{L"fifteen",{5,1,82,4}},
	//	{L"five",	{7,1,22,4}},
	//	{L"eleven",	{10,21,12,34}}
	//};


// Declare ) map<string, ing>
std::map<std::string, std::vector<char*>>	map_std_vector_string;
//std::map<std::string, std::vector<char*>>	map_std_vector_string	 = 
//{
//	{"zero",	{"zero", "zero", "zero", "zero"}},
//	{"two",		{"zero", "zero", "zero", "zero"}},
//	{"tree",	{"zero", "zero", "zero", "zero"}},
//	{"fifteen",	{"zero", "zero", "zero", "zero"}},
//	{"five",	{"zero", "zero", "zero", "zero"}},
//	{"eleven",	{"zero", "zero", "zero", "zero"}}
//};

// Declare ) unordered_map<string, ing>
std::unordered_map<int, int>	unordered_map_std_int_int;
//std::unordered_map<int, int>	unordered_map_std_int_int	 = 
//{
//	{0,		0},
//	{3,		2},
//	{5,		3},
//	{6,		14},
//	{7,		5},
//	{10,	11}
//};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, int>	unordered_map_std_string_int;
//std::unordered_map<std::string, int>	unordered_map_std_string_int	 = 
//{
//	{"zero",	0},
//	{"two",		2},
//	{"tree",	3},
//	{"fifteen",	14},
//	{"five",	5},
//	{"eleven",	11}
//};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<int>>	unordered_map_std_string_vector_int;
//std::unordered_map<std::string, std::vector<int>>	unordered_map_std_string_vector_int	 = 
//{
//	{"zero",	{0,1,2,4}},
//	{"two",		{3,1,22,4}},
//	{"tree",	{4,1,12,4}},
//	{"fifteen",	{5,1,82,4}},
//	{"five",	{7,1,22,4}},
//	{"eleven",	{10,21,12,34}}
//};

// Declare ) unordered_map<string, ing>
std::unordered_map<std::string, std::vector<char*>>	unordered_map_std_vector_string;
//std::unordered_map<std::string, std::vector<char*>>	unordered_map_std_vector_string	 = 
//{
//	{"zero",	{"zero", "zero", "zero", "zero"}},
//	{"two",		{"zero", "zero", "zero", "zero"}},
//	{"tree",	{"zero", "zero", "zero", "zero"}},
//	{"fifteen",	{"zero", "zero", "zero", "zero"}},
//	{"five",	{"zero", "zero", "zero", "zero"}},
//	{"eleven",	{"zero", "zero", "zero", "zero"}}
//};


void InitContainers()
{
	// Declare ) vector<ing>
	vector_int.clear();
	vector_int.push_back(0);
	vector_int.push_back(2);
	vector_int.push_back(3);
	vector_int.push_back(14);
	vector_int.push_back(5);
	vector_int.push_back(11);

	// Declare ) vector<string>
	vector_std_string.clear();
	vector_std_string.push_back("zero");
	vector_std_string.push_back("two");
	vector_std_string.push_back("tree");
	vector_std_string.push_back("fifteen");
	vector_std_string.push_back("five");
	vector_std_string.push_back("eleven");

	// Declare ) vector<string>
	vector_vector_int.clear();
	{	std::vector<int>	temp;	temp.push_back(0);	temp.push_back(0);	temp.push_back(3);	vector_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(3);	temp.push_back(2);	temp.push_back(64);	vector_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(5);	temp.push_back(3);	temp.push_back(11);	vector_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(6);	temp.push_back(14);	temp.push_back(13);	vector_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(70);	temp.push_back(5);	temp.push_back(200); temp.push_back(400); temp.push_back(12); temp.push_back(33); vector_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(10);	temp.push_back(11);	temp.push_back(12);	temp.push_back(900); vector_vector_int.push_back(temp);}

	// Declare ) list<ing>
	list_int.clear();
	list_int.push_back(0);
	list_int.push_back(2);
	list_int.push_back(3);
	list_int.push_back(14);
	list_int.push_back(5);
	list_int.push_back(11);

	// Declare ) list<string>
	list_std_string.clear();
	list_std_string.push_back("zero");
	list_std_string.push_back("two");
	list_std_string.push_back("tree");
	list_std_string.push_back("fifteen");
	list_std_string.push_back("five");
	list_std_string.push_back("eleven");

	// Declare ) list<string>
	list_vector_int.clear();
	{	std::vector<int>	temp;	temp.push_back(0);	temp.push_back(0);	temp.push_back(3);	list_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(3);	temp.push_back(2);	temp.push_back(64);	list_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(5);	temp.push_back(3);	temp.push_back(11);	list_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(6);	temp.push_back(14);	temp.push_back(13);	list_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(70);	temp.push_back(5);	temp.push_back(200); temp.push_back(400); temp.push_back(12); temp.push_back(33); list_vector_int.push_back(temp);}
	{	std::vector<int>	temp;	temp.push_back(10);	temp.push_back(11);	temp.push_back(12);	temp.push_back(900); list_vector_int.push_back(temp);}


	// Declare ) set<ing>
	set_int.clear();
	set_int.insert(0);
	set_int.insert(2);
	set_int.insert(3);
	set_int.insert(14);
	set_int.insert(5);
	set_int.insert(11);

	// Declare ) set<string>
	set_std_string.clear();
	set_std_string.insert("zero");
	set_std_string.insert("two");
	set_std_string.insert("tree");
	set_std_string.insert("fifteen");
	set_std_string.insert("five");
	set_std_string.insert("eleven");

	// Declare ) map<int, ing>
	map_std_int_int.clear();
	map_std_int_int.insert(std::make_pair(0, 0));
	map_std_int_int.insert(std::make_pair(3, 2));
	map_std_int_int.insert(std::make_pair(5, 3));
	map_std_int_int.insert(std::make_pair(6, 14));
	map_std_int_int.insert(std::make_pair(7, 5 ));
	map_std_int_int.insert(std::make_pair(10, 11));

	// Declare ) map<string, ing>
	map_std_string_int.clear();
	map_std_string_int.insert(std::make_pair("zero", 0));
	map_std_string_int.insert(std::make_pair("two", 2));
	map_std_string_int.insert(std::make_pair("tree", 3));
	map_std_string_int.insert(std::make_pair("fifteen", 14));
	map_std_string_int.insert(std::make_pair("five", 5 ));
	map_std_string_int.insert(std::make_pair("eleven", 11));

	// Declare ) map<string, ing>
	map_std_string_vector_int.clear();
	{	std::vector<int> temp;	temp.push_back(0);	temp.push_back(1);	temp.push_back(2);	temp.push_back(4);	map_std_string_vector_int.insert(std::make_pair("zero", temp));}
	{	std::vector<int> temp;	temp.push_back(3);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	map_std_string_vector_int.insert(std::make_pair("two", temp));}
	{	std::vector<int> temp;	temp.push_back(4);	temp.push_back(1);	temp.push_back(12);	temp.push_back(4);	map_std_string_vector_int.insert(std::make_pair("tree", temp));}
	{	std::vector<int> temp;	temp.push_back(5);	temp.push_back(1);	temp.push_back(82);	temp.push_back(4);	map_std_string_vector_int.insert(std::make_pair("fifteen", temp));}
	{	std::vector<int> temp;	temp.push_back(7);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	map_std_string_vector_int.insert(std::make_pair("five", temp));}
	{	std::vector<int> temp;	temp.push_back(10);	temp.push_back(21);	temp.push_back(12);	temp.push_back(34);	map_std_string_vector_int.insert(std::make_pair("eleven", temp));}

	// Declare ) std::map<std::wstring, std::vector<int>>
	map_std_wstring_vector_int.clear();
	{	std::vector<int> temp;	temp.push_back(0);	temp.push_back(1);	temp.push_back(2);	temp.push_back(4);	map_std_wstring_vector_int.insert(std::make_pair(L"zero", temp));}
	{	std::vector<int> temp;	temp.push_back(3);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	map_std_wstring_vector_int.insert(std::make_pair(L"two", temp));}
	{	std::vector<int> temp;	temp.push_back(4);	temp.push_back(1);	temp.push_back(12);	temp.push_back(4);	map_std_wstring_vector_int.insert(std::make_pair(L"tree", temp));}
	{	std::vector<int> temp;	temp.push_back(5);	temp.push_back(1);	temp.push_back(82);	temp.push_back(4);	map_std_wstring_vector_int.insert(std::make_pair(L"fifteen", temp));}
	{	std::vector<int> temp;	temp.push_back(7);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	map_std_wstring_vector_int.insert(std::make_pair(L"five", temp));}
	{	std::vector<int> temp;	temp.push_back(10);	temp.push_back(21);	temp.push_back(12);	temp.push_back(34);	map_std_wstring_vector_int.insert(std::make_pair(L"eleven", temp));}

	


	// Declare ) map<string, ing>
	map_std_vector_string.clear();
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("zero", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("two", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("tree", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("fifteen", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("five", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	map_std_vector_string.insert(std::make_pair("eleven", temp));}

	// Declare ) unordered_map<string, ing>
	unordered_map_std_int_int.clear();
	unordered_map_std_int_int.insert(std::make_pair(0,  0));
	unordered_map_std_int_int.insert(std::make_pair(3,  2));
	unordered_map_std_int_int.insert(std::make_pair(5,  3));
	unordered_map_std_int_int.insert(std::make_pair(6, 14));
	unordered_map_std_int_int.insert(std::make_pair(7,  5));
	unordered_map_std_int_int.insert(std::make_pair(10,11));

	// Declare ) unordered_map<string, ing>
	unordered_map_std_string_int.clear();
	unordered_map_std_string_int.insert(std::make_pair("zero",  0));
	unordered_map_std_string_int.insert(std::make_pair("two",  2));
	unordered_map_std_string_int.insert(std::make_pair("tree",  3));
	unordered_map_std_string_int.insert(std::make_pair("fifteen", 14));
	unordered_map_std_string_int.insert(std::make_pair("five",  5));
	unordered_map_std_string_int.insert(std::make_pair("eleven",11));

	// Declare ) unordered_map<string, ing>
	unordered_map_std_string_vector_int.clear();
	{	std::vector<int> temp;	temp.push_back(0);	temp.push_back(1);	temp.push_back(2);	temp.push_back(4);	unordered_map_std_string_vector_int.insert(std::make_pair("zero", temp));}
	{	std::vector<int> temp;	temp.push_back(3);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	unordered_map_std_string_vector_int.insert(std::make_pair("two", temp));}
	{	std::vector<int> temp;	temp.push_back(4);	temp.push_back(1);	temp.push_back(12);	temp.push_back(4);	unordered_map_std_string_vector_int.insert(std::make_pair("tree", temp));}
	{	std::vector<int> temp;	temp.push_back(5);	temp.push_back(1);	temp.push_back(82);	temp.push_back(4);	unordered_map_std_string_vector_int.insert(std::make_pair("fifteen", temp));}
	{	std::vector<int> temp;	temp.push_back(7);	temp.push_back(1);	temp.push_back(22);	temp.push_back(4);	unordered_map_std_string_vector_int.insert(std::make_pair("five", temp));}
	{	std::vector<int> temp;	temp.push_back(10);	temp.push_back(21);	temp.push_back(12);	temp.push_back(34);	unordered_map_std_string_vector_int.insert(std::make_pair("eleven", temp));}

	// Declare ) unordered_map<string, ing>
	unordered_map_std_vector_string.clear();
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("zero", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("two", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("tree", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("fifteen", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("five", temp));}
	{	std::vector<char*> temp;	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	temp.push_back("zero");	unordered_map_std_vector_string.insert(std::make_pair("eleven", temp));}
}