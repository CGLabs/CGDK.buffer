#include "stdafx.h"

namespace UnitTest_BufferTemplates
{		
#if _MSC_VER>=1700
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif
	TEST_CLASS(UnitTest_Cpp_BufferTemplates_ptr)
	{
	public:
		UnitTest_Cpp_BufferTemplates_ptr()
		{
			InitContainers();
		}

	public:
		template<class T>
		CGD::ptr function_ptr_STRING_append(CGD::ptr _Ptr, T* _List)
		{
			// 2) 
			_Ptr.append<T>(_List[0]);
			_Ptr.append<T>(_List[1]);
			_Ptr.append<T>(_List[2]);
			_Ptr.append<T>(_List[3]);
			_Ptr.append<T>(_List[4]);
			_Ptr.append<T>(_List[5]);
			_Ptr.append<T>(_List[6]);
			_Ptr.append<T>(_List[7]);
		
			return	_Ptr;
		}

		template<class T>
		void function_ptr_extract_STRING(CGD::ptr _Ptr)
		{
			// 1) extract TEST
			{
				T	strValue1	 = _Ptr.extract<T>();
				T	strValue2	 = _Ptr.extract<T>();
				T	strValue3	 = _Ptr.extract<T>();
				T	strValue4	 = _Ptr.extract<T>();
				T	strValue5	 = _Ptr.extract<T>();
				T	strValue6	 = _Ptr.extract<T>();
				T	strValue7	 = _Ptr.extract<T>();
				T	strValue8	 = _Ptr.extract<T>();
			}
		}

		template<class T>
		void function_ptr_front_STRING(CGD::ptr _Ptr)
		{
			{
				// Declare)
				CGD::POS	tempPos;

				// 3) Read
				T	strValue1	 = _Ptr.front<T>(tempPos);
				T	strValue2	 = _Ptr.front<T>(tempPos);
				T	strValue3	 = _Ptr.front<T>(tempPos);
				T	strValue4	 = _Ptr.front<T>(tempPos);
				T	strValue5	 = _Ptr.front<T>(tempPos);
				T	strValue6	 = _Ptr.front<T>(tempPos);
				T	strValue7	 = _Ptr.front<T>(tempPos);
				T	strValue8	 = _Ptr.front<T>(tempPos);
			}

		}

		void function_ptr_append_GENERAL(CGD::ptr& _Ptr)
		{
			_Ptr.append<char>(12);
			_Ptr.append<unsigned char>(3);
			_Ptr.append<wchar_t>(4);
			_Ptr.append<char16_t>(10);
			_Ptr.append<char32_t>(22);
			_Ptr.append<int16_t>(4100);
			_Ptr.append<uint16_t>(32210);
			_Ptr.append<int32_t>(123310);
			_Ptr.append<uint32_t>(121234);
			_Ptr.append<int64_t>(-1000443);
			_Ptr.append<uint64_t>(12233094310);
			_Ptr.append<float>(1.0f);
			_Ptr.append<double>(2.0);
		}

		void function_ptr_extract_GENERAL(CGD::ptr _Ptr)
		{
			auto	value1	 = _Ptr.extract<char>();
			auto	value2	 = _Ptr.extract<unsigned char>();
			auto	value3	 = _Ptr.extract<wchar_t>();
			auto	value4	 = _Ptr.extract<char16_t>();
			auto	value5	 = _Ptr.extract<char32_t>();
			auto	value6	 = _Ptr.extract<int16_t>();
			auto	value7	 = _Ptr.extract<uint16_t>();
			auto	value8	 = _Ptr.extract<int32_t>();
			auto	value9	 = _Ptr.extract<uint32_t>();
			auto	value10	 = _Ptr.extract<int64_t>();
			auto	value11	 = _Ptr.extract<uint64_t>();
			auto	value12	 = _Ptr.extract<float>();
			auto	value13	 = _Ptr.extract<double>();
		}

		void function_ptr_front_GENERAL(CGD::ptr _Ptr)
		{
			int	iPosNow	 = 0;

			auto	value1	 = _Ptr.front<char>(iPosNow);			iPosNow+=sizeof(char);
			auto	value2	 = _Ptr.front<unsigned char>(iPosNow);	iPosNow+=sizeof(unsigned char);
			auto	value3	 = _Ptr.front<wchar_t>(iPosNow);		iPosNow+=sizeof(wchar_t);
			auto	value4	 = _Ptr.front<char16_t>(iPosNow);		iPosNow+=sizeof(char16_t);
			auto	value5	 = _Ptr.front<char32_t>(iPosNow);		iPosNow+=sizeof(char32_t);
			auto	value6	 = _Ptr.front<int16_t>(iPosNow);		iPosNow+=sizeof(int16_t);
			auto	value7	 = _Ptr.front<uint16_t>(iPosNow);		iPosNow+=sizeof(uint16_t);
			auto	value8	 = _Ptr.front<int32_t>(iPosNow);		iPosNow+=sizeof(int32_t);
			auto	value9	 = _Ptr.front<uint32_t>(iPosNow);		iPosNow+=sizeof(uint32_t);
			auto	value10	 = _Ptr.front<int64_t>(iPosNow);		iPosNow+=sizeof(int64_t);
			auto	value11	 = _Ptr.front<uint64_t>(iPosNow);		iPosNow+=sizeof(uint64_t);
			auto	value12	 = _Ptr.front<float>(iPosNow);			iPosNow+=sizeof(float);
			auto	value13	 = _Ptr.front<double>(iPosNow);			iPosNow+=sizeof(double);
		}

		void function_ptr_front_with_pos_GENERAL(CGD::ptr _Ptr)
		{
			CGD::POS	posNow;

			auto	value1	 = _Ptr.front<char>(posNow);
			auto	value2	 = _Ptr.front<unsigned char>(posNow);
			auto	value3	 = _Ptr.front<wchar_t>(posNow);
			auto	value4	 = _Ptr.front<char16_t>(posNow);
			auto	value5	 = _Ptr.front<char32_t>(posNow);
			auto	value6	 = _Ptr.front<int16_t>(posNow);
			auto	value7	 = _Ptr.front<uint16_t>(posNow);
			auto	value8	 = _Ptr.front<int32_t>(posNow);
			auto	value9	 = _Ptr.front<uint32_t>(posNow);
			auto	value10	 = _Ptr.front<int64_t>(posNow);
			auto	value11	 = _Ptr.front<uint64_t>(posNow);
			auto	value12	 = _Ptr.front<float>(posNow);
			auto	value13	 = _Ptr.front<double>(posNow);
		}

	public:
		TEST_METHOD(Test_ptr_append_general)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			CGD::buffer	bufferTemp(tempBuffer);

			for(int i=0; i<_TEST_COUNT;++i)
			{
				function_ptr_append_GENERAL(CGD::ptr(bufferTemp.front()));
			}
		}

		TEST_METHOD(Test_ptr_extract_general)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferTemp(tempBuffer);

			// - 값 써넣기
			function_ptr_append_GENERAL(CGD::ptr(bufferTemp.front()));

			for(int i=0; i<_TEST_COUNT;++i)
			{
				function_ptr_extract_GENERAL(bufferTemp);
			}
		}

		TEST_METHOD(Test_ptr_front_general)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferTemp(tempBuffer);

			// - 값 써넣기
			function_ptr_append_GENERAL(CGD::ptr(bufferTemp.front()));

			for(int i=0; i<_TEST_COUNT;++i)
			{
				function_ptr_front_GENERAL(bufferTemp);
			}
		}

		TEST_METHOD(Test_ptr_front_general_with_pos)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferTemp(tempBuffer);

			// - 값 써넣기
			function_ptr_append_GENERAL(CGD::ptr(bufferTemp.front()));

			for(int i=0; i<_TEST_COUNT;++i)
			{
				function_ptr_front_with_pos_GENERAL(bufferTemp);
			}
		}

		TEST_METHOD(Test_ptr_prepend_const_string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferCreate(tempBuffer);

			// Defintions)
			const	char*	strTest = "Test String";

			// - 임시로...
			CGD::ptr	bufferTest = bufferCreate + 256;

			// - 값 써넣기
			bufferTest.prepend(CGD::_const("Test String"));

			// - 값 읽기
			char*	strRead = bufferTest.extract<char*>();

			// Check) 
		#ifdef _ENABLE_ASSERT
			Assert::IsTrue(bufferTest==(bufferCreate.front()+256));
			Assert::IsTrue(std::char_traits<char>::compare(strTest, strRead, 0) == 0);
		#endif
		}

		TEST_METHOD(Test_ptr_append_const_string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferCreate(tempBuffer);

			// - 임시로...
			CGD::ptr	bufferWrite = bufferCreate;

			// Defintions)
			const	char*	strTest = "Test String";

			// - 값 써넣기
			bufferWrite.append(CGD::_const("Test String"));

			// - 임시로...
			CGD::ptr	bufferRead = bufferCreate;

			// - 값 읽기
			char*	strRead = bufferRead.extract<char*>();

			// Check) 
		#ifdef _ENABLE_ASSERT
			Assert::IsTrue(bufferWrite.front() == bufferRead);
			Assert::IsTrue(std::char_traits<char>::compare(strTest, strRead, 0) == 0);
		#endif
		}

		TEST_METHOD(Test_ptr_String2)
		{
			// 1) 임시 문자열 list<std::string> 만듬(Create temporary string list)
			std::list<std::string>	listTest;

			listTest.push_back("This");
			listTest.push_back("is a");
			listTest.push_back("Simple");
			listTest.push_back("Example!!");


			//-----------------------------------------------------------------
			// 설명) 배열에 저장된 String 읽어들이기 (2)
			//-----------------------------------------------------------------
			// X) Memory Alloc
			std::auto_ptr<char>	tempBuffer1(new char[1024]);
			std::auto_ptr<char>	tempBuffer2(new char[1024]);
			
			// Case A) 메모리 할당 (Allocating Memory)
			CGD::buffer	bufferWrite(tempBuffer1.get());

			// Declare) 
			CGD::ptr	ptrWrite	 = bufferWrite.front();

			// 2) 문자열 리스트 통채로 추가 (appending string list)
			ptrWrite.append(listTest);

			// Case B) 메모리 할당 (Allocation Memory)
			CGD::buffer	tempBuffer(tempBuffer2.get());

			// Declare) 
			CGD::ptr	ptrWrite2	 = tempBuffer.front();

			// 3) Iterator를 사용해 특정 범위의 데이터만 써넣을 수도 있다.(ranged appending using iterator)
			ptrWrite2.append(listTest.begin(), listTest.end());


			//-----------------------------------------------------------------
			// 설명) 배열에 저장된 String 읽어들이기 (2)
			//-----------------------------------------------------------------
			{
				// 1) Buffer...
				CGD::ptr	bufferRead	 = bufferWrite.front();

				// 1) 
				std::list<std::string>	listRead;

				// 2) 읽어오기
				listRead	 = bufferRead.extract<std::list<std::string>>();
	
				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(listTest==listRead);
			#endif
			}

			//-----------------------------------------------------------------
			// 설명) 배열에 저장된 String 읽어들이기 (2)
			//-----------------------------------------------------------------
			{
				// 1) Buffer...
				CGD::ptr	bufferRead	 = bufferWrite.front();

				// Declare) 데이터를 읽어올 vector<T>
				std::vector<std::string>	vectorRead;

				// 2) 읽어오기
				vectorRead	 = bufferRead.extract<std::vector<std::string>>();
	
				// Check) 
			#ifdef _ENABLE_ASSERT
				auto	iterCompare	 = vectorRead.begin();
				for(auto& iter:listTest)
				{
					Assert::IsTrue(iter==*iterCompare);
					++iterCompare;
				}
			#endif
			}

			//-----------------------------------------------------------------
			//
			//-----------------------------------------------------------------
			{
				// 1) Buffer를 Swallow복사 (버퍼 내용을 복사하는 것이 아니라 포인터만 복사한다.)
				CGD::ptr	bufferRead	 = bufferWrite.front();

				// Declare) 데이터를 읽어올 list<T>
				std::list<char*>	listRead;

				// 2) 읽어오기
				listRead	 = bufferRead.extract<std::list<char*>>();
	
				// Check) 
			#ifdef _ENABLE_ASSERT
				auto	iterCompare	 = listRead.begin();
				for(auto& iter:listTest)
				{
					Assert::IsTrue(std::char_traits<char>::compare(iter.c_str(), *iterCompare, 0)==0);
					++iterCompare;
				}
			#endif
			}

			//-----------------------------------------------------------------
			//
			//-----------------------------------------------------------------
			{
				// 1) Buffer를 Swallow복사 (버퍼 내용을 복사하는 것이 아니라 포인터만 복사한다.)
				CGD::ptr	bufferRead	 = bufferWrite.front();

				// Declare) 데이터를 읽어올 list<T>
				std::list<char*>	listRead;

				// 2) 읽어오기
				listRead	 = bufferRead.front<std::list<char*>>();
	
				// Check) 
			#ifdef _ENABLE_ASSERT
				auto	iterCompare	 = listRead.begin();
				for(auto& iter:listTest)
				{
					Assert::IsTrue(std::char_traits<char>::compare(iter.c_str(), *iterCompare, 0)==0);
					++iterCompare;
				}
			#endif
			}

			//-----------------------------------------------------------------
			//
			//-----------------------------------------------------------------
			{
				// 1) CGD::ptr을 사용해서 읽도록 했다.(CCD:buffer나 CGD::buffer를 사용해도 된다.)
				CGD::ptr	tempRead	 = bufferWrite.front();

				// 2) 갯수를 읽어온다.
				int	iCount	= tempRead.extract<COUNT_T>();

				// 3) iCount 갯수 만큼의 스트링을 읽어온다.
				auto	iterOriginal	 = listTest.begin();
				for(int i=0; i<iCount;++i, ++iterOriginal)
				{
					// - String들을 읽어낸다.
					const char*	strItem	 = tempRead.extract<char*>();

					// Check) 
				#ifdef _ENABLE_ASSERT
					Assert::IsTrue(std::char_traits<char>::compare((*iterOriginal).c_str(), strItem, 0)==0);
				#endif
				}
			}
		}

	#ifdef _SUPPORT_INITIALIZER_LIST
		TEST_METHOD(Test_ptr_append_Initializer_list)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) 임시 ptr
			CGD::ptr	ptrTemp		 = bufferTemp.front();

			// 3) 추가한다
			ptrTemp.append({1,2,3,4,5,6,7});
		}

		TEST_METHOD(Test_ptr_stream)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// Declare) 
			const	int			iValue_Write		 = 3;
			const	float		fValue_Write		 = 4.0f;
			const	char*		strValue1_Write		 = "Test1";
			const	wchar_t*	strValue2_Write		 = L"Test2";
			const	std::string	strValue3_Write		 = "Test3";
			std::vector<int>	vectorValue_Write	 = {1, 2, 4, 3, 6, 7, 5};

			// 2) 버퍼에 값 써넣기 (Streadm-In)
			{
				// - 임시 ptr
				CGD::ptr	ptrTemp	 = bufferTemp.front();

				// - 추가한다
				ptrTemp<<iValue_Write<<fValue_Write<<strValue1_Write<<strValue2_Write<<strValue3_Write<<vectorValue_Write;
			}
			
			// 3) 버퍼에서 값 읽어오기 (Streadm-Out)
			{
				// - 임시 ptr
				CGD::ptr	ptrTemp	 = bufferTemp.front();

				// Declare) 
				int					iValue_Read;
				float				fValue_Read;
				char*				strValue1_Read;
				wchar_t*			strValue2_Read;
				std::string			strValue3_Read;
				std::vector<int>	vectorValue_Read;

				// - 읽어낸다.
				ptrTemp>>iValue_Read>>fValue_Read>>strValue1_Read>>strValue2_Read>>strValue3_Read>>vectorValue_Read;

				// Check)
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(iValue_Read==iValue_Write);
				Assert::IsTrue(fValue_Read==fValue_Write);
				Assert::IsTrue(std::char_traits<char>::compare(strValue1_Read,strValue1_Write, 0)==0);
				Assert::IsTrue(std::char_traits<wchar_t>::compare(strValue2_Write,strValue2_Write, 0)==0);
				Assert::IsTrue(strValue3_Write==strValue3_Read);
				Assert::IsTrue(vectorValue_Write==vectorValue_Read);
			#endif
			}
		}
#endif

		TEST_METHOD(Test_ptr_append_front_STRUCT)
		{
			struct TESTSTRUCT
			{
   				int			iValue;
   				uint32_t	dwValue;
   				char		chValue;
			};

			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) ...
			CGD::ptr	ptrWrite	 = bufferTemp.front();

			// 2) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
			TESTSTRUCT&	tempWirte = ptrWrite.append<TESTSTRUCT>();

			// 3) 이렇게 먼저 추가해 놓고 쓰게 되면 실질적으로는 Buffer내에 해당 위치에 쓰여진다.
   			tempWirte.iValue	 = 10;
   			tempWirte.dwValue	 = 100;
   			tempWirte.chValue	 = 2;

			// 2) ...
			CGD::ptr	ptrRead		 = bufferTemp.front();

			// 4) 값을 읽어온다.
			TESTSTRUCT&	tempRead	 = ptrRead.front<TESTSTRUCT>(0);

			// Check)
		#ifdef _ENABLE_ASSERT
			Assert::IsTrue(tempWirte.iValue==tempRead.iValue);
			Assert::IsTrue(tempWirte.dwValue==tempRead.dwValue);
			Assert::IsTrue(tempWirte.chValue==tempRead.chValue);
		#endif
		}

		TEST_METHOD(Test_ptr_BasicAppend5)
		{
			#define	VALUE1	1
			#define	VALUE2	12
			#define	VALUE3	4322
			#define	VALUE4	12.3f
			#define	VALUE5	1244.123

			struct TESTSTRUCT
			{
			public:
   				char		chValue;
   				int			iValue;
   				uint32_t	dwValue;
   				float		fchValue;
   				double		dchValue;
			public:
				TESTSTRUCT():chValue(VALUE1),iValue(VALUE2),dwValue(VALUE3),fchValue(VALUE4),dchValue(VALUE5) {}
			};

			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) ...
			CGD::ptr	ptrTempWrite	 = bufferTemp.front();

			// 3) 버퍼에 Struct를 빈값으로 써넣는다! 그리고 추가한 곳 위치의 참조를 얻는다.
			TESTSTRUCT&	temp = ptrTempWrite.append(TESTSTRUCT());


			// 2) ...
			CGD::ptr	ptrTempRead	 = bufferTemp.front();

			// 4) 값을 읽어온다.
			TESTSTRUCT&	tempRead = ptrTempRead.front<TESTSTRUCT>(0);

			// Check)
		#ifdef _ENABLE_ASSERT
			Assert::AreEqual(temp.chValue, tempRead.chValue);
			Assert::AreEqual(temp.iValue, tempRead.iValue);
			Assert::AreEqual(temp.dwValue, tempRead.dwValue);
			Assert::AreEqual(temp.fchValue, tempRead.fchValue);
			Assert::AreEqual(temp.dchValue, tempRead.dchValue);
		#endif
		}

		TEST_METHOD(Test_ptr_append_text)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - Buffer 할당
			CGD::buffer	bufferCreate(tempBuffer);

			// Defintions)
			const char*	strTest = "Test String";

			// - 임시로...
			CGD::ptr	bufferTest = bufferCreate;

			// 1) String을 Append한다. (String형 Append는 NULL을 붙이기 때문에 문자열길이+1이 리턴되어 온다.)
			size_t iSizeA	 = bufferTest.append(CGD::_text(strTest));

		#ifdef _ENABLE_ASSERT
			Assert::IsTrue(std::char_traits<char>::length(strTest) == iSizeA);
		#endif

			// 2) Text를 Append한다. (Text형 Append는 NULL을 붙이지 않기 때문에 문자열 길이만 리턴되어 온다.)
			size_t iSizeB = bufferTest.append(CGD::_const_text("Test Temp"));

			// Check) 길이를 확인한다. (
		#ifdef _ENABLE_ASSERT
			Assert::IsTrue(std::char_traits<char>::length("Test Temp") == iSizeB);

			// Check) 
			Assert::IsTrue(bufferTest-bufferCreate.begin() == iSizeA+iSizeB);

			// Chec) String 내용 검사			
			Assert::IsTrue(memcmp("Test String", bufferCreate.buf, std::char_traits<char>::length(strTest)*sizeof(char))==0);
			Assert::IsTrue(memcmp("Test Temp", bufferCreate.buf+ std::char_traits<char>::length(strTest)*sizeof(char), std::char_traits<char>::length("Test Temp")*sizeof(char)) == 0);
		#endif
		}




		//-----------------------------------------------------------------
		// Test) String append / extract 
		//-----------------------------------------------------------------
		// 1) append / extract [char*](UTF-8)
		TEST_METHOD(Test_ptr_extract_string_char)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<char*>(bufCreate.front(), array_string_char);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_extract_STRING<char*>(bufCreate.front());
			}
		}

		// 2) append / extract [wchar_t*](UCS)
		TEST_METHOD(Test_ptr_extract_string_wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<wchar_t*>(bufCreate.front(), array_string_wchar_t);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_extract_STRING<wchar_t*>(bufCreate.front());
			}
		}

		//// 3) append / extract [char16_t*](UTF-16)
		//TEST_METHOD(Test_ptr_extract_string_char16_t)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char16_t*>(bufCreate.front(), array_string_char16_t);
		//
		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_extract_STRING<char16_t*>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		//// 4) append / extract [char32_t*](UTF-32)
		//TEST_METHOD(Test_ptr_extract_string_char32_t)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char32_t*>(bufCreate.front(), array_string_char32_t);

		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_extract_STRING<char32_t*>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		// 5) append / extract [std::string](UTF-8)
		TEST_METHOD(Test_ptr_extract_string_std_string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<char*>(bufCreate.front(), array_string_char);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_extract_STRING<std::string>(bufCreate.front());
			}
		}

		// 6) append / extract [std::wstring](UTF-8)(UCS)
		TEST_METHOD(Test_ptr_extract_string_std_wstring)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<wchar_t*>(bufCreate.front(), array_string_wchar_t);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_extract_STRING<std::wstring>(bufCreate.front());
			}
		}
		
		// 7) append / extract [std::u16string](UTF-8)(UCS)
		//TEST_METHOD(Test_ptr_extract_string_std_u16string)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char16_t*>(bufCreate.front(), array_string_char16_t);
		//
		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_extract_STRING<std::u16string>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		// 8) append / extract [std::u32string](UTF-8)(UCS)
		//TEST_METHOD(Test_ptr_extract_string_std_u32string)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char16_t*>(bufCreate.front(), array_string_char32_t);
		//
		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_extract_STRING<std::u32string>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}


		//-----------------------------------------------------------------
		// Test) String append / front 
		//-----------------------------------------------------------------
		// 1) append / extract [char*](UTF-8)
		TEST_METHOD(Test_ptr_front_string_char)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<char*>(bufCreate.front(), array_string_char);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_front_STRING<char*>(bufCreate.front());
			}
		}

		// 2) append / extract [wchar_t*](UCS)
		TEST_METHOD(Test_ptr_front_string_wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<wchar_t*>(bufCreate.front(), array_string_wchar_t);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_front_STRING<wchar_t*>(bufCreate.front());
			}
		}

		// 3) append / extract [char16_t*](UTF-16)
		//TEST_METHOD(Test_ptr_front_string_UTF_16)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char16_t*>(bufCreate.front(), array_string_char16_t);

		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_front_STRING<char16_t*>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		// 4) append / extract [char32_t*](UTF-32)
		//TEST_METHOD(Test_ptr_front_string_UTF_32)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::ptr	temp	 = function_ptr_STRING_append<char32_t*>(bufCreate.front(), array_string_char32_t);

		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_front_STRING<char32_t*>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		// 5) append / extract [std::string](UTF-8)
		TEST_METHOD(Test_ptr_front_string_std_string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<char*>(bufCreate.front(), array_string_char);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_front_STRING<std::string>(bufCreate.front());
			}
		}

		// 6) append / extract [std::wstring](UTF-8)(UCS)
		TEST_METHOD(Test_ptr_front_string_std_wstring)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - 임시 Buffer 할당
			CGD::buffer	bufCreate(tempBuffer);

			// - String append
			CGD::ptr	temp	 = function_ptr_STRING_append<wchar_t*>(bufCreate.front(), array_string_wchar_t);

			// - String extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				function_ptr_front_STRING<std::wstring>(bufCreate.front());
			}
		}
		
		// 7) append / extract [std::u16string](UTF-8)(UCS)
		//TEST_METHOD(Test_ptr_front_string_std_u16string)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::buffer	temp	 = function_ptr_STRING_append<char16_t*>(bufCreate.front(), array_string_char16_t);

		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_front_STRING<std::u16string>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		// 8) append / extract [std::u32string](UTF-8)(UCS)
		//TEST_METHOD(Test_ptr_front_string_std_u32string)
		//{
		//	// - 임시 Buffer 할당
		//	CGD::buffer	bufCreate	 = malloc(2048);
		//
		//	// - String append
		//	CGD::buffer	temp	 = function_ptr_STRING_append<char32_t*>(bufCreate.front(), array_string_char32_t);

		//	// - String extract
		//	for(int i=0;i<_TEST_COUNT;++i)
		//	{
		//		function_ptr_front_STRING<std::u32string>(bufCreate.front());
		//	}
		//
		//	// -임시 Buffer 할당해제
		//	free(bufCreate.clear());
		//}

		//-----------------------------------------------------------------
		// Test) array
		//-----------------------------------------------------------------
		// 1) array
		//char*										array_string_char[];
		//wchar_t*									array_string_wchar_t[];
		//std::string								array_std_string_stdstring[];
		//std::wstring								array_std_string_stdwstring[];
		TEST_METHOD(Test_ptr_append_CONTAINER_array$wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate.front();

				bufferWrite.append(array_string_wchar_t);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_array$wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(array_string_wchar_t);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate.front();

				auto	temp	 = ptrTemp.extract<decltype(array_string_wchar_t)>();
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_array$wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(array_string_wchar_t);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate.front();

				auto	temp	 = ptrTemp.front<decltype(array_string_wchar_t)>(0);
			}
		}
		
		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_array$wchar_t)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(array_string_wchar_t);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(array_string_wchar_t)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(compare_array_string<wchar_t>(temp.value, array_string_wchar_t, 8), L"Fail to array[wchar_t] prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		//-----------------------------------------------------------------
		// Test) Container-vector
		//-----------------------------------------------------------------
		// 2) vector
		//std::vector<int>			vector_int;
		//std::vector<std::string>	vector_std_string;
		TEST_METHOD(Test_ptr_append_CONTAINER_vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(vector_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;

				auto	temp	 = ptrTemp.extract<decltype(vector_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_int, L"Fail to vector<int> append/extract");
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(vector_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_int, L"Fail to vector<int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}
		
		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp		 = bufferCreate+2048;
				CGD::ptr	ptrOrigin	 = ptrTemp;

				// - 
				ptrTemp.prepend(vector_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(vector_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_int, L"Fail to vector[int] prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.front()+2048);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_append_CONTAINER_vector$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(vector_std_string);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_vector$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(vector_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;

				auto	temp	 = ptrTemp.extract<decltype(vector_std_string)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_std_string, L"Fail to vector<int> append/extract");
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_vector$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(vector_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(vector_std_string)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_std_string, L"Fail to vector<int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_vector$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp		 = bufferCreate+2048;
				CGD::ptr	ptrOrigin	 = ptrTemp;

				// - 
				ptrTemp.prepend(vector_std_string);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(vector_std_string)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==vector_std_string, L"Fail to vector[int] prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.front()+2048);
			#endif
			}
		}


		//-----------------------------------------------------------------
		// Test) Container-list
		//-----------------------------------------------------------------
		// 1) std::list<int>					list_int;
		TEST_METHOD(Test_ptr_append_CONTAINER_list$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(list_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_list$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;

				auto	temp	 = ptrTemp.extract<decltype(list_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_int, L"Fail to list<int> append/extract");
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_list$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(list_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_int, L"Fail to list<int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_list$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(list_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(list_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_int, L"Fail to list[int] prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.front()+2048);
			#endif
			}
		}

		// 2) std::list<std::string>			list_std_string;
		TEST_METHOD(Test_ptr_append_CONTAINER_list$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(list_std_string);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_list$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;

				auto	temp	 = ptrTemp.extract<decltype(list_std_string)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_std_string, L"Fail to list<string> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_list$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(list_std_string)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_std_string, L"Fail to list<string> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_list$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(list_std_string);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(list_std_string)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_std_string, L"Fail to list[string] prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}

		// 3) std::list<std::vector<int>>		list_vector_int;
		TEST_METHOD(Test_ptr_append_CONTAINER_list$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(list_vector_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_list$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;

				auto	temp	 = ptrTemp.extract<decltype(list_vector_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_vector_int, L"Fail to list<vector<int>> append/extract");
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_list$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(list_vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(list_vector_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_vector_int, L"Fail to list<vector<int>> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_list$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(list_vector_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(list_vector_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==list_vector_int, L"Fail to list<vector<int>> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		//-----------------------------------------------------------------
		// Test) Container-set
		//-----------------------------------------------------------------
		// 1) std::set<int>			set_int;
		TEST_METHOD(Test_ptr_append_CONTAINER_set$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(set_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_set$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(set_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(set_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_int, L"Fail to set<int> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_set$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(set_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(set_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_int, L"Fail to set<int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}
	
		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_set$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(set_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(set_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_int, L"Fail to set<int> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}



		// 2) std::set<std::string>	set_std_string;
		TEST_METHOD(Test_ptr_append_CONTAINER_set$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(set_std_string);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_set$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(set_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(set_std_string)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_std_string, L"Fail to set<std::string> append/extract");
				Assert::IsTrue(ptrTemp.front()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_set$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(set_std_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(set_std_string)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_std_string, L"Fail to set<std::string> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}
	
		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_set$string)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(set_std_string);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(set_std_string)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==set_std_string, L"Fail to set<std::string> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}
		

		//-----------------------------------------------------------------
		// Test) Container-map
		//-----------------------------------------------------------------
		// 1) std::map<int, int>							;
		TEST_METHOD(Test_ptr_append_CONTAINER_map$int$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(map_std_int_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_map$int$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_int_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(map_std_int_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_int_int, L"Fail to map<int,int> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_map$int$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_int_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto		temp	 = ptrTemp.front<decltype(map_std_int_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_int_int, L"Fail to map<int,int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_map$int$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(map_std_int_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(map_std_int_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_int_int, L"Fail to map<int,int> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}
		


		// 2) std::map<std::string, int>
		TEST_METHOD(Test_ptr_append_CONTAINER_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(map_std_string_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_string_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(map_std_string_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_int, L"Fail to map<string,int> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_string_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto		temp	 = ptrTemp.front<decltype(map_std_string_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_int, L"Fail to map<string,int> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_map$string$int_push)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(map_std_string_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(map_std_string_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_int, L"Fail to map<string,int> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		// 3) std::map<std::string, std::vector<int>>		map_std_string_vector_int;
		TEST_METHOD(Test_ptr_append_CONTAINER_map$string$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(map_std_string_vector_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_map$string$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_string_vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(map_std_string_vector_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_vector_int, L"Fail to map<string,vector<int>> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_map$string$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_string_vector_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				CGD::POS	posTemp;

				auto	temp	 = ptrTemp.front<decltype(map_std_string_vector_int)>(posTemp);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_vector_int, L"Fail to map<string,vector<int>> append/front");
				Assert::IsTrue(posTemp.get_pos()==bufferCreate.len);
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_map$string$vector$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(map_std_string_vector_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(map_std_string_vector_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==map_std_string_vector_int, L"Fail to map<string,vector<int>> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		// 4) std::map<std::string, std::vector<char*>>	map_std_vector_string;
		TEST_METHOD(Test_ptr_append_CONTAINER_map$string$vector$charP)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(map_std_vector_string);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_map$string$vector$charP)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_vector_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(map_std_vector_string)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(compare_map_std_vector_string(temp, map_std_vector_string), L"Fail to map<string,vector<char*>> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_map$string$vector$charP)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			bufferCreate.append(map_std_vector_string);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.front<decltype(map_std_vector_string)>(0);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(compare_map_std_vector_string(temp, map_std_vector_string), L"Fail to map<string,vector<char*>> append/front");
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_map$string$vector$charP)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(map_std_vector_string);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(map_std_vector_string)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(compare_map_std_vector_string(temp,map_std_vector_string), L"Fail to map<string,vector<char*>> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		//-----------------------------------------------------------------
		// Test) Container-unordered_map
		//-----------------------------------------------------------------
		// 1) unordered_map
		// 2) std::unordered_map<int, int>						unordered_map_std_int_int;
		// 3) std::unordered_map<std::string, int>				unordered_map_std_string_int;
		// 4) std::unordered_map<std::string, std::vector<int>>	unordered_map_std_string_vector_int;
		// 5) std::unordered_map<std::string, std::vector<char*>>	unordered_map_std_vector_string;
		TEST_METHOD(Test_ptr_append_CONTAINER_unoredered_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	bufferWrite	 = bufferCreate;

				bufferWrite.append(unordered_map_std_string_int);
			}
		}

		TEST_METHOD(Test_ptr_extract_CONTAINER_unoredered_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);
			bufferCreate.append(unordered_map_std_string_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.extract<decltype(unordered_map_std_string_int)>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==unordered_map_std_string_int, L"Fail to unordered_map<std::string,int> append/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==bufferCreate.back());
			#endif
			}
		}

		TEST_METHOD(Test_ptr_front_CONTAINER_unoredered_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);
			bufferCreate.append(unordered_map_std_string_int);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				CGD::ptr	ptrTemp	 = bufferCreate;
				auto		temp	 = ptrTemp.front<decltype(unordered_map_std_string_int)>(0);

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==unordered_map_std_string_int, L"Fail to unordered_map<std::string,int> append/front");
			#endif
			}
		}

		TEST_METHOD(Test_ptr_prepend_extract_CONTAINER_unoredered_map$string$int)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// - String append
			CGD::buffer	bufferCreate(tempBuffer);

			// - extract
			for(int i=0;i<_TEST_COUNT;++i)
			{
				// - 
				CGD::ptr	ptrTemp	 = bufferCreate+2048;

				// - 
				ptrTemp.prepend(unordered_map_std_string_int);

				// - pop front!
				auto	temp	 = ptrTemp.extract<decltype(unordered_map_std_string_int)>();

				// Check) 비교...
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(temp==unordered_map_std_string_int, L"Fail to unordered_map<std::string,int> prepend/extract");
				Assert::IsTrue(ptrTemp.get_ptr()==(bufferCreate.front()+2048));
			#endif
			}
		}


		//-----------------------------------------------------------------
		// Test) int append / front 
		//-----------------------------------------------------------------
		TEST_METHOD(Test_ptr_4)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) Ptr
			CGD::ptr	ptrTemp		 = bufferTemp;

			// 2) 테스트를 위해 0~9 중 임의의 데이터 갯수를 구한다.
			int		iCount	 = rand()%10;

			// 3) 먼저 갯수를 써넣는다.
			ptrTemp.append<int>(iCount);

			// 4) 갯수만큼 데이터를 써넣는다.
			for(int i=0; i<iCount; ++i)
			{
				ptrTemp.append<int>(i);
			}

			// 5) ...
			{
				// - 값을 읽어온다.
				CGD::ptr	bufferRead	 = bufferTemp;

				// - 먼저 데이터의 값을 읽어온다.
				int	iCountX	 = bufferRead.extract<int>();

				// - 갯수만큼 데이터를읽어들인다.
				for(int i=0; i<iCountX; ++i)
				{
					int	value	 = bufferRead.extract<int>();

				#ifdef _ENABLE_ASSERT
					Assert::AreEqual(i, value, L"Fail to [int] append/extract ");
				#endif
				}
			}
		}
	#ifdef _SUPPORT_INITIALIZER_LIST
		TEST_METHOD(Test_ptr_map_tuple1)
		{
			// X) Memory Alloc
			char	tempBuffer[2048];

			// 1) Buffer를 할당한다. (넉넉하게 256Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) Ptr
			CGD::ptr	ptrTemp		 = bufferTemp;

			{
				// 2) 6개의 원소를 가진 임시 vector를 생성한다.
				int			iValue		 = 3;
				const char*	strValue	 = "Test";
				float		fValue		 = 2.0f;
	
				// 3) vector를 append하면 각 개체가 통채로 들어간다.
				ptrTemp.append(std::tuple<int, const char*, float>(iValue, strValue, fValue));
			}

			{
				// 1) 값을 읽어온다.
				CGD::ptr	bufferRead	 = bufferTemp;

				// 2) 값 읽기
				int			iValue		 = bufferRead.extract<int>();
				const char*	strValue	 = bufferRead.extract<const char*>();
				float		fValue		 = bufferRead.extract<float>();

				// Trace) 값을 찍어본다.

			}

			{
				// 1) 값을 읽어온다.
				CGD::ptr	bufferRead	 = bufferTemp;

				// 2) 값 읽기
				auto	tupleRead	 = bufferRead.extract<std::tuple<int, char*, float>>();

				// Trace) 값을 찍어본다.

			}

			{
				// 1) 값을 읽어온다.
				CGD::ptr	bufferRead	 = bufferTemp;

				// 2) 값 읽기
				auto	tupleRead	 = bufferRead.front<std::tuple<int, char*, float>>();

				// Trace) 값을 찍어본다.
			}

			{
				// 1) 값을 읽어온다.
				CGD::ptr	bufferRead	 = bufferTemp;

				// 2) 값 읽기
				int			iValue;
				const char*	strValue;
				float		fValue;

				// 3) std::tie<...>를 사용해서 값을 대입하기
				std::tie<int, const char*, float>(iValue, strValue, fValue)	 = bufferRead.extract<std::tuple<int, char*, float>>();

				// * std::tuple<T...>에 저장된 값을 std::tie<...>로 값을 대입할 수 있다.
				//
				//   std::get<0>(tupleRead) -> iValue
				//   std::get<1>(tupleRead) -> strValue
				//   std::get<2>(tupleRead) -> fValue
				//

				// Trace) 값을 찍어본다.
				//iValue, strValue, fValue;
			}
		}

		TEST_METHOD(Test_ptr_map_tuple2)
		{
			// Definitions)
			typedef	std::tuple<int, int, float, const char*>	TUPPLE_A;
			typedef	std::tuple<int, TUPPLE_A, const char*>		TUPPLE_B;

			// 1) 써넣은 예제 Tupple
			TUPPLE_B	temp	 = TUPPLE_B(0, TUPPLE_A(0, 0, 1.0f, "Test"), "Value");

			// X) Memory Alloc
			char	tempBuffer[2048];

			// 2) Buffer를 할당한다. (최소 64Byte를 할당받는다.)
			CGD::buffer	bufferTemp(tempBuffer);

			// 2) Ptr
			CGD::ptr	ptrTemp		 = bufferTemp;

			// 3)
			ptrTemp.append(temp);

			{
				// 1) 값을 읽어온다.
				CGD::ptr	tempRead	 = bufferTemp;

				// 2) 일어 값을 저장할 Tupple
				TUPPLE_B	tuppleRead	 = tempRead.extract<TUPPLE_B>();

				// Check) 
			#ifdef _ENABLE_ASSERT
				Assert::IsTrue(std::get<0>(temp)==std::get<0>(tuppleRead), L"Fail! Tupple 2");
				Assert::IsTrue(std::get<0>(std::get<1>(temp))==std::get<0>(std::get<1>(tuppleRead)), L"Fail! Tupple 2");
				Assert::IsTrue(std::get<1>(std::get<1>(temp))==std::get<1>(std::get<1>(tuppleRead)), L"Fail! Tupple 2");
				Assert::IsTrue(std::get<2>(std::get<1>(temp))==std::get<2>(std::get<1>(tuppleRead)), L"Fail! Tupple 2");
				Assert::IsTrue(std::char_traits<char>::compare(std::get<3>(std::get<1>(temp)),std::get<3>(std::get<1>(tuppleRead)),0)==0, L"Fail! Tupple 2");
				Assert::IsTrue(std::char_traits<char>::compare(std::get<2>(temp), std::get<2>(tuppleRead), 0)==0, L"Fail! Tupple 2");
			#endif
			}
		}
#endif


		////-----------------------------------------------------------------
		//// Test) Object Serialize
		////-----------------------------------------------------------------
		//TEST_METHOD(Test_ptr_append_extract_Serializable)
		//{
		//	struct TEMP_OBJECT : public CGD::IBufferSerializable
		//	{
		//	public:
		//		int			m_ix;
		//		float		m_fy;
		//		std::string	m_strZ;

		//	public:
		//		// Declare) 
		//		CGD_BUFFER_SERIAZABLE(TEMP_OBJECT);

		//		virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer)
		//		{
		//			m_ix	 = _Buffer.extract<int>();
		//			m_fy	 = _Buffer.extract<float>();
		//			m_strZ	 = _Buffer.extract<std::string>();

		//			return	true;
		//		}

		//		virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer)
		//		{
		//			_Buffer.append(m_ix);
		//			_Buffer.append(m_fy);
		//			_Buffer.append(m_strZ);

		//			return	true;
		//		}

		//	
		//	};

		//	// 1) 필요한 메모리는 12Byte지만 적당히 100Byte를 할당받았다.
		//	CGD::buffer	bufferTemp	 = malloc(1024);

		//	// Declare) 임시 객체
		//	TEMP_OBJECT	a;

		//	// 3) Object를 작성
		//	{
		//		// - 값을 집어 넣음
		//		a.m_ix	 = 10;
		//		a.m_fy	 = 2.0;
		//		a.m_strZ = "Test Value";

		//		// - 객체 append
		//		bufferTemp.append(a);
		//	}

		//	{
		//		// - 값을 읽을 버퍼
		//		CGD::buffer	tempRead	 = bufferTemp;

		//		// - 임시 객체를 생성
		//		TEMP_OBJECT	b;

		//		// - 객체 extract!
		//		b	 = tempRead.extract<TEMP_OBJECT>();

		//		// Check) 
		//		Assert::IsTrue(a.m_ix==b.m_ix, L"Fail to Object Serialize");
		//		Assert::IsTrue(a.m_fy==b.m_fy, L"Fail to Object Serialize");
		//		Assert::IsTrue(a.m_strZ==b.m_strZ, L"Fail to Object Serialize");
		//	}

		//	// 6) 할당 해제
		//	free(bufferTemp.clear());
		//}
	};
}