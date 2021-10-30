//*****************************************************************************
//*                                                                           *
//*                             CGDK::buffer_view                             *
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

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CGDK::buffer_base
//
//-----------------------------------------------------------------------------
template <class ELEMENT_T = char>
class oserializaer
{
// traits) 
protected:
			using traits		 = _buffer_traits_t<ELEMENT_T>;
			using element_t		 = ELEMENT_T;
			using size_type		 = std::size_t;

public:
	// 3) extract/subtract
			template <std::size_t ISIZE>
	constexpr auto				extract()								{ return _extract_bytes(ISIZE);}
	constexpr auto				extract(CGDK::size _length)				{ return _extract_bytes(_length.amount);}
	constexpr auto				extract(CGDK::skip _length)				{ return _extract_bytes(_length.amount);}
	constexpr auto				extract(size_type _size, void* _buffer)	{ return _extract_bytes(_size, _buffer);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract()								{ return serializer_extract<_buffer_view, std::remove_const_t<T>>::_do_extract(*this);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest)					{ serializer_extract<_buffer_view, std::remove_const_t<T>>::_do_extract(_dest, *this);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract()								{ return _extract_general<std::remove_reference_t<std::remove_const_t<T>>>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract(T& _dest)						{ _extract_general<std::remove_reference_t<std::remove_const_t<T>>>(_dest);}
			template <class T>
	constexpr auto				extract_string(T* _string, size_type _length_in_words=(size_type(-1))) { return _extract_string_copy(_string, _length_in_words);}
			template<class... T>
	constexpr _buffer_view		extract(const std::tuple<T...>& _tuple)	{ auto buf_old = this->data_; _extract_tuple(_tuple); return _buffer_view(buf_old, this->data_ - buf_old);}
			template<class... T>
	constexpr _buffer_view		extract(std::tuple<T...>&& _tuple)		{ auto buf_old = this->data_; _extract_tuple(std::move(_tuple)); return _buffer_view(buf_old, this->data_ - buf_old);}
	constexpr std::string_view	extract_web_modify()					{ return _extract_web_modify();}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								extract_text(T _terminal = 0)			{ return _extract_text(_terminal);}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								extract_text(T _terminal, T _modify)	{ return _extract_text(_terminal, _modify);}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								extract_text(CGDK::size _length)		{ return _extract_text<T>(_length.amount);}

			template <class T>
	constexpr auto&				subtract()								{ return _subtract_general<T>();}
	constexpr auto				subtract(size_type _length)				{ return _subtract_bytes(_length);}

	// 4) front
	constexpr auto				front(int64_t _offset = 0) const		{ return _front(_offset);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, peek_tr<T>>
								front(int64_t _offset = 0) const		{ return _front<T>(_offset);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								front(int64_t _offset = 0) const		{ return _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_offset);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								front_to(T& _dest, int64_t _offset = 0) const { _front<T>(_dest, _offset);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								front_to(T& _dest, int64_t _offset = 0) const { _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_dest, _offset);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, peek_tr<T>>
								front(POS& _pos) const					{ return _front<T>(_pos.offset);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								front(POS& _pos) const					{ return _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_pos.offset);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								front_to(T& _dest, POS& _pos) const		{ _front<T>(_dest, _pos.offset);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								front_to(T& _dest, POS& _pos) const		{ _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_dest, _pos.offset);}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								front_text(T _terminal = 0, int64_t _offset = 0) { return _front(_text<T>(_terminal, _offset));}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								front_text(CGDK::size _length, int64_t _offset = 0) { return _front_text_by_length<T>(_length.amount, _offset);}

	// 5) back
	constexpr auto				back(int64_t _offset = 0) const			{ return _back(_offset);}
			template <class T>
	constexpr peek_tr<T>		back(int64_t _offset = 0) const			{ return _back<T>(_offset);}
			template <class T>
	constexpr peek_tr<T>		back(POS& _pos) const					{ return _back<T>(_pos.offset);}
};


}
