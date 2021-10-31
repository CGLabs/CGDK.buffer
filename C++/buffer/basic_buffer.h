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
// CGDK::basic_buffer
//
//-----------------------------------------------------------------------------
template <class ELEM_T>
class _basic_buffer : public _buffer_view<char>
{
// traits) 
public:
			using base_t	  = _buffer_view<char>;
			using self_t	  = _basic_buffer<ELEM_T>;
			using traits	  = typename base_t::traits;
			using element_t	  = typename base_t::element_t;
			using size_type	  = typename base_t::size_type;

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
	constexpr _basic_buffer(_buffer_view<T> _buffer, const buffer_bound& _bound) noexcept : base_t(_buffer), bound(_bound) {}
	template <class T>
	constexpr _basic_buffer(_buffer_view<T> _buffer, buffer_bound&& _bound) noexcept : base_t(_buffer), bound(_bound) {}
	template <class T>
	constexpr _basic_buffer(std::basic_string_view<T> _string) noexcept : base_t{ _string }, bound{ _string.data(), _string.data() + _string.size() } {}
	template <class T, std::size_t N>
	constexpr _basic_buffer(T(&_memory)[N]) noexcept : base_t{ _memory }, bound{ _memory, _memory + N } {}

protected:
#if defined(CGDK_SYSTEM_OBJECT)
	constexpr _basic_buffer(Imemory* _pbuffer) noexcept : base_t((_pbuffer != nullptr) ? *_pbuffer : base_t()), bound((_pbuffer != nullptr) ? _pbuffer->get_bound() : buffer_bound()) {}
	constexpr _basic_buffer(object_ptr<Imemory>&& _pbuffer) noexcept : base_t((_pbuffer.exist()) ? *_pbuffer : base_t()), bound((_pbuffer.exist()) ? _pbuffer->get_bound() : buffer_bound()) {}
#endif

public:
	// 1) capacity/clear/copy/clone
	constexpr void				resize(std::size_t _new_size)													{ if (data() + _new_size > get_upper_bound()) throw std::length_error("buffer overflow. out of upper bound 'resize(size_t)'"); size_ = _new_size;}
			std::size_t			capacity() const noexcept														{ return (bound.upper != nullptr) ? (reinterpret_cast<const char*>(bound.upper) - data_) : 0;}
	constexpr void				clear() noexcept																{ base_t::clear(); bound.reset();}
			void				copy(const base_t& _source)														{ if (data_ + _source.size() > get_upper_bound()) throw std::length_error("buffer overflow. out of upper bound 'copy(_source)'"); memcpy(data(), _source.data(), _source.size()); size_ = _source.size();}
	constexpr void				swap(_basic_buffer& _rhs) noexcept												{ base_t::swap(_rhs); auto p = _rhs.get_bound(); _rhs._set_bound(bound); bound = p; }
	constexpr void				swap(base_t& _rhs)																{ if (_rhs.data() < get_lower_bound() || (_rhs.data() + _rhs.size()) > get_upper_bound()) { assert(false); throw std::out_of_range("_rhs data_ is must in bound of this shared_buffer"); } base_t::swap(_rhs); }

#if defined(FMT_FORMAT_H_)
	template<class T>
	constexpr fmt_buffer<T>		to_fmt_remained_buffer() noexcept												{ return fmt_buffer(data<T>() + size(), 0, this->get_remained_size()); }
#endif
			//shared_buffer		clone(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) const;
			self_t				split_head(const base_t& _source)
			{
				_CGD_BUFFER_BOUND_CHECK(size_ >= _source.size());
				char* p = data();
				memcpy(data(), _source.data(), _source.size());
				data_+= _source.size();
				size_-=_source.size();
				return self_t{ buffer_view{p, _source.size()}, bound };
			}
			self_t				split_tail(const base_t& _source)
			{
				_CGD_BUFFER_BOUND_CHECK(size_ >= _source.size());
				memcpy(data() + size_ - _source.size(), _source.data(), _source.size());
				size_ -= _source.size();
				return self_t{ buffer_view{data() + size(), _source.size()}, bound };
			}

	// 2) prepend																								  
			template <std::size_t ISIZE>
	constexpr auto				prepend()																		{ return _prepend_skip(ISIZE);}
			template <class T>																					  
	constexpr T&				prepend()																		{ return *reinterpret_cast<T*>(_prepend_skip(sizeof(T)));}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(const T& _data)															{ return PRPD_t<self_t, T>::_do_prepend(*this, _data);;}
			template <class T>																					  
	constexpr prpd_tr<T>		prepend(T&& _data)																{ return PRPD_t<self_t, T>::_do_prepend(*this, _data);;}
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
								prepend_string(const std::basic_string_view<T> _format, F&& _first, TREST&&... _rest) { return _prepend_string_format(_format.data(), std::forward<F>(_first), std::forward<TREST>(_rest)...);}
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
	constexpr appd_tr<T>		append(const T& _data)															{ return APPD_t<self_t,T>::_do_append(*this, _data); }
			template <class T>																					  
	constexpr appd_tr<T>		append(T&& _data)																{ return APPD_t<self_t,T>::_do_append(*this, std::forward<T>(_data)); }
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

	// 4) extract/subtract
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract()																		{ return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest)															{ base_t::template extract_to<T>(_dest);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract()																		{ return base_t::template extract<T>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract_to(T& _dest)															{ base_t::template extract_to<T>(_dest);}
			template <std::size_t ISIZE>
	constexpr auto				extract()																		{ return self_t(base_t::extract(CGDK::size(ISIZE)), bound);}
	constexpr auto				extract(CGDK::size _length)														{ return self_t(base_t::extract(_length), bound);}
	constexpr auto				extract(CGDK::skip _length)														{ return self_t(base_t::extract(_length), bound);}

	// 5) reference
			template <class T = char>
	constexpr void				set_front_ptr(T* _pos)															{ _CGD_BUFFER_BOUND_CHECK(_pos >= get_lower_bound() && _pos <= this->get_back_ptr<T>()); auto temp_offset = reinterpret_cast<char*>(_pos) - this->data_; this->data_ = reinterpret_cast<char*>(_pos); this->size_ -= temp_offset;  }
			template <class T = char>
	constexpr void				set_back_ptr(T* _pos)															{ _CGD_BUFFER_BOUND_CHECK(_pos >= this->get_front_ptr<T>() && _pos <= get_upper_bound()); this->size_ = reinterpret_cast<char*>(_pos) - this->data_; }
	constexpr const buffer_bound& get_bound() const noexcept													{ return bound;}
	constexpr std::size_t		get_remained_size() const noexcept												{ return static_cast<const char*>(bound.upper) - data_ - size_;}

	// 6) operator overloading																					  
			// [operator] +/-		
	constexpr self_t			operator ~ () const																{ auto data_value = data_ + size_; return self_t{ base_t { data_value, static_cast<size_type>(static_cast<const element_t*>(bound.upper) - data_value) }, bound }; }
	constexpr self_t			operator+(offset _rhs) const													{ return self_t{ base_t::operator+(_rhs), bound };}
	constexpr self_t			operator-(offset _rhs) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ - _rhs.amount >= get_lower_bound());

				// return) 
				return self_t(base_t{ this->data_ - _rhs.amount, this->size_ + _rhs.amount }, bound);
			}
	constexpr self_t			operator+(CGDK::size _rhs) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ + this->size_ + _rhs.amount <= get_upper_bound());

				// return) 
				return self_t(base_t{ this->data_, this->size_ + _rhs.amount }, bound);
			}
	constexpr self_t			operator-(CGDK::size _rhs) const												{ return self_t{ base_t::operator-(_rhs), bound }; }
			// [operator] +=/-=
	constexpr self_t&			operator+=(offset _rhs)															{ base_t::operator+=(_rhs); return *this; }
	constexpr self_t&			operator-=(offset _rhs)
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ - _rhs.amount >= get_lower_bound());

				this->data_ -= _rhs.amount;
				this->size_ += _rhs.amount;
				
				return *this;
			}
	constexpr self_t			operator+=(CGDK::size _rhs)
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(this->data_ + this->size_ + _rhs.amount <= get_upper_bound());

				// - add
				this->size_ += _rhs.amount;

				// return) 
				return *this;
			}
	constexpr self_t			operator-=(CGDK::size _rhs)														{ base_t::operator-=(_rhs); return *this; }
	constexpr self_t&			operator+=(const base_t& _rhs)													{ _append_bytes(_rhs.size(), _rhs.data()); return *this;}
	constexpr self_t&			operator+=(base_t&& _rhs)														{ _append_bytes(_rhs.size(), _rhs.data()); return *this;}
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator+=(const T& _rhs)														{ for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size_, iter.data()); } return *this; }
			template <class T>
	constexpr std::enable_if_t<is_linear_container_with_buffer<T>::value, self_t&>
								operator+=(T&& _rhs)															{ for (auto& iter : _rhs) { if (iter.empty()) continue; _append_bytes(iter.size_, iter.data()); } return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(const std::array<T, N>& _rhs)										{ for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size_, iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(std::array<T, N>&& _rhs)												{ for(auto& iter: _rhs) { if (iter.empty()) continue; _append_bytes(iter.size_, iter.data());} return *this; }
			template <class T, std::size_t N>
	constexpr std::enable_if_t<std::is_base_of_v<base_t, T>, self_t&>
								operator+=(const base_t(&_rhs)[N] )												{ const T* iter = _rhs; const T* iter_end = _rhs + N; for(;iter != iter_end; ++iter) { if (iter->empty()) continue; _append_bytes(iter->size_, iter->data_); } return *this;	}
	constexpr self_t&			operator+=(const self_t& _rhs)													{ _append_bytes(_rhs.size_, _rhs.data()); return *this;}
	constexpr self_t&			operator+=(self_t&& _rhs)														{ _append_bytes(_rhs.size_, _rhs.data()); return *this;}
			// [operator] =
	constexpr self_t&			operator= (const base_t& _rhs) noexcept											{ _check_bound(_rhs); base_t::operator=(_rhs); return *this; }
	constexpr self_t&			operator= (base_t&& _rhs) noexcept												{ _check_bound(_rhs); base_t::operator=(_rhs); return *this; }
	constexpr self_t&			operator= (const self_t& _rhs) noexcept											{ base_t::operator=(_rhs); bound = _rhs.bound; return *this; }
	constexpr self_t&			operator= (self_t&& _rhs) noexcept												{ base_t::operator=(_rhs); bound = _rhs.bound; return *this; }
#if defined(CGDK_SYSTEM_OBJECT)
	constexpr self_t&			operator= (Imemory* _rhs) noexcept												{ if(_rhs != nullptr) { base_t::operator=(_rhs); bound = _rhs->get_bound(); } else { clear();} return *this; }
	constexpr self_t&			operator= (const object_ptr<Imemory>& _rhs) noexcept							{ if(_rhs.exist()) { base_t::operator=(_rhs); bound = _rhs->get_bound(); } else { clear();} return *this; }
	constexpr self_t&			operator= (object_ptr<Imemory>&& _rhs) noexcept									{ if(_rhs.exist()) { base_t::operator=(_rhs); bound = _rhs->get_bound(); } else { clear();} return *this; }
#endif
			// [operator] ^=
			template<class T>
	constexpr self_t&			operator^=(const _buffer_view<T>& _rhs)											{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(_buffer_view<T>&& _rhs)												{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(const buffer_base<T>& _rhs)											{ base_t::operator=(_rhs); return *this;}
			template<class T>
	constexpr self_t&			operator^=(buffer_base<T>&& _rhs)												{ base_t::operator=(_rhs); return *this;}
	constexpr self_t&			operator^=(std::size_t _rhs)													{ base_t::set_size(_rhs); return *this;}
			// [operator >> - extract
			template <class T>
			self_t&				operator>>(T& _rhs)																{ _rhs = _extract<T>(); return *this;}
			// [operator] << - append																			  
			template <class T>																					  
			self_t&				operator<<(const T& _rhs)														{ APPD_t<self_t, T>::_do_append(*this, _rhs); return *this;}

public:
	// prepend) 
	template <class T>
	constexpr prpd_tr<T>		_prepend(const T& _data) { return PRPD_t<self_t,T>::_do_prepend(*this, _data);}
	template <class T>
	constexpr prpd_tr<T>		_prepend(T&& _data) { return PRPD_t<self_t,T>::_do_prepend(*this, _data); }
			//template <class T, std::size_t N>
			//typename serializer_prepend< std::remove_const_t<T>>::type _prepend(const T(&_data)[N]) { return serializer_prepend<typename std::remove_const_t<T>[N]>::_do_prepend(*this, _data);}
	constexpr base_t			_prepend_skip(std::size_t _size)
			{
				// check) lower bound
				_CGD_BUFFER_BOUND_CHECK((data_ - _size) >= get_lower_bound());

				// 1) [����_����_������]�� _size��ŭ ���δ�.
				data_ -= _size;

				// 2) [����_����_����]�� _size��ŭ �ø���. 
				size_ += _size;

				// return) 
				return base_t(data_, _size);
			}

	template <class T>
	constexpr T&				_prepend_general(const T& _data)
	{
		//// check) T must basic type
		//static_assert(is_general_serializable_v<T>, "T is not basic type, so it may not work properly. use ENABLE_STRUCT_SERIALIZABLE");

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - sizeof(T)) >= get_lower_bound());

		// 1) [����_����]�� ���� ������ �ִ´�.
		*reinterpret_cast<T*>(data() - sizeof(T)) = _data;
	
		// 2) [����_����_������]�� ũ�⸦ sizeof(T)��ŭ ���δ�.
		data_ -= sizeof(T);
	
		// 3) [����_����_����]�� sizeof(T)��ŭ �ø���. 
		size_ += sizeof(T);
	
		// return) 
		return *reinterpret_cast<T*>(data());
	}
	template <class T> 
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_prepend_array(const T* _data, std::size_t _count)
	{
		// check) _count�� 0���ϸ� �ȵȴ�.
		CGDK_ASSERT(_count >= 0, throw std::invalid_argument("_count is invalid [0]"));

		// 1)
		auto buf_old = data_;

		// 2) [������_����]��ŭ �����͵��� ��ä�� �����Ѵ�.
		_prepend_bytes(sizeof(T)*_count, _data);

		// 3) [������_����]�� ��ִ´�.
		_prepend<COUNT_T>(static_cast<COUNT_T>(_count));

		// return) 
		return base_t(data_, buf_old - data_);
	}
	template <class T> 
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_prepend_array(const T* _data, std::size_t _count)
	{
		// check) _count�� 0���ϸ� �ȵȴ�.
		CGDK_ASSERT(_count >= 0, throw std::invalid_argument("_count is invalid [0]"));

		// 1)
		auto buf_old = data_;

		// 2) [������_����]��ŭ �����͵��� �߰��Ѵ�.
		for(int i=static_cast<int>(_count-1);i>=0;--i)
		{
			_prepend<T>(_data[i]);
		}

		// 3) [������_����]�� ��ִ´�.
		_prepend<COUNT_T>(static_cast<COUNT_T>(_count));

		// return) 
		return base_t(data_, buf_old - data_);
	}
	template <class T, std::size_t N>
	constexpr base_t			_prepend_string(const T(&_string)[N])
	{
		// 1) calculate string size ( string + NULL )
		constexpr auto lengh_string = std::char_traits<T>::length(_string) + 1;
		constexpr auto bytes_copy = lengh_string * sizeof(T);
		constexpr auto added_length = sizeof(COUNT_T) + bytes_copy;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - added_length) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		auto p = data_ - bytes_copy;

		// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		memcpy(p, _string, bytes_copy);

		// 4) �̵�
		p -= sizeof(COUNT_T);

		// 4) [���ڿ� ����]�� ��ִ´�.
		*reinterpret_cast<COUNT_T*>(p) = bytes_copy;

		// 5) [����_����_������]�� [����_����_����]�� �ű��.
		data_  = p;
		size_ += added_length;

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
		_CGD_BUFFER_BOUND_CHECK((data_ - added_length) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		auto p = data_ - bytes_copy;

		// 3) ���ڿ��� ��ȯ�Ѵ�.
		if (bytes_copy != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) �̵�
		p -= sizeof(COUNT_T);

		// 4) [���ڿ� ����]�� ��ִ´�.
		*reinterpret_cast<COUNT_T*>(p) = bytes_copy;

		// 5) [����_����_������]�� [����_����_����]�� �ű��.
		data_  = p;
		size_ += added_length;
				
		// return) 
		return base_t(p, added_length);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string_format(const T* _format, TREST&&... _rest)
	{
		// check) _format�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_format != nullptr, throw std::invalid_argument("_format is nullptr [0]"));

		// 1) store data_
		auto buf_old = data_;

		// 2) get lower bound
		auto bound_lower = get_lower_bound();

		// 3) get max length
		std::size_t	max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(data_ - sizeof(COUNT_T)) - reinterpret_cast<const T*>(bound_lower)));

		// 4) [�ӽ�_����]�� �Ҵ��Ѵ�
	#if defined(CGDK_SYSTEM_OBJECT)
		const auto pbuf_temp = mem_alloc(max_length * sizeof(T));
		const auto str_start = reinterpret_cast<T*>(pbuf_temp->data_);
	#else
		const auto pbuf_temp = ::malloc(max_length * sizeof(T));
		const auto str_start = reinterpret_cast<T*>(pbuf_temp);
	#endif

		// 5) [����_����_����_ũ��]�� [����_���ڿ�]�� ��ִ´�.
		const auto length_string = CGDK::_Xsprintf(str_start, max_length, _format, std::forward<TREST>(_rest)...) + 1;
		const auto size_string = length_string * sizeof(T);

		// 6) [��ǥ_������]�� ���Ѵ�.
		auto p = data_ - size_string;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((p - sizeof(COUNT_T)) >= get_lower_bound());
	
		// 7) [���ڿ�]�� �����Ѵ�.
		memcpy(p, str_start, size_string);

	#if !defined(CGDK_SYSTEM_OBJECT)
		::free(pbuf_temp);
	#endif

		// 8) [��ǥ_������]�� sizeof(COUNT_T)��ŭ�� ����.
		p -= sizeof(COUNT_T);

		// 9) [���ڿ�_����]�� ��ִ´�.
		*reinterpret_cast<COUNT_T*>(p) = static_cast<COUNT_T>(length_string);

		// 10)[����_����_������]�� ������Ʈ�Ѵ�.
		data_ = p;
		size_ += size_string + sizeof(COUNT_T);

		// return) 
		return base_t(data_, buf_old - data_);
	}
	template <class T>
	constexpr base_t			_prepend_text(std::string_view _string)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_string!=nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [���ڿ�_����]�� ���Ѵ�.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		T* p = data_-size_string;
	
		// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		if(p!=_string)
		{
			memcpy(p, _string, size_string);
		}

		// 4) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string;

		// return) 
		return base_t(p, size_string);
	}
	template <class T, class TY>
	constexpr base_t			_prepend_text_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_string!=nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [���ڿ�_����]�� ���Ѵ�.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		T* p = data_ - size_string;
	
		// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		if(size_string != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string;

		// return) 
		return base_t(p, size_string);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text_format(const T* _format, TREST&&... _rest)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_format!=nullptr, throw std::invalid_argument("_format is nullptr! [0]"));

		// declare)
		constexpr std::size_t TEMP_STRING_BUFFER_SIZE = 2048;

		// 1) [�ӽ�_����]�� �Ҵ��Ѵ�
	#if defined(CGDK_SYSTEM_OBJECT)
		auto pbuf_temp = mem_alloc(TEMP_STRING_BUFFER_SIZE);
		auto str_start = reinterpret_cast<T*>(pbuf_temp->data_);
	#else
		auto pbuf_temp = ::malloc(TEMP_STRING_BUFFER_SIZE);
		auto str_start = reinterpret_cast<T*>(pbuf_temp);
	#endif

		// 3) get lower bound
		auto bound_lower = get_lower_bound();

		// 4) get max length
		std::size_t	max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(data_ - sizeof(COUNT_T)) - reinterpret_cast<const T*>(bound_lower)));

		// 5) [����_����_����_ũ��]�� [����_���ڿ�]�� ��ִ´�.
		const auto length_string = _Xsprintf(str_start, max_length, std::forward<TREST>(_rest)...);
		const auto size_string = length_string * sizeof(T);

		// 6) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		auto p = data_ - size_string;

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK(p >= get_lower_bound());

		// 7) [���ڿ�]�� �߰��Ѵ�.
		memcpy(p, str_start, size_string);

	#if !defined(CGDK_SYSTEM_OBJECT)
		::free(pbuf_temp);
	#endif

		// 9) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string;

		// return) 
		return base_t(p, size_string);
	}
	constexpr base_t			_prepend_bytes(std::size_t _size, const void* _buffer)
	{
		// check) _buffer�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_buffer != nullptr, throw std::invalid_argument("_buffer is nullptr [1]"));

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_-_size) >= get_lower_bound());

		// 1) store data_
		auto buf_old = data_;

		// 2) [����_����_������]�� ũ�⸦ _size��ŭ ���δ�.
		auto p = data() -_size;
	
		// check) _size�� 0�̸� ������.
		if(_size == 0) return base_t(p,0);

		// 3) [����_����_������]�� [������]�� [������_ũ��]��ŭ �����Ѵ�.
		if(_buffer != nullptr && _buffer!=p)
		{
			memcpy(p, _buffer, _size);
		}

		// 4) [����_����_������]�� �����Ѵ�.
		data_  = p;

		// 5) [����_����_����]�� _size��ŭ �ø���. 
		size_ += _size;

		// return) 
		return base_t(data_, buf_old - data_);
	}
	constexpr self_t			_prepend_buffer(const base_t& _buffer)
	{
		// 1) store data_
		auto buf_old = data_;

		// 1) [������_����]��ŭ �����͵��� ��ä�� �����Ѵ�.
		_prepend_bytes(_buffer.size(), _buffer.data());

		// 2) [������_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_buffer.size()));

		// return) 
		return self_t{ base_t{ data_, static_cast<size_type>(buf_old - data_) } };
	}
	template <class T>
	constexpr base_t			_prepend_initializer_list(const std::initializer_list<T>& _list)
	{
		auto p = data_;

		for(auto& iter:_list)
		{
			_prepend<T>(iter);
		}
		
		return base_t(p, data_ - p);
	}
	template <class T>
	constexpr base_t			_prepend_tuple(const std::tuple<T>& _data)
	{
		auto p = data_;
		_prepend<T>(std::get<0>(_data)); 
		return base_t(data_, p - data_);
	}
	template <class TFIRST, class TSECOND, class... TREST>
	constexpr base_t			_prepend_tuple(const std::tuple<TFIRST, TSECOND, TREST...>& _tupple)
	{
		auto p = data_;
		_prepend_tuple((const std::tuple<TSECOND, TREST...>&)_tupple); _prepend<TFIRST>(std::get<0>(_tupple));
		return base_t(data_, p - data_);
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
		auto p = data_;
		_prepend_multi_<T...>(std::forward<T>(_multi)...);
		return base_t(data_, p - data_);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string(std::basic_string_view<T> _string)
	{
		// 1) ...
		const auto buf_old = data_;

		// 2) String���̸� ���Ѵ�.(NULL���̱��� �����ϹǷ� +1�Ѵ�.)
		const auto length_string = _string.length();
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string - sizeof(COUNT_T)) >= get_lower_bound());

		// 3) NULL���� ���� ���� �ִ´�.
		_prepend_general<T>(0);

		// 4) [���ڿ�]�� [���ڿ�_����]��ŭ �����Ѵ�.
		_prepend_bytes(size_string, _string.data());

		// 5) [���ڿ�_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(length_string + 1));

		// return) String�� ���� ó�� ��ġ�� ������!!
		return	base_t(data_, buf_old - data_);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_string_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [���ڿ�_����]�� ���Ѵ�.
		const auto length_string = _string.length();
		const auto size_string = (length_string + 1) * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string - sizeof(COUNT_T)) >= get_lower_bound());

		// 2) ...
		T* p = reinterpret_cast<T*>(data_ - sizeof(T));

		// 3) append NULL
		*reinterpret_cast<COUNT_T*>(p) = 0;

		// 4) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		p -= length_string;

		// 5) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		if (length_string != 0 && p != _string.data())
		{
			encode_string(p, _string);
		}

		// 6) [���ڿ� ����]�� ��ִ´�.
		*reinterpret_cast<COUNT_T*>(reinterpret_cast<char*>(p) - sizeof(COUNT_T)) = length_string + 1;

		// 4) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string + sizeof(COUNT_T);

		// return) String�� ���� ó�� ��ġ�� ������!!
		return	base_t(data_, size_string + sizeof(COUNT_T));
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text(std::basic_string_view<T> _string)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [���ڿ�_����]�� ���Ѵ�.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		auto p = data() - size_string;

		// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		if (p != _string)
		{
			memcpy(p, _string, size_string);
		}

		// 4) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string;

		// return) 
		return	base_t(p, p - data_);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_prepend_text_encoding(std::basic_string_view<TY> _string)
	{
		// check) _string�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [0]"));

		// 1) [���ڿ�_����]�� ���Ѵ�.
		const auto length_string = std::char_traits<T>::length(_string);
		const auto size_string = length_string * sizeof(T);

		// check) lower bound
		_CGD_BUFFER_BOUND_CHECK((data_ - size_string) >= get_lower_bound());

		// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
		auto p = data() - size_string;

		// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
		if (size_string != 0 && p != _string)
		{
			encode_string(reinterpret_cast<T*>(p), _string);
		}

		// 4) [����_����_������]�� [����_����_����]�� �ű��.
		data_ = p;
		size_ += size_string;

		// return) 
		return	base_t(p, p - data_);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, base_t>
								_prepend_container_array(const T& _container)
	{
		// 1) store data_
		auto p = data();

		// 2) [������]���� �ٷ� memcopy�Ѵ�.
		_prepend_bytes(_container.size() * sizeof(typename T::value_type), &_container.front());

		// 3) [������_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return	base_t(data_, p-data_);
	}
	template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, base_t>
								_prepend_container_array(const T& _container)
	{
		// 1) store data_
		auto p = data();

		// 2) Begin/End Iterator
		auto iter = _container.rbegin();
		auto iter_end = _container.rend();

		// 3) [������]���� ��ִ´�.
		for (; iter != iter_end; ++iter)
		{
			_prepend<typename T::value_type>(*iter);
		}

		// 4) [������_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return	base_t(data_, p - data_);
	}
	template<class RI>
	constexpr std::enable_if_t<is_iterator<RI>::value, base_t>
								_prepend_iterator(RI _reverse_first, RI _reverse_last)
	{
		// 1) store data_
		auto p = data();

		// declare)
		COUNT_T iter_count = 0;

		// 1) �����͵��� �����Ѵ�.
		for (; _reverse_first != _reverse_last; ++_reverse_first, ++iter_count)
		{
			_prepend<typename RI::value_type>(*_reverse_first);
		}

		// 2) ũ�⸦ ����� ��ġ ����
		_prepend_general<COUNT_T>(iter_count);

		// return) 
		return base_t(data_, p - data_);
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
		return APPD_t<self_t,T>::_do_append(*this, *_data);
	}
	template <class T>
	constexpr base_t			_append_initializer_list(const std::initializer_list<T>& _list)
	{
		auto p = data_;
		for(auto& iter:_list)
		{
			_append<T>(iter);
		}
		return base_t(p, data_ - p);
	}
	constexpr base_t			_append_skip(std::size_t _length)
			{
				// 1) [����_����_��_������]�� ���Ѵ�.
				auto p = data() + size_;

				// check) lower bound
				_CGD_BUFFER_BOUND_CHECK((p + _length) <= get_upper_bound());

				// 2) [����_����_����]�� _length��ŭ �ø���. 
				size_ += _length;

				// return) [����_����_��_������]���� �����Ѵ�.
				return base_t(p, _length);
			}
	template <class T>
	constexpr T&				_append_emplace()
	{
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + sizeof(T)) <= get_upper_bound());

		// 1) [����_����_��_������]�� ���Ѵ�.
		auto p = reinterpret_cast<T*>(data() + size_);

		// 2) [����_����_��_������]�� �����ڸ� ȣ���Ѵ�.
	#pragma push_macro("new")
	#undef new
		new (p) T;
	#pragma pop_macro("new")

		// 3) [����_����_����]�� _length��ŭ �ø���. 
		size_ += sizeof(T);

		// return) [����_����_��_������]���� �����Ѵ�.
		return *p;
	}
	template <class T>
	constexpr T&				_append_general(const T& _data)
	{
		//// check) T must basic type
		//static_assert(is_general_serializable_v<T>, "T is not basic type, so it may not work properly. use ENABLE_STRUCT_SERIALIZABLE");

		// 1) [����_����_��_������]�� ���Ѵ�.
		auto p = reinterpret_cast<T*>(data() + size_);
	
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((p + 1) <= get_upper_bound());

		// 2) [����_����_��_������]�� ��(_data)�� ��ִ´�.
		*p = _data;
	
		// 3) [����_����_����]�� sizeof(T)��ŭ �ø���. 
		size_ += sizeof(T);
	
		// return) [����_����_��_��]�� �����Ѵ�.
		return *p;
	}
	template <class T> 
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data, std::size_t _count)
	{
		// check) _data�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_data != nullptr && _count != 0, throw std::invalid_argument("_data is nullptr or _count is 0 [1]"));

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + sizeof(T) * _count) <= get_upper_bound());

		// 1) [����_����_������]�� ������ ���´�.
		auto len_old = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_count));

		// 3) [������]���� �߰��Ѵ�.
		for(std::size_t i=0;i<_count;++i)
		{
			_append<T>(_data[i]);
		}

		// return)
		return base_t(data_ + len_old, size_ - len_old);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data, std::size_t _count)
	{
		// check) _data�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_data != nullptr && _count != 0, throw std::invalid_argument("_data is nullptr or _count is 0 [1]"));
	
		// 1) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_count));

		// 2) [������]���� ��ä�� �����Ѵ�.
		return _append_bytes(_count * sizeof(T), _data);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<!is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data)
	{
		return _append_array<T>(_data, N);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<is_memcopy_able<T>::value, base_t>
								_append_array(const T* _data)
	{
		// check)
		static_assert(N != 0, "size of array '_data' is 0");

		// 1) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(N));

		// 2) [������]���� ��ä�� �����Ѵ�.
		return _append_bytes(N * sizeof(T), _data);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string(std::basic_string_view<T> _string)
	{
		// 1) [��ǥ_������]�� ���Ѵ�.
		const auto buf_dest = data_ + size_;

		// 2) get values
		const auto length_string = _string.size();	// strnlen(, _buffer_size)
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + sizeof(T) + bytes_copy;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [���ڿ�_����]�� �����Ѵ�. (NULL����)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string + 1);
		buf_now += sizeof(COUNT_T);

		// 4) copy string
		if (bytes_copy != 0)
		{
			memcpy(buf_now, _string.data(), bytes_copy);
			buf_now += bytes_copy;
		}

		// 5) NULL�� �߰��Ѵ�.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [����_����]�� ������Ʈ�Ѵ�.
		size_ += added_length;

		// return)
		return	base_t(buf_dest, added_length);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_encoding(std::basic_string_view<TY> _string)
	{
		// 1) [��ǥ_������]�� ���Ѵ�.
		const auto buf_dest = data_ + size_;

		// 2) get values
		const auto length_string = _string.size();	// strnlen(, _buffer_size)
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + sizeof(T) + bytes_copy;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [���ڿ�_����]�� �����Ѵ�. (NULL����)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string + 1);
		buf_now += sizeof(COUNT_T);

		// 4) copy string
		if (bytes_copy != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_now), _string);
			buf_now += bytes_copy;
		}

		// 5) NULL�� �߰��Ѵ�.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [����_����]�� ������Ʈ�Ѵ�.
		size_ += added_length;

		// return)
		return	base_t(buf_dest, added_length);
	}
	template <class T, std::size_t N>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string(const T(&_string)[N])
	{
		// declare)
		const auto length_string = std::char_traits<T>::length(_string) + 1;
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + bytes_copy;

		// 1) ���ڿ��� ������ ��ġ�� ���Ѵ�.
		auto buf_dest = data_ + size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [���ڿ�_����]�� �����Ѵ�. (NULL����)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string);
		buf_now += sizeof(COUNT_T);

		// 4) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
		if (bytes_copy != 0)
		{
			memcpy(buf_now, _string, bytes_copy);
			buf_now += bytes_copy;
		}

		// 5) NULL�� �߰��Ѵ�.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [����_����]�� ������Ʈ�Ѵ�.
		size_ += added_length;

		// return) ����
		return	base_t(buf_dest, added_length);
	}
	template <class T, std::size_t N, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_encoding(const TY(&_string)[N])
	{
		// declare)
		const auto length_string = std::char_traits<T>::length(_string) + 1;
		const auto bytes_copy = length_string * sizeof(T);
		const auto added_length = sizeof(COUNT_T) + bytes_copy;

		// 1) ���ڿ��� ������ ��ġ�� ���Ѵ�.
		auto buf_dest = data_ + size_;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= get_upper_bound());

		// declare) 
		auto buf_now = buf_dest;

		// 3) [���ڿ�_����]�� �����Ѵ�. (NULL����)
		*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string);
		buf_now += sizeof(COUNT_T);

		// 4) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
		if (bytes_copy != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_now), _string);
			buf_now += bytes_copy;
		}

		// 5) NULL�� �߰��Ѵ�.
		*reinterpret_cast<T*>(buf_now) = 0;

		// 6) [����_����]�� ������Ʈ�Ѵ�.
		size_ += added_length;

		// return) ����
		return	base_t(buf_dest, added_length);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_format(std::basic_string_view<T> _format, TREST&&... _rest)
	{
		// 1) [���ڿ�]�� ������ ��ġ�� ���Ѵ�.
		const auto buf_dest = data() + size_;
		std::size_t length_string = 1;

		// declare)
		const auto bound_upper = get_upper_bound();

		// 2) get max length
		std::size_t	max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(bound_upper) - reinterpret_cast<const T*>(buf_dest + sizeof(COUNT_T))));

		// 3) [���ڿ�]�� �����Ѵ�.
		if (_format.empty() == false)
		{
			length_string = _Xsprintf(reinterpret_cast<T*>(buf_dest + sizeof(COUNT_T)), max_length, _format.data(), std::forward<TREST>(_rest)...) + 1;
		}

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + sizeof(COUNT_T) + length_string * sizeof(T)) <= bound_upper);

		// 4) [���ڿ�_����]�� �����Ѵ�.
		*reinterpret_cast<COUNT_T*>(data() + size_) = static_cast<COUNT_T>(length_string);

		// 5) get added length
		auto added_length = length_string * sizeof(T) + sizeof(COUNT_T);

		// 6) [����]�� ������Ʈ�Ѵ�.
		size_ += added_length;

		// return)
		return	base_t(buf_dest, added_length);
	}
	template <class T, std::size_t N, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_string_format(const T(&_format)[N], TREST&&... _rest)
	{
		// 1) [���ڿ�]�� ������ ��ġ�� ���Ѵ�.
		const auto buf_dest = data() + size_;
		std::size_t	length_string = 1;

		// declare) 
		auto bound_upper = get_upper_bound();

		// 2) get max length
		const std::size_t max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(bound_upper) - reinterpret_cast<const T*>(buf_dest + sizeof(COUNT_T))));

		// 3) [���ڿ�]�� �����Ѵ�.
		length_string = _Xsprintf(reinterpret_cast<T*>(buf_dest + sizeof(COUNT_T)), max_length, _format, std::forward<TREST>(_rest)...) + 1;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + sizeof(COUNT_T) + length_string * sizeof(T)) <= bound_upper);

		// 4) [���ڿ�_����]�� �����Ѵ�.
		*reinterpret_cast<COUNT_T*>(buf_dest) = static_cast<COUNT_T>(length_string);

		// 5) get added length
		const auto added_length = length_string * sizeof(T) + sizeof(COUNT_T);

		// 6) [����]�� ������Ʈ�Ѵ�.
		size_	+= added_length;

		// return)
		return	base_t(buf_dest, added_length);
	}
	template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text(std::basic_string_view<T> _string)
	{
		// 1) [���ڿ�]�� ���̸� ���Ѵ�.
		auto size_string = _string.size() * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + size_string) <= get_upper_bound());

		// 2) 
		auto buf_pos = data() + size_;

		// 2) [���ڿ�]�� �����Ѵ�.
		memcpy(buf_pos, _string.data(), size_string);

		// 3) [���ڿ�_����]��ŭ ���Ѵ�.
		size_ += size_string;

		// return) 
		return	base_t(buf_pos, size_string);
	}
	template <class T, class TY>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text_encoding(std::basic_string_view<TY> _string)
	{
		// 1) [���ڿ�]�� ���̸� ���Ѵ�.
		auto size_string = _string.size() * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + size_string) <= get_upper_bound());

		// 2) 
		auto buf_pos = data() + size_;

		// 3) [���ڿ�]�� �����Ѵ�
		if (size_string != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_pos), _string);
		}

		// 4) [���ڿ�_����]��ŭ ���Ѵ�.
		size_ += size_string;

		// return) 
		return	base_t(buf_pos, size_string);
	}

	template <class T, std::size_t N>
	constexpr base_t			_append_text(const T(&_text)[N])
			{
				// declare) 
				const auto length_string = std::char_traits<T>::length(_text);
				const auto size_string = length_string * sizeof(T);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK((data_ + size_ + size_string) <= get_upper_bound());

				// declare)
				auto buf_dest = data() + size_;

				// 1) [���ڿ�]�� �����ϰ� [���ڿ�_����]��ŭ ���Ѵ�.
				memcpy(buf_dest, _text, size_string);

				// 2) [���ڿ�_����]��ŭ ���Ѵ�.
				size_ += size_string;

				// return) 
				return	base_t(buf_dest, size_string);
			}
	template <class T, std::size_t N, class TY>
	constexpr base_t			_append_text_encoding(const TY(&_text)[N])
	{
		// declare) 
		const auto length_string = std::char_traits<T>::length(_text);
		const auto size_string = length_string * sizeof(T);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + size_string) <= get_upper_bound());

		// declare)
		const auto buf_dest = data() + size_;

		// 1) [���ڿ�]�� �����ϰ� [���ڿ�_����]��ŭ ���Ѵ�.
		if (size_string != 0)
		{
			encode_string(reinterpret_cast<T*>(buf_dest), _text);
		}

		// 2) [���ڿ�_����]��ŭ ���Ѵ�.
		size_ += size_string;

		// return) 
		return	base_t(buf_dest, size_string);
	}
	template <class T, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text_sprintf(const T* _format, TREST&&... _rest)
	{
		// 1) [���ڿ�]�� ������ ��ġ�� �����Ѵ�.
		const auto buf_dest = data() + size_;

		// declare) 
		const auto bound_upper = get_upper_bound();

		// 2) get max length
		std::size_t	max_length = _buffer_string_size_saturate((reinterpret_cast<const T*>(bound_upper) - reinterpret_cast<const T*>(buf_dest + sizeof(COUNT_T))));

	#if defined(_MSC_VER)
		#pragma warning(disable:4996)
	#endif
		// 2) [���ڿ�]�� �����Ѵ�.
		const auto length_string = _Xsprintf(reinterpret_cast<T*>(buf_dest), max_length, _format, std::forward<TREST>(_rest)...);

	#if defined(_MSC_VER)
		#pragma warning(default:4996)
	#endif
		const auto size_string = length_string * sizeof(T);

		// 3) [����]�� ������Ʈ�Ѵ�.
		size_ += size_string;

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_) <= bound_upper);

		// return) ����
		return base_t(buf_dest, size_string);
	}
	template <class T, class TFIRST, class... TREST>
	constexpr std::enable_if_t<is_string_type<T>::value, base_t>
								_append_text_fmt_format(const T* _format, TFIRST&& _first, TREST&&... _rest)
	{
	#if defined(FMT_FORMAT_H_)
		// declare) 
		fmt::basic_memory_buffer<T> temp_buffer;

		// 3) Generate trace Message
		fmt::format_to(temp_buffer, _format, std::forward<TFIRST>(_first), std::forward<TREST>(_rest)...);

		// check)
		if (temp_buffer.size() <= 0)
			return base_t();

		// return) 
		return _append_text(std::basic_string_view<T>(temp_buffer.data(), temp_buffer.size()));
	#else
		CGDK_ASSERT(false);
		return base_t();
	#endif
	}
	constexpr base_t			_append_bytes(std::size_t _size, const void* _buffer)
	{
		// check) _buffer�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_buffer != nullptr || (_buffer == nullptr && _size == 0), throw std::invalid_argument("_buffer is nullptr [1]"));

		// check) upper bound 
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + _size) <= get_upper_bound());

		// 1) [����_����_��_������]�� ��´�.
		const auto buf_dest = data() + size_;
	
		// check) _size�� 0�̸� ������.
		if(_size==0) return base_t(buf_dest, 0);
	
		// 2) [����_����_��_������]�� [������]�� [������_ũ��]��ŭ �����Ѵ�.
		if(_buffer!=nullptr && _buffer != buf_dest)
		{
			memcpy(buf_dest, _buffer, _size);
		}
	
		// 3) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
		size_ += _size;
	
		// return) 
		return base_t(buf_dest, _size);
	}
	constexpr self_t			_append_buffer(const base_t& _buffer)
	{
		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((data_ + size_ + sizeof(base_t::size_type) + _buffer.size()) <= get_upper_bound());

		// check) _data�� nullptr�̸� �ȵȴ�.
		CGDK_ASSERT(_buffer.data() != nullptr || _buffer.size() == 0, throw std::invalid_argument("_data is nullptr [1]"));

		// 1) [����_����_������]�� ������ ���´�.
		auto len_old = size_;

		// 2) �����͸� ��ִ´�.
		if(_buffer.data() != nullptr && _buffer.size() != 0)
		{
			// - [������_����]�� ��ִ´�.
			_append_general<base_t::size_type>(_buffer.size());

			// - [������]���� ��ä�� �����Ѵ�.
			_append_bytes(_buffer.size(), _buffer.data());
		}
		else
		{
			// 2) [������_����]�� 0���� ��ִ´�.
			_append_general<base_t::size_type>(0);
		}

		// return) 
		return self_t{ base_t{data_ + len_old, size_ - len_old} };
	}
	template<class T>
	constexpr base_t			_append_tuple(const std::tuple<T>& _tupple)
	{
		auto len_old = size_;
		_append<std::decay_t<T>>(std::get<0>(_tupple));
		return base_t(data_ + len_old, size_ - len_old);
	}
	template<class TFIRST, class TSECOND, class... TREST>
	constexpr base_t			_append_tuple(const std::tuple<TFIRST, TSECOND, TREST...>& _tupple)
	{ 
		auto len_old = size_;
		_append<std::decay_t<TFIRST>>(std::get<0>(_tupple));
		_append_tuple<TSECOND, TREST...>((const std::tuple<TSECOND, TREST...>&)_tupple);
		return base_t(data_ + len_old, size_ - len_old);
	}
	template<class T>
	constexpr void				_append_multi_(T&& _tupple)
	{
		_append<std::decay_t<T>>(std::forward<T>(_tupple));
	}
	template<class TFIRST, class TSECOND, class... TREST>
	constexpr void				_append_multi_(TFIRST&& _first, TSECOND&& _second, TREST&&... _rest)
	{ 
		_append<std::decay_t<TFIRST>>(_first);
		_append_multi_<TSECOND, TREST...>(std::forward<TSECOND>(_second), std::forward<TREST>(_rest)...);
	}
	template<class... T>
	constexpr base_t			_append_multi(T&&... _multi)
	{ 
		auto len_old = size_;
		_append_multi_<T...>(std::forward<T>(_multi)...);
		return base_t(data_ + len_old, size_ - len_old);
	}

	template <class T>
	constexpr auto				_append_text_integral(char _value)				{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(int8_t _value)			{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(uint8_t _value)			{ return _append_text_integral<T>(static_cast<uint64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(int16_t _value)			{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(uint16_t _value)			{ return _append_text_integral<T>(static_cast<uint64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(int32_t _value)			{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(uint32_t _value)			{ return _append_text_integral<T>(static_cast<uint64_t>(_value));}
#if defined(_MSC_VER)
	template <class T>
	constexpr auto				_append_text_integral(long _value)				{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(unsigned long _value)		{ return _append_text_integral<T>(static_cast<uint64_t>(_value));}
#else
	template <class T>
	constexpr auto				_append_text_integral(long long _value)			{ return _append_text_integral<T>(static_cast<int64_t>(_value));}
	template <class T>
	constexpr auto				_append_text_integral(unsigned long long _value){ return _append_text_integral<T>(static_cast<uint64_t>(_value));}
#endif
	template <class T>
	constexpr std::basic_string_view<T> _append_text_integral(uint64_t _value)
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
		auto buf_dest = data() + size_;

		// declare)
		std::basic_string_view<T> result(buf_dest, pos_now - temp_buf);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + result.size()) <= get_upper_bound());

		// 3) reverse copy
		for (--pos_now; pos_now >= temp_buf; ++buf_dest, --pos_now)
		{
			*buf_dest = *pos_now;
		}

		// 4) set size_
		size_ += result.size() * sizeof(T);

		// return) 
		return	result;
	}
	template <class T>
	constexpr std::basic_string_view<T> _append_text_integral(int64_t _value)
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
		auto buf_dest = data() + size_;

		// declare)
		std::basic_string_view<T> result(buf_dest, pos_now - temp_buf);

		// check) upper bound
		_CGD_BUFFER_BOUND_CHECK((buf_dest + result.size()) <= get_upper_bound());

		// 3) reverse copy
		for (--pos_now; pos_now >= temp_buf; ++buf_dest, --pos_now)
		{
			*buf_dest = *pos_now;
		}

		// 4) set size_
		size_ += result.size() * sizeof(T);

		// return) 
		return	result;
	}
	template <class T>
	std::basic_string_view<T>	_append_text_float(double _value)//;
	//template <>
	//constexpr std::basic_string_view<char> _append_text_float<char>(double _value)
	{
		auto temp = std::to_string(_value);
		return _append_text(static_cast<std::string_view>(temp));
	}
	//template <>
	//constexpr std::basic_string_view<wchar_t> _append_text_float<wchar_t>(double _value)
	//{
	//	return _append_text((std::wstring_view)std::to_wstring(_value));
	//}

	template<class T>
	constexpr base_t			_append_container_associative(const T& _container)
	{
		// !����) value-key ������ append�ؾ� �Ѵ�.

		// 1) store data_
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [������]���� ��ִ´�.
		for (auto iter = _container.begin(); iter != _container.end(); ++iter)
		{
			// _ key�� ��ִ´�.
			_append<typename T::key_type>(iter->first);
			// - Value�� ��ִ´�.
			_append<typename T::mapped_type>(iter->second);
		}

		// return) 
		return base_t(data_ + l, size_ - l);
	}
	template<class T>
	constexpr base_t			_prepend_container_associative(const T& _container)
	{
		// ����) extract�� value->key������ extract�ǹǷ� prepaend�ÿ��� key->value������ prepend����� �Ѵ�.

		// declare) 
		auto p = data_;

		// 1) Begin/End Iterator
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		// 2) [������]���� ��ִ´�.
		for(; iter!=iterEnd; ++iter)
		{
			// - Value�� ��ִ´�.
			_prepend<typename T::mapped_type>(iter->second);
			// _ key�� ��ִ´�.
			_prepend<typename T::key_type>(iter->first);
		}

		// 3) [������_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return base_t(data_, p - data_);
	}

	template<class I>
	constexpr std::enable_if_t<is_iterator<I>::value, base_t>
								_append_iterator(I _first, I _last)
	{
		// 1) store data_
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		auto buf_count = _append_skip(sizeof(COUNT_T));

		// declare)
		COUNT_T iter_count = 0;

		// 3) [������]���� ��ִ´�.
		for (; _first != _last; ++_first, ++iter_count)
		{
			_append<typename I::value_type>(*_first);
		}

		// 4) ������ ���� ��ġ�� ������ ��ִ´�.
		buf_count.template front<COUNT_T>() = iter_count;

		// return) 
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, base_t>
								_append_container_array(const T& _container)
	{
		// 1) [����_����_����]�� �����´�.
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [������]���� ��ִ´�.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			_append<typename T::value_type>(*iter);
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, base_t>
								_append_container_array(const T& _container)
	{
		// 1) [����_����_����]�� �����´�.
		auto l = size_;

		// declare)
		auto count = _container.size();

		// 1) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(count));

		// 3) [������]���� ��ִ´�.
		if (count != 0)
		{
			_append_bytes(count * sizeof(typename T::value_type), &_container.front());
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_own_ptr_list(const T& _container)
	{
		// 1) [����_����_����]�� �����´�.
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [������]���� ��ִ´�.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			if(iter->empty()==false)
			{
				_append<typename T::value_type>(*iter);
			}
			else
			{
				_append<COUNT_T>(COUNT_T(0)-1);
			}
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_object_ptr_list(const T& _container)
	{
		// 1) [����_����_����]�� �����´�.
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [������]���� ��ִ´�.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for (; iter != iterEnd; ++iter)
		{
			if(iter->empty()==false)
			{
				_append<typename T::value_type>(*iter);
			}
			else
			{
				_append<COUNT_T>(COUNT_T(0)-1);
			}
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr base_t			_append_container_list(const T& _container)
	{
		// 1) [����_����_����]�� �����´�.
		auto l = size_;

		// 2) [������_����]�� ��ִ´�.
		_append_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// 3) [������]���� ��ִ´�.
		auto iter = _container.begin();
		auto iterEnd = _container.end();

		for(; iter!=iterEnd; ++iter)
		{
			_append<typename T::value_type>(*iter);
		}

		// return)
		return base_t(data_ + l, size_ - l);
	}
	template <class T>
	constexpr base_t			_prepend_container_list(const T& _container)
	{
		// declare) 
		auto p = data_;

		// 1) Begin/End Iterator
		auto iter = _container.rbegin();
		auto iter_end = _container.rend();

		// 2) [������]���� ��ִ´�.
		for(; iter != iter_end; ++iter)
		{
			_prepend<typename T::value_type>(*iter);
		}

		// 3) [������_����]�� ��ִ´�.
		_prepend_general<COUNT_T>(static_cast<COUNT_T>(_container.size()));

		// return) 
		return	base_t(data_, p - data_);
	}

public:
	// 10) begin/end)
	constexpr self_t			_begin(int _offset) const noexcept { return self_t(base_t::_begin(_offset), bound);}
	constexpr self_t			_end(int _offset) const noexcept { return self_t(base_t::_end(_offset), bound);}

	// 11) append/extarct
	constexpr self_t			_extract_buffer();

	constexpr bool				_is_buffer_overflow() const
								{
									// check) 
									RETURN_IF(get_upper_bound() == nullptr, false);

									// check) Check Lower Bound
									RETURN_IF(data_ > get_lower_bound(), false);

									// check) Check Upper Bound
									RETURN_IF((data_ + size_) <= get_upper_bound(), false);

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
									CGDK_ASSERT(_rhs.get_front_ptr() >= get_lower_bound()); 

									// check) 
									if(_rhs.get_front_ptr() < get_lower_bound())
										throw std::length_error("buffer overflow. out of lower bound'");

									// check) 
									CGDK_ASSERT(_rhs.get_back_ptr() <= get_upper_bound());

									// check) 
									if (_rhs.get_back_ptr() > get_upper_bound())
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


}

#include "buffer/basic_buffer.inl"
