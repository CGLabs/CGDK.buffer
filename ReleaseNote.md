## CGDK 3.03.(3) (2023.11.10)
   #### (C#)
   * size 형이 short -> Int32 로 변경되었습니다.
     - C++버전은 size의 기본형(COUNT_T)가 int32_t로 되어 있으므로 그에 맞춰 변경.

## CGDK 3.03.(2) (2023.11.8, bug fix)
   #### (C++)
   * common
     - unit_test update(버그 수정, 빠진 파일 추가)
     - flatbuffers unit_test 관련 빠진 파일 업데이트
     - 빠진 tutorial file 추가(add mission tutorial)
     - 문서 업데이트(document update)

## CGDK 3.03 (2023.10.28)
   #### (C++)
   * common
     - unit_test update
     - document update

## CGDK 3.02 (2023.10.24)
   #### (C++)
   * common
     - add_size, sub_size, set_size 같은 함수에 경계정보 검증과정을 추가.
     - 오류와 오타를 수정.

## CGDK 3.01 (2022.07.10)
   #### (C++)
   * common
     - buffer의 overflow시 assert, exception, 혹은 무반응을 사용자가 설정할 수 있도록 변경<br>
        ``` C++
         #define CGDK_NO_BOUND_CHECK // bound 검사를 하지 않음(assert나 exception 던지지 않음)<br>
         #define CGD_DISABLE_ASSERT // bound 범위 밖 조작의 경우에도 assert 발생를 발생하지 않고 (Debug 모드일 때만 해당) 그냥 예외를 바로 짐.<br>
        ```
     - 구조체 직렬화(structure serialzation)시 stack overflow 발생 상황 줄임.<br>
      구조체 직렬화는 지역 변수를 활용하기 때문에 지나치 큰 변수의 직렬화시 stack overflow가 날 수 있었다.<br>
      최대한 지역 변수의 사용을 최소화함으로 인해 stack에 의한 제한을 많이 완화 했음.<br>
     - unreal 3d를 지원하기 위한 기능.

   * buffer(_basic_buffer)
     - _basic_buffer(buffer) 배열로 초기화 기능 추가<br>
     - ramained()함수 추가 - 원본 버퍼의 남은 영역을 buffer로 만들어 리턴해 주는 함수<br>
     - append시 return값이 모두 reference형에서 오는 오류 수정 (기본형일 경우만 reference 리턴값 가짐)<br>
     - 중복 코드 제거<br>
     - buffer_view의 extract시 오류 수정<br>
     - extract_multi 시 own_ptr<T> 동작 오류 수정(CGDK10에서 사용할 경우에만 해당)<br>
   * _shared_buffer
     - remained()함수 추가. 원본 버퍼의 남은 버퍼를 shared)buffer로 만들어 리턴해주는 함수<br>

   * toturial 정리
    - tutorial 내용과 설명을 일부 변경<br>

## CGDK 3.0 (2022.07.10)
   CGD.buffer에서 CGDK.buffer로 명칭 변경<br>
   #### (C++)
   - CGDK::buffer_view, CGDK::buffer, CGDK::shared_buffer로 buffer 세분화<br>
     CGDK::buffer_view는 extract<T>와 front<T> 기능만 가지며 append<T>는 사용 불가능함.<br>
     CGDK::buffer는 CGDK::buffer_view를 상속받아 append<T> 기능이 추가됨. <br>
     CGDK::shared_bufer는 스마트 포인터를 사용한 버퍼가 구현되어 메모리의 해제를 자동 관리함.<br>
   - 복합형 멤버를 가진 구조체 직렬화 지원<br>
     std:string, std::vector<T> 등등을 멤버로 가진 구조체(struct 혹은 class)도 append<T>, extract<T>로 바로 직렬화 가능<br>
   - get_size_of<T>() 직렬화될 크기 업는 함수 추가.<br>
   - C++17 지원 => std::string_view 등등 ...<br>
   - C++20 지원 => std::span<T> 등등...<br>
   - unreal 자료구조 지원 추가 (FString, FStringView, TAraay<T>, TLinkedListBase<T>. TMapBase<K,V> ... 등등<br>
   - 형식 문자열을 기존 sprintf에서 fmt::format 혹은 std::format 으로 변경<br>
   - std::tuple<T...>, std::tie<T...> 지원<br>
   - CGDK::buffer의 append, extract 지원<br>
   - 문자열 변환 기능을 가진 appened_text<T> 추가<br>

   #### (C#) 
   - get_size_of<T> 지원<br>
   - .NET, .NET.core, .NET.framework 등등 다양한 플랫폼 지원.<br>

-------------------------------------------------------------------------------------
## 2.0.3pre (2015.7.3)
   #### (C++)
   - CGD::buffer::extract(SKIP) 함수 추가.<br>
   - CGD::buffer::operator>>(SKIP) 추가.<br>
   - CGD::buffer::_prepend_tuple 함수 오타 수정<br>
   - gcc용 C++11버전 지원<br>
     gcc에서도 C++11지원을 위해 config 수정<br>
     gcc warning disable 추가.<br>
     gcc일 경우 _aligned_malloc(msvc용) 대신 malloc(stadard c++)으로 사용<br>
     is_memcopy_able gcc 지원용으로 수정<br>
   - CGD::TIME 관련 오류 수정<br>
   - std::tuple<T...> 지원 오류 수정<br>
   - _Xappend_string_format()함수 리펙토링<br>

## 2.0.2pre (2015.6.26)
   #### (C++)
   - Linux 지원. (Linux GCC, cygwin, MinGW, Solaris,  C++11이상 지원 필요)<br>

   - 버그 수정<br>
     - CGD::buffer::_append_array 함수: _Count가 0개일 경우 _Data가 nullptr라도 허용하도록 수정.<br>
     - CGD::buffer::_append_array 함수: _Count가 0개일 경우 _Data가 nullptr라도 허용하도록 수정.<br>
     - CGD::buffer::_extract_string_copy: _LengthInWords 변수명 오류 수정<br>
     - string 처리 과정 중 NULL이 char형으로 캐티팅되지 않아 뜨는 warning 수정.<br>
     - struct CGD::text<T>: operator 정의 오류 수정<br>
     - CGD::_Xextract_container_CGPTR_list 함수 오류 수정<br>
     - CGD::append_string(const const_string<T,N>& _String): 컴파일 오류 수정<br>
     - CGD::ptr::_prepend_string_format() 함수 오타로 인한 컴파일 오류 수정.<br>
     - CGD::ptr::_append_string_format 스트링 길이 계산 오류 수정<br>
     - CGD::ptr::_extract_string_copy()함수 파라미터 이름 오류 수정.<br>

## 2.0.1pre (2015.2.26)
   - visual studio 2010용 Project 추가<br>
   - C++용 CGD::buffer Example01 내용 보강<br>
   - C++용 CGD::ptr 오타로 인한 오류 수정<br>
   - C++용 vs2013 컴파일시 Warning 수정<br>

## 2.0pre (2015.1.5) 
   - CGCII 프로젝트에서 독립 프로젝트로 분리<br>
   - CGDK 8.0부터 포함되는 CCGBuffer의 기반<br>
   - 클래스명 변경<br>
     CGBUF     -> CGD::buffer <br>
     CCGMemPtr -> CGD::ptr<br>

   - 함수명이 전부 소문자로 바뀌었습니다.(예, Append -> append, Extract -> extract)<br>
   - 함수명이 대폭 변경<br>
       Append<T>      -> append<T><br>
       ExtractHead<T> -> extract<T><br>
       ExtractTail<T> -> subtract<T><br>
       Head<T>        -> front<T><br>
       Tail<T>        -> back<T><br>

   - C++11 기준 template meta programming이 적용<br>
   - meta programming이 적용되어 vector/list 등의 복합형을 동일이름으로 동작가능<br>
   - meta programming이 적용되어 array, vector<T>와 같은 복합형은 Block copy를 지원해 성능을 향상<br>
   - std::string/std::wstring뿐만 아니라 char16_t, char32_t 등 다양한 문자열을 지원합니다<br>
   - literal로 작성된 문자열은 실시간으로 문자열을 길이를 계산하는 것이 아니라 컴파일 타임에 계산되어 적용(constexpr 일부 지원)<br>
   - vector/array/string 등의 복합형 객체의 다계층을 지원<br>
   - C#은 struct를 통해 Heterogenous형을 지원<br>
   - C++버전은 std::tuple을 통해 Heterogenous 복합형을 지원<br>
   - std::initializer_list를 지원<br>
   - C++버전은 prepend 기능이 추가<br>
   - C++버전은 배열형 extract 기능도 추가<br>
   - 웹서버 통신에 필요한 형식 추가('\r\n'을 사용하는 문자열 처리 추가)<br>
   - r-value 관련 오류 가능성 수정<br>

## 1.0   CGDK 7.0까지 포함되어 있던 CCGBuffer