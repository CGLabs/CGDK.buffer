using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace CGDBuffer_CSharp_UnitTest
{
    [TestClass]
    public class CGDbuffer_CSharp_Unittest_Functional
    {
		public const int _TEST_COUNT = 10000;

		public enum ENUM_A
		{
			A	 = 10,
			B	 = 20,
			C	 = 30,
			D	 = 40,
			E	 = 50
		}

		[Serializable]
		public class CTest
		{
			[CGDK.Attribute.Serializable]
			public int	x;

			[CGDK.Attribute.Serializable]
			public int	y;
			public int	z;
		}

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

		public Dictionary<int, int>	dictionary_int_int = new Dictionary<int, int>
		{
			{0,		0},
			{3,		2},
			{5,		3},
			{6,		14},
			{7,		5},
			{10,	11}
		};

		public Dictionary<string, int>	dictionary_string_int = new Dictionary<string, int>
		{
			{"zero",	0},
			{"two",		2},
			{"tree",	3},
			{"fifteen",	14},
			{"five",	5},
			{"eleven",	11}
		};

		public Dictionary<string, string>	dictionary_string_string = new Dictionary<string, string>
		{
			{"zero",	"0"},
			{"two",		"2"},
			{"tree",	"3"},
			{"fifteen",	"14"},
			{"five",	"5"},
			{"eleven",	"11"}
		};

		public Dictionary<string, List<int>>	dictionary_string_List_int = new Dictionary<string, List<int>>
		{
			{"zero",	new List<int> {0,1,2,4}},
			{"two",		new List<int> {3,1,22,4}},
			{"tree",	new List<int> {4,1,12,4}},
			{"fifteen",	new List<int> {5,1,82,4}},
			{"five",	new List<int> {7,1,22,4}},
			{"eleven",	new List<int> {10,21,12,34}}
		};

		public Dictionary<string, List<string>>	dictionary_string_List_string = new Dictionary<string, List<string>>
		{
			{"zero",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"two",		new List<string> {"zero", "zero", "zero", "zero"}},
			{"tree",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"fifteen",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"five",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"eleven",	new List<string> {"zero", "zero", "zero", "zero"}}
		};

		void function_append_GENERAL_1(ref CGDK.buffer _buffer)
		{
			_buffer.append<char>((char)12);
			_buffer.append<sbyte>((sbyte)3);
			_buffer.append<byte>((byte)4);
			_buffer.append<short>((short)4100);
			_buffer.append<ushort>((ushort)32210);
			_buffer.append<int>((int)123310);
			_buffer.append<uint>((uint)12);
			_buffer.append<long>((long)-1000443L);
			_buffer.append<ulong>((ulong)12233094310UL);
			_buffer.append<float>((float)1.0f);
			_buffer.append<double>((double)2.0);
		}

		void function_append_GENERAL_2(ref CGDK.buffer _buffer)
		{
			_buffer.append((char)12);
			_buffer.append((sbyte)3);
			_buffer.append((byte)4);
			_buffer.append((short)4100);
			_buffer.append((ushort)32210);
			_buffer.append((int)123310);
			_buffer.append((uint)12);
			_buffer.append((long)-1000443L);
			_buffer.append((ulong)12233094310UL);
			_buffer.append((float)1.0f);
			_buffer.append((double)2.0);
		}

		void function_extract_GENERAL_1(ref CGDK.buffer _buffer)
		{
			var value1  = _buffer.extract<char>();
			var value2  = _buffer.extract<sbyte>();
			var value3  = _buffer.extract<byte>();
			var value4  = _buffer.extract<short>();
			var value5  = _buffer.extract<ushort>();
			var value6  = _buffer.extract<int>();
			var value7  = _buffer.extract<uint>();
			var value8  = _buffer.extract<long>();
			var value9  = _buffer.extract<ulong>();
            var value10 = _buffer.extract<float>();
            var value11 = _buffer.extract<double>();
		}

		void function_extract_GENERAL_2(ref CGDK.buffer _buffer)
		{
			var value1  = _buffer.extract_char();
			var value2  = _buffer.extract_sbyte();
			var value3  = _buffer.extract_byte();
			var value4  = _buffer.extract_short();
			var value5  = _buffer.extract_ushort();
			var value6  = _buffer.extract_int();
			var value7  = _buffer.extract_uint();
			var value8  = _buffer.extract_long();
			var value9  = _buffer.extract_ulong();
			var value10 = _buffer.extract_float();
			var value11 = _buffer.extract_double();
		}


		void function_append_STRING(ref CGDK.buffer _buffer)
		{
			_buffer.append<string>(array_string[0]);
			_buffer.append<string>(array_string[1]);
			_buffer.append<string>(array_string[2]);
			_buffer.append<string>(array_string[3]);
			_buffer.append<string>(array_string[4]);
			_buffer.append<string>(array_string[5]);
			_buffer.append<string>(array_string[6]);
			_buffer.append<string>(array_string[7]);
		}

		string[] function_extract_STRING(ref CGDK.buffer _buffer)
		{
			string[] temp = new string[8];

			temp[0] = _buffer.extract<string>();
			temp[1] = _buffer.extract<string>();
			temp[2] = _buffer.extract<string>();
			temp[3] = _buffer.extract<string>();
			temp[4] = _buffer.extract<string>();
			temp[5] = _buffer.extract<string>();
			temp[6] = _buffer.extract<string>();
			temp[7] = _buffer.extract<string>();

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
				var	buf_temp = buf_create;

				// - 값 써넣기
				function_extract_GENERAL_1(ref buf_temp);
			}
		}

		[TestMethod]
		public void test_buffer_general_extract_2()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			function_append_GENERAL_2(ref buf_create);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Temp
				var buf_temp = buf_create;

				// - 값 써넣기
				function_extract_GENERAL_2(ref buf_temp);
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
			buf_create.append<char>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<char>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<char>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<char>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<char>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<char>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<char>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<char>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<char>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<char>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(char));
			buf_create.extract<char>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			try
			{
				buf_create.append<char>((float)100);

				// Error float는 char로 넣을 수 없다.
				Assert.IsTrue(false);
			}
			catch (System.Exception)
			{
			}

			// - double
			try
			{
				buf_create.append<char>((double)100);

				// Error float는 char로 넣을 수 없다.
				Assert.IsTrue(false);
			}
			catch (System.Exception)
			{
			}
		}

		[TestMethod]
		public void test_buffer_general_append_sbyte()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<sbyte>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<sbyte>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<sbyte>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<sbyte>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<sbyte>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<sbyte>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<sbyte>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<sbyte>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<sbyte>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<sbyte>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<sbyte>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(sbyte));
			buf_create.extract<sbyte>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_byte()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<byte>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<byte>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - bytes
			buf_create.append<byte>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<byte>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<byte>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<byte>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<byte>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<byte>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<byte>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<byte>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<byte>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(byte));
			buf_create.extract<byte>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_short()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<short>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<short>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<short>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<short>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<short>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<short>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<short>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<short>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<short>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<short>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<short>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(short));
			buf_create.extract<short>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_ushort()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<ushort>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<ushort>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<ushort>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - shrot
			buf_create.append<ushort>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<ushort>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<ushort>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<ushort>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<ushort>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<ushort>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<ushort>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<ushort>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(ushort));
			buf_create.extract<ushort>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_int()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<int>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<int>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<int>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<int>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<int>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<int>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<int>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<int>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<int>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<int>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<int>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(int));
			buf_create.extract<int>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_uint()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<uint>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<uint>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<uint>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<uint>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<uint>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<uint>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<uint>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<uint>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<uint>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<uint>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<uint>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(uint));
			buf_create.extract<uint>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_long()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<long>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<long>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<long>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<long>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<long>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<long>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<long>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<long>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<long>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<long>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<long>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(long));
			buf_create.extract<long>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_general_append_ulong()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			buf_create.append<ulong>((char)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - sbyte
			buf_create.append<ulong>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<ulong>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<ulong>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<ulong>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<ulong>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<ulong>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<ulong>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<ulong>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<ulong>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<ulong>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(ulong));
			buf_create.extract<ulong>();
			Assert.IsTrue(buf_create.Count == 0);
		}


		[TestMethod]
		public void test_buffer_general_append_float()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			try 
			{ 
				buf_create.append<float>((char)100);

				// Error float는 char로 넣을 수 없다.
				Assert.IsTrue(false);
			}
			catch (System.Exception)
			{
			}

			// - sbyte
			buf_create.append<float>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<float>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<float>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<float>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<float>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<float>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<float>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<float>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<float>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<float>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(float));
			buf_create.extract<float>();
			Assert.IsTrue(buf_create.Count == 0);
		}


		[TestMethod]
		public void test_buffer_general_append_double()
		{
			// - Buffer 할당
			var buf_create = new CGDK.buffer(1024);

			// - char
			try
			{
				buf_create.append<double>((char)100);

				// Error float는 char로 넣을 수 없다.
				Assert.IsTrue(false);
			}
			catch (System.Exception)
			{
			}

			// - sbyte
			buf_create.append<double>((sbyte)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - byte
			buf_create.append<double>((byte)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - short
			buf_create.append<double>((short)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ushort
			buf_create.append<double>((ushort)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - int
			buf_create.append<double>((int)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - uint
			buf_create.append<double>((uint)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - long
			buf_create.append<double>((long)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - ulong
			buf_create.append<double>((ulong)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - float
			buf_create.append<double>((float)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);

			// - double
			buf_create.append<double>((double)100);
			Assert.IsTrue(buf_create.Count == sizeof(double));
			buf_create.extract<double>();
			Assert.IsTrue(buf_create.Count == 0);
		}

		[TestMethod]
		public void test_buffer_get_size_of_general()
		{
			char		value1	 = 'X';
			sbyte		value2	 = 0;
			byte		value3	 = 0;
			short		value4	 = 0;
			ushort		value5	 = 0;
			int			value6	 = 0;
			uint		value7	 = 0;
			long		value8	 = 0;
			ulong		value9	 = 0;
			UInt64		value10	 = 0;
			float		value11	 = 0.0f;
			double		value12	 = 0.0;

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				Assert.IsTrue(CGDK.buffer.get_size_of(value1) == Marshal.SizeOf(value1));
				Assert.IsTrue(CGDK.buffer.get_size_of(value2) == sizeof(sbyte));
				Assert.IsTrue(CGDK.buffer.get_size_of(value3) == sizeof(byte));
				Assert.IsTrue(CGDK.buffer.get_size_of(value4) == sizeof(short));
				Assert.IsTrue(CGDK.buffer.get_size_of(value5) == sizeof(ushort));
				Assert.IsTrue(CGDK.buffer.get_size_of(value6) == sizeof(int));
				Assert.IsTrue(CGDK.buffer.get_size_of(value7) == sizeof(uint));
				Assert.IsTrue(CGDK.buffer.get_size_of(value8) == sizeof(long));
				Assert.IsTrue(CGDK.buffer.get_size_of(value9) == sizeof(ulong));
				Assert.IsTrue(CGDK.buffer.get_size_of(value10) == sizeof(UInt64));
				Assert.IsTrue(CGDK.buffer.get_size_of(value11) == sizeof(float));
				Assert.IsTrue(CGDK.buffer.get_size_of(value12) == sizeof(double));
			}
		}

		[TestMethod]
		public void test_buffer_front_general()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

				buf_temp.append<char>((char)12);
				buf_temp.set_front<char>((char)12);
				var	a0	 = buf_temp.get_front<char>();
				Assert.IsTrue(a0==12);

				buf_temp.append<sbyte>((sbyte)3);
				buf_temp.set_front<sbyte>(3);
				var	a1	 = buf_temp.get_front<sbyte>();
				Assert.IsTrue(a1==3);

				buf_temp.append<byte>((byte)4);
				buf_temp.set_front<byte>(4);
				var	a2	 = buf_temp.get_front<byte>();
				Assert.IsTrue(a2==4);

				buf_temp.append<short>((short)4100);
				buf_temp.set_front<short>(4100);
				var	a3	 = buf_temp.get_front<short>();
				Assert.IsTrue(a3==4100);

				buf_temp.append<ushort>((ushort)32210);
				buf_temp.set_front<ushort>(32210);
				var	a4	 = buf_temp.get_front<ushort>();
				Assert.IsTrue(a4==32210);

				buf_temp.append<int>((int)123310);
				buf_temp.set_front<int>(123310);
				var	a5	 = buf_temp.get_front<int>();
				Assert.IsTrue(a5==123310);

				buf_temp.append<uint>((uint)12);
				buf_temp.set_front<uint>(12);
				var	a6	 = buf_temp.get_front<uint>();
				Assert.IsTrue(a6==12);

				buf_temp.append<long>((long)-1000443L);
				buf_temp.set_front<long>(-1000443L);
				var	a7	 = buf_temp.get_front<long>();
				Assert.IsTrue(a7==-1000443L);

				buf_temp.append<ulong>((ulong)12233094310UL);
				buf_temp.set_front<ulong>(12233094310UL);
				var	a8	 = buf_temp.get_front<ulong>();
				Assert.IsTrue(a8==12233094310UL);

				buf_temp.append<float>((float)1.0f);
				buf_temp.set_front<float>(1.0f);
				var	a9	 = buf_temp.get_front<float>();
				Assert.IsTrue(a9==1.0f);

				buf_temp.append<double>((double)2.0);
				buf_temp.set_front<double>(2.0);
				var	a10	 = buf_temp.get_front<double>();
				Assert.IsTrue(a10==2.0);
			}
		}

		[TestMethod]
		public void test_buffer_datetime1()
		{
			var tempTime = new DateTime(2016, 12, 11, 03, 12, 22);
			var size_source = CGDK.buffer.get_size_of(tempTime);

			// check) 
			Assert.IsTrue(size_source == 8);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(tempTime);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<DateTime>();

				// Check) 
				Assert.IsTrue(tempTime == temp);
				Assert.IsTrue(buf_temp.size == 0);
			}
		}

		[TestMethod]
		public void test_buffer_appendextract_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

				string[] strResult;

				// - 값 써넣기
				function_append_STRING(ref buf_temp);
				strResult = function_extract_STRING(ref buf_temp);

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
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
		public void test_buffer_append_getfront_string()
		{
			var size_source = CGDK.buffer.get_size_of("test_String");

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(1024);

				// - 값 써넣기
				buf_temp.append<string>("test_String");

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var result = buf_temp.get_front<string>();

				// Check) 
				Assert.IsTrue(result == "test_String");
			}
		}

		[TestMethod]
		public void test_buffer_append_array_int_extract_int()
		{
			var size_source = CGDK.buffer.get_size_of(list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(list_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<int[]>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(list_int.Count==temp.Length);
				for(int j=0;j<list_int.Count;++j)
					Assert.AreEqual(list_int[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_array_int_get_front_array_int()
		{
			var size_source = CGDK.buffer.get_size_of(list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(list_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.get_front<int[]>();

				// Check) 
				Assert.IsTrue(list_int.Count==temp.Length);
				for(int j=0;j<list_int.Count;++j)
					Assert.AreEqual(list_int[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_array_string_extract_string()
		{
			var size_source = CGDK.buffer.get_size_of(array_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				CGDK.buffer buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(array_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<string[]>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(array_string.Length==temp.Length);
				for(int j=0;j<array_string.Length;++j)
					Assert.AreEqual(array_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_array_string_get_front_string()
		{
			var size_source = CGDK.buffer.get_size_of(array_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(array_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				string[] temp = buf_temp.get_front<string[]>();

				// Check) 
				Assert.IsTrue(array_string.Length==temp.Length);
				for(int j=0;j<array_string.Length;++j)
					Assert.AreEqual(array_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_list_string_extract_general()
		{
			var size_source = CGDK.buffer.get_size_of(list_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(list_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<List<string>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(list_string.Count==temp.Count);
				for(int j=0;j<list_string.Count;++j)
					Assert.AreEqual(list_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_list_string_get_front_list_string()
		{
			var size_source = CGDK.buffer.get_size_of(list_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(list_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.get_front<List<string>>();

				// Check) 
				Assert.IsTrue(list_string.Count==temp.Count);
				for(int j=0;j<list_string.Count;++j)
					Assert.AreEqual(list_string[j], temp[j]);
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_int_int_extract_int_int()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_int_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_int_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<Dictionary<int, int>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(dictionary_int_int.Count==temp.Count);
				var ka = dictionary_int_int.Keys.GetEnumerator();
				var va = dictionary_int_int.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_int_int_get_front_int_int()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_int_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_int_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				// - 값 읽기
				var temp = buf_temp.get_front<Dictionary<int, int>>();

				// Check) 
				Assert.IsTrue(dictionary_int_int.Count==temp.Count);
				var ka = dictionary_int_int.Keys.GetEnumerator();
				var va = dictionary_int_int.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_extract_string_int()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(dictionary_string_int.Count==temp.Count);
				var ka = dictionary_string_int.Keys.GetEnumerator();
				var va = dictionary_string_int.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_extract_string_int_2()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == 0);
				Assert.IsTrue(dictionary_string_int.Count == temp.Count);
				var ka = dictionary_string_int.Keys.GetEnumerator();
				var va = dictionary_string_int.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while (ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current == kb.Current);
					Assert.IsTrue(va.Current == vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_int_get_front_string_int()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_int);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				// - 값 읽기 get_front
				var temp = buf_temp.get_front<Dictionary<string, int>>();

				// Check) 
				Assert.IsTrue(dictionary_string_int.Count==temp.Count);
				var ka = dictionary_string_int.Keys.GetEnumerator();
				var va = dictionary_string_int.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_string_extract_string_string()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp =buf_temp.extract<Dictionary<string, string>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count==0);
				Assert.IsTrue(dictionary_string_string.Count==temp.Count);
				var ka = dictionary_string_string.Keys.GetEnumerator();
				var va = dictionary_string_string.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_string_get_front_string_string()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				// - 값 읽기
				Dictionary<string, string> temp = buf_temp.get_front<Dictionary<string, string>>();

				// Check) 
				Assert.IsTrue(dictionary_string_string.Count==temp.Count);
				var ka = dictionary_string_string.Keys.GetEnumerator();
				var va = dictionary_string_string.Values.GetEnumerator();
				var kb = temp.Keys.GetEnumerator();
				var vb = temp.Values.GetEnumerator();
				while(ka.MoveNext() && kb.MoveNext() && va.MoveNext() && vb.MoveNext())
				{
					Assert.IsTrue(ka.Current==kb.Current);
					Assert.IsTrue(va.Current==vb.Current);
				}
			}
		}

		[TestMethod]
		public void test_buffer_append_list_list_int_string_get_front()
		{
			var size_source = CGDK.buffer.get_size_of(list_list_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(list_list_int);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				// - 값 써넣기
				buf_temp.append(list_list_int);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source + size_source);

				var temp1 = buf_temp.extract<List<List<int>>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var temp2 = buf_temp.extract<List<List<int>>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_list_int_get_front()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_List_int);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_List_int);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				// - 값 써넣기
				buf_temp.append(dictionary_string_List_int);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source + size_source);

				var temp1 = buf_temp.extract<Dictionary<string, List<int>>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var temp2 = buf_temp.extract<Dictionary<string, List<int>>>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == 0);
			}
		}

		[TestMethod]
		public void test_buffer_append_dictionary_string_list_string_get_front()
		{
			var size_source = CGDK.buffer.get_size_of(dictionary_string_List_string);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - Buffer 할당
				var buf_temp = new CGDK.buffer(2048);

				// - 값 써넣기
				buf_temp.append(dictionary_string_List_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var temp = buf_temp.extract<Dictionary<string, List<string>>>();
			}
		}

		public struct TEST
		{
			[NonSerialized()]
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

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(100);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<int>(10);
				buf_temp.append<TEST>(temp);
				buf_temp.append<string>(temp_string);

				var a1 = buf_temp.extract<int>();
				var a2 = buf_temp.extract<TEST>();
				var a3 = buf_temp.extract<string>();
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

			var size_a = CGDK.buffer.get_size_of((int)10);
			var size_b = CGDK.buffer.get_size_of(temp);
			var size_c = CGDK.buffer.get_size_of(temp_string);
			var size_source = size_a + size_b + size_c;

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<int>(10);
				buf_temp.append<TEST_B>(temp);
				buf_temp.append<string>(temp_string);

				// Check) 
				Assert.IsTrue(size_source == buf_temp.Count);

				var a1 = buf_temp.extract<int>();
				var a2 = buf_temp.extract<TEST_B>();
				var a3 = buf_temp.extract<string>();

				// Check) 
				Assert.IsTrue(buf_temp.size == 0);
			}
		}


		struct TEST_C
		{
			public int			x;
			public List<int>	y;
			public DateTime		t;
			public TEST_B		z;
			public ENUM_A		a;

			[NonSerialized()]
			public TEST_B		w;
		};

		[TestMethod]
		public void test_buffer_struct_TEST_C_multi_level()
		{
			TEST_C temp = new TEST_C();
			temp.x	 = 10;
			temp.y	 = new List<int> { 1, 2, 3};
			temp.t	 = new DateTime(1990, 12, 11, 10, 21, 11);
			temp.z.x = 10;
			temp.z.y = "Tesfdsafdsafdsafdst";
			temp.z.z = 100;
			temp.z.w = new List<int> { 10, 20, 30};
			temp.a   = ENUM_A.B;
			temp.w.x = 100;
			temp.w.y = "no serialized";
			temp.w.z = 123;
			temp.w.w = new List<int> { 1, 2, 3 };
			
			string temp_string;
			temp_string = "Txxfasgfsgfdfx";

			Dictionary<long, long>	tempDic	 = new Dictionary<long, long>();
			tempDic.Add(1, 100);
			tempDic.Add(2, 100);
			tempDic.Add(3, 100);
			tempDic.Add(4, 100);

			var size_a = CGDK.buffer.get_size_of((int)10);
			var size_b = CGDK.buffer.get_size_of(temp);
			var size_c = CGDK.buffer.get_size_of(temp_string);
			var size_d = CGDK.buffer.get_size_of(tempDic);
			var size_source = size_a + size_b + size_c + size_d;

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(size_source);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<int>(10);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_a);

				buf_temp.append<TEST_C>(temp);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_a + size_b);

				buf_temp.append<string>(temp_string);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_a + size_b + size_c);

				buf_temp.append<Dictionary<long, long>>(tempDic);

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_source);

				var a1 = buf_temp.extract<int>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_b + size_c + size_d);

				var a2 = buf_temp.extract<TEST_C>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_c + size_d);

				var a3 = buf_temp.extract<string>();

				// Check) 
				Assert.IsTrue(buf_temp.Count == size_d);

				var a4 = buf_temp.extract<Dictionary<long, long>>();

				// Check) 
				Assert.IsTrue(buf_temp.size == 0);
			}
		}

		[Serializable]
		public class TEST_CLASS1
		{
			public int a;
		#if NET
			public List<int>? b;
		#else
			public List<int> b;
		#endif

			[CGDK.Attribute.Serializable]
			int c { get { return 100;} set { } }

			[CGDK.Attribute.Serializable]
			public TEST d;

			[CGDK.Attribute.Serializable]
			public ENUM_A e;
		};

		[CGDK.Attribute.Serializable]
		public class TEST_CLASS2 : TEST_CLASS1
		{
			[CGDK.Attribute.Serializable]
			public UInt32 f;

			[CGDK.Attribute.Serializable]
		#if NET
			public int[]? g;
		#else
			public int[] g;
		#endif
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

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<int>(10);
				buf_temp.append<TEST_CLASS1>(temp);
				buf_temp.append<string>(temp_string);

				var a1 = buf_temp.extract<int>();
				var a2 = buf_temp.extract<TEST_CLASS1>();
				var a3 = buf_temp.extract<string>();
			}
        }

		[TestMethod]
		public void test_buffer_class_TEST_CLASS1_get_size_of()
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

			buf_temp.alloc(256);

			buf_temp.append<TEST_CLASS1>(temp);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				int size_source = CGDK.buffer.get_size_of(temp);

				Assert.IsTrue(size_source == buf_temp.Count);
			}
		}

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

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<int>(10);
				buf_temp.append<TEST_CLASS2>(temp);
				buf_temp.append<string>(temp_string);

				var a1 = buf_temp.extract<int>();
				var a2 = buf_temp.extract<TEST_CLASS2>();
				var a3 = buf_temp.extract<string>();
			}
        }

		[TestMethod]
		public void test_buffer_class_TEST_CLASS2_get_size_of()
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

			buf_temp.alloc(256);

			buf_temp.append<TEST_CLASS2>(temp);


			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				int size_source = CGDK.buffer.get_size_of(temp);

				Assert.IsTrue(size_source == buf_temp.Count);
			}
		}

		[TestMethod]
		public void test_buffer_append_extract_buffer()
		{
			var tempBufer2 = new CGDK.buffer();
			tempBufer2.alloc(64);
			tempBufer2.append<int>(100);
			tempBufer2.append<int>(100);
			tempBufer2.append<int>(100);

			var size_source = CGDK.buffer.get_size_of(tempBufer2);

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(256);
			
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append(tempBufer2);

				Assert.IsTrue(size_source == buf_temp.Count);

				var rr = buf_temp.extract<CGDK.buffer>();

				Assert.IsTrue(0 == buf_temp.Count);
			}
		}

		[TestMethod]
		public void test_buffer_enum()
		{
			var size_source = CGDK.buffer.get_size_of(ENUM_A.A);

			var buf_alloc = new CGDK.buffer();

			buf_alloc.alloc(256);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				var buf_temp = buf_alloc;

				buf_temp.append<ENUM_A>(ENUM_A.A);

				Assert.IsTrue(size_source == buf_temp.Count);

				buf_temp.extract<ENUM_A>();

				Assert.IsTrue(buf_temp.size == 0);
			}
		}
	}
}