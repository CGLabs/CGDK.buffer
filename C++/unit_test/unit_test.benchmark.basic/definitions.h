#pragma once

// Common Data)
extern int															array_int[8];
extern const char*													array_string_char[8];
extern const char8_t*												array_string_char8_t[8];
extern const wchar_t*												array_string_wchar_t[8];
extern std::string													array_std_string[8];
extern std::wstring													array_std_wstring[8];
	   
extern std::vector<int>												std_vector_int;
extern std::vector<std::string>										std_vector_std_string;
extern std::vector<std::wstring>									std_vector_std_wstring;
	   
extern std::vector<std::vector<int>>								std_vector_std_vector_int;
	   
extern std::list<int>												std_list_int;
extern std::list<std::string>										std_list_std_string;
extern std::list<std::vector<int>>									std_list_std_vector_int;
	   
extern std::set<int>												std_set_int;
extern std::set<std::string>										std_set_std_string;
	   
extern std::map<int, int>											std_map_int_int;
extern std::map<std::string, int>									std_map_std_string_int;
extern std::map<std::string, std::vector<int>>						std_map_std_string_std_vector_int;
extern std::map<std::wstring, std::vector<int>>						std_map_std_wstring_std_vector_int;
extern std::map<std::string, std::vector<const char*>>				std_map_std_vector_string;
	   
extern std::unordered_map<int, int>									std_unordered_map_int_int;
extern std::unordered_map<std::string, int>							std_unordered_map_std_string_int;
extern std::unordered_map<std::string, std::vector<int>>			std_unordered_map_std_string_std_vector_int;
extern std::unordered_map<std::string, std::vector<const char*>>	std_unordered_map_std_vector_std_string;

struct FOO
{
	ENABLE_STRUCT_SERIALIZABLE

	int							v1;
	std::string					v2;
	std::list<int>				v3;
	uint64_t					v4;
	std::map<std::string, int>	v5;
};

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

inline bool compare_map_std_vector_string(const std::map<std::string, std::vector<const char*>>& lhs, const std::map<std::string, std::vector<const char*>>& rhs)
{
	auto iterX	  = lhs.begin();
	auto iterXEnd = lhs.end();
	auto iterY	  = rhs.begin();

	for(; iterX!=iterXEnd; ++iterX, ++iterY)
	{
		auto iterA	  = iterX->second.begin();
		auto iterAEnd = iterX->second.end();
		auto iterB	  = iterY->second.begin();

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

	return iterY == rhs.end();
}

void init_containers();
