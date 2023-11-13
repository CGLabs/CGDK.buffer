using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.IO;
using ProtoBuf;

namespace UnitTest_Performance_Protobuf
{
	[TestClass]
	public class UnitTest_Performance_Protobuf
	{
		public const int _TEST_COUNT = 1000000;

		[ ProtoContract]
		class TEST_CHAR {
			[ProtoMember(1)]
			public char value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_BYTE
		{
			[ProtoMember(1)]
			public	byte	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_SBYTE
		{
			[ProtoMember(1)]
			public	sbyte	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_SHORT
		{
			[ProtoMember(1)]
			public	short	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_USHORT
		{
			[ProtoMember(1)]
			public	ushort	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_INT
		{
			[ProtoMember(1)]
			public	int	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_UINT
		{
			[ProtoMember(1)]
			public	uint	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_LONG
		{
			[ProtoMember(1)]
			public	long	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_ULONG
		{
			[ProtoMember(1)]
			public	ulong	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_FLOAT
		{
			[ProtoMember(1)]
			public	float	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_DOUBLE
		{
			[ProtoMember(1)]
			public	double	value0 {	get; set;}
		}

		[ProtoContract]
		class TEST_STRING
		{
			[ProtoMember(1)]
		#if NET
			public	string?	value0 {	get; set;}
		#else
			public	string	value0 {	get; set;}
		#endif
		}


		[ProtoContract]
		class TEST 
		{
			[ProtoMember(1)]
			public	sbyte	value0;
			[ProtoMember(2)]
			public	byte	value1;
			[ProtoMember(3)]
			public	short	value2;
			[ProtoMember(4)]
			public	ushort	value3;
			[ProtoMember(5)]
			public	int		value4;
			[ProtoMember(6)]
			public	uint	value5;
			[ProtoMember(7)]
			public	long	value6;
			[ProtoMember(8)]
			public	ulong	value7;
			[ProtoMember(9)]
			public	float	value8;
			[ProtoMember(10)]
			public	double	value9;
		};

		[ProtoContract]
		class TEST_X
		{
			[ProtoMember(1)]
			public	int		value0;
			[ProtoMember(2)]
			public	uint	value1;
			[ProtoMember(3)]
			public	short	value2;
			[ProtoMember(4)]
			public	short	value3;
		};

		class TEST_Y
		{
			[ProtoMember(1)]
			public	short	value0 = 0;
			[ProtoMember(2)]
			public	short	value1 = 0;
			[ProtoMember(3)]
			public	int		value2 = 0;
			[ProtoMember(4)]
			public	int		value3 = 0;
		};

		[ProtoContract]
		class TEST2
		{
			[ProtoMember(1)]
		#if NET
			public	string?	value0;
		#else
			public	string	value0;
		#endif
		};

		[ProtoContract]
		class TEST3
		{
			[ProtoMember(1)]
		#if NET
			public	List<int>?	value0;
		#else
			public	List<int>	value0;
		#endif
		};

		[ProtoContract]
		class TEST4
		{
			[ProtoMember(1)]
		#if NET
			public	List<string>?	value0;
		#else
			public	List<string>	value0;
		#endif
		};

		[ProtoContract]
		class TEST5
		{
			[ProtoMember(1)]
		#if NET
			public	Dictionary<string, List<int>>?	value0;
		#else
			public	Dictionary<string, List<int>>	value0;
		#endif
		};

		[ProtoContract]
		class TEST6
		{
			[ProtoMember(1)]
			public int		value0;

			[ProtoMember(2)]
		#if NET
			public	TEST2?	value1;
		#else
			public	TEST2	value1;
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

		//[TestMethod]
		//public void TestMethod_General_append_extract()
		//{
		//	MemoryStream memSerialize = new MemoryStream();

		//	var I0=new TEST_SBYTE();	I0.value0=3;
		//	var I1=new TEST_BYTE();		I1.value0=4;
		//	var I2=new TEST_SHORT();	I2.value0=4100;
		//	var I3=new TEST_USHORT();	I3.value0=32210;
		//	var I4=new TEST_INT();		I4.value0=123310;
		//	var I5=new TEST_UINT();		I5.value0=121234;
		//	var I6=new TEST_LONG();		I6.value0=1000443L;
		//	var I7=new TEST_ULONG();	I7.value0=12233094310UL;
		//	var I8=new TEST_FLOAT();	I8.value0=1.0f;
		//	var I9=new TEST_DOUBLE();	I9.value0=2.0;

		//	for (int i = 0; i < _TEST_COUNT; ++i)
		//	{
		//		memSerialize.SetLength(0);

		//		// 1) 값 써넣기
		//		ProtoBuf.Serializer.Serialize<TEST_SBYTE>((Stream)memSerialize, I0);
		//		ProtoBuf.Serializer.Serialize<TEST_BYTE>((Stream)memSerialize, I1);
		//		ProtoBuf.Serializer.Serialize<TEST_SHORT>((Stream)memSerialize, I2);
		//		ProtoBuf.Serializer.Serialize<TEST_USHORT>((Stream)memSerialize, I3);
		//		ProtoBuf.Serializer.Serialize<TEST_INT>((Stream)memSerialize, I4);
		//		ProtoBuf.Serializer.Serialize<TEST_UINT>((Stream)memSerialize, I5);
		//		ProtoBuf.Serializer.Serialize<TEST_LONG>((Stream)memSerialize, I6);
		//		ProtoBuf.Serializer.Serialize<TEST_ULONG>((Stream)memSerialize, I7);
		//		ProtoBuf.Serializer.Serialize<TEST_FLOAT>((Stream)memSerialize, I8);
		//		ProtoBuf.Serializer.Serialize<TEST_DOUBLE>((Stream)memSerialize, I9);

		//		memSerialize.Seek(0, SeekOrigin.Begin);

		//		// 2) 값 읽기
		//		TEST_SBYTE	tempDeserialize0 = Serializer.Deserialize<TEST_SBYTE>(memSerialize);
		//		TEST_BYTE	tempDeserialize1 = Serializer.Deserialize<TEST_BYTE>(memSerialize);
		//		TEST_SHORT	tempDeserialize2 = Serializer.Deserialize<TEST_SHORT>(memSerialize);
		//		TEST_USHORT	tempDeserialize3 = Serializer.Deserialize<TEST_USHORT>(memSerialize);
		//		TEST_INT	tempDeserialize4 = Serializer.Deserialize<TEST_INT>(memSerialize);
		//		TEST_UINT	tempDeserialize5 = Serializer.Deserialize<TEST_UINT>(memSerialize);
		//		TEST_LONG	tempDeserialize6 = Serializer.Deserialize<TEST_LONG>(memSerialize);
		//		TEST_ULONG	tempDeserialize7 = Serializer.Deserialize<TEST_ULONG>(memSerialize);
		//		TEST_FLOAT	tempDeserialize8 = Serializer.Deserialize<TEST_FLOAT>(memSerialize);
		//		TEST_DOUBLE	tempDeserialize9 = Serializer.Deserialize<TEST_DOUBLE>(memSerialize);
		//	}
		//}
		[TestMethod]
		public void TestMethod_General_append_extract() 
		{
			var tempObject = new TEST 
			{
				value0=3,
				value1=4,
				value2=4100,
				value3=32210,
				value4=123310,
				value5=121234,
				value6=-1000443L,
				value7=12233094310UL,
				value8=1.0f,
				value9=2.0
			};

			MemoryStream memSerialize = new MemoryStream();

			for(int i = 0;i<_TEST_COUNT;++i) 
			{
				memSerialize.SetLength(0);

				// 1) 값 써넣기
				ProtoBuf.Serializer.Serialize<TEST>((Stream)memSerialize,tempObject);

				memSerialize.Seek(0,SeekOrigin.Begin);

				// 2) 값 읽기
				var tempDeserialize0 = Serializer.Deserialize<TEST>(memSerialize);
			}
		}
		[TestMethod]
		public void TestMethod_String_append_extract()
		{
			TEST2[] tempObject = new TEST2[8];
			MemoryStream[] memSerialize = new MemoryStream[8];

			for(int i=0;i<tempObject.Length; ++i)
			{
				tempObject[i] = new TEST2();
				tempObject[i].value0 = list_string[i];

				memSerialize[i]	 = new MemoryStream(256);
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

		//[TestMethod]
		//public void TestMethod_String_append_extract2()
		//{
		//	MemoryStream memSerialize = new MemoryStream(4096);

		//	for (int i = 0; i < _TEST_COUNT; ++i)
		//	{
		//		memSerialize.SetLength(0);

		//		// 1) 값 써넣기
		//		ProtoBuf.Serializer.Serialize<byte>((Stream)memSerialize, 3);
		//		ProtoBuf.Serializer.Serialize<sbyte>((Stream)memSerialize, 4);
		//		ProtoBuf.Serializer.Serialize<short>((Stream)memSerialize, 4100);
		//		ProtoBuf.Serializer.Serialize<ushort>((Stream)memSerialize, 32210);
		//		ProtoBuf.Serializer.Serialize<int>((Stream)memSerialize, 123310);
		//		ProtoBuf.Serializer.Serialize<uint>((Stream)memSerialize, 121234);
		//		ProtoBuf.Serializer.Serialize<long>((Stream)memSerialize, 1000443L);
		//		ProtoBuf.Serializer.Serialize<ulong>((Stream)memSerialize, 12233094310UL);
		//		ProtoBuf.Serializer.Serialize<float>((Stream)memSerialize, 1.0f);
		//		ProtoBuf.Serializer.Serialize<double>((Stream)memSerialize, 2.0);

		//		memSerialize.Seek(0, SeekOrigin.Begin);

		//		// 2) 값 읽기
		//		var tempDeserialize0 = Serializer.Deserialize<byte>(memSerialize);
		//		var tempDeserialize1 = Serializer.Deserialize<sbyte>(memSerialize);
		//		var tempDeserialize2 = Serializer.Deserialize<short>(memSerialize);
		//		var tempDeserialize3 = Serializer.Deserialize<ushort>(memSerialize);
		//		var tempDeserialize4 = Serializer.Deserialize<int>(memSerialize);
		//		var tempDeserialize5 = Serializer.Deserialize<uint>(memSerialize);
		//		var tempDeserialize6 = Serializer.Deserialize<long>(memSerialize);
		//		var tempDeserialize7 = Serializer.Deserialize<ulong>(memSerialize);
		//		var tempDeserialize8 = Serializer.Deserialize<float>(memSerialize);
		//		var tempDeserialize9 = Serializer.Deserialize<double>(memSerialize);
		//	}
		//}

		[TestMethod]
		public void TestMethod_List_int_append_extract()
		{
			var	tempObject = new TEST3 { value0= list_int };

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
		public void TestMethod_List_string_append_extract()
		{
			var	tempObject = new TEST4 { value0= list_string };

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
		public void TestMethod_Associated_string_list_int_append_extract()
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
		public void TestMethod_multi_leveled()
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

				Assert.IsTrue(tempObject.value0==tempDeserialize.value0);
				Assert.IsTrue(tempObject.value1.value0==tempDeserialize.value1.value0);
			}
		}


		[TestMethod]
		public void TestMethod_multi_leveled3()
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

				//Assert.IsTrue(tempObject.value0==tempDeserialize.value0);
				//Assert.IsTrue(tempObject.value1.value0==tempDeserialize.value1.value0);
			}
		}

		
	}
}
