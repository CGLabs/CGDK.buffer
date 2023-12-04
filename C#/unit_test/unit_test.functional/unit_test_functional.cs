using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Linq;

namespace CGDBuffer_CSharp_UnitTest
{
	[TestClass]
	public class CGDbuffer_CSharp_Unittest_Functional
	{
		public const int _TEST_COUNT = 1;

		public enum ENUM_A
		{
			A = 10,
			B = 20,
			C = 30,
			D = 40,
			E = 50
		}

		[Serializable]
		public class CTest
		{
			public int x;
			public int y;
			public int z;
		}

		int[] array_int =
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

		public List<int> list_int = new List<int>
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

		public Dictionary<int, int> dictionary_int_int = new Dictionary<int, int>
		{
			{0,     0},
			{3,     2},
			{5,     3},
			{6,     14},
			{7,     5},
			{10,    11}
		};

		public Dictionary<string, int> dictionary_string_int = new Dictionary<string, int>
		{
			{"zero",    0},
			{"two",     2},
			{"tree",    3},
			{"fifteen", 14},
			{"five",    5},
			{"eleven",  11}
		};

		public Dictionary<string, string> dictionary_string_string = new Dictionary<string, string>
		{
			{"zero",    "0"},
			{"two",     "2"},
			{"tree",    "3"},
			{"fifteen", "14"},
			{"five",    "5"},
			{"eleven",  "11"}
		};

		public Dictionary<string, List<int>> dictionary_string_List_int = new Dictionary<string, List<int>>
		{
			{"zero",    new List<int> {0,1,2,4}},
			{"two",     new List<int> {3,1,22,4}},
			{"tree",    new List<int> {4,1,12,4}},
			{"fifteen", new List<int> {5,1,82,4}},
			{"five",    new List<int> {7,1,22,4}},
			{"eleven",  new List<int> {10,21,12,34}}
		};

		public Dictionary<string, List<string>> dictionary_string_List_string = new Dictionary<string, List<string>>
		{
			{"zero",    new List<string> {"zero", "one", "two", "four"}},
			{"two",     new List<string> {"five", "six", "seven", "eight"}},
			{"tree",    new List<string> {"nine", "ten", "eleven", "twelve"}},
			{"fifteen", new List<string> {"thirteen", "fourteen", "fifteen", "sixteen"}},
			{"five",    new List<string> {"seventeen", "eighteen", "nineteen", "twenty"}},
			{"eleven",  new List<string> {"twenthone", "twentytwo", "twentythree", "twentyfour"}}
		};

		void function_append_GENERAL_1(ref CGDK.buffer _buffer)
		{
			_buffer.Append<char>((char)12);
			_buffer.Append<sbyte>((sbyte)3);
			_buffer.Append<byte>((byte)4);
			_buffer.Append<short>((short)4100);
			_buffer.Append<ushort>((ushort)32210);
			_buffer.Append<int>((int)123310);
			_buffer.Append<uint>((uint)12);
			_buffer.Append<long>((long)-1000443L);
			_buffer.Append<ulong>((ulong)12233094310UL);
			_buffer.Append<float>((float)1.0f);
			_buffer.Append<double>((double)2.0);
		}

		void function_append_GENERAL_2(ref CGDK.buffer _buffer)
		{
			_buffer.Append((char)12);
			_buffer.Append((sbyte)3);
			_buffer.Append((byte)4);
			_buffer.Append((short)4100);
			_buffer.Append((ushort)32210);
			_buffer.Append((int)123310);
			_buffer.Append((uint)12);
			_buffer.Append((long)-1000443L);
			_buffer.Append((ulong)12233094310UL);
			_buffer.Append((float)1.0f);
			_buffer.Append((double)2.0);
		}

		void function_extract_GENERAL_1(ref CGDK.buffer _buffer)
		{
			var value1 = _buffer.Extract<char>();
			var value2 = _buffer.Extract<sbyte>();
			var value3 = _buffer.Extract<byte>();
			var value4 = _buffer.Extract<short>();
			var value5 = _buffer.Extract<ushort>();
			var value6 = _buffer.Extract<int>();
			var value7 = _buffer.Extract<uint>();
			var value8 = _buffer.Extract<long>();
			var value9 = _buffer.Extract<ulong>();
			var value10 = _buffer.Extract<float>();
			var value11 = _buffer.Extract<double>();
		}

		void function_append_STRING(ref CGDK.buffer _buffer)
		{
			_buffer.Append<string>(array_string[0]);
			_buffer.Append<string>(array_string[1]);
			_buffer.Append<string>(array_string[2]);
			_buffer.Append<string>(array_string[3]);
			_buffer.Append<string>(array_string[4]);
			_buffer.Append<string>(array_string[5]);
			_buffer.Append<string>(array_string[6]);
			_buffer.Append<string>(array_string[7]);
		}

#if NET
		string?[] function_extract_STRING(ref CGDK.buffer _buffer)
#else
		string[] function_extract_STRING(ref CGDK.buffer _buffer)
#endif
		{
#if NET
			string?[] temp = new string[8];
#else
			string[] temp = new string[8];
#endif

			temp[0] = _buffer.Extract<string>();
			temp[1] = _buffer.Extract<string>();
			temp[2] = _buffer.Extract<string>();
			temp[3] = _buffer.Extract<string>();
			temp[4] = _buffer.Extract<string>();
			temp[5] = _buffer.Extract<string>();
			temp[6] = _buffer.Extract<string>();
			temp[7] = _buffer.Extract<string>();

			return temp;
		}

		[TestMethod]
		public void test_buffer_general_extract_1()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			function_append_GENERAL_1(ref buf_create);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Temp
				var buf_temp = buf_create;

				// - 값 써넣기
				function_extract_GENERAL_1(ref buf_temp);
			}
		}

		[TestMethod]
		public void test_buffer_general_append_1()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_create;

				// - 값 써넣기
				function_append_GENERAL_1(ref buf_temp);
			}
		}

		[TestMethod]
		public void test_buffer_general_append_2()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_create;

				// - 값 써넣기
				function_append_GENERAL_2(ref buf_temp);
			}
		}

		[TestMethod]
		public void test_buffer_general_append_char()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.Append<char>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.Extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			//// - sbyte
			//{
			//	buf_create.Append<char>((sbyte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - byte
			//{
			//	buf_create.Append<char>((byte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - short
			//{
			//	buf_create.Append<char>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ushort
			//{
			//	buf_create.Append<char>((ushort)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ushort
			//{
			//	buf_create.Append<char>((ushort)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - int
			//{
			//	buf_create.Append<char>((int)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - uint
			//{
			//	buf_create.Append<char>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<char>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<char>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(char));
			//	var v = buf_create.Extract<char>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//try
			//{
			//	buf_create.Append<char>((float)100);

			//	// Error float는 char로 넣을 수 없다.
			//	Assert.IsTrue(false);
			//}
			//catch (System.Exception)
			//{
			//}

			//// - double
			//try
			//{
			//	buf_create.Append<char>((double)100);

			//	// Error float는 char로 넣을 수 없다.
			//	Assert.IsTrue(false);
			//}
			//catch (System.Exception)
			//{
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_sbyte()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<sbyte>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<sbyte>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(sbyte));
				var v = buf_create.Extract<sbyte>();
				Assert.IsTrue(v == 100);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - byte
			//{
			//	buf_create.Append<sbyte>((byte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - short
			//{
			//	buf_create.Append<sbyte>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ushort
			//{
			//	buf_create.Append<sbyte>((ushort)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - int
			{
				buf_create.Append<sbyte>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(sbyte));
				var v = buf_create.Extract<sbyte>();
				Assert.IsTrue(v == 100);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - uint
			//{
			//	buf_create.Append<sbyte>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<sbyte>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<sbyte>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<sbyte>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<sbyte>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			//	var v = buf_create.Extract<sbyte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_byte()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<byte>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - sbyte
			//{
			//	buf_create.Append<byte>((sbyte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - bytes
			{
				buf_create.Append<byte>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(byte));
				var v = buf_create.Extract<byte>();
				Assert.IsTrue(v == 100);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - short
			//{
			//	buf_create.Append<byte>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ushort
			//{
			//	buf_create.Append<byte>((ushort)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - int
			{
				buf_create.Append<byte>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(byte));
				var v = buf_create.Extract<byte>();
				Assert.IsTrue(v == 100);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - uint
			//{
			//	buf_create.Append<byte>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<byte>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<byte>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<byte>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<byte>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(byte));
			//	var v = buf_create.Extract<byte>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_short()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<short>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<short>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(short));
				var v = buf_create.Extract<short>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - byte
			{
				buf_create.Append<short>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(short));
				var v = buf_create.Extract<short>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - short
			{
				buf_create.Append<short>((short)100);
				Assert.IsTrue(buf_create.Count == sizeof(short));
				var v = buf_create.Extract<short>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - ushort
			//{
			//	buf_create.Append<short>((ushort)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - int
			{
				buf_create.Append<short>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(short));
				var v = buf_create.Extract<short>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - uint
			//{
			//	buf_create.Append<short>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<short>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<short>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<short>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<short>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(short));
			//	var v = buf_create.Extract<short>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_ushort()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<ushort>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - sbyte
			//{
			//	buf_create.Append<ushort>((sbyte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - byte
			{
				buf_create.Append<ushort>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(ushort));
				var v = buf_create.Extract<ushort>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - shrot
			//{
			//	buf_create.Append<ushort>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - ushort
			{
				buf_create.Append<ushort>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(ushort));
				var v = buf_create.Extract<ushort>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<ushort>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(ushort));
				var v = buf_create.Extract<ushort>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - uint
			//{
			//	buf_create.Append<ushort>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<ushort>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<ushort>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<ushort>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<ushort>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ushort));
			//	var v = buf_create.Extract<ushort>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_int()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<int>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<int>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(int));
				var v = buf_create.Extract<int>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - byte
			{
				buf_create.Append<int>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(int));
				var v = buf_create.Extract<int>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - short
			{
				buf_create.Append<int>((short)100);
				Assert.IsTrue(buf_create.Count == sizeof(int));
				var v = buf_create.Extract<int>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ushort
			{
				buf_create.Append<int>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(int));
				var v = buf_create.Extract<int>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<int>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(int));
				var v = buf_create.Extract<int>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - uint
			//{
			//	buf_create.Append<int>((uint)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - long
			//{
			//	buf_create.Append<int>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<int>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<int>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<int>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(int));
			//	var v = buf_create.Extract<int>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_uint()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<uint>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - sbyte
			//{
			//	buf_create.Append<uint>((sbyte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - byte
			{
				buf_create.Append<uint>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(uint));
				var v = buf_create.Extract<uint>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - short
			//{
			//	buf_create.Append<uint>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - ushort
			{
				buf_create.Append<uint>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(uint));
				var v = buf_create.Extract<uint>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<uint>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(uint));
				var v = buf_create.Extract<uint>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - uint
			{
				buf_create.Append<uint>((uint)100);
				Assert.IsTrue(buf_create.Count == sizeof(uint));
				var v = buf_create.Extract<uint>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - long
			//{
			//	buf_create.Append<uint>((long)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - ulong
			//{
			//	buf_create.Append<uint>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<uint>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<uint>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(uint));
			//	var v = buf_create.Extract<uint>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_long()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<long>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(long));
			//	var v = buf_create.Extract<long>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<long>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - byte
			{
				buf_create.Append<long>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - short
			{
				buf_create.Append<long>((short)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ushort
			{
				buf_create.Append<long>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<long>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - uint
			{
				buf_create.Append<long>((uint)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - long
			{
				buf_create.Append<long>((long)100);
				Assert.IsTrue(buf_create.Count == sizeof(long));
				var v = buf_create.Extract<long>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - ulong
			//{
			//	buf_create.Append<long>((ulong)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(long));
			//	var v = buf_create.Extract<long>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - float
			//{
			//	buf_create.Append<long>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(long));
			//	var v = buf_create.Extract<long>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<long>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(long));
			//	var v = buf_create.Extract<long>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}

		[TestMethod]
		public void test_buffer_general_append_ulong()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<ulong>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ulong));
			//	var v = buf_create.Extract<ulong>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - sbyte
			//{
			//	buf_create.Append<ulong>((sbyte)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ulong));
			//	var v = buf_create.Extract<ulong>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - byte
			{
				buf_create.Append<ulong>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - short
			//{
			//	buf_create.Append<ulong>((short)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ulong));
			//	var v = buf_create.Extract<ulong>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - ushort
			{
				buf_create.Append<ulong>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<ulong>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - uint
			{
				buf_create.Append<ulong>((uint)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - long
			{
				buf_create.Append<ulong>((long)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ulong
			{
				buf_create.Append<ulong>((ulong)100);
				Assert.IsTrue(buf_create.Count == sizeof(ulong));
				var v = buf_create.Extract<ulong>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - float
			//{
			//	buf_create.Append<ulong>((float)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ulong));
			//	var v = buf_create.Extract<ulong>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			//// - double
			//{
			//	buf_create.Append<ulong>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(ulong));
			//	var v = buf_create.Extract<ulong>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}


		[TestMethod]
		public void test_buffer_general_append_float()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<float>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(float));
			//	var v = buf_create.Extract<float>();
			//	Assert.IsTrue(v == 100);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<float>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - byte
			{
				buf_create.Append<float>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - short
			{
				buf_create.Append<float>((short)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ushort
			{
				buf_create.Append<float>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<float>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - uint
			buf_create.Append<float>((uint)100);
			{
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - long
			{
				buf_create.Append<float>((long)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ulong
			{
				buf_create.Append<float>((ulong)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - float
			{
				buf_create.Append<float>((float)100);
				Assert.IsTrue(buf_create.Count == sizeof(float));
				var v = buf_create.Extract<float>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			//// - double
			//{
			//	buf_create.Append<float>((double)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(float));
			//	var v = buf_create.Extract<float>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}
		}


		[TestMethod]
		public void test_buffer_general_append_double()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			//// - char
			//{
			//	buf_create.Append<double>((char)100);
			//	Assert.IsTrue(buf_create.Count == sizeof(double));
			//	var v = buf_create.Extract<double>();
			//	Assert.IsTrue(v == 100.0);
			//	Assert.IsTrue(buf_create.Count == 0);
			//}

			// - sbyte
			{
				buf_create.Append<double>((sbyte)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - byte
			{
				buf_create.Append<double>((byte)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - short
			{
				buf_create.Append<double>((short)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ushort
			{
				buf_create.Append<double>((ushort)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - int
			{
				buf_create.Append<double>((int)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - uint
			{
				buf_create.Append<double>((uint)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - long
			{
				buf_create.Append<double>((long)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - ulong
			{
				buf_create.Append<double>((ulong)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - float
			{
				buf_create.Append<double>((float)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}

			// - double
			{
				buf_create.Append<double>((double)100);
				Assert.IsTrue(buf_create.Count == sizeof(double));
				var v = buf_create.Extract<double>();
				Assert.IsTrue(v == 100.0);
				Assert.IsTrue(buf_create.Count == 0);
			}
		}

		[TestMethod]
		public void test_buffer_GetSizeOf_general()
		{
			char value1 = 'X';
			sbyte value2 = 0;
			byte value3 = 0;
			short value4 = 0;
			ushort value5 = 0;
			int value6 = 0;
			uint value7 = 0;
			long value8 = 0;
			ulong value9 = 0;
			UInt64 value10 = 0;
			float value11 = 0.0f;
			double value12 = 0.0;

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value1) == sizeof(char));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value2) == sizeof(sbyte));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value3) == sizeof(byte));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value4) == sizeof(short));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value5) == sizeof(ushort));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value6) == sizeof(int));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value7) == sizeof(uint));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value8) == sizeof(long));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value9) == sizeof(ulong));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value10) == sizeof(UInt64));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value11) == sizeof(float));
				Assert.IsTrue(CGDK.buffer.GetSizeOf(value12) == sizeof(double));
			}
		}

		[TestMethod]
		public void test_buffer_front_general()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

				buf_temp.Append<char>((char)12);
				var p0 = buf_temp.SetFront<char>((char)12);
				Assert.IsTrue(p0 == 2);
				var a0 = buf_temp.GetFront<char>();
				Assert.IsTrue(a0 == 12);

				buf_temp.Append<sbyte>((sbyte)3);
				var p1 = buf_temp.SetFront<sbyte>(3);
				Assert.IsTrue(p1 == 1);
				var a1 = buf_temp.GetFront<sbyte>();
				Assert.IsTrue(a1 == 3);

				buf_temp.Append<byte>((byte)4);
				var p2 = buf_temp.SetFront<byte>(4);
				Assert.IsTrue(p2 == 1);
				var a2 = buf_temp.GetFront<byte>();
				Assert.IsTrue(a2 == 4);

				buf_temp.Append<short>((short)4100);
				var p3 = buf_temp.SetFront<short>(4100);
				Assert.IsTrue(p3 == 2);
				var a3 = buf_temp.GetFront<short>();
				Assert.IsTrue(a3 == 4100);

				buf_temp.Append<ushort>((ushort)32210);
				var p4 = buf_temp.SetFront<ushort>(32210);
				Assert.IsTrue(p4 == 2);
				var a4 = buf_temp.GetFront<ushort>();
				Assert.IsTrue(a4 == 32210);

				buf_temp.Append<int>((int)123310);
				var p5 = buf_temp.SetFront<int>(123310);
				Assert.IsTrue(p5 == 4);
				var a5 = buf_temp.GetFront<int>();
				Assert.IsTrue(a5 == 123310);

				buf_temp.Append<uint>((uint)12);
				var p6 = buf_temp.SetFront<uint>(12);
				Assert.IsTrue(p6 == 4);
				var a6 = buf_temp.GetFront<uint>();
				Assert.IsTrue(a6 == 12);

				buf_temp.Append<long>((long)-1000443L);
				var p7 = buf_temp.SetFront<long>(-1000443L);
				Assert.IsTrue(p7 == 8);
				var a7 = buf_temp.GetFront<long>();
				Assert.IsTrue(a7 == -1000443L);

				buf_temp.Append<ulong>((ulong)12233094310UL);
				var p8 = buf_temp.SetFront<ulong>(12233094310UL);
				Assert.IsTrue(p8 == 8);
				var a8 = buf_temp.GetFront<ulong>();
				Assert.IsTrue(a8 == 12233094310UL);

				buf_temp.Append<float>((float)1.0f);
				var p9 = buf_temp.SetFront<float>(1.0f);
				Assert.IsTrue(p9 == 4);
				var a9 = buf_temp.GetFront<float>();
				Assert.IsTrue(a9 == 1.0f);

				buf_temp.Append<double>((double)2.0);
				var p10 = buf_temp.SetFront<double>(2.0);
				Assert.IsTrue(p10 == 8);
				var a10 = buf_temp.GetFront<double>();
				Assert.IsTrue(a10 == 2.0);
			}
		}

		[TestMethod]
		public void test_buffer_datetime1()
		{
			var tempTime = new DateTime(2016, 12, 11, 03, 12, 22);
			var size_source = CGDK.buffer.GetSizeOf(tempTime);

			// check) 
			Assert.IsTrue(size_source == 8);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(tempTime);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<DateTime>();

				// check) 
				Assert.IsTrue(tempTime == temp);
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		[TestMethod]
		public void test_buffer_appendextract_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

#if NET
				string?[] strResult;
#else
				string[] strResult;
#endif

				// - 값 써넣기
				function_append_STRING(ref buf_temp);
				strResult = function_extract_STRING(ref buf_temp);

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(strResult != null);
				Assert.IsTrue(array_string[0] == strResult[0]);
				Assert.IsTrue(array_string[1] == strResult[1]);
				Assert.IsTrue(array_string[2] == strResult[2]);
				Assert.IsTrue(array_string[3] == strResult[3]);
				Assert.IsTrue(array_string[4] == strResult[4]);
				Assert.IsTrue(array_string[5] == strResult[5]);
				Assert.IsTrue(array_string[6] == strResult[6]);
				Assert.IsTrue(array_string[7] == strResult[7]);
			}
		}

		[TestMethod]
		public void test_buffer_append_getfront_string()
		{
			var size_source = CGDK.buffer.GetSizeOf("test_String");

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

				// - 값 써넣기
				buf_temp.Append<string>("test_String");

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var result = buf_temp.GetFront<string>();

				// check) 
				Assert.IsTrue(result == "test_String");
			}
		}

		[TestMethod]
		public void test_buffer_append_array_int_extract_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(list_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<int[]>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(list_int.Count == temp.Length);
#if NET
				foreach (var (x, y) in list_int.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_array_int_get_front_array_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(list_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.GetFront<int[]>();

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(list_int.Count == temp.Length);
#if NET
				foreach (var (x, y) in list_int.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_array_string_extract_string()
		{
			var size_source = CGDK.buffer.GetSizeOf(array_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGDK.buffer buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(array_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<string[]>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(array_string.Length == temp.Length);
#if NET
				foreach (var (x, y) in array_string.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_array_string_get_front_string()
		{
			var size_source = CGDK.buffer.GetSizeOf(array_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(array_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

#if NET
				string[]? temp = buf_temp.GetFront<string[]>();
#else
				string[] temp = buf_temp.GetFront<string[]>();
#endif

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(array_string.Length == temp.Length);
#if NET
				foreach (var (x, y) in array_string.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_list_string_extract_general()
		{
			var size_source = CGDK.buffer.GetSizeOf(list_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(list_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<List<string>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(list_string.Count == temp.Count);
#if NET
				foreach (var (x, y) in list_string.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_list_string_get_front_list_string()
		{
			var size_source = CGDK.buffer.GetSizeOf(list_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(list_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.GetFront<List<string>>();

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(list_string.Count == temp.Count);
#if NET
				foreach (var (x, y) in list_string.Zip(temp))
					Assert.AreEqual(x, y);
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_int_int_extract_int_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_int_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_int_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<Dictionary<int, int>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_int_int.Count == temp.Count);
#if NET
				foreach (var (x, y) in dictionary_int_int.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_int_int_get_front_int_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_int_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_int_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp_size = buf_temp.Count;
				var temp_offset = new CGDK.Offset(0);

				// - 값 읽기
				var temp = buf_temp.GetFront<Dictionary<int, int>>(ref temp_offset);

				// check)
				Assert.IsTrue(temp_offset.amount == temp_size);

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_int_int.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_int_int.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_extract_string_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<Dictionary<string, int>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_string_int.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_string_int.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_extract_string_int_2()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<Dictionary<string, int>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_string_int.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_string_int.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_get_front_string_int()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_int);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				// - 값 읽기 GetFront
				var temp = buf_temp.GetFront<Dictionary<string, int>>();

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_string_int.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_string_int.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_string_extract_string_string()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.Extract<Dictionary<string, string>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_string_string.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_string_string.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_string_get_front_string_string()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				// - 값 읽기
			#if NET
				Dictionary<string, string>? temp = buf_temp.GetFront<Dictionary<string, string>>();
			#else
				Dictionary<string, string> temp = buf_temp.GetFront<Dictionary<string, string>>();
			#endif

				// check) 
				Assert.IsTrue(temp != null);
				Assert.IsTrue(dictionary_string_string.Count == temp.Count);
			#if NET
				foreach (var (x, y) in dictionary_string_string.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					Assert.AreEqual(x.Value, y.Value);
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_list_list_int_string_get_front()
		{
			var size_source = CGDK.buffer.GetSizeOf(list_list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(list_list_int);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				// - 값 써넣기
				buf_temp.Append(list_list_int);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source + size_source);

				var temp1 = buf_temp.Extract<List<List<int>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);
				Assert.IsTrue(temp1 != null);
			#if NET
				foreach (var (x, y) in list_list_int.Zip(temp1))
				{
					foreach (var (z, w) in x.Zip(y))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif

				var temp2 = buf_temp.GetFront<List<List<int>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);
				Assert.IsTrue(temp2 != null);
			#if NET
				foreach (var (x, y) in list_list_int.Zip(temp2))
				{
					foreach (var (z, w) in x.Zip(y))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_list_int_get_front()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_List_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_List_int);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_List_int);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source + size_source);

				var temp1 = buf_temp.Extract<Dictionary<string, List<int>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);
				Assert.IsTrue(temp1 != null);
			#if NET
				foreach (var (x, y) in dictionary_string_List_int.Zip(temp1))
				{
					Assert.AreEqual(x.Key, y.Key);
					foreach (var (z, w) in x.Value.Zip(y.Value))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif

				var temp2 = buf_temp.GetFront<Dictionary<string, List<int>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);
				Assert.IsTrue(temp2 != null);
			#if NET
				foreach (var (x, y) in dictionary_string_List_int.Zip(temp2))
				{
					Assert.AreEqual(x.Key, y.Key);
					foreach (var (z, w) in x.Value.Zip(y.Value))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_list_string_Extract()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_List_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_List_string);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var temp = buf_temp.Extract<Dictionary<string, List<string>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(temp != null);
			#if NET
				foreach (var (x, y) in dictionary_string_List_string.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					foreach (var (z, w) in x.Value.Zip(y.Value))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_list_string_GetFront()
		{
			var size_source = CGDK.buffer.GetSizeOf(dictionary_string_List_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.Append(dictionary_string_List_string);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var temp = buf_temp.GetFront<Dictionary<string, List<string>>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);
				Assert.IsTrue(temp != null);
			#if NET
				foreach (var (x, y) in dictionary_string_List_string.Zip(temp))
				{
					Assert.AreEqual(x.Key, y.Key);
					foreach (var (z, w) in x.Value.Zip(y.Value))
					{
						Assert.AreEqual(z, w);
					}
				}
			#endif
			}
		}

#if NET
		[TestMethod]
		public void test_buffer_append_Numeric()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			var v1 = new Vector2(1.0f, 1.0f);
			var v2 = new Vector3(1.0f, 1.0f, 1.0f);
			var v3 = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			var p1 = new Plane(1.0f, 0.0f, 0.0f, 1.0f);
			var m1 = new Matrix3x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			var m2 = new Matrix4x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<Vector2>(v1);
				bufferTemp.Append<Vector3>(v2);
				bufferTemp.Append<Vector4>(v3);
				bufferTemp.Append<Plane>(p1);
				bufferTemp.Append<Matrix3x2>(m1);
				bufferTemp.Append<Matrix4x4>(m2);

				// - 역직렬화
				var value1 = bufferTemp.Extract<Vector2>();
				Assert.IsTrue(value1.X == v1.X);
				Assert.IsTrue(value1.Y == v1.Y);

				var value2 = bufferTemp.Extract<Vector3>();
				Assert.IsTrue(value2.X == v2.X);
				Assert.IsTrue(value2.Y == v2.Y);
				Assert.IsTrue(value2.Z == v2.Z);

				var value3 = bufferTemp.Extract<Vector4>();
				Assert.IsTrue(value3.X == v3.X);
				Assert.IsTrue(value3.Y == v3.Y);
				Assert.IsTrue(value3.Z == v3.Z);
				Assert.IsTrue(value3.W == v3.W);

				var value4 = bufferTemp.Extract<Plane>();
				Assert.IsTrue(value4.Normal == p1.Normal);
				Assert.IsTrue(value4.D == p1.D);

				var value5 = bufferTemp.Extract<Matrix3x2>();
				Assert.IsTrue(value5.M11 == m1.M11);
				Assert.IsTrue(value5.M12 == m1.M12);
				Assert.IsTrue(value5.M21 == m1.M21);
				Assert.IsTrue(value5.M22 == m1.M22);
				Assert.IsTrue(value5.M31 == m1.M31);
				Assert.IsTrue(value5.M32 == m1.M32);

				var value6 = bufferTemp.Extract<Matrix4x4>();
				Assert.IsTrue(value6.M11 == m2.M11);
				Assert.IsTrue(value6.M12 == m2.M12);
				Assert.IsTrue(value6.M13 == m2.M13);
				Assert.IsTrue(value6.M14 == m2.M14);
				Assert.IsTrue(value6.M21 == m2.M21);
				Assert.IsTrue(value6.M22 == m2.M22);
				Assert.IsTrue(value6.M23 == m2.M23);
				Assert.IsTrue(value6.M24 == m2.M24);
				Assert.IsTrue(value6.M31 == m2.M31);
				Assert.IsTrue(value6.M32 == m2.M32);
				Assert.IsTrue(value6.M33 == m2.M33);
				Assert.IsTrue(value6.M34 == m2.M34);
				Assert.IsTrue(value6.M41 == m2.M41);
				Assert.IsTrue(value6.M42 == m2.M42);
				Assert.IsTrue(value6.M43 == m2.M43);
				Assert.IsTrue(value6.M44 == m2.M44);

				Assert.IsTrue(bufferTemp.Count== 0);
			}
		}
#endif

		public struct TEST
		{
			//[NonSerialized()]
			public int x;
			public float y;
			public UInt32 z;
			public ENUM_A w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST()
		{
			TEST temp = new TEST();
			temp.x = 10;
			temp.y = 1.0f;
			temp.z = 100;
			temp.w = ENUM_A.A;

			string temp_string = "Txxx";

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(100);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST>(temp);
				buf_temp.Append<string>(temp_string);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST>();
				var a3 = buf_temp.Extract<string>();
			}
		}


		struct TEST_B
		{
			public int x;
			public string y;
			public UInt32 z;
			public List<int> w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST_B()
		{
			TEST_B temp = new TEST_B();
			temp.x = 10;
			temp.y = "Tesfdsafdsafdsafdst";
			temp.z = 100;
			temp.w = new List<int> { 10, 20, 30 };

			string temp_string = "Txxfasgfsgfdfx";

			var size_a = CGDK.buffer.GetSizeOf((int)10);
			var size_b = CGDK.buffer.GetSizeOf(temp);
			var size_c = CGDK.buffer.GetSizeOf(temp_string);
			var size_source = size_a + size_b + size_c;

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST_B>(temp);
				buf_temp.Append<string>(temp_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST_B>();
				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		struct TEST_STATIC
		{
			public static int a;
			public int x;
			public string y;
			public UInt32 z;
			public List<int> w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST_STATIC()
		{
			var temp = new TEST_STATIC();
			TEST_STATIC.a = 100;
			temp.x = 10;
			temp.y = "Tesfdsafdsafdsafdst";
			temp.z = 100;
			temp.w = new List<int> { 10, 20, 30 };

			string temp_string = "Txxfasgfsgfdfx";

			var size_a = CGDK.buffer.GetSizeOf((int)10);
			var size_b = CGDK.buffer.GetSizeOf(temp);
			var size_c = CGDK.buffer.GetSizeOf(temp_string);
			var size_source = size_a + size_b + size_c;

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST_STATIC>(temp);
				buf_temp.Append<string>(temp_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST_STATIC>();
				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		struct TEST_CONST
		{
			public const int a = 100;
			public int x;
			public string y;
			public UInt32 z;
			public List<int> w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST_CONST()
		{
			var temp = new TEST_CONST();
			temp.x = 10;
			temp.y = "Tesfdsafdsafdsafdst";
			temp.z = 100;
			temp.w = new List<int> { 10, 20, 30 };

			string temp_string = "Txxfasgfsgfdfx";

			var size_a = CGDK.buffer.GetSizeOf((int)10);
			var size_b = CGDK.buffer.GetSizeOf(temp);
			var size_c = CGDK.buffer.GetSizeOf(temp_string);
			var size_source = size_a + size_b + size_c;

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST_CONST>(temp);
				buf_temp.Append<string>(temp_string);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST_CONST>();
				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		struct TEST_C
		{
			public int x;
			public List<int> y;
			public DateTime t;
			public TEST_B z;
			public ENUM_A a;

			[CGDK.Attribute.Field(false)] // 직렬화/역직렬화 대상에서 제외
			public TEST_B w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST_C_multi_level()
		{
			var temp = new TEST_C();
			temp.x = 10;
			temp.y = new List<int> { 1, 2, 3 };
			temp.t = new DateTime(1990, 12, 11, 10, 21, 11);
			temp.z.x = 10;
			temp.z.y = "Tesfdsafdsafdsafdst";
			temp.z.z = 100;
			temp.z.w = new List<int> { 10, 20, 30 };
			temp.a = ENUM_A.B;
			temp.w.x = 100;
			temp.w.y = "no serialized";
			temp.w.z = 123;
			temp.w.w = new List<int> { 1, 2, 3 };

			string temp_string;
			temp_string = "Txxfasgfsgfdfx";

			var tempDic = new Dictionary<long, long>();
			tempDic.Add(1, 100);
			tempDic.Add(2, 100);
			tempDic.Add(3, 100);
			tempDic.Add(4, 100);

			var size_a = CGDK.buffer.GetSizeOf((int)10);
			var size_b = CGDK.buffer.GetSizeOf(temp);
			var size_c = CGDK.buffer.GetSizeOf(temp_string);
			var size_d = CGDK.buffer.GetSizeOf(tempDic);
			var size_source = size_a + size_b + size_c + size_d;

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_a);

				buf_temp.Append<TEST_C>(temp);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_a + size_b);

				buf_temp.Append<string>(temp_string);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_a + size_b + size_c);

				buf_temp.Append<Dictionary<long, long>>(tempDic);

				// check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var a1 = buf_temp.Extract<int>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_b + size_c + size_d);
				Assert.IsTrue(a1 == 10);

				var a2 = buf_temp.Extract<TEST_C>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_c + size_d);
				Assert.IsTrue(a2.x == temp.x);
			#if NET
				foreach (var (x, y) in a2.y.Zip(temp.y))
					Assert.IsTrue(x == y);
			#endif
				Assert.IsTrue(a2.t == temp.t);
				Assert.IsTrue(a2.z.x == temp.z.x);
				Assert.IsTrue(a2.z.y == temp.z.y);
				Assert.IsTrue(a2.z.z == temp.z.z);
			#if NET
				foreach (var (x, y) in a2.z.w.Zip(temp.z.w))
					Assert.IsTrue(x == y);
			#endif
				Assert.IsTrue(a2.a == temp.a);
				Assert.IsTrue(a2.w.x == 0);     // excepted
				Assert.IsTrue(a2.w.y == null);  // excepted
				Assert.IsTrue(a2.w.z == 0);     // excepted
				Assert.IsTrue(a2.w.w == null);  // excepted

				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(buf_temp.Count == size_d);
				Assert.IsTrue(a3 == temp_string);

				var a4 = buf_temp.Extract<Dictionary<long, long>>();

				// check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(tempDic != null);
				Assert.IsTrue(a4 != null);
			#if NET
				foreach (var (x, y) in a4.Zip(tempDic))
				{
					Assert.IsTrue(x.Key == y.Key);
					Assert.IsTrue(x.Value == y.Value);
				}
			#endif
			}
		}

		[CGDK.Attribute.Serializable]
		public class TEST_CLASS1
		{
			public int a;
		#if NET
			[CGDK.Attribute.Field]
			public List<int>? b;
		#else
			[CGDK.Attribute.Field]
			public List<int> b;
		#endif

			int c { get { return 100; } set { } }

			[CGDK.Attribute.Field]
			public TEST d;

			public ENUM_A e;
		};

		[TestMethod]
		public void test_buffer_class_TEST_CLASS1_append_extract()
		{
			TEST_CLASS1 temp = new TEST_CLASS1();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.d = new TEST();
			temp.d.x = 10;
			temp.d.y = 1.0f;
			temp.d.z = 100;
			temp.d.w = ENUM_A.A;
			temp.e = ENUM_A.B;

			string temp_string = "Txxx";

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST_CLASS1>(temp);
				buf_temp.Append<string>(temp_string);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST_CLASS1>();
				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(a2 != null);
				Assert.IsTrue(a2.a == 0); // excepted
				Assert.IsTrue(a2.b == null);
				Assert.IsTrue(a2.d.x == temp.d.x);
				Assert.IsTrue(a2.d.y == temp.d.y);
				Assert.IsTrue(a2.d.z == temp.d.z);
				Assert.IsTrue(a2.d.w == temp.d.w);
				Assert.IsTrue(a2.e == 0); // excepted
			}
		}

		[TestMethod]
		public void test_buffer_class_TEST_CLASS1_GetSizeOf()
		{
			TEST_CLASS1 temp = new TEST_CLASS1();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.d = new TEST();
			temp.d.x = 10;
			temp.d.y = 1.0f;
			temp.d.z = 100;
			temp.d.w = ENUM_A.A;
			temp.e = ENUM_A.B;

			var buf_temp = new CGDK.buffer();

			buf_temp.Alloc(256);

			buf_temp.Append<TEST_CLASS1>(temp);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				int size_source = CGDK.buffer.GetSizeOf(temp);

				Assert.IsTrue(size_source == buf_temp.Count);
			}
		}

		public class TEST_CLASS2 : TEST_CLASS1
		{
			[CGDK.Attribute.Field]
			public UInt32 f;

		#if NET
			[CGDK.Attribute.Field]
			public int[]? g;
		#else
			[CGDK.Attribute.Field]
			public int[] g;
		#endif
		};


		[TestMethod]
		public void test_buffer_class_TEST_CLASS2_append_extract()
		{
			TEST_CLASS2 temp = new TEST_CLASS2();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.d = new TEST();
			temp.d.x = 10;
			temp.d.y = 1.0f;
			temp.d.z = 100;
			temp.d.w = ENUM_A.A;
			temp.e = ENUM_A.B;
			temp.f = 5;
			// temp.g 는 설정하지 않는다. -> null

			string temp_string = "Txxx";

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<int>(10);
				buf_temp.Append<TEST_CLASS2>(temp);
				buf_temp.Append<string>(temp_string);

				var a1 = buf_temp.Extract<int>();
				var a2 = buf_temp.Extract<TEST_CLASS2>();
				var a3 = buf_temp.Extract<string>();

				// check) 
				Assert.IsTrue(a1 == 10);
				Assert.IsTrue(a2 != null);
				Assert.IsTrue(a2.a == 0); // excepted
				Assert.IsTrue(a2.b == null); // excepted
				Assert.IsTrue(a2.d.x == temp.d.x);
				Assert.IsTrue(a2.d.y == temp.d.y);
				Assert.IsTrue(a2.d.z == temp.d.z);
				Assert.IsTrue(a2.d.w == temp.d.w);
				Assert.IsTrue(a2.e == 0); // excepted
				Assert.IsTrue(a2.f == temp.f);
				Assert.IsTrue(a2.g == temp.g); // null! => not created
				Assert.IsTrue(a3 == temp_string);
			}
		}

		[TestMethod]
		public void test_buffer_class_TEST_CLASS2_GetSizeOf()
		{
			TEST_CLASS2 temp = new TEST_CLASS2();
			temp.a = 10;
			//temp.b;				// 생성하지 않았다! (이 변수는 null일 것이다.)
			temp.d = new TEST();
			temp.d.x = 10;
			temp.d.y = 1.0f;
			temp.d.z = 100;
			temp.d.w = ENUM_A.A;
			temp.e = ENUM_A.B;
			temp.f = 5;

			var buf_temp = new CGDK.buffer();

			buf_temp.Alloc(256);

			buf_temp.Append<TEST_CLASS2>(temp);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				int size_source = CGDK.buffer.GetSizeOf(temp);

				Assert.IsTrue(size_source == buf_temp.Count);
			}
		}

		[TestMethod]
		public void test_buffer_append_extract_buffer()
		{
			var tempBufer2 = new CGDK.buffer();
			tempBufer2.Alloc(64);
			tempBufer2.Append<int>(100);
			tempBufer2.Append<int>(10000);
			tempBufer2.Append<int>(100000);

			var size_source = CGDK.buffer.GetSizeOf(tempBufer2);

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append(tempBufer2);

				Assert.IsTrue(size_source == buf_temp.Count);

				var rr = buf_temp.Extract<CGDK.buffer>();

				Assert.IsTrue(0 == buf_temp.Count);

				var v1 = rr.Extract<int>();
				var v2 = rr.Extract<int>();
				var v3 = rr.Extract<int>();

				Assert.IsTrue(v1 == 100);
				Assert.IsTrue(v2 == 10000);
				Assert.IsTrue(v3 == 100000);
			}
		}

		[TestMethod]
		public void test_buffer_enum()
		{
			var size_source = CGDK.buffer.GetSizeOf(ENUM_A.A);

			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<ENUM_A>(ENUM_A.A);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var result = buf_temp.Extract<ENUM_A>();

				// check) 
				Assert.IsTrue(result == ENUM_A.A);
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}
		[TestMethod]
		public void test_buffer_enum2()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			var temp_list = new List<ENUM_A>();
			temp_list.Add(ENUM_A.A);
			temp_list.Add(ENUM_A.B);
			temp_list.Add(ENUM_A.C);

			var size_source = CGDK.buffer.GetSizeOf(temp_list);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_Alloc;

				buf_temp.Append<List<ENUM_A>>(temp_list);

				// check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var result = buf_temp.Extract<List<ENUM_A>>();

				// check) 
				Assert.IsTrue(result != null);
				Assert.IsTrue(result.Count == 3);
				Assert.IsTrue(result[0] == ENUM_A.A);
				Assert.IsTrue(result[1] == ENUM_A.B);
				Assert.IsTrue(result[2] == ENUM_A.C);
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}
		[TestMethod]
		public void test_buffer_offset()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			Assert.IsTrue(buf_Alloc.Count == 12);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc + new CGDK.Offset(4);

				// check) 
				Assert.IsTrue(buf_temp.Count == 8);

				var v1 = buf_temp.Extract<int>();

				// check) 
				Assert.IsTrue(v1 == 10);

				// - 값 써넣기
				var buf_temp2 = buf_temp - new CGDK.Offset(4);

				// check) 
				Assert.IsTrue(buf_temp2.Count == 8);

				// - 읽기
				var v2 = buf_temp2.Extract<int>();

				// check) 
				Assert.IsTrue(v2 == 10);
			}
		}

		[TestMethod]
		public void test_buffer_offset_bound_plus()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc + new CGDK.Offset(12);

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 12);
				Assert.IsTrue(buf_temp.Count == 0);

				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp2 = buf_temp + new CGDK.Offset(13);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
		[TestMethod]
		public void test_buffer_offset_minus()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			// - 값 써넣기
			var buf_temp = buf_Alloc + new CGDK.Offset(8);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp2 = buf_temp + new CGDK.Offset(-4);

				// check) 
				Assert.IsTrue(buf_temp2.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp2.Offset == 4);
				Assert.IsTrue(buf_temp2.Count == 8);

				// - Bound 딱 경계
				var buf_temp3 = buf_temp + new CGDK.Offset(-8);

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp4 = buf_temp + new CGDK.Offset(-9);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}

		[TestMethod]
		public void test_buffer_size_minus()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc - new CGDK.Size(12);

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 0);
				Assert.IsTrue(buf_temp.Count == 0);

				// - Bound 딱 경계
				var buf_temp2 = buf_Alloc - new CGDK.Size(12);

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp3 = buf_Alloc - new CGDK.Size(13);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
		[TestMethod]
		public void test_buffer_size_plus()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(24);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{

				// - 값 써넣기
				var buf_temp = buf_Alloc + new CGDK.Size(12);

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 0);
				Assert.IsTrue(buf_temp.Count == 24);

				// - Bound 딱 경계
				var buf_temp2 = buf_Alloc + new CGDK.Size(12);

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp3 = buf_Alloc + new CGDK.Size(13);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
		[TestMethod]
		public void test_buffer_operator_set_offset()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc ^ new CGDK.Offset(12);

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 12);
				Assert.IsTrue(buf_temp.Count == 12);

				// - Bound 딱 경계
				var buf_temp2 = buf_temp ^ new CGDK.Size(244);

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp3 = buf_temp ^ new CGDK.Size(245);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
		[TestMethod]
		public void test_buffer_operator_set_size()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc ^ new CGDK.Size(12);

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 0);
				Assert.IsTrue(buf_temp.Count == 12);

				// - Bound 딱 경계
				var buf_temp2 = buf_temp ^ new CGDK.Size(256);

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp3 = buf_temp ^ new CGDK.Size(257);

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
		[TestMethod]
		public void test_buffer_operator_set_offset_size()
		{
			var buf_Alloc = new CGDK.buffer();

			buf_Alloc.Alloc(256);

			buf_Alloc.Append<int>(100);
			buf_Alloc.Append<int>(10);
			buf_Alloc.Append<int>(1);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 값 써넣기
				var buf_temp = buf_Alloc ^ ( new CGDK.Offset(12), new CGDK.Size(12));

				// check) 
				Assert.IsTrue(buf_temp.Data == buf_Alloc.Data);
				Assert.IsTrue(buf_temp.Offset == 12);
				Assert.IsTrue(buf_temp.Count == 12);

				// - Bound 딱 경계
				var buf_temp2 = buf_temp ^ (new CGDK.Offset(12), new CGDK.Size(244));

				// - Bound owerflow
				// 주의) 이 부분은 CGDK.buffe가 Debug일 때 Assert가 걸리므로 Reelase로 컴파일된 CGDK.buffer dll을 쓸때만 정상 통과합니다.
				try
				{
					// - Bound를 넘기는 offset
					var buf_temp3 = buf_temp ^ (new CGDK.Offset(12), new CGDK.Size(245));

					// check) 
					Assert.IsTrue(false);
				}
				catch (System.IndexOutOfRangeException)
				{
				}
			}
		}
	}
}