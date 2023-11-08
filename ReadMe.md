## CGDK::buffer란
CGDK::buffer는 메시지 직렬화 버퍼 시스템<br>
C++버전은 CGDK::buffer이며<br>
C# 버전은 CGDK.buffer<br>

자세한 소개 (https://github.com/CGLabs/CGDK.buffer/blob/master/C%2B%2B/document/intruduce_CGDK.buffer.pptx)<br>


#### CGD::buffer
   - 매우 간단(사실상 append/extract/front가 전부...)<br>
   - 초고성능 (c++ 버전은 tmp로 구현되어 압도적 최강의 성능을 자랑합니다.)<br>
   - 작고 가벼움<br>
   - Schemaless와 Schema(구조체 직렬화)를 모두 지원<br>
   - 설정이나 스크립트(IDL)없이 구조체를 그대로 Schema로 사용 가능<br>
   - C++은 C++11 Template Meta Programming을 사용해 구현해 100% template이므로 Include만으로 사용 가능<br>
   - 자료형에 따라 그에 맞는 직렬화를 수행<br>
   - 지원되는 자료형은<br>
      * 기본 자료형(char,int32_t, ... float, double)<br>
      * enum<br>
      * 문자열(char*, wchar_t*, std::string, std::wstring, std_string_view, ...)<br>
      * 배열(T[N], std::array<T,N>)<br>
      * 컨테이너(std::vector<T>, std::list<T>, std::set<T>,std::map<K,V>, ...)<br>
      * 시간(chrono::time_stamp, chrono::duration, ...) <br>
      * 포인터(std::shared_ptr<T>, std::unique_ptr<T>)<br>
      * buffer (CGDK::buffer_veiew, CGDK::buffer,CGDK::shared_buffer)<br>
      * struct<br>
      * Ibuffer_serialzable<br>
      * 기타...<br>

#### CGD.buffer
   - C#버전<br>
   - 직렬화/역직렬화 방법은 C++과 동일합니다.(append/extract)<br>
   - reflection을 사용하여 구현하였습니다.<br>
   - C++ 버전화 호환됩니다.<br>
<br>
<br>

## buffer 클래스 종류
[C++]<br>
   3종류의 buffer를 제공하고 있으며 모두 상속 관계<br>

  - CGDK::buffer_view<br>
     data_와 size_만 가진 buffer로 읽기나 덥어쓰기만 가능<br>
     'extract<T>' 함수(읽어내기)<br>
     'front<T>' 함수(읽기와 덥어 쓰기)<br><br>
  - CGDK::buffer<br>
     CGDK::buffer_view를 상속받아 경계정보(boung_info)를 추가한 버퍼 클래스<br>
     'append<T>'함수로 붙히기를 지원<br><br>
  - CGDK::shared_buffer<br>
     CGDK::buffer를 상속 받아 스마트 포인터 기능을 더한 버퍼 클래스<br>
     할당된 원본 버퍼를 스마트포인터로 관리함<br>
     alloc_shared_buffer(SIZE) 혹은 make_shared_buffer<T>를 사용해 버퍼를 할당 받을 수 있음<br>
<br>

[C#]<br>
   단일 클라스 종류만 존재.
   (C#은 shared_buffer가 필요하지 않음)
  - CGDK.buffer <br>
     <br>
     <br>

## CGD::buffer 사용하기
### 1. 직렬화하기(Schemaless)  
   버퍼에 데이터를 버퍼에 쓰기는 간단히 append<T>()로 가능<br>
   (TYPE를 생략할 경우 입력되는 값의 자료형으로 간주함)<br>
   ``` C++
     buf.append<[TYPE]>([value]);
   ```
    
[C++]
``` C++
CGDK::shard_buffer bufTemp = alloc_shard_buffer(256);
       
bufTemp.append<uint8_t>(10);
bufTemp.append<char>(20);
bufTemp.append<int>(-100);
bufTemp.append<uint32_t>(1000);
bufTemp.append<std::string>("Test String"); // 문자열도 가능
```
<br>

[C#]
``` C#
CGDK.buffer bufTemp = new CGDK.buffer(new byte[256]);
       
bufTemp.append<byte>(10);
bufTemp.append<sbyte>(20);
bufTemp.append<int>(-100);
bufTemp.append<uint>(1000);
bufTemp.append<string>("Test String");	// 문자열도 가능
```
<br><br>
### 2. 역직렬화하기(Schemaless)<br>

``` C++
  [value] buf.extract<[TYPE]>();
```
extract<T>() 함수로 간단히 역직렬화를 할 수 있습니다.  

[C++]
``` C++
auto temp1 = bufTemp.extract<uint8_t>();
auto temp2 = bufTemp.extract<char>();
auto temp3 = bufTemp.extract<int>();
auto temp4 = bufTemp.extract<uint32_t>();
auto temp5 = bufTemp.extract<std::string>();
```
<br>

[C#]
``` C#
var temp1 = bufTemp.extract<byte>();
var temp2 = bufTemp.extract<SByte>();
var temp3 = bufTemp.extract<int>();
var temp4 = bufTemp.extract<uint>();
var temp5 = bufTemp.extract<string>();
```

복합형 데이터의 직렬화/역직렬화도 가능<br> 
C++의 vector<T>, list<T>, set<T>, map<T> ....<br>
C#의 List<T>, Dictionary<K,V> ...<br>

[C++]
``` C++
std::vector<int>                  listTest = { ...};
std::list<std::string>            listStringTest = { ...};
std::map<std::string, int>        mapTemp = { ...};
std::map<int, list<std::string>>  maplistTemp = { ...};
	    
CGD::buffer bufTemp(malloc(256));
	    
bufTemp.append(listTest);
bufTemp.append(listStringTest);
bufTemp.append(mapTemp);
bufTemp.append(maplistTemp);
	    
.................
	    
auto temp1 = bufTemp.extract<std::vector<int>>();
auto temp2 = bufTemp.extract<std::list<std::string>>();
auto temp3 = bufTemp.extract<std::map<int, std::string>>();
auto temp4 = bufTemp.extract<std::map<int, std::list<std::string>>>();
```
<br>

[C#]
``` C#
List<int>                      listTest = new ...;
List<string>                   listStringTest = new ...;
Dictionary<string, int>        dicTest = new ...;
Dictionary<int, List<string>>  dicListTest = new ...;
       
CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
       
bufTemp.append(listTest);
bufTemp.append(listStringTest);
bufTemp.append(dicTest);
bufTemp.append(dicListTest);
       
.................
       
var temp1 = bufTemp.extract<List<int>> ();
var temp2 = bufTemp.extract<List<string>> ();
var temp3 = bufTemp.extract<Dictionary<string,int>> ();
var temp4 = bufTemp.extract<Dictionary<string,List<int>>> ();

bufTemp.append(maplistTemp);
```

<br>

### 3. 직렬화에 필요한 메모리 구하기
데이터를 직렬화 했을 때의 메모리 크기를 CGDK::get_size_of()르 사용해 얻을 수 있음 <br>
[C++]
``` C++
auto size = CGDK::get_size_of(maplistTemp);
```

<br>

### 4. 동적 메모리 할당 받기
CGDK::alloc_shared_buffer([SIZE])를 사용해 메모리를 동적 할당 가능<br> 
CGDK::shared_buffer로 할당받은 버퍼를 받을 수 있으며 스마트 포인터로 관리되므로 참조가 모두 끝나면 자동 할당 해제 됨<br>

[C++]
``` C++
// 1000byte 메모리를 동적 할당 받는다.
auto temp1 = CGDK::alloc_shared_buffer(1000); 

// maplistTemp를 직렬화할 만큼의 메모리를 할당받는다.
auto temp2 = CGDK::alloc_shared_buffer(CGDK::get_size_of(maplistTemp)); 
```

<br>

### 5. 구조체 직렬화
'구조체 직렬화'를 원하는 구조체의 'ENABLE_STRUCT_SERIALIZABLE'을 추가해 주면 됨<br>
구조체를 Schema로 사용 가능<br>

[C++]
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
이렇게 정의한 후<br>

[C++]
``` C++
TEST2  tempData;
	    
auto bufTemp = alloc_shared_buffer(get_size_of(tempData));
	    
bufTemp.append<TEST2>(tempData);
	    
.................
	    
var temp1 = bufTemp.extract<TEST2>();

```
이렇게 직렬화/역직렬화를 수행 <br>
주의) 생성자와 virtaul 함수를 가져서는 안됨<br>
<br>

## 지원
* C+17이상이면 지원가능<br>
* C# 모든 버전 지원<br>
* unreal3D(c++) 지원<br>
* unity 3D(c#) 지원<br>

<br>

## 시작하기
 https://github.com/CGLabs/CGDK.buffer/blob/master/C%2B%2B/document/Getting_start_CGDK.buffer.pptx


> sangducks@gmail.com
> sangduck@cgcii.co.kr