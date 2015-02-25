//*****************************************************************************
//*                                                                           *
//*                                CGD::buffer                                *
//*                      Ver 2.0pre / Release 2015.01.05                      *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.com           *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// Configures for CGBuffer
//
//
//-----------------------------------------------------------------------------

// 1) 갯수를 저장하는 형
//    - String 혹은 Container등 여러 데이터를 묶어서 써넣을 때 데이터의 갯수를 
//      저장하기 위한 형을 의미한다.
//    - uint_16(16Bit Unsigned int)가 일반적이나 필요에 따라 uint32_t나 uint8_t등
//      다양한 설정이 가능하다.
//    - COUNT_T가 정의되기 전에 정의되면 그 정의에 따른다.
#ifndef	COUNT_T
	//typedef uint32_t	COUNT_T;
	typedef int16_t		COUNT_T;
#endif

// 2) 버퍼 경계 검사 여부
//    - 버퍼에 데이터를 추가할 때 그 경계 검사를 수행하여 경계를 넘어 설경우
//      ASSERT를 걸어주거나 Exception을 던지는 수행에 대한 여부를 결정한다.
//    - 일반적으로 _DEBUG모드에서는 활성화되며 아닐 경우 비활성화 된다.
//    - 필요하지 않을 경우 이 헤드 파일 이전에 _CGD_DISABLE_BUFFER_BOUND_CHECK를 
//      추가하면 된다.
//    - Debug 모드가 아니어도 필요할 경우 _CGD_DISABLE_BUFFER_BOUND_CHECK를
//      헤드파일 이전에 선언해 주면 된다.
#if defined(_CGD_DISABLE_BUFFER_BOUND_CHECK)
	#if defined(_CGD_ENABLE_BUFFER_BOUND_CHECK)
		#error "Conflict _CGD_ENABLE_BUFFER_BOUND_CHECK and _CGD_NO_BUFFER_BOUND_CHECK! select one only!"
	#endif
#elif !defined(_CGD_ENABLE_BUFFER_BOUND_CHECK)
	#if defined(_DEBUG)
		#define	_CGD_ENABLE_BUFFER_BOUND_CHECK
	#endif
#endif

// 3) Support =delete (C++11)
#ifndef _SUPPORT_DELETE_FUNCTION
	#if _MSC_VER>=1800
		#define _SUPPORT_DELETE_FUNCTION
	#endif
#endif

// 4) Support variodic template paramter (C++11)
#ifndef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
	#if _MSC_VER>=1800
		#define _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
	#endif
#endif

// 5) Support constexpr (C++11)
#ifndef _CONSTEXPR
	#if _MSC_VER>=1800
		#define	_CONSTEXPR	constexpr
	#else
		#define	_CONSTEXPR
	#endif
#endif // !_CONSTEXPR

// 6) Zero-sized Array (C++11)
#ifndef _SUPPORT_ZERO_SIZED_ARRAY
	#if _MSC_VER>=1700
		#define _SUPPORT_ZERO_SIZED_ARRAY
	#endif
#endif

// 7) Suport C++11 Traits 
#ifndef _SUPPORT_CPP11_TRAITS
	#if _MSC_VER>=1700
		#define _SUPPORT_CPP11_TRAITS
	#endif
#endif
