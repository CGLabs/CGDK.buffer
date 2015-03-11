using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace CGDBuffers_CSharp_UnitTest
{
    [TestClass]
    public class CGDbuffer_CSharp_UnitTest_Functional
    {
		public const int _TEST_COUNT = 1;

		int[]	array_int = 
		{
			3,
			2,
			9,
			10,
			11,
			22,
			44,
			22
		};

		public string[] array_string = {
			"Please Let test this",
			"이것 좀 테스트하게 해주세요.",
			"这件事 试验",
			"これを試ためさせてください",
			"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
			"Please 这件事 試ためさせてください 합시다.",
			"Test What ever",
			"1234"};

		public List<int>	list_int = new List<int>
		{
			3,
			2,
			9,
			10,
			11,
			22,
			44,
			22
		};

		public List<List<int>> list_list_int = new List<List<int>>
		{
			new List<int> {0, 0, 3},
			new List<int> {3, 2, 64},
			new List<int> {5, 3, 11},
			new List<int> {6, 14, 13},
			new List<int> {7, 5, 200, 400, 12, 33},
			new List<int> {10, 11, 12,900}
		};

		public List<string> list_string = new List<string> {
			"Please Let test this",
			"이것 좀 테스트하게 해주세요.",
			"这件事 试验",
			"これを試ためさせてください",
			"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
			"Please 这件事 試ためさせてください 합시다.",
			"Test What ever",
			"1234"};

		public Dictionary<int, int>	dictionary_int_int	 = new Dictionary<int, int>
		{
			{0,		0},
			{3,		2},
			{5,		3},
			{6,		14},
			{7,		5},
			{10,	11}
		};

		public Dictionary<string, int>	dictionary_string_int	 = new Dictionary<string, int>
		{
			{"zero",	0},
			{"two",		2},
			{"tree",	3},
			{"fifteen",	14},
			{"five",	5},
			{"eleven",	11}
		};

		public Dictionary<string, string>	dictionary_string_string	 = new Dictionary<string, string>
		{
			{"zero",	"0"},
			{"two",		"2"},
			{"tree",	"3"},
			{"fifteen",	"14"},
			{"five",	"5"},
			{"eleven",	"11"}
		};

		public Dictionary<string, List<int>>	dictionary_string_List_int	 = new Dictionary<string, List<int>>
		{
			{"zero",	new List<int> {0,1,2,4}},
			{"two",		new List<int> {3,1,22,4}},
			{"tree",	new List<int> {4,1,12,4}},
			{"fifteen",	new List<int> {5,1,82,4}},
			{"five",	new List<int> {7,1,22,4}},
			{"eleven",	new List<int> {10,21,12,34}}
		};

		public Dictionary<string, List<string>>	dictionary_string_List_string	 = new Dictionary<string, List<string>>
		{
			{"zero",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"two",		new List<string> {"zero", "zero", "zero", "zero"}},
			{"tree",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"fifteen",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"five",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"eleven",	new List<string> {"zero", "zero", "zero", "zero"}}
		};

		void function_append_GENERAL(ref CGD.buffer _Buffer)
		{
			_Buffer.append<char>((char)12);
			_Buffer.append<sbyte>((byte)3);
			_Buffer.append<byte>((sbyte)4);
			_Buffer.append<short>((short)4100);
			_Buffer.append<ushort>((ushort)32210);
			_Buffer.append<int>(123310);
			_Buffer.append<uint>(12);
			_Buffer.append<long>(-1000443L);
			_Buffer.append<ulong>(12233094310UL);
			_Buffer.append<float>(1.0f);
			_Buffer.append<double>(2.0);
		}

		void function_extract_GENERAL(ref CGD.buffer _Buffer)
		{
			var		value1	 = _Buffer.extract<char>();
			var		value2	 = _Buffer.extract<sbyte>();
			var		value3	 = _Buffer.extract<byte>();
			var		value4	 = _Buffer.extract<short>();
			var		value5	 = _Buffer.extract<ushort>();
			var		value6	 = _Buffer.extract<int>();
			var		value7	 = _Buffer.extract<uint>();
			var		value8	 = _Buffer.extract<long>();
			var		value9	 = _Buffer.extract<ulong>();
			var		value10	 = _Buffer.extract<float>();
			var		value11	 = _Buffer.extract<double>();
		}

		void function_append_STRING(ref CGD.buffer _Buffer)
		{
			_Buffer.append<string>(array_string[0]);
			_Buffer.append<string>(array_string[1]);
			_Buffer.append<string>(array_string[2]);
			_Buffer.append<string>(array_string[3]);
			_Buffer.append<string>(array_string[4]);
			_Buffer.append<string>(array_string[5]);
			_Buffer.append<string>(array_string[6]);
			_Buffer.append<string>(array_string[7]);
		}

		string[] function_extract_STRING(ref CGD.buffer _Buffer)
		{
			string[] temp = new string[8];

			temp[0] = _Buffer.extract<string>();
			temp[1] = _Buffer.extract<string>();
			temp[2] = _Buffer.extract<string>();
			temp[3] = _Buffer.extract<string>();
			temp[4] = _Buffer.extract<string>();
			temp[5] = _Buffer.extract<string>();
			temp[6] = _Buffer.extract<string>();
			temp[7] = _Buffer.extract<string>();

			return temp;
		}

        [TestMethod]
		public void Test_buffer_append_extract_general()
		{
			// - Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(1024);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Temp
				CGD.buffer	bufferTemp	 = bufferCreate;

				// - 값 써넣기
				function_append_GENERAL(ref bufferTemp);
				function_extract_GENERAL(ref bufferTemp);
			}
		}

		[TestMethod]
		public void Test_buffer_append_general()
		{
			// - Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(1024);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				CGD.buffer	bufferTemp	 = bufferCreate;

				// - 값 써넣기
				function_append_GENERAL(ref bufferTemp);
			}
		}

        [TestMethod]
		public void Test_buffer_front_general()
		{
			// - Buffer 할당
			CGD.buffer bufferTemp = new CGD.buffer(1024);

			bufferTemp.append<char>(12);
			bufferTemp.set_front<char>(12);
			var	a0	 = bufferTemp.get_front<char>();
			Assert.IsTrue(a0==12);

			bufferTemp.append<sbyte>(3);
			bufferTemp.set_front<sbyte>(3);
			var	a1	 = bufferTemp.get_front<sbyte>();
			Assert.IsTrue(a1==3);

			bufferTemp.append<byte>(4);
			bufferTemp.set_front<byte>(4);
			var	a2	 = bufferTemp.get_front<byte>();
			Assert.IsTrue(a2==4);

			bufferTemp.append<short>(4100);
			bufferTemp.set_front<short>(4100);
			var	a3	 = bufferTemp.get_front<short>();
			Assert.IsTrue(a3==4100);

			bufferTemp.append<ushort>(32210);
			bufferTemp.set_front<ushort>(32210);
			var	a4	 = bufferTemp.get_front<ushort>();
			Assert.IsTrue(a4==32210);

			bufferTemp.append<int>(123310);
			bufferTemp.set_front<int>(123310);
			var	a5	 = bufferTemp.get_front<int>();
			Assert.IsTrue(a5==123310);

			bufferTemp.append<uint>(12);
			bufferTemp.set_front<uint>(12);
			var	a6	 = bufferTemp.get_front<uint>();
			Assert.IsTrue(a6==12);

			bufferTemp.append<long>(-1000443L);
			bufferTemp.set_front<long>(-1000443L);
			var	a7	 = bufferTemp.get_front<long>();
			Assert.IsTrue(a7==-1000443L);

			bufferTemp.append<ulong>(12233094310UL);
			bufferTemp.set_front<ulong>(12233094310UL);
			var	a8	 = bufferTemp.get_front<ulong>();
			Assert.IsTrue(a8==12233094310UL);

			bufferTemp.append<float>(1.0f);
			bufferTemp.set_front<float>(1.0f);
			var	a9	 = bufferTemp.get_front<float>();
			Assert.IsTrue(a9==1.0f);

			bufferTemp.append<double>(2.0);
			bufferTemp.set_front<double>(2.0);
			var	a10	 = bufferTemp.get_front<double>();
			Assert.IsTrue(a10==2.0);
		}

        [TestMethod]
		public void Test_buffer_date()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				DateTime	tempTime	 = new DateTime(2016, 12, 11, 03, 12, 12, 999);

				// - 값 써넣기
				bufferTemp.append(tempTime);

				var	temp	 = bufferTemp.extract<DateTime>();

				// Check) 
                Assert.IsTrue(tempTime == temp);
				Assert.IsTrue(tempTime.Ticks == temp.Ticks);
				Assert.IsTrue(bufferTemp.len==0);
			}
		}


        [TestMethod]
		public void Test_buffer_appendextract_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(1024);

				string[] strResult;

				// - 값 써넣기
				function_append_STRING(ref bufferTemp);
				strResult	 = function_extract_STRING(ref bufferTemp);

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(array_string[0]==strResult[0]);
				Assert.IsTrue(array_string[1]==strResult[1]);
				Assert.IsTrue(array_string[2]==strResult[2]);
				Assert.IsTrue(array_string[3]==strResult[3]);
				Assert.IsTrue(array_string[4]==strResult[4]);
				Assert.IsTrue(array_string[5]==strResult[5]);
				Assert.IsTrue(array_string[6]==strResult[6]);
				Assert.IsTrue(array_string[7]==strResult[7]);
			}
		}

        [TestMethod]
		public void Test_buffer_append_getfront_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(1024);

				// - 값 써넣기
				bufferTemp.append<string>("Test_String");

				string	strResult;
				strResult	 = bufferTemp.get_front<string>();

				// Check) 
				Assert.IsTrue(strResult=="Test_String");
			}
		}

		[TestMethod]
		public void Test_buffer_append_array_int_extract_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(list_int);

				int[]	temp	 = bufferTemp.extract<int[]>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(list_int.Count==temp.Length);
				for(int j=0;j<list_int.Count;++j)
					Assert.AreEqual(list_int[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_array_int_get_front_array_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(list_int);

				int[]	temp	 = bufferTemp.get_front<int[]>();

				// Check) 
				Assert.IsTrue(list_int.Count==temp.Length);
				for(int j=0;j<list_int.Count;++j)
					Assert.AreEqual(list_int[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_array_string_extract_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(array_string);

				string[]	temp	 = bufferTemp.extract<string[]>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(array_string.Length==temp.Length);
				for(int j=0;j<array_string.Length;++j)
					Assert.AreEqual(array_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_array_string_get_front_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(array_string);

				string[]	temp	 = bufferTemp.get_front<string[]>();

				// Check) 
				Assert.IsTrue(array_string.Length==temp.Length);
				for(int j=0;j<array_string.Length;++j)
					Assert.AreEqual(array_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_list_string_extract_general()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(list_string);

				List<string>	temp	 = bufferTemp.extract<List<string>>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(list_string.Count==temp.Count);
				for(int j=0;j<list_string.Count;++j)
					Assert.AreEqual(list_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_list_string_get_front_list_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(list_string);

				List<string>	temp	 = bufferTemp.get_front<List<string>>();

				// Check) 
				Assert.IsTrue(list_string.Count==temp.Count);
				for(int j=0;j<list_string.Count;++j)
					Assert.AreEqual(list_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_int_int_extract_int_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_int_int);

				Dictionary<int, int>	temp	 = bufferTemp.extract<Dictionary<int, int>>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(dictionary_int_int.Count==temp.Count);
				IEnumerator<int>	ka	 = dictionary_int_int.Keys.GetEnumerator();
				IEnumerator<int>	va	 = dictionary_int_int.Values.GetEnumerator();
				IEnumerator<int>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<int>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_int_int_get_front_int_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_int_int);

				// - 값 읽기
				Dictionary<int, int>	temp	 = bufferTemp.get_front<Dictionary<int, int>>();

				// Check) 
				Assert.IsTrue(dictionary_int_int.Count==temp.Count);
				IEnumerator<int>	ka	 = dictionary_int_int.Keys.GetEnumerator();
				IEnumerator<int>	va	 = dictionary_int_int.Values.GetEnumerator();
				IEnumerator<int>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<int>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_int_extract_string_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_int);

				Dictionary<string, int>	temp	 = bufferTemp.extract<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(dictionary_string_int.Count==temp.Count);
				IEnumerator<string>	ka	 = dictionary_string_int.Keys.GetEnumerator();
				IEnumerator<int>	va	 = dictionary_string_int.Values.GetEnumerator();
				IEnumerator<string>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<int>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_int_extract_string_int_2()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{

				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_int);

				Dictionary<string, int> temp = bufferTemp.extract<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count == 0);
				Assert.IsTrue(dictionary_string_int.Count == temp.Count);
				IEnumerator<string> ka = dictionary_string_int.Keys.GetEnumerator();
				IEnumerator<int> va = dictionary_string_int.Values.GetEnumerator();
				IEnumerator<string> kb = temp.Keys.GetEnumerator();
				IEnumerator<int> vb = temp.Values.GetEnumerator();
				while (ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current == kb.Current);
					Assert.IsTrue(va.Current == vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_int_get_front_string_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_int);

				// - 값 읽기 get_front
				Dictionary<string, int>	temp	 = bufferTemp.get_front<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(dictionary_string_int.Count==temp.Count);
				IEnumerator<string>	ka	 = dictionary_string_int.Keys.GetEnumerator();
				IEnumerator<int>	va	 = dictionary_string_int.Values.GetEnumerator();
				IEnumerator<string>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<int>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_string_extract_string_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_string);

				Dictionary<string, string>	temp=bufferTemp.extract<Dictionary<string, string>>();

				// Check) 
				Assert.IsTrue(bufferTemp.Count==0);
				Assert.IsTrue(dictionary_string_string.Count==temp.Count);
				IEnumerator<string>	ka	 = dictionary_string_string.Keys.GetEnumerator();
				IEnumerator<string>	va	 = dictionary_string_string.Values.GetEnumerator();
				IEnumerator<string>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<string>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_string_get_front_string_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_string);

				// - 값 읽기
				Dictionary<string, string>	temp	 = bufferTemp.get_front<Dictionary<string, string>>();

				// Check) 
				Assert.IsTrue(dictionary_string_string.Count==temp.Count);
				IEnumerator<string>	ka	 = dictionary_string_string.Keys.GetEnumerator();
				IEnumerator<string>	va	 = dictionary_string_string.Values.GetEnumerator();
				IEnumerator<string>	kb	 = temp.Keys.GetEnumerator();
				IEnumerator<string>	vb	 = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void Test_buffer_append_list_list_int_string_get_front()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(list_list_int);

				List<List<int>>	temp	= bufferTemp.extract<List<List<int>>>();
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_list_int_get_front()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_List_int);

				Dictionary<string, List<int>>	temp	= bufferTemp.extract<Dictionary<string, List<int>>>();
			}
		}

		[TestMethod]
		public void Test_buffer_append_dictionary_string_list_string_get_front()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGD.buffer bufferTemp = new CGD.buffer(2048);

				// - 값 써넣기
				bufferTemp.append(dictionary_string_List_string);

				Dictionary<string, List<string>>	temp=bufferTemp.extract<Dictionary<string, List<string>>>();
			}
		}

		public struct TEST
		{
			public int X;
			public float Y;
			public UInt32 Z;
		};

		[TestMethod]
        public void TestMethod1()
        {
			CGD.buffer tempBufer = new CGD.buffer();

            tempBufer.alloc(100);

            TEST temp = new TEST();
            
            temp.X   = 10;
            temp.Y   = 1.0f;
            temp.Z   = 100;

            string tempString = "Txxx";

            
            tempBufer.append<int>(10);
            tempBufer.append<TEST>(temp);
            tempBufer.append<string>(tempString);

            int     a1   = tempBufer.extract<int>();
            TEST    a2   = tempBufer.extract<TEST>();
            string  a3   = tempBufer.extract<string>();
        }


		struct TEST_B
		{
			public int X;
			public string Y;
			public UInt32 Z;
			public List<int> W;
		};

		[TestMethod]
		public void TestMethod2()
		{
			CGD.buffer tempBufer = new CGD.buffer();

			tempBufer.alloc(200);


			TEST_B temp = new TEST_B();

			temp.X = 10;
			temp.Y = "Tesfdsafdsafdsafdst";
			temp.Z = 100;
			temp.W = new List<int>	{ 10, 20, 30};


			string tempString;
			
			
			tempString = "Txxfasgfsgfdfx";


			tempBufer.append<int>(10);
			tempBufer.append<TEST_B>(temp);
			tempBufer.append<string>(tempString);

			int a1		 = tempBufer.extract<int>();
			TEST_B a2	 = tempBufer.extract<TEST_B>();
			string a3	 = tempBufer.extract<string>();
		}


		struct TEST_C
		{
			public int			x;
			public List<int>	y;
			public DateTime		t;
			public TEST_B		z;
		};

		[TestMethod]
		public void Test_buffer__multi_level()
		{
			CGD.buffer tempBufer = new CGD.buffer();

			tempBufer.alloc(200);

			TEST_C temp = new TEST_C();

			temp.x	 = 10;
			temp.y	 = new List<int> { 1, 2, 3};
			temp.t	 = new DateTime(1990, 12, 11, 10, 21, 11);
			temp.z.X = 10;
			temp.z.Y = "Tesfdsafdsafdsafdst";
			temp.z.Z = 100;
			temp.z.W = new List<int>	{ 10, 20, 30};


			string tempString;
			tempString = "Txxfasgfsgfdfx";


			tempBufer.append<int>(10);
			tempBufer.append<TEST_C>(temp);
			tempBufer.append<string>(tempString);

			var a1	 = tempBufer.extract<int>();
			var a2	 = tempBufer.extract<TEST_C>();
			var a3	 = tempBufer.extract<string>();
		}
    }
}
