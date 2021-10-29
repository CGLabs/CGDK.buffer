#pragma once


// Definitions) 
#define	_TEST_COUNT	10
#define	_ENABLE_ASSERT

// Common Data)
extern	int													array_int[8];
extern	char*												array_string_char[8];
extern	wchar_t*											array_string_wchar_t[8];
extern	std::string											array_std_string_stdstring[8];
extern	std::wstring										array_std_string_stdwstring[8];

extern	std::vector<int>									vector_int;
extern	std::vector<std::string>							vector_std_string;
extern	std::vector<std::vector<int>>						vector_vector_int;

extern	std::list<int>										list_int;
extern	std::list<std::string>								list_std_string;
extern	std::list<std::vector<int>>							list_vector_int;

extern	std::set<int>										set_int;
extern	std::set<std::string>								set_std_string;

extern	std::map<int, int>									map_std_int_int;
extern	std::map<std::string, int>							map_std_string_int;
extern	std::map<std::string, std::vector<int>>				map_std_string_vector_int;
extern	std::map<std::string, std::vector<char*>>			map_std_vector_string;

#if _MSC_VER>=1700
extern	std::unordered_map<int, int>						unordered_map_std_int_int;
extern	std::unordered_map<std::string, int>				unordered_map_std_string_int;
extern	std::unordered_map<std::string, std::vector<int>>	unordered_map_std_string_vector_int;
extern	std::unordered_map<std::string, std::vector<char*>>	unordered_map_std_vector_string;
#endif

template<class T>
bool compare_array_string(T* lhs[], T* rhs[], int _Count)
{
	for(int i=0; i<_Count; ++i)
	{
		if(std::char_traits<T>::compare(lhs[i], rhs[i], 0)!=0) 
		{
			return	false;
		}
	}

	return	true;
}

inline bool compare_map_std_vector_string(const std::map<std::string, std::vector<char*>>& lhs, const std::map<std::string, std::vector<char*>>& rhs)
{
	auto	iterX		 = lhs.begin();
	auto	iterXEnd	 = lhs.end();
	auto	iterY		 = rhs.begin();

	for(; iterX!=iterXEnd; ++iterX, ++iterY)
	{
		auto	iterA		 = iterX->second.begin();
		auto	iterAEnd	 = iterX->second.end();
		auto	iterB		 = iterY->second.begin();

		for(; iterA!=iterAEnd; ++iterA, ++iterB)
		{
			if(std::char_traits<char>::compare(*iterA, *iterB, 0)!=0)
			{
				return	false;
			}
		}

		if(iterB!=iterY->second.end())
			return	false;
	}

	return	iterY==rhs.end();
}

void InitContainers();
