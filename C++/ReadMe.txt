==============================================================================
                                                                           
                                CGD::buffer                                 
                                                                           
                                                                           
                                                                           
                                                                           
  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        
  Best for Game Developement and Optimized for Game Developement.          
                                                                           
                          http://www.CGDbuffer.co.kr                           
                                                                           
==============================================================================

1. CGD.buffer 사용법 및 주의 사항
   
   - CGD::buffer는 MIT 라이센스에 따르는 공개 라이브러리입니다.
   - CGD::buffer는 템플릿으로 작성되어 디렉토리를 Path설정만 해주면 사용할수 있습니다.
   - CGD::buffer의 Path는 반드시 'CGDbuffer'있는 위치로 Path를 걸어주십시요.



2. 추가적 설명
   - CGD::buffer는 C#버전인 CGD.bufer와 호완됩니다.
     CGD::buffer와 CGD.buffer로 작성된 메시지는 상호간 호환이 되지만 일부 기능은
     제공되지 않는 것들이 있으니 숙지하여 사용하시기 바랍니다.
    

	
3. 패치 설명
   1.0 CGDK 7.0까지 포함되어 있던 CCGBuffer입니다.

   2.0pre (2015.1.5)
      - CGCII 프로젝트에서 독립 프로젝트로 분리
      - CGDK 8.0부터 포함되는 CCGBuffer의 기반
      - 클래스명 변경
        CGBUF     -> CGD::buffer 
        CCGMemPtr -> CGD::ptr

      - 함수명이 전부 소문자로 바뀌었습니다.(예, Append -> append, Extract -> extract)
      - 함수명이 대폭 변경되었습니다.
          Append<T>      -> append<T>
          ExtractHead<T> -> extract<T>
          ExtractTail<T> -> subtract<T>
          Head<T>        -> front<T>
          Tail<T>        -> back<T>
          
      - C# 버전이 추가되었습니다.
        주요기능의 차이는 아래와 같습니다.
              -------------------------------------------
                              (C++)             (C#)
              -------------------------------------------
              buffer 클래스  CGD::buffer     CGD.buffer
              ptr 클래스     CGD::ptr            x
              앞에 붙이기    prepend(...)        x
              뒤에 붙이기    append(...)     append(...)
              앞에서 빼내기  extract(...)    extract(...)
              뒤에서 빼내기  subtract(...)       x
              -------------------------------------------
              상수_문자열        o               x
              복합형             o               o
              다계층             o               o
              Hetro-type         *(tuple)        O
              string(USC)        o               x
              string(UTF-8)      o               o
              string(UTF-16)     o               x
              string(UTF-32)     o               x
              Pool할당 지원      o(CGPool필요)   o(CGPool필요)
              Bounding Check     o               o
              DateTime지원       o               o
              initializer_list   o               x
              -------------------------------------------
           
      - C++11 기준의 template meta programming이 적용되었습니다.
      - meta programming이 적용되어 vector/list 등의 복합형을 동일이름으로 동작가능합니다.
      - meta programming이 적용되어 array, vector<T>와 같은 복합형은 
        Block copy를 지원해 성능을 향상시켰습니다.
      - std::string/std::wstring뿐만 아니라 char16_t, char32_t 등 다양한
        문자열을 지원합니다
      - literal로 작성된 문자열은 실시간으로 문자열을 길이를 계산하는 것이
        아니라 컴파일 타임에 계산되어 적용됩니다.(constexpr 일부 지원)
      - vector/array/ string 등으 복합형의 다계층을 지원합니다.
      - C++버전은 std::tuple을 통해 Heterogenous 형을 지원합니다.
      - C#은 struct를 통해 Heterogenous 형을 지원합니다.
      - std::initializer_list를 지원합니다.
      - C++버전은 prepend 기능이 추가되었습니다.
      - C++버전은 배열형 extract 기능도 추가되었습니다.
      - 웹서버 통신에 필요한 형식 추가('\r\n'을 사용하는 문자열 처리 추가)
      - r-value 관련 오류 가능성 수정
     

4. Contact
   @ http://www.cgdbuffer.co.kr
   @ http://www.cgcii.co.kr
   @ sangduck@cgcii.co.kr