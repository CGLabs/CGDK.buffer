==============================================================================
                                                                           
                                CGD.buffer                                 
                                                                           
                                                                           
                                                                           
                                                                           
  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        
  Best for Game Developement and Optimized for Game Developement.          
                                                                           
                          http://www.CGDbuffer.co.kr                           
                                                                           
==============================================================================

1. CGD::buffer이란
   - 네트워크 상에서 메시지를 주고 받기 위한 직렬화 버퍼입니다.
     CGD::buffer는 메시지를 작성하기 위한 직렬화 지원 버퍼입니다.
     메모리 버퍼에 직렬화를 위한 데이터를 쓰고 읽는 역할만 수행합니다.
     따라서 직렬화된 데이터를 사용자가 필요에 따라 여러 용도로 사용할 수도 있고 
     자신의 시스템의 일부로 포함해 쓸수도 있습니다.

   - 가벼운 간단하며 쉽게...
     특별한 설정이나 특별한 스크립트없이 기본 프로그래밍 언어 안에서 동작하는 것을 추구합니다. 
     사전 설정이나 사후 처리 등과 같은 것의 최소화를 추구합니다.

   - 메시지 내용과 메시지구조의 분리
     -> 메시지에는 메시지 구조 정보를 담고 있지 않습니다.
     -> 메시지는 메시지 구조를 송신측과 수신측이 가지고 있어야 합니다.
     -> 따라서 메시지의 크기를 최소화할 수 있으며 단순히 메시지를 중간에 가로챈다고 해서 쉽게 정보를 알수 있지 않습니다.

   - 최소 단위 호완성
     다른 플랫폼간의 정보교환을 위해 문자열 구조를 사용하는 것이 아니라 최소단위의 데이터간에만 호완성만 제공을 해줍니다.
     그리고 이 호완성을 가진 단위데이터들만으로 메시지 구성하도록 합니다.
     이로 인해 효율화된 이진/문자열 전송을 추구합니다. 

   - 프로그래머블 메시지 구조
     메시지 구조를 특별한 포맷에 맞춰 스크립트나 형식을 나타내는 구조를 선언해야만 메시지를 전송하는 것이 아니라 언제든 프로그래머블하게 구조를 작성하게 하는 것을 추구합니다.
     필요에 따라 포맷이나 구조를 선언할 수도 있습니다.


2. CGD::buffer의 특이사항
   - 사용법이 매우 간단합니다.(사실상 append/extract가 전부...)
   - 매우 빠릅니다. (C#버전은 protobuf, msgpack과 빠른 부분도 있고 느린 부분도 있음, C++ 버전은 매우 빠름... )
   - 매우 작고 가볍습니다. (msgpack-300k~400k, protobuf-100~200k, CGD.buffer-17k~28k)
   - C++은 C++11 Template Meta Programming을 사용해 구현해 전부 template으로만 구현되어
     Include만으로 동작됩니다.
	 또 자동적으로 각종 형을 구분해 그에 맞는 처리를 수행하며 최적의 성능을 낼수 있도록 
	 컴파일 타임에 많은 처리가 진행됩니다.  예를 들어
	 * 문자열(char*, wchar_t*, std::string, std::wstring)을 추가할 경우 문자열에 맞는 처리를 합니다.
     * 고정된 문자열은 strlen으로 실시간 문자열 길이를 처리하지 않고 Compile시간에 상수로 처리합니다.
	 * vector<T>, list<T>, map<K,V>같은 복합형 데이터는 자동적으로 그 형에 맞는 처리를 합니다.
	 * vector<T>같이 컨테이너가 메모리복사가 가능하면 memcpy로 복사합니다.
   - C++버전은 Debug버전에서는 매우 다양한 내부적 Check를 수행해 Assert를 처리하므로 느리지만
     Release는 이 부분을 하지 않아 매우 빠릅니다.
   - VS2010부터 사용은 가능하나 제대로된 기능은 2012부터 가능합니다.(GCC는 추가 예정)
   - C#버전은 Reflection을 사용에 좀더 편리합니다. (Hetrogenous형 지원)

3. CGD::buffer의 간단한 사용 예

    버퍼에 데이터를 버퍼에 쓰기는 간단히 append()로 가능합니다.
    
        C++)
             CGD::buffer bufTemp(malloc(256));
       
             bufTemp.append<uint8_t>(10);
             bufTemp.append<char>(20);
             bufTemp.append<int>(-100);
             bufTemp.append<uint32_t>(1000);
             bufTemp.append<std::string>("Test String"); // 문자열도 가능
       
        C#) 
             CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
       
             bufTemp.append<byte>(10);
             bufTemp.append<sbyte>(20);
             bufTemp.append<int>(-100);
             bufTemp.append<uint>(1000);
             bufTemp.append<string>("Test String");	// 문자열도 가능


    이렇게 작성된 메시지는 extract()로 간단히 읽어낼 수가 있습니다.

         C++)
             auto temp1 = bufTemp.extract<uint8_t>();
             auto temp2 = bufTemp.extract<char>();
             auto temp3 = bufTemp.extract<int>();
             auto temp4 = bufTemp.extract<uint32_t>();
             auto temp5 = bufTemp.extract<std::string>();
   	     
         C#) 
             var temp1 = bufTemp.extract<byte>();
             var temp2 = bufTemp.extract<SByte>();
             var temp3 = bufTemp.extract<int>();
             var temp4 = bufTemp.extract<uint>();
             var temp5 = bufTemp.extract<string>();
	     

    복합형 데이터도 가능하며 그 복합 데이터들 간의 다계층도 가능합니다.
     C#의 List<T>, Dictionary<K,V> ...
     C++의 vector<T>, list<T>, set<T>, map<T> ....

        C++)
            vector<int>                  listTest = { ...};
            list<std::string>            listStringTest = { ...};
            map<std::string, int>        mapTemp = { ...};
            map<int, list<std::string>>  maplistTemp = { ...};
	    
            CGD::buffer bufTemp(malloc(256));
	    
            bufTemp.append<vector<int>>(listTest);
            bufTemp.append<list<std::string>>(listStringTest);
            bufTemp.append<map<std::string, int>>(mapTemp);
            bufTemp.append<map<int, list<std::string>>>(maplistTemp);
	    
            .................
	    
            auto temp1 = bufTemp.extract<vector<int>>();
            auto temp2 = bufTemp.extract<list<std::string>>();
            auto temp3 = bufTemp.extract<map<int, std::string>>();
            auto temp4 = bufTemp.extract<map<int, list<std::string>>>();

   
        C#) 
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


    C#의 경우 구조체를 사용해서 복합형 구현도 가능합니다.
    (C++의 경우 tuple을 통해 할수 가능하나 생략...)

        C#) 
            struct TEST
            {
	            public int       x;
                public float     y;
                public string    z;
                public List<int> w;
            };
	    
            struct TEST2
            {
                public int       a;
                public List<int> b;
                public TEST      c;
            };
	    
    위의 TEST2와 같이 복합적이고 다계층 구조체도 처리가 가능합니다.

        C#) 
            TEST2  tempData;
	    
            CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
	    
            bufTemp.append<TEST2>(tempData);
	    
            .................
	    
            var temp1 = bufTemp.extract<TEST2>();

	주의) 아직 C++버전은 struct는 primitive 형으로 취급하기 때문에 아무런 다른 조작없이
	      내부에 string이나 vector<T>, list<T>같은 것을 지원하지 않습니다.


4. 기타사항 및 주의 사항
   - CGD::buffer는 C++ 버전입니다.
   - CGD.buffer는 CGD::bufer의 C#버전입니다.
   - CGD.buffer와 CGD::buffer로 작성된 메시지는 상호간 호환이 되지만 일부 기능은
     제공되지 않는 것들이 있으니 숙지하여 사용하시기 바랍니다.
     (현재까지 C# struct에 구현이 C++과는 다릅니다.)

   - C++과 C#의 주요기능의 차이는 아래와 같습니다.
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


5. 문의 및 요구사항
   @ http://www.cgdbuffer.co.kr
   @ http://www.cgcii.co.kr
   @ sangduck@cgcii.co.kr
