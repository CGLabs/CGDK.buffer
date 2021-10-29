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
// (��*: �Ʒ��� ������ Debug�� �ɾ� ���� ���� �����ϰ��� ���ø� ���� ���Դϴ�.)
//
//----------------------------------------------------------------------------
int main(int argc, _TCHAR* argv[])
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

	// Example 7) front�� ���� �а� ����
	Sample_simple_append_front1();
	Sample_simple_append_front2();
	Sample_simple_append_front3();

	// Example 8) CGD::ptr�� �а� ����
	Sample_ptr1();

	// Example 9) Stream operator�� �а� ����
	Sample_stream();

	// Example 10) buffer split and gather
	Sample_buffer_split_gather();

	// ��)
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
	char* temp_memory = new char[256];

	// Case 5) char�� �޸𸮿� �Բ� Offset�� Length�� �����ϱ�
	//         (len:100)
	CGD::buffer bufTemp4(temp_memory, 10);

	// Case 6) ������ CGD::buffer���� �����´�.(���� ����)
	CGD::buffer bufTemp5 = bufTemp1;

	// Case 7) ������ �⺻ ���ۿ��� Offset�� 10��ŭ ���� �� ��������
	CGD::buffer bufTemp6 = bufTemp2 + 10;

	// Case 8) ���纻�� �����. (���� ����)
	CGD::buffer bufTemp7 = bufTemp1.clone();

	// X) �޸� ���� �Ҵ� ����
	delete bufTemp1.clear();
	delete bufTemp2.clear();
	delete temp_memory;

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
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

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
	auto temp1 = bufTemp.extract<uint8_t>();		// 10
	auto temp2 = bufTemp.extract<char>();			// 20
	auto temp3 = bufTemp.extract<int>();		// -100
	auto temp4 = bufTemp.extract<uint32_t>();		// 1000

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
//  C++������ char*, wchar_t, std::string, std::wstring�� ���ڿ��� �Ǵ��մϴ�.
//  ����
//
//     append<char*>(...) 
//     append<wchar_t*>(...)
//     append<std::string>(...)
//     append<std::wstring>(...)
// 
//  ���� Append�ϸ� char*�� 4Byte�� ������ ���� �����ϴ� ���� �ƴ϶� ���ڿ��� �Ǵ�
//  �ϰ� ���ڿ�ó���� �մϴ�.
//
//----------------------------------------------------------------------------
void Sample_simple_append_extract_string()
{
	// X) �޸� ���� �Ҵ�
	auto_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) ���ڿ��� �߰��Ѵ�. (1) 
	bufTemp.append<const char*>("First");		// char*���� ���ڿ��� �Ǵ�
	bufTemp.append<const char*>("Second");		// const char*�� ���ڿ��� �Ǵ�
	bufTemp.append<string>("Thrird");			// std::string���� ���ڿ��� �Ǵ�
	bufTemp.append("Fourth");	// ���� ���� ���� �ʾƵ� const char*���̹Ƿ� �����ڵ� ���ڿ��� �Ǵ��Ѵ�.

	bufTemp.append<const wchar_t*>(L"fifth");	// wchar_t*���� �����ڵ� ���ڿ��� �Ǵ�
	bufTemp.append<const wchar_t*>(L"sixth");	// const wchar_t*�� �����ڵ� ���ڿ��� �Ǵ�
	bufTemp.append<std::wstring>(L"seventh");	// std::wstring���� �����ڵ� ���ڿ��� �Ǵ�
	bufTemp.append(L"eighth");// ���� ���� ���� �ʾƵ� const wchar_t*���̹Ƿ� �����ڵ� ���ڿ��� �Ǵ��Ѵ�.

	bufTemp.append(CGD::_const("nineth"));// ��� ���ڿ��� ��� _const("TEXT")�� �� ���̸� ������ڿ��� ó���� �ǽð� ó���� �ּ�ȭ�Ҽ� �ֽ��ϴ�.

	// EXTRACT) �߰��� ���ڿ��� �̾Ƴ���.

	// ����)
	// ��ְų� �о���� �� const char*�� char*�� std::string�̳� ��� �����ϴ�.
	// ���� ������ ���ڿ� �ڵ��̱⸸ �ϸ� �� �Ȱ��� ������ �о���� �ʿ�� ����.
	// ���� ��� const char*, string ������ append�Ѵ��ص� ��������δ� ���ڿ� 2���� �߰��� ���̱� ������
	// �о� ���� ���� �׳� ���ڿ��� �о���̴� ���¸� char*���̵� const char*�� string���̵� �����ϰ� �о���δ�.
	// �ٸ� str::string�̳� std::wstring�� ������ ��Ʈ���� �����ؼ� �������ش�.
	// ������ �׳� ���������� char*, const char*, wchar_t* const wchar_t*���� ���縦 ���� �ʰ� ������
	// �ش� ���ڿ� ��ġ�� �����͸� ������ �ش�. 

	// �̾ƿ� ���� Template�� ���� �ݵ�� ����־�� �Ѵ�.
	auto str1 = bufTemp.extract<const char*>();	// "First"  char*���� ���ڿ��� �о���δ�.(�����͸� �����ش�.)
	auto str2 = bufTemp.extract<char*>();// "Second" const char* ���� ���ڿ��� �о���δ�.(�����͸� �����ش�.)
	auto str3 = bufTemp.extract<char*>();// "Thrird" string���� ���ڿ��� �޾Ƶ��δ�.(���ڿ��� ������ �ش�.)
	auto str4 = bufTemp.extract<std::string>();	// "Fourth"

	auto str5 = bufTemp.extract<std::wstring>();// L"fifth" std::wsting�� �����ڵ� ���ڿ��� �о���δ�.(���縦 ���ش�.)
	auto str6 = bufTemp.extract<wchar_t*>();		// L"sixth" �����ڵ� ���ڿ��� �Ǵ��Ѵ�.
	auto str7 = bufTemp.extract<const wchar_t*>();// L"seventh" �����ڵ� ���ڿ��� �Ǵ��Ѵ�.
	auto str8 = bufTemp.extract<wchar_t*>();		// L"eighth" �����ڵ� ���ڿ��� �Ǵ��Ѵ�.

	auto str9 = bufTemp.extract<char*>();		// "ninth"
	// ���)
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
// Example 4) Collection ����/�б�
//
//  Collection ���� �׳� append�Լ��� �Ȱ��� �а� ���� �ִ�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_extract_collection()
{
	// Decalre) �ӽ÷� ����� List�� �����Ѵ�.
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

	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

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
	TEST()	{}
	TEST(int _x, float _y) : x(_x), y(_y) {}
public:
	int x;
	float y;
};

void Sample_simple_append_extract_struct()
{
	// Decalre) �ӽ÷� ����� List�� �����Ѵ�.
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

	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp = CGD::buffer(temp_memory.get());

	// APPEND) List<int>�� �߰��Ѵ�.
	bufTemp.append(temp);
	bufTemp.append(temp_z);
	bufTemp.append(temp_w);

	// EXTRACT) �߰��ߴ� ���ڿ��� �о��.
	auto tempRead = bufTemp.extract<TEST>();
	string tempRead_z = bufTemp.extract<string>();
	auto tempRead_w = bufTemp.extract<list<int>>();

	// 2) ����Ѵ�.
	cout << tempRead.x << endl;
	cout << tempRead.y << endl;
	cout << tempRead_z << endl;
	for (auto iter = tempRead_w.begin(); iter != tempRead_w.end(); ++iter)
		cout << (*iter) << endl;
	;
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

			   // Decalre) �ӽ÷� ����� List�� �����Ѵ�.
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

	// X) �޸� ���� �Ҵ�
	char* temp_memory = new char[256];

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp = CGD::buffer(temp_memory);

	// APPEND) List<int>�� �߰��Ѵ�.
	bufTemp.append(temp);

	// EXTRACT) �߰��ߴ� ���ڿ��� �о��.
	auto tempRead = bufTemp.extract<TEST_TUPPLE_2>();

	// 2) ����Ѵ�.
	cout<<get<0>(tempRead)<<endl;
	for(auto& iter:get<1>(tempRead)) {cout<<iter<<endl;}
	cout<<get<0>(get<2>(tempRead))<<endl;
	cout<<get<1>(get<2>(tempRead))<<endl;
	cout<<get<2>(get<2>(tempRead))<<endl;
	for(auto& iter:get<3>(get<2>(tempRead))) {cout<<iter<<endl;}

	// X) �޸� ���� �Ҵ� ����
	delete temp_memory;
#endif
}

//----------------------------------------------------------------------------
// Example 7-1) front()�� �б� (1)
//
//  extract()�� ���� �а� �� ���Ŀ� ������ �����͸� ������ ������.
//  �׷��� front<T>�Լ��� ����ϸ� �����͸� �������� �ʰ� �о�� �ִ�.
//  extract�� ���� ���� �������� Offset�� �������� �Ѵٴ� �Ͱ�
//  Primitive Type(char, int, long ,... )�� ���۷����� ���� ���� ���� ������
//  ���� �ִٴ� ���̴�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front1()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) �׽�Ʈ������ ������ ����
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");

	// 2) ���� int -100�� �о���� �ʹٸ�...
	//    -100�� 20�� ��־��� ������ ��־������ϱ� ������ �տ��� 4Byte��ŭ
	//    ������ �ִ�. ���� Offset�� 4�� ������ ���� �о� �ü� �ִ�.
	auto temp1 = bufTemp.front<int>(4);

	// 3) �� ���� char*�� ����� String�� �о���� �ʹٸ�
	//    Offset 8�� ������ ������ �ȴ�.
	auto temp2 = bufTemp.front<char*>(8);

	// 4)
	printf("temp1:%d  temp2:%s", temp1, temp2);
}

//----------------------------------------------------------------------------
// Example 7-2) front()�� �б� (2)
//
//  front<T>�δ� �����͸� �����Ű�� �ʰ� �о� �ü��� ������ ������ �Ź� Offset��
//  ������Ѿ� �Ѵٴ� ���̴�.
//  �̰� CGD::POS�� ����ϸ� �о������ ��ġ�� �޾� �ü� �־ ���� �ڵ��� ����
//  �ϴ�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front2()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) �׽�Ʈ������ ������ ����
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) CGD::POS�� ����ϸ� �о������ ��ġ�� �޾� �ü� �ִ�.
	//    -100�� Offset�� 4Byte�̴�. ����
	CGD::POS posTemp(4);	// �ʱⰪ�� 4!!!

	// 3) ���ڴ�� POS�� �ѱ��. �׸��� �ױ⿡ 4�� �����Ǿ� �ִٸ�
	//    Offset 4���� int���� �о���̰� ���� �� ��ȯ ��ġ��
	//    postTemp�� ���ش�.
	//    ���� �Ʒ� ������ ����� �� bufTemp�� ���� �����ʹ� ������� �ʾ�����
	//    posTemp���� 8�� ����Ǿ��� ���̴�.
	auto temp1 = bufTemp.front<int>(posTemp);

	// 4) ���� �� ���� ���� �б� ���ؼ��� �׳� �״�� �ٽ� ������ �ȴ�.
	//    �̷��� Offset 8�� ������ ���� string�� �о���� �ȴ�.
	auto temp2 = bufTemp.front<char*>(posTemp);

	// 5) �̷��� �Ǹ� ��Ʈ���� ���� �� ������ ��ġ�� ����Ǿ��� ���̹Ƿ�
	//     �׳� �� ���ڿ��� �о���� "second"��� ���ڿ��� �о� �ü� �ִ�.
	auto temp3 = bufTemp.front<char*>(posTemp);

	// Ȯ��) ���� ����� �о��� ����.
	cout << temp1 << endl;
	cout << temp2 << endl;
	cout << temp3 << endl;
}

//----------------------------------------------------------------------------
// Example 7-3) front()�� ������
//
//  front<T>�δ� ���� �д� �ͻӸ� �ƴ϶� ������ ���� ���� �ִ�.
//  front<T>�� �⺻������ �������� �޾ƿ��� ���¶� �̷� ���� �����ϴ�.
//
//  ����) front<T>�� ���� ������� ������ ���� �����ʹ� �����Ű�� ������ POS�� �����ص�
//  POS���� �����Ű�� �ʴ´�.
// 
//----------------------------------------------------------------------------
void Sample_simple_append_front3()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND1) �׽�Ʈ������ ������ ����
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) -100�̶�� ����� ���� 30���� �ٲ�ְ� �ʹ�!
	bufTemp.front<int>(4) = 30;

	// 3) front<T>�δ� string�̳� list, map�� ���� �������� ���ؼ��� ����� �� ����.
	//    Primitive ���� �����ϴ�.

	// Ȯ��) ���� �ٲ���� ����.
	cout << bufTemp.front<int>(4) << endl;
}

//----------------------------------------------------------------------------
// Example 8) CGD::ptr�� �а� ����
//
// ���� ������ �����͸� ������ �ؼ��� �ȵ� �� front�� ���� ���� ���� �����ϴٸ�
// CGD::ptr�� ����� ���� �ִ�.
// �� ��ü�� CGD::buffer�� ���� buf�� len������ ���� ���� �ƴϰ� ptr�� ������ �ϳ���
// ���� ��ü��.
// �� ��ü�� �׳� ptr�ε� ��ġ CGD::buffer�� ������ �̸����� ���۽�ų�� �ִ�.
//
//----------------------------------------------------------------------------
void Sample_ptr1()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// 2) CGD::ptr�� ������ �Ʒ�ó�� bufTemp�� ptrTmp�������� bufTemp�� ���� �� �����Ͱ� ����.
	CGD::ptr ptrTmp = bufTemp;

	// 3) �Ʒ�ó�� bufTemp.begin()+10�� �ϸ� bufTemp�� ���� �տ��� 10byte ������ ��ġ�� �����Ͱ� ����.
	ptrTmp = bufTemp.begin() + 10;

	// 3) �Ʒ�ó�� bufTemp.end()�� �ϸ� bufTemp�� ���� ���� �����Ͱ� ����.
	ptrTmp = bufTemp.end();

	// APPEND1) �׽�Ʈ������ ������ ����
	bufTemp.append<int>(20);
	bufTemp.append<int>(-100);
	bufTemp.append<const char*>("TestString");
	bufTemp.append<const char*>("second");

	// 2) "TestString"�� �κ��� �а� �ʹٸ�.. CGD::ptr�� �� ��ġ�� ����.
	ptrTmp = bufTemp.begin() + 8;

	// 3) CGD::buffer�� �Ȱ��� �аų� ����
	auto temp1 = ptrTmp.extract<char*>();
	auto temp2 = ptrTmp.extract<char*>();

	// Ȯ��) ����� 2���� ���ڿ��� �о����� Ȯ���� ����.
	cout << temp1 << endl;
	cout << temp2 << endl;

	// ����) append�� ����� ���� �� ���� �ִ�. 

	// 4) ptrTmp�� ó�� ��ġ���� 4Byte ������ ��ġ�� �����Ѵ�.
	ptrTmp = bufTemp.begin() + 4;

	// 5) Offset 4Byte������ ���� ���� 4�� ��־���.
	ptrTmp.append<int>(5);

	// 6) ���ο� String�� ����� ������.
	//   (����) ��� �̷��� ū�� �Ҽ� �ִ�! �ֳĸ� ���� ������ len�� �����Ű�� ����ü ���밪�� �ٲٹǷ�..
	//         ���� �̷� ������ ���� �ʹٸ� �ݵ�� ����� ���̸� ���� ���ۿ� �ݿ��� �ֱ� �ٶ���.
	ptrTmp.append<const char*>("New String");

	// ����) ���� ������ ������ ptrTmp�� ����� ���� �� ���ȴ�.
	//       �׸��� String�� ���̰� �ٸ� �� �ִ�. ���� ������ ��Ʈ���� ���̰� �ٸ��� �Ǹ�
	//       ������ ���̰� �޶� ���� ������ ó���� ������ �ɼ� �����Ƿ� �ݵ�� �����ϱ� �ٶ���.
	// ���ο� ���̸� ���ϰ��� �Ѵٸ� ptrTmp�� ������ ���Ͼ� ��ġ�� ���� �����ν� ���� �� �ִ�.
	bufTemp.len = ptrTmp - bufTemp.begin();

	// 7) ����Ǿ��� �������ۿ��� �о����
	auto temp3 = bufTemp.extract<int>();
	auto temp4 = bufTemp.extract<int>();
	auto temp5 = bufTemp.extract<char*>();

	// Ȯ��) ����� �����ߴ��� Ȯ���� ����.
	cout << temp3 << endl;
	cout << temp4 << endl;
	cout << temp5 << endl;
}

//----------------------------------------------------------------------------
// Example 9) stream operator��  �а� ����
//
// C++������ ��� append/extract�� <<�����ڳ� >> �����ڸ� ����� ó���Ҽ� �ִ�.
//
//----------------------------------------------------------------------------
void Sample_stream()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND) ���� �� �ִ´�.
	bufTemp << int32_t(10) << uint32_t(200) << TEST(10, 10.0f) << "Test stream";

	// Declare) 
	int32_t temp1;
	uint32_t temp2;
	TEST temp3;
	char* temp4;

	// EXTRACT) ���� �о� ����.
	bufTemp >> temp1 >> temp2 >> temp3 >> temp4;

	// Ȯ��) ����� ����
	cout << temp1 << endl;
	cout << temp2 << endl;
	cout << temp3.x << ", " << temp3.y << endl;
	cout << temp4 << endl;
}

//----------------------------------------------------------------------------
// Example 10) buffer split and gather
//
// append�� �����ϴ� ���۸� ���� ������ �߰��� �ʿ䰡 �ִ� ��찡 �ֽ��ϴ�.
// �̶� �������� �޸� ���۸� ��ĥ�� ����� �޸𸮶�� ���簡 �̷������ �ʽ��ϴ�.
//
//----------------------------------------------------------------------------
void Sample_buffer_split_gather()
{
	// X) �޸� ���� �Ҵ�
	unique_ptr<char> temp_memory(new char[256]);

	// 1) byte[256]�� �����ؼ� �����Ѵ�.
	CGD::buffer bufTemp(temp_memory.get());

	// APPEND) ���� �� �ִ´�.
	bufTemp.append<int>(10);
	bufTemp.append<int>(30);
	bufTemp.append("Test Message");

	// 2) bufTemp2�� bufTemp���������� �Ҵ�Ǿ����ϴ�.
	CGD::buffer bufTemp2 = bufTemp.end();

	// 3) bufTemp2�� �޽����� ��ֽ��ϴ�.
	bufTemp2.append<int>(40);
	bufTemp2.append<int>(80);
	bufTemp2.append("Test Message 2");

	// 4) bufTemp2�� bufTemp1�ڿ� ���Դϴ�.
	bufTemp.append(bufTemp2);

	// - �̶� bufTemp2�� bufTemp�� ������ ���۵� ���ӵ� �޸𸮿� ��ġ�� �ֽ��ϴ�.
	//   �̷��� �Ǹ� ���縦 �� �ʿ䰡 ���� �׳� bufTemp�� len�� bufTemp2.len��ŭ
	//   �÷��� �ָ� �˴ϴ�. 
	//   CGD::buffer�� ���������� �ڵ������� �̷� �۾��� ������ ����ȭ�� ���ݴϴ�.

	// Ȯ��) ����� ����
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<const char*>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<int>() << endl;
	cout << bufTemp.extract<const char*>() << endl;
}
