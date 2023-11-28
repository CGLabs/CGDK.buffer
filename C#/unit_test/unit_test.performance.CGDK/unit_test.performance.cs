using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;


namespace CGDBuffer_CSharp_UnitTest_CGDKbuffer
{
	[TestClass]
	public class Performance
	{
		public const int _TEST_COUNT = 1000000;

		private static readonly int[] array_int = 
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

		private static readonly string[] array_string = {
			"Please Let test this",
			"이것 좀 테스트하게 해주세요.",
			"这件事 试验",
			"これを試ためさせてください",
			"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
			"Please 这件事 試ためさせてください 합시다.",
			"Test What ever",
			"1234"};

		private static readonly List<int> list_int = new List<int>
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

		private static readonly List<List<int>> list_list_int = new List<List<int>>
		{
			new List<int> {0, 0, 3},
			new List<int> {3, 2, 64},
			new List<int> {5, 3, 11},
			new List<int> {6, 14, 13},
			new List<int> {7, 5, 200, 400, 12, 33},
			new List<int> {10, 11, 12,900}
		};

		private static readonly List<string> list_string = new List<string> {
			"Please Let test this",
			"이것 좀 테스트하게 해주세요.",
			"这件事 试验",
			"これを試ためさせてください",
			"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
			"Please 这件事 試ためさせてください 합시다.",
			"Test What ever",
			"1234"};

		private static readonly Dictionary<int, int> dictionary_int_int = new Dictionary<int, int>
		{
			{0,		0},
			{3,		2},
			{5,		3},
			{6,		14},
			{7,		5},
			{10,	11}
		};

		private static readonly Dictionary<string, int> dictionary_string_int = new Dictionary<string, int>
		{
			{"zero",	0},
			{"two",		2},
			{"tree",	3},
			{"fifteen",	14},
			{"five",	5},
			{"eleven",	11}
		};

		private static readonly Dictionary<string, string> dictionary_string_string = new Dictionary<string, string>
		{
			{"zero",	"0"},
			{"two",		"2"},
			{"tree",	"3"},
			{"fifteen",	"14"},
			{"five",	"5"},
			{"eleven",	"11"}
		};

		private static readonly Dictionary<string, List<int>> dictionary_string_List_int = new Dictionary<string, List<int>>
		{
			{"zero",	new List<int> {0,1,2,4}},
			{"two",		new List<int> {3,1,22,4}},
			{"tree",	new List<int> {4,1,12,4}},
			{"fifteen",	new List<int> {5,1,82,4}},
			{"five",	new List<int> {7,1,22,4}},
			{"eleven",	new List<int> {10,21,12,34}}
		};

		private static readonly Dictionary<string, List<string>> dictionary_string_List_string = new Dictionary<string, List<string>>
		{
			{"zero",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"two",		new List<string> {"zero", "zero", "zero", "zero"}},
			{"tree",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"fifteen",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"five",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"eleven",	new List<string> {"zero", "zero", "zero", "zero"}}
		};

		[CGDK.Attribute.Serializable]
		public struct TEST
		{
			public	sbyte	v0;
			public	byte	v1;
			public	short	v2;
			public	ushort	v3;
			public	int		v4;
			public	uint	v5;
			public	long	v6;
			public	ulong	v7;
			public	float	v8;
			public	double	v9;
		};

		static void function_append_GENERAL(ref CGDK.buffer _Buffer)
		{
			_Buffer.Append<char>((char)12);
			_Buffer.Append<sbyte>((sbyte)3);
			_Buffer.Append<byte>((byte)4);
			_Buffer.Append<short>((short)4100);
			_Buffer.Append<ushort>((ushort)32210);
			_Buffer.Append<int>((int)123310);
			_Buffer.Append<uint>((uint)121234);
			_Buffer.Append<long>((long)-1000443L);
			_Buffer.Append<ulong>((ulong)12233094310UL);
			_Buffer.Append<float>((float)1.0f);
			_Buffer.Append<double>((double)2.0);
		}

		static void function_extract_GENERAL(ref CGDK.buffer _Buffer)
		{
			var value1 = _Buffer.Extract<char>();
			var value2 = _Buffer.Extract<sbyte>();
			var value3 = _Buffer.Extract<byte>();
			var value4 = _Buffer.Extract<short>();
			var value5 = _Buffer.Extract<ushort>();
			var value6 = _Buffer.Extract<int>();
			var value7 = _Buffer.Extract<uint>();
			var value8 = _Buffer.Extract<long>();
			var value9 = _Buffer.Extract<ulong>();
			var value10 = _Buffer.Extract<float>();
			var value11 = _Buffer.Extract<double>();
		}

		static void function_append_STRING(ref CGDK.buffer _Buffer)
		{
			_Buffer.Append<string>(array_string[0]);
			_Buffer.Append<string>(array_string[1]);
			_Buffer.Append<string>(array_string[2]);
			_Buffer.Append<string>(array_string[3]);
			_Buffer.Append<string>(array_string[4]);
			_Buffer.Append<string>(array_string[5]);
			_Buffer.Append<string>(array_string[6]);
			_Buffer.Append<string>(array_string[7]);
		}

		[TestInitialize]
		public void TestInitialize()
		{
		#if NET
			CGDK.BufferSerializer.Generator.Initialize();
		#endif

		}
	#if NET
		static string?[] function_extract_STRING(ref CGDK.buffer _Buffer)
	#else
		static string[] function_extract_STRING(ref CGDK.buffer _Buffer)
	#endif
		{
		#if NET
			string?[] temp = new string[8];
		#else
			string[] temp = new string[8];
		#endif

			temp[0] = _Buffer.Extract<string>();
			temp[1] = _Buffer.Extract<string>();
			temp[2] = _Buffer.Extract<string>();
			temp[3] = _Buffer.Extract<string>();
			temp[4] = _Buffer.Extract<string>();
			temp[5] = _Buffer.Extract<string>();
			temp[6] = _Buffer.Extract<string>();
			temp[7] = _Buffer.Extract<string>();

			return temp;
		}

		[TestMethod]
		public void CGDKb_benchmark_01_primitive()
		{
			Int32 value_1 = 1;
			UInt32 value_2 = 101;
			Int64 value_3 = -12345;
			UInt64 value_4 = 123456;
			float value_5 = 1.0f;
			double value_6 = 10.0;

			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<int>(value_1);
				bufferTemp.Append<uint>(value_2);
				bufferTemp.Append<long>(value_3);
				bufferTemp.Append<ulong>(value_4);
				bufferTemp.Append<float>(value_5);
				bufferTemp.Append<double>(value_6);

				// - 역직렬화
				var d_value_1 = bufferTemp.Extract<Int32>();
				var d_value_2 = bufferTemp.Extract<UInt32>();
				var d_value_3 = bufferTemp.Extract<Int64>();
				var d_value_4 = bufferTemp.Extract<UInt64>();
				var d_value_5 = bufferTemp.Extract<float>();
				var d_value_6 = bufferTemp.Extract<double>();
			}
		}

		[TestMethod]
		public void CGDKb_benchmark_02_list_int()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append(list_int);

				// - 역직렬화
				var temp = bufferTemp.Extract<List<int>>();
			}
		}

		[TestMethod]
		public void CGDKb_benchmark_03_string()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<string>(array_string[0]);
				bufferTemp.Append<string>(array_string[1]);
				bufferTemp.Append<string>(array_string[2]);
				bufferTemp.Append<string>(array_string[3]);
				bufferTemp.Append<string>(array_string[4]);
				bufferTemp.Append<string>(array_string[5]);
				bufferTemp.Append<string>(array_string[6]);
				bufferTemp.Append<string>(array_string[7]);

				// - 역직렬화
				var value_1 = bufferTemp.Extract<string>();
				var value_2 = bufferTemp.Extract<string>();
				var value_3 = bufferTemp.Extract<string>();
				var value_4 = bufferTemp.Extract<string>();
				var value_5 = bufferTemp.Extract<string>();
				var value_6 = bufferTemp.Extract<string>();
				var value_7 = bufferTemp.Extract<string>();
				var value_8 = bufferTemp.Extract<string>();
			}
		}

		[TestMethod]
		public void CGDKb_benchmark_04_list_string()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append(list_string);

				// - 역직렬화
				var temp = bufferTemp.Extract<List<string>>();
			}
		}

		[TestMethod]
		public void CGDKb_benchmark_05_key_value_int_int()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append(dictionary_int_int);

				// - 역직렬화
				var temp = bufferTemp.Extract<Dictionary<int,int>>();
			}
		}
		[TestMethod]
		public void CGDKb_benchmark_06_key_value_string_string()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<Dictionary<string, string>>(dictionary_string_string);

				// - 역직렬화
				var temp = bufferTemp.Extract<Dictionary<string,string>>();
			}
		}
		[TestMethod]
		public void CGDKb_benchmark_07_key_value_string_list_int()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 버퍼 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<Dictionary<string, List<int>>>(dictionary_string_List_int);

				// - 역직렬화
				var temp = bufferTemp.Extract<Dictionary<string, List<int>>>();
			}
		}

		[TestMethod]
		public void CGDKb_benchmark_08_struct_primitive()
		{
			// - 버퍼 준비
			CGDK.buffer	bufferCreate = new CGDK.buffer(2048);
			TEST tempData = new TEST
			{
				v0 = (sbyte)3,
				v1 = (byte)4,
				v2 = (short)4100,
				v3 = (ushort)32210,
				v4 = 123310,
				v5 = 121234,
				v6 = -1000443L,
				v7 = 12233094310UL,
				v8 = 1.0f,
				v9 = 2.0
			};

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<TEST>(tempData);

				// - 역직렬화
				var value2 = bufferTemp.Extract<TEST>();
			}
		}

		[CGDK.Attribute.Serializable]
		public struct TEST_EX
		{
			public int v1;

			public string v2;

			public List<int> v3;

			public UInt64 v4;

			public Dictionary<string, int> v5;
		}
		[TestMethod]
		public void CGDKb_benchmark_09_struct_composite()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			var foo = new TEST_EX
			{
				v1 = 100,
				v2 = "test_string",
				v3 = new List<int> { 1, 2, 3, 4, 5 },
				v4 = 10000,
				v5 = new Dictionary<string, int> { { "a", 1 }, { "b", 2 }, { "c", 3 } }
			};

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<TEST_EX>(foo);

				// - 역직렬화
				var value2 = bufferTemp.Extract<TEST_EX>();
			}
		}


		[CGDK.Attribute.Serializable]
		public class TEST_EX2
		{
			[CGDK.Attribute.Field]
			public int v1;

			[CGDK.Attribute.Field]
#if NET
			public string? v2;
#else
			public string v2;
#endif

#if NET
			private List<int>? v3;
#else
			private List<int> v3;
#endif

			[CGDK.Attribute.Field]
			public UInt64 v4;

			[CGDK.Attribute.Field]
#if NET
			public Dictionary<string, int>? v5;
#else
			public Dictionary<string, int> v5;
#endif

			[CGDK.Attribute.Field]
			public int value_6 
			{
				get { return this.v6; }
				set { this.v6 = value; }
			}

			private int v6;
		}

		[TestMethod]
		public void CGDKb_benchmark_10_class_composite()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);

			var foo = new TEST_EX2
			{
				v1 = 100,
				v2 = "test_string",
				//foo.v3 = new List<int> { 1, 2, 3, 4, 5 };
				v4 = 10000,
				v5 = new Dictionary<string, int> { { "a", 1 }, { "b", 2 }, { "c", 3 } },
				value_6 = 10
			};

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<TEST_EX2>(foo);

				// - 역직렬화
				var value2 = bufferTemp.Extract<TEST_EX2>();
			}
		}

		[CGDK.Attribute.Serializable]
		public struct TEST3
		{
			public TEST x;
		};

		[TestMethod]
		public void CGDKb_benchmark_11_struct_hierachy()
		{
			// - 버퍼 준비
			CGDK.buffer bufferCreate = new CGDK.buffer(2048);
			TEST3 tempData = new TEST3();

			tempData.x.v0 = (sbyte)3;
			tempData.x.v1 = (byte)4;
			tempData.x.v2 = (short)4100;
			tempData.x.v3 = (ushort)32210;
			tempData.x.v4 = 123310;
			tempData.x.v5 = 121234;
			tempData.x.v6 = -1000443L;
			tempData.x.v7 = 12233094310UL;
			tempData.x.v8 = 1.0f;
			tempData.x.v9 = 2.0;

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGDK.buffer bufferTemp = bufferCreate;

				// - 직렬화
				bufferTemp.Append<TEST3>(tempData);

				// - 역직렬화
				var value2 = bufferTemp.Extract<TEST3>();
			}
		}

	}
}
