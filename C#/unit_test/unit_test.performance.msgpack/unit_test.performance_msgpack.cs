using MessagePack;

namespace UnitTest_Performance_MessagePack
{
	[TestClass]
	public class Performance
	{
		public const int _TEST_COUNT = 1000000;

		[MessagePackObject]
		public class TEST
		{
			[Key(0)]
			public sbyte value0 = default;
			[Key(1)]
			public byte value1 = default;
			[Key(2)]
			public short value2 = default;
			[Key(3)]
			public ushort value3 = default;
			[Key(4)]
			public int value4 = default;
			[Key(5)]
			public uint value5 = default;
			[Key(6)]
			public long value6 = default;
			[Key(7)]
			public ulong value7 = default;
			[Key(8)]
			public float value8 = default;
			[Key(9)]
			public double value9 = default;
		};

		[MessagePackObject]
		public class TEST_EX
		{
			[Key(0)]
			public int value0 = default;
		#if NET
			[Key(1)]
			public string? value1 = default;
			[Key(2)]
			public List<int>? value2 = default;
		#else
			[Key(1)]
			public string value1 = default;
			[Key(2)]
			public List<int> value2 = default;
		#endif
			[Key(3)]
			public UInt64 value3 = default;
			[Key(4)]
		#if NET
			public Dictionary<string,int>? value4 = default;
		#else
			public Dictionary<string,int> value4 = default;
		#endif
		};

		public int[] array_int = 
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
		public void MsgPk_benchmark_01_primitive()
		{
			Int32	value_1 = 1;
			UInt32	value_2 = 101;
			Int64	value_3 = -12345;
			UInt64	value_4 = 123456;
			float	value_5 = 1.0f;
			double	value_6 = 10.0;

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize_1 = MessagePackSerializer.Serialize(value_1);
				var serialize_2 = MessagePackSerializer.Serialize(value_2);
				var serialize_3 = MessagePackSerializer.Serialize(value_3);
				var serialize_4 = MessagePackSerializer.Serialize(value_4);
				var serialize_5 = MessagePackSerializer.Serialize(value_5);
				var serialize_6 = MessagePackSerializer.Serialize(value_6);

				// - 역직렬화
				var de_value_1 = MessagePackSerializer.Deserialize<Int32>(serialize_1);
				var de_value_2 = MessagePackSerializer.Deserialize<UInt32>(serialize_2);
				var de_value_3 = MessagePackSerializer.Deserialize<Int64>(serialize_3);
				var de_value_4 = MessagePackSerializer.Deserialize<UInt64>(serialize_4);
				var de_value_5 = MessagePackSerializer.Deserialize<float>(serialize_5);
				var de_value_6 = MessagePackSerializer.Deserialize<double>(serialize_6);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_02_list_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(list_int);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<List<int>>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_03_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize_1 = MessagePackSerializer.Serialize(array_string[0]);
				var serialize_2 = MessagePackSerializer.Serialize(array_string[1]);
				var serialize_3 = MessagePackSerializer.Serialize(array_string[2]);
				var serialize_4 = MessagePackSerializer.Serialize(array_string[3]);
				var serialize_5 = MessagePackSerializer.Serialize(array_string[4]);
				var serialize_6 = MessagePackSerializer.Serialize(array_string[5]);
				var serialize_7 = MessagePackSerializer.Serialize(array_string[6]);
				var serialize_8 = MessagePackSerializer.Serialize(array_string[7]);

				// - 역직렬화
				var de_value_1 = MessagePackSerializer.Deserialize<string>(serialize_1);
				var de_value_2 = MessagePackSerializer.Deserialize<string>(serialize_2);
				var de_value_3 = MessagePackSerializer.Deserialize<string>(serialize_3);
				var de_value_4 = MessagePackSerializer.Deserialize<string>(serialize_4);
				var de_value_5 = MessagePackSerializer.Deserialize<string>(serialize_5);
				var de_value_6 = MessagePackSerializer.Deserialize<string>(serialize_6);
				var de_value_7 = MessagePackSerializer.Deserialize<string>(serialize_7);
				var de_value_8 = MessagePackSerializer.Deserialize<string>(serialize_8);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_04_list_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(list_string);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<List<string>>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_05_key_value_int_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(dictionary_int_int);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<Dictionary<int,int>>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_06_key_value_string_string()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(dictionary_string_string);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<Dictionary<string,string>>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_07_key_value_string_list_int()
		{
			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(dictionary_string_List_int);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<Dictionary<string, List<int>>>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_08_struct_primitive()
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

			for (int i = 0; i < _TEST_COUNT; ++i)
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(tempObject);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<TEST>(serialize);
			}
		}
		[TestMethod]
		public void MsgPk_benchmark_09_struct_composite()
		{
			var tempObject = new TEST_EX();
			tempObject.value0 = 100;
			tempObject.value1 = "test_string";
			tempObject.value2 = new List<int> { 1, 2, 3, 4, 5 };
			tempObject.value3 = 10000;
			tempObject.value4 = new Dictionary<string, int> { { "a", 1 }, { "b", 2 }, { "c", 3 } };

			for (int i = 0;i<_TEST_COUNT;++i) 
			{
				// - 직렬화
				var serialize = MessagePackSerializer.Serialize(tempObject);

				// - 역직렬화
				var de_value = MessagePackSerializer.Deserialize<TEST_EX>(serialize);
			}
		}
	}
}
