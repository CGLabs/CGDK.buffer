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
	// Example 1) �پ��� ������ ���� ��� 
	Sample_simple_creation_copy();

	// Example 2) ���� �⺻���� ���� ����� �б�
	Sample_simple_append_extract();

	// Example 3) ���ڿ� ����/�б�
	Sample_simple_append_extract_string();

	// Example 4) Collection ����/�б�
	Sample_simple_append_extract_collection();

	// Example 5) struct(No! Heterogenous Type) ����/�б� (1)
	//            (C#ó�� struc�� Heterogenouse type���� �������� �ʴ´�.)
	Sample_simple_append_extract_struct();

	// Example 6) �ٰ���(Multiple-Layerd) tuple ����/�б�
	Sample_simple_append_extract_struct2();

	return 0;
}


//----------------------------------------------------------------------------
// Example 1) �پ��� ������ ���� ��� 
//  
//----------------------------------------------------------------------------
void Sample_simple_creation_copy()
{
	// Case 1) 256 Byte�� �޸𸮸� �Ҵ��� buffer�� �����Ѵ�.
	CGD::buffer bufTemp1(new char[256]);

	// Case 2) ���� �� �Ҵ��ϱ�
	CGD::buffer bufTemp2;

	bufTemp2.set_buffer(new char[256]);

	// Case 3) CGPool�� ���� ���
	//CGD::buffer buffer 3 = MEM_POOL_Alloc(256);

	// X) �޸� ���� �Ҵ�
	char*	temp_memory	 = new char[256];

	// Case 5) char�� �޸𸮿� �Բ� Offset�� Length�� �����ϱ�
	//         (len:100)
	CGD::buffer bufTemp4 (temp_memory, 10);

	// Case 6) ������ CGD::buffer���� �����´�.(���� ����)
	CGD::buffer bufTemp5 = bufTemp1;

	// Case 7) ������ �⺻ ���ۿ��� Offset�� 10��ŭ ���� �� ��������
	CGD::buffer bufTemp6 = bufTemp2 + 10;


	// Case 8) ���纻�� �����. (���� ����)
	CGD::buffer bufTemp7	 = bufTemp1.clone();

	// X) �޸� ���� �Ҵ� ����
	delete	bufTemp1.clear();
	delete	bufTemp2.clear();
	delete	temp_memory;

	// * ���� ���� �Ҵ翡 ����...
	//   ���⼭�� �������� malloc Ȥ�� new�� ���� �޸𸮸� �Ҵ��ϰ� �������� �Ҵ����� �ϴٷ� �ۼ��ߴ�.
	//   ���۷��� ī���� ����� �߰��� CCGBuffer������ �޸� ������ �Ű澵 �ʿ�� ����.
	//   �� ������ CGPTR<T>Ŭ�������� CGD::buffer���� ���Ե��� �ʾұ⿡ ���ܽ��״�.
}

// Example 2) ���� �⺻���� ���� ����� �б�
//
//  append<T> �Լ��� ����Ͽ� ������ ���� T�� ���� ����� �� �ִ�.
//  extract<T> �Լ��� ����Ͽ� ���ۿ� ���� �տ������� T�� ���� �о�� �� �ִ�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract()
{
	// X) �޸� ���� �Ҵ�
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer	bufTemp(temp_memory.get());

	// APPEND) �⺻���� ������ ��ִ´�.
	bufTemp.append<uint8_t>(10);
	bufTemp.append<char>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<uint32_t>(1000);

	// * ������� append�� ���������� �� 14Byte�� ������
	//   Count ���� 14�� �ȴ�. Offset�� ������ 0������ 
	// * append�Ҷ� �ٿ��� <T>���ٴ� ������ ���� ���� ��������.

	// EXTRACT) ���� �Ͼ��.
	//    - ���� �о�� �Ǹ� Offset������ ���� �о�� �ǰ� Offset���� �о ũ�� ������Ų��.
	auto	temp1	 = bufTemp.extract<uint8_t>();		// 10
	auto	temp2	 = bufTemp.extract<char>();			// 20
	auto	temp3	 = bufTemp.extract<int>();		// -100
	auto	temp4	 = bufTemp.extract<uint32_t>();		// 1000

	// Ȯ��)
	printf("temp1:%d temp2:%d temp3:%d temp4:%d\n", temp1, temp2, temp3, temp4);
}
//----------------------------------------------------------------------------
// Example 3) ���ڿ� ����/�б�
//
//  ���� append<string> �Լ��� ����Ͽ� ������ ���� string�� ���� ���� �ִ�.
//  ���� <string>�� �� �ʿ䰡 ������ �ڵ��� �������� ���� �ٿ� �ִ� ��찡 ����.
//  
//  ���� ���� extract<string> �Լ��� ����Ͽ� ���� �� �ִ�.
//  ���⼭�� �ݵ�� ���ø� ������ <string>�� ���־�� �Ѵ�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_string()
{
	// X) �޸� ���� �Ҵ�
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer	bufTemp(temp_memory.get());

	// APPEND1) ���ڿ��� �߰��Ѵ�. (1) 
	bufTemp.append<string>("First test String");

	// APPEND2) ���ڿ��� �߰��Ѵ�. ���� <string>�� �� �ʿ�� ����.(2) 
	bufTemp.append("Second");

	// Declare) �ӽ÷� ���ڿ� ������ �����.
	string	tempString	 = "Third";

	// APPEND3) ���ڿ��� �߰��Ѵ�. ���� <string>�� �� �ʿ�� ����.(2) 
	bufTemp.append(tempString);


	// EXTRACT) �߰��� ���ڿ��� �̾Ƴ���.
	auto	str1 = bufTemp.extract<string>();	// "First test String"
	auto	str2 = bufTemp.extract<string>();	// "Second"
	auto	str3 = bufTemp.extract<string>();	// "Third"

	// Ȯ��)
	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
}

//----------------------------------------------------------------------------
// Example 4) Collection ����/�б�
//
//  Collection ���� �׳� append�Լ��� �Ȱ��� �а� ���� �ִ�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_collection()
{
	// Decalre) �ӽ÷� ����� List�� �����Ѵ�.
#if _MSC_VER>=1800
	list<int>			list_int		{ 10, 20, 30, 40};
	list<string>		list_string		{ "first","second","third"};
	map<string, int>	map_int_string	{ {"first", 10}, {"second", 20}, {"third", 30}};
#else
	list<int>			list_int;		list_int.push_back(10); list_int.push_back(20); list_int.push_back(30); list_int.push_back(40);
	list<string>		list_string;	list_string.push_back("first"); list_string.push_back("second"); list_string.push_back("third");
	map<string, int>	map_int_string;	map_int_string.insert(make_pair("first", 10)); map_int_string.insert(make_pair("second", 20)); map_int_string.insert(make_pair("third", 30));
#endif

	// X) �޸� ���� �Ҵ�
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>�� �߰��Ѵ�.
	bufTemp.append(list_int);
	bufTemp.append(list_string);
	bufTemp.append(map_int_string);

	// EXTRACT) �߰��ߴ� ���ڿ��� �о��.
	auto data1 = bufTemp.extract<list<int>>();
	auto data2 = bufTemp.extract<list<string>>();
	auto data3 = bufTemp.extract<map<string, int>>();

	// 2) ����Ѵ�.
	for(auto& iter:data1)	{ cout<<iter<<endl;}
	for(auto& iter:data2)	{ cout<<iter<<endl;}
	for(auto& iter:data3)	{ cout<<"["<<iter.first<<", "<<iter.second<<"]"<<endl;}
}


//----------------------------------------------------------------------------
// Example 5) struct(primitive Type) ����/�б� (1)
//
//  ����ü�� �б�/���� ���� �����ϴ�. �׳� ���� ����� �� append/extract�� �����
//  �а� ���� �ִ�.
//  ������ C++���� ����ü�� C#ó�� ������� ���� ���� append�� extract�� �����ϴ� 
//  ���� �ƴ϶� �׳� primitive type���� ����� ���縦 �����Ѵ�.
//  (struct�� c#�� ���� ó���ϱ� ���ؼ��� �ٸ�ó���� �ʿ��ϴ�.)
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
	// Decalre) �ӽ÷� ����� List�� �����Ѵ�.
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

	// X) �޸� ���� �Ҵ�
	auto_ptr<char>	temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>�� �߰��Ѵ�.
	bufTemp.append(temp);
	bufTemp.append(temp_z);
	bufTemp.append(temp_w);
	

	// EXTRACT) �߰��ߴ� ���ڿ��� �о��.
	auto	tempRead	= bufTemp.extract<TEST>();
	string	tempRead_z = bufTemp.extract<string>();
	auto	tempRead_w = bufTemp.extract<list<int>>();

	// 2) ����Ѵ�.
	cout<<tempRead.x<<endl;
	cout<<tempRead.y<<endl;
	cout<<tempRead_z<<endl;
	for(auto& iter:tempRead_w) { cout<<iter<<endl; }
}

//----------------------------------------------------------------------------
// Example 6) tuple (Heterogenous Type) ����/�б� (1)
//
//  C++���� �������� ó���� tuple�� ���ؼ� �����ϴ�.
//  �ٸ� tuple�� struct�� �ͼ��� ����ڿ��� �ټ� �����ϰ� C#�� ������ �ڵ�� �ۼ���
//  ���� ������ �־� �� ��������� �ʴ´�.
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


	// Decalre) �ӽ÷� ����� List�� �����Ѵ�.
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

	// X) �޸� ���� �Ҵ�
	char*	temp_memory	 = new char[256];

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp = CGD::buffer(temp_memory);

	// APPEND) List<int>�� �߰��Ѵ�.
	bufTemp.append(temp);


	// EXTRACT) �߰��ߴ� ���ڿ��� �о��.
	auto	tempRead	= bufTemp.extract<TEST_TUPPLE_2>();

	// 2) ����Ѵ�.
	//cout<<tempRead.x<<endl;
	//cout<<tempRead.y<<endl;
	//cout<<tempRead_z<<endl;
	//for(auto& iter:tempRead_w) { cout<<iter<<endl; }

	// X) �޸� ���� �Ҵ� ����
	delete	temp_memory;
#endif
}