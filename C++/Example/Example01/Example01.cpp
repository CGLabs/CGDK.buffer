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
void Sample_simple_append_front1();
void Sample_simple_append_front2();
void Sample_simple_append_front3();
void Sample_ptr1();
void Sample_stream();
void Sample_buffer_split_gather();

//----------------------------------------------------------------------------
//
//  01. CGD::buffer
//
// (주*: 아래의 예제를 Debug를 걸어 한줄 한출 실행하가면 보시면 쉬울 것입니다.)
//
//----------------------------------------------------------------------------
int main(int argc, _TCHAR* argv[])
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

	// Example 7) front로 값을 읽고 쓰기
	Sample_simple_append_front1();
	Sample_simple_append_front2();
	Sample_simple_append_front3();

	// Example 8) CGD::ptr로 읽고 쓰기
	Sample_ptr1();

	// Example 9) Stream operator로 읽고 쓰기
	Sample_stream();

	// Example 10) buffer split and gather
	Sample_buffer_split_gather();

	// 끝)
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
	char* temp_memory = new char[256];

	// Case 5) char형 메모리와 함께 Offset과 Length도 설정하기
	//         (len:100)
	CGD::buffer bufTemp4(temp_memory, 10);

	// Case 6) 생성된 CGD::buffer에서 가져온다.(얕은 복사)
	CGD::buffer bufTemp5 = bufTemp1;

	// Case 7) 생성된 기본 버퍼에서 Offset을 10만큼 더한 후 가져오기
	CGD::buffer bufTemp6 = bufTemp2 + 10;

	// Case 8) 복사본을 만든다. (깊은 복사)
	CGD::buffer bufTemp7 = bufTemp1.clone();

	// X) 메모리 동적 할당 해제
	delete bufTemp1.clear();
	delete bufTemp2.clear();
	delete temp_memory;

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
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

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
	auto temp1 = bufTemp.extract<uint8_t>();		// 10
	auto temp2 = bufTemp.extract<char>();			// 20
	auto temp3 = bufTemp.extract<int>();		// -100
	auto temp4 = bufTemp.extract<uint32_t>();		// 1000

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
//  C++에서는 char*, wchar_t, std::string, std::wstring을 문자열로 판단합니다.
//  따라서
//
//     append<char*>(...) 
//     append<wchar_t*>(...)
//     append<std::string>(...)
//     append<std::wstring>(...)
// 
//  으로 Append하면 char*로 4Byte만 포인터 값를 저장하는 것이 아니라 문자열로 판단
//  하고 문자열처리를 합니다.
//
//----------------------------------------------------------------------------
void Sample_simple_append_extract_string()
{
	// X) 메모리 동적 할당
	auto_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) 문자열을 추가한다. (1) 
	bufTemp.append<const char*>("First");		// char*형은 문자열로 판단
	bufTemp.append<const char*>("Second");		// const char*도 문자열로 판단
	bufTemp.append<string>("Thrird");			// std::string형도 문자열로 판단
	bufTemp.append("Fourth");	// 굳이 형을 쓰지 않아도 const char*형이므로 유니코드 문자열로 판단한다.

	bufTemp.append<const wchar_t*>(L"fifth");	// wchar_t*형은 유니코드 문자열로 판단
	bufTemp.append<const wchar_t*>(L"sixth");	// const wchar_t*도 유니코드 문자열로 판단
	bufTemp.append<std::wstring>(L"seventh");	// std::wstring형도 유니코드 문자열로 판단
	bufTemp.append(L"eighth");// 굳이 형을 쓰지 않아도 const wchar_t*형이므로 유니코드 문자열로 판단한다.

	bufTemp.append(CGD::_const("nineth"));// 상수 문자열의 경우 _const("TEXT")로 를 붙이면 상수문자열로 처리해 실시간 처리를 최소화할수 있습니다.

	// EXTRACT) 추가된 문자열을 뽑아낸다.

	// 설명)
	// 써넣거나 읽어들일 때 const char*나 char*나 std::string이나 모두 동일하다.
	// 따라서 동일한 문자열 코드이기만 하면 꼭 똑같은 형으로 읽어들일 필요는 없다.
	// 에를 들어 const char*, string 순서로 append한다해도 결론적으로는 문자열 2개가 추개된 것이기 때문에
	// 읽어 들일 때는 그냥 문자열을 읽어들이는 형태면 char*형이든 const char*흔 string형이든 동일하게 읽어들인다.
	// 다만 str::string이나 std::wstring은 버퍼의 스트링을 복사해서 리턴해준다.
	// 하지만 그냥 포인터형인 char*, const char*, wchar_t* const wchar_t*형은 복사를 하지 않고 버퍼중
	// 해당 문자열 위치의 포인터만 리턴해 준다. 

	// 뽑아올 때는 Template의 형을 반드시 명시주어야 한다.
	auto str1 = bufTemp.extract<const char*>();	// "First"  char*형도 문자열로 읽어들인다.(포인터만 돌려준다.)
	auto str2 = bufTemp.extract<char*>();// "Second" const char* 역시 문자열로 읽어들인다.(포인터만 돌려준다.)
	auto str3 = bufTemp.extract<char*>();// "Thrird" string형도 문자열로 받아들인다.(문자열을 복사해 준다.)
	auto str4 = bufTemp.extract<std::string>();	// "Fourth"

	auto str5 = bufTemp.extract<std::wstring>();// L"fifth" std::wsting은 유니코드 문자열로 읽어들인다.(복사를 해준다.)
	auto str6 = bufTemp.extract<wchar_t*>();		// L"sixth" 유니코드 문자열로 판단한다.
	auto str7 = bufTemp.extract<const wchar_t*>();// L"seventh" 유니코드 문자열로 판단한다.
	auto str8 = bufTemp.extract<wchar_t*>();		// L"eighth" 유니코드 문자열로 판단한다.

	auto str9 = bufTemp.extract<char*>();		// "ninth"
	// 출력)
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4.c_str() << endl;
	cout << str5.c_str() << endl;
	cout << str6 << endl;
	cout << str7 << endl;
	cout << str8 << endl;
	cout << str9 << endl;
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
	list<int> list_int {10, 20, 30, 40};
	list<string> list_string {"first","second","third"};
	map<string, int> map_int_string { {"first", 10}, {"second", 20}, {"third", 30}};
#else
	list<int> list_int;
	list_int.push_back(10);
	list_int.push_back(20);
	list_int.push_back(30);
	list_int.push_back(40);
	list<string> list_string;
	list_string.push_back("first");
	list_string.push_back("second");
	list_string.push_back("third");
	map<string, int> map_int_string;
	map_int_string.insert(make_pair("first", 10));
	map_int_string.insert(make_pair("second", 20));
	map_int_string.insert(make_pair("third", 30));
#endif

	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

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
	for (auto iter = data1.begin(); iter != data1.end(); ++iter)
	{
		cout << "[" << (*iter) << "]" << endl;
	}

	for (auto iter = data2.begin(); iter != data2.end(); ++iter)
	{
		cout << "[" << (*iter) << "]" << endl;
	}

	for (auto iter = data3.begin(); iter != data3.end(); ++iter)
	{
		cout << "[" << (*iter).first << ", " << (*iter).second << "]" << endl;
	}
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
	TEST()	{}
	TEST(int _x, float _y) : x(_x), y(_y) {}
public:
	int x;
	float y;
};

void Sample_simple_append_extract_struct()
{
	// Decalre) 임시로 사용할 List를 선언한다.
	TEST temp;
	temp.x = 10;
	temp.y = 1.0f;

	string temp_z("temp string");
#if _MSC_VER>=1800
	list<int> temp_w {10, 20, 30};
#else
	list<int> temp_w;
	temp_w.push_back(10);
	temp_w.push_back(20);
	temp_w.push_back(30);
#endif

	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>를 추가한다.
	bufTemp.append(temp);
	bufTemp.append(temp_z);
	bufTemp.append(temp_w);

	// EXTRACT) 추가했던 문자열을 읽어낸다.
	auto tempRead = bufTemp.extract<TEST>();
	string tempRead_z = bufTemp.extract<string>();
	auto tempRead_w = bufTemp.extract<list<int>>();

	// 2) 출력한다.
	cout << tempRead.x << endl;
	cout << tempRead.y << endl;
	cout << tempRead_z << endl;
	for (auto iter = tempRead_w.begin(); iter != tempRead_w.end(); ++iter)
		cout << (*iter) << endl;
	;
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
	typedef tuple
	<
	int,			// 1) x
	float,// 2) y
	string,// 3) z
	list<int>// 4) w
	>TEST_TUPPLE;

	typedef tuple
	<
	int,  // 1) a
	vector<int>,// 2) b
	TEST_TUPPLE// 3) c
	>TEST_TUPPLE_2;

			   // Decalre) 임시로 사용할 List를 선언한다.
	TEST_TUPPLE_2 temp
	(
			0,
			{	10, 20, 30},
			TEST_TUPPLE
			(
					10,
					1.0f,
					"temp string",
					{	10, 20, 30}
			)
	);

	// X) 메모리 동적 할당
	char* temp_memory = new char[256];

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp = CGD::buffer(temp_memory);

	// APPEND) List<int>를 추가한다.
	bufTemp.append(temp);

	// EXTRACT) 추가했던 문자열을 읽어낸다.
	auto tempRead = bufTemp.extract<TEST_TUPPLE_2>();

	// 2) 출력한다.
	cout<<get<0>(tempRead)<<endl;
	for(auto& iter:get<1>(tempRead)) {cout<<iter<<endl;}
	cout<<get<0>(get<2>(tempRead))<<endl;
	cout<<get<1>(get<2>(tempRead))<<endl;
	cout<<get<2>(get<2>(tempRead))<<endl;
	for(auto& iter:get<3>(get<2>(tempRead))) {cout<<iter<<endl;}

	// X) 메모리 동적 할당 해제
	delete temp_memory;
#endif
}

//----------------------------------------------------------------------------
// Example 7-1) front()로 읽기 (1)
//
//  extract()를 쓰면 읽고 난 이후에 내부적 포인터를 움직여 버린다.
//  그래서 front<T>함수를 사용하면 포인터를 움직이지 않고 읽어낼수 있다.
//  extract와 사용법 상의 차이점은 Offset을 명시해줘야 한다는 것과
//  Primitive Type(char, int, long ,... )은 레퍼런스를 얻어와 값을 직접 변경할
//  수도 있다는 것이다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front1()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) 테스트용으로 간단히 만듬
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");

	// 2) 만약 int -100을 읽어오고 싶다면...
	//    -100은 20이 써넣어진 다음에 써넣어졌으니까 버퍼의 앞에서 4Byte만큼
	//    떨어져 있다. 따라서 Offset은 4며 다음과 같이 읽어 올수 있다.
	auto temp1 = bufTemp.front<int>(4);

	// 3) 그 다음 char*로 써넣은 String을 읽어오고 싶다면
	//    Offset 8인 곳에서 읽으면 된다.
	auto temp2 = bufTemp.front<char*>(8);

	// 4)
	printf("temp1:%d  temp2:%s", temp1, temp2);
}

//----------------------------------------------------------------------------
// Example 7-2) front()로 읽기 (2)
//
//  front<T>로는 포인터를 변경시키지 않고 읽어 올수는 있지만 문제는 매번 Offset을
//  변경시켜야 한다는 것이다.
//  이건 CGD::POS를 사용하면 읽어낸마지막 위치를 받아 올수 있어서 쉽게 코딩이 가능
//  하다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front2()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) 테스트용으로 간단히 만듬
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) CGD::POS를 사용하면 읽어낸마지막 위치를 받아 올수 있다.
	//    -100의 Offset은 4Byte이다. 따라서
	CGD::POS posTemp(4);	// 초기값은 4!!!

	// 3) 숫자대신 POS형 넘긴다. 그리고 그기에 4로 설졍되어 있다면
	//    Offset 4에서 int값을 읽어들이고 읽은 후 변환 위치를
	//    postTemp에 써준다.
	//    따라서 아래 동작이 수행된 후 bufTemp의 내부 포인터는 변경되지 않았지만
	//    posTemp값은 8로 변경되었을 것이다.
	auto temp1 = bufTemp.front<int>(posTemp);

	// 4) 따라서 그 다음 값을 읽기 위해서는 그냥 그대로 다시 읽으면 된다.
	//    이러면 Offset 8인 곳에서 값을 string을 읽어오게 된다.
	auto temp2 = bufTemp.front<char*>(posTemp);

	// 5) 이렇게 되면 스트링을 읽은 후 마지막 위치가 저장되었을 것이므로
	//     그냥 또 문자열을 읽어오면 "second"라는 문자열을 읽어 올수 있다.
	auto temp3 = bufTemp.front<char*>(posTemp);

	// 확인) 값을 제대로 읽었나 찍어본다.
	cout << temp1 << endl;
	cout << temp2 << endl;
	cout << temp3 << endl;
}

//----------------------------------------------------------------------------
// Example 7-3) front()로 값쓰기
//
//  front<T>로는 값을 읽는 것뿐만 아니라 갱신해 넣을 수도 있다.
//  front<T>는 기본적으로 참조값을 받아오는 형태라 이런 것이 가능하다.
//
//  주의) front<T>로 값을 써넣으면 버퍼의 내부 포인터는 변경시키지 않으며 POS를 쓴다해도
//  POS값도 변경시키지 않는다.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front3()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) 테스트용으로 간단히 만듬
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) -100이라고 써넣은 것을 30으로 바꿔넣고 싶다!
	bufTemp.front<int>(4) = 30;

	// 3) front<T>로는 string이나 list, map과 같은 복합형에 대해서는 써넣을 수 없다.
	//    Primitive 형만 가능하다.

	// 확인) 값이 바뀌었나 찍어본다.
	cout << bufTemp.front<int>(4) << endl;
}

//----------------------------------------------------------------------------
// Example 8) CGD::ptr로 읽고 쓰기
//
// 원본 버퍼의 포인터를 변경을 해서는 안될 때 front와 같은 것을 쓰기 불편하다면
// CGD::ptr을 사용할 수도 있다.
// 이 객체는 CGD::buffer와 같이 buf와 len변수를 가진 것이 아니고 ptr로 포인터 하나만
// 가진 객체다.
// 이 객체는 그냥 ptr인데 마치 CGD::buffer와 동일한 이름으로 동작시킬수 있다.
//
//----------------------------------------------------------------------------
void Sample_ptr1()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// 2) CGD::ptr을 선언해 아래처럼 bufTemp을 ptrTmp에넣으면 bufTemp의 제일 앞 포인터가 들어간다.
	CGD::ptr ptrTmp = bufTemp;

	// 3) 아래처럼 bufTemp.begin()+10을 하면 bufTemp의 제일 앞에서 10byte 떨어진 위치의 포인터가 들어간다.
	ptrTmp = bufTemp.begin() + 10;

	// 3) 아래처럼 bufTemp.end()를 하면 bufTemp의 제일 끝이 포인터가 들어간다.
	ptrTmp = bufTemp.end();

	// APPEND1) 테스트용으로 간단히 만듬
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) "TestString"을 부분을 읽고 싶다면.. CGD::ptr을 그 위치에 놓자.
	ptrTmp = bufTemp.begin() + 8;

	// 3) CGD::buffer와 똑같이 읽거나 쓰자
	auto temp1 = ptrTmp.extract<char*>();
	auto temp2 = ptrTmp.extract<char*>();

	// 확인) 제대로 2개의 문자열을 읽었는지 확인해 본다.
	cout << temp1 << endl;
	cout << temp2 << endl;

	// 설명) append를 사용해 값을 쓸 수도 있다. 

	// 4) ptrTmp를 처음 위치에서 4Byte 떨어진 위치로 설정한다.
	ptrTmp = bufTemp.begin() + 4;

	// 5) Offset 4Byte떨어진 곳에 값을 4로 써넣었다.
	ptrTmp.append<int>(5);

	// 6) 새로운 String을 덥어써 버린다.
	//   (주의) 사실 이러면 큰일 닐수 있다! 왜냐면 원본 버퍼의 len을 변경시키지 않은체 내용값만 바꾸므로..
	//         만약 이런 식으로 쓰고 싶다면 반드시 변경된 길이를 원본 버퍼에 반영해 주길 바란다.
	ptrTmp.append<const char*>("New String");

	// 주의) 원본 버퍼의 내용을 ptrTmp를 사용해 덥어 써 버렸다.
	//       그리고 String은 길이가 다를 수 있다. 만약 원본의 스트링과 길이가 다르게 되면
	//       버퍼의 길이가 달라 추후 데이터 처리에 문제가 될수 있으므로 반드시 주의하길 바란다.
	// 새로운 길이를 구하고자 한다면 ptrTmp와 버퍼의 제일앞 위치의 차를 함으로써 구할 수 있다.
	bufTemp.len = ptrTmp - bufTemp.begin();

	// 7) 변경되었나 원본버퍼에서 읽어내보기
	auto temp3 = bufTemp.extract<int>();
	auto temp4 = bufTemp.extract<int>();
	auto temp5 = bufTemp.extract<char*>();

	// 확인) 제대로 변경했는지 확인해 본다.
	cout << temp3 << endl;
	cout << temp4 << endl;
	cout << temp5 << endl;
}

//----------------------------------------------------------------------------
// Example 9) stream operator로  읽고 쓰기
//
// C++버전의 경우 append/extract를 <<연산자나 >> 연산자를 사용해 처리할수 있다.
//
//----------------------------------------------------------------------------
void Sample_stream()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND) 값을 써 넣는다.
	bufTemp << int32_t(10) << uint32_t(200) << TEST(10, 10.0f) << "Test stream";

	// Declare) 
	int32_t temp1;
	uint32_t temp2;
	TEST temp3;
	char* temp4;

	// EXTRACT) 값을 읽어 낸다.
	bufTemp >> temp1 >> temp2 >> temp3 >> temp4;

	// 확인) 출력해 보기
	cout << temp1 << endl;
	cout << temp2 << endl;
	cout << temp3.x << ", " << temp3.y << endl;
	cout << temp4 << endl;
}

//----------------------------------------------------------------------------
// Example 10) buffer split and gather
//
// append를 수행하다 버퍼를 새로 만들어야 추가할 필요가 있는 경우가 있습니다.
// 이때 나누어진 메모리 버퍼를 합칠때 연결된 메모리라면 복사가 이루어지지 않습니다.
//
//----------------------------------------------------------------------------
void Sample_buffer_split_gather()
{
	// X) 메모리 동적 할당
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]를 생성해서 설정한다.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND) 값을 써 넣는다.
	bufTemp.append<int>(10);
	bufTemp.append<int>(30);
	bufTemp.append("Test Message");

	// 2) bufTemp2는 bufTemp끝에서부터 할당되었습니다.
	CGD::buffer bufTemp2 = bufTemp.end();

	// 3) bufTemp2에 메시지를 써넣습니다.
	bufTemp2.append<int>(40);
	bufTemp2.append<int>(80);
	bufTemp2.append("Test Message 2");

	// 4) bufTemp2를 bufTemp1뒤에 붙입니다.
	bufTemp.append(bufTemp2);

	// - 이때 bufTemp2는 bufTemp의 끝에서 시작되 연속된 메모리에 위치해 있습니다.
	//   이렇게 되면 복사를 할 필요가 없이 그냥 bufTemp의 len만 bufTemp2.len만큼
	//   늘려면 주면 됩니다. 
	//   CGD::buffer는 내부적으로 자동적으로 이런 작업을 수행해 최적화를 해줍니다.

	// 확인) 출력해 보기
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<const char*>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<const char*>() << endl;
}
