#include "stdafx.h"
#include "CGDBuffers_UnitTest_Definitions.h"

namespace UnitTest_BufferTemplates
{		
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	TEST_CLASS(UnitTest_BufferTemplates_CGBuffer)
	{
	public:
		//-----------------------------------------------------------------
		// Test) Object Serialize
		//-----------------------------------------------------------------
		TEST_METHOD(Test_ptr_append_extract_Serializable)
		{
			struct TEMP_OBJECT : 
				virtual public CGD::IBufferSerializable, 
				public	NCGPoolable<TEMP_OBJECT>
				//virtual public ICGReferenceCount
			{
			public:
				~TEMP_OBJECT()	{}
			public:
				int			m_ix;
				float		m_fy;
				std::string	m_strZ;

			public:
				// Declare) 
				CGD_BUFFER_SERIAZABLE(TEMP_OBJECT);

				virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer)
				{
					m_ix	 = _Buffer.extract<int>();
					m_fy	 = _Buffer.extract<float>();
					m_strZ	 = _Buffer.extract<std::string>();

					return	true;
				}

				virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer)
				{
					_Buffer.append(m_ix);
					_Buffer.append(m_fy);
					_Buffer.append(m_strZ);

					return	true;
				}
			};

			// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
			CGD::buffer	bufferTemp	 = malloc(1024);

			{
				std::vector<CGPTR<TEMP_OBJECT>>	vecTemp;

				for(int i=0; i<10;++i)
				{
					// Declare) 임시 객체
					CGPTR<TEMP_OBJECT>	a	 = NEW<TEMP_OBJECT>();

					// - 값을 집어 넣음
					a->m_ix	 = 10;
					a->m_fy	 = 2.0;
					a->m_strZ = "Test Value";

					// - 추가
					vecTemp.push_back(a);
				}

				// - 객체 append
				//bufferTemp.append(a);

				//bufferTemp.append(vecTemp);
				bufferTemp<<vecTemp;
			}

			{
				// - 값을 읽을 버퍼
				std::vector<CGPTR<TEMP_OBJECT>>	vecTempRead;

				CGD::buffer	tempRead	 = bufferTemp;

				//// - 임시 객체를 생성
				//CGPTR<TEMP_OBJECT>	b	 = NEW<TEMP_OBJECT>();;

				// - 객체 extract!
				//b	 = tempRead.extract<TEMP_OBJECT>();

				tempRead>>vecTempRead;
				//vecTempRead	 = tempRead.extract<decltype(vecTempRead)>();

				//// Check) 
				//Assert::IsTrue(a->m_ix==b->m_ix, L"Fail to Object Serialize");
				//Assert::IsTrue(a->m_fy==b->m_fy, L"Fail to Object Serialize");
				//Assert::IsTrue(a->m_strZ==b->m_strZ, L"Fail to Object Serialize");
			}
		}
	};
}

//
//
//void test()
//{
//	struct TEMP_OBJECT : 
//		virtual public CGD::IBufferSerializable, 
//		virtual public ICGReferenceCount
//	{
//	public:
//		int			m_ix;
//		float		m_fy;
//		std::string	m_strZ;
//
//	public:
//		// Declare) 
//		CGD_BUFFER_SERIAZABLE(TEMP_OBJECT);
//
//		virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer)
//		{
//			m_ix	 = _Buffer.extract<int>();
//			m_fy	 = _Buffer.extract<float>();
//			m_strZ	 = _Buffer.extract<std::string>();
//
//			return	true;
//		}
//
//		virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer)
//		{
//			_Buffer.append(m_ix);
//			_Buffer.append(m_fy);
//			_Buffer.append(m_strZ);
//
//			return	true;
//		}
//
//			
//	};
//
//	// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
//	CGD::buffer	bufferTemp	 = malloc(1024);
//
//	{
//		std::vector<CGPTR<TEMP_OBJECT>>	vecTemp;
//
//		for(int i=0; i<10;++i)
//		{
//			// Declare) 임시 객체
//			CGPTR<TEMP_OBJECT>	a	 = NEW<TEMP_OBJECT>();
//
//			// - 값을 집어 넣음
//			a->m_ix	 = 10;
//			a->m_fy	 = 2.0;
//			a->m_strZ = "Test Value";
//
//			// - 추가
//			vecTemp.append(a);
//		}
//
//		// - 객체 append
//		//bufferTemp.append(a);
//
//		bufferTemp.append(vecTemp);
//		//bufferTemp<<vecTemp;
//	}
//
//	{
//		// - 값을 읽을 버퍼
//		std::vector<CGPTR<TEMP_OBJECT>>	vecTempRead;
//
//		CGD::buffer	tempRead	 = bufferTemp;
//
//		//// - 임시 객체를 생성
//		//CGPTR<TEMP_OBJECT>	b	 = NEW<TEMP_OBJECT>();;
//
//		// - 객체 extract!
//		//b	 = tempRead.extract<TEMP_OBJECT>();
//
//		//tempRead>>vecTempRead;
//		vecTempRead	 = tempRead.extract<decltype(vecTempRead)>();
//
//		//// Check) 
//		//Assert::IsTrue(a->m_ix==b->m_ix, L"Fail to Object Serialize");
//		//Assert::IsTrue(a->m_fy==b->m_fy, L"Fail to Object Serialize");
//		//Assert::IsTrue(a->m_strZ==b->m_strZ, L"Fail to Object Serialize");
//	}
//	//// 6) 할당 해제
//	//free(bufferTemp.clear());
//}
