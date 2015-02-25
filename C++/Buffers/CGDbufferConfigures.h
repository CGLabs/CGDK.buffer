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

// 1) ������ �����ϴ� ��
//    - String Ȥ�� Container�� ���� �����͸� ��� ����� �� �������� ������ 
//      �����ϱ� ���� ���� �ǹ��Ѵ�.
//    - uint_16(16Bit Unsigned int)�� �Ϲ����̳� �ʿ信 ���� uint32_t�� uint8_t��
//      �پ��� ������ �����ϴ�.
//    - COUNT_T�� ���ǵǱ� ���� ���ǵǸ� �� ���ǿ� ������.
#ifndef	COUNT_T
	//typedef uint32_t	COUNT_T;
	typedef int16_t		COUNT_T;
#endif

// 2) ���� ��� �˻� ����
//    - ���ۿ� �����͸� �߰��� �� �� ��� �˻縦 �����Ͽ� ��踦 �Ѿ� �����
//      ASSERT�� �ɾ��ְų� Exception�� ������ ���࿡ ���� ���θ� �����Ѵ�.
//    - �Ϲ������� _DEBUG��忡���� Ȱ��ȭ�Ǹ� �ƴ� ��� ��Ȱ��ȭ �ȴ�.
//    - �ʿ����� ���� ��� �� ��� ���� ������ _CGD_DISABLE_BUFFER_BOUND_CHECK�� 
//      �߰��ϸ� �ȴ�.
//    - Debug ��尡 �ƴϾ �ʿ��� ��� _CGD_DISABLE_BUFFER_BOUND_CHECK��
//      ������� ������ ������ �ָ� �ȴ�.
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
