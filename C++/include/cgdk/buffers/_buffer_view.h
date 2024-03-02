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
template <class ELEM_T>
class _buffer_view : protected buffer_base<ELEM_T>
{
// traits) 
public:
			using base_t	  = buffer_base<ELEM_T>;
			using self_t	  = _buffer_view<ELEM_T>;
			using element_t	  = std::remove_pointer_t<decltype(base_t::data_)>;
			using size_type	  = decltype(base_t::size_);
			using traits	  = _buffer_traits_t<element_t>;

			template<class T> using peek_tr = PEEK_tr<self_t, T>;
			template<class T> using extr_tr = EXTR_tr<self_t, T>;

// constructor/destructor) 
public:
	// 1) costructor
	constexpr _buffer_view() noexcept {}
	constexpr _buffer_view(_element_void_t<element_t>* _ptr, size_type _size = 0) noexcept : base_t{ _size, reinterpret_cast<element_t*>(_ptr) } {}
	constexpr _buffer_view(const self_t& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
	constexpr _buffer_view(self_t&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
	template <class T>
	constexpr _buffer_view(const _buffer_view<T>& _buffer) noexcept : base_t{ _buffer.size(), const_cast<std::remove_const_t<T>*>(_buffer.data()) } {}
	template <class T>
	constexpr _buffer_view(_buffer_view<T>&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
	constexpr _buffer_view(const base_t& _buffer) noexcept : base_t{ _buffer.size_, _buffer.data_ } {}
	template <class T>
	constexpr _buffer_view(const buffer_base<T>& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}
	constexpr _buffer_view(base_t&& _buffer) noexcept : base_t{ _buffer.size_, _buffer.data_ } {}
	template <class T>
	constexpr _buffer_view(buffer_base<T>&& _buffer) noexcept : base_t{ _buffer.size(), _buffer.data() } {}

	template <class T, size_t N>
	constexpr _buffer_view(T(&_array)[N]) noexcept : base_t{ N * sizeof(T), reinterpret_cast<element_t*>(_array) } {}
	template <class T, size_t N>
	constexpr _buffer_view(std::array<T, N>& _array) noexcept : base_t{ N * sizeof(T), reinterpret_cast<element_t*>(_array.data()) } {}
	template <class T>
	constexpr _buffer_view(std::basic_string_view<T> _string) noexcept : base_t{ _string.size() * sizeof(T), reinterpret_cast<element_t*>(const_cast<T*>(_string.data())) } {}

// public) 
public:
	// 1) 
	constexpr bool				exist() const noexcept					{ return this->size_ != 0;}
	constexpr bool				empty() const noexcept					{ return this->size_ == 0;}
	constexpr size_type			size() const noexcept					{ return this->size_;}
#ifdef _WIN32
	#pragma warning(disable:4267)
#endif
	template <class CAST_SIZE_T>
	constexpr CAST_SIZE_T		size() const noexcept					{ CGDK_ASSERT(this->size_ == static_cast<size_type>(static_cast<CAST_SIZE_T>(this->size_))); return static_cast<CAST_SIZE_T>(this->size_);}
#ifdef _WIN32
	#pragma warning(default:4267)
#endif
	constexpr size_type			size_bytes() const noexcept				{ return this->size_ * sizeof(element_t);}
	template <class CAST_SIZE_T>
	constexpr CAST_SIZE_T		size_bytes() const noexcept				{ auto bytes = size_bytes(); CGDK_ASSERT(bytes == static_cast<size_type>(static_cast<CAST_SIZE_T>(bytes))); return static_cast<CAST_SIZE_T>(bytes);}
	constexpr void				set_size(size_type _new_size)			{ this->size_ = _new_size; } // unsafe
	constexpr void				add_size(size_type _size)				{ this->size_ += _size; } // unsafe
	constexpr void				sub_size(size_type _size)				{ this->size_ -= _size; } // unsafe
	constexpr void				inc_size()								{ ++this->size_; } // unsafe
	constexpr void				dec_size()								{ --this->size_; } // unsafe
	constexpr void				clear() noexcept						{ this->size_ = 0; this->data_ = nullptr;}

	constexpr auto&				operator[](size_type _index)			{ return this->data_[_index];}
	constexpr const auto&		operator[](size_type _index) const		{ return this->data_[_index];}

	template <class T>
	constexpr auto				to_string() const noexcept				{ return std::basic_string_view<T>(reinterpret_cast<const T*>(this->data_), this->size_ / sizeof(T)); }

	// 2) data/
	constexpr element_t*		data() const noexcept					{ return this->data_;}
	constexpr element_t*		data(int64_t _offset) const				{ return this->data_ + _offset;} // unsafe
	template <class T = element_t>
	constexpr auto				data() const noexcept					{ return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_);}
	template <class T = element_t>
	constexpr auto				data(int64_t _offset) const				{ return reinterpret_cast<_buffer_return_t<traits, T>*>(this->data_ + _offset);} // unsafe
	constexpr void				set_data(element_t* _data)				{ this->data_ = _data; } // unsafe
	constexpr void				add_data(size_type _size)				{ this->data_ += _size; } // unsafe
	constexpr void				sub_data(size_type _size)				{ this->data_ -= _size; } // unsafe

	// 3) exist/empty
	constexpr void				swap(base_t& _rhs) noexcept				{ auto a = this->data_; this->data_ = _rhs.data_; _rhs.data_ = a; auto b = this->size_; this->size_ = _rhs.size_; _rhs.size_ = b; }
	constexpr void				swap(self_t& _rhs) noexcept				{ auto a = this->data_; this->data_ = _rhs.data(); _rhs.set_data(a); auto b = this->size(); this->size_ = _rhs.size(); _rhs.set_size(b); }
	template <class T>
	constexpr void				copy_from(const _buffer_view<T>& _source) { memcpy(this->data_, _source.data(), _source.size()); this->size_ = _source.size(); }
	constexpr self_t			split_head(size_type _amount) noexcept	{ if (this->size_ < _amount) _amount = this->size_; self_t p{ this->data_, this->size_ - _amount }; this->data_ += _amount; this->size_ = _amount; return p; }
	constexpr self_t			split_tail(size_type _amount) noexcept	{ if (this->size_ < _amount) _amount = this->size_; self_t p{ this->data_ + _amount, this->size_ - _amount }; this->size_ = _amount; return p; }

	// 4) extract/subtract
			template <std::size_t ISIZE>
	constexpr auto				extract()								{ return _extract_bytes(ISIZE);}
	constexpr auto				extract(CGDK::size _length)				{ return _extract_bytes(_length.amount);}
	constexpr auto				extract(size_type _size, void* _buffer)	{ return _extract_bytes(_size, _buffer);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, extr_tr<T>>
								extract()								{ return serializer_extract<self_t, std::remove_const_t<T>>::_do_extract(*this);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								extract_to(T& _dest)					{ serializer_extract<self_t, std::remove_const_t<T>>::_do_extract(_dest, *this);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								extract()								{ return _extract_general<std::remove_reference_t<std::remove_const_t<T>>>();}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								extract(T& _dest)						{ _extract_general<std::remove_reference_t<std::remove_const_t<T>>>(_dest);}
			template <class T>
	constexpr auto				extract_string(T* _string, size_type _length_in_words=(size_type(-1))) { return _extract_string_copy(_string, _length_in_words);}
			template<class... T>
	constexpr self_t			extract(const std::tuple<T...>& _tuple)	{ auto buf_old = this->data_; _extract_tuple(_tuple); return self_t(buf_old, this->data_ - buf_old);}
			template<class... T>
	constexpr self_t			extract(std::tuple<T...>&& _tuple)		{ auto buf_old = this->data_; _extract_tuple(std::move(_tuple)); return self_t(buf_old, this->data_ - buf_old);}
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

	// 5) front
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
								front(offset& _pos) const				{ return _front<T>(_pos.amount);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, T>
								front(offset& _pos) const				{ return _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_pos.amount);}
			template <class T>
	constexpr std::enable_if_t<!std::is_reference_v<T>, void>
								front_to(T& _dest, offset& _pos) const	{ _front<T>(_dest, _pos.amount);}
			template <class T>
	constexpr std::enable_if_t<std::is_reference_v<T>, void>
								front_to(T& _dest, offset& _pos) const	{ _front_general<std::remove_reference_t<std::remove_const_t<T>>>(_dest, _pos.amount);}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								front_text(T _terminal = 0, int64_t _offset = 0) { return _front(_text<T>(_terminal, _offset));}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								front_text(CGDK::size _length, int64_t _offset = 0) { return _front_text_by_length<T>(_length.amount, _offset);}

	// 6) back
	constexpr auto				back(int64_t _offset = 0) const			{ return _back(_offset);}
			template <class T>
	constexpr peek_tr<T>		back(int64_t _offset = 0) const			{ return _back<T>(_offset);}
			template <class T>
	constexpr peek_tr<T>		back(offset& _pos) const				{ return _back<T>(_pos.amount);}

	// 7) begin/end														  
	constexpr auto				begin() const							{ return _begin();}
	constexpr auto				end() const								{ return _end();}
	constexpr auto				end(int _offset) const					{ return _end(_offset);}
	constexpr auto				get_front_ptr() const noexcept			{ return this->data_;}
			template <class T>
	constexpr auto				get_front_ptr() const noexcept			{ return reinterpret_cast<T*>(this->data_); }
			template <class T = char>
	constexpr void				set_front_ptr(T* _pos)					{ _CGD_BUFFER_BOUND_CHECK(_pos <= this->get_back_ptr<T>()); auto temp_offset = reinterpret_cast<element_t*>(_pos) - this->data_; this->data_ = reinterpret_cast<element_t*>(_pos); this->size_ -= temp_offset;  }
	constexpr auto				get_back_ptr() const noexcept			{ return this->data_ + this->size_;}
			template <class T>
	constexpr auto				get_back_ptr() const noexcept			{ return reinterpret_cast<T*>(this->data_ + this->size_);}
			template <class T = char>
	constexpr void				set_back_ptr(T* _pos)					{ _CGD_BUFFER_BOUND_CHECK(_pos >= this->get_front_ptr<T>()); this->size_ = reinterpret_cast<element_t*>(_pos) - this->data_; }

	// 8) Operator Overloading
			// [operator] +/-
	constexpr self_t			operator+ (CGDK::offset _rhs) const
			{
				if (_rhs.amount > static_cast<int64_t>(this->size_))
					throw std::length_error("out of range. operator '+' (_rhs > size_)'");

				return self_t{ this->data_ + _rhs.amount, this->size_ - static_cast<decltype(this->size_)>(_rhs.amount)};
			}
	constexpr self_t			operator- (CGDK::size _rhs) const
			{
				if (_rhs.amount > static_cast<int64_t>(this->size_))
					throw std::length_error("out of range. operator '-' (_rhs > size_)");

				return self_t{ this->data_, this->size_ - _rhs.amount };
			}
			// [operator] =
	constexpr self_t&			operator= (const self_t& _rhs) noexcept { this->data_ =_rhs.data(); this->size_ =_rhs.size(); return *this;}
			template<class T>
	constexpr self_t&			operator= (const _buffer_view<T>& _rhs) noexcept { this->data_ =_rhs.data(); this->size_ =_rhs.size(); return *this;}
	constexpr self_t&			operator= (self_t&& _rhs) noexcept { this->data_ =_rhs.data(); this->size_ =_rhs.size(); return *this;}
			template<class T>
	constexpr self_t&			operator= (_buffer_view<T>&& _rhs) noexcept { this->data_ =_rhs.data(); this->size_ =_rhs.size(); return *this;}
			// [operator] =				   
	constexpr self_t&			operator= (const base_t& _rhs) noexcept { this->data_ =_rhs.data(); this->size_ =_rhs.size(); return *this;}
			template<class T>
	constexpr self_t&			operator= (const buffer_base<T>& _rhs) noexcept { this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }
	constexpr self_t&			operator= (base_t&& _rhs) noexcept { this->data_ =_rhs.data_; this->size_ =_rhs.size_; return *this;}
			template<class T>
	constexpr self_t&			operator= (buffer_base<T>&& _rhs) noexcept { this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }

			// [operator] +=/-=
	constexpr self_t&			operator+= (CGDK::offset _rhs)
			{
				if (_rhs.amount > static_cast<int64_t>(this->size_))
					throw std::length_error("out of range. operator '+=' (_rhs > size_)");
		
				this->data_ += _rhs.amount;
				this->size_ -= _rhs.amount;

				return *this;
			}
	constexpr self_t&			operator-= (CGDK::size _rhs)
			{
				if (_rhs.amount > static_cast<int64_t>(this->size_))
					throw std::length_error("out of rangne. operator '-=' (_rhs > size_)");
		
				this->size_ -= _rhs.amount;

				return *this;
			}
			// [operator] ^=
			template<class T>
	constexpr self_t&			operator^=(const _buffer_view<T>& _rhs)	{ this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }
			template<class T>
	constexpr self_t&			operator^=(_buffer_view<T>&& _rhs) { this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }
			template<class T>
	constexpr self_t&			operator^=(const buffer_base<T>& _rhs) { this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }
			template<class T>
	constexpr self_t&			operator^=(buffer_base<T>&& _rhs) { this->data_ = _rhs.data(); this->size_ = _rhs.size(); return *this; }
	constexpr self_t&			operator^=(size_type _rhs) { this->size_ = _rhs; return *this;}
			// [operator] >> - extract
			template <class T>
	constexpr self_t&			operator>>(T& _rhs) { _rhs = _extract<T>(); return *this;}
			// [operator] Conversion
			template <class T>
	constexpr					operator std::basic_string_view<T>() const noexcept { return std::basic_string_view<T>(reinterpret_cast<T*>(const_cast<char*>(this->data_)), (this->size_ * sizeof(element_t))/sizeof(T));}

public:
	// extract) 
			template <class T>
	constexpr extr_tr<T>		_extract() { return EXTR_t<self_t,T>::_do_extract(*this);}
			template <class T>
	constexpr void				_extract(T& _dest) { EXTR_t<self_t,T>::_do_extract(_dest, *this);}
	constexpr self_t			_extract_bytes(size_type _length)
			{
				// check) _length가 0이하면 안된다.
				CGDK_ASSERT(_length >= 0, throw std::invalid_argument("_length is invalid [0]"));

				// check) [원본_버퍼_크기]보다 _length가 커야 한다.
				_CGD_BUFFER_BOUND_CHECK(this->size_ >= _length);

				// 1) [원본_버퍼_포인터]의 크기를 임시로 저장한다.
				auto buf_old = this->data_;

				// 1) [원본_버퍼_포인터]의 크기를 _length만큼 늘리고 [원본_버퍼_길이]는 줄인다.
				this->data_ += _length;
				this->size_ -= _length;

				// return) [원본_버퍼_처음_포인터]
				return self_t(buf_old, _length);
			}

			template <class T>
	constexpr std::basic_string<T> _extract_string() { return std::basic_string<T>(_extract_string_view<T>()); }
			template <class T>
	constexpr void				_extract_string(std::basic_string<T>& _dest) { _dest = _extract_string_view<T>(); }
			template <class T>
			COUNT_T				_extract_string_copy(T* _string, size_type _length_in_words=(size_type(0)-1))
			{
				// check) _string이 nullptr이면 안된다.
				CGDK_ASSERT(_string != nullptr, throw std::invalid_argument("_string is nullptr [1]"));

				// check) _length_in_words가 0이하면 안된다.
				CGDK_ASSERT(_length_in_words >= 0, throw std::invalid_argument("_length_in_words is invalid [0]"));

				// 1) [데이터_크기]를 얻어온다.(COUNT_T[문자열_길이]+length(String))
				auto length_string = this->_get_front_string_length<T>();

				// check) length가 0보다 작으면 그냥 리턴한다.
				if (length_string == COUNT_T(-1))
				{
					this->data_ += sizeof(COUNT_T);
					this->size_ -= sizeof(COUNT_T);
					return COUNT_T(-1);
				}

				// 2) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+size(String))
				auto size_string = length_string * sizeof(T);

				// check) [문자열_길이]가 [목표_버퍼_길이]보다 작은 지를 확인한다.
				if (size_string >= _length_in_words)
					throw std::length_error("_buffer_view size is too small!! [5]");

				// 3) [복사할 위치]를 얻는다.
				auto p = reinterpret_cast<const T*>(this->data_ + sizeof(COUNT_T));

				// 4) [원본_버퍼_포인터]에 [문자열을]을 복사한다.
				if (_string != p)
				{
					memcpy(_string, p, size_string);
				}

				// 5) 문자열 길이를 sizeof(COUNT_T)만큼 늘린다.
				size_string += sizeof(COUNT_T);

				// 5) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
				this->data_ += size_string;
				this->size_ -= size_string;

				// return) [문자열_길이]를 리턴한다.
				return length_string;
			}

			template<class T>
	constexpr std::enable_if_t<!is_own_ptr_serialziable<T>::value && !std::is_base_of_v<Ibuffer_serializable, T>, void>
								_extract_tuple(std::tuple<T>& _dest)
			{
				std::get<0>(_dest) = this->_extract<std::remove_reference_t<std::remove_cv_t<T>>>();
			}
			template<class T>
	constexpr std::enable_if_t<is_own_ptr_serialziable<T>::value || (std::is_base_of_v<Ibuffer_serializable, T> && !is_object_ptr_v<T>), void>
								_extract_tuple(std::tuple<T>& _dest)
			{
				std::get<0>(_dest).serialize_in(*this);
			}
			template<class T>
	constexpr std::enable_if_t<is_own_ptr_serialziable<T>::value || (std::is_base_of_v<Ibuffer_serializable, T> && is_object_ptr_v<T>), void>
								_extract_tuple(std::tuple<T>& _dest)
			{
				std::get<0>(_dest)->serialize_in(*this);
			}

			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<!is_own_ptr_serialziable<TFIRST>::value && !std::is_base_of_v<Ibuffer_serializable, TFIRST>, void>
								_extract_tuple(std::tuple<TFIRST, TSECOND, TREST...>& _dest)
			{
				std::get<0>(_dest) = this->_extract< std::remove_reference_t<std::remove_cv_t<TFIRST>>>();
				this->_extract_tuple((std::tuple<TSECOND, TREST...>&)_dest);
			}
			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<is_own_ptr_serialziable<TFIRST>::value || (std::is_base_of_v<Ibuffer_serializable, TFIRST> && !is_object_ptr_v<TFIRST>), void>
								_extract_tuple(std::tuple<TFIRST, TSECOND, TREST...>& _dest)
			{
				std::get<0>(_dest).serialize_in(*this);
				this->_extract_tuple((std::tuple<TSECOND, TREST...>&)_dest);
			}
			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<is_own_ptr_serialziable<TFIRST>::value || (std::is_base_of_v<Ibuffer_serializable, TFIRST> && is_object_ptr_v<TFIRST>), void>
								_extract_tuple(std::tuple<TFIRST, TSECOND, TREST...>& _dest)
			{
				std::get<0>(_dest)->serialize_in(*this);
				this->_extract_tuple((std::tuple<TSECOND, TREST...>&)_dest);
			}

			template<class T>
	constexpr std::enable_if_t<!is_own_ptr_serialziable<T>::value && !std::is_base_of_v<Ibuffer_serializable, T>, void>
								_extract_multi(T& _dest)
			{
				_dest = this->_extract<T>();
			}

			template<class T>
	constexpr std::enable_if_t<is_own_ptr_serialziable<T>::value || (std::is_base_of_v<Ibuffer_serializable, T> && !is_object_ptr_v<T>), void>
								_extract_multi(T& _dest)
			{
				_dest.serialize_in(*this);
			}

			template<class T>
	constexpr std::enable_if_t<is_own_ptr_serialziable<T>::value || (std::is_base_of_v<Ibuffer_serializable, T> && is_object_ptr_v<T>), void>
								_extract_multi(T& _dest)
			{
				_dest->serialize_in(*this);
			}

			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<!is_own_ptr_serialziable<TFIRST>::value && !std::is_base_of_v<Ibuffer_serializable, TFIRST>, void>
								_extract_multi(TFIRST& _first, TSECOND& _second, TREST&... _rest)
			{
				_first = this->_extract<std::remove_reference_t<std::remove_cv_t<TFIRST>>>();
				this->_extract_multi(_second, _rest...);
			}

			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<is_own_ptr_serialziable<TFIRST>::value || (std::is_base_of_v<Ibuffer_serializable, TFIRST> && !is_object_ptr_v<TFIRST>), void>
								_extract_multi(TFIRST& _first, TSECOND& _second, TREST&... _rest)
			{
				_first.serialize_in(*this);
				this->_extract_multi(_second, _rest...);
			}

			template<class TFIRST, class TSECOND, class... TREST>
	constexpr std::enable_if_t<is_own_ptr_serialziable<TFIRST>::value || (std::is_base_of_v<Ibuffer_serializable, TFIRST> && is_object_ptr_v<TFIRST>), void>
								_extract_multi(TFIRST& _first, TSECOND& _second, TREST&... _rest)
			{
				_first->serialize_in(*this);
				this->_extract_multi(_second, _rest...);
			}

	constexpr std::string_view	_extract_web_modify()
			{
				// definition)
				const uint16_t web_terminal = ('\n' << 8) | '\r';

				// declare)
				auto ptr_begin = (char*)(this->data_);
				auto ptr_now = ptr_begin;
				auto ptr_end = ptr_begin + this->size_ - 1;
				std::string_view result;

				// 1) /r/n을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*reinterpret_cast<uint16_t*>(ptr_now) == web_terminal)
					{
						// - data_를 ptr_now+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
						this->data_ = (ptr_now + 2);
						this->size_ = (ptr_end - ptr_now - 1);

						// - NULL을 넣는다.
						*ptr_now = 0;

						// - 문자열을 설정한다.
						result = std::string_view(ptr_begin, ptr_now - ptr_begin);

						// break;)
						break;
					}
				}

				// return)
				return result;
			}
	constexpr std::string_view _extract_web()
			{
				std::string_view result;
				_extract_web(result);
				return result;
			}

	constexpr void _extract_web(std::string_view& _dest)
			{
				// definition)
				const uint16_t web_terminal = ('\n' << 8) | '\r';

				// declare)
				auto ptr_begin = reinterpret_cast<char*>(this->data_);
				auto ptr_now = ptr_begin;
				auto ptr_end = ptr_begin + this->size_ - 1;

				// 1) /r/n을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*(uint16_t*)ptr_now == web_terminal)
					{
						// - data_를 ptr_now+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
						this->data_ = (ptr_now + 2);
						this->size_ = (ptr_end - ptr_now - 1);

						// return) 
						_dest = std::string_view(ptr_begin, ptr_now - ptr_begin);

						// break)
						return;
					}
				}

				// 2) clear string_view
				_dest = std::string_view();
			}

	constexpr std::string_view	_extract_web(char* _buffer, size_type _buffer_size = (size_type(0) - 1))
	{
		std::string_view result;
		_extract_web(result, _buffer, _buffer_size);
		return result;
	}
	constexpr void _extract_web(std::string_view& _dest, char* _buffer, size_type _buffer_size = (size_type(0)-1))
			{
				// check) _buffer_size가 0이하면 안된다.
				CGDK_ASSERT(_buffer_size >= 0, throw std::invalid_argument("_buffer_size is invalid [0]"));

				// check) _buffer이 nullptr이면 안된다.
				CGDK_ASSERT(_buffer != nullptr, throw std::invalid_argument("_buffer is nullptr [1]"));

				// definition)
				const uint16_t web_terminal = ('\n' << 8) | '\r';

				// declare)
				auto ptr_begin = reinterpret_cast<char*>(this->data_);
				auto ptr_now = ptr_begin;
				auto ptr_end = ptr_begin + this->size_ - 1;

				// 1) /r/n을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*(uint16_t*)ptr_now == web_terminal)
					{
						// - 깅리를 구한다.
						size_type str_length = ptr_now - ptr_begin;

						// - 최대 버퍼를 넘지않도록 한다.
						if (str_length > (_buffer_size - 1)) str_length = (_buffer_size - 1);

						// - 복사한다
						memcpy(_buffer, this->data_, str_length);

						// - 마지막에 NULL을 추가한다.
						*(_buffer + str_length) = 0;

						// - data_를 ptr_now+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
						this->data_ = (ptr_now + 2);
						this->size_ = (ptr_end - ptr_now - 1);

						// - 
						_dest = std::string_view(_buffer, str_length);

						// break)
						return;
					}
				}

				// 2) clear string_view
				_dest = std::string_view();
			}

			self_t				_extract_bytes(size_type _size, void* _buffer)
			{
				self_t _dest;
				this->_extract_bytes(_dest, _size, _buffer);
				return _dest;
			}
			void				_extract_bytes(self_t& _dest, size_type _size, void* _buffer)
			{
				// check) _buffer이 nullptr이면 안된다.
				CGDK_ASSERT(_buffer != nullptr, throw std::invalid_argument("_buffer is nullptr [0]"));

				// check) _size가 0이하면 안된다.
				CGDK_ASSERT(_size >= 0, throw std::invalid_argument("_size is invalid [1]"));

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_size <= this->size_);

				// 1) clear dest
				_dest = self_t(this->data_, 0);

				// check) 길이가 0이면 그냥 되돌린다.
				if (_size == 0)
				{
					return;
				}

				// 2) 복사한다.
				memcpy(_buffer, this->data_, _size);

				// 3) set dest
				_dest = self_t(this->data_, _size);

				// 4) _size만큼 더한다.
				this->data_ += _size;
				this->size_ -= _size;
			}

			template <class T>
			void _extract_general(T& _dest)
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(sizeof(T) <= this->size_);

				// declare)
				_dest = *reinterpret_cast<_buffer_return_t<traits,T>*>(this->data_);

				// 2) _size만큼 더한다.
				this->data_ += sizeof(T);
				this->size_ -= sizeof(T);
			}
			template <class T>
			T&					_extract_general()
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(sizeof(T) <= this->size_);

				// declare)
				T* p = reinterpret_cast<_buffer_return_t<traits,T>*>(this->data_);

				// 2) _size만큼 더한다.
				this->data_ += sizeof(T);
				this->size_ -= sizeof(T);

				// return) 
				return *p;
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_extract_string_view()
			{
				std::basic_string_view<T> dest;
				_extract_string_view(dest);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_extract_string_view(std::basic_string_view<T>& _dest)
			{
				// 1) [데이터_크기]를 얻어온다.(COUNT_T[문자열_길이]+length(String))
				COUNT_T	str_length = this->_get_front_string_length<T>();

				// check) length가 0보다 작으면 그냥 리턴한다.
				if (str_length == COUNT_T(-1))
				{
					this->data_ += sizeof(COUNT_T);
					this->size_ -= sizeof(COUNT_T);
					_dest = std::basic_string_view<T>();
					return;
				}

				// 2) 문자열의 제일 앞 포인터를 얻어둔다.
				auto str_string = this->data<T>(sizeof(COUNT_T));

				// 2) sizeOfData 구하기
				auto size_data = static_cast<COUNT_T>(str_length * sizeof(T) + sizeof(COUNT_T));

				// 3) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
				this->data_ += size_data;

				// 4) [원본_버퍼_길이]를 [데이터_크기]만큼 줄인다.
				this->size_ -= size_data;

				// return) [문자열_시작_포인터]을 리턴한다.
				_dest = std::basic_string_view<T>(str_string, static_cast<size_type>(str_length) - 1);
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_extract_text(T _wchar_terminal)
			{
				std::basic_string_view<T> dest;
				this->_extract_text<T>(dest, _wchar_terminal);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_extract_text(std::basic_string_view<T>& _dest, T _wchar_terminal)
			{
				// declare)
				auto ptr_begin = reinterpret_cast<T*>(this->data_);
				auto ptr_now = ptr_begin;
				auto ptr_end = reinterpret_cast<T*>(this->data_ + this->size_);

				// 1) /r/n을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*ptr_now == _wchar_terminal)
					{
						// - data_를 ptr_now+1로 설정한다. (Terminal 문제 부분을 빼기위해+2를 함.)
						this->data_ = (ptr_now + 1);
						this->size_ = (size_type)ptr_end - (size_type)ptr_now;

						// - 문자열을 설정한다.
						_dest = std::basic_string_view<T>(ptr_begin, ptr_now - ptr_begin);

						// return)
						return;
					}
				}

				// 2) failed
				_dest = std::basic_string_view<T>();
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_extract_text(T _wchar_terminal,  T _wchar_change)
			{
				std::basic_string_view<T> dest;
				this->_extract_text<T>(dest, _wchar_terminal, _wchar_change);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_extract_text(std::basic_string_view<T>& _dest, T _wchar_terminal,  T _wchar_change)
			{
				// declare) 
				auto ptr_begin = reinterpret_cast<T*>(this->data_);
				auto ptr_now = ptr_begin;
				auto ptr_end = reinterpret_cast<T*>(this->data_ + this->size_);

				// 1) _wchar_terminal을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*ptr_now == _wchar_terminal)
					{
						// - data_를 ptr_now+2로 설정한다. (Terminal 문제부분을 빼기위해+2를 함.)
						this->data_ = (ptr_now + 1);
						this->size_ = reinterpret_cast<size_type>(ptr_end) - reinterpret_cast<size_type>(ptr_now);

						// - _wchar_change로 값을 대체한다.
						*ptr_now = _wchar_change;

						// - set string
						_dest = std::basic_string_view<T>(ptr_begin, ptr_now - ptr_begin);

						// break)
						break;
					}
				}

				// 2) failed
				_dest = std::basic_string_view<T>();
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_extract_text(size_type _length)
			{
				return this->_extract_bytes(_length * sizeof(T));
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_extract_text(std::basic_string_view<T>& _dest, size_type _length)
			{
				this->_extract_bytes(_dest, _length * sizeof(T));
			}

	// subtract) 
			template <class T>
	constexpr T&				_subtract_general()
			{
				// check) Pointer형이면 안됀다.
				static_assert(!std::is_pointer<T>::value, "must not be Pointer Type!!");

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (this->size_ < sizeof(T))
					throw std::length_error("_buffer_view overflow [0]");

				// 1) [원본_버퍼_길이]를 sizeof(T)만큼 줄인다.
				this->size_ -= sizeof(T);

				// return) [원본_버퍼_처음_값]을 리턴한다.
				return *reinterpret_cast<T*>(this->data_ + this->size_);
			}
	constexpr self_t			_subtract_bytes(size_type _length)
			{
				// check) _length가 0이하면 안된다.
				CGDK_ASSERT(_length >= 0, throw std::invalid_argument("_length is invalid [0]"));

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (this->size_ < _length)
					throw std::length_error("_buffer_view Overflow!!");

				// 1) [원본_버퍼_길이]를 _length만큼 줄인다.
				this->size_ -= _length;

				// return) [원본_버퍼_끝_포인터]
				return self_t(this->data_ + this->size_, _length);
			}
	// front) 
	constexpr element_t*		_front(int64_t _offset) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset <= static_cast<int64_t>(this->size_));

				return this->data_ + _offset;
			}
			template <class T>
			peek_tr<T>			_front(int64_t& _offset) const { return PEEK_t<self_t, T>::_do_peek(*this, _offset);}
			template <class T>
			void				_front(T& _dest, int64_t& _offset) const { PEEK_t<self_t, T>::_do_peek(_dest, *this, _offset); }

			template <class T>
	constexpr T&				_front_general(int64_t& _offset) const
			{
				// check) upper bound
				CGDK_ASSERT(_offset + sizeof(T) <= this->size_);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset + sizeof(T) <= this->size_);

				// 1) [원본_버퍼_처음_포인터]+[_offset]을 얻는다.
				auto p = this->data<T>(_offset);

				// 2) Offset을 Sizeof(T)증가시킨다.
				_offset += static_cast<int64_t>(sizeof(T));

				// return) [원본_버퍼_처음_포인터]+[_offset]값을 리턴한다.
				return *p;
			}
			template <class T>
	constexpr void				_front_general(T& _dest, int64_t& _offset) const
			{
				// check) upper bound
				CGDK_ASSERT(_offset + sizeof(T) <= this->size_);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset + sizeof(T) <= this->size_);

				// 1) [원본_버퍼_처음_포인터]+[_offset]을 얻는다.
				_dest = *this->data<_buffer_return_t<traits, T>>(_offset);

				// 2) Offset을 Sizeof(T)증가시킨다.
				_offset += static_cast<int64_t>(sizeof(T));
			}

			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_front_text(T _terminal = 0, int64_t _offset = 0)
			{
				return _buffer_view<ELEM_T>(*this + offset(_offset))._extract_text<T>(_terminal);
			}
			template <class T = char>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_front_text(std::basic_string_view<T>& _dest, T _terminal = 0, int64_t _offset = 0)
			{
				_buffer_view<ELEM_T>(*this + offset(_offset))._extract_text<T>(_dest, _terminal);
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_front_text_by_length(size_t _length, int64_t _offset) const
			{
				std::string_view dest;
				this->_front_text_by_length<T>(dest, _length, _offset);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_front_text_by_length(std::basic_string_view<T>& _dest, size_t _length, int64_t _offset) const
			{
				// check) Pointer형이면 안됀다.
				static_assert(!std::is_pointer<T>::value, "must no pointer type!");

				const size_t length = _length * sizeof(T);

				// check) upper bound
				CGDK_ASSERT(_offset + length <= this->size_);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset + length <= this->size_);

				// 1) [원본_버퍼_처음_포인터]+[_offset]을 얻는다.
				_dest = std::string_view(this->data<T>(_offset), _length);

				// 2) Offset을 Sizeof(T)증가시킨다.
				_offset += static_cast<int64_t>(length);
			}

			template <class T>
	constexpr T*				_front_string_pointer(int64_t& _offset) const
			{
				// check) Lower Bound & Upper Bound 확인
				_CGD_BUFFER_BOUND_CHECK((_offset + sizeof(COUNT_T) + sizeof(T)) <= this->size_);

				// check) [문자열_시작_위치]가 [원본_버퍼_길이]보다 길면 안됀다.
				if ((_offset + sizeof(COUNT_T)) > this->size_)
					throw std::out_of_range("string is too short!! [0]");

				// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
				auto length_string = static_cast<size_type>(*reinterpret_cast<const COUNT_T*>(this->data_ + _offset));

				// check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
				if (length_string < 1)
					throw std::length_error("string is too short!! [1]");

				// 2) [문자열_시작_위치]를 구한다.
				auto pos_begin = _offset + sizeof(COUNT_T);

				// 3) [문자열_끝_위치]를 구한다.
				auto pos_end = pos_begin + length_string * sizeof(T);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(pos_end <= this->size_);

				// check) [문자열_끝_위치]가 [원본_버퍼_길이]보다 크면 안됀다.
				if (pos_end > this->size_)
					throw std::out_of_range("string is to long!! [2]");

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (*reinterpret_cast<const T*>(this->data_ + pos_end - sizeof(T)) != 0)
					throw std::out_of_range("Invalid string! [3]");

				// 4) 최종적으로 계산된 Offset값을 업데이트한다.
				_offset = static_cast<int64_t>(pos_end);

				// return) [문자열_시작_포인터]을 리턴한다.
				return this->data<T>(pos_begin);
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string<T>>
								_front_string(int64_t& _offset) const
			{
				std::basic_string<T> dest;
				_front_string<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_front_string(std::basic_string<T>& _dest, int64_t& _offset) const
			{
				// check) Lower Bound & Upper Bound 확인
				_CGD_BUFFER_BOUND_CHECK((_offset + sizeof(COUNT_T) + sizeof(T)) <= this->size_);

				// check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
				if ((_offset + sizeof(COUNT_T) + sizeof(T)) > this->size_)
					throw std::length_error("string is too short!! [0]");

				// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
				auto length_string = static_cast<size_type>(*reinterpret_cast<COUNT_T*>(this->data_ + _offset));

				// check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
				if (length_string < 1)
					throw std::length_error("string is too short!! [1]");

				// 2) [문자열_시작_위치]를 구한다.
				auto pos_begin = _offset + sizeof(COUNT_T);

				// 3) [문자열_끝_위치]를 구한다.
				auto pos_end = pos_begin + length_string * sizeof(T);

				// check) Lower Bound & Upper Bound 확인
				_CGD_BUFFER_BOUND_CHECK(pos_end <= this->size_);

				// check) [문자열_끝_위치]가 [원본_버퍼_길이]보다 크면 안됀다.
				if (pos_end > this->size_)
					throw std::out_of_range("string is to long!! [2]");

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (*reinterpret_cast<const T*>(this->data_ + pos_end - sizeof(T)) != 0)
					throw std::out_of_range("string is too short!! [3]");

				// 4) 최종적으로 계산된 Offset값을 업데이트한다.
				_offset = static_cast<int64_t>(pos_end);

				// return) [문자열]을 리턴한다. (RVO)
				_dest = std::basic_string<T>(reinterpret_cast<T*>(this->data_ + pos_begin));
			}
	constexpr std::string_view	_front_web(int64_t& _offset) const
			{
				std::string_view dest;
				this->_front_web(dest, _offset);
				return dest;
			}

	constexpr void _front_web(std::string_view& _dest, int64_t& _offset) const
			{
				// definition)
				const uint16_t terminal_compare = ('\n' << 8) | '\r';

				// check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
				if (_offset > static_cast<int64_t>(this->size_ - 1)) throw std::out_of_range("_offset is Out of Range!! [0]");

				// declare)
				auto ptr_begin = (char*)(this->data_ + _offset);
				auto ptr_now = ptr_begin;
				auto ptr_end = ptr_begin + this->size_ - 1;

				// 1) /r/n을 찾는다.
				for (; ptr_now < ptr_end; ++ptr_now)
				{
					if (*(uint16_t*)ptr_now == terminal_compare)
					{
						// - offset을 update한다.
						_offset = static_cast<int64_t>(ptr_now + 2 - this->data_);

						// - string 정보를 설정한다.
						_dest = std::string_view(ptr_begin, ptr_now - ptr_begin);

						// return) 
						return;
					}
				}

				// 2) set
				_dest = std::string_view();
			}
			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, std::basic_string_view<T>>
								_front_string_view(int64_t& _offset) const
			{
				std::basic_string_view<T> dest;
				this->_front_string_view<T>(dest, _offset);
				return dest;
			}

			template <class T>
	constexpr std::enable_if_t<is_string_type<T>::value, void>
								_front_string_view(std::basic_string_view<T>& _dest, int64_t& _offset) const
			{
				// check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
				if (static_cast<uint64_t>(_offset + sizeof(COUNT_T) + sizeof(T)) > this->size_)
					throw std::length_error("string is too short!! [0]");

				// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
				auto length_string = static_cast<size_type>(*reinterpret_cast<const COUNT_T*>(this->data_ + _offset));

				// check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기보다 작으면 오류다!
				if (length_string < 1)
					throw std::length_error("string is too short!! [1]");

				// 2) [문자열_시작_위치]를 구한다.
				auto pos_begin = _offset + sizeof(COUNT_T);

				// 3) [문자열_끝_위치]를 구한다.
				auto pos_end = pos_begin + length_string * sizeof(T);

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(pos_end <= this->size_);

				// check) [문자열_끝_위치]가 [원본_버퍼_길이]보다 크면 안됀다.
				if (pos_end > this->size_)
					throw std::out_of_range("string is to long!! [2]");

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (*reinterpret_cast<const T*>(this->data_ + pos_end - sizeof(T)) != 0)
					throw std::out_of_range("string is too short!! [3]");

				// 4) 최종적으로 계산된 Offset값을 업데이트한다.
				_offset = static_cast<int64_t>(pos_end);

				// return) [문자열]을 리턴한다. (RVO)
				_dest = std::basic_string_view<T>(reinterpret_cast<T*>(this->data_ + pos_begin), length_string - 1);
			}
			template<class T>
	constexpr T					_front_own_ptr_container_associative(int64_t& _offset) const
			{
				T dest;
				this->_front_own_ptr_container_associative<T>(dest, _offset);
				return dest;
			}
			template<class T>
	constexpr void				_front_own_ptr_container_associative(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest = T();

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = *reinterpret_cast<COUNT_T*>(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_peek<self_t, typename T::key_type>::_do_peek(*this, offset));

					// - set value
					serializer_peek<self_t, typename T::mapped_type>::_do_peek(iter.first->second, *this, offset);
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}

			template<class T>
	constexpr T					_front_object_ptr_container_associative(int64_t& _offset) const
			{
				T dest;
				this->_front_object_ptr_container_associative<T>(dest, _offset);
				return dest;
			}
			template<class T>
	constexpr void				_front_object_ptr_container_associative(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) reset
				_dest = T();

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = *reinterpret_cast<COUNT_T*>(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_peek<self_t, typename T::key_type>::_do_peek(*this, offset));

					// - set value
					serializer_peek<self_t, typename T::mapped_type>::_do_peek(iter.first->ssecond , *this, offset);
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}
			template<class T>
	constexpr T					_front_container_associative(int64_t& _offset) const
			{
				T dest;
				this->_front_container_associative<T>(dest, _offset);
				return dest;
			}
			template<class T>
	constexpr void				_front_container_associative(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) reset
				_dest = T();

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = *reinterpret_cast<COUNT_T*>(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_peek<self_t, typename T::key_type>::_do_peek(*this, offset), typename T::mapped_type());
					
					// - set value
					serializer_peek<self_t, typename T::mapped_type>::_do_peek(iter.first->second, *this, offset);
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}

			template<class T>
	constexpr T					_extract_own_ptr_container_associative()
			{
				T dest;
				this->_extract_own_ptr_container_associative<T>(dest);
				return dest;
			}
			template<class T>
	constexpr void				_extract_own_ptr_container_associative(T& _dest)
			{
				// 1) clear container
				_dest = T();

				// 2) 
				_buffer_view<ELEM_T> buf_temp = *this;

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = buf_temp.template _extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_extract<self_t, typename T::key_type>::_do_extract(buf_temp), typename T::mapped_type());
					
					// - set value
					serializer_extract<self_t, typename T::mapped_type>::_do_extract(iter.first->second, buf_temp);
				}

				// 4) 변경된 정보 엡데이트
				*this = buf_temp;
			}
			template<class T>
	constexpr T					_extract_object_ptr_container_associative()
			{
				T dest;
				this->_extract_object_ptr_container_associative<T>(dest);
				return dest;
			}
			template<class T>
	constexpr void				_extract_object_ptr_container_associative(T& _dest)
			{
				// 1) clear container
				_dest = T();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = _extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_extract<self_t, typename T::key_type>::_do_extract(*this), typename T::mapped_type());

					// - set value
					serializer_extract<self_t, typename T::mapped_type>::_do_extract(iter.first->second, *this);
				}
			}

			template<class T>
	constexpr T					_extract_container_associative()
			{
				T dest;
				this->_extract_container_associative<T>(dest);
				return dest;
			}
			template<class T>
	constexpr void				_extract_container_associative(T& _dest)
			{
				// 1) clear container
				_dest = T();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = _extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - get key and insert
					auto iter = _dest.emplace(serializer_extract<self_t, typename T::key_type>::_do_extract(*this), typename T::mapped_type());

					// - set value
					serializer_extract<self_t, typename T::mapped_type>::_do_extract(iter.first->second, *this);
				}
			}

			template<class T, size_type X>
	constexpr std::array<T, X>	_extract_array()
			{
				std::array<T, X> dest{};
				this->_extract_array<T, X>(dest);
				return dest;
			}
			template<class T, size_type X>
	constexpr void				_extract_array(std::array<T, X>& _dest)
			{
				// 1) clear
				_dest = std::array<T, X>();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = _extract<COUNT_T>();

				// check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
				if (static_cast<size_type>(size_data) > X)
					throw std::length_error("overflow array size");

				// 3) [데이터_갯수]만큼 읽어들인다.
				for (COUNT_T i = 0; i < size_data; ++i)
				{
					_extract<T>(_dest[i]);
				}
			}

			template <class T>
	constexpr T					_extract_own_ptr_set()
			{
				T dest;
				this->_extract_own_ptr_set<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void					_extract_own_ptr_set(T& _dest)
			{
				// 1) clear 
				_dest.clear();

				// 1) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 2) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_object_ptr_set()
			{
				T dest;
				this->_extract_object_ptr_set<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_object_ptr_set(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_set()
			{
				T dest;
				_extract_set<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_set(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 1) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 2) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_container_own_ptr_list()
			{
				T dest;
				this->_extract_container_own_ptr_list<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_container_own_ptr_list(T& _dest)
			{
				// declare) 
				_dest.clear();

				// 1) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 2) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_container_object_ptr_list()
			{
				T dest;
				this->_extract_container_object_ptr_list<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_container_object_ptr_list(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 1) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 2) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_container_list()
			{
				T dest;
				this->_extract_container_list<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_container_list(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
					return;

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_container_own_ptr_array()
			{
				T dest;
				this->_extract_container_own_ptr_array<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_container_own_ptr_array(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data <= 0)
					return;

				// 3) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}
			template <class T>
	constexpr T					_extract_container_object_ptr_array()
			{
				T dest;
				this->_extract_container_object_ptr_array<T>(dest);
				return dest;
			}
			template <class T>
	constexpr void				_extract_container_object_ptr_array(T& _dest)
			{
				// 1) clear
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data <= 0)
					return;

				// 2) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_extract<self_t, typename T::value_type>::_do_extract(*this));
				}
			}

			template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, T>
								_extract_container_array()
			{
				T dest;
				this->_extract_container_array<T>(dest);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, void>
								_extract_container_array(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = this->_extract<COUNT_T>();

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data <= 0)
					return;

				// 3) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					auto& iter = _dest.emplace_back();
					serializer_extract<self_t, typename T::value_type>::_do_extract(iter, *this);
				}
			}

			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, T>
								_extract_container_array()
			{
				T dest;
				_extract_container_array<T>(dest);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, void>
								_extract_container_array(T& _dest)
			{
				// 1) clear container
				_dest.clear();

				// 2) extract [data_size]
				auto size_data = this->_extract<COUNT_T>();

				// check) return if size_data is zero or less tnan zero
				if (size_data <= 0)
					return;

				// 3) resize as [data_count]
				_dest.resize(size_data);

				// 4) extract bytes 
				this->_extract_bytes(size_data * sizeof(typename T::value_type), &_dest.front());
			}

			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, T>
								_extract_container_span()
			{
				T dest;
				_extract_container_span<T>(dest);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, void>
								_extract_container_span(T& _dest)
			{
				// check) [원본_버퍼_크기]보다 _length가 커야 한다.
				_CGD_BUFFER_BOUND_CHECK(this->size_ >= sizeof(COUNT_T));

				// 2) extract [data_size]
				typename T::size_type size_data = *reinterpret_cast<COUNT_T*>(this->data_);

				// 3) get size
				auto size_bytes = sizeof(COUNT_T) + sizeof(typename T::value_type) * size_data;

				// check) [원본_버퍼_크기]보다 _length가 커야 한다.
				_CGD_BUFFER_BOUND_CHECK(this->size_ >= size_bytes);

				// 3) get pos
				auto p = reinterpret_cast<typename T::value_type*>(this->data_ + sizeof(COUNT_T));

				// 3) set
				_dest = T{p, size_data};

				// 4) update data_ and size_
				this->data_ += size_bytes;
				this->size_ -= size_bytes;
			}

	constexpr self_t			_extract_buffer_view();
	constexpr void				_extract_buffer_view(_buffer_view<ELEM_T>& _dest);
			template<class BUFFER_T>
	constexpr _basic_buffer<BUFFER_T> _extract_basic_buffer();
			template<class BUFFER_T>
	constexpr _shared_buffer<BUFFER_T> _extract_shared_buffer();

			template <class T>
	constexpr T					_front_own_ptr_set(int64_t& _offset) const
			{
				T dest;
				this->_front_own_ptr_set<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr void				_front_own_ptr_set(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}

			template <class T>
	constexpr T					_front_object_ptr_set(int64_t& _offset) const
			{
				T dest;
				_front_object_ptr_set<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr void				_front_object_ptr_set(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 3) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 4) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_set(int64_t& _offset) const
			{
				T dest;
				_front_set<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr void					_front_set(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) 
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 4) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_container_own_ptr_list(int64_t& _offset) const
			{
				T dest;
				this->_front_container_own_ptr_list<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr T					_front_container_own_ptr_list(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 4) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_container_object_ptr_list(int64_t& _offset) const
			{
				T dest;
				this->_front_container_object_ptr_list<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr void				_front_container_object_ptr_list(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_peek<self_t, typename T::value_type>::_do_peek(offset));
				}

				// 4) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_container_list(int64_t& _offset) const
			{
				T dest;
				this->_front_container_list<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr void				_front_container_list(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 4) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_own_ptr_vector(int64_t& _offset) const
			{
				T dest;
				this->_front_own_ptr_vector<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr T					_front_own_ptr_vector(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// declare) 
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}
			template <class T>
	constexpr T					_front_object_ptr_vector(int64_t& _offset) const
			{
				T dest;
				this->_front_object_ptr_vector<T>(dest, _offset);
				return dest;
			}
			template <class S, class T>
	constexpr void				_front_object_ptr_vector(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					_dest.emplace_back(serializer_peek<self_t, typename T::value_type>::_do_peek(*this, offset));
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}

			template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, T>
								_front_container_array(int64_t& _offset) const
			{
				T dest;
				this->_front_container_array<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<!is_memcopy_able<typename T::value_type>::value, void>
								_front_container_array(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 vector를 Reserve한다.
				_dest.reserve(size_data);

				// 4) [데이터_갯수]만큼 읽어 들여 저장한다.
				for (; size_data > 0; size_data--)
				{
					// - insert now first
					auto& iter = _dest.emplace_back();

					// - read value and set
					serializer_peek<self_t, typename T::value_type>::_do_peek(iter, *this, offset);
				}

				// 5) Offset을 업데이트한다.
				_offset = offset;
			}


			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, T>
								_front_container_array(int64_t& _offset) const
			{
				T dest;
				this->_front_container_array<T>(dest, _offset);
				return dest;
			}
			template <class T>
	constexpr std::enable_if_t<is_memcopy_able<typename T::value_type>::value, void>
								_front_container_array(T& _dest, int64_t& _offset) const
			{
				// 1) 임시로 Offset (Rollback시를 위해 복사해 사용)
				auto offset = _offset;

				// 2) clear container
				_dest.clear();

				// 2) [데이터_갯수]를 얻어낸다.
				auto size_data = *(COUNT_T*)(this->data_ + offset);
				offset += sizeof(COUNT_T);

				// check) size_data가 0보다 작으면 그냥 리턴한다.
				if (size_data == COUNT_T(-1))
				{
					_offset = offset;
					return;
				}

				// 3) [데이터_갯수]만큼 vector를 Resize한다.
				_dest.resize(size_data);

				// 4) [데이터_갯수]만큼 통째로 읽어들인다.
				this->_copy_buffer<char>(offset, buffer_base<char>{ static_cast<size_type>(size_data) * sizeof(typename T::value_type), reinterpret_cast<char*>(&_dest.front()) });

				// 5) Offset을 업데이트한다.
				_offset = offset + size_data * sizeof(typename T::value_type);
			}

	// back)
	constexpr element_t*		_back(int64_t _offset) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset <= static_cast<int64_t>(this->size_));

				// return) 
				return this->data_ + this->size_ + _offset;
			}
			template <class T>
			peek_tr<T>			_back(int64_t& _offset) const { int64_t _temp = this->size_ + _offset; return PEEK_t<self_t,T>::_do_peek(*this, _temp);}
			template <class T>
	constexpr T&				_back_general(int64_t& _offset) const
			{
				// check) Pointer형이면 안됀다.
				static_assert(!std::is_pointer<T>::value, "must not be Pointer Type!!");

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset + sizeof(T) <= this->size_);

				// 1) [원본_버퍼_끝_포인터]+[_offset]을 얻는다.
				auto p = reinterpret_cast<T*>(this->data_ + this->size_ + _offset);

				// 2) Offset을 Sizeof(T)증가시킨다.
				_offset += static_cast<int64_t>(sizeof(T));

				// return) [원본_버퍼_끝_포인터]+[_offset]값을 리턴한다.
				return *p;
			}

	// begin)
	constexpr self_t			_begin(int64_t _offset = 0) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset <= static_cast<int64_t>(this->size_));

				// return) _offset 이동한 버퍼 생성후 리턴(RVO)
				return self_t(this->data_ + _offset, static_cast<size_type>((_offset < static_cast<int64_t>(this->size_)) ? this->size_ - _offset : 0));
			}
	constexpr self_t			_end(int64_t _offset = 0) const
			{
				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(_offset <= static_cast<int64_t>(this->size_));

				// return) [원본_버퍼_끝_포인터]+[_offset]한 곳을 기준으로 버퍼를 만든다.
				return self_t(this->data_ + this->size_ + _offset, static_cast<size_type>((_offset <= 0ll) ? (-_offset) : 0ll));
			}

	// etc)
			template <class T>
	constexpr COUNT_T			_get_front_string_length()
			{
				// check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
				if (sizeof(COUNT_T) > this->size_)
					throw std::length_error("_buffer_view is too short [0]");

				// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
				auto length_string = *reinterpret_cast<const COUNT_T*>(this->data_);

				// check) length가 0보다 작으면 그냥 리턴한다.
				if (length_string == COUNT_T(-1)) return COUNT_T(-1);

				// 2) String의 크기를 구한다.
				auto size_string = length_string * sizeof(T);

				// check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
				if (size_string < sizeof(T))
					throw std::length_error("string is too short!! [1]");

				// 3) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+length(String))
				auto size_data = sizeof(COUNT_T) + size_string;

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK(size_data <= this->size_);

				// check) [데이터_크기]가 [남은_원본_버퍼_길이](size_)보다 작은지 검사한다.
				if (size_data > this->size_)
					throw std::length_error("string is too short!! [2]");

				// check) 문자열의 제일 끝이 NULL인지 확인한다.
				if (*reinterpret_cast<const T*>(this->data_ + size_data - sizeof(T)) != 0)
					throw std::length_error("it's invalid string! [3]");

				// return) [문자열_시작_포인터]을 리턴한다.
				return length_string;
			}
			template <class T>
			void				_copy_buffer(int64_t _offset, buffer_base<T> _dest) const
			{
				// check) _dest.data_이 nullptr이면 안된다.
				CGDK_ASSERT(_dest.data_ != nullptr, throw std::invalid_argument("_dest.data_ is nullptr [0]"));

				// check) _dest.size_가 0이하면 안된다.
				CGDK_ASSERT(_dest.size_ >= 0, throw std::invalid_argument("_dest.size_ is invalid [1]"));

				// check) upper bound
				_CGD_BUFFER_BOUND_CHECK((_offset + _dest.size_) <= this->size_);

				// 1) 복사한다.
				memcpy(_dest.data_, this->data_ + _offset, _dest.size_);
			}
};

template <class T>
constexpr _buffer_view<T> operator ^ (const _buffer_view<T>& _lhs, std::size_t _size) noexcept
{
	return _buffer_view<T> { _lhs.data(), _size };
}

template <class T>
constexpr _buffer_view<T> to_buffer_view(std::basic_string_view<T> _string)
{
	return _buffer_view<T>(const_cast<T*>(_string.data()), _string.size() );
}

template <class T, std::size_t N>
constexpr _buffer_view<T> to_buffer_view(T(&_memory)[N])
{
	return _buffer_view<T>{ typename _buffer_view<T>::base_t{ _memory }};
}

template <class T, std::size_t N>
constexpr _buffer_view<T> to_buffer_view(T(&_memory)[N], std::size_t _size)
{
	return _buffer_view<T>{ typename _buffer_view<T>::base_t{ _memory, _size }};
}


}

#include "cgdk/buffers/_buffer_view.inl"
