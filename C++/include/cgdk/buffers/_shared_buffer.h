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
			using memory_t	  = Imemory;

		#if defined(_CGDK)
			using object_ptr_t = object_ptr<memory_t>;
		#else
			using object_ptr_t = std::shared_ptr<memory_t>;
		#endif

			template <class T> using extr_tr = typename base_t::template extr_tr<T>;
			template <class T> class to_base_t {};
			template <class X> class to_base_t<_buffer_view<X>> { public: static _buffer_view<X> casting (Imemory* _rhs) { return (_rhs != nullptr) ? _buffer_view<X>{ _rhs->data(), 0}: _buffer_view<X>{}; }};
			template <class X> class to_base_t<_basic_buffer<X>> { public: static _basic_buffer<X> casting (Imemory* _rhs) { return (_rhs != nullptr) ? _basic_buffer<X> {_buffer_view<X>{ _rhs->data(), 0}, _rhs->get_bound()} : _basic_buffer<X>{}; }};

// constructor/destructor) 
public:
	constexpr _shared_buffer() noexcept {}
	constexpr _shared_buffer(const self_t& _copy) noexcept : base_t(_copy), psource(_copy.psource) {}
	constexpr _shared_buffer(self_t&& _move) noexcept : base_t(static_cast<base_t&>(_move)), psource(std::move(_move.psource)) {}
			template<class T>
	constexpr _shared_buffer(const _shared_buffer<T>& _copy) noexcept : base_t(_copy), psource(_copy.psource) {}
			template<class T>
	constexpr _shared_buffer(_shared_buffer<T>&& _move) noexcept : base_t(_move), psource(std::move(_move.psource)) {}
	constexpr _shared_buffer(const base_t& _buffer) noexcept : base_t(_buffer) {}
	constexpr _shared_buffer(base_t&& _buffer) noexcept : base_t(std::move(_buffer)) {}

protected:
#if defined(_CGDK)
	constexpr _shared_buffer(const base_t& _buffer, Imemory* _psource) noexcept : base_t(_buffer), psource(_psource) {}
	constexpr _shared_buffer(base_t&& _buffer, Imemory* _psource) noexcept : base_t(std::move(_buffer)), psource(_psource) {}
#else
	constexpr _shared_buffer(const base_t& _buffer, const object_ptr_t& _psource) noexcept : base_t(_buffer), psource(_psource) {}
	constexpr _shared_buffer(base_t&& _buffer, object_ptr_t& _psource) noexcept : base_t(std::move(_buffer)), psource(_psource) {}
#endif

public:
	// 1) capacity/clear/copy/clone
		#if defined(_CGDK)
			void				reserve(std::size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) { if ((this->data_ + _size) <= base_t::get_upper_bound()) return; _change_source(_mem_alloc(_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING));}
			void				resize(std::size_t _new_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) { reserve(_new_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); this->size_ = _new_size; }
			self_t				clone(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) const { self_t a; a = _mem_alloc(this->size_ CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); a._append_bytes(this->size_, this->data_); return a;}
			self_t				clone(size_t _buffer_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) const { if (_buffer_size < this->size_) _buffer_size = this->size_; self_t a; a = _mem_alloc(_buffer_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); a._append_bytes(this->size_, this->data_); return a;}
		#else
			void				reserve(std::size_t _size) { if ((this->data_ + _size) <= base_t::get_upper_bound()) return; _change_source(std::make_shared<memory_t>()); }
			void				resize(std::size_t _new_size) { this->reserve(_new_size); this->size_ = _new_size; }
			self_t				clone() const { self_t a = _alloc_shared_buffer(this->size_); a._append_bytes(this->size_, this->data_); return a;}
			self_t				clone(size_t _buffer_size) const { if(_buffer_size < this->size_) _buffer_size = this->size_; self_t a = _alloc_shared_buffer(_buffer_size); a._append_bytes(this->size_, this->data_); return a;}
		#endif
			void				shrink_to_fit()	 { if(this->remained_size() == 0) return; *this = this->clone(); }
			void				clear() noexcept { base_t::clear(); this->psource.reset();}
			void				swap(self_t& _rhs) noexcept { base_t::swap(_rhs); object_ptr_t p = std::move(_rhs.psource); _rhs.psource = std::move(this->psource); this->psource = std::move(p);}
			void				swap(base_t& _rhs) noexcept { base_t::swap(_rhs);}
	constexpr self_t			remained() const noexcept { return self_t(base_t(typename base_t::base_t{ this->get_back_ptr(), 0 }, this->bound), this->psource); }
	constexpr self_t			remained(skip _skip) const noexcept { return self_t(base_t(typename base_t::base_t{ this->get_back_ptr() + _skip.amount, 0 }, this->bound), this->psource); }
	template <class T>
			self_t				split_head(const _buffer_view<T>& _source);
	template <class T>
			self_t				split_tail(const _buffer_view<T>& _source);

	// 2) extract/subtract
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract() { return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest) { base_t::template extract_to<T>(_dest);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract() { return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract_to(T& _dest) { base_t::template extract_to<T>(_dest);}
			template <std::size_t ISIZE>
	constexpr auto				extract() { return self_t { base_t::template extract<ISIZE>(), psource }; }
	constexpr auto				extract(CGDK::size _length) { return self_t { base_t::extract(_length), psource }; }

	// 3) reference																							  
			void				set_source(Imemory* _pbuffer) noexcept { _set_source(_pbuffer);}
			void				set_source(const object_ptr_t& _source) noexcept { _set_source(_source);}
			void				set_source(object_ptr_t&& _source) noexcept { _set_source(std::move(_source));}
			object_ptr_t		get_source() const noexcept { return psource;}
			object_ptr_t&&		move_out_source() noexcept { return std::move(psource); }

	// 4) operator overloading																  
			// [operator] +/-
	constexpr self_t			operator ~  () const { return self_t { ~(*(base_t*)this), psource }; }
	constexpr self_t			operator +  (CGDK::offset _rhs) const { return self_t { base_t::operator+(_rhs), this->psource }; }
	constexpr self_t			operator -  (CGDK::offset _rhs) const { return self_t { base_t::operator-(_rhs), this->psource }; }
	constexpr self_t			operator +  (CGDK::size _rhs) const { return self_t { base_t::operator+(_rhs), this->psource }; }
	constexpr self_t			operator -  (CGDK::size _rhs) const { return self_t { base_t::operator-(_rhs), this->psource }; }
			// [operator] +=/-=			 
	constexpr self_t&			operator += (CGDK::offset _rhs) { base_t::operator+=(_rhs);	return *this; }
	constexpr self_t&			operator -= (CGDK::offset _rhs) { base_t::operator-=(_rhs);	return *this; }
	constexpr self_t&			operator += (CGDK::size _rhs) { base_t::operator+=(_rhs); return *this; }
	constexpr self_t&			operator -= (CGDK::size _rhs) { base_t::operator-=(_rhs); return *this; }
			template <class T>			    
	constexpr self_t&			operator += (const _buffer_view<T>& _rhs) { base_t::_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr self_t&			operator += (_buffer_view<T>&& _rhs) { base_t::_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator += (const T& _rhs) { for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator += (T&& _rhs) { for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, self_t&>
								operator += (const std::array<T, N>& _rhs) { for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, self_t&>
								operator += (std::array<T, N>&& _rhs) { for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<_buffer_view<typename T::element_t>, T>, self_t&>
								operator += (const _buffer_view<T>(&_rhs)[N] ) { const T* iter = _rhs; const T* iter_end = _rhs + N; for(;iter != iter_end; ++iter) { if (iter->empty()) continue; _append_bytes(iter->size(), iter->data());	} return *this;	}
	constexpr self_t&			operator += (const self_t& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr self_t&			operator += (self_t&& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr self_t&			operator -= (std::size_t _rhs) { this->data_ -= _rhs; this->size_ += _rhs; return *this;}
			// [operator] =
			template <class T>			    
	constexpr self_t&			operator =  (const _buffer_view<T>& _rhs) noexcept { base_t::operator=(_rhs); return *this;}
			template <class T>			    
	constexpr self_t&			operator =  (_buffer_view<T>&& _rhs) noexcept { base_t::operator=(_rhs); return *this;}
			template<class T>			    
	constexpr self_t&			operator =  (const buffer_base<T>& _rhs) { base_t::operator=(_rhs); return *this;}
			template<class T>			    
	constexpr self_t&			operator =  (buffer_base<T>&& _rhs) { base_t::operator=(_rhs); return *this;}
	constexpr self_t&			operator =  (const self_t& _rhs) noexcept { this->psource = _rhs.get_source(); base_t::operator=(_rhs); return *this;}
	constexpr self_t&			operator =  (self_t&& _rhs) noexcept { this->psource = std::move(_rhs.psource); base_t::operator=(_rhs); return *this;}
			self_t&				operator =  (Imemory* _rhs) noexcept { base_t::operator=(to_base_t<BASE_T>::casting(_rhs)); this->psource = _rhs; return *this;}
			self_t&				operator =  (const object_ptr_t& _rhs) noexcept { base_t::operator=(to_base_t<BASE_T>::casting(_rhs)); this->psource = _rhs; return *this; }
			self_t&				operator =  (object_ptr_t&& _rhs) noexcept { base_t::operator=(to_base_t<BASE_T>::casting(_rhs.get())); this->psource = std::move(_rhs); return *this; }

			// [operator] ^=
			template<class T>
	constexpr self_t&			operator ^= (const _buffer_view<T>& _rhs) { base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator ^= (_buffer_view<T>&& _rhs) { base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator ^= (const buffer_base<T>& _rhs) { base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator ^= (buffer_base<T>&& _rhs) { base_t::operator=(_rhs); return *this;}
	constexpr self_t&			operator ^= (std::size_t _rhs) { base_t::set_size(_rhs); return *this;}
			// [operator] >> - extract
			template <class T>
			self_t&				operator>>(T& _rhs) { _rhs = this->template _extract<T>(); return *this;}
			// [operator] << - append																			  
			template <class T>																					  
			self_t&				operator<<(const T& _rhs) { APPD_t<self_t, T>::_do_append(*this, _rhs); return *this;}
			// [operator] compare
			template <class T>
	constexpr bool				operator==(const self_t& _rhs) const noexcept { return this->data_ == _rhs.data() && this->size_ == _rhs.size();}
			template <class T>
	constexpr bool				operator==(const _buffer_view<T>& _rhs) const noexcept { return this->data_ == _rhs.data() && this->size_ == _rhs.size();}
			template <class T>
	constexpr bool				operator!=(const self_t& _rhs) const noexcept { return this->data_ != _rhs.data() || this->size_ != _rhs.size();}
			template <class T>
	constexpr bool				operator!=(const _buffer_view<T>& _rhs) const noexcept { return this->data_ != _rhs.data() || this->size_ != _rhs.size();}

public:
	// 5) begin/end) 
	constexpr self_t			_begin(int64_t _offset) const noexcept { return self_t(base_t::_begin(_offset), this->psource);}
	constexpr self_t			_end(int64_t _offset) const noexcept { return self_t(base_t::_end(_offset), this->psource);}

	// 6) extarct
			template<class BUFFER_T>
	constexpr _shared_buffer<BUFFER_T> _extract_shared_buffer();
protected:
	constexpr void				_change_source(object_ptr_t&& _pmem_new) noexcept { if(this->size_ > 0) { ::memcpy(_pmem_new->data(), this->data_, this->size_);} this->data_ = _pmem_new->data(); _set_source(std::move(_pmem_new));}
	constexpr void				_set_source(Imemory* _pmem_new) noexcept { this->psource = _pmem_new; base_t::_set_bound(_pmem_new->get_bound());}
	constexpr void				_set_source(object_ptr_t&& _pmem_new) noexcept { this->psource = std::move(_pmem_new); base_t::_set_bound(this->psource->get_bound());}

private:
			object_ptr_t		psource;

#if defined(_ENABLE_DEBUG_NEW)
			friend _shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS);
#else
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

	// check) this->data_를 넣는다.
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
constexpr CGDK::_shared_buffer<T> operator ^ (const CGDK::_shared_buffer<T>& _lhs, size_t _size)
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
	memcpy(this->data_ + this->size_ - _source.size(), _source.data(), _source.size());
	this->size_ -= _source.size();
	return *this ^ _buffer_view<T> {this->data_ + this->size_, _source.size()};
}


}