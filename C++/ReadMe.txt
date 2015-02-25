==============================================================================
                                                                           
                                CGD::buffer                                 
                                                                           
                                                                           
                                                                           
                                                                           
  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        
  Best for Game Developement and Optimized for Game Developement.          
                                                                           
                          http://www.CGDbuffer.co.kr                           
                                                                           
==============================================================================

1. CGD.buffer ���� �� ���� ����
   
   - CGD::buffer�� MIT ���̼����� ������ ���� ���̺귯���Դϴ�.
   - CGD::buffer�� ���ø����� �ۼ��Ǿ� ���丮�� Path������ ���ָ� ����Ҽ� �ֽ��ϴ�.
   - CGD::buffer�� Path�� �ݵ�� 'CGDbuffer'�ִ� ��ġ�� Path�� �ɾ��ֽʽÿ�.



2. �߰��� ����
   - CGD::buffer�� C#������ CGD.bufer�� ȣ�ϵ˴ϴ�.
     CGD::buffer�� CGD.buffer�� �ۼ��� �޽����� ��ȣ�� ȣȯ�� ������ �Ϻ� �����
     �������� �ʴ� �͵��� ������ �����Ͽ� ����Ͻñ� �ٶ��ϴ�.
    

	
3. ��ġ ����
   1.0 CGDK 7.0���� ���ԵǾ� �ִ� CCGBuffer�Դϴ�.

   2.0pre (2015.1.5)
      - CGCII ������Ʈ���� ���� ������Ʈ�� �и�
      - CGDK 8.0���� ���ԵǴ� CCGBuffer�� ���
      - Ŭ������ ����
        CGBUF     -> CGD::buffer 
        CCGMemPtr -> CGD::ptr

      - �Լ����� ���� �ҹ��ڷ� �ٲ�����ϴ�.(��, Append -> append, Extract -> extract)
      - �Լ����� ���� ����Ǿ����ϴ�.
          Append<T>      -> append<T>
          ExtractHead<T> -> extract<T>
          ExtractTail<T> -> subtract<T>
          Head<T>        -> front<T>
          Tail<T>        -> back<T>
          
      - C# ������ �߰��Ǿ����ϴ�.
        �ֿ����� ���̴� �Ʒ��� �����ϴ�.
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
           
      - C++11 ������ template meta programming�� ����Ǿ����ϴ�.
      - meta programming�� ����Ǿ� vector/list ���� �������� �����̸����� ���۰����մϴ�.
      - meta programming�� ����Ǿ� array, vector<T>�� ���� �������� 
        Block copy�� ������ ������ �����׽��ϴ�.
      - std::string/std::wstring�Ӹ� �ƴ϶� char16_t, char32_t �� �پ���
        ���ڿ��� �����մϴ�
      - literal�� �ۼ��� ���ڿ��� �ǽð����� ���ڿ��� ���̸� ����ϴ� ����
        �ƴ϶� ������ Ÿ�ӿ� ���Ǿ� ����˴ϴ�.(constexpr �Ϻ� ����)
      - vector/array/ string ���� �������� �ٰ����� �����մϴ�.
      - C++������ std::tuple�� ���� Heterogenous ���� �����մϴ�.
      - C#�� struct�� ���� Heterogenous ���� �����մϴ�.
      - std::initializer_list�� �����մϴ�.
      - C++������ prepend ����� �߰��Ǿ����ϴ�.
      - C++������ �迭�� extract ��ɵ� �߰��Ǿ����ϴ�.
      - ������ ��ſ� �ʿ��� ���� �߰�('\r\n'�� ����ϴ� ���ڿ� ó�� �߰�)
      - r-value ���� ���� ���ɼ� ����
     

4. Contact
   @ http://www.cgdbuffer.co.kr
   @ http://www.cgcii.co.kr
   @ sangduck@cgcii.co.kr