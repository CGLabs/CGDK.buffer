==============================================================================
                                                                           
                                CGD.buffer                                 
                                                                           
                                                                           
                                                                           
                                                                           
  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        
  Best for Game Developement and Optimized for Game Developement.          
                                                                           
                          http://www.CGDbuffer.co.kr                           
                                                                           
==============================================================================

1. CGD::buffer�̶�
   - ��Ʈ��ũ �󿡼� �޽����� �ְ� �ޱ� ���� ����ȭ �����Դϴ�.
     CGD::buffer�� �޽����� �ۼ��ϱ� ���� ����ȭ ���� �����Դϴ�.
     �޸� ���ۿ� ����ȭ�� ���� �����͸� ���� �д� ���Ҹ� �����մϴ�.
     ���� ����ȭ�� �����͸� ����ڰ� �ʿ信 ���� ���� �뵵�� ����� ���� �ְ� 
     �ڽ��� �ý����� �Ϻη� ������ ������ �ֽ��ϴ�.

   - ������ �����ϸ� ����...
     Ư���� �����̳� Ư���� ��ũ��Ʈ���� �⺻ ���α׷��� ��� �ȿ��� �����ϴ� ���� �߱��մϴ�. 
     ���� �����̳� ���� ó�� ��� ���� ���� �ּ�ȭ�� �߱��մϴ�.

   - �޽��� ����� �޽��������� �и�
     -> �޽������� �޽��� ���� ������ ��� ���� �ʽ��ϴ�.
     -> �޽����� �޽��� ������ �۽����� �������� ������ �־�� �մϴ�.
     -> ���� �޽����� ũ�⸦ �ּ�ȭ�� �� ������ �ܼ��� �޽����� �߰��� ����æ�ٰ� �ؼ� ���� ������ �˼� ���� �ʽ��ϴ�.

   - �ּ� ���� ȣ�ϼ�
     �ٸ� �÷������� ������ȯ�� ���� ���ڿ� ������ ����ϴ� ���� �ƴ϶� �ּҴ����� �����Ͱ����� ȣ�ϼ��� ������ ���ݴϴ�.
     �׸��� �� ȣ�ϼ��� ���� ���������͵鸸���� �޽��� �����ϵ��� �մϴ�.
     �̷� ���� ȿ��ȭ�� ����/���ڿ� ������ �߱��մϴ�. 

   - ���α׷��Ӻ� �޽��� ����
     �޽��� ������ Ư���� ���˿� ���� ��ũ��Ʈ�� ������ ��Ÿ���� ������ �����ؾ߸� �޽����� �����ϴ� ���� �ƴ϶� ������ ���α׷��Ӻ��ϰ� ������ �ۼ��ϰ� �ϴ� ���� �߱��մϴ�.
     �ʿ信 ���� �����̳� ������ ������ ���� �ֽ��ϴ�.


2. CGD::buffer�� Ư�̻���
   - ������ �ſ� �����մϴ�.(��ǻ� append/extract�� ����...)
   - �ſ� �����ϴ�. (C#������ protobuf, msgpack�� ���� �κе� �ְ� ���� �κе� ����, C++ ������ �ſ� ����... )
   - �ſ� �۰� �������ϴ�. (msgpack-300k~400k, protobuf-100~200k, CGD.buffer-17k~28k)
   - C++�� C++11 Template Meta Programming�� ����� ������ ���� template���θ� �����Ǿ�
     Include������ ���۵˴ϴ�.
	 �� �ڵ������� ���� ���� ������ �׿� �´� ó���� �����ϸ� ������ ������ ���� �ֵ��� 
	 ������ Ÿ�ӿ� ���� ó���� ����˴ϴ�.  ���� ���
	 * ���ڿ�(char*, wchar_t*, std::string, std::wstring)�� �߰��� ��� ���ڿ��� �´� ó���� �մϴ�.
     * ������ ���ڿ��� strlen���� �ǽð� ���ڿ� ���̸� ó������ �ʰ� Compile�ð��� ����� ó���մϴ�.
	 * vector<T>, list<T>, map<K,V>���� ������ �����ʹ� �ڵ������� �� ���� �´� ó���� �մϴ�.
	 * vector<T>���� �����̳ʰ� �޸𸮺��簡 �����ϸ� memcpy�� �����մϴ�.
   - C++������ Debug���������� �ſ� �پ��� ������ Check�� ������ Assert�� ó���ϹǷ� ��������
     Release�� �� �κ��� ���� �ʾ� �ſ� �����ϴ�.
   - VS2010���� ����� �����ϳ� ����ε� ����� 2012���� �����մϴ�.(GCC�� �߰� ����)
   - C#������ Reflection�� ��뿡 ���� ���մϴ�. (Hetrogenous�� ����)

3. CGD::buffer�� ������ ��� ��

    ���ۿ� �����͸� ���ۿ� ����� ������ append()�� �����մϴ�.
    
        C++)
             CGD::buffer bufTemp(malloc(256));
       
             bufTemp.append<uint8_t>(10);
             bufTemp.append<char>(20);
             bufTemp.append<int>(-100);
             bufTemp.append<uint32_t>(1000);
             bufTemp.append<std::string>("Test String"); // ���ڿ��� ����
       
        C#) 
             CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
       
             bufTemp.append<byte>(10);
             bufTemp.append<sbyte>(20);
             bufTemp.append<int>(-100);
             bufTemp.append<uint>(1000);
             bufTemp.append<string>("Test String");	// ���ڿ��� ����


    �̷��� �ۼ��� �޽����� extract()�� ������ �о ���� �ֽ��ϴ�.

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
	     

    ������ �����͵� �����ϸ� �� ���� �����͵� ���� �ٰ����� �����մϴ�.
     C#�� List<T>, Dictionary<K,V> ...
     C++�� vector<T>, list<T>, set<T>, map<T> ....

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


    C#�� ��� ����ü�� ����ؼ� ������ ������ �����մϴ�.
    (C++�� ��� tuple�� ���� �Ҽ� �����ϳ� ����...)

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
	    
    ���� TEST2�� ���� �������̰� �ٰ��� ����ü�� ó���� �����մϴ�.

        C#) 
            TEST2  tempData;
	    
            CGD.buffer bufTemp = new CGD.buffer(new byte[256]);
	    
            bufTemp.append<TEST2>(tempData);
	    
            .................
	    
            var temp1 = bufTemp.extract<TEST2>();

	����) ���� C++������ struct�� primitive ������ ����ϱ� ������ �ƹ��� �ٸ� ���۾���
	      ���ο� string�̳� vector<T>, list<T>���� ���� �������� �ʽ��ϴ�.


4. ��Ÿ���� �� ���� ����
   - CGD::buffer�� C++ �����Դϴ�.
   - CGD.buffer�� CGD::bufer�� C#�����Դϴ�.
   - CGD.buffer�� CGD::buffer�� �ۼ��� �޽����� ��ȣ�� ȣȯ�� ������ �Ϻ� �����
     �������� �ʴ� �͵��� ������ �����Ͽ� ����Ͻñ� �ٶ��ϴ�.
     (������� C# struct�� ������ C++���� �ٸ��ϴ�.)

   - C++�� C#�� �ֿ����� ���̴� �Ʒ��� �����ϴ�.
      -------------------------------------------
                      (C++)             (C#)
      -------------------------------------------
      buffer Ŭ����  CGD::buffer     CGD.buffer
      ptr Ŭ����     CGD::ptr            x
      �տ� ���̱�    prepend(...)        x
      �ڿ� ���̱�    append(...)     append(...)
      �տ��� ������  extract(...)    extract(...)
      �ڿ��� ������  subtract(...)       x
      -------------------------------------------
      ���_���ڿ�        o               x
      ������             o               o
      �ٰ���             o               o
      Hetro-type         *(tuple)        O
      string(USC)        o               x
      string(UTF-8)      o               o
      string(UTF-16)     o               x
      string(UTF-32)     o               x
      Pool�Ҵ� ����      o(CGPool�ʿ�)   o(CGPool�ʿ�)
      Bounding Check     o               o
      DateTime����       o               o
      initializer_list   o               x
      -------------------------------------------


5. ���� �� �䱸����
   @ http://www.cgdbuffer.co.kr
   @ http://www.cgcii.co.kr
   @ sangduck@cgcii.co.kr
