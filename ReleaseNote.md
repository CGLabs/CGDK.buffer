## CGDK 3.22 (2024.3.22)
   #### (C++)
   * buffer를 std::move했을 때 data_와 size_값을 nullptr와 0으로 reset 되도록 수정.
   * gcc-13 컴파일 나는 error 수정.
     
## CGDK 3.21 (2023.12.4)
   #### (C#)
   * No Unsafe
   * ``Roslyn``을 이용해 ``Source Generaion``하는 과정
   * Unit_test를 추가했습니다.(``static``, ``const`` 멤버 테스트) 
   * 배열의 ``Append``,``Extract``시 중대 버그 수정
   * ``class``/``struct``의 크기 계산 중대 버그 수정
     
## CGDK 3.20 (2023.12.1)
   #### (C#)
   * 성능 최적화 
     - ``Boxing/Unboxing``의 최소화 (``Enumerator``를 최대한 ``Boxing/Unboxing``이 발생하지 않는 것으로 선택)
     - ``List<T>``, ``Dictionary<T>``에서 ``Capacity``를 미리 확보하는 처리 추가
   * Nuget에 대응
     - Nuget에 대응해 Project 설정 변경
   * ``Roslyn``을 이용해 ``Source Generaion``하는 과정에서 오류 메시지 추가
     - ``Source Ganeration`` 하는 과정에서 오류가 발생하면 Error 메시지가 제대로 출력하도록 처리했습니다.

## CGDK 3.10 (2023.11.26)
   #### (C#)
   * ``Roslyn``을 사용해 ``Source generator``를 추가
     - ``Serializer``를 ``struct`` & ``class`` 전용 ``Serializer``를 ``Source generator``를 사용해 생성<br>
     - ``struct`` & ``class``의 성능 대폭 향상
   * Documentation Comment 
     - C#에서 제공하는 xml을 사용한 Documentation Comment에 맞춰 주요 클래스와 주요 함수의 주석화 처리를 했습니다.

## CGDK 3.03.(5) (2023.11.23)
   #### (C#)
   * 8년만에 완전 구조 변경
     - 실시간 ``Reflection``를 사용하지 않고 ``Serializer``를 생성해 직렬화/역직렬화 수행<br>
       (즉, 매번 직렬화/역직렬화할 때마다 ``Reflection``을 사용하지 않고 한번만 ``Reflection``으로 ``Serializer``를 생성해 직렬화/역직렬화를 함) <br>
     - 성능의 비약성 향상(``struct`` & ``class``를 제외하고는 ``MemoryPack``에 비해서도 앞도적 성능을 제공)<br>
       (``struct`` & ``class`` 직렬화/역직렬화 성능은 향상되지 않음.) <br>
     - ``Roslyn``과 ``Souce Ganetratation``을 이용한 버전은 이번 업데이트에서 제외 <br>
      <br>
   * 명명 방식을 C# 표준안에 따르게 수정 <br>
     - 전부 소문자 + '_' 명명 방식을 첫글자 대문자 방식으로 변경 <br>
       따라서 이름이 아래와 같은 방식으로 변경되었다. <br>
       <br>
         ``append`` => __``Append``__ <br>
         ``extract`` => __``Extract``__ <br>
         ``get_size_of`` => __``GetSizeOf``__ <br>
         ``get_front`` => __``GetFront``__ <br>
         ``set_front`` => __``SetFront``__ <br>
         ... <br>
         <br>
   * 파일 분리 <br>
     - ``.NET``, ``.NET core``, ``.NET framework``의 소스파일을 분리 <br>
       (``nullable``, ``Unsafe``, ``Linq`` 등 문법이 너무 상이해 더이상 코드의 공용이 힘들다고 판단) <br>

   * unit test 업데이트. <br>

## CGDK 3.03.(4) (2023.11.13) <br>
   #### (C#)  <br>
   * 성능 향상 작업  <br>
     - unsafe를 사용해 일부 기능 성능 향상 <br>
   * Warning 수정 <br>
     - ``.NET``과 ``.NET core`` 컴파일 시 발생하던 Warning 수정 <br>
   * 디렉토리 재조정 <br>
     - unit_test는 디렉토리를 따로 만들어 분리 <br>
   * CGDK.buffer의 직렬화/역직렬화시 size 저장 변수를 4Byte->8Byte (C++버전과의 호환을 위해) <br>
 <br>

## CGDK 3.03.(3) (2023.11.10) <br>
   #### (C#) <br>
   * ``size`` 형이 ``short`` -> ``Int32`` 로 변경되었습니다. <br>
     - C++버전은 ``size``의 기본형(``COUNT_T``)가 ``int32_t``로 되어 있으므로 그에 맞춰 변경. <br>
     <br>

## CGDK 3.03.(2) (2023.11.8, bug fix) <br>
   #### (C++) <br>
   * common <br>
     - unit_test update(버그 수정, 빠진 파일 추가) <br>
     - ``flatbuffers`` unit_test 관련 빠진 파일 업데이트 <br>
     - 빠진 tutorial file 추가(add mission tutorial) <br>
     - 문서 업데이트(document update) <br>
 <br>

## CGDK 3.03 (2023.10.28) <br>
   #### (C++) <br>
   * common <br>
     - unit_test update <br>
     - document update <br>
      <br>

## CGDK 3.02 (2023.10.24) <br>
   #### (C++) <br>
   * common <br>
     - ``add_size``, ``sub_size``, ``set_size`` 같은 함수에 경계정보 검증과정을 추가. <br>
     - 오류와 오타를 수정. <br>
 <br>

## CGDK 3.01 (2022.07.10) <br>
   #### (C++) <br>
   * common <br>
     - buffer의 overflow시 ``assert``, ``exception``, 혹은 무반응을 사용자가 설정할 수 있도록 변경<br>
        ``` C++
         #define CGDK_NO_BOUND_CHECK // bound 검사를 하지 않음(assert나 exception 던지지 않음)<br>
         #define CGD_DISABLE_ASSERT // bound 범위 밖 조작의 경우에도 assert 발생를 발생하지 않고 (Debug 모드일 때만 해당) 그냥 예외를 바로 짐.<br>
        ```
     - 구조체 직렬화(structure serialzation)시 stack overflow 발생 상황 줄임.<br>
      구조체 직렬화는 지역 변수를 활용하기 때문에 지나치 큰 변수의 직렬화시 stack overflow가 날 수 있었다.<br>
      최대한 지역 변수의 사용을 최소화함으로 인해 stack에 의한 제한을 많이 완화 했음.<br>
     - unreal 3d를 지원하기 위한 기능. <br>

   * buffer(``_basic_buffer``) <br>
     - ``_basic_buffer``(``buffer``) 배열로 초기화 기능 추가<br>
     - ``remained()``함수 추가 - 원본 버퍼의 남은 영역을 ``buffer``로 만들어 리턴해 주는 함수<br>
     - ``append``시 return값이 모두 reference형에서 오는 오류 수정 (기본형일 경우만 reference 리턴값 가짐)<br>
     - 중복 코드 제거 <br>
     - ``buffer_view``의 ``extract``시 오류 수정<br>
     - ``extract_multi`` 시 ``own_ptr<T>`` 동작 오류 수정(``CGDK10``에서 사용할 경우에만 해당)<br>
   * ``_shared_buffer`` <br>
     - ``remained()``함수 추가. 원본 버퍼의 남은 버퍼를 ``shared_buffer``로 만들어 리턴해주는 함수<br>
 <br>
   * toturial 정리 <br>
    - tutorial 내용과 설명을 일부 변경<br>
 <br>

## CGDK 3.0 (2022.07.10) <br>
   ``CGD.buffer``에서 ``CGDK.buffer``로 명칭 변경<br>
   #### (C++) <br>
   - ``CGDK::buffer_view``, ``CGDK::buffer``, ``CGDK::shared_buffer``로 ``buffer`` 세분화<br>
     ``CGDK::buffer_view``는 ``extract<T>``와 ``front<T>`` 기능만 가지며 ``append<T>``는 사용 불가능함.<br>
     ``CGDK::buffer``는 ``CGDK::buffer_view``를 상속받아 ``append<T>`` 기능이 추가됨. <br>
     ``CGDK::shared_bufer``는 스마트 포인터를 사용한 버퍼가 구현되어 메모리의 해제를 자동 관리함.<br>
   - 복합형 멤버를 가진 구조체 직렬화 지원<br>
     ``std:string``, ``std::vector<T>`` 등등을 멤버로 가진 구조체(``struct`` 혹은 ``class``)도 ``append<T>``, ``extract<T>``로 바로 직렬화 가능<br>
   - ``get_size_of<T>()`` 직렬화될 크기 업는 함수 추가.<br>
   - C++17 지원 => ``std::string_view`` 등등 ...<br>
   - C++20 지원 => ``std::span<T>`` 등등...<br>
   - unreal 자료구조 지원 추가 (``FString``, ``FStringView``, ``TAraay<T>``, ``TLinkedListBase<T>``. ``TMapBase<K,V>`` ... 등등<br>
   - 형식 문자열을 기존 ``sprintf``에서 ``fmt::format`` 혹은 ``std::format`` 으로 변경<br>
   - ``std::tuple<T...>``, ``std::tie<T...>`` 지원<br>
   - ``CGDK::buffer``의 ``append``, ``extract`` 지원<br>
   - 문자열 변환 기능을 가진 ``appened_text<T>`` 추가<br>
 <br>

   #### (C#)  <br>
   - ``get_size_of<T>`` 지원<br>
   - ``.NET``, ``.NET.core``, ``.NET.framework`` 등등 다양한 플랫폼 지원.<br>

------------------------------------------------------------------------------------- <br>
## 2.0.3pre (2015.7.3)
   #### (C++)
   - ``CGD::buffer::extract(SKIP)`` 함수 추가.<br>
   - ``CGD::buffer::operator>>(SKIP)`` 추가.<br>
   - ``CGD::buffer::_prepend_tuple`` 함수 오타 수정<br>
   - gcc용 C++11버전 지원<br>
     gcc에서도 C++11지원을 위해 config 수정<br>
     gcc warning disable 추가.<br>
     gcc일 경우 _aligned_malloc(msvc용) 대신 ``malloc``(standard c++)으로 사용<br>
     ``is_memcopy_able`` gcc 지원용으로 수정<br>
   - ``CGD::TIME`` 관련 오류 수정<br>
   - ``std::tuple<T...>`` 지원 오류 수정<br>
   - ``_Xappend_string_format()``함수 리펙토링<br>

## 2.0.2pre (2015.6.26)
   #### (C++)
   - Linux 지원. (``Linux GCC``, ``cygwin``, ``MinGW``, ``Solaris``,  C++11이상 지원 필요)<br>
 <br>

   - 버그 수정<br>
     - ``CGD::buffer::_append_array`` 함수: ``_Count``가 0개일 경우 _Data가 ``nullptr``라도 허용하도록 수정.<br>
     - ``CGD::buffer::_append_array`` 함수: ``_Count``가 0개일 경우 _Data가 ``nullptr``라도 허용하도록 수정.<br>
     - ``CGD::buffer::_extract_string_copy``: ``_LengthInWords`` 변수명 오류 수정<br>
     - ``string`` 처리 과정 중 ``NULL``이 ``char``형으로 캐티팅되지 않아 뜨는 warning 수정.<br>
     - ``struct CGD::text<T>: operator`` 정의 오류 수정<br>
     - ``CGD::_Xextract_container_CGPTR_list`` 함수 오류 수정<br>
     - ``CGD::append_string(const const_string<T,N>& _String)``: 컴파일 오류 수정<br>
     - ``CGD::ptr::_prepend_string_format()`` 함수 오타로 인한 컴파일 오류 수정.<br>
     - ``CGD::ptr::_append_string_format`` 스트링 길이 계산 오류 수정<br>
     - ``CGD::ptr::_extract_string_copy()``함수 파라미터 이름 오류 수정.<br>
 <br>

## 2.0.1pre (2015.2.26)
   - visual studio 2010용 Project 추가<br>
   - C++용 ``CGD::buffer`` ``Example01`` 내용 보강<br>
   - C++용 ``CGD::ptr`` 오타로 인한 오류 수정<br>
   - C++용 vs2013 컴파일시 Warning 수정<br>
 <br>

## 2.0pre (2015.1.5) 
   - ``CGCII`` 프로젝트에서 독립 프로젝트로 분리<br>
   - ``CGDK 8.0``부터 포함되는 ``CCGBuffer``의 기반<br>
   - 클래스명 변경<br>
     ``CGBUF``     -> ``CGD::buffer`` <br>
     ``CCGMemPtr`` -> ``CGD::ptr``<br>
 <br>
   - 함수명이 전부 소문자로 바뀌었습니다.(예, ``Append`` -> ``append``, ``Extract`` -> ``extract``)<br>
   - 함수명이 대폭 변경<br>
  
       ``Append<T>``      -> ``append<T>``<br>
       ``ExtractHead<T>`` -> ``extract<T>``<br>
       ``ExtractTail<T>`` -> ``subtract<T>``<br>
       ``Head<T>``        -> ``front<T>``<br>
       ``Tail<T>``        -> ``back<T>``<br>
 <br>
   - C++11 기준 ``template meta programming``이 적용<br>
   - ``meta programming``이 적용되어 ``vector``/``list`` 등의 복합형을 동일이름으로 동작가능<br>
   - ``meta programming``이 적용되어 ``array``, ``vector<T>``와 같은 복합형은 Block copy를 지원해 성능을 향상<br>
   - ``std::string``/``std::wstring``뿐만 아니라 ``char16_t``, ``char32_t`` 등 다양한 문자열을 지원합니다<br>
   - ``literal``로 작성된 문자열은 실시간으로 문자열을 길이를 계산하는 것이 아니라 컴파일 타임에 계산되어 적용(``constexpr`` 일부 지원)<br>
   - ``vector``/``array``/``string`` 등의 복합형 객체의 다계층을 지원<br>
   - C#은 ``struct``를 통해 Heterogenous형을 지원<br>
   - C++버전은 ``std::tuple``을 통해 Heterogenous 복합형을 지원<br>
   - ``std::initializer_list``를 지원<br>
   - C++버전은 ``prepend`` 기능이 추가<br>
   - C++버전은 배열형 ``extract`` 기능도 추가<br>
   - 웹서버 통신에 필요한 형식 추가(``'\r\n'``을 사용하는 문자열 처리 추가)<br>
   - ``r-value`` 관련 오류 가능성 수정<br>
 <br>

## 1.0   CGDK 7.0까지 포함되어 있던 CCGBuffer     <br>
