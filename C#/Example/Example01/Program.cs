using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Example
{
	class Program
	{
		//----------------------------------------------------------------------------
		// Example 1) 다양한 형태의 생성 방법 
		//  
		//----------------------------------------------------------------------------
		static void Sample_simple_creation_copy()
		{
			// Case 1) 256 Byte의 메모리를 할당한다.
			CGD.buffer bufTemp1 = new CGD.buffer(256);

			// Case ) 선언 후 할당하기
			CGD.buffer bufTemp2 = new CGD.buffer();
			
			bufTemp2.alloc(256);

			// Case 3) 바이트 배열을 직접 할당해 넣기.
			CGD.buffer bufTemp3 = new CGD.buffer(new byte[256]);

			// Case 4) byte[]과 함께 Offset과 Length도 설정하기
			//         (offset:10, Count:100)
			CGD.buffer bufTemp4 = new CGD.buffer(new byte[256], 10, 100);

			// Case 5) 생성된 CGD.buffer에서 가져온다.(얕은 복사)
			CGD.buffer bufTemp5 = bufTemp1;

			// Case 6) 생성된 기본 버퍼에서 Offset을 10만큼 더한 후 가져오기
			CGD.buffer bufTemp6 = bufTemp2 + 10;


			// Case 7) 복사본을 만든다. (깊은 복사)
			CGD.buffer bufTemp7	 = bufTemp1.clone();

			// 할당 해제
			bufTemp1.free();
		}

		//----------------------------------------------------------------------------
		// Example 1) 가장 기본적인 형의 쓰기와 읽기
		//
		//  append<T> 함수를 사용하여 버퍼의 끝에 T형 값을 써넣을 수 있다.
		//  extract<T> 함수를 사용하여 버퍼에 제일 앞에서부터 T형 값을 읽어올 수 있다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_append_extract()
		{
			// 1) byte[256]를 생성해서 설정한다.
			CGD.buffer	bufTemp	 = new CGD.buffer(new byte[256]);

			// APPEND) 기본적인 값들을 써넣는다.
			bufTemp.append<byte>(10);
			bufTemp.append<sbyte>(20);
			bufTemp.append<int>(-100);
			bufTemp.append<uint>(1000);

			// * 여기까지 append를 수행했으면 총 14Byte가 쓰여져
			//   Count 값은 14가 된다. Offset은 여전히 0이지만 
			// * append할때 붙여진 <T>보다는 쓰여진 값에 따라 쓰여진다.

			// EXTRACT) 값을 일어낸다.
			//    - 값을 읽어내게 되면 Offset값부터 값을 읽어내게 되고 Offset값을 읽어낸 크기 증가시킨다.
			var	temp1	 = bufTemp.extract<byte>();		// 10
			var	temp2	 = bufTemp.extract<SByte>();	// 20
			var	temp3	 = bufTemp.extract<int>();		// -100
			var	temp4	 = bufTemp.extract<uint>();		// 1000

			// 확인)
			Console.WriteLine("temp1:"+temp1 +"  temp2:"+ temp2 + "  temp3"+temp3 + "  temp4"+temp4);
		}
		//----------------------------------------------------------------------------
		// Example 2) 문자열 쓰기/읽기
		//
		//  역시 append<string> 함수를 사용하여 버퍼의 끝에 string형 값을 쓸수 있다.
		//  굳이 <string>을 쓸 필요가 없지만 코드의 가독성을 위해 붙여 주는 경우가 많다.
		//  
		//  읽을 때는 extract<string> 함수를 사용하여 읽을 수 있다.
		//  여기서는 반드시 템플릿 인자인 <string>를 써주어야 한다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_append_extract_string()
		{
			// 1) byte[256]를 생성해서 설정한다.
			CGD.buffer	bufTemp	 = new CGD.buffer(new byte[256]);

			// APPEND1) 문자열을 추가한다. (1) 
			bufTemp.append<string>("First test String");

			// APPEND2) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
			bufTemp.append("Second");

			// Declare) 임시로 문자열 변수를 만든다.
			string	tempString	 = "Third";

			// APPEND3) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
			bufTemp.append(tempString);



			// EXTRACT) 추가된 문자열을 뽑아낸다.
			var	str1 = bufTemp.extract<string>();	// "First test String"
			var str2 = bufTemp.extract<string>();	// "Second"
			var str3 = bufTemp.extract<string>();	// "Third"

			// 확인)
			Console.WriteLine(str1);
			Console.WriteLine(str2);
			Console.WriteLine(str3);
		}

		//----------------------------------------------------------------------------
		// Example 2) Collection 쓰기/읽기
		//
		//  Collection 역시 그냥 append함수로 똑같이 읽고 쓸수 있다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_append_extract_collection()
		{
			// Decalre) 임시로 사용할 List를 선언한다.
			List<int>				list_int	 = new List<int>	{ 10, 20, 30, 40};
			List<string>			list_string	 = new List<string> { "first","second","second"};
			Dictionary<string, int>	dictionary_int_string	 = new Dictionary<string, int> { {"first", 10}, {"second", 20}, {"third", 30}};

			// 1) byte[256]를 생성해서 설정한다.
			CGD.buffer bufTemp = new CGD.buffer(new byte[256]);

			// APPEND) List<int>를 추가한다.
			bufTemp.append(list_int);
			bufTemp.append(list_string);
			bufTemp.append(dictionary_int_string);

			
			// EXTRACT) 추가했던 문자열을 읽어낸다.
			var data1 = bufTemp.extract<List<int>>();
			var data2 = bufTemp.extract<List<string>>();
			var data3 = bufTemp.extract<Dictionary<string, int>>();

			// 2) 출력한다.
			foreach(var iter in data1)	{Console.WriteLine(iter.ToString());}
			foreach(var iter in data2)	{Console.WriteLine(iter.ToString());}
			foreach(var iter in data3)	{Console.WriteLine(iter.ToString());}
		}


		//----------------------------------------------------------------------------
		// Example 2) struct 쓰기/읽기
		//
		//  구조체의 읽기/쓰기 역시 동일하다. 그냥 값을 써넣은 후 append/extract를 사용해
		//  읽고 쓸수 있다.
		//  구조체는 통채로 복사되는 것이 아니라 각 멤버 하나 하나를 따로 쓰고 읽는다.
		// 
		//----------------------------------------------------------------------------
		struct TEST
		{
			public	int			x;
			public	float		y;
			public	string		z;
			public	List<int>	w;
		};

		static void Sample_simple_append_extract_struct()
		{
			// Decalre) 임시로 사용할 List를 선언한다.
			TEST	temp	 = new TEST();
			temp.x	 = 10;
			temp.y	 = 1.0f;
			temp.z	 = "temp string";
			temp.w	 = new List<int> { 10, 20, 30};
			

			// 1) byte[256]를 생성해서 설정한다.
			CGD.buffer bufTemp = new CGD.buffer(new byte[256]);

			// APPEND) List<int>를 추가한다.
			bufTemp.append(temp);



			// EXTRACT) 추가했던 문자열을 읽어낸다.
			var tempRead = bufTemp.extract<TEST>();

			// 2) 출력한다.
			Console.WriteLine(tempRead.x);
			Console.WriteLine(tempRead.y);
			Console.WriteLine(tempRead.z);
			foreach (var iter in tempRead.w) { Console.WriteLine(iter.ToString()); }
		}

		//----------------------------------------------------------------------------
		// Example 2) 다계층 struct 쓰기/읽기
		//
		//  구조체가 구조체를 가지고 있을 경우에도 크게 신경쓰지 않고 append/extract로
		//  읽고 쓸수 있다.
		// 
		//----------------------------------------------------------------------------
		struct TEST2
		{
			public int			a;
			public List<int>	b;
			public TEST			c;
		};

		static void Sample_simple_append_extract_struct2()
		{
			// Declare) 임시로 사용할 List를 선언한다.
			TEST2 temp = new TEST2();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.c = new TEST();
			temp.c.x = 10;
			temp.c.y = 1.0f;
			temp.c.z = "temp string";
			temp.c.w = new List<int> { 10, 20, 30 };

			// 1) byte[256]를 생성해서 설정한다.
			CGD.buffer bufTemp = new CGD.buffer(new byte[256]);

			// APPEND 1) List<int>를 추가한다.
			bufTemp.append(temp);
			
			// EXTRACT 1) 추가했던 문자열을 읽어낸다.
			var tempRead = bufTemp.extract<TEST2>();

			// 4) 출력한다.
			Console.WriteLine(tempRead.a);
			Console.WriteLine(tempRead.b);
			Console.WriteLine(tempRead.c.x);
			Console.WriteLine(tempRead.c.y);
			Console.WriteLine(tempRead.c.z);
			foreach (var iter in tempRead.c.w) { Console.WriteLine(iter.ToString()); }
		}


		static void Main(string[] args)
		{
			// 1) 생성과 복사
			Sample_simple_creation_copy();

			// 1) 기본적인 형의 append/extract
			Sample_simple_append_extract();

			// 2) 문자열의 append/extract
			Sample_simple_append_extract_string();

			// 3) Collection형의 append/extract
			Sample_simple_append_extract_collection();

			// 4) 구조체의 append/extract
			Sample_simple_append_extract_struct();

			// 5) 다계층 구조체의 append/extract
			Sample_simple_append_extract_struct2();
		}
	}
}
