using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace CSharp_UnitTest_Performance_CGDBuffers
{
	[TestClass]
	public class CSharp_UnitTest_Performance_CGDBuffers
	{
		public const int _TEST_COUNT = 1000000;

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
			{0,		0},
			{3,		2},
			{5,		3},
			{6,		14},
			{7,		5},
			{10,	11}
		};

		public Dictionary<string, int> dictionary_string_int = new Dictionary<string, int>
		{
			{"zero",	0},
			{"two",		2},
			{"tree",	3},
			{"fifteen",	14},
			{"five",	5},
			{"eleven",	11}
		};

		public Dictionary<string, string> dictionary_string_string = new Dictionary<string, string>
		{
			{"zero",	"0"},
			{"two",		"2"},
			{"tree",	"3"},
			{"fifteen",	"14"},
			{"five",	"5"},
			{"eleven",	"11"}
		};

		public Dictionary<string, List<int>> dictionary_string_List_int = new Dictionary<string, List<int>>
		{
			{"zero",	new List<int> {0,1,2,4}},
			{"two",		new List<int> {3,1,22,4}},
			{"tree",	new List<int> {4,1,12,4}},
			{"fifteen",	new List<int> {5,1,82,4}},
			{"five",	new List<int> {7,1,22,4}},
			{"eleven",	new List<int> {10,21,12,34}}
		};

		public Dictionary<string, List<string>> dictionary_string_List_string = new Dictionary<string, List<string>>
		{
			{"zero",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"two",		new List<string> {"zero", "zero", "zero", "zero"}},
			{"tree",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"fifteen",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"five",	new List<string> {"zero", "zero", "zero", "zero"}},
			{"eleven",	new List<string> {"zero", "zero", "zero", "zero"}}
		};

		struct TEST
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

		void function_append_GENERAL(ref CGD.buffer _Buffer)
		{
			_Buffer.append<char>((char)12);
			_Buffer.append<sbyte>((byte)3);
			_Buffer.append<byte>((sbyte)4);
			_Buffer.append<short>((short)4100);
			_Buffer.append<ushort>((ushort)32210);
			_Buffer.append<int>(123310);
			_Buffer.append<uint>(121234);
			_Buffer.append<long>(-1000443L);
			_Buffer.append<ulong>(12233094310UL);
			_Buffer.append<float>(1.0f);
			_Buffer.append<double>(2.0);
		}

		void function_extract_GENERAL(ref CGD.buffer _Buffer)
		{
			var value1 = _Buffer.extract<char>();
			var value2 = _Buffer.extract<sbyte>();
			var value3 = _Buffer.extract<byte>();
			var value4 = _Buffer.extract<short>();
			var value5 = _Buffer.extract<ushort>();
			var value6 = _Buffer.extract<int>();
			var value7 = _Buffer.extract<uint>();
			var value8 = _Buffer.extract<long>();
			var value9 = _Buffer.extract<ulong>();
			var value10 = _Buffer.extract<float>();
			var value11 = _Buffer.extract<double>();
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
		public void TestMethod_General_append_extract()
		{
			// 1) Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 2) 값 써넣기
				bufferTemp.append<sbyte>((sbyte)3);
				bufferTemp.append<byte>((byte)4);
				bufferTemp.append<short>((short)4100);
				bufferTemp.append<ushort>((ushort)32210);
				bufferTemp.append<int>(123310);
				bufferTemp.append<uint>(121234);
				bufferTemp.append<long>(-1000443L);
				bufferTemp.append<ulong>(12233094310UL);
				bufferTemp.append<float>(1.0f);
				bufferTemp.append<double>(2.0);

				// 3) 값 읽기
				var value0	 = bufferTemp.extract<sbyte>();
				var value1	 = bufferTemp.extract<byte>();
				var value2	 = bufferTemp.extract<short>();
				var value3	 = bufferTemp.extract<ushort>();
				var value4	 = bufferTemp.extract<int>();
				var value5	 = bufferTemp.extract<uint>();
				var value6	 = bufferTemp.extract<long>();
				var value7	 = bufferTemp.extract<ulong>();
				var value8	 = bufferTemp.extract<float>();
				var value9	 = bufferTemp.extract<double>();
			}
		}
		[TestMethod]
		public void TestMethod_General_append_extract_struct()
		{
			// 1) Buffer 할당
			CGD.buffer	bufferCreate = new CGD.buffer(2048);
			TEST		tempData	 = new TEST();
			
			tempData.v0	 = 	(sbyte)3;
			tempData.v1	 = 	(byte)4;
			tempData.v2	 = 	(short)4100;
			tempData.v3	 = 	(ushort)32210;
			tempData.v4	 = 	123310;
			tempData.v5	 = 	121234;
			tempData.v6	 = 	-1000443L;
			tempData.v7	 = 	12233094310UL;
			tempData.v8	 = 	1.0f;
			tempData.v9	 = 	2.0;
			
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 2) 값 써넣기
				bufferTemp.append<TEST>(tempData);

				// 3) 값 읽기
				var value2 = bufferTemp.extract<TEST>();
			}
		}
		[TestMethod]
		public void TestMethod_String_append_extract()
		{
			// 1) Buffer 할당
			CGD.buffer	bufferCreate	 = new CGD.buffer(2048);
			string[]	stringExtract	 = new string[8];

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append<string>(array_string[0]);
				bufferTemp.append<string>(array_string[1]);
				bufferTemp.append<string>(array_string[2]);
				bufferTemp.append<string>(array_string[3]);
				bufferTemp.append<string>(array_string[4]);
				bufferTemp.append<string>(array_string[5]);
				bufferTemp.append<string>(array_string[6]);
				bufferTemp.append<string>(array_string[7]);

				// 4) 값 읽기
				stringExtract[0] = bufferTemp.extract<string>();
				stringExtract[1] = bufferTemp.extract<string>();
				stringExtract[2] = bufferTemp.extract<string>();
				stringExtract[3] = bufferTemp.extract<string>();
				stringExtract[4] = bufferTemp.extract<string>();
				stringExtract[5] = bufferTemp.extract<string>();
				stringExtract[6] = bufferTemp.extract<string>();
				stringExtract[7] = bufferTemp.extract<string>();
			}
		}

		[TestMethod]
		public void TestMethod_List_int_append_extract()
		{
			// 1) Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(list_int);

				// 4) 값 읽기
				var	temp = bufferTemp.extract<List<int>>();
			}
		}

		[TestMethod]
		public void TestMethod_List_string_append_extract()
		{
			// 1) Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(list_int);

				// 4) 값 읽기
				var temp = bufferTemp.extract<List<int>>();
			}
		}

		[TestMethod]
		public void TestMethod_Associated_string_list_int_append_extract()
		{
			// 1) Buffer 할당
			CGD.buffer bufferCreate = new CGD.buffer(2048);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 2) Buffer 준비
				CGD.buffer bufferTemp = bufferCreate;

				// 3) 값 써넣기
				bufferTemp.append(dictionary_string_List_int);

				// 4) 값 읽기
				var temp = bufferTemp.extract<Dictionary<string, List<int>> >();
			}
		}

	}
}
