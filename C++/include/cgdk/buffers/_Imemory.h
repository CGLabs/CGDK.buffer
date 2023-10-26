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

#if !defined(_CGDK)
class Imemory : protected _buffer_view<char>
{
public:
			Imemory() noexcept {}
			Imemory(char* _data, std::size_t _size) noexcept : buffer_view(_data, _size) {}
			Imemory(const _buffer_view<char>& _buffer) noexcept : _buffer_view<char>(_buffer) {}
	virtual	~Imemory() noexcept {}

			auto data() const noexcept { return this->data_;}
			auto size() const noexcept { return this->size_; }

	auto	get_lower_bound() const noexcept { return data_;};
	auto	get_upper_bound() const noexcept { return data_ + size_;};
	auto	get_bound() const noexcept { return buffer_bound{ get_lower_bound(), get_upper_bound() }; };
};

_shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size);

#endif

}
