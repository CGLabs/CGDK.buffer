## CGDK::buffer란
CGDK::buffer는 메시지 직렬화 버퍼 시스템입니다.
C++버전은 CGDK::buffer이며 C# 버전은 CGDK.buffer입니다.

### CGD::buffer
   - 매우 간단합니다.(사실상 append/extract/front가 전부...)
   - 매우 빠릅니다. (c++ 버전은 tmp로 구현되어 압도적 최강의 성능을 자랑합니다.)
   - 매우 작고 가볍습니다.
   - Schemaless와 Schema(구조체 직렬화)를 지원합니다.
   - 특별한 설정이나 특별한 스크립트(IDL)없이 구조체를 Schema로 그사용 가능합니다.
   - C++은 C++11 Template Meta Programming을 사용해 구현해 10% template으로만 구현 되어 Include만으로 사용 가능합니다.
   - 자료형에 따라 직렬화를 수행합니다.
   - 지원되는 자료형은
      * 기본 자료형(char,int32_t, ... float, double)
      * ENUM
      * 문자열(char*, wchar_t*, std::string, std::wstring, std_string_view, ...)
      * 배열(T[N], std::array<T,N>)
      * 컨테이너(std::vector<T>, std::list<T>, std::set<T>,std::map<K,V>, ...)
      * 시간(chrono::time_stamp, chrono::duration, ...) 
      * 포인터(std::shared_ptr<T>, std::unique_ptr<T>)
      * buffer (CGDK::buffer_veiew, CGDK::buffer,CGDK::shared_buffer)
      * struct
      * Ibuffer_serialzable
      * 기타...

### CGD.buffer
   - C#버전
   - Reflection을 사용하여 구현하였습니다.
   - C++ 버전화 호환됩니다.

## buffer의 종류
3종류의 buffer를 제공하고 있으며 모두 상속 관계에 있습니다.
### CGDK::buffer_view
* data_와 size_만 가진 buffer로 읽기나 덥어쓰기만 가능합니다.
* 'extract<T>' 함수(읽어내기)
* 'front<T>' 함수(읽기와 덥어 쓰기)
### CGDK::buffer
* CGDK::buffer_view를 상속받아 경계정보(boung_info)를 추가한 버퍼 클래스입니다.
* 'append<T>'함수로 붙히기를 지원합니다.
### CGDK::shared_buffer
* CGDK::buffer를 상속 받아 스마트 포인터 기능을 더한 버퍼 클래스입니다.
* 할당된 원본 버퍼를 스마트포인터로 관리합니다.
* alloc_shared_buffer(SIZE) 혹은 make_shared_buffer<T>를 사용해 버퍼를 할당 받을 수 있습니다.


## CGD::buffer사용하기
### 직렬화하기(Schemaless)  
``` C++
  buf.append<[TYPE]>([value]);
```
* 버퍼에 데이터를 버퍼에 쓰기는 간단히 append<T>()로 가능합니다.
* TYPE를 생략할 경우 입력되는 값의 자료형으로 간주합니다.
    
``` C++
CGD::buffer bufTemp(malloc(256));
       
bufTemp.append<uint8_t>(10);
bufTemp.append<char>(20);
bufTemp.append<int>(-100);
bufTemp.append<uint32_t>(1000);
bufTemp.append<std::string>("Test String"); // 문자열도 가능
```
``` C#
CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
       
bufTemp.append<byte>(10);
bufTemp.append<sbyte>(20);
bufTemp.append<int>(-100);
bufTemp.append<uint>(1000);
bufTemp.append<string>("Test String");	// 문자열도 가능
```

### 역직렬화하기(Schemaless)

``` C++
  [value] buf.extract<[TYPE]>();
```
* 작성된 메시지는 extract()로 간단히 읽어낼 수가 있습니다.
* 버퍼 제일 앞에서 TYPE형으로 데이터를 역직렬화를 합니다.

``` C++
auto temp1 = bufTemp.extract<uint8_t>();
auto temp2 = bufTemp.extract<char>();
auto temp3 = bufTemp.extract<int>();
auto temp4 = bufTemp.extract<uint32_t>();
auto temp5 = bufTemp.extract<std::string>();
```
``` C#
var temp1 = bufTemp.extract<byte>();
var temp2 = bufTemp.extract<SByte>();
var temp3 = bufTemp.extract<int>();
var temp4 = bufTemp.extract<uint>();
var temp5 = bufTemp.extract<string>();
```

* 복합형 데이터의 직렬화 역직렬화도 가능합니다.
C++의 vector<T>, list<T>, set<T>, map<T> ....
C#의 List<T>, Dictionary<K,V> ...

``` C++
std::vector<int>                  listTest = { ...};
std::list<std::string>            listStringTest = { ...};
std::map<std::string, int>        mapTemp = { ...};
std::map<int, list<std::string>>  maplistTemp = { ...};
	    
CGD::buffer bufTemp(malloc(256));
	    
bufTemp.append<std::vector<int>>(listTest);
bufTemp.append<std::list<std::string>>(listStringTest);
bufTemp.append<map<std::std::string, int>>(mapTemp);
bufTemp.append<map<int, std::list<std::string>>>(maplistTemp);
	    
.................
	    
auto temp1 = bufTemp.extract<std::vector<int>>();
auto temp2 = bufTemp.extract<std::list<std::string>>();
auto temp3 = bufTemp.extract<std::map<int, std::string>>();
auto temp4 = bufTemp.extract<std::map<int, std::list<std::string>>>();
```
``` C#
List<int>                      listTest = new ...;
List<string>                   listStringTest = new ...;
Dictionary<string, int>        dicTest = new ...;
Dictionary<int, List<string>>  dicListTest = new ...;
       
CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
       
bufTemp.append<List<int>> (listTest);
bufTemp.append<List<string>> (listStringTest);
bufTemp.append<Dictionary<string,int>> (dicTest);
bufTemp.append<Dictionary<string,List<int>>> (dicListTest);
       
.................
       
var temp1 = bufTemp.extract<List<int>> ();
var temp2 = bufTemp.extract<List<string>> ();
var temp3 = bufTemp.extract<Dictionary<string,int>> ();
var temp4 = bufTemp.extract<Dictionary<string,List<int>>> ();

bufTemp.append(maplistTemp);
```

### 직렬화에 필요한 메모리 구하기
``` C++
auto size = CGDK::get_size_of(maplistTemp);
```
* 데이터를 직렬화 했을 때의 메모리 크기를 CGDK::get_size_of()르 사용해 얻을 수 있습니다.

### buffer에 메모리 동적 할당 받기
* CGDK::alloc_shared_buffer([SIZE])를 사용해 메모리를 동적 할당 받을 수 있습니다.
* CGD::shared_buffer로 할당받은 버퍼를 받을 수 있으며 스마트 포인터로 관리되므로 참조가 모두 끝나면 자동 할당해제됩니다.

``` C++
// 1000byte 메모리를 동적 할당 받는다.
auto temp1 = CGDK::alloc_shared_buffer(1000); 

// maplistTemp를 직렬화할 만큼의 메모리를 할당받는다.
auto temp2 = CGDK::alloc_shared_buffer(CGDK::get_size_of(maplistTemp)); 
```

### 구조체 직렬화
* 구조체를 Schema로 사용 가능합니다.
* '구조체 직렬화'를 원하는 구조체의 'ENABLE_STRUCT_SERIALIZABLE'을 추가해 주면 됩니다.

``` C++
struct TEST
{
    ENABLE_STRUCT_SERIALIZABLE

    int       x;
    float     y;
    string    z;
    std::vector<int> w;
};
	    
struct TEST2
{
    ENABLE_STRUCT_SERIALIZABLE

    int       a;
    std::vector<int> b;
    TEST      c;
};
```
이렇게 정의한 후

``` C++
TEST2  tempData;
	    
auto bufTemp = alloc_shared_buffer(get_size_of(tempData));
	    
bufTemp.append<TEST2>(tempData);
	    
.................
	    
var temp1 = bufTemp.extract<TEST2>();

```
이렇게 직렬화/역직렬화를 수행하면 됩니다.
주의) 생성자를 가져서는 안됩니다.

## 지원
* C+17이상이면 지원가능
* C# 모든 버전 지원
* unreal3D(c++) 지원
* unity 3D(c#) 지원

## 소개
* intruduce_CGDK.buffer.pptx 를 참조하십시요.

## 시작하기
* C++/document/Getting_start_CGDK.buffer.pptx 를 참조하십시요.
