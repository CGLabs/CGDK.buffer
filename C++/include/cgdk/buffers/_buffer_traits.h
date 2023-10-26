//*****************************************************************************
//*                                                                           *
//*                               CGDK::buffer                                *
//*                       ver 3.03 / release 2023.10.17                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  programmed by Cho SangHyun. sangduck@cgcii.com                           *
//*                                                                           *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
// CGDK::buffer_traits
//-----------------------------------------------------------------------------
class  _buffer_traits_const {};
class  _buffer_traits_mutable {};


//-----------------------------------------------------------------------------
// CGDK::buffer_traits
//-----------------------------------------------------------------------------
template <class T, class F=void>	class _buffer_traits {};
template <class T>					class _buffer_traits <T, std::enable_if_t<std::is_const_v<T>>>	{ public: using type = _buffer_traits_const; };
template <class T>					class _buffer_traits <T, std::enable_if_t<!std::is_const_v<T>>>	{ public: using type = _buffer_traits_mutable; };

template <class T> using _buffer_traits_t = typename _buffer_traits<T>::type;


//-----------------------------------------------------------------------------
// CGDK::const...
//-----------------------------------------------------------------------------
template <class T, class F=void>	class _element_void {};
template <class T>					class _element_void <T, std::enable_if_t<std::is_const_v<T>>> { public: using type = const void; };
template <class T>					class _element_void <T, std::enable_if_t<!std::is_const_v<T>>> { public: using type = void; };

template <class T> using _element_void_t = typename _element_void<T>::type;


//-----------------------------------------------------------------------------
// CGDK::buffer_traits
//-----------------------------------------------------------------------------
template <class TRAITS_T, class T>	class _buffer_return {};
template <class T>					class _buffer_return< _buffer_traits_const, T> { public: using type = const T; };
template <class T>					class _buffer_return< _buffer_traits_mutable, T> { public: using type = T; };
																								
template <class TRAITS_T, class T> using _buffer_return_t = typename _buffer_return<TRAITS_T, T>::type;


}
