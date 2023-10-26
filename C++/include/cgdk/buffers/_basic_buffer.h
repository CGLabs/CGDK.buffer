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

#if !defined(FMT_FORMAT_H_) && !defined(__GNUC__)
	#include <format>
#endif

namespace CGDK
{
#if defined(FMT_FORMAT_H_)
	template <class T, class... TREST>
	constexpr std::basic_string<T> _fmt_format_string(std::basic_string_view<T> _format, TREST&&... _rest)
	{
		return fmt::format(_format, std::forward<TREST>(_rest)...);
	}
#else
	#if defined(__GNUC__)
		template <class T, class... TREST>
		constexpr std::basic_string<T> _fmt_format_string(std::basic_string_view<T> _format, TREST&&... _rest)
		{
		#if defined(__linux__)
			// check) GCC don't support {fmt} yet~ include {fmt} manually
			assert(false);

			// retrun) failre
			return std::basic_string<T>();
		#else
			return std::format(_format, std::forward<TREST>(_rest)...);
		#endif
		}
	#else
		template <class... TREST>
		constexpr std::string _fmt_format_string(std::string_view _format, TREST&&... _rest)
		{
			return std::vformat(_format, std::make_format_args(std::forward<TREST>(_rest)...));
		}
		template <class... TREST>
		constexpr std::wstring _fmt_format_string(std::wstring_view _format, TREST&&... _rest)
		{
			return std::vformat(_format, std::make_wformat_args(std::forward<TREST>(_rest)...));
		}
	#endif
#endif

template <class ELEM_T>
class _basic_buffer : public _buffer_view<char>
{
// traits) 
public:
			using base_t = _buffer_view<char>;
			using self_t = _basic_buffer<ELEM_T>;
			using traits = typename base_t::traits;
			using element_t = typename base_t::element_t;
			using size_type = typename base_t::size_type;

			template<class T> using peek_tr = PEEK_tr<self_t, T>;
			template<class T> using extr_tr = EXTR_tr<self_t, T>;
			template<class T> using appd_tr = APPD_tr<self_t, T>;
			template<class T> using prpd_tr = PRPD_tr<self_t, T>;

// constructor/destructor) 
public:
	constexpr _basic_buffer() noexcept {}
	constexpr _basic_buffer(const _basic_buffer& _buffer) noexcept : base_t(_buffer), bound(_buffer.get_bound()) {}
	constexpr _basic_buffer(_basic_buffer&& _buffer) noexcept : base_t(_buffer), bound(_buffer.get_bound()) {}
	template <class T>
	constexpr _basic_buffer(_buffer_view<T> _buffer) noexcept : base_t(_buffer), bound{ _buffer.get_front_ptr(), _buffer.get_back_ptr() } {}
	template <class T>
	constexpr _basic_buffer(_buffer_view<T> _buffer, const buffer_bound& _bound) : base_t(_buffer), bound(_bound) { _CGD_BUFFER_BOUND_CHECK(_buffer.get_front_ptr() >= _bound.lower && _buffer.get_back_ptr() <= _bound.upper); }
	template <class T>
	constexpr _basic_buffer(_buffer_view<T> _buffer, buffer_bound&& _bound) : base_t(_buffer), bound(_bound) { _CGD_BUFFER_BOUND_CHECK(_buffer.get_front_ptr() >= this->get_lower_bound() && _buffer.get_back_ptr() <= this->get_back_ptr<T>()); }

	template <class T, size_t N>
	constexpr _basic_buffer(T (&_buffer)[N]) : base_t(_buffer, 0), bound{reinterpret_cast<element_t*>(_buffer), reinterpret_cast<element_t*>(_buffer + N)} {}
	template <class T, size_t N>
	constexpr _basic_buffer(std::array<T, N>& _buffer) : base_t(_buffer.data(), 0), bound{ reinterpret_cast<element_t*>(_buffer.data()), reinterpret_cast<element_t*>(_buffer.data() + _buffer.size()) } {}
	template <class T>
	constexpr _basic_buffer(std::basic_string_view<T> _string) : base_t(_string.data(), 0), bound{ reinterpret_cast<element_t*>(_string.data()), reinterpret_cast<element_t*>(_string.data() + _string.size()) } {}

public:
	// 1) capacity/clear/copy/clone
	constexpr void				set_size(size_type _new_size) { _CGD_BUFFER_BOUND_CHECK((this->data_ + _new_size) >= this->get_lower_bound() && (this->data_ + _new_size) <= this->get_upper_bound()); this->size_ = _new_size; }
	constexpr void				add_size(size_type _size) { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + _size) <= this->get_upper_bound()); this->size_ += _size; }
	constexpr void				sub_size(size_type _size) { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ - _size) >= this->get_lower_bound()); this->size_ -= _size; }
	constexpr void				inc_size() { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + 1) <= this->get_upper_bound()); ++this->size_; }
	constexpr void				dec_size() { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ - 1) >= this->get_lower_bound()); --this->size_; }

	// 2) data/
	constexpr element_t*		data() const noexcept { return this->data_; }
	constexpr element_t*		data(int64_t _offset) const { _CGD_BUFFER_BOUND_CHECK((this->data_ + _offset) <= this->get_upper_bound()); return this->data_ + _offset; } // unsafe
	template <class T = element_t>
	constexpr auto				data() const noexcept { return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_); }
	template <class T = element_t>
	constexpr auto				data(int64_t _offset) const { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + _offset) <= this->get_upper_bound()); return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_ + _offset); } // unsafe
	constexpr void				set_data(element_t* _data) { _CGD_BUFFER_BOUND_CHECK(_data >= this->get_lower_bound() && (_data + this->size_) <= this->get_upper_bound()); this->data_ = _data; } // unsafe
	constexpr void				add_data(size_type _size) { _CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + _size) <= this->get_upper_bound()); this->data_ += _size; } // unsafe
	constexpr void				sub_data(size_type _size) { _CGD_BUFFER_BOUND_CHECK((this->data_ - _size) >= this->get_lower_bound()); this->data_ -= _size; } // unsafe

	constexpr std::size_t		capacity() const noexcept { return (this->bound.upper != nullptr) ? (reinterpret_cast<const element_t*>(this->bound.upper) - this->data_) : 0;}
	constexpr std::size_t		remained_size() const noexcept { return this->get_remained_size();}
	constexpr void				clear() noexcept { this->base_t::clear(); this->bound.reset();}
	constexpr self_t			remained() const noexcept { return self_t({ this->get_back_ptr(),0}, this->bound); }
	constexpr self_t			remained(skip _skip) const noexcept { return self_t({this->get_back_ptr() + _skip.amount, 0 }, this->bound); }
			template <class T>
			void				copy_from(const _buffer_view<T>& _source) { if (this->data_ + _source.size() > this->get_upper_bound()) throw std::length_error("buffer overflow. out of upper bound 'copy(_source)'"); memcpy(data(), _source.data(), _source.size()); size_ = _source.size();}
	constexpr void				swap(_basic_buffer& _rhs) noexcept { this->base_t::swap(_rhs); auto p = _rhs.get_bound(); _rhs._set_bound(bound); bound = p; }
	constexpr void				swap(base_t& _rhs) { if (_rhs.data() < this->get_lower_bound() || (_rhs.data() + _rhs.size()) > this->get_upper_bound()) { assert(false); throw std::out_of_range("_rhs data_ is must in bound of this shared_buffer"); } this->base_t::swap(_rhs); }
			self_t				split_head(const base_t& _source)
			{
				_CGD_BUFFER_BOUND_CHECK(size_ >= _source.size());
				char* p = this->data_;
				memcpy(p, _source.data(), _source.size());
				this->data_+= _source.size();
				this->size_-=_source.size();
				return self_t{ buffer_view{p, _source.size()}, bound };
			}
			self_t				split_tail(const base_t& _source)
			{
				_CGD_BUFFER_BOUND_CHECK(size_ >= _source.size());
				char* p = this->data_;
				memcpy(p + this->size_ - _source.size(), _source.data(), _source.size());
				this->size_ -= _source.size();
				return self_t{ buffer_view{p + this->size_, _source.size()}, bound };
			}

	// 3) prepend																								  
			template <std::size_t N>
	constexpr auto				prepend() { return _prepend_skip(N);}
			template <class T>																					  
	constexpr T&				prepend() { return *reinterpret_cast<T*>(_prepend_skip(sizeof(T)));}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(const T& _data) { return PRPD_t<self_t, T>::_do_prepend(*this, _data);;}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(T&& _data) { return PRPD_t<self_t, T>::_do_prepend(*this, _data);;}
			template <class T> 																					  
	constexpr base_t			prepend(const T* _data, std::size_t _count) { return _prepend_array(_data, _count);}
			template <class T> 																					  
	constexpr auto				prepend(const std::initializer_list<T>& _list) { _prepend_initializer_list<T>(_list); return data();}
			template<class I> 																					  
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								prepend(I _first, I _last) { return _prepend_iterator(_first, _last);}
			auto				prepend(std::size_t _size, const void* _buffer) { return _prepend_bytes(_size, _buffer);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(std::basic_string_view<T> _text) { return _prepend_string(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(const std::basic_string_view<T> _format, F&& _first, TREST&&... _rest) { return _prepend_string_format(_format.data(), std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_string(const T(&_format)[N], F&& _first, TREST&&... _rest) { return _prepend_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(std::string_view _text) { return _prepend_text(_text);}
			template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(const T(&_text)[N]) { return _prepend_text(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest) { return _prepend_text_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								prepend_text(const T(&_format)[N], F&& _first, TREST&&... _rest) { return _prepend_text_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}

	// 4) append
			template <std::size_t N>
	constexpr auto&				append() { return this->_append_skip(N);}

			template <class T>																					  
	constexpr std::enable_if_t<is_basic_type_v<T>, T&>
						  		append() { return this->_append_emplace<std::remove_reference_t<std::remove_const_t<T>>>();}
	template <class T>
	constexpr std::enable_if_t<!is_basic_type_v<T>, appd_tr<T>>
								append() { return this->append<T>(T{}); }
			template <class T>																					  
	constexpr appd_tr<T>		append(const T& _data) { return APPD_t<self_t,T>::_do_append(*this, _data); }
			template <class T>																					  
	constexpr appd_tr<T>		append(T&& _data) { return APPD_t<self_t,T>::_do_append(*this, std::forward<T>(_data)); }
			template <class T>																					  
	constexpr auto				append(const T* _data, std::size_t _count) { return this->_append_array(_data, _count);}
			template <class T> 																					  
	constexpr base_t			append(const std::initializer_list<T>& _List) { return this->_append_initializer_list<T>(_List);}
			template<class I> 																					  
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								append(I _first, I _last) { return _append_iterator(_first, _last);}
	constexpr auto				append(std::size_t _size, const void* _buffer) { return this->_append_bytes(_size, _buffer); }

			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest) { return this->_append_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append(const T(&_format)[N], F&& _first, TREST&&... _rest) { return this->_append_string_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(std::basic_string_view<T> _text) { return this->_append_text(_text);}

			template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(const T(&_text)[N]) { return this->_append_text(_text);}
			template <class T, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(std::basic_string_view<T> _format, F&& _first, TREST&&... _rest) { return this->_append_text_format(_format.data(), std::forward<F>(_first), std::forward<TREST>(_rest)...);}
			template <class T, std::size_t N, class F, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								append_text(const T(&_format)[N] , F&& _first, TREST&&... _rest) { return this->_append_text_format(_format, std::forward<F>(_first), std::forward<TREST>(_rest)...);}

			template <class T = char, class TNUM>
	constexpr std::enable_if_t<std::is_integral_v<TNUM>, base_t>
				 				append_text(TNUM _value) { return this->_append_text_integer<T>(_value);}
			template <class T = char, class TNUM>
	constexpr std::enable_if_t<std::is_floating_point_v<TNUM>, base_t>
				 				append_text(TNUM _value) { return this->_append_text_float<T>(_value);}
			template <class T = char>
			base_t				append_text_hex(const char* _data, std::size_t _size) { return this->_append_text_binary<T>(_data, _size); }

	// 5) extract/subtract
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract() { return this->base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest) { this->base_t::template extract_to<T>(_dest);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract() { return this->base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract_to(T& _dest) { this->base_t::template extract_to<T>(_dest);}
			template <std::size_t N>
	constexpr auto				extract() { return self_t(this->base_t::extract(CGDK::size(N)), bound);}
	constexpr auto				extract(CGDK::size _length) { return self_t(this->base_t::extract(_length), bound);}

	// 6) reference
			template <class T = char>
	constexpr void				set_front_ptr(T* _pos) { _CGD_BUFFER_BOUND_CHECK(_pos >= this->get_lower_bound() && _pos <= this->get_back_ptr<T>()); auto temp_offset = reinterpret_cast<element_t*>(_pos) - this->data_; this->data_ = reinterpret_cast<element_t*>(_pos); this->size_ -= temp_offset;  }
			template <class T = char>
	constexpr void				set_back_ptr(T* _pos) { _CGD_BUFFER_BOUND_CHECK(_pos >= this->get_front_ptr<T>() && _pos <= this->get_upper_bound()); this->size_ = reinterpret_cast<element_t*>(_pos) - this->data_; }
	constexpr const buffer_bound& get_bound() const noexcept { return this->bound;}
	constexpr std::size_t		get_remained_size() const noexcept { return static_cast<const char*>(this->bound.upper) - this->data_ - this->size_;}

	// 7) operator overloading																					  
			// [operator] +/-		
	constexpr self_t			operator ~ () const { auto data_value = this->data_ + this->size_; return self_t{ base_t { data_value, static_cast<size_type>(static_cast<const element_t*>(this->bound.upper) - data_value) }, this->bound }; }
	constexpr self_t			operator + (offset _rhs) const { return self_t{ this->base_t::operator+(_rhs), bound };}
	constexpr self_t			operator - (offset _rhs) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ - _rhs.amount >= this->get_lower_bound());

				// return) 
				return self_t(base_t{ this->data_ - _rhs.amount, this->size_ + _rhs.amount }, bound);
			}
	constexpr self_t			operator+(CGDK::size _rhs) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ + this->size_ + _rhs.amount <= this->get_upper_bound());

				// return) 
				return self_t(base_t{ this->data_, this->size_ + _rhs.amount }, bound);
			}
	constexpr self_t			operator-(CGDK::size _rhs) const { return self_t{ this->base_t::operator-(_rhs), bound }; }
			// [operator] +=/-=
	constexpr self_t&			operator+=(offset _rhs) { this->base_t::operator+=(_rhs); return *this; }
	constexpr self_t&			operator-=(offset _rhs)
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ - _rhs.amount >= this->get_lower_bound());

				this->data_ -= _rhs.amount;
				this->size_ += _rhs.amount;
				
				return *this;
			}
	constexpr self_t			operator+=(CGDK::size _rhs)
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ + this->size_ + _rhs.amount <= this->get_upper_bound());

				// - add
				this->size_ += _rhs.amount;

				// return) 
				return *this;
			}
	constexpr self_t			operator-=(CGDK::size _rhs) { this->base_t::operator-=(_rhs); return *this; }
	constexpr self_t&			operator+=(const base_t& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr self_t&			operator+=(base_t&& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator+=(const T& _rhs) { for (auto& iter : _rhs) { if (iter.empty()) continue; this->_append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator+=(T&& _rhs) { for (auto& iter : _rhs) { if (iter.empty()) continue; this->_append_bytes(iter.size(), iter.data()); } return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(const std::array<T, N>& _rhs) { for(auto& iter: _rhs) { if (iter.empty()) continue; this->_append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(std::array<T, N>&& _rhs) { for(auto& iter: _rhs) { if (iter.empty()) continue; this->_append_bytes(iter.size(), iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(const base_t(&_rhs)[N] ) { const T* iter = _rhs; const T* iter_end = _rhs + N; for(;iter != iter_end; ++iter) { if (iter->empty()) continue; this->_append_bytes(iter->size_, iter->data_); } return *this;	}
	constexpr self_t&			operator+=(const self_t& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr self_t&			operator+=(self_t&& _rhs) { this->_append_bytes(_rhs.size(), _rhs.data()); return *this;}
			// [operator] =
	constexpr self_t&			operator= (const base_t& _rhs) noexcept { _check_bound(_rhs); this->base_t::operator=(_rhs); return *this; }
	constexpr self_t&			operator= (base_t&& _rhs) noexcept { _check_bound(_rhs); this->base_t::operator=(_rhs); return *this; }
	constexpr self_t&			operator= (const self_t& _rhs) noexcept { this->base_t::operator=(_rhs); bound = _rhs.bound; return *this; }
	constexpr self_t&			operator= (self_t&& _rhs) noexcept { this->base_t::operator=(_rhs); bound = _rhs.bound; return *this; }

			// [operator] ^=
			template<class T>
	constexpr self_t&			operator^=(const _buffer_view<T>& _rhs) { this->base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(_buffer_view<T>&& _rhs) { this->base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(const buffer_base<T>& _rhs) { this->base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(buffer_base<T>&& _rhs) { this->base_t::operator=(_rhs); return *this;}
	constexpr self_t&			operator^=(std::size_t _rhs) { this->base_t::set_size(_rhs); return *this;}
			// [operator >> - extract
			template <class T>
			self_t&				operator>>(T& _rhs) { _rhs = _extract<T>(); return *this;}
			// [operator] << - append																			  
			template <class T>																					  
			self_t&				operator<<(const T& _rhs) { APPD_t<self_t, T>::_do_append(*this, _rhs); return *this;}

public:
	// prepend) 
	template <class T>
	constexpr prpd_tr<T>		_prepend(const T& _data) { return PRPD_t<self_t,T>::_do_prepend(*this, _data);}
	template <class T>
	constexpr prpd_tr<T>		_prepend(T&& _data) { return PRPD_t<self_t,T>::_do_prepend(*this, _data); }
	constexpr base_t			_prepend_skip(std::size_t _size)
			{
				// check) lower bound
				_CGD_BUFFER_BOUND_CHECK((this->data_ - this->_size) >= this->get_lower_bound());

				// 1) decrease [source_buffer_pointer] as much as _size
				this->data_ -= _size;

				// 2) increase [source_buffer_size] as much as _size
				this->size_ += _size;

				// return) 
				return base_t(this->data_, _size);
			}

	template <class T>
	constexpr T&				_prepend_general(const T& _data)
	{
		//// check) T must basic type
		//static_assert(is_general_serializable_v<T>, "T is not basic type, so it may not work properly. use ENABLE_STRUCT_SERIALIZABLE");

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - sizeof(T)) >= this->get_lower_bound());

		// 1) copy into [buffer]
		*reinterpret_cast<T*>(this->data_ - sizeof(T)) = _data;
	
		// 2) ...
		this->data_ -= sizeof(T);
		this->size_ += sizeof(T);
	
		// return) 
		return *reinterpret_cast<T*>(data());
	}
	template <class T> 
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_prepend_array(const T* _data, std::size_t _count)
	{
		// 1)
		auto buf_old = this->data_;

		// 2) copy by size [data_count]
		_prepend_bytes(sizeof(T)*_count, _data);

		// 3) write [data_count]
		_prepend<COUNT_T>(static_cast<COUNT_T>(_count));

		// return) 
		return base_t(this->data_, buf_old - this->data_);
	}
	template <class T> 
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_prepend_array(const T* _data, std::size_t _count)
	{
		// 1)
		auto buf_old = this->data_;

		// 2) prepend data by [data_count]
		for(int i=static_cast<int>(_count-1);i>=0;--i)
		{
			_prepend<T>(_data[i]);
		}

		// 3) write [data_count]
		_prepend<COUNT_T>(static_cast<COUNT_T>(_count));

		// return) 
		return base_t(this->data_, buf_old - this->data_);
	}
	template <class T, std::size_t N>
	constexpr base_t			_prepend_string(const T(&_string)[N])
	{
		// 1) calculate string size ( string + NULL )
		constexpr auto lengh_string = std::char_traits<T>::length(_string) + 1;
		constexpr auto bytes_copy = lengh_string * sizeof(T);
		constexpr auto added_length = sizeof(COUNT_T) + bytes_copy;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - added_length) >= this->get_lower_bound());

		// 2) obtain [target_pointer] by subtracting [source_buffer_pointer] by [string_length]
		auto p = this->data_ - bytes_copy;

		// 3) copy string to [source_buffer_pointer] as much as [string_length]
		memcpy(p, _string, bytes_copy);

		// 4) 이동
		p -= sizeof(COUNT_T);

		// 4) write [string_length]
		*reinterpret_cast<COUNT_T*>(p) = bytes_copy;

		// 5) update [source_buffer_pointer] and [source_buffer_length]
		this->data_  = p;
		this->size_ += added_length;

		// return) 
		return base_t(p, added_length);
	}
	template <class T, class TY, std::size_t N>
	constexpr base_t			_prepend_string_encoding(const TY(&_string)[N])
	{
		// 1) calculate string size ( string + NULL )
		constexpr auto lengh_string = std::char_traits<T>::length(_string) + 1;
		constexpr auto bytes_copy = lengh_string * sizeof(T);
		constexpr auto added_length = sizeof(COUNT_T) + bytes_copy;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - added_length) >= this->get_lower_bound());

		// 2) obtain [target_pointer] by subtracting [source_buffer_pointer] by [string_length]
		auto p = this->data_ - bytes_copy;

		// 3) encoding string
		if (bytes_copy != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) move [target_pointer] by size of COUNT_T
		p -= sizeof(COUNT_T);

		// 4) write [string_length]
		*reinterpret_cast<COUNT_T*>(p) = bytes_copy;

		// 5) update [source_buffer_pointer] and [source_buffer_length]
		this->data_  = p;
		this->size_ += added_length;
				
		// return) 
		return base_t(p, added_length);
	}

	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string_format(const T* _format, TREST&&... _rest)
	{
#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		// check) _format must not be nullptr
		CGDK_ASSERT(_format != nullptr, throw std::invalid_argument("_format is nullptr [0]"));

		// 1) store data_
		auto buf_old = this->data_;

		// 2) [원본_버퍼_시작_크기]에 [형식_문자열]를 써넣는다.
		auto temp_buffer = _fmt_format_string(std::basic_string_view<T>(_format), std::forward<TREST>(_rest)...);
		const auto str_start = temp_buffer.data();
		const auto length_string = temp_buffer.size() + 1;
		const auto size_string = length_string * sizeof(T);

		// 3) [목표_포인터]를 구한다.
		auto p = this->data_ - size_string;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((p - sizeof(COUNT_T)) >= this->get_lower_bound());
	
		// 4) [문자열]을 복사한다.
		memcpy(p, str_start, size_string);

		// 5) [목표_포인터]를 sizeof(COUNT_T)만큼을 뺀다.
		p -= sizeof(COUNT_T);

		// 6) [문자열_길이]를 써넣는다.
		*reinterpret_cast<COUNT_T*>(p) = static_cast<COUNT_T>(length_string);

		// 7)[원본_버퍼_포인터]를 업데이트한다.
		this->data_ = p;
		this->size_ += size_string + sizeof(COUNT_T);

		// return) 
		return base_t(this->data_, buf_old - p);
#else
		#if defined(__cpp_lib_format)
			//static_assert(false, "include <format> before including 'CGDK.buffer'");
			throw std::exception("include <format> before including 'CGDK.buffer'");
		#else
			//static_assert(false, "'std::format' is not supported");
			throw std::exception("'std::format' is not supported");
		#endif
#endif
	}
	template <class T>
	constexpr base_t			_prepend_text(std::string_view _string)
	{
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_string!=nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [문자열_길이]를 구한다.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string) >= this->get_lower_bound());

		// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		auto p = reinterpret_cast<T*>(this->data_ - size_string);
	
		// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
		if(p!=_string)
		{
			memcpy(p, _string, size_string);
		}

		// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
		this->data_ = p;
		this->size_ += size_string;

		// return) 
		return base_t(p, size_string);
	}
	template <class T, class TY>
	constexpr base_t			_prepend_text_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [문자열_길이]를 구한다.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string) >= this->get_lower_bound());

		// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		auto p = reinterpret_cast<T*>(this->data_ - size_string);
	
		// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
		if(size_string != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
		this->data_ = p;
		this->size_ += size_string;

		// return) 
		return base_t(p, size_string);
	}

	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text_format(const T* _format, TREST&&... _rest)
	{
#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_format != nullptr, throw std::invalid_argument("_format is nullptr! [0]"));

		auto temp_buffer = _fmt_format_string(std::basic_string_view<T>(_format), std::forward<TREST>(_rest)...);
		const auto str_start = temp_buffer.data();
		const auto size_string = (temp_buffer.size() + 1) * sizeof(T);

		// 6) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		auto p = this->data_ - size_string;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK(p >= this->get_lower_bound());

		// 7) [문자열]을 추가한다.
		memcpy(p, str_start, size_string);

		// 9) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
		this->data_ = p;
		this->size_ += size_string;

		// return) 
		return base_t(p, size_string);
#else
		#if defined(__cpp_lib_format)
			//static_assert(false, "include <format> before including 'CGDK.buffer'");
			throw std::exception("include <format> before including 'CGDK.buffer'");
		#else
			//static_assert(false, "'std::format' is not supported");
			throw std::exception("'std::format' is not supported");
		#endif
#endif
	}
	constexpr base_t			_prepend_bytes(std::size_t _size, const void* _buffer)
	{
		// check) _buffer이 nullptr이면 안된다.
		CGDK_ASSERT(_buffer != nullptr, throw std::invalid_argument("_buffer is nullptr [1]"));

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - _size) >= this->get_lower_bound());

		// 1) store data_
		auto buf_old = this->data_;

		// 2) [원본_버퍼_포인터]의 크기를 _size만큼 줄인다.
		auto p = buf_old -_size;
	
		// check) _size가 0이면 끝낸다.
		if(_size == 0) return base_t(p,0);

		// 3) [원본_버퍼_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
		if(_buffer != nullptr && _buffer != p)
		{
			memcpy(p, _buffer, _size);
		}

		// 4) update data_ and size_
		this->data_  = p;
		this->size_ += _size;

		// return) 
		return base_t(this->data_, buf_old - this->data_);
	}
	constexpr self_t			_prepend_buffer(const base_t& _buffer)
	{
		// 1) store data_
		auto buf_old = this->data_;

		// 1) [데이터_갯수]만큼 데이터들을 통채로 복사한다.
		_prepend_bytes(_buffer.size(), _buffer.data());

		// 2) [데이터_갯수]를 써넣는다.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_buffer.size()));

		// return) 
		return self_t{ base_t{ this->data_, static_cast<size_type>(buf_old - this->data_) } };
	}
	template <class T>
	constexpr base_t			_prepend_initializer_list(const std::initializer_list<T>& _list)
	{
		auto p = this->data_;

		for(auto& iter:_list)
		{
			_prepend<T>(iter);
		}
		
		return base_t(p, this->data_ - p);
	}
	template <class T>
	constexpr base_t			_prepend_tuple(const std::tuple<T>& _data)
	{
		auto p = this->data_;
		_prepend<T>(std::get<0>(_data)); 
		return base_t(this->data_, p - this->data_);
	}
	template <class TFIRST, class TSECOND, class... TREST>
	constexpr base_t			_prepend_tuple(const std::tuple<TFIRST, TSECOND, TREST...>& _tupple)
	{
		auto p = this->data_;
		_prepend_tuple((const std::tuple<TSECOND, TREST...>&)_tupple); _prepend<TFIRST>(std::get<0>(_tupple));
		return base_t(this->data_, p - this->data_);
	}
	template <class T>
	constexpr void				_prepend_multi_(T&& _data)
	{
		_prepend<T>(std::forward<T>(_data));
	}
	template <class TFIRST, class TSECOND, class... TREST>
	constexpr void				_prepend_multi_(TFIRST&& _first, TSECOND&& _second, TREST&&... _rest)
	{
		_prepend_multi_<TSECOND, TREST...>(std::forward<TSECOND>(_second), std::forward<TREST>(_rest)...);
		_prepend<TFIRST>(std::forward<TFIRST>(_first));
	}
	template<class... T>
	constexpr base_t			_prepend_multi(T&&... _multi)
	{ 
		auto p = this->data_;
		_prepend_multi_<T...>(std::forward<T>(_multi)...);
		return base_t(this->data_, p - this->data_);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string(std::basic_string_view<T> _string)
	{
		// 1) ...
		const auto buf_old = this->data_;

		// 2) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
		const auto length_string = _string.length();
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string - sizeof(COUNT_T)) >= this->get_lower_bound());

		// 3) NULL으르 제일 먼저 넣는다.
		_prepend_general<T>(0);

		// 4) [문자열]을 [문자열_길이]만큼 복사한다.
		_prepend_bytes(size_string, _string.data());

		// 5) [문자열_길이]를 써넣는다.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(length_string + 1));

		// return) String의 제일 처음 위치를 리턴함!!
		return base_t(this->data_, buf_old - this->data_);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [문자열_길이]를 구한다.
		const auto length_string = _string.length();
		const auto size_string = (length_string + 1) * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string - sizeof(COUNT_T)) >= this->get_lower_bound());

		// 2) ...
		auto p = reinterpret_cast<T*>(this->data_ - sizeof(T));

		// 3) append NULL
		*reinterpret_cast<COUNT_T*>(p) = 0;

		// 4) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		p -= length_string;

		// 5) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
		if (length_string != 0 && p != _string.data())
		{
			encode_string(p, _string);
		}

		// 6) [문자열 길이]를 써넣는다.
		*reinterpret_cast<COUNT_T*>(reinterpret_cast<char*>(p) - sizeof(COUNT_T)) = length_string + 1;

		// 7) update data_ and size_
		this->data_ = p;
		this->size_ += size_string + sizeof(COUNT_T);

		// return) String의 제일 처음 위치를 리턴함!!
		return	base_t(data_, size_string + sizeof(COUNT_T));
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text(std::basic_string_view<T> _string)
	{
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [문자열_길이]를 구한다.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string) >= this->get_lower_bound());

		// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		auto p = this->data_ - size_string;

		// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
		if (p != _string)
		{
			memcpy(p, _string, size_string);
		}

		// 4) update data_ and size_
		this->data_ = p;
		this->size_ += size_string;

		// return) 
		return base_t(p, p - this->data_);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string이 nullptr이면 안된다.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [문자열_길이]를 구한다.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ - size_string) >= this->get_lower_bound());

		// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
		auto p = this->data_ - size_string;

		// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
		if (size_string != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) update data_ and size_
		this->data_ = p;
		this->size_ += size_string;

		// return) 
		return base_t(p, p - this->data_);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, base_t>
								_prepend_container_array(const T& _container)
	{
		// 1) store data_
		auto p = this->data_;

		// 2) [데이터]들을 바로 memcopy한다.
		this->_prepend_bytes(_container.size() * sizeof(typename T::value_type), &_container.front());

		// 3) [데이터_갯수]를 써넣는다.
		this->_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return base_t(this->data_, p - this->data_);
	}
	template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, base_t>
								_prepend_container_array(const T& _container)
	{
		// 1) store data_
		auto p = this->data_;

		// 2) Begin/End Iterator
		auto iter = _container.rbegin();
		auto iter_end = _container.rend();

		// 3) [데이터]들을 써넣는다.
		for (; iter != iter_end; ++iter)
		{
			this->_prepend<typename T::value_type>(*iter);
		}

		// 4) [데이터_갯수]를 써넣는다.
		this->_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return base_t(this->data_, p - this->data_);
	}
	template<class RI>
	constexpr std::enable_if_t<is_iterator<RI>::value, base_t>
								_prepend_iterator(RI _reverse_first, RI _reverse_last)
	{
		// 1) store data_
		auto p = this->data_;

		// declare)
		COUNT_T iter_count = 0;

		// 1) 데이터들을 저장한다.
		for (; _reverse_first != _reverse_last; ++_reverse_first, ++iter_count)
		{
			this->_prepend<typename RI::value_type>(*_reverse_first);
		}

		// 2) 크기를 써넣을 위치 예약
		this->_prepend_general<COUNT_T>(iter_count);

		// return) 
		return base_t(this->data_, p - this->data_);
	}
	// append) 
	template <class T>
	constexpr appd_tr<T>		_append(const T& _data)
	{
		return APPD_t<self_t,T>::_do_append(*this, _data);
	}
	template <class T>
	constexpr appd_tr<T>		_append(const object_ptr<std::remove_const_t<T>>& _data)
	{
		return this->APPD_t<self_t,T>::_do_append(*this, *_data);
	}
	template <class T>
	constexpr base_t			_append_initializer_list(const std::initializer_list<T>& _list)
	{
		auto p = this->data_;
		for(auto& iter:_list)
		{
			_append<T>(iter);
		}
		return base_t(p, this->data_ - p);
	}
	constexpr base_t			_append_skip(std::size_t _length)
	{
		// 1) [원본_버퍼_끝_포인터]를 구한다.
		auto p = this->data_ + this->size_;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((p + _length) <= this->get_upper_bound());

		// 2) [원본_버퍼_길이]를 _length만큼 늘린다. 
		this->size_ += _length;

		// return) [원본_버퍼_끝_포인터]값을 리턴한다.
		return base_t(p, _length);
	}
	template <class T>
	constexpr T&				_append_emplace()
	{
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + sizeof(T)) <= this->get_upper_bound());

		// 1) [원본_버퍼_끝_포인터]를 구한다.
		auto p = reinterpret_cast<T*>(this->data_ + this->size_);

		// 2) [원본_버퍼_끝_포인터]에 생성자를 호출한다.
	#pragma push_macro("new")
	#undef new
		new (p) T;
	#pragma pop_macro("new")

		// 3) [원본_버퍼_길이]를 _length만큼 늘린다. 
		this->size_ += sizeof(T);

		// return) [원본_버퍼_끝_포인터]값을 리턴한다.
		return *p;
	}
	template <class T>
	constexpr T&				_append_general(const T& _data)
	{
		//// check) T must basic type
		//static_assert(is_general_serializable_v<T>, "T is not basic type, so it may not work properly. use ENABLE_STRUCT_SERIALIZABLE");

		// 1) [원본_버퍼_끝_포인터]를 구한다.
		auto p = reinterpret_cast<T*>(this->data_ + this->size_);
	
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((p + 1) <= this->get_upper_bound());

		// 2) [원본_버퍼_끝_포인터]에 값(_data)를 써넣는다.
		*p = _data;
	
		// 3) [원본_버퍼_길이]를 sizeof(T)만큼 늘린다. 
		this->size_ += sizeof(T);
	
		// return) [원본_버퍼_끝_값]을 리턴한다.
		return *p;
	}
	template <class T> 
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data, std::size_t _count)
	{
		// check) _data이 nullptr이면 안된다.
		CGDK_ASSERT(_data != nullptr && _count != 0, throw std::invalid_argument("_data is nullptr or _count is 0 [1]"));

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + sizeof(T) * _count) <= this->get_upper_bound());

		// 1) [원본_버퍼_포인터]를 저장해 놓는다.
		auto len_old = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_count));

		// 3) [데이터]들을 추가한다.
		for(std::size_t i=0; i<_count; ++i)
		{
			this->_append<T>(_data[i]);
		}

		// return)
		return base_t(this->data_ + len_old, this->size_ - len_old);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data, std::size_t _count)
	{
		// check) _data이 nullptr이면 안된다.
		CGDK_ASSERT(_data != nullptr && _count != 0, throw std::invalid_argument("_data is nullptr or _count is 0 [1]"));
	
		// 1) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_count));

		// 2) [데이터]들을 통채로 복사한다.
		return this->_append_bytes(_count * sizeof(T), _data);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data)
	{
		return this->_append_array<T>(_data, N);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data)
	{
		// check)
		static_assert(N != 0, "size of array '_data' is 0");

		// 1) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(N));

		// 2) [데이터]들을 통채로 복사한다.
		return this->_append_bytes(N * sizeof(T), _data);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string(std::basic_string_view<T> _string)
	{
		// 1) [목표_포인터]를 구한다.
		const auto buf_dest = this->data_ + this->size_;

		// 2) get values
		const auto length_string = _string.size();	// strnlen(, _buffer_size)
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + sizeof(T) + bytes_copy;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= this->get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [문자열_길이]를 저장한다. (NULL포함)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string + 1);
		buf_now += sizeof(COUNT_T);

		// 4) copy string
		if (bytes_copy != 0)
		{
			memcpy(buf_now, _string.data(), bytes_copy);
			buf_now += bytes_copy;
		}

		// 5) NULL을 추가한다.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [버퍼_길이]를 업데이트한다.
		this->size_ += added_length;

		// return)
		return base_t(buf_dest, added_length);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_encoding(std::basic_string_view<TY> _string)
	{
		// 1) [목표_포인터]를 구한다.
		const auto buf_dest = this->data_ + this->size_;

		// 2) get values
		const auto length_string = _string.size();	// strnlen(, _buffer_size)
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + sizeof(T) + bytes_copy;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= this->get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [문자열_길이]를 저장한다. (NULL포함)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string + 1);
		buf_now += sizeof(COUNT_T);

		// 4) copy string
		if (bytes_copy != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_now), _string);
			buf_now += bytes_copy;
		}

		// 5) NULL을 추가한다.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [버퍼_길이]를 업데이트한다.
		this->size_ += added_length;

		// return)
		return base_t(buf_dest, added_length);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string(const T(&_string)[N])
	{
		// declare)
		const auto length_string = std::char_traits<T>::length(_string) + 1;
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + bytes_copy;

		// 1) 문자열을 복사할 위치를 구한다.
		auto buf_dest = this->data_ + this->size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= this->get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [문자열_길이]를 저장한다. (NULL포함)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string);
		buf_now += sizeof(COUNT_T);

		// 4) [문자열]을 [원본_버퍼_포인터] 위치에 복사한다.
		if (bytes_copy != 0)
		{
			memcpy(buf_now, _string, bytes_copy);
			buf_now += bytes_copy;
		}

		// 5) NULL을 추가한다.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [버퍼_길이]를 업데이트한다.
		this->size_ += added_length;

		// return) 리턴
		return base_t(buf_dest, added_length);
	}
	template <class T, std::size_t N, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_encoding(const TY(&_string)[N])
	{
		// declare)
		const auto length_string = std::char_traits<T>::length(_string) + 1;
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + bytes_copy;

		// 1) 문자열을 복사할 위치를 구한다.
		auto buf_dest = this->data_ + this->size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= this->get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [문자열_길이]를 저장한다. (NULL포함)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string);
		buf_now += sizeof(COUNT_T);

		// 4) [문자열]을 [원본_버퍼_포인터] 위치에 복사한다.
		if (bytes_copy != 0)
		{
			this->encode_string(reinterpret_cast<T*>(buf_now), _string);
			buf_now += bytes_copy;
		}

		// 5) NULL을 추가한다.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [버퍼_길이]를 업데이트한다.
		this->size_ += added_length;

		// return) 리턴
		return base_t(buf_dest, added_length);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_format(std::basic_string_view<T> _format, TREST&&... _rest)
	{
#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		// 1) get formatted string
		auto temp_buffer = _fmt_format_string(_format, std::forward<TREST>(_rest)...);
		const auto length_string = temp_buffer.size() + 1;
		const auto size_string = length_string * sizeof(T);

		// 2) get [dest]
		const auto buf_dest = this->data_ + this->size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + sizeof(COUNT_T) + size_string) <= this->get_upper_bound());

		// 4) store [string_length]
		*reinterpret_cast<COUNT_T*>(buf_dest) = static_cast<COUNT_T>(length_string);

		// 5) copy string to buffer
		::memcpy(buf_dest + sizeof(COUNT_T), temp_buffer.data(), size_string);

		// 6) get added length
		const auto added_length = size_string + sizeof(COUNT_T);

		// 7) update [size_]
		this->size_ += added_length;

		// return)
		return base_t(buf_dest, added_length);
#else
		#if defined(__cpp_lib_format)
			//static_assert(false, "include <format> before including 'CGDK.buffer'");
			throw std::exception("include <format> before including 'CGDK.buffer'");
		#else
			//static_assert(false, "'std::format' is not supported");
			throw std::exception("'std::format' is not supported");
		#endif
#endif
	}
	template <class T, std::size_t N, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_format(const T(&_format)[N], TREST&&... _rest)
	{
		return _append_string_format(std::basic_string_view<T>(_format), std::forward<TREST>(_rest)...);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text(std::basic_string_view<T> _string)
	{
		// 1) [문자열]의 길이를 구한다.
		auto size_string = _string.size() * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + size_string) <= this->get_upper_bound());

		// 2) 
		auto buf_pos = this->data_ + this->size_;

		// 2) [문자열]을 복사한다.
		memcpy(buf_pos, _string.data(), size_string);

		// 3) [문자열_길이]만큼 더한다.
		this->size_ += size_string;

		// return) 
		return base_t(buf_pos, size_string);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text_encoding(std::basic_string_view<TY> _string)
	{
		// 1) [문자열]의 길이를 구한다.
		auto size_string = _string.size() * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + size_string) <= this->get_upper_bound());

		// 2) 
		auto buf_pos = this->data_ + this->size_;

		// 3) [문자열]을 복사한다
		if (size_string != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_pos), _string);
		}

		// 4) [문자열_길이]만큼 더한다.
		this->size_ += size_string;

		// return) 
		return base_t(buf_pos, size_string);
	}

	template <class T, std::size_t N>
	constexpr base_t			_append_text(const T(&_text)[N])
	{
		// declare) 
		const auto length_string = std::char_traits<T>::length(_text);
		const auto size_string = length_string * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + size_string) <= this->get_upper_bound());

		// declare)
		auto buf_dest = this->data_ + this->size_;

		// 1) [문자열]을 복사하고 [문자열_길이]만큼 더한다.
		memcpy(buf_dest, _text, size_string);

		// 2) [문자열_길이]만큼 더한다.
		this->size_ += size_string;

		// return) 
		return base_t(buf_dest, size_string);
	}
	template <class T, std::size_t N, class TY>
	constexpr base_t			_append_text_encoding(const TY(&_text)[N])
	{
		// declare) 
		const auto length_string = std::char_traits<T>::length(_text);
		const auto size_string = length_string * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + size_string) <= this->get_upper_bound());

		// declare)
		const auto buf_dest = this->data_ + this->size_;

		// 1) [문자열]을 복사하고 [문자열_길이]만큼 더한다.
		if (size_string != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_dest), _text);
		}

		// 2) [문자열_길이]만큼 더한다.
		this->size_ += size_string;

		// return) 
		return base_t(buf_dest, size_string);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text_sprintf(const T* _format, TREST&&... _rest)
	{
#if defined(FMT_FORMAT_H_) || (defined(__cpp_lib_format) && defined(_FORMAT_))
		//// 1) get max length
		//const std::size_t max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(bound_upper) - reinterpret_cast<const T*>(buf_dest + sizeof(COUNT_T))));

		// 1) get formatted string
		auto temp_buffer = _fmt_format_string(std::basic_string_view<T>(_format), std::forward<TREST>(_rest)...);
		const auto length_string = temp_buffer.size();
		const auto size_string = length_string * sizeof(T);

		// 2) get [dest]
		const auto buf_dest = this->data_ + this->size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + size_string) <= this->get_upper_bound());

		// 5) copy string to buffer
		::memcpy(buf_dest, temp_buffer.data(), size_string);

		// 6) get added length
		const auto added_length = size_string;

		// 7) update [size_]
		this->size_ += added_length;

		// return)
		return base_t(buf_dest, added_length);
#else
		#if defined(__cpp_lib_format)
			//static_assert(false, "include <format> before including 'CGDK.buffer'");
			throw std::exception("include <format> before including 'CGDK.buffer'");
		#else
			//static_assert(false, "'std::format' is not supported");
			throw std::exception("'std::format' is not supported");
		#endif
#endif
	}

#if defined(FMT_FORMAT_H_)
	template <class T, class TFIRST, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
		_append_text_format(const T* _format, TFIRST&& _first, TREST&&... _rest)
	{
		// declare) 
		fmt::basic_memory_buffer<T> temp_buffer;

		// 1) Generate trace Message
		fmt::format_to(temp_buffer, _format, std::forward<TFIRST>(_first), std::forward<TREST>(_rest)...);

		// check)
		if (temp_buffer.size() <= 0)
			return base_t();

		// return) 
		return this->_append_text(std::basic_string_view<T>(temp_buffer.data(), temp_buffer.size()));
	}

#elif defined(__cpp_lib_format) && defined(_FORMAT_)
	#if defined(__GNUC__)
	template <class T, class TFIRST, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
		_append_text_format(const T* _format, TFIRST&& _first, TREST&&... _rest)
	{
		// declare)
		auto buf_dest = this->data_ + this->size_;

		// 1) Generate trace Message
		auto result = std::format_to_n(buf_dest, get_remained_size() - 1, std::_Fmt_string < T, TFIRST, TREST...>(std::forward<const T*>(_format)), std::forward<TFIRST>(_first), std::forward<TREST>(_rest)...);

		// 2) [문자열_길이]를 구한다.
		auto size_string = result.out - buf_dest;

		// 3) [문자열_길이]만큼 더한다.
		this->size_ += size_string;

		// return) 
		return base_t(buf_dest, size_string);
	}
	#else
	template <class TFIRST, class... TREST>
	base_t _append_text_format(const char* _format, TFIRST&& _first, TREST&&... _rest)
	{
		// 1) Generate trace Message
		auto temp_buffer = std::vformat(_format, std::make_format_args(std::forward<TFIRST>(_first), std::forward<TREST>(_rest)...));;

		// check)
		if (temp_buffer.size() <= 0)
			return base_t();

		// return) 
		return this->_append_text(std::string_view(temp_buffer.data(), temp_buffer.size()));
	}
	template <class TFIRST, class... TREST>
	base_t _append_text_format(const wchar_t* _format, TFIRST&& _first, TREST&&... _rest)
	{
		// 1) Generate trace Message
		auto temp_buffer = std::vformat(_format, std::make_wformat_args(std::forward<TFIRST>(_first), std::forward<TREST>(_rest)...));;

		// check)
		if (temp_buffer.size() <= 0)
			return base_t();

		// return) 
		return this->_append_text(std::wstring_view(temp_buffer.data(), temp_buffer.size()));
	}
	#endif
#else
	template <class T, class TFIRST, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
		_append_text_format(const T * _format, TFIRST && _first, TREST&&... _rest)
	{
		#if defined(__cpp_lib_format)
			//static_assert(false, "include <format> before including 'CGDK.buffer'");
			throw std::exception("include <format> before including 'CGDK.buffer'");
		#else
			//static_assert(false, "'std::format' is not supported");
			throw std::exception("'std::format' is not supported");
		#endif
	}
#endif
	constexpr base_t			_append_bytes(std::size_t _size, const void* _buffer)
	{
		// check) _buffer이 nullptr이면 안된다.
		CGDK_ASSERT(_buffer != nullptr || (_buffer == nullptr && _size == 0), throw std::invalid_argument("_buffer is nullptr [1]"));

		// check) upper bound 
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + _size) <= this->get_upper_bound());

		// 1) [원본_버퍼_끝_포인터]를 얻는다.
		const auto buf_dest = this->data_ + this->size_;
	
		// check) _size가 0이면 끝낸다.
		if(_size == 0) return base_t(buf_dest, 0);
	
		// 2) [원본_버퍼_끝_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
		if(_buffer!=nullptr && _buffer != buf_dest)
		{
			memcpy(buf_dest, _buffer, _size);
		}
	
		// 3) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
		this->size_ += _size;
	
		// return) 
		return base_t(buf_dest, _size);
	}
	constexpr self_t			_append_buffer(const base_t& _buffer)
	{
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((this->data_ + this->size_ + sizeof(base_t::size_type) + _buffer.size()) <= this->get_upper_bound());

		// check) _data이 nullptr이면 안된다.
		CGDK_ASSERT(_buffer.data() != nullptr || _buffer.size() == 0, throw std::invalid_argument("_data is nullptr [1]"));

		// 1) [원본_버퍼_포인터]를 저장해 놓는다.
		auto len_old = this->size_;

		// 2) 데이터를 써넣는다.
		if(_buffer.data() != nullptr && _buffer.size() != 0)
		{
			// - [데이터_갯수]를 써넣는다.
			this->_append_general<base_t::size_type>(_buffer.size());

			// - [데이터]들을 통채로 복사한다.
			this->_append_bytes(_buffer.size(), _buffer.data());
		}
		else
		{
			// 2) [데이터_갯수]를 0으로 써넣는다.
			this->_append_general<base_t::size_type>(0);
		}

		// return) 
		return self_t{ base_t{this->data_ + len_old, this->size_ - len_old} };
	}
	template<class T>
	constexpr base_t			_append_tuple(const std::tuple<T>& _tupple)
	{
		auto len_old = this->size_;
		this->_append<std::decay_t<T>>(std::get<0>(_tupple));
		return base_t(this->data_ + len_old, this->size_ - len_old);
	}
	template<class TFIRST, class TSECOND, class... TREST>
	constexpr base_t			_append_tuple(const std::tuple<TFIRST, TSECOND, TREST...>& _tupple)
	{ 
		auto len_old = this->size_;
		this->_append<std::decay_t<TFIRST>>(std::get<0>(_tupple));
		this->_append_tuple<TSECOND, TREST...>((const std::tuple<TSECOND, TREST...>&)_tupple);
		return base_t(this->data_ + len_old, this->size_ - len_old);
	}
	template<class T>
	constexpr void				_append_multi_(T&& _tupple)
	{
		this->_append<std::decay_t<T>>(std::forward<T>(_tupple));
	}
	template<class TFIRST, class TSECOND, class... TREST>
	constexpr void				_append_multi_(TFIRST&& _first, TSECOND&& _second, TREST&&... _rest)
	{ 
		this->_append<std::decay_t<TFIRST>>(_first);
		this->_append_multi_<TSECOND, TREST...>(std::forward<TSECOND>(_second), std::forward<TREST>(_rest)...);
	}
	template<class... T>
	constexpr base_t			_append_multi(T&&... _multi)
	{ 
		auto len_old = size_;
		this->_append_multi_<T...>(std::forward<T>(_multi)...);
		return base_t(data_ + len_old, size_ - len_old);
	}

	template <class T>
	constexpr auto				_append_text_integer(char _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(int8_t _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(uint8_t _value) { return this->_append_text_integer<T>(static_cast<uint64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(int16_t _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(uint16_t _value) { return this->_append_text_integer<T>(static_cast<uint64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(int32_t _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(uint32_t _value) { return this->_append_text_integer<T>(static_cast<uint64_t>(_value));}
#if defined(_MSC_VER)
	template <class T>
	constexpr auto				_append_text_integer(long _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(unsigned long _value) { return this->_append_text_integer<T>(static_cast<uint64_t>(_value));}
#else
	template <class T>
	constexpr auto				_append_text_integer(long long _value) { return this->_append_text_integer<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integer(unsigned long long _value) { return this->_append_text_integer<T>(static_cast<uint64_t>(_value));}
#endif
	template <class T>
	constexpr base_t			_append_text_integer(uint64_t _value)
	{
		// declare) 
		T temp_buf[32];
		auto pos_now = temp_buf;

		// 1) ...
		if (_value != 0)
		{
			while (_value)
			{
				*(pos_now++) = _value % 10 + '0';
				_value /= 10;
			}
		}
		else
		{
			*(pos_now++) = '0';
		}

		// 2) copy
		auto buf_dest = this->data_ + this->size_;

		// declare)
		base_t result(buf_dest, (pos_now - temp_buf) * sizeof(T));

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + result.size()) <= this->get_upper_bound());

		// 3) reverse copy
		for (--pos_now; pos_now >= temp_buf; ++buf_dest, --pos_now)
		{
			*buf_dest = *pos_now;
		}

		// 4) set size_
		this->size_ += result.size() * sizeof(T);

		// return) 
		return result;
	}
	template <class T>
	constexpr base_t			_append_text_integer(int64_t _value)
	{
		// declare) 
		T temp_buf[32];
		auto pos_now = temp_buf;

		// 1-1) positive value
		if (_value > 0)
		{
			do
			{
				*(pos_now++) = _value % 10 + '0';
				_value /= 10;
			} while (_value);
		}
		// 1-2) zeroS
		else if (_value == 0)
		{
			*(pos_now++) = '0';
		}
		// 1-3) negative value
		else
		{
			// - get 2's completment
			_value = ~_value + 1;

			// - convert to string
			do
			{
				*(pos_now++) = _value % 10 + '0';
				_value /= 10;
			} while (_value);

			// - append '-'
			*(pos_now++) = '-';
		}

		// 2) copy
		auto buf_dest = this->data_ + this->size_;

		// declare)
		base_t result(buf_dest, (pos_now - temp_buf) * sizeof(T));

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + result.size()) <= this->get_upper_bound());

		// 3) reverse copy
		for (--pos_now; pos_now >= temp_buf; ++buf_dest, --pos_now)
		{
			*buf_dest = *pos_now;
		}

		// 4) set size_
		this->size_ += result.size() * sizeof(T);

		// return) 
		return result;
	}
	template <class T>
	constexpr base_t			_append_text_float(double _value)
	{
		auto temp = _float_to_string<T>(_value);
		return _append_text(static_cast<std::basic_string_view<T>>(temp));
	}

	template <class T = char>
	constexpr base_t			_append_text_binary(const char* _buffer, std::size_t _length)
	{
		// check) _buffer이 nullptr이면 안된다.
		CGDK_ASSERT(_buffer != nullptr || (_buffer == nullptr && _length == 0), throw std::invalid_argument("_buffer is nullptr [1]"));

		// 1) calculate size to write
		auto size_added = _length * sizeof(T) * 2;

		// check) upper bound 
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + size_added) <= this->get_upper_bound());

		// 1) [원본_버퍼_끝_포인터]를 얻는다.
		auto buf_dest = reinterpret_cast<T*>(this->data_ + this->size_);
	
		// check) _length가 0이면 끝낸다.
		if(_length == 0) return base_t(buf_dest, 0);
	
		// 2) [원본_버퍼_끝_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
		auto buf_src = reinterpret_cast<const uint8_t*>(_buffer);
		auto buf_src_end = buf_src + _length;

		while(buf_src != buf_src_end)
		{
			auto temp = *buf_src++;
			*buf_dest++ = __hex_to_ascii(temp >> 4);
			*buf_dest++ = __hex_to_ascii(temp & 0x0f);
		}
	
		// 3) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
		this->size_ += size_added;
	
		// return) 
		return base_t(buf_dest, size_added);
	}

	template<class T>
	constexpr base_t			_append_container_associative(const T& _container)
	{
		// !주의) value-key 순으로 append해야 한다.

		// 1) store data_
		auto l = size_;

		// 2) [데이터_갯수]를 써넣는다.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [데이터]들을 써넣는다.
		for (auto iter = _container.begin(); iter != _container.end(); ++iter)
		{
			// _ key를 써넣는다.
			this->_append<typename T::key_type>(iter->first);
			// - Value를 써넣는다.
			this->_append<typename T::mapped_type>(iter->second);
		}

		// return) 
		return base_t(this->data_ + l, this->size_ - l);
	}
	template<class T>
	constexpr base_t			_prepend_container_associative(const T& _container)
	{
		// 주의) extract시 value->key순으로 extract되므로 prepaend시에는 key->value순으로 prepend해줘야 한다.

		// declare) 
		auto p = this->data_;

		// 1) Begin/End Iterator
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		// 2) [데이터]들을 써넣는다.
		for(; iter!=iterEnd; ++iter)
		{
			// - Value를 써넣는다.
			this->_prepend<typename T::mapped_type>(iter->second);
			// _ key를 써넣는다.
			this->_prepend<typename T::key_type>(iter->first);
		}

		// 3) [데이터_갯수]를 써넣는다.
		this->_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return base_t(this->data_, p - this->data_);
	}

	template<class I>
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								_append_iterator(I _first, I _last)
	{
		// 1) store data_
		auto l = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		auto buf_count = _append_skip(sizeof(COUNT_T));

		// declare)
		COUNT_T iter_count = 0;

		// 3) [데이터]들을 써넣는다.
		for (; _first != _last; ++_first, ++iter_count)
		{
			_append<typename I::value_type>(*_first);
		}

		// 4) 예약해 놓은 위치에 갯수를 써넣는다.
		buf_count.template front<COUNT_T>() = iter_count;

		// return) 
		return base_t(this->data_ + l, this->size_ - l);
	}
	template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, base_t>
								_append_container_array(const T& _container)
	{
		// 1) [원본_버퍼_길이]을 얻어놓는다.
		auto l = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [데이터]들을 써넣는다.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			this->_append<typename T::value_type>(*iter);
		}

		// return)
		return base_t(this->data_ + l, this->size_ - l);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, base_t>
								_append_container_array(const T& _container)
	{
		// 1) [원본_버퍼_길이]을 얻어놓는다.
		auto l = this->size_;

		// declare)
		auto count = _container.size();

		// 1) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(count));

		// 3) [데이터]들을 써넣는다.
		if (count != 0)
		{
			this->_append_bytes(count * sizeof(typename T::value_type), &_container.front());
		}

		// return)
		return base_t(this->data_ + l, this->size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_own_ptr_list(const T& _container)
	{
		// 1) [원본_버퍼_길이]을 얻어놓는다.
		auto l = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [데이터]들을 써넣는다.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			if(iter->empty()==false)
			{
				this->_append<typename T::value_type>(*iter);
			}
			else
			{
				this->_append<COUNT_T>(COUNT_T(0)-1);
			}
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_object_ptr_list(const T& _container)
	{
		// 1) [원본_버퍼_길이]을 얻어놓는다.
		auto l = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [데이터]들을 써넣는다.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			if(iter->empty()==false)
			{
				this->_append<typename T::value_type>(*iter);
			}
			else
			{
				this->_append<COUNT_T>(COUNT_T(0)-1);
			}
		}

		// return)
		return base_t(this->data_ + l, this->size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_list(const T& _container)
	{
		// 1) [원본_버퍼_길이]을 얻어놓는다.
		auto l = this->size_;

		// 2) [데이터_갯수]를 써넣는다.
		this->_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [데이터]들을 써넣는다.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for(; iter!=iterEnd; ++iter)
		{
			this->_append<typename T::value_type>(*iter);
		}

		// return)
		return base_t(this->data_ + l, this->size_ - l);
	}
	template <class T>
	constexpr base_t			_prepend_container_list(const T& _container)
	{
		// declare) 
		auto p = this->data_;

		// 1) Begin/End Iterator
		auto iter = _container.rbegin();
		auto iter_end = _container.rend();

		// 2) [데이터]들을 써넣는다.
		for(; iter != iter_end; ++iter)
		{
			this->_prepend<typename T::value_type>(*iter);
		}

		// 3) [데이터_갯수]를 써넣는다.
		this->_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return base_t(this->data_, p - this->data_);
	}

public:
	// 10) begin/end)
	constexpr self_t			_begin(int _offset) const noexcept { return self_t(this->base_t::_begin(_offset), bound);}
	constexpr self_t			_end(int _offset) const noexcept { return self_t(this->base_t::_end(_offset), bound);}

	// 11) append/extarct
	constexpr self_t			_extract_buffer();

	constexpr bool				_is_buffer_overflow() const
								{
									// check) 
									if(this->get_upper_bound() == nullptr)
										return false;

									// check) Check Lower Bound
									if(this->data_ > this->get_lower_bound())
										return false;

									// check) Check Upper Bound
									if((this->data_ + this->size_) <= this->get_upper_bound())
										return false;

									// return) Success!
									return true;
								}

	constexpr const void*		get_lower_bound() const noexcept { return bound.lower;}
	constexpr const void*		get_upper_bound() const noexcept { return bound.upper;}
protected:
	constexpr void				_set_bound(const buffer_bound&  _bound) { bound = _bound;}

	constexpr void				_check_bound(const _buffer_view<char>& _rhs) const
								{
									// check) 
									CGDK_ASSERT(_rhs.get_front_ptr() >= this->get_lower_bound());

									// check) 
									if(_rhs.get_front_ptr() < this->get_lower_bound())
										throw std::length_error("buffer overflow. out of lower bound'");

									// check) 
									CGDK_ASSERT(_rhs.get_back_ptr() <= this->get_upper_bound());

									// check) 
									if (_rhs.get_back_ptr() > this->get_upper_bound())
										throw std::length_error("buffer overflow. out of upper bound'");
								}
	// 11) source
			buffer_bound		bound;
};

template <class U>
constexpr CGDK::_basic_buffer<U> operator ^ (const CGDK::_basic_buffer<U>& _lhs, std::size_t _size)
{
	return CGDK::_basic_buffer<U>{ ((const CGDK::_buffer_view<U>&)_lhs) ^ _size, _lhs.get_bound() };
}

template <class U>
constexpr CGDK::_basic_buffer<U> operator ^ (const CGDK::_basic_buffer<U>& _lhs, CGDK::_buffer_view<U> _buffer)
{
	return CGDK::_basic_buffer<U>{ _buffer, _lhs.get_bound() };
}


template <class T, class V, std::size_t N>
constexpr _basic_buffer<T> to_basic_buffer(V(&_memory)[N])
{
	return _basic_buffer<T>{ typename _basic_buffer<T>::base_t{ _memory, 0 }, buffer_bound{ _memory, _memory + N }};
}

template <class T, class V, std::size_t N>
constexpr _basic_buffer<T> to_basic_buffer(T(&_memory)[N], std::size_t _size)
{
	return _basic_buffer<T>{ typename _basic_buffer<T>::base_t{ _memory, _size }, buffer_bound{ _memory, _memory + N }};
}

template <class T, class V>
constexpr _basic_buffer<T> to_basic_buffer(std::basic_string_view<V> _string)
{
	return _basic_buffer<T>{ typename _basic_buffer<T>::base_t{ reinterpret_cast<T*>(const_cast<V*>(_string.data())), (_string.size() * sizeof(V)) / sizeof(T) }};
}


}

#include "cgdk/buffers/_basic_buffer.inl"