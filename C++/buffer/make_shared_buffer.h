//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             Archive Classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
#if defined(CGDK_SYSTEM_OBJECT)

// make_shared_buffer
template <class T, class E = void>
constexpr void _do_post_make_shared_buffer(CGDK::_shared_buffer<buffer>&)
{
}

// alloc_shared_buffer
inline _shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size)
{
	// declare)
	_shared_buffer<buffer> buf_serialized;

	// 1) set memory source
	buf_serialized = std::make_shared<char>(new chaar[_size]);

	// 2) set bound info
	buf_serialized.bound.upper = reinterpret_cast<const char*>(buf_serialized.bound.lower) + _size;

	// return) 
	return buf_serialized;
}

template <class T>
_shared_buffer<buffer> _make_shared_buffer(const T& _data)
{
	// 1) allocate shared_buffer
	auto buf_serialized = _alloc_shared_buffer(get_size_of(_data));
	
	// 2) append _data
	buf_serialized.template append<std::remove_reference_t<std::remove_cv_t<T>>>(_data);

	// 3) do post_process (optional)
	_do_post_make_shared_buffer<T>(buf_serialized);

	// return) 
	return buf_serialized;
}

template <class ELEM_T>
template<class BUFFER_T>
constexpr _shared_buffer<BUFFER_T> _buffer_view<ELEM_T>::_extract_shared_buffer()
{
	// declare)
	_shared_buffer<BUFFER_T> buf_temp;

	// 1) get length of data
	std::size_t length = this->_extract<size_type>();

	// check)
	RETURN_IF(length == 0, buf_temp);

	// 2) alloc shared buffer
	buf_temp = alloc_shared_buffer(length);

	// 3) append data
	buf_temp.append(length, data());

	// 4) extract bytes
	this->_extract_bytes(length);

	// return) 
	return buf_temp;
}
#endif

template <class T, class U>
inline _shared_buffer<buffer> operator + (_buffer_view<T>&& _lhs, _buffer_view<U>&& _rhs)
{
	// 1) alloc shared_buffer
	auto temp = alloc_shared_buffer(_lhs.size() + _rhs.size());

	// 2) append data
	temp._append_bytes(_lhs.size(), _lhs.data());
	temp._append_bytes(_rhs.size(), _rhs.data());
	
	// return)
	return temp;
}


}