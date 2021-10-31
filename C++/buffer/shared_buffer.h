//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            CGBuffer Templates                             *
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
//-----------------------------------------------------------------------------
//
// CGDK::_shared_buffer<T>
//
//
//-----------------------------------------------------------------------------
#if !defined(CGDK_SYSTEM_OBJECT)
	_shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size);
#endif

template <class BASE_T = _buffer_view<char>>
class _shared_buffer : public BASE_T
{
// traits) 
public:
			using base_t	  = BASE_T;
			using self_t	  = _shared_buffer<BASE_T>;
			using traits	  = typename base_t::traits;
			using element_t	  = typename base_t::element_t;
			using size_type	  = typename base_t::size_type;

			template<class T> using extr_tr = typename base_t::template extr_tr<T>;

// constructor/destructor) 
public:
	constexpr _shared_buffer() noexcept {}
	constexpr _shared_buffer(const _shared_buffer& _copy) noexcept : base_t(_copy), psource(_copy.psource) {}
	constexpr _shared_buffer(_shared_buffer&& _move) noexcept : base_t(_move), psource(std::move(_move.psource)) {}
			template<class T>
	constexpr _shared_buffer(const _shared_buffer<T>& _copy) noexcept : base_t(_copy), psource(_copy.psource) {}
			template<class T>
	constexpr _shared_buffer(_shared_buffer<T>&& _move) noexcept : base_t(_move), psource(std::move(_move.psource)) {}
	constexpr _shared_buffer(const base_t& _buffer) noexcept : base_t(_buffer) {}
	constexpr _shared_buffer(base_t&& _buffer) noexcept : base_t(std::move(_buffer)) {}
	template <class T>
	constexpr _shared_buffer(std::basic_string_view<T> _string) noexcept : base_t{ _string } {}

protected:
#if defined(CGDK_SYSTEM_OBJECT)
	constexpr _shared_buffer(const base_t& _buffer, Imemory* _psource) noexcept : base_t(_buffer), psource(_psource) {}
	constexpr _shared_buffer(base_t&& _buffer, Imemory* _psource) noexcept : base_t(std::move(_buffer)), psource(_psource) {}
#else
	constexpr _shared_buffer(const base_t& _buffer, std::shared_ptr<char>& _psource) noexcept : base_t(_buffer), psource(_psource) {}
	constexpr _shared_buffer(base_t&& _buffer, std::shared_ptr<char>& _psource) noexcept : base_t(std::move(_buffer)), psource(_psource) {}
#endif

public:
	// 1) capacity/clear/copy/clone
		#if defined(_ENABLE_DEBUG_NEW)
			void				reserve(std::size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) { if ((this->data_ + _size) <= base_t::get_upper_bound()) return; _change_source(_mem_alloc(_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING));}
			void				resize(std::size_t _new_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) { reserve(_new_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); this->size_ = _new_size; }
			_shared_buffer		clone(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) const		{ _shared_buffer a; a = _mem_alloc(this->size_ CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); a._append_bytes(this->size_, this->data_); return a;}
			_shared_buffer		clone(size_t _buffer_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) const { if (_buffer_size < this->size_) _buffer_size = this->size_; _shared_buffer a; a = _mem_alloc(_buffer_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); a._append_bytes(this->size_, this->data_); return a;}
		#else
			void				reserve(std::size_t _size)									{ if ((this->data_ + _size) <= base_t::get_upper_bound()) return; _change_source(::malloc(_size));}
			void				resize(std::size_t _new_size)								{ reserve(_new_size); this->size_ = _new_size; }
			_shared_buffer		clone() const												{ _shared_buffer a = _alloc_shared_buffer(this->size_); a._append_bytes(this->size_, this->data_); return a;}
			_shared_buffer		clone(size_t _buffer_size) const							{ if(_buffer_size < this->size_) _buffer_size = this->size_; _shared_buffer a = _alloc_shared_buffer(_buffer_size); a._append_bytes(this->size_, this->data_); return a;}
		#endif
	constexpr void				clear() noexcept											{ base_t::clear(); psource.reset();}
	constexpr void				swap(_shared_buffer& _rhs) noexcept							{ base_t::swap(_rhs); auto p = std::move(_rhs.psource); _rhs.psource = std::move(psource); psource = std::move(p);}
	constexpr void				swap(base_t& _rhs) noexcept									{ base_t::swap(_rhs);}
	template <class T>
	constexpr void				copy_from(const _buffer_view<T>& _source) noexcept			{ memcpy(this->data_, _source.data(), _source.size_); this->size_ = _source.size_;}
	template <class T>
			_shared_buffer		split_head(const _buffer_view<T>& _source);
	template <class T>
			_shared_buffer		split_tail(const _buffer_view<T>& _source);

	// 2) extract/subtract
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract()													{ return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest)										{ base_t::template extract_to<T>(_dest);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract()													{ return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract_to(T& _dest)										{ base_t::template extract_to<T>(_dest);}
			template <std::size_t ISIZE>
	constexpr auto				extract()													{ return _shared_buffer{ base_t::template extract<ISIZE>(), psource }; }
	constexpr auto				extract(CGDK::size _length)									{ return _shared_buffer{ base_t::extract(_length), psource }; }
	constexpr auto				extract(CGDK::skip _length)									{ return _shared_buffer{ base_t::extract(_length.amount), psource }; }

	// 3) reference
	#if defined(CGDK_SYSTEM_OBJECT)
			void				set_source(Imemory* _pbuffer) noexcept						{ _set_source(_pbuffer);}
			void				set_source(const object_ptr<Imemory>& _source) noexcept		{ _set_source(_source);}
			void				set_source(object_ptr<Imemory>&& _source) noexcept			{ _set_source(std::move(_source));}
			auto				get_source() const noexcept									{ return psource;}
	#else
			void				set_source(const std::shared_ptr<char>& _source) noexcept	{ _set_source(_source);}
			void				set_source(std::shared_ptr<char>&& _source) noexcept		{ _set_source(std::move(_source));}
			auto				get_source() const noexcept									{ return psource;}
	#endif
	// 4) operator overloading																  
			// [operator] +/-
	constexpr _shared_buffer	operator ~  () const										{ return _shared_buffer { ~(*(base_t*)this), psource }; }
	constexpr _shared_buffer	operator +  (offset _rhs) const								{ return _shared_buffer { base_t::operator+(_rhs), psource }; }
	constexpr _shared_buffer	operator -  (offset _rhs) const								{ return _shared_buffer { base_t::operator-(_rhs), psource }; }
	constexpr _shared_buffer	operator +  (CGDK::size _rhs) const							{ return _shared_buffer { base_t::operator+(_rhs), psource }; }
	constexpr _shared_buffer	operator -  (CGDK::size _rhs) const							{ return _shared_buffer { base_t::operator-(_rhs), psource }; }
			// [operator] +=/-=			 
	constexpr _shared_buffer&	operator += (offset _rhs)									{ base_t::operator+=(_rhs);	return *this; }
	constexpr _shared_buffer&	operator -= (offset _rhs)									{ base_t::operator-=(_rhs);	return *this; }
	constexpr _shared_buffer&	operator += (CGDK::size _rhs)								{ base_t::operator+=(_rhs);	return *this; }
	constexpr _shared_buffer&	operator -= (CGDK::size _rhs)								{ base_t::operator-=(_rhs);	return *this; }
			template <class T>			    
	constexpr _shared_buffer&	operator += (const _buffer_view<T>& _rhs)					{ base_t::_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr _shared_buffer&	operator += (_buffer_view<T>&& _rhs)						{ base_t::_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, _shared_buffer&>
								operator += (const T& _rhs)									{ for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, _shared_buffer&>
								operator += (T&& _rhs)										{ for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, _shared_buffer&>
								operator += (const std::array<T, N>& _rhs)					{ for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, _shared_buffer&>
								operator += (std::array<T, N>&& _rhs)						{ for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, _shared_buffer&>
								operator += (const _buffer_view<T>(&_rhs)[N] )				{ const T* iter = _rhs; const T* iter_end = _rhs + N; for(;iter != iter_end; ++iter) { if (iter->empty()) continue; _append_bytes(iter->size(), iter->data());	} return *this;	}
	constexpr _shared_buffer&	operator += (const _shared_buffer& _rhs)					{ this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr _shared_buffer&	operator += (_shared_buffer&& _rhs)							{ this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr _shared_buffer&	operator -= (std::size_t _rhs)								{ this->data_ -= _rhs; this->size_ += _rhs; return *this;}
			// [operator] =
			template <class T>			    
	constexpr _shared_buffer&	operator =  (const _buffer_view<T>& _rhs) noexcept			{ base_t::operator=(_rhs); return *this;}
			template <class T>			    
	constexpr _shared_buffer&	operator =  (_buffer_view<T>&& _rhs) noexcept				{ base_t::operator=(_rhs); return *this;}
			template<class T>			    
	constexpr _shared_buffer&	operator =  (const buffer_base<T>& _rhs)					{ base_t::operator=(_rhs); return *this;}
			template<class T>			    
	constexpr _shared_buffer&	operator =  (buffer_base<T>&& _rhs)							{ base_t::operator=(_rhs); return *this;}
	constexpr _shared_buffer&	operator =  (const _shared_buffer& _rhs) noexcept			{ psource = _rhs.get_source(); base_t::operator=(_rhs); return *this;}
	constexpr _shared_buffer&	operator =  (_shared_buffer&& _rhs) noexcept				{ psource = std::move(_rhs.psource); base_t::operator=(_rhs); return *this;}
	constexpr _shared_buffer&	operator =  (const static_buffer& _rhs) noexcept			{ base_t::operator=(_rhs); psource.reset(); return *this;}
	constexpr _shared_buffer&	operator =  (static_buffer&& _rhs) noexcept					{ base_t::operator=(_rhs); psource.reset(); return *this;}
	#if defined(CGDK_SYSTEM_OBJECT)
			_shared_buffer&		operator =  (Imemory* _rhs) noexcept						{ base_t::operator=(_rhs); psource = _rhs; return *this;}
			_shared_buffer&		operator =  (const object_ptr<Imemory>& _rhs) noexcept		{ base_t::operator=(_rhs); psource = _rhs; return *this;}
			_shared_buffer&		operator =  (object_ptr<Imemory>&& _rhs) noexcept			{ base_t::operator=(_rhs); psource = std::move(_rhs); return *this; }
	#else
			_shared_buffer&		operator =  (const std::shared_ptr<char>& _rhs) noexcept	{ base_t::operator=(_rhs); psource = _rhs; return *this;}
			_shared_buffer&		operator =  (std::shared_ptr<char>&& _rhs) noexcept			{ base_t::operator=(_rhs); psource = std::move(_rhs); return *this; }
	#endif
			// [operator] ^=
			template<class T>
	constexpr _shared_buffer&	operator ^= (const _buffer_view<T>& _rhs)					{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr _shared_buffer&	operator ^= (_buffer_view<T>&& _rhs)						{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr _shared_buffer&	operator ^= (const buffer_base<T>& _rhs)					{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr _shared_buffer&	operator ^= (buffer_base<T>&& _rhs)							{ base_t::operator=(_rhs); return *this;}
	constexpr _shared_buffer&	operator ^= (std::size_t _rhs)								{ base_t::set_size(_rhs); return *this;}
			// [operator] >> - extract
			template <class T>
			_shared_buffer&	operator>>(T& _rhs)												{ _rhs = this->template _extract<T>(); return *this;}
			// [operator] compare
			template <class T>
	constexpr bool				operator==(const _shared_buffer& _rhs) const noexcept		{ return this->data_ == _rhs.data() && this->size_ == _rhs.size();}
			template <class T>
	constexpr bool				operator==(const _buffer_view<T>& _rhs) const noexcept		{ return this->data_ == _rhs.data() && this->size_ == _rhs.size();}
			template <class T>
	constexpr bool				operator!=(const _shared_buffer& _rhs) const noexcept		{ return this->data_ != _rhs.data() || this->size_ != _rhs.size();}
			template <class T>
	constexpr bool				operator!=(const _buffer_view<T>& _rhs) const noexcept		{ return this->data_ != _rhs.data() || this->size_ != _rhs.size();}

public:
	// 5) begin/end) 
	constexpr _shared_buffer	_begin(int64_t _offset) const noexcept						{ return _shared_buffer(base_t::_begin(_offset), psource);}
	constexpr _shared_buffer	_end(int64_t _offset) const noexcept						{ return _shared_buffer(base_t::_end(_offset), psource);}

	// 6) extarct
			template<class BUFFER_T>
	constexpr _shared_buffer<BUFFER_T> _extract_shared_buffer();
protected:
#if defined(CGDK_SYSTEM_OBJECT)
	constexpr void				_change_source(object_ptr<Imemory>&& _pmem_new) noexcept	{ if(this->size_ > 0) { std::memcpy(_pmem_new->data_, this->data_, this->size_);} this->data_ = _pmem_new->data_; _set_source(std::move(_pmem_new));}
	constexpr void				_set_source(Imemory* _pmem_new) noexcept					{ psource = _pmem_new; base_t::_set_bound(_pmem_new->get_bound());}
	constexpr void				_set_source(object_ptr<Imemory>&& _pmem_new) noexcept		{ psource = std::move(_pmem_new); base_t::_set_bound(psource->get_bound());}
#else
	constexpr void				_change_source(std::shared_ptr<char>&& _pmem_new) noexcept	{ if (this->size_ > 0) { std::memcpy(_pmem_new->data_, this->data_, this->size_); } this->data_ = _pmem_new->data_; _set_source(std::move(_pmem_new)); }
	constexpr void				_set_source(const std::shared_ptr<char>& _pmem_new) noexcept{ psource = _pmem_new; base_t::_set_bound(_pmem_new->get_bound()); }
	constexpr void				_set_source(std::shared_ptr<char>&& _pmem_new) noexcept		{ psource = std::move(_pmem_new); base_t::_set_bound(psource->get_bound()); }
#endif

private:
#if defined(CGDK_SYSTEM_OBJECT)
			object_ptr<Imemory>	psource;
			friend _shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS);
#else
			std::shared_ptr<char> psource;
			friend _shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size);
#endif
};

template <class BASE_T>
template<class BUFFER_T>
constexpr _shared_buffer<BUFFER_T> _shared_buffer<BASE_T>::_extract_shared_buffer()
{
	// declare)
	_shared_buffer<BUFFER_T> buf_temp;

	// check) 
	_CGD_BUFFER_BOUND_CHECK(this->size_ >= sizeof(size_type));

	// 1) [데이터_갯수를 먼저 읽어들인다.]
	auto length = *reinterpret_cast<size_type*>(this->data_);

	// check)
	if(length == 0)
		return buf_temp;

	// 2) 
	const auto bytes_extract = length + sizeof(size_type);
	const auto ptr_data = this->data_ + sizeof(size_type);

	// 2) 
	buf_temp = _shared_buffer<BUFFER_T>{ BASE_T{ ptr_data, length }, get_source() };

	// 3) [데이터_바이트수]만큼 
	this->_extract_bytes(length);

	// return) 
	return buf_temp;
}

template <class T>
constexpr CGDK::_shared_buffer<T> operator ^ (const CGDK::_shared_buffer<T>& _lhs, std::size_t _size)
{
	CGDK::_shared_buffer<T> x = _lhs;
	x.set_size(_size);
	return x;
}

template <class T, class U>
constexpr CGDK::_shared_buffer<T> operator ^ (const CGDK::_shared_buffer<T>& _lhs, CGDK::_buffer_view<U> _buffer)
{
	CGDK::_shared_buffer<T> x = _lhs;
	x = _buffer;
	return x;
}


}


namespace CGDK
{

template <class ELEM_T>
template <class T>
_shared_buffer<ELEM_T> _shared_buffer<ELEM_T>::split_head(const _buffer_view<T>& _source)
{
	_CGD_BUFFER_BOUND_CHECK(this->size_ >= _source.size());
	memcpy(this->data_, _source.data(), _source.size());
	char* p = this->data_;
	this->data_ += _source.size();
	this->size_ -= _source.size();
	return *this ^ _buffer_view<element_t> {p, _source.size() };
}

template <class ELEM_T>
template <class T>
_shared_buffer<ELEM_T> _shared_buffer<ELEM_T>::split_tail(const _buffer_view<T>& _source)
{
	_CGD_BUFFER_BOUND_CHECK(this->size_ >= _source.size());
	memcpy(this->data_ + this->size_ - _source.size_, _source.data(), _source.size());
	this->size_ -= _source.size();
	return *this ^ _buffer_view<T> {this->data_ + this->size_, _source.size()};
}


}