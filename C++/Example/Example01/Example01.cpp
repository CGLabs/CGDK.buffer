// Example01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <vector>
#include <list>
#include <map>
#include <string>
#include <CGDbuffer>
#include <memory>

using namespace std;

void Sample_simple_creation_copy();
void Sample_simple_append_extract();
void Sample_simple_append_extract_string();
void Sample_simple_append_extract_collection();
void Sample_simple_append_extract_struct();
void Sample_simple_append_extract_struct2();

int _tmain(int argc, _TCHAR* argv[])
{
	// Example 1) 다양한 형태의 생성 방법 
	Sample_simple_creation_copy();

	// Example 2) 가장 기본적인 형의 쓰기와 읽기
	Sample_simple_append_extract();

	// Example 3) 문자열 쓰기/읽기
	Sample_simple_append_extract_string();

	// Example 4) Collection 쓰기/읽기
	Sample_simple_append_extract_collection();

	// Example 5) struct(No! Heterogenous Type) 쓰기/읽기 (1)
	//            (C#처럼 struc로 Heterogenouse type으로 동작하지 않는다.)
	Sample_simple_append_extract_struct();

	// Example 6) 다계층(Multiple-Layerd) tuple 쓰기/읽기
	Sample_simple_append_extract_struct2();

	return 0;
}


//----------------------------------------------------------------------------
// Example 1) 다양한 형태의 생성 방법 
//  
//----------------------------------------------------------------------------
void Sample_simple_creation_copy()
{
	// Case 1) 256 Byte의 메모리를 할당해 buffer를 선언한다.
	CGD::buffer bufTemp1(new char[256]);

	// Case 2) 선언 후 할당하기
	CGD::buffer bufTemp2;

	bufTemp2.set_buffer(new char[256]);

	// Case 3) CGPool이 있을 경우
	//CGD::buffer buffer 3 = MEM_POOL_Alloc(256);

	// X) 메모리 동적 할당
	char*	temp_memory	 = new char[256];

	// Case 5) char형 메모리와 함께 Offset과 Length도 설정하기
	//         (len:100)
	CGD::buffer bufTemp4 (temp_memory, 10);

	// Case 6) 생성된 CGD::buffer에서 가져온다.(얕은 복사)
	CGD::buffer bufTemp5 = bufTemp1;

	// Case 7) 생성된 기본 버퍼에서 Offset을 10만큼 더한 후 가져오기
	CGD::buffer bufTemp6 = bufTemp2 + 10;


	// Case 8) 복사본을 만든다. (깊은 복사)
	CGD::buffer bufTemp7	 = bufTemp1.clone();

	// X) 메모리 동적 할당 해제
	delete	bufTemp1.clear();
	delete	bufTemp2.clear();
	delete	temp_memory;

	// * 동적 버퍼 할당에 대해...
	//   여기서는 수동으로 malloc 혹은 new를 통해 메모리를 할당하고 수동으로 할당해제 하다록 작성했다.
	//   레퍼런스 카운팅 기능을 추가한 CCGBuffer에서는 메모리 해제를 신경쓸 필요는 없다.
	//   그 예제는 CGPTR<T>클래스등이 CGD::buffer에는 포함되지 않았기에 제외시켰다.
}

// Example 2) 가장 기본적인 형의 쓰기와 읽기
//
//  append<T> 함수를 사용하여 버퍼의 끝에 T형 값을 써넣을 수 있다.
//  extract<T> 함수를 사용하여 버퍼에 제일 앞에서부터 T형 값을 읽어올 수 있다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract()
{
	// X) 메모리 동적 할당
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer	bufTemp(temp_memory.get());

	// APPEND) 기본적인 값들을 써넣는다.
	bufTemp.append<uint8_t>(10);
	bufTemp.append<char>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<uint32_t>(1000);

	// * 여기까지 append를 수행했으면 총 14Byte가 쓰여져
	//   Count 값은 14가 된다. Offset은 여전히 0이지만 
	// * append할때 붙여진 <T>보다는 쓰여진 값에 따라 쓰여진다.

	// EXTRACT) 값을 일어낸다.
	//    - 값을 읽어내게 되면 Offset값부터 값을 읽어내게 되고 Offset값을 읽어낸 크기 증가시킨다.
	auto	temp1	 = bufTemp.extract<uint8_t>();		// 10
	auto	temp2	 = bufTemp.extract<char>();			// 20
	auto	temp3	 = bufTemp.extract<int>();		// -100
	auto	temp4	 = bufTemp.extract<uint32_t>();		// 1000

	// 확인)
	printf("temp1:%d temp2:%d temp3:%d temp4:%d\n", temp1, temp2, temp3, temp4);
}
//----------------------------------------------------------------------------
// Example 3) 문자열 쓰기/읽기
//
//  역시 append<string> 함수를 사용하여 버퍼의 끝에 string형 값을 쓸수 있다.
//  굳이 <string>을 쓸 필요가 없지만 코드의 가독성을 위해 붙여 주는 경우가 많다.
//  
//  읽을 때는 extract<string> 함수를 사용하여 읽을 수 있다.
//  여기서는 반드시 템플릿 인자인 <string>를 써주어야 한다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_string()
{
	// X) 메모리 동적 할당
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer	bufTemp(temp_memory.get());

	// APPEND1) 문자열을 추가한다. (1) 
	bufTemp.append<string>("First test String");

	// APPEND2) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
	bufTemp.append("Second");

	// Declare) 임시로 문자열 변수를 만든다.
	string	tempString	 = "Third";

	// APPEND3) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
	bufTemp.append(tempString);


	// EXTRACT) 추가된 문자열을 뽑아낸다.
	auto	str1 = bufTemp.extract<string>();	// "First test String"
	auto	str2 = bufTemp.extract<string>();	// "Second"
	auto	str3 = bufTemp.extract<string>();	// "Third"

	// 확인)
	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
}

//----------------------------------------------------------------------------
// Example 4) Collection 쓰기/읽기
//
//  Collection 역시 그냥 append함수로 똑같이 읽고 쓸수 있다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_collection()
{
	// Decalre) 임시로 사용할 List를 선언한다.
#if _MSC_VER>=1800
	list<int>			list_int		{ 10, 20, 30, 40};
	list<string>		list_string		{ "first","second","third"};
	map<string, int>	map_int_string	{ {"first", 10}, {"second", 20}, {"third", 30}};
#else
	list<int>			list_int;		list_int.push_back(10); list_int.push_back(20); list_int.push_back(30); list_int.push_back(40);
	list<string>		list_string;	list_string.push_back("first"); list_string.push_back("second"); list_string.push_back("third");
	map<string, int>	map_int_string;	map_int_string.insert(make_pair("first", 10)); map_int_string.insert(make_pair("second", 20)); map_int_string.insert(make_pair("third", 30));
#endif

	// X) 메모리 동적 할당
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>를 추가한다.
	bufTemp.append(list_int);
	bufTemp.append(list_string);
	bufTemp.append(map_int_string);

	// EXTRACT) 추가했던 문자열을 읽어낸다.
	auto data1 = bufTemp.extract<list<int>>();
	auto data2 = bufTemp.extract<list<string>>();
	auto data3 = bufTemp.extract<map<string, int>>();

	// 2) 출력한다.
	for(auto& iter:data1)	{ cout<<iter<<endl;}
	for(auto& iter:data2)	{ cout<<iter<<endl;}
	for(auto& iter:data3)	{ cout<<"["<<iter.first<<", "<<iter.second<<"]"<<endl;}
}


//----------------------------------------------------------------------------
// Example 5) struct(primitive Type) 쓰기/읽기 (1)
//
//  구조체의 읽기/쓰기 역시 동일하다. 그냥 값을 써넣은 후 append/extract를 사용해
//  읽고 쓸수 있다.
//  하지만 C++에서 구조체는 C#처럼 멤버들의 형에 따라 append나 extract를 수행하는 
//  것이 아니라 그냥 primitive type으로 취급해 복사를 수행한다.
//  (struct를 c#과 같이 처리하기 위해서는 다른처리가 필요하다.)
// 
//----------------------------------------------------------------------------
struct TEST
{
public:
	int			x;
	float		y;
};

void Sample_simple_append_extract_struct()
{
	// Decalre) 임시로 사용할 List를 선언한다.
	TEST	temp;
	temp.x	 = 10;
	temp.y	 = 1.0f;

	string	temp_z("temp string");
#if _MSC_VER>=1800
	list<int>	temp_w;
	temp_w.push_back({ 10, 20, 30});
#else
	list<int>	temp_w;
	temp_w.push_back(10); temp_w.push_back(20); temp_w.push_back(30);
#endif

	// X) 메모리 동적 할당
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>를 추가한다.
	bufTemp.append(temp);
	bufTemp.append(temp_z);
	bufTemp.append(temp_w);
	

	// EXTRACT) 추가했던 문자열을 읽어낸다.
	auto	tempRead	= bufTemp.extract<TEST>();
	string	tempRead_z = bufTemp.extract<string>();
	auto	tempRead_w = bufTemp.extract<list<int>>();

	// 2) 출력한다.
	cout<<tempRead.x<<endl;
	cout<<tempRead.y<<endl;
	cout<<tempRead_z<<endl;
	for(auto& iter:tempRead_w) { cout<<iter<<endl; }
}

//----------------------------------------------------------------------------
// Example 6) tuple (Heterogenous Type) 쓰기/읽기 (1)
//
//  C++에서 복합형을 처리는 tuple을 통해서 가능하다.
//  다만 tuple을 struct에 익숙한 사용자에게 다소 불편하고 C#과 동일한 코드로 작성이
//  힘든 단점이 있어 잘 사용하지는 않는다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_struct2()
{
#if _MSC_VER>=1800
	typedef	tuple
		<
		int,			// 1) x
		float,			// 2) y
		string,			// 3) z
		list<int>		// 4) w
		>TEST_TUPPLE;

	typedef	tuple
		<
		int,			// 1) a
		vector<int>,	// 2) b
		TEST_TUPPLE		// 3) c
		>TEST_TUPPLE_2;


	// Decalre) 임시로 사용할 List를 선언한다.
	TEST_TUPPLE_2	temp
	(
		0,
		{10, 20, 30},
		TEST_TUPPLE
		(
			10,
			1.0f,
			"temp string",
			{ 10, 20, 30}
		)
	);

	// X) 메모리 동적 할당
	char*	temp_memory	 = new char[256];

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp = CGD::buffer(temp_memory);

	// APPEND) List<int>를 추가한다.
	bufTemp.append(temp);


	// EXTRACT) 추가했던 문자열을 읽어낸다.
	auto	tempRead	= bufTemp.extract<TEST_TUPPLE_2>();

	// 2) 출력한다.
	//cout<<tempRead.x<<endl;
	//cout<<tempRead.y<<endl;
	//cout<<tempRead_z<<endl;
	//for(auto& iter:tempRead_w) { cout<<iter<<endl; }

	// X) 메모리 동적 할당 해제
	delete	temp_memory;
#endif
}