using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Example
{
	class Program
	{
		static void Main(string[] args)
		{
			// Example 1) 다양한 형태의 생성 방법 
			Sample_simple_creation_copy();

			// Example 2) 가장 기본적인 형의 쓰기와 읽기
			Sample_simple_Append_Extract();

			// Example 3) 문자열 쓰기/읽기
			Sample_simple_Append_Extract_string();

			// Example 4) Collection 쓰기/읽기
			Sample_simple_Append_Extract_collection();

			// Example 5) struct(Heterogenous Type) 쓰기/읽기 (1)
			Sample_simple_Append_Extract_struct();

			// Example 6) 다계층(Multiple-Layerd) struct 쓰기/읽기
			Sample_simple_Append_Extract_struct2();

			// Example 7) 클래스(Class) 쓰기/읽기
			Sample_simple_Append_Extract_class();
		}

		//----------------------------------------------------------------------------
		// Example 1) 다양한 형태의 생성 방법 
		//  
		//----------------------------------------------------------------------------
		static void Sample_simple_creation_copy()
		{
			// Case 1) 256 Byte의 메모리를 할당한다.
			CGDK.buffer bufTemp1 = new CGDK.buffer(256);

			// Case 2) 선언 후 할당하기
			CGDK.buffer bufTemp2 = new CGDK.buffer();
			
			bufTemp2.Alloc(256);

			// Case 3) CGPool이 있을 경우
			//CGDK.buffer buffer 3 = MEM_POOL.Alloc(256);

			// Case 4) 바이트 배열을 직접 할당해 넣기.
			CGDK.buffer bufTemp3 = new CGDK.buffer(new byte[256]);

			// Case 5) byte[]과 함께 Offset과 Length도 설정하기
			//         (offset:10, Count:100)
			CGDK.buffer bufTemp4 = new CGDK.buffer(new byte[256], 10, 100);

			// Case 6) 생성된 CGDK.buffer에서 가져온다.(얕은 복사)
			CGDK.buffer bufTemp5 = bufTemp1;

			// - 임시로 data 추간
			bufTemp2.Append<int>(10);
			bufTemp2.Append<int>(20);
			bufTemp2.Append<int>(30);
			bufTemp2.Append<int>(40);

			// Case 7) 생성된 기본 버퍼에서 Offset을 10만큼 더한 후 가져오기
			CGDK.buffer bufTemp6 = bufTemp2 + 10;


			// Case 8) 복사본을 만든다. (깊은 복사)
			CGDK.buffer bufTemp7 = bufTemp1.Clone();

			// 할당 해제
			bufTemp1.Clear();
		}

		//----------------------------------------------------------------------------
		// Example 2) 가장 기본적인 형의 쓰기와 읽기
		//
		//  Append<T> 함수를 사용하여 버퍼의 끝에 T형 값을 써넣을 수 있다.
		//  Extract<T> 함수를 사용하여 버퍼에 제일 앞에서부터 T형 값을 읽어올 수 있다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_Append_Extract()
		{
			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer	bufTemp	 = new CGDK.buffer(new byte[256]);

			// APPEND) 기본적인 값들을 써넣는다.
			bufTemp.Append<byte>(10);
			bufTemp.Append<sbyte>(20);
			bufTemp.Append<int>(-100);
			bufTemp.Append<uint>(1000);

			// * 여기까지 Append를 수행했으면 총 14Byte가 쓰여져
			//   Count 값은 14가 된다. Offset은 여전히 0이지만 
			// * Append할때 붙여진 <T>보다는 쓰여진 값에 따라 쓰여진다.

			// EXTRACT) 값을 일어낸다.
			//    - 값을 읽어내게 되면 Offset값부터 값을 읽어내게 되고 Offset값을 읽어낸 크기 증가시킨다.
			var	temp1 = bufTemp.Extract<byte>(); // 10
			var	temp2 = bufTemp.Extract<SByte>(); // 20
			var	temp3 = bufTemp.Extract<int>(); // -100
			var	temp4 = bufTemp.Extract<uint>(); // 1000

			// 확인)
			Console.WriteLine("temp1:"+temp1 +"  temp2:"+ temp2 + "  temp3"+temp3 + "  temp4"+temp4);
		}
		//----------------------------------------------------------------------------
		// Example 3) 문자열 쓰기/읽기
		//
		//  역시 Append<string> 함수를 사용하여 버퍼의 끝에 string형 값을 쓸수 있다.
		//  굳이 <string>을 쓸 필요가 없지만 코드의 가독성을 위해 붙여 주는 경우가 많다.
		//  
		//  읽을 때는 Extract<string> 함수를 사용하여 읽을 수 있다.
		//  여기서는 반드시 템플릿 인자인 <string>를 써주어야 한다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_Append_Extract_string()
		{
			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer	bufTemp	 = new CGDK.buffer(new byte[256]);

			// APPEND1) 문자열을 추가한다. (1) 
			bufTemp.Append<string>("First test String");

			// APPEND2) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
			bufTemp.Append("Second");

			// Declare) 임시로 문자열 변수를 만든다.
			string	tempString	 = "Third";

			// APPEND3) 문자열을 추가한다. 구지 <string>을 쓸 필요는 없다.(2) 
			bufTemp.Append(tempString);



			// EXTRACT) 추가된 문자열을 뽑아낸다.
			var	str1 = bufTemp.Extract<string>(); // "First test String"
			var str2 = bufTemp.Extract<string>(); // "Second"
			var str3 = bufTemp.Extract<string>(); // "Third"

			// 확인)
			Console.WriteLine(str1);
			Console.WriteLine(str2);
			Console.WriteLine(str3);
		}

		//----------------------------------------------------------------------------
		// Example 4) Collection 쓰기/읽기
		//
		//  Collection 역시 그냥 Append함수로 똑같이 읽고 쓸수 있다.
		// 
		//----------------------------------------------------------------------------
		static void Sample_simple_Append_Extract_collection()
		{
			// Decalre) 임시로 사용할 List를 선언한다.
			List<int> list_int = new List<int>{ 10, 20, 30, 40};
			List<string> list_string = new List<string> { "first","second","second"};
			Dictionary<string, int>	dictionary_int_string = new Dictionary<string, int> { {"first", 10}, {"second", 20}, {"third", 30}};

			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer bufTemp = new CGDK.buffer(new byte[256]);

			// APPEND) List<int>를 추가한다.
			bufTemp.Append(list_int);
			bufTemp.Append(list_string);
			bufTemp.Append(dictionary_int_string);

			
			// EXTRACT) 추가했던 문자열을 읽어낸다.
			var data1 = bufTemp.Extract<List<int>>();
			var data2 = bufTemp.Extract<List<string>>();
			var data3 = bufTemp.Extract<Dictionary<string, int>>();

			// 2) 출력한다.
			foreach(var iter in data1) {Console.WriteLine(iter.ToString());}
			foreach(var iter in data2) {Console.WriteLine(iter.ToString());}
			foreach(var iter in data3) {Console.WriteLine(iter.ToString());}
		}


		//----------------------------------------------------------------------------
		// Example 5) struct(Heterogenous Type) 쓰기/읽기 (1)
		//
		//  구조체의 읽기/쓰기 역시 동일하다. 그냥 값을 써넣은 후 Append/Extract를 사용해
		//  읽고 쓸수 있다.
		//  구조체는 통채로 복사되는 것이 아니라 각 멤버 하나 하나를 따로 쓰고 읽는다.
		// 
		//----------------------------------------------------------------------------
		[CGDK.Attribute.Serializable]
		public struct TEST
		{
			public int x;
			public float y;
			public string z;
			public List<int> w;
		};

		static void Sample_simple_Append_Extract_struct()
		{
			// Decalre) 임시로 사용할 List를 선언한다.
			TEST temp = new TEST();
			temp.x = 10;
			temp.y = 1.0f;
			temp.z = "temp string";
			temp.w = new List<int> { 10, 20, 30};


			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer bufTemp = new CGDK.buffer(new byte[256]);

			// APPEND) List<int>를 추가한다.
			bufTemp.Append(temp);



			// EXTRACT) 추가했던 문자열을 읽어낸다.
			var tempRead = bufTemp.Extract<TEST>();

			// 2) 출력한다.
			Console.WriteLine(tempRead.x);
			Console.WriteLine(tempRead.y);
			Console.WriteLine(tempRead.z);
			foreach (var iter in tempRead.w) { Console.WriteLine(iter.ToString()); }
		}

		//----------------------------------------------------------------------------
		// Example 6) 다계층(Multiple-Layerd) struct 쓰기/읽기
		//
		//  구조체가 구조체를 가지고 있을 경우에도 크게 신경쓰지 않고 Append/Extract로
		//  읽고 쓸수 있다.
		// 
		//----------------------------------------------------------------------------
	#pragma warning disable 0649
		[CGDK.Attribute.Serializable]
		public struct TEST2
		{
			public int a;
			public List<int> b;
			public TEST c;
		};
	#pragma warning restore 0649

		static void Sample_simple_Append_Extract_struct2()
		{
			// Declare) 임시로 사용할 List를 선언한다.
			TEST2 temp = new TEST2();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.c = new TEST();
			temp.c.x = 10;
			temp.c.y = 1.0f;
			//temp.c.z = "temp string";
			temp.c.w = new List<int> { 10, 20, 30 };

			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer bufTemp = new CGDK.buffer(new byte[256]);

			// APPEND 1) List<int>를 추가한다.
			bufTemp.Append(temp);
			
			// EXTRACT 1) 추가했던 문자열을 읽어낸다.
			var tempRead = bufTemp.Extract<TEST2>();

			// 4) 출력한다.
			Console.WriteLine(tempRead.a);
			Console.WriteLine(tempRead.b);
			Console.WriteLine(tempRead.c.x);
			Console.WriteLine(tempRead.c.y);
			Console.WriteLine(tempRead.c.z);
			foreach (var iter in tempRead.c.w) { Console.WriteLine(iter.ToString()); }
		}

		//----------------------------------------------------------------------------
		// Example 7) 클래스(Class) 쓰기/읽기
		//
		//  클래스를 쓰고 읽기 위해서는 CGDK.Serialize attribute를 붙여 주어야 한다.
		// 
		//----------------------------------------------------------------------------
		[CGDK.Attribute.Serializable]
		public class TEST3
		{
			[CGDK.Attribute.Field]
			public int a;
			[CGDK.Attribute.Field]
			public List<int> b = null;
			[CGDK.Attribute.Field]
			public TEST c;
		};

		[Serializable]
		public class TEST4 : TEST3
		{
			public	int d = 0;
		}

		static void	Sample_simple_Append_Extract_class()
		{
			// Declare) 임시로 사용할 List를 선언한다.
			TEST3 temp = new TEST3();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.c = new TEST();
			temp.c.x = 10;
			temp.c.y = 1.0f;
			//temp.c.z = "temp string";
			temp.c.w = new List<int> { 10, 20, 30 };

			// 1) byte[256]를 생성해서 설정한다.
			CGDK.buffer bufTemp = new CGDK.buffer(new byte[256]);

			// APPEND 1) List<int>를 추가한다.
			bufTemp.Append(temp);
			
			// EXTRACT 1) 추가했던 문자열을 읽어낸다.
			var tempRead = bufTemp.Extract<TEST3>();

			// 4) 출력한다.
			Console.WriteLine(tempRead.a);
			Console.WriteLine(tempRead.b);
			Console.WriteLine(tempRead.c.x);
			Console.WriteLine(tempRead.c.y);
			Console.WriteLine(tempRead.c.z);
			foreach (var iter in tempRead.c.w) { Console.WriteLine(iter.ToString()); }
		}
	}
}
