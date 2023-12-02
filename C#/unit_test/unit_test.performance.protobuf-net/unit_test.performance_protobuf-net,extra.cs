using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.IO;
using ProtoBuf;

namespace UnitTest_Performance_Protobuf
{
	[TestClass]
	public class Performance_extra
	{
		public const int _TEST_COUNT = 1000000;

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


		public List<string> list_string = new List<string> {
			"Please Let test this",
			"이것 좀 테스트하게 해주세요.",
			"这件事 试验",
			"これを試ためさせてください",
			"1234567!@#$%%^&}¢‡¥”w¯¥„ÈÉÞ´µ½²ÂÄÂÁ¾¿ÀÁÂ",
			"Please 这件事 試ためさせてください 합시다.",
			"Test What ever",
			"1234"};

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
