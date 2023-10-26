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
// CGDK::buffer_base
//-----------------------------------------------------------------------------
template <class ELEMENT_T = char>
class  buffer_base
{
// traits) 
protected:
			using traits	 = _buffer_traits_t<ELEMENT_T>;
			using element_t	 = ELEMENT_T;
			using size_type	 = size_t;

// variable)
public:
			size_type		size_ = 0;
			element_t*		data_ = nullptr;
};


//-----------------------------------------------------------------------------
// standard names (for C++ standard)
//-----------------------------------------------------------------------------
// 1) const_buffer
using const_buffer = buffer_base<const char>;

// 2) mutable_buffer
using mutable_buffer = buffer_base<char>;


//-----------------------------------------------------------------------------
// class defintions
//-----------------------------------------------------------------------------
// 1) memory
class Imemory;

}
