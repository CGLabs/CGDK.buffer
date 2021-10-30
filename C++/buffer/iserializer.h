//*****************************************************************************
//*                                                                           *
//*                              CGDK::buffer_view                            *
//*                        Ver 5.0 / Release 2020.12.11                       *
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

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CGDK::buffer_base
//
//-----------------------------------------------------------------------------
template <class ELEMENT_T = char>
class iserializaer
{
// traits) 
protected:
			using traits		 = _buffer_traits_t<ELEMENT_T>;
			using element_t		 = ELEMENT_T;
			using size_type		 = std::size_t;

public:
	// 2) prepend																								  
			template <std::size_t ISIZE>
	constexpr auto				prepend()																		{ return _prepend_skip(ISIZE);}
			template <class T>																					  
	constexpr T&				prepend()																		{ return *reinterpret_cast<T*>(_prepend_skip(sizeof(T)));}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(const T& _data)															{ return PRPD_t<basic_buffer, T>::_do_prepend(*this, _data);;}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(T&& _data)																{ return PRPD_t<basic_buffer, T>::_do_prepend(*this, _data);;}
	//		template <class T, std::size_t N>
	//constexpr typename serializer_prepend<T[N]>::type prepend(const T (&_data)[N])								{ return _prepend(_data);}
			template <class T> 																					  
	constexpr base_t			prepend(const T* _data, std::size_t _count)										{ return _prepend_array(_data, _count);}
			template <class T> 																					  
	constexpr auto				prepend(const std::initializer_list<T>& _list)									{ _prepend_initializer_list<T>(_list); return data();}
			template<class I> 																					  
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								prepend(I _first, I _last)														{ return _prepend_iterator(_first, _last);}
			auto				prepend(std::size_t _size, const void* _buffer)									{ return _prepend_bytes(_size, _buffer);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(std::basic_string_view<T> _text)									{ return _prepend_string(_text);}
	//		template <class T, std::size_t N>
	//constexpr std::enable_if_t<is_string_type<T>::value, base_t>
	//							prepend_string(const T(&_text)[N])												{ return _prepend_string_pointer(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(const std::basic_string_view<T> _format, F&& _first, TREST&&... _rest)	{ return _prepend_string_format(_format.data(), std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(const T(&_format)[N], F&& _first, TREST&&... _rest)				{ return _prepend_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(std::string_view _text)											{ return _prepend_text(_text);}
			template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(const T(&_text)[N])												{ return _prepend_text(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest)	{ return _prepend_text_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(const T(&_format)[N], F&& _first, TREST&&... _rest)				{ return _prepend_text_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}

	// 3) append
			template <std::size_t ISIZE>
	constexpr auto&				append()																		{ return _append_skip(ISIZE);}
			template <class T>																					  
	constexpr auto&				append()																		{ return _append_emplace<std::remove_reference_t<std::remove_const_t<T>>>();}
			template <class T>																					  
	constexpr appd_tr<T>		append(const T& _data)															{ return APPD_t<basic_buffer,T>::_do_append(*this, _data); }
			template <class T>																					  
	constexpr appd_tr<T>		append(T&& _data)																{ return APPD_t<basic_buffer,T>::_do_append(*this, std::forward<T>(_data)); }
			template <class T>																					  
	constexpr auto				append(const T* _data, std::size_t _count)										{ return _append_array(_data, _count);}
			template <class T> 																					  
	constexpr base_t			append(const std::initializer_list<T>& _List)									{ return _append_initializer_list<T>(_List);}
			template<class I> 																					  
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								append(I _first, I _last)														{ return _append_iterator(_first, _last);}
	constexpr auto				append(std::size_t _size, const void* _buffer)									{ return _append_bytes(_size, _buffer); }

			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest)			{ return _append_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append(const T(&_format)[N], F&& _first, TREST&&... _rest)						{ return _append_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(std::basic_string_view<T> _text)									{ return _append_text(_text);}

			template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(const T(&_text)[N])													{ return _append_text(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest)	{ return _append_text_fmt_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(const T(&_format)[N] , F&& _first, TREST&&... _rest)				{ return _append_text_fmt_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}

			template <class T = char, class TNUM>
	constexpr std::enable_if_t<std::is_integral_v<TNUM>, base_t>
				 				append_text(TNUM _value)														{ return _append_text_integral<T>(_value);}
			template <class T = char, class TNUM>
	constexpr std::enable_if_t<std::is_floating_point_v<TNUM>, base_t>
				 				append_text(TNUM _value)														{ return _append_text_float<T>(_value);}
};


}
