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
class ioserializaer
{
// traits) 
protected:
			using traits		 = _buffer_traits_t<ELEMENT_T>;
			using element_t		 = ELEMENT_T;
			using size_type		 = std::size_t;
};

}
