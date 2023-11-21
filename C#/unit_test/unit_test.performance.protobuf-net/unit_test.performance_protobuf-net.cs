using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.IO;
using ProtoBuf;

namespace UnitTest_Performance_Protobuf
{
	[TestClass]
	public class Performance
	{
		public const int _TEST_COUNT = 1000000;

		[ ProtoContract]
		class TEST_CHAR {
			[ProtoMember(1)]
			public char value {	get; set;}
		}

		[ProtoContract]
		class TEST_BYTE
		{
			[ProtoMember(1)]
			public	byte value {	get; set;}
		}

		[ProtoContract]
		class TEST_SBYTE
		{
			[ProtoMember(1)]
			public	sbyte value {	get; set;}
		}

		[ProtoContract]
		class TEST_SHORT
		{
			[ProtoMember(1)]
			public	short value {	get; set;}
		}

		[ProtoContract]
		class TEST_USHORT
		{
			[ProtoMember(1)]
			public	ushort value {	get; set;}
		}

		[ProtoContract]
		class TEST_INT
		{
			[ProtoMember(1)]
			public	int value {	get; set;}
		}

		[ProtoContract]
		class TEST_UINT
		{
			[ProtoMember(1)]
			public	uint value {	get; set;}
		}

		[ProtoContract]
		class TEST_LONG
		{
			[ProtoMember(1)]
			public	long value {	get; set;}
		}

		[ProtoContract]
		class TEST_ULONG
		{
			[ProtoMember(1)]
			public	ulong value {	get; set;}
		}

		[ProtoContract]
		class TEST_FLOAT
		{
			[ProtoMember(1)]
			public	float value {	get; set;}
		}

		[ProtoContract]
		class TEST_DOUBLE
		{
			[ProtoMember(1)]
			public	double value {	get; set;}
		}

		[ProtoContract]
		class TEST_STRING
		{
			[ProtoMember(1)]
		#if NET
			public	string? value {	get; set;}
		#else
			public	string	value {	get; set;}
		#endif
		}


		[ProtoContract]
		class TEST 
		{
			[ProtoMember(1)]
			public	sbyte value0 = default;
			[ProtoMember(2)]
			public	byte value1 = default;
			[ProtoMember(3)]
			public	short value2 = default;
			[ProtoMember(4)]
			public	ushort value3 = default;
			[ProtoMember(5)]
			public	int value4 = default;
			[ProtoMember(6)]
			public	uint value5 = default;
			[ProtoMember(7)]
			public	long value6 = default;
			[ProtoMember(8)]
			public	ulong value7 = default;
			[ProtoMember(9)]
			public	float value8 = default;
			[ProtoMember(10)]
			public	double value9 = default;
		};

		[ProtoContract]
		class TEST_X
		{
			[ProtoMember(1)]
			public	int		value0 = default;
			[ProtoMember(2)]
			public	uint	value1 = default;
			[ProtoMember(3)]
			public	short	value2 = default;
			[ProtoMember(4)]
			public	short	value3 = default;
		};

		[ProtoContract]
		class TEST_EX
		{
			[ProtoMember(1)]
			public int value0 = default;
		#if NET
			[ProtoMember(2)]
			public string? value1 = default;
			[ProtoMember(3)]
			public List<int>? value2 = default;
#else
			[ProtoMember(2)]
			public string value1 = default;
			[ProtoMember(3)]
			public List<int> value2 = default;
#endif
			[ProtoMember(4)]
			public UInt64 value3;
			[ProtoMember(5)]
		#if NET
			public Dictionary<string,int>? value4 = default;
#else
			public Dictionary<string,int> value4 = default;
#endif
		};

		class TEST_Y
		{
			[ProtoMember(1)]
			public	short	value0 = default;
			[ProtoMember(2)]
			public	short	value1 = default;
			[ProtoMember(3)]
			public	int		value2 = default;
			[ProtoMember(4)]
			public	int		value3 = default;
		};

		[ProtoContract]
		class TEST2
		{
			[ProtoMember(1)]
		#if NET
			public	string?	value0 = default;
#else
			public	string	value0 = default;
#endif
		};

		[ProtoContract]
		class TEST3
		{
			[ProtoMember(1)]
		#if NET
			public	List<int>?	value0 = default;
#else
			public	List<int>	value0 = default;
#endif
		};

		[ProtoContract]
		class TEST4
		{
			[ProtoMember(1)]
		#if NET
			public	List<string>?	value0 = default;
#else
			public	List<string>	value0 = default;
#endif
		};

		[ProtoContract]
		class TEST5
		{
			[ProtoMember(1)]
		#if NET
			public	Dictionary<string, List<int>>?	value0 = default;
#else
			public	Dictionary<string, List<int>>	value0 = default;
#endif
		};

		[ProtoContract]
		class TEST6
		{
			[ProtoMember(1)]
			public int		value0 = default;

			[ProtoMember(2)]
		#if NET
			public	TEST2?	value1 = default;
#else
			public	TEST2	value1 = default;
#endif
		};


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

		[TestMethod]
		public void PrBfn_benchmark_01_primitive()
		{
			MemoryStream memSerialize = new MemoryStream(4096);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<Int32>((Stream)memSerialize, 1);
				ProtoBuf.Serializer.Serialize<UInt32>((Stream)memSerialize, 101);
				ProtoBuf.Serializer.Serialize<Int64>((Stream)memSerialize, -12345);
				ProtoBuf.Serializer.Serialize<UInt64>((Stream)memSerialize, 123456);
				ProtoBuf.Serializer.Serialize<float>((Stream)memSerialize, 1.0f);
				ProtoBuf.Serializer.Serialize<double>((Stream)memSerialize, 10.0);

				// 2) 값 읽기
				var tempDeserialize0 = Serializer.Deserialize<Int32>(memSerialize);
				var tempDeserialize1 = Serializer.Deserialize<UInt32>(memSerialize);
				var tempDeserialize2 = Serializer.Deserialize<Int64>(memSerialize);
				var tempDeserialize3 = Serializer.Deserialize<UInt64>(memSerialize);
				var tempDeserialize4 = Serializer.Deserialize<float>(memSerialize);
				var tempDeserialize5 = Serializer.Deserialize<double>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_02_list_int()
		{
			var tempObject = new TEST3 { value0 = list_int };

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST3>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize = Serializer.Deserialize<TEST3>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_03_string()
		{
			MemoryStream memSerialize = new MemoryStream(4096);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Write
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[0]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[1]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[2]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[3]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[4]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[5]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[6]);
				ProtoBuf.Serializer.Serialize<string>((Stream)memSerialize, array_string[7]);

				// 2) Read
				var tempDeserialize0 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize1 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize2 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize3 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize4 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize5 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize6 = Serializer.Deserialize<string>(memSerialize);
				var tempDeserialize7 = Serializer.Deserialize<string>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_04_list_string()
		{
			var tempObject = new TEST4 { value0 = list_string };

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST4>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize = Serializer.Deserialize<TEST4>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_05_key_value_int_int()
		{
			//var tempObject = new TEST5 { value0 = dictionary_int_int };

			//MemoryStream memSerialize = new MemoryStream();

			//for (int i = 0; i < _TEST_COUNT; ++i)
			//{
			//	memSerialize.SetLength(0);

			//	// 1) 값 써넣기
			//	ProtoBuf.Serializer.Serialize<TEST5>((Stream)memSerialize, tempObject);

			//	memSerialize.Seek(0, SeekOrigin.Begin);

			//	// 2) 값 읽기
			//	var tempDeserialize = Serializer.Deserialize<TEST5>(memSerialize);
			//}
		}
		[TestMethod]
		public void PrBfn_benchmark_05_key_value_string_string()
		{
			//var tempObject = new TEST5 { value0 = dictionary_string_string };

			//MemoryStream memSerialize = new MemoryStream();

			//for (int i = 0; i < _TEST_COUNT; ++i)
			//{
			//	memSerialize.SetLength(0);

			//	// 1) 값 써넣기
			//	ProtoBuf.Serializer.Serialize<TEST5>((Stream)memSerialize, tempObject);

			//	memSerialize.Seek(0, SeekOrigin.Begin);

			//	// 2) 값 읽기
			//	var tempDeserialize = Serializer.Deserialize<TEST5>(memSerialize);
			//}
		}
		[TestMethod]
		public void PrBfn_benchmark_07_key_value_string_list_int()
		{
			var tempObject = new TEST5 { value0 = dictionary_string_List_int };

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST5>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize = Serializer.Deserialize<TEST5>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_08_struct_primitive()
		{
			var tempObject = new TEST
			{
				value0 = 3,
				value1 = 4,
				value2 = 4100,
				value3 = 32210,
				value4 = 123310,
				value5 = 121234,
				value6 = -1000443L,
				value7 = 12233094310UL,
				value8 = 1.0f,
				value9 = 2.0
			};
			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize0 = Serializer.Deserialize<TEST>(memSerialize);
			}
		}
		[TestMethod]
		public void PrBfn_benchmark_09_struct_composite()
		{
			var tempObject = new TEST_EX();
			tempObject.value0 = 100;
			tempObject.value1 = "test_string";
			tempObject.value2 = new List<int> { 1, 2, 3, 4, 5 };
			tempObject.value3 = 10000;
			tempObject.value4 = new Dictionary<string, int> { { "a", 1 }, { "b", 2 }, { "c", 3 } };

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0;i<_TEST_COUNT;++i) 
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST_EX>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0,SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize0 = Serializer.Deserialize<TEST_EX>(memSerialize);
			}
		}

		[TestMethod]
		public void PrBfn_benchmark_extra_01_general()
		{
			MemoryStream memSerialize = new MemoryStream(4096);

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<byte>((Stream)memSerialize, 3);
				ProtoBuf.Serializer.Serialize<sbyte>((Stream)memSerialize, 4);
				ProtoBuf.Serializer.Serialize<short>((Stream)memSerialize, 4100);
				ProtoBuf.Serializer.Serialize<ushort>((Stream)memSerialize, 32210);
				ProtoBuf.Serializer.Serialize<int>((Stream)memSerialize, 123310);
				ProtoBuf.Serializer.Serialize<uint>((Stream)memSerialize, 121234);
				ProtoBuf.Serializer.Serialize<long>((Stream)memSerialize, 1000443L);
				ProtoBuf.Serializer.Serialize<ulong>((Stream)memSerialize, 12233094310UL);
				ProtoBuf.Serializer.Serialize<float>((Stream)memSerialize, 1.0f);
				ProtoBuf.Serializer.Serialize<double>((Stream)memSerialize, 2.0);

				// 2) 값 읽기
				var tempDeserialize0 = Serializer.Deserialize<byte>(memSerialize);
				var tempDeserialize1 = Serializer.Deserialize<sbyte>(memSerialize);
				var tempDeserialize2 = Serializer.Deserialize<short>(memSerialize);
				var tempDeserialize3 = Serializer.Deserialize<ushort>(memSerialize);
				var tempDeserialize4 = Serializer.Deserialize<int>(memSerialize);
				var tempDeserialize5 = Serializer.Deserialize<uint>(memSerialize);
				var tempDeserialize6 = Serializer.Deserialize<long>(memSerialize);
				var tempDeserialize7 = Serializer.Deserialize<ulong>(memSerialize);
				var tempDeserialize8 = Serializer.Deserialize<float>(memSerialize);
				var tempDeserialize9 = Serializer.Deserialize<double>(memSerialize);
			}
		}

		[TestMethod]
		public void PrBfn_benchmark_extra_02_multi_leveled()
		{
			TEST6 tempObject = new TEST6();

			tempObject.value0 = 10;
			tempObject.value1 = new TEST2();
			tempObject.value1.value0 = "TempString";

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST6>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize = Serializer.Deserialize<TEST6>(memSerialize);

				Assert.IsTrue(tempObject.value0 == tempDeserialize.value0);
				Assert.IsTrue(tempObject.value1 != null);
				Assert.IsTrue(tempObject.value1 != null);
				Assert.IsTrue(tempObject.value1?.value0 == tempDeserialize.value1?.value0);
			}
		}


		[TestMethod]
		public void PrBfn_benchmark_extra_03_multi_leveled3()
		{
			TEST_X	tempObject = new TEST_X();

			tempObject.value0 = 10;
			tempObject.value1 = 20;
			tempObject.value2 = 20;
			tempObject.value3 = 20;

			MemoryStream memSerialize = new MemoryStream();

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST_X>((Stream)memSerialize, tempObject);

				memSerialize.Seek(0, SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize = Serializer.Deserialize<TEST_X>(memSerialize);
			}
		}

		[TestMethod]
		public void PrBfn_benchmark_extra_04_append_peek_string()
		{
			TEST2[] tempObject = new TEST2[8];
			MemoryStream[] memSerialize = new MemoryStream[8];

			for (int i = 0; i < tempObject.Length; ++i)
			{
				tempObject[i] = new TEST2();
				tempObject[i].value0 = list_string[i];

				memSerialize[i] = new MemoryStream(256);
			}

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// 1) Write
				memSerialize[0].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[0], tempObject[0]);
				memSerialize[1].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[1], tempObject[1]);
				memSerialize[2].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[2], tempObject[2]);
				memSerialize[3].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[3], tempObject[3]);
				memSerialize[4].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[4], tempObject[4]);
				memSerialize[5].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[5], tempObject[5]);
				memSerialize[6].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[6], tempObject[6]);
				memSerialize[7].SetLength(0); ProtoBuf.Serializer.Serialize<TEST2>((Stream)memSerialize[7], tempObject[7]);

				// 2) Read
				memSerialize[0].Seek(0, SeekOrigin.Begin); var tempDeserialize1 = Serializer.Deserialize<TEST2>(memSerialize[0]).value0;
				memSerialize[1].Seek(0, SeekOrigin.Begin); var tempDeserialize2 = Serializer.Deserialize<TEST2>(memSerialize[1]).value0;
				memSerialize[2].Seek(0, SeekOrigin.Begin); var tempDeserialize3 = Serializer.Deserialize<TEST2>(memSerialize[2]).value0;
				memSerialize[3].Seek(0, SeekOrigin.Begin); var tempDeserialize4 = Serializer.Deserialize<TEST2>(memSerialize[3]).value0;
				memSerialize[4].Seek(0, SeekOrigin.Begin); var tempDeserialize5 = Serializer.Deserialize<TEST2>(memSerialize[4]).value0;
				memSerialize[5].Seek(0, SeekOrigin.Begin); var tempDeserialize6 = Serializer.Deserialize<TEST2>(memSerialize[5]).value0;
				memSerialize[6].Seek(0, SeekOrigin.Begin); var tempDeserialize7 = Serializer.Deserialize<TEST2>(memSerialize[6]).value0;
				memSerialize[7].Seek(0, SeekOrigin.Begin); var tempDeserialize8 = Serializer.Deserialize<TEST2>(memSerialize[7]).value0;
			}
		}

	}
}
