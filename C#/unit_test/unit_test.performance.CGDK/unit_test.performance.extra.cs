using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;


namespace CGDBuffer_CSharp_UnitTest_CGDKbuffer
{
	[TestClass]
	public class Performance_extra
	{
		public const int _TEST_COUNT = 1000000;

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

		#pragma warning disable 0169
		#if NET
			private List<int>? v3;
		#else
			private List<int> v3;
		#endif
		#pragma warning restore 0169

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
