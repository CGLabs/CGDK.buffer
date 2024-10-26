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
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// 1) C++ Standard Libraries and Common Includes
#include <cassert>
#include <stdexcept>
#include <type_traits>

// 2) memory
#include <memory>
#if !defined(_MSC_VER)
	#include <list>
#endif


//-----------------------------------------------------------------------------
//
// compile options
//
//  1) #define CGDK_NO_BOUND_CHECK
//     disable bound check, no assert, no throw exception on buffer overflow
// 
//  2) #define CGDK_DISABLE_ASSERT
//     enable bound check, no assert, throw exceptions on buffer overflow
// 
//  3) default
//     enable bound check, assert and then throw exceptions on buffer overflow
// 
//-----------------------------------------------------------------------------
#if defined(NDEBUG) || !defined(_DEBUG)
	#define CGDK_DISABLE_ASSERT
#endif

#if defined(CGDK_NO_BOUND_CHECK)
	#define _CGD_BUFFER_BOUND_CHECK(condition)	
#elif defined(CGDK_DISABLE_ASSERT)
	#define _CGD_BUFFER_BOUND_CHECK(condition)	if((condition) == false) { throw std::overflow_error("CGDK::shared_buffer out of memory bounding");}
#else
	#define _CGD_BUFFER_BOUND_CHECK(condition)	if((condition) == false) { CGDK_ASSERT_ON_BOUND; throw std::overflow_error("CGDK::shared_buffer out of memory bounding");}
#endif


//-----------------------------------------------------------------------------
// preprocess
//-----------------------------------------------------------------------------
// 1) C++ Standard Template Libraries
namespace std
{
	template<class, size_t> class array;

	template<class,class> class vector;
	template<class,class> class deque;
#if defined(_MSC_VER)
	template<class,class> class list;
#endif
	template<class,class> class deque;

	template<class,class,class> class set;
	template<class,class,class> class multiset;

	template<class,class,class,class> class map;
	template<class,class,class,class> class multimap;

	template<class,class,class,class> class hash_map;
	template<class,class,class,class> class hash_multimap;

	template<class,class,class,class> class unordered_set;
	template<class,class,class,class> class unordered_multiset;

	template<class,class,class,class,class> class unordered_map;
	template<class,class,class,class,class> class unordered_multimap;

#if defined(__cpp_lib_span)
	template<class,size_t> class span;
#endif
}

// 2) CGDK classes
namespace CGDK
{
	template<class,std::size_t> class static_vector;
	template<class>	class placement_vector;
	template<class,class> class circular_list;
#if defined(__CGDK_STATIC_STRING)
	template<class, std::size_t> class basic_static_string;
#endif

	template<class> class object_ptr;
	template<class> class own_ptr;

	class Ibuffer_serializable;
	template<class=char> class _buffer_view;
	using buffer_view = _buffer_view<char>;
	using const_buffer_view = _buffer_view<const char>;
	template<class = char> class _basic_buffer;
	using buffer = _basic_buffer<char>;

	template<class> class _shared_buffer;
	using shared_buffer = _shared_buffer<buffer>;
	using const_shared_buffer = _shared_buffer<const_buffer_view>;

	struct buffer_bound
	{
		const void* lower = nullptr;
		const void* upper = nullptr;
		constexpr void reset() noexcept { lower = upper = nullptr; }
	};
}

//-----------------------------------------------------------------------------
//
// configure
//
//-----------------------------------------------------------------------------
#ifndef	COUNT_T
	using COUNT_T = int32_t;
#endif

constexpr std::size_t	_XX_MAX_STRING_SIZE = 65536;
inline std::size_t _buffer_string_size_saturate(std::size_t _a) { return (_a < _XX_MAX_STRING_SIZE) ? _a : _XX_MAX_STRING_SIZE; }


//-----------------------------------------------------------------------------
//
// General Definitions
//
//-----------------------------------------------------------------------------
// 1) CGDK Assert
#if !defined(_DEBUG) && defined(NDEBUG)
	#define	CGDK_ASSERT(condition, ...)	
	#define	CGDK_ASSERT_ERROR
#else
	#define	CGDK_ASSERT(condition, ...)		if ((condition) == false) { assert(condition); __VA_ARGS__;}
	#define	CGDK_ASSERT_ERROR				/*assert(false);*/
#endif

// 2) ASSERT on bound check
#if defined(_CGDK_NO_ASSERT_ON_BOUND_CHECK) || defined(NDEBUG)
	#define	CGDK_ASSERT_ON_BOUND
#else
	#define	CGDK_ASSERT_ON_BOUND			assert(false)
#endif

constexpr char __hex_to_ascii(uint8_t _data) noexcept { return (_data < 10) ? (_data + '0') : (_data + ('a' - 10)); }


namespace CGDK
{
//-----------------------------------------------------------------------------
// throwable classes
//-----------------------------------------------------------------------------
//namespace throwable
//{
//	//class buffer_exception : public Nthrowable
//	//{
//	//public:
//	//			buffer_exception() noexcept : Nthrowable(), m_offset(0)  {}
//	//			buffer_exception(std::size_t _offset, const std::string& _description) noexcept : CGDK::Nthrowable(_description), m_offset(_offset) {}
//	//			buffer_exception(std::size_t _offset, std::string&& _description) noexcept : CGDK::Nthrowable(std::forward<std::string>(_description)), m_offset(_offset) {}
//	//			buffer_exception(std::size_t _offset, result_code _reason, intptr_t _param = 0) noexcept : CGDK::Nthrowable(_reason, _param), m_offset(_offset) {}
//	//			buffer_exception(std::size_t _offset, result_code _reason, intptr_t _param, const std::string& _description) noexcept : CGDK::Nthrowable(_reason, _param, _description), m_offset(_offset) {}
//	//			buffer_exception(std::size_t _offset, result_code _reason, intptr_t _param, std::string&& _description) noexcept : CGDK::Nthrowable(_reason, _param, std::move(_description)), m_offset(_offset) {}
//	//	virtual	~buffer_exception() noexcept {}
//
//	//public:
//	//			auto			offset() const noexcept { return m_offset; }
//	//private:
//	//			std::size_t		m_offset;
//	//};
//
//	class buffer_exception : public std::exception
//	{
//	public:
//				buffer_exception() noexcept : std::exception(), m_offset(0)  {}
//				//buffer_exception(std::size_t _offset, const std::string& _description) noexcept : std::exception(_description), m_offset(_offset) {}
//				//buffer_exception(std::size_t _offset, std::string&& _description) noexcept : std::exception(std::forward<std::string>(_description)), m_offset(_offset) {}
//				buffer_exception(std::size_t _offset, int _reason, intptr_t _param = 0) noexcept : std::exception(/*_reason, _param*/), m_offset(_offset) {}
//				//buffer_exception(std::size_t _offset, int _reason, intptr_t _param, const std::string& _description) noexcept : std::exception(_reason, _param, _description), m_offset(_offset) {}
//				//buffer_exception(std::size_t _offset, int _reason, intptr_t _param, std::string&& _description) noexcept : std::exception(_reason, _param, std::move(_description)), m_offset(_offset) {}
//		virtual	~buffer_exception() noexcept {}
//
//	public:
//				auto			offset() const noexcept { return m_offset; }
//	private:
//				std::size_t		m_offset;
//	};
//
//	class invalid_buffer : public buffer_exception
//	{
//	public:
//				invalid_buffer(std::size_t _offset, int _reason, intptr_t _param, const std::string& _description) noexcept : buffer_exception(/*_offset, _reason, _param, _description*/) {}
//				invalid_buffer(std::size_t _offset, int _reason, intptr_t _param, std::string&& _description) noexcept : buffer_exception(/*_offset, _reason, _param, std::forward<std::string>(_description)*/) {}
//	};
//
//	class invalid_string : public buffer_exception
//	{
//	public:
//				invalid_string(std::size_t _offset, int _reason, intptr_t _param, const std::string& _description) noexcept : buffer_exception(/*_offset, _reason, _param, _description*/) {}
//				invalid_string(std::size_t _offset, int _reason, intptr_t _param, std::string&& _description) noexcept : buffer_exception(/*_offset, _reason, _param, std::forward<std::string>(_description)*/) {}
//	};
//}


//-----------------------------------------------------------------------------
// definitions for append(<<) and Extract(>>)
//-----------------------------------------------------------------------------
// 1) Skip
class skip
{
public:
	constexpr skip(int64_t _amount) noexcept : amount(_amount) {}
public:
	int64_t	amount;
};

// 2) offset
class offset : public skip
{
public:
	constexpr offset() noexcept : skip(0) {}
	constexpr offset(const offset& _offset) noexcept : skip(_offset.amount) {}
	constexpr offset(int64_t _offset) noexcept : skip(_offset) {}

public:
	constexpr bool	operator==(const offset& _rhs) const noexcept { return this->amount == _rhs.amount; }
	constexpr bool	operator!=(const offset& _rhs) const noexcept { return this->amount != _rhs.amount; }
	constexpr bool	operator>=(const offset& _rhs) const noexcept { return this->amount >= _rhs.amount; }
	constexpr bool	operator> (const offset& _rhs) const noexcept { return this->amount >  _rhs.amount; }
	constexpr bool	operator<=(const offset& _rhs) const noexcept { return this->amount <= _rhs.amount; }
	constexpr bool	operator< (const offset& _rhs) const noexcept { return this->amount <  _rhs.amount; }

	constexpr bool	operator==(int64_t _rhs) const noexcept { return this->amount == _rhs; }
	constexpr bool	operator!=(int64_t _rhs) const noexcept { return this->amount != _rhs; }
	constexpr bool	operator>=(int64_t _rhs) const noexcept { return this->amount >= _rhs; }
	constexpr bool	operator> (int64_t _rhs) const noexcept { return this->amount > _rhs; }
	constexpr bool	operator<=(int64_t _rhs) const noexcept { return this->amount <= _rhs; }
	constexpr bool	operator< (int64_t _rhs) const noexcept { return this->amount < _rhs; }

	constexpr offset& operator+=(const offset& _rhs) noexcept { this->amount += _rhs.amount; return *this; }
	constexpr offset& operator+=(int64_t _rhs) noexcept { amount += _rhs; return *this; }
	constexpr offset& operator-=(const offset& _rhs) noexcept { this->amount += _rhs.amount; return *this; }
	constexpr offset& operator-=(int64_t _rhs) noexcept { amount += _rhs; return *this; }
	constexpr offset& operator*=(const offset& _rhs) noexcept { this->amount += _rhs.amount; return *this; }
	constexpr offset& operator*=(int64_t _rhs) noexcept { amount += _rhs; return *this; }
	constexpr offset& operator/=(const offset& _rhs) noexcept { this->amount += _rhs.amount; return *this; }
	constexpr offset& operator/=(int64_t _rhs) noexcept { amount += _rhs; return *this; }

	constexpr operator int64_t& () { return this->amount; }
	constexpr operator const int64_t& () const { return this->amount; }
};



// 3) size
class size : public skip
{
public:
	constexpr size(std::size_t _amount) noexcept : skip(_amount) {}
};

// 4) 
template<class...> struct enable_if_exist { using type = void;};
template<class, class = void>	struct is_iterator : std::false_type {};
template<class _Ty>				struct is_iterator<_Ty*> : std::true_type {};
template<class _Ty>				struct is_iterator<_Ty, typename enable_if_exist<
	typename _Ty::iterator_category,
	typename _Ty::value_type,
	typename _Ty::difference_type,
	typename _Ty::pointer,
	typename _Ty::reference
>::type>
: std::true_type
{
};

template<class I, class TENABLE = std::enable_if_t<is_iterator<I>::value, void>>
class _ITERATOR
{
public:
	_ITERATOR(const I& _iter_begin, const I& _iter_end) noexcept : iterFirst(_iter_begin), iterLast(_iter_end) {}
public:
	I		iterFirst;
	I		iterLast;
};

template<class I>
std::enable_if_t<is_iterator<I>::value, _ITERATOR<I,void>>
ITERATOR(const I& _iter_begin, const I& _iter_end)
{
	return _ITERATOR<I, void>(_iter_begin, _iter_end);
}


//-----------------------------------------------------------------------------
// text<T>
//-----------------------------------------------------------------------------
// 3) Web String
struct WEB {};

// 3) Web String
struct WEB_MODIFY {};

// 4) Text
template <class T>
struct text
{
public:
	using	value_type = T;

public:
	constexpr text() noexcept {}
	constexpr text(const text& _rhs) noexcept : p(_rhs.p) {}
	constexpr text(std::basic_string_view<T> _str) noexcept : p(_str) {}
	constexpr text(const std::basic_string<T>& _str) noexcept : p(_str) {}
#if defined(__CGDK_STATIC_STRING)
	template <std::size_t N>
	constexpr text(CGDK::static_string<N> _str) noexcept : p(_str) {}
#endif
	template <std::size_t N>
	constexpr text(const T(&_str)[N]) noexcept : p{ _str, N } {}
	constexpr text(const T* _str) noexcept : p(_str) {}

public:
	constexpr std::size_t	bytes() const noexcept { return p.size() * sizeof(T); }

public:
	constexpr text&	operator=(const text& _rhs) noexcept { p = _rhs.p; return *this; }
	constexpr text&	operator=(const std::basic_string_view<T> _rhs) noexcept { p = _rhs; return *this; }

	constexpr bool	operator==(const text& _rhs) const noexcept						{ return p == _rhs.p; }
	constexpr bool	operator==(const std::basic_string_view<T>& _rhs) const noexcept{ return p == _rhs.p; }
	constexpr bool	operator!=(const text& _rhs) const noexcept						{ return p != _rhs.p; }
	constexpr bool	operator!=(const std::basic_string_view<T>& _rhs) const noexcept{ return p != _rhs.p; }
	constexpr bool	operator>=(const text& _rhs) const noexcept						{ return p >= _rhs.p; }
	constexpr bool	operator>=(const std::basic_string_view<T>& _rhs) const noexcept{ return p >= _rhs.p; }
	constexpr bool	operator> (const text& _rhs) const noexcept						{ return p >  _rhs.p; }
	constexpr bool	operator> (const std::basic_string_view<T>& _rhs) const noexcept{ return p >  _rhs.p; }
	constexpr bool	operator<=(const text& _rhs) const noexcept						{ return p <= _rhs.p; }
	constexpr bool	operator<=(const std::basic_string_view<T>& _rhs) const noexcept{ return p <= _rhs.p; }
	constexpr bool	operator< (const text& _rhs) const noexcept						{ return p <  _rhs.p; }
	constexpr bool	operator< (const std::basic_string_view<T>& _rhs) const noexcept{ return p <  _rhs.p; }
	constexpr 		operator std::basic_string_view<T>() const noexcept				{ return p; }
public:
	std::basic_string_view<T>	p;
};

template <class T>
constexpr text<T> _text(std::basic_string_view<T> _str) noexcept
{
	return text<T>(_str);
}

template <class T>
constexpr text<T> _text(const T* _str) noexcept
{
	return text<T>(_str);
}


using TEXT_CHAR = text<char>;
using TEXT_WCHAR = text<wchar_t>;
using TEXT_WEB = TEXT_CHAR;

inline text<char>		operator "" _text(const char* _text, std::size_t _size) noexcept { return text<char>(std::string_view(_text, _size));}
inline text<wchar_t>	operator "" _text(const wchar_t* _text, std::size_t _size) noexcept { return text<wchar_t>(std::wstring_view(_text, _size));}
#if defined(__cpp_char8_t)
inline text<char8_t> 	operator "" _text(const char8_t* _text, std::size_t _size) noexcept { return text<char8_t>(std::u8string_view(_text, _size)); }
#else
//inline text<uint8_t> 	operator "" _text(const uint8_t* _text, std::size_t _size) noexcept { return text<uint8_t>(std::basic_string_view<uint8_t>(_text, _size)); }
#endif
inline text<char16_t>	operator "" _text(const char16_t* _text, std::size_t _size) noexcept { return text<char16_t>(std::u16string_view(_text, _size));}
inline text<char32_t>	operator "" _text(const char32_t* _text, std::size_t _size) noexcept { return text<char32_t>(std::u32string_view(_text, _size));}


//-----------------------------------------------------------------------------
// Ibuffer_serializable
//-----------------------------------------------------------------------------
#define	DEFINE_BUFFER_SERIALIZE(...) \
				virtual	void	process_serialize_in(CGDK::buffer_view& _buffer) override { _buffer._extract_multi(__VA_ARGS__); }\
				virtual	void	process_serialize_out(CGDK::buffer& _buffer) override { _buffer._append_multi(__VA_ARGS__); }\
				virtual std::size_t	process_size_of() const override { return CGDK::get_size_of(__VA_ARGS__);}

// 1) serializable 
class Ibuffer_serializable
{
public:
			void		serialize_in(buffer_view& _buffer) { process_serialize_in(_buffer);}
			void		serialize_out(buffer& _buffer) { process_serialize_out(_buffer); }
			std::size_t	get_size_of() const { return process_size_of(); }
	template <class T>
	static	std::size_t	get_size_of(const T& _source);

protected:
	virtual	void		process_serialize_in(buffer_view& _buffer) = 0;
	virtual	void		process_serialize_out(buffer& _buffer) = 0;
	virtual std::size_t	process_size_of() const = 0;
};

#define ENABLE_STRUCT_SERIALIZABLE	public: using enable_struct_serialize = std::true_type;
#define DISABLE_STRUCT_SERIALIZABLE	public: using enable_struct_serialize = std::false_type;


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// 1) is tupple
template<class T> struct is_tuple : public std::false_type {};
template<class... TA> struct is_tuple<std::tuple<TA...>> : public std::true_type {};

// 2) is reserved class
template<class T>	struct is_reserved_class : public std::false_type {};
template<class T>	struct is_reserved_class<text<T>> : public std::true_type {};
template <class T> constexpr bool is_reserved_class_v = is_reserved_class<T>::value;

// 3) is text classes
template<class T>	struct is_text : public std::false_type {};
template<class T>	struct is_text<text<T>> : public std::true_type {};

// 3) is std::string_view
template <class T>
struct is_std_string_view
{
	static const bool value  = (std::is_base_of_v<std::string_view, T>
							|| std::is_base_of_v<std::wstring_view, T>
						#if defined(__cpp_char8_t)
							|| std::is_base_of_v<std::u8string_view, T>
						#else
							|| std::is_base_of_v<std::basic_string_view<uint8_t>, T>
						#endif
							|| std::is_base_of_v<std::u16string_view, T>
							|| std::is_base_of_v<std::u32string_view, T>);
};
template <class T> constexpr bool is_std_string_view_v = is_std_string_view<T>::value;

// 4) is std::string
template <class T>
struct is_std_string
{
	static const bool value  = std::is_base_of_v<std::string, T>
							|| std::is_base_of_v<std::wstring, T>
						#ifdef __cpp_char8_t
							|| std::is_base_of_v<std::u8string, T>
						#else
							|| std::is_base_of_v<std::basic_string<uint8_t>, T>
						#endif
							|| std::is_base_of_v<std::u16string, T>
							|| std::is_base_of_v<std::u32string, T>;
};
template <class T> constexpr bool is_std_string_v = is_std_string<T>::value;

// 4) is std::static_string
#if defined(__CGDK_STATIC_STRING)
template<class T> struct is_static_string : public std::false_type {};
template<std::size_t N> struct is_static_string<static_string<N>> : public std::true_type {};
template<std::size_t N> struct is_static_string<static_wstring<N>> : public std::true_type {};
template<std::size_t N> struct is_static_string<static_u8string<N>> : public std::true_type {};
template<std::size_t N> struct is_static_string<static_u16string<N>> : public std::true_type {};
template<std::size_t N> struct is_static_string<static_u32string<N>> : public std::true_type {};
template <class T> constexpr bool is_static_string_v = is_static_string<T>::value;
#endif

// 5) object_ptr<T>
template<class T> struct is_object_ptr : public std::false_type {};
template<class A> struct is_object_ptr<object_ptr<A>> : public std::true_type {};
template <class T> constexpr bool is_object_ptr_v = is_object_ptr<T>::value;

// 6) own_ptr<T>
template<class T> struct is_own_ptr : public std::false_type {};
template<class A> struct is_own_ptr<own_ptr<A>> : public std::true_type {};
template <class T> constexpr bool is_own_ptr_v = is_own_ptr<T>::value;

// 7) is struct serializable
template <class T, class F = void> struct is_struct_serializable : public std::false_type {};
template <class T>
struct is_struct_serializable<T, std::enable_if_t<T::enable_struct_serialize::value && !std::is_base_of_v<Ibuffer_serializable, T>>>
{
	static const bool value = true;
};
template <class T> constexpr bool is_struct_serializable_v = is_struct_serializable<T>::value;

// 8) memcpy_able
template <class T> struct is_memcopy_able
{
	static const bool value  = std::is_trivially_copyable<T>::value
							&& !std::is_pointer<T>::value
							&& !is_std_string_view<T>::value
							&& !is_std_string<T>::value
							&& !is_reserved_class<T>::value
							&& !is_struct_serializable<T>::value;
};
template <class T> constexpr bool is_memcopy_able_v = is_memcopy_able<T>::value;

// 9) is own_ptr<T> and serializable
template <class T> struct is_own_ptr_serialziable				{ static const bool value = false; };
template <class T> struct is_own_ptr_serialziable<own_ptr<T>>	{ static const bool value = std::is_base_of_v<Ibuffer_serializable, T>; };
template <class T> constexpr bool is_own_ptr_serialziable_v = is_own_ptr_serialziable<T>::value;

// 10) ...
// linear container<T>)
template<class T> struct is_linear_container : public std::false_type {};
template<class A, class B> struct is_linear_container<std::list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::deque<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<circular_list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::list<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::deque<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<circular_list<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::list<own_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::deque<own_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<circular_list<own_ptr<A>, B>> : public std::false_type {};

// linear container<object_ptr<T>>)
template<class T> struct is_linear_object_ptr_container : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::deque<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<circular_list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::list<object_ptr<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::deque<object_ptr<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_object_ptr_container<circular_list<object_ptr<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::list<own_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<std::deque<own_ptr<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_object_ptr_container<circular_list<own_ptr<A>, B>> : public std::false_type {};

// linear container<own_ptr<T>>)
template<class T> struct is_linear_own_ptr_container : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::list<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::deque<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<circular_list<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::list<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::deque<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<circular_list<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::list<own_ptr<A>, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_own_ptr_container<std::deque<own_ptr<A>, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_own_ptr_container<circular_list<own_ptr<A>, B>> : public std::true_type {};

// linear container<shared_buffer>)
template<class T>					struct is_linear_container_with_buffer : public std::false_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::vector<_buffer_view<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::vector<_basic_buffer<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::list<_buffer_view<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::list<_basic_buffer<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::deque<_buffer_view<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<std::deque<_basic_buffer<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<circular_list<_buffer_view<B>, A...>> : public std::true_type {};
template<class B, class... A>		struct is_linear_container_with_buffer<circular_list<_basic_buffer<B>, A...>> : public std::true_type {};
template<class B, std::size_t N>	struct is_linear_container_with_buffer<static_vector<_buffer_view<B>, N>> : public std::true_type {};
template<class B, std::size_t N>	struct is_linear_container_with_buffer<static_vector<_basic_buffer<B>, N>> : public std::true_type {};

// linear container<T>
template<class T>					struct is_linear_container_with_reserve : public std::false_type {};
template<class A, class B>			struct is_linear_container_with_reserve<std::vector<A, B>> : public std::true_type {};
template<class A, std::size_t B>	struct is_linear_container_with_reserve<static_vector<A, B>> : public std::true_type {};
template<class A, class B>			struct is_linear_container_with_reserve<std::vector<object_ptr<A>, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_container_with_reserve<static_vector<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B>			struct is_linear_container_with_reserve<std::vector<own_ptr<A>, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_container_with_reserve<static_vector<own_ptr<A>, B>> : public std::false_type {};

// linear container<object_ptr<T>>
template<class T>					struct is_linear_object_ptr_container_with_reserve : public std::false_type {};
template<class A, class B>			struct is_linear_object_ptr_container_with_reserve<std::vector<A, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_object_ptr_container_with_reserve<static_vector<A, B>> : public std::false_type {};
template<class A, class B>			struct is_linear_object_ptr_container_with_reserve<std::vector<object_ptr<A>, B>> : public std::true_type {};
template<class A, std::size_t B>	struct is_linear_object_ptr_container_with_reserve<static_vector<object_ptr<A>, B>> : public std::true_type {};
template<class A, class B>			struct is_linear_object_ptr_container_with_reserve<std::vector<own_ptr<A>, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_object_ptr_container_with_reserve<static_vector<own_ptr<A>, B>> : public std::false_type {};

// linear container<own_ptr<T>>
template<class T>					struct is_linear_own_ptr_container_with_reserve : public std::false_type {};
template<class A, class B>			struct is_linear_own_ptr_container_with_reserve<std::vector<A, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_own_ptr_container_with_reserve<static_vector<A, B>> : public std::false_type {};
template<class A, class B>			struct is_linear_own_ptr_container_with_reserve<std::vector<object_ptr<A>, B>> : public std::false_type {};
template<class A, std::size_t B>	struct is_linear_own_ptr_container_with_reserve<static_vector<object_ptr<A>, B>> : public std::false_type {};
template<class A, class B>			struct is_linear_own_ptr_container_with_reserve<std::vector<own_ptr<A>, B>> : public std::true_type {};
template<class A, std::size_t B>	struct is_linear_own_ptr_container_with_reserve<static_vector<own_ptr<A>, B>> : public std::true_type {};

// set container<T>)
template<class T> struct is_set_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::set<A, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<A, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_container<std::set<object_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<object_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::set<own_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<own_ptr<A>, B, C>> : public std::false_type {};

// std::set<object_ptr<T>>, std::multiset<object_ptr<T>>, ...
template<class T> struct is_set_object_ptr_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::set<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::multiset<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::set<object_ptr<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::multiset<object_ptr<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::set<own_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_object_ptr_container<std::multiset<own_ptr<A>, B, C>> : public std::false_type {};

// std::set<own_ptr<T>>, std::multiset<own_ptr<T>>, ...
template<class T> struct is_set_own_ptr_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::set<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::multiset<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::set<object_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::multiset<object_ptr<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::set<own_ptr<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_own_ptr_container<std::multiset<own_ptr<A>, B, C>> : public std::true_type {};

// associated container<T>)
template<class T> struct is_associative_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, object_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, object_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, own_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, own_ptr<B>, C, D, E>> : public std::false_type {};

// associated container<object_ptr<T>>)
template<class T> struct is_associative_object_ptr_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::map<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::multimap<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_set<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_multiset<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_map<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_multimap<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::map<A, object_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::multimap<A, object_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_set<A, object_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_multiset<A, object_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_map<A, object_ptr<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_multimap<A, object_ptr<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::map<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::multimap<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_set<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_object_ptr_container<std::unordered_multiset<A, own_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_map<A, own_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_object_ptr_container<std::unordered_multimap<A, own_ptr<B>, C, D, E>> : public std::false_type {};

// associated container<own_ptr<T>>)
template<class T> struct is_associative_own_ptr_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::map<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::multimap<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_set<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_multiset<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_map<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_multimap<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::map<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::multimap<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_set<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_multiset<A, object_ptr<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_map<A, object_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_multimap<A, object_ptr<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::map<A, own_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::multimap<A, own_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_set<A, own_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_own_ptr_container<std::unordered_multiset<A, own_ptr<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_map<A, own_ptr<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_own_ptr_container<std::unordered_multimap<A, own_ptr<B>, C, D, E>> : public std::true_type {};


template<class T> struct is_buffer_type : public std::false_type {};
template<class X> struct is_buffer_type<_buffer_view<X>> : public std::true_type {};
template<class X> struct is_buffer_type<_basic_buffer<X>> : public std::true_type {};
template<class X> struct is_buffer_type<_shared_buffer<X>> : public std::true_type {};
template <class T> constexpr bool is_buffer_type_v = is_buffer_type<T>::value;

// 11) is basic_type
template <class T> struct is_basic_type
{
	static const bool value	 = /*std::is_trivially_copyable<T>::value*/
							(!std::is_class<T>::value || std::is_trivially_copyable<T>::value || std::is_union<T>::value)
							&& !is_std_string_view<T>::value
							&& !is_std_string<T>::value
							&& !std::is_base_of_v<Ibuffer_serializable, T>
							&& !is_struct_serializable_v<T>
							&& !is_linear_container<T>::value
							&& !is_linear_object_ptr_container<T>::value
							&& !is_linear_own_ptr_container<T>::value
							&& !is_linear_container_with_reserve<T>::value
							&& !is_linear_object_ptr_container_with_reserve<T>::value
							&& !is_linear_own_ptr_container_with_reserve<T>::value
							&& !is_set_container<T>::value
							&& !is_set_object_ptr_container<T>::value
							&& !is_set_own_ptr_container<T>::value
							&& !is_associative_container<T>::value
							&& !is_associative_object_ptr_container<T>::value
							&& !is_associative_own_ptr_container<T>::value
							&& !std::is_pointer<T>::value
							&& !is_buffer_type_v<T>
							&& !is_tuple<T>::value
							&& !is_reserved_class<T>::value;
};
template <class T> constexpr bool is_basic_type_v = is_basic_type<T>::value;

// 12) is general serializable
template <class T> struct is_general_serializable
{
#if defined(__CGDK_STATIC_STRING)
	static const bool value	 = is_basic_type_v<T>
							|| is_static_string_v<T>;
#else
	static const bool value = is_basic_type_v<T>;
#endif
};
template <class T> constexpr bool is_general_serializable_v = is_general_serializable<T>::value;



//-----------------------------------------------------------------------------
// string type
//-----------------------------------------------------------------------------
template<class T> struct _is_string_type : public std::false_type {};
template<> struct _is_string_type<char> : public std::true_type {};
template<> struct _is_string_type<wchar_t> : public std::true_type {};
#ifdef __cpp_char8_t
template<> struct _is_string_type<char8_t> : public std::true_type {};
#else
template<> struct _is_string_type<uint8_t> : public std::true_type {};
#endif
template<> struct _is_string_type<char16_t> : public std::true_type {};
template<> struct _is_string_type<char32_t> : public std::true_type {};
template<> struct _is_string_type<const char> : public std::true_type {};
template<> struct _is_string_type<const wchar_t> : public std::true_type {};
#ifdef __cpp_char8_t
template<> struct _is_string_type<const char8_t> : public std::true_type {};
#else
template<> struct _is_string_type<const uint8_t> : public std::true_type {};
#endif
template<> struct _is_string_type<const char16_t> : public std::true_type {};
template<> struct _is_string_type<const char32_t> : public std::true_type {};
template<class T> 
using is_string_type = _is_string_type<std::remove_const_t<T>>;
template <class T> constexpr bool is_string_type_v = is_string_type<T>::value;

template<class T> struct _is_string_pointer_type : public std::false_type {};
template<> struct _is_string_pointer_type<char*> : public std::true_type {};
template<> struct _is_string_pointer_type<wchar_t*> : public std::true_type {};
#ifdef __cpp_char8_t
template<> struct _is_string_pointer_type<char8_t*> : public std::true_type {};
#else
template<> struct _is_string_pointer_type<uint8_t*> : public std::true_type {};
#endif
template<> struct _is_string_pointer_type<char16_t*> : public std::true_type {};
template<> struct _is_string_pointer_type<char32_t*> : public std::true_type {};
template<> struct _is_string_pointer_type<const char*> : public std::true_type {};
template<> struct _is_string_pointer_type<const wchar_t*> : public std::true_type {};
#ifdef __cpp_char8_t
template<> struct _is_string_pointer_type<const char8_t*> : public std::true_type {};
#else
template<> struct _is_string_pointer_type<const uint8_t*> : public std::true_type {};
#endif
template<> struct _is_string_pointer_type<const char16_t*> : public std::true_type {};
template<> struct _is_string_pointer_type<const char32_t*> : public std::true_type {};
template<class T>
using is_string_pointer_type = _is_string_pointer_type<std::remove_const_t<T>>;
template <class T> constexpr bool is_string_pointer_type_v = is_string_pointer_type<T>::value;


//-----------------------------------------------------------------------------
// base
//-----------------------------------------------------------------------------
template<class B, class T, class FLAG = void> class serializer_prepend
							{	using TX = std::remove_const_t<T>;
								public: using type = TX&;
								template<class S> constexpr static type _do_prepend(S& _s, const TX& _data) { return _s.template _prepend_general<TX> (_data); }
							};
template<class B, class T, class FLAG = void> class serializer_append
							{	using TX = std::remove_const_t<T>;
								public: using type = TX&;
								template<class S> constexpr static type _do_append(S& _s, const TX& _data) { return _s.template _append_general<TX> (_data); }
							};
template<class B, class T, class FLAG = void> class serializer_extract
							{	using T_BASE = std::remove_const_t<T>;
								using TX = typename _buffer_return<typename B::traits, T_BASE>::type;
								public: using type = TX&;
								public: using const_type = const TX&;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_general<TX>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_general<T_BASE>(_dest); }
							};
template<class B, class T, class FLAG = void> class serializer_peek
							{	using T_BASE = std::remove_const_t<T>;
								using TX = typename _buffer_return<typename B::traits, T_BASE>::type;
								public: using type = TX&;
								public: using const_type = const TX&;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_general<TX> (_offset); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { return _s.template _front_general<T_BASE> (_dest, _offset); }
							};
template<class T, class FLAG = void> class serializer_size_of
							{	public:
								constexpr static std::size_t  _get_append_size(const T&) { return sizeof(T);}
								template<class S>
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { auto size = sizeof(T); if((_buffer.size() - _offset) < size) throw std::exception(); return size;}
							};

template<class B, class T> using APPD_t	 = serializer_append<B, std::remove_reference_t<std::remove_const_t<T>>>;
template<class B, class T> using APPD_tr = typename APPD_t<B, T>::type;

template<class B, class T> using PRPD_t	 = serializer_prepend<B, std::remove_reference_t<std::remove_const_t<T>>>;
template<class B, class T> using PRPD_tr = typename PRPD_t<B, T>::type;

template<class B, class T> using EXTR_t	 = serializer_extract<B, std::remove_reference_t<std::remove_const_t<T>>>;
template<class B, class T> using EXTR_tr = typename EXTR_t<B, T>::type;

template<class B, class T> using PEEK_t	 = serializer_peek<B, std::remove_reference_t<std::remove_const_t<T>>>;
template<class B, class T> using PEEK_tr = typename PEEK_t<B, T>::type;

template<class T> using SIZE_OF_t = serializer_size_of<std::remove_reference_t<std::remove_const_t<T>>>;


//-----------------------------------------------------------------------------
//   get_size_of function
//-----------------------------------------------------------------------------
template<class TRETURN = std::size_t, class T>
constexpr TRETURN get_size_of(const T& _object)
{
	return static_cast<TRETURN>(SIZE_OF_t<T>::_get_append_size(_object));
}

template<class TRETURN = std::size_t, class TFIRST, class TSECOND, class... TREST>
constexpr TRETURN get_size_of(const TFIRST& _first, const TSECOND& _second, const TREST&... _rest)
{
	return static_cast<TRETURN>(SIZE_OF_t<TFIRST>::_get_append_size(_first) + get_size_of<TRETURN, TSECOND, TREST...>(_second, _rest...));
}

template <class T>
std::size_t Ibuffer_serializable::get_size_of(const T& _source)
{
	return CGDK::get_size_of(_source);
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// class for prepend)
template<class B, class T,class E>	class serializer_prepend<B, _ITERATOR<T,E>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const _ITERATOR<T,E>& _data) { return _s.template _prepend_iterator(_data.iterFirst, _data.iterLast);}
								template<class S> constexpr static type _do_prepend(S& _s, _ITERATOR<T,E>&& _data) { return _s.template _prepend_iterator(_data.iterFirst, _data.iterLast);}
							};
template<class B, class T>	class serializer_prepend<B, std::initializer_list<T>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;;
								template<class S> constexpr static type _do_prepend(S& _s, const std::initializer_list<TX>& _data){ return _s.template _prepend_initializer_list(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, std::initializer_list<TX>&& _data){ return _s.template _prepend_initializer_list(_data);}
							};

// class for append)
template<class B, class T,class E>	class serializer_append<B, _ITERATOR<T,E>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const _ITERATOR<T,E>& _data) { return _s.template _append_iterator(_data.iterFirst, _data.iterLast);}
								template<class S> constexpr static type _do_append(S& _s, _ITERATOR<T,E>&& _data) { return _s.template _append_iterator(_data.iterFirst, _data.iterLast);}
							};
template<class B, class T>			class serializer_append<B, std::initializer_list<T>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::initializer_list<TX>& _data){ return _s.template _append_initializer_list(_data);;}
								template<class S> constexpr static type _do_append(S& _s, std::initializer_list<TX>&& _data) { return _s.template _append_initializer_list(_data);}
							};


//-----------------------------------------------------------------------------
// array
//-----------------------------------------------------------------------------
// serializer_prepend - T[N]
template<class B, class T, std::size_t N> class serializer_prepend<B, T[N], void>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const TX (&_data)[N]) { return _s.template _prepend_array<TX>((TX*)_data, N);}
								template<class S> constexpr static type _do_prepend(S& _s, TX (&&_data)[N]) { return _s.template _prepend_array<TX>((TX*)_data, N);}
							};
template<class B, class T, std::size_t N> class serializer_append<B, T[N], void>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX(&_data)[N]) { return _s.template _append_array<TX,N>((TX*)_data);}
								template<class S> constexpr static type _do_append(S& _s, TX(&&_data)[N]) { return _s.template _append_array<TX,N>((TX*)_data);}
							};

// serializer_extract - T[N] & !is_string_type_v<T> && !is_string_pointer_type_v<T>
template<class B, class T, std::size_t N> class serializer_extract<B, T[N], std::enable_if_t<!is_string_type_v<T> && !is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::array<TX, N>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_array<TX,N>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_array<TX, N>(_dest); }
							};

template<class B, class T, std::size_t N> class serializer_peek<B, T[N], std::enable_if_t<!is_string_type_v<T> && !is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::array<TX, N>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + _offset; auto temp = tb.template _extract_array<TX,N>(); _offset = tb.data() - _s.data(); return temp;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + _offset; tb.template _extract_array<D,TX,N>(_dest); _offset = tb.data() - _s.data();}
							};

// serializer_extract - T[N] & is_string_type_v<T>
template<class B, class T, std::size_t N> class serializer_extract<B, T[N], std::enable_if_t<is_string_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_string_view<TX>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_string_view<TX>(_dest);}
							};
template<class B, class T, std::size_t N> class serializer_peek<B, T[N], std::enable_if_t<is_string_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_string_view<TX>(); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_string_view<TX>(_dest); }
							};

// serializer_extract - T[N] & is_string_pointer_type_v<T>
template<class B, class T, std::size_t N> class serializer_extract<B, T[N], std::enable_if_t<is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::array<std::basic_string_view<TX>, N>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_array<std::basic_string_view<TX>,N>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_array<D, std::basic_string_view<TX>,N>(_dest);}
							};
template<class B, class T, std::size_t N> class serializer_peek<B, T[N], std::enable_if_t<is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::array<std::basic_string_view<TX>, N>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); auto temp = tb.template _extract_array<std::basic_string_view<TX>,N>(); _offset = tb.data() - _s.data(); return temp;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); tb.template _extract_array<D,std::basic_string_view<TX>,N>(_dest); _offset = tb.data() - _s.data();}
							};

// serializer_size_of - T[N]
template<class T, std::size_t N> class serializer_size_of<T[N], std::enable_if_t<!is_memcopy_able<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX(&_object)[N]) { std::size_t size = sizeof(COUNT_T); for (const auto& iter : _object) size += get_size_of(iter); return size; }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { std::size_t size = sizeof(COUNT_T); if ((_buffer.size() - _offset) < size) throw std::exception();  _offset += size; /*for (const auto& iter : _object) size += get_extract_size_of<T>(_buffer, _offset);*/ return size; }
							};

template<class T, std::size_t N> class serializer_size_of<T[N], std::enable_if_t<is_memcopy_able<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX(&)[N]) { return sizeof(COUNT_T) + sizeof(TX) * N; }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { std::size_t size = sizeof(COUNT_T) + sizeof(TX) * N; if ((_buffer.size() - _offset) < size) throw std::exception();  _offset += size; return size; }
							};

// serializer_extract - T[] & !is_string_type_v<T> && !is_string_pointer_type_v<T>
template<class B, class T>	class serializer_extract<B, T[], std::enable_if_t<!is_string_type_v<T> && !is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::vector<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_list<type>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_list<type>(_dest); }
							};
template<class B, class T>	class serializer_peek<B, T[], std::enable_if_t<!is_string_type_v<T> && !is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::vector<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_container_list<type>(_offset); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_container_list<type>(_dest, _offset); }
							};

// 4) serializer_extract - T[] &  is_string_type_v<T>
template<class B, class T>	class serializer_extract<B, T[], std::enable_if_t<is_string_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::vector<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_string_view<TX>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_string_view<TX>(_dest); }
};
template<class B, class T>	class serializer_peek<B, T[], std::enable_if_t<is_string_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::vector<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_string_view<TX>(); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_string_view<TX>(_dest); }
							};

// 4) serializer_extract - T[] &  is_string_pointer_type_v<T>
template<class B, class T>	class serializer_extract<B, T[], std::enable_if_t<is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::vector<std::basic_string_view<TX>>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_list<type>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_list<type>(_dest); }
							};
template<class B, class T>	class serializer_peek<B, T[], std::enable_if_t<is_string_pointer_type_v<T>>>
							{	using TX = std::remove_const_t<std::remove_pointer_t<T>>;
								public:	using type = std::vector<std::basic_string_view<TX>>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_container_list<type>(_offset); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_container_list<type>(_dest, _offset); }
							};


//-----------------------------------------------------------------------------
// std::array<T,X>
//-----------------------------------------------------------------------------
// 1) T[N] - !is_string_pointer_type_v<T>
template<class B, class T, std::size_t N> class serializer_prepend<B, std::array<T,N>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const std::array<T,N>& _data) { return _s.template _prepend_array<T>(_data.data(), N);}
								template<class S> constexpr static type _do_prepend(S& _s, std::array<T,N>&& _data) { return _s.template _prepend_array<T>(_data.data(), N);}
							};
template<class B, class T, std::size_t N> class serializer_append<B, std::array<T,N>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::array<T,N>& _data) { return _s.template _append_array<T,N>(_data.data());}
								template<class S> constexpr static type _do_append(S& _s, std::array<T,N>&& _data) { return _s.template _append_array<T,N>(_data.data());}
							};
template<class B, class T, std::size_t N> class serializer_extract<B, std::array<T,N>>
							{	public: using type = std::array<T,N>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_array<T, N>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_array<T, N>(_dest); }
							};
template<class B, class T, std::size_t N> class serializer_peek<B, std::array<T,N>>
							{	public:	using type = std::array<T,N>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + _offset; auto temp = tb.template _extract_array<T,N>(); _offset = tb.data() - _s.data(); return temp;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + _offset; tb.template _extract_array<T,N>(_dest); _offset = tb.data() - _s.data();}
							};
template<class T, std::size_t N> class serializer_size_of<std::array<T,N>>
							{	public:
								constexpr static std::size_t  _get_append_size(const std::array<T,N>& _object) { std::size_t size = sizeof(COUNT_T); for (const auto& iter : _object) size += get_size_of(iter); return size; }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { std::size_t size = sizeof(COUNT_T); if ((_buffer.size() - _offset) < size) throw std::exception();  _offset += size; /*for (const auto& iter : _object) size += get_extract_size_of<T>(_buffer, _offset);*/ return size; }
							};


//-----------------------------------------------------------------------------
// buffer_view
//-----------------------------------------------------------------------------
template<class B>			class serializer_prepend<B, _buffer_view<typename B::element_t>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const _buffer_view<typename B::element_t>& _data) { return _s._prepend_buffer(_data);}
							};
template<class B>			class serializer_prepend<B, _basic_buffer<typename B::element_t>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const _basic_buffer<typename B::element_t>& _data) { return _s._prepend_buffer(_data);}
							};
template<class B, class T>	class serializer_prepend<B, _shared_buffer<T>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const _shared_buffer<T>& _data) { return _s._prepend_buffer(_data);}
							};

template<class B>			class serializer_append<B, _buffer_view<typename B::element_t>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const _buffer_view<typename B::element_t>& _data) { return _s._append_buffer(_data);}
							};
template<class B>			class serializer_append<B, _basic_buffer<typename B::element_t>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const _basic_buffer<typename B::element_t>& _data) { return _s._append_buffer(_data);}
							};
template<class B, class T>	class serializer_append<B, _shared_buffer<T>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const _shared_buffer<T>& _data) { return _s._append_buffer(_data);}
							};

template<class B>			class serializer_extract<B, _buffer_view<typename B::element_t>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s._extract_buffer_view();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s._extract_buffer_view(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<std::is_base_of_v<_buffer_view<typename B::element_t>, T>>>
							{
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); auto temp = tb.template _extract_buffer<T>(); _offset = tb.data() - _s.data(); return temp;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); tb.template _extract_buffer<T>(_dest); _offset = tb.data() - _s.data();}
							};
template<class T>	class serializer_size_of<T, std::enable_if_t<is_buffer_type_v<T>>>
							{
								public:
								constexpr static std::size_t  _get_append_size(const T& _object) { return (_object.data() != nullptr) ? (sizeof(std::size_t) + _object.size()) : sizeof(std::size_t); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};


//-----------------------------------------------------------------------------
// web
//-----------------------------------------------------------------------------
// 1) web
template<class B>			class serializer_extract<B, WEB>
							{	public:	using type = std::string_view;
								template<class S> constexpr static type _do_extract(S& _s) { return _s._extract_web();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s._extract_web(_dest);}
							};
template<class B>			class serializer_peek<B, WEB>
							{	public:	using type = std::string_view;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s._front_web(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s._front_web(_dest, _offset);}
							};
template<>					class serializer_size_of<WEB>
							{	public:
								constexpr static std::size_t _get_append_size(const WEB&) noexcept { CGDK_ASSERT_ERROR; return 0; }
								template<class S> 
								static constexpr std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 2) web_modify
template<class B>			class serializer_extract<B, WEB_MODIFY>
							{	public:	using type = std::string_view;
								template<class S> constexpr static type _do_extract(S& _s) { return _s._extract_web_modify();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s._extract_web_modify(_dest);}
							};
template<class B>			class serializer_peek<B, WEB_MODIFY>
							{	public:	using type = std::string_view;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); return tb._extract_web_modify();}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); tb._extract_web_modify(_dest);}
							};
template<>					class serializer_size_of<WEB_MODIFY>
							{	public:
								constexpr static std::size_t _get_append_size(const WEB&) noexcept { CGDK_ASSERT_ERROR; return 0; }
								template<class S> 
								constexpr static std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};


//-----------------------------------------------------------------------------
// skip
//-----------------------------------------------------------------------------
template<class B>			class serializer_prepend<B, skip>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const skip& _data) { return _s._prepend_skip(_data.amount);}
								template<class S> constexpr static type _do_prepend(S& _s, skip&& _data) { return _s._prepend_skip(_data.amount);}
							};
template<class B>			class serializer_append<B, skip>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const skip& _data) { return _s._append_skip(_data.amount);}
								template<class S> constexpr static type _do_append(S& _s, skip&& _data) { return _s._append_skip(_data.amount);}
							};

template<>					class serializer_size_of<skip>
							{	public:
								constexpr static std::size_t  _get_append_size(const skip& _object) { return static_cast<std::size_t>(_object.amount); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};


//-----------------------------------------------------------------------------
// tupple
//-----------------------------------------------------------------------------
template<class B, class... T> class serializer_prepend<B, std::tuple<T...>>
							{
								public:	using type = _buffer_view<typename B::element_t>;;
								template<class S> constexpr static type _do_prepend(S& _s, const std::tuple<T...>& _data) { return _s.template _prepend_tuple(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, std::tuple<T...>&& _data) { return _s.template _prepend_tuple(_data);}
							};
template<class B, class... T>	class serializer_append<B, std::tuple<T...>>
							{
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::tuple<T...>& _data) { return _s.template _append_tuple<T...>(_data);}
								template<class S> constexpr static type _do_append(S& _s, std::tuple<T...>&& _data) { return _s.template _append_tuple<T...>(std::move(_data));}
							};
template<class B, class... T> class serializer_extract<B, std::tuple<T...>>
							{	public:	using type = std::tuple<T...>;
								template<class S> constexpr static type _do_extract(S& _s) { std::tuple<T...> temp; _s.template _extract_tuple<T...>(temp); return temp;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_tuple<T...>(_dest);}
							};
template<class B, class... T> class serializer_peek<B, std::tuple<T...>>
							{	public:	using type = std::tuple<T...>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb = _s + static_cast<std::size_t>(_offset); std::tuple<T...> temp; tb.template _extract_tuple<T...>(temp); _offset = tb.data() - _s.data(); return temp;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb = _s + static_cast<std::size_t>(_offset); tb.template _extract_tuple<T...>(_dest); _offset = tb.data() - _s.data();}
								constexpr static std::size_t  _get_extract_size(const buffer_view& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};
template<class... T>		class serializer_size_of<std::tuple<T...>>
							{	public:
								template<class TLAST>
								constexpr static std::size_t  _get_append_size(const std::tuple<TLAST>& _tuple) { return get_size_of(std::get<0>(_tuple)); }
								template<class TFIRST, class TSECOND, class... TREST>
								constexpr static std::size_t  _get_append_size(const std::tuple<TFIRST, TSECOND, TREST...>& _tuple)	{ return get_size_of(std::get<0>(_tuple)) + _get_append_size((const std::tuple<TSECOND, TREST...>&)_tuple); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};


//-----------------------------------------------------------------------------
// Ibuffer_serializable
//-----------------------------------------------------------------------------
// 1) T- Ibuffer_serializable
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX& _data) { auto len_old = _s.size(); const_cast<TX&>(_data).serialize_out(_s); return type(_s.data() + len_old, _s.size() - len_old);}
								template<class S> constexpr static type _do_append(S& _s, TX&& _data) { auto len_old = _s.size(); _data.serialize_out(_s); return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = TX;
								template<class S> constexpr static type _do_extract(S& _s) { TX tx; tx.serialize_in(_s); return tx;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _dest.serialize_in(_s);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); type tx; tx.serialize_in(tb); return tx;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); _dest.serialize_in(tb);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX& _object) { return _object.get_size_of(); }
								constexpr static std::size_t  _get_extract_size(const buffer_view& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 2) T* - Ibuffer_serializable 여기: 제거?
template<class B, class T>	class serializer_append<B, T*, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S>
								constexpr static type _do_append(S& _s, const TX* _data) { auto len_old = _s.size(); if(_data!=nullptr) {const_cast<std::decay_t<TX>*>(_data)->serialize_out(_s);} else { _s.template _append<COUNT_T>(COUNT_T(0)-1);} return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class T>			class serializer_size_of<T*, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object) { return _object->get_size_of(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
							};


#if defined(_CGDK)
// 2) object_ptr<T>- Ibuffer_serializable
template<class B, class T>	class serializer_append<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX* _data) { auto len_old = _s.size(); if(_data != nullptr) {const_cast<TX*>(_data)->serialize_out(_s);} else { _s.template _append<COUNT_T>(COUNT_T(0)-1);} return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class B, class T>	class serializer_extract<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = object_ptr<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { object_ptr<TX> t = make_object<TX>(); t->serialize_in(_s); return t;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _dest = make_object<TX>(); _dest->serialize_in(_s);}
							};
template<class B, class T>	class serializer_peek<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = object_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); type tx; tx->serialize_in(tb); return tx;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); _dest->serialize_in(tb);}
							};
template<class T>			class serializer_size_of<object_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object) { return _object->get_size_of(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 3) own_ptr<T>- Ibuffer_serializable
template<class B, class T>	class serializer_append<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX* _data) { auto len_old = _s.size(); if(_data != nullptr) {const_cast<TX*>(_data)->serialize_out(_s);} else { _s.template _append<COUNT_T>(COUNT_T(0)-1);} return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class B, class T>	class serializer_extract<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = own_ptr<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { own_ptr<TX> t = make_own<TX>(); t->serialize_in(_s); return t;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _dest = make_own<TX>(); _dest->serialize_in(_s);}
							};
template<class B, class T>	class serializer_peek<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = own_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); type tx; tx->serialize_in(tb); return tx;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); _dest->serialize_in(tb);}
							};
template<class T>			class serializer_size_of<own_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object) { return _object->get_size_of(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
							};
#endif

// 4) std::shared_ptr<T>- Ibuffer_serializable
template<class B, class T>	class serializer_append<B, std::shared_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::shared_ptr<T>& _data) { auto len_old = _s.size(); if(_data != nullptr) { _data->serialize_out(_s);} else { _s.template _append<COUNT_T>(COUNT_T(0)-1);} return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class B, class T>	class serializer_extract<B, std::shared_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::shared_ptr<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { std::shared_ptr<TX> t = std::make_shared<TX>(); t->serialize_in(_s); return t;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _dest = std::make_shared<TX>(); _dest->serialize_in(_s);}
							};
template<class B, class T>	class serializer_peek<B, std::shared_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::shared_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); type tx; tx->serialize_in(tb); return tx;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); _dest->serialize_in(tb);}
							};
template<class T>			class serializer_size_of<std::shared_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const std::shared_ptr<T>& _object) { return _object->get_size_of(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 5) std::unique_ptr<T>- Ibuffer_serializable
template<class B, class T>	class serializer_append<B, std::unique_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::unique_ptr<T>& _data) { auto len_old = _s.size(); if(_data != nullptr) { _data->serialize_out(_s);} else { _s.template _append<COUNT_T>(COUNT_T(0)-1);} return type(_s.data() + len_old, _s.size() - len_old);}
							};
template<class B, class T>	class serializer_extract<B, std::unique_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::unique_ptr<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { std::unique_ptr<TX> t = std::make_unique<TX>(); t->serialize_in(_s); return t;}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _dest = std::make_unique<TX>(); _dest->serialize_in(_s);}
							};
template<class B, class T>	class serializer_peek<B, std::unique_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::unique_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); type tx; tx->serialize_in(tb); return tx;}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { S tb =_s + static_cast<std::size_t>(_offset); _dest->serialize_in(tb);}
							};
template<class T>			class serializer_size_of<std::unique_ptr<T>, std::enable_if_t<std::is_base_of_v<Ibuffer_serializable, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const std::unique_ptr<T>& _object) { return _object->get_size_of(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};


//-----------------------------------------------------------------------------
// protobuf
//-----------------------------------------------------------------------------
#if defined(GOOGLE_PROTOBUF_MESSAGE_H__)
// 1) T- protobuf
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX& _data)					
								{
									auto object_size = _data.ByteSizeLong();
									auto dest_ptr = _s.get_back_ptr();
									auto remained = static_cast<int>(_s.capacity() - _s.size());

									auto result = const_cast<TX&>(_data).SerializePartialToArray(dest_ptr, remained);

									if (result == false)
										throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(append)")*/);

									type result_return(dest_ptr, object_size);
									_s.add_size(object_size);

									return result_return;
								}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = TX;
								template<class S> constexpr static type _do_extract(S& _s)
								{
									TX dest;
									_do_extract(dest, _s);
									return dest;
								}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s)
								{
									auto result = _dest.ParseFromArray(_s.template data<void>(), _s.template size<int>());

									if (result == false)
										throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(extract)")*/);

									_s += offset(_dest.ByteSizeLong());
								}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)
								{
									type dest;
									_do_peek(dest, _s, _offset);
									return dest;
								}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset)
								{
									S tb =_s + static_cast<std::size_t>(_offset);

									auto result = _dest.ParseFromArray(tb.template data<void>(), tb.template size<int>());

									if (result == false)
										throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(peek)")*/);

									_offset += _dest.ByteSizeLong();
								}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX& _object) { return _object.ByteSizeLong(); }
								constexpr static std::size_t  _get_extract_size(const buffer_view& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 2) T* - protobuf 여기: 제거?
template<class B, class T>	class serializer_append<B, T*, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S>
								constexpr static type _do_append(S& _s, const TX* _data)
								{
									auto len_old = _s.size();

									if(_data != nullptr)
									{
										auto object_size = _data.ByteSizeLong();
										auto dest_ptr = _s.get_back_ptr();
										auto remained = static_cast<int>(_s.capacity() - _s.size());

										auto result = const_cast<TX&>(_data).SerializePartialToArray(dest_ptr, remained);

										if (result == false)
											throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(append)")*/);

										type result_return(dest_ptr, object_size);
										_s.add_size(object_size);
									}
									else
									{
										_s.template _append<COUNT_T>(COUNT_T(0)-1);
									}

									return type(_s.data() + len_old, _s.size() - len_old);
								}
							};
template<class T>			class serializer_size_of<T*, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object) { return _object->ByteSizeLong(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
							};

// 2) object_ptr<T>- protobuf
template<class B, class T>	class serializer_append<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX* _data)
								{
									auto len_old = _s.size();
									
									if(_data != nullptr)
									{
										auto object_size = _data.ByteSizeLong();
										auto dest_ptr = _s.get_back_ptr();
										auto remained = static_cast<int>(_s.capacity() - _s.size());

										auto result = const_cast<TX&>(_data).SerializePartialToArray(dest_ptr, remained);

										if (result == false)
											throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(append)")*/);

										type result_return(dest_ptr, object_size);
										_s.add_size(object_size);
									}
									else
									{
										_s.template _append<COUNT_T>(COUNT_T(0)-1);
									}
									
									return type(_s.data() + len_old, _s.size() - len_old);
								}
							};
template<class B, class T>	class serializer_extract<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = object_ptr<TX>;
								template<class S> constexpr static type _do_extract(S& _s)
								{
									object_ptr<TX> dest; 
									_do_extract(dest, _s);
									return dest;
								}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s)
								{
									_dest = make_object<TX>();

									auto result = _dest.ParseFromArray(_s.template data<void>(), _s.template size<int>());

									if (result == false)
										throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(extract)")*/);

									_s += offset(_dest.ByteSizeLong());
								}
							};
template<class B, class T>	class serializer_peek<B, object_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = object_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)
								{
									object_ptr<TX> dest;
									_do_peek(dest, _s);
									return dest;
								}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset)
								{
									S tb =_s + static_cast<std::size_t>(_offset);

									_dest = make_object<TX>();

									auto result = _dest.ParseFromArray(tb.template data<void>(), tb.template size<int>());

									if (result == false)
										throw std::exception(/*tb.size<std::size_t>(), std::string("protobuf:fail to serialize(peek)")*/);

									_offset += _dest.ByteSizeLong();
								}
							};
template<class T>			class serializer_size_of<object_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object) { return _object->ByteSizeLong(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};

// 3) own_ptr<T>- protobuf
template<class B, class T>	class serializer_append<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX* _data)
								{
									auto len_old = _s.size();
									
									if(_data != nullptr)
									{
										auto object_size = _data.ByteSizeLong();
										auto dest_ptr = _s.get_back_ptr();
										auto remained = static_cast<int>(_s.capacity() - _s.size());

										auto result = const_cast<TX&>(_data).SerializePartialToArray(dest_ptr, remained);

										if (result == false)
											throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(append)")*/);

										type result_return(dest_ptr, object_size);
										_s.add_size(object_size);
									}
									else
									{
										_s.template _append<COUNT_T>(COUNT_T(0)-1);
									}
									
									return type(_s.data() + len_old, _s.size() - len_old);
								}
							};
template<class B, class T>	class serializer_extract<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = own_ptr<TX>&&;
								template<class S> constexpr static type _do_extract(S& _s)
								{
									own_ptr<TX> t;
									_do_extract(t, _s);

									return t;
								}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s)
								{
									_dest = make_own<TX>();
									
									auto result = _dest.ParseFromArray(_s.template data<void>(), _s.template size<int>());

									if (result == false)
										throw std::exception(/*_s.size<std::size_t>(), std::string("protobuf:fail to serialize(extract)")*/);

									_s += offset(_dest.ByteSizeLong());
								}
							};
template<class B, class T>	class serializer_peek<B, own_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = own_ptr<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)
								{
									S tb =_s + static_cast<std::size_t>(_offset);
									
									type tx;
									tx->serialize_in(tb);
									return tx;
								}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset)
								{
									S tb =_s + static_cast<std::size_t>(_offset);
									
									_dest->serialize_in(tb);
								}
							};
template<class T>			class serializer_size_of<own_ptr<T>, std::enable_if_t<std::is_base_of_v<::google::protobuf::Message, T>>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const TX* _object)							
								{
									return _object->ByteSizeLong();
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR; return 0;
								}
							};
#endif


//-----------------------------------------------------------------------------
//
// for strings
//-----------------------------------------------------------------------------
// class for prepend)
template<class B, class T>	class serializer_prepend<B, T*, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const TX* _data) { return _s.template  _prepend_string<TX>(_data);}
								template<class S, class TY> constexpr static type _do_prepend(S& _s, const TY* _data) { return _s.template  _prepend_string_encoding<TX,TY>(_data);}
							};
template<class B, class T>	class serializer_prepend<B, text<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const text<T>& _data) { return _s.template  _prepend_text<TX>(_data.p);}
								template<class S> constexpr static type _do_prepend(S& _s, text<T>&& _data) { return _s.template  _prepend_text<TX>(_data.p);}
								template<class S, class TY> constexpr static type _do_prepend(S& _s, text<TY>&& _data) { return _s.template  _prepend_text_encoding<TX,TY>(_data.p);}
							};
template<class B, class T>	class serializer_prepend<B, std::basic_string<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const std::basic_string<TX>& _data) { return _s.template  _prepend_string<TX>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, std::basic_string<TX>&& _data) { return _s.template  _prepend_string<TX>(_data); }
								template<class S, class TY> constexpr static type _do_prepend(S& _s, std::basic_string<TY>&& _data){ return _s.template  _prepend_string_encoding<TX,TY>(_data); }
							};
template<class B, class T>	class serializer_prepend<B, std::basic_string_view<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const std::basic_string_view<TX>& _data) { return _s.template _prepend_string<TX>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, std::basic_string_view<TX>&& _data) { return _s.template _prepend_string<TX>(_data);}
								template<class S, class TY> constexpr static type _do_prepend(S& _s, std::basic_string_view<T>&& _data){ return _s.template _prepend_string_encoding<TX, TY>(_data);}
							};

// class for append)
template<class B, class T>	class serializer_append<B, T*, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const TX* _data) { return _s.template  _append_string<TX>(std::basic_string_view<TX>(_data));}
								template<class S, class TY> constexpr static type _do_append(S& _s, const TY* _data) { return _s.template  _append_string_encoding<TX,TY>(std::basic_string_view<TY>(_data));}
							};
template<class B, class T>	class serializer_append<B, text<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const text<T>& _data) { return _s.template  _append_text<TX>(_data.p);}
								template<class S> constexpr static type _do_append(S& _s, text<T>&& _data) { return _s.template  _append_text<TX>(_data.p);}
								template<class S, class TY> constexpr static type _do_append(S& _s, text<TY>&& _data) { return _s.template  _append_text_encoding<TX,TY>(_data.p);}
							};
template<class B, class T>	class serializer_append<B, std::basic_string<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::basic_string<TX>& _data) { return _s.template  _append_string<TX>(_data);}
								template<class S> constexpr static type _do_append(S& _s, std::basic_string<TX>&& _data) { return _s.template  _append_string<TX>(_data);}
								template<class S, class TY> constexpr static type _do_append(S& _s, std::basic_string<TY>&& _data) { return _s.template  _append_string_encoding<TX,TY>(_data);}
							};
template<class B, class T>	class serializer_append<B, std::basic_string_view<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::basic_string_view<TX>& _data) { return _s.template  _append_string<TX>(_data);}
								template<class S> constexpr static type _do_append(S& _s, std::basic_string_view<TX>&& _data) { return _s.template  _append_string<TX>(_data);}
								template<class S, class TY> constexpr static type _do_append(S& _s, std::basic_string_view<TY>&& _data){ return _s.template  _append_string_encoding<TX,TY>(_data);}
							};

// class for extract)
template<class B, class T>	class serializer_extract<B, T*, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_string_view<TX>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_string_view<TX>(_dest);}
							};
template<class B, class T>	class serializer_extract<B, text<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_text<TX>(static_cast<TX>(0));}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_text<TX>(static_cast<TX>(_dest, 0));}
							};
template<class B, class T>	class serializer_extract<B, std::basic_string<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_string<TX>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_string<TX>(_dest);}
							};
template<class B, class T>	class serializer_extract<B, std::basic_string_view<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_string_view<TX>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_string_view<TX>(_dest);}
							};

// class for front)
template<class B, class T>	class serializer_peek<B, T*, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_string_view<TX>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_string_view<TX>(_dest, _offset);}
							};
template<class B, class T>	class serializer_peek<B, text<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)	{ return _s.template _front_text<TX>(_offset, 0);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_text<TX>(_dest, _offset, 0);}
							};
template<class B, class T>	class serializer_peek<B, std::basic_string<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_string<TX>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_string<TX>(_dest, _offset);}
							};
template<class B, class T>	class serializer_peek<B, std::basic_string_view<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:	using type = std::basic_string_view<TX>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_string_view<TX>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_string_view<TX>(_dest, _offset);}
							};

// class for get_size_of)
template<class T>			class serializer_size_of<T*, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const std::basic_string_view<TX>& _object) { return sizeof(COUNT_T) + (_object.size() + 1) * sizeof(TX); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
};
template<class T>			class serializer_size_of<text<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const text<TX>& _object) { return _object.bytes(); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0;}
							};
template<class T>			class serializer_size_of<std::basic_string<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const std::basic_string<TX>& _object) { return sizeof(COUNT_T) + (_object.size() + 1) * sizeof(TX); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
};
template<class T>			class serializer_size_of<std::basic_string_view<T>, std::enable_if_t<is_string_type<T>::value>>
							{	using TX = std::remove_const_t<T>;
								public:
								constexpr static std::size_t  _get_append_size(const std::basic_string_view<TX>& _object) { return sizeof(COUNT_T) + (_object.size() + 1) * sizeof(TX); }
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept { CGDK_ASSERT_ERROR; return 0; }
							};


//-----------------------------------------------------------------------------
// linear container - push_back() only (list<T>, deque<T>, circular_list<T>, ...)
//-----------------------------------------------------------------------------
// linear container<T>)
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_list<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_list<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)	{ return _s.template _front_container_list<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_container_list<T>(_dest, _offset);}
							};

template<typename T>		class serializer_size_of<T, std::enable_if_t<is_linear_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};

// linear container<object_ptr<T>>)
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_object_ptr_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_object_ptr_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_object_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_object_ptr_list<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_object_ptr_list<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_object_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_container_object_ptr_list<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_container_object_ptr_list<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_linear_object_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};

// linear container<own_ptr<T>>)
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_own_ptr_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_own_ptr_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_own_ptr_list<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_own_ptr_list<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_container_own_ptr_list<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_container_own_ptr_list<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_linear_own_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


//-----------------------------------------------------------------------------
// linear container<shared_buffer> - push_back() and reserve() - (vector<T>, ...)
//-----------------------------------------------------------------------------
// linear container<T>
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_array<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_array<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_array<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_array<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_array<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_array<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_container_array<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_container_array<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_linear_container_with_reserve<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}

							};

// linear container<object_ptr<T>>
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_object_ptr_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_array<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_array<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_object_ptr_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_array<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_array<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_object_ptr_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_object_ptr_array<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_object_ptr_array<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_object_ptr_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_object_ptr_vector<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_object_ptr_vector<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_linear_object_ptr_container_with_reserve<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);

									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const buffer_view& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};

// linear container<own_ptr<T>>
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_linear_own_ptr_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_array<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_array<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_linear_own_ptr_container_with_reserve<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_array<T>(_s, _data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_array<T>(_s, _data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_linear_own_ptr_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_own_ptr_array<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_own_ptr_array<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_linear_own_ptr_container_with_reserve<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_own_ptr_vector<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_own_ptr_vector<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_linear_own_ptr_container_with_reserve<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{ 
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


//-----------------------------------------------------------------------------
// std::span<T>
//-----------------------------------------------------------------------------
#if defined(__cpp_lib_span)
// std::span<T>)
template<class B, class T,size_t E>	class serializer_prepend<B, std::span<T,E>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const std::span<T,E>& _data) { return _s.template _prepend_container_list<std::span<T,E>>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, std::span<T,E>&& _data) { return _s.template _prepend_container_list<std::span<T,E>>(_data);}
							};
template<class B, class T,size_t E>	class serializer_append<B, std::span<T,E>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const std::span<T,E>& _data) { return _s.template _append_container_list<std::span<T,E>>(_data);}
								template<class S> constexpr static type _do_append(S& _s, std::span<T,E>&& _data) { return _s.template _append_container_list<std::span<T,E>>(_data);}
							};
template<class B, class T,size_t E>	class serializer_extract<B, std::span<T,E>, std::enable_if_t<is_memcopy_able<T>::value>>
							{	public:	using type = std::span<T,E>;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_container_span<std::span<T,E>>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_container_span<std::span<T,E>>(_dest);}
							};
template<class B, class T,size_t E>	class serializer_extract<B, std::span<T,E>, std::enable_if_t<!is_memcopy_able<T>::value>>
							{
							};
template<class B, class T,size_t E>	class serializer_peek<B, std::span<T,E>, std::enable_if_t<is_memcopy_able<T>::value>>
							{	public:	using type = std::span<T,E>;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset)	{ return _s.template _front_container_array<std::span<T,E>>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_container_array<std::span<T,E>>(_dest, _offset);}
							};
template<class B, class T,size_t E>	class serializer_peek<B, std::span<T,E>, std::enable_if_t<!is_memcopy_able<T>::value>>
							{
							};

template<class T,size_t E>	class serializer_size_of<std::span<T,E>>
							{	public:
								constexpr static std::size_t  _get_append_size(const std::span<T,E>& _object)
								{
									return sizeof(COUNT_T) + sizeof(T) * _object.size();
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};
#endif
														
//-----------------------------------------------------------------------------
// associated container (set<T>, multiset<T>, ...)
//-----------------------------------------------------------------------------
// set container<T>)
// std::set<T>, std::multiset<T>, ...
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_set_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_set_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_set_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_set<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_set<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_set_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_set<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_set<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_set_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);

									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};

// std::set<object_ptr<T>>, std::multiset<object_ptr<T>>, ...
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_set_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_set_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_set_object_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_object_ptr_set<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_object_ptr_set<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_set_object_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_object_ptr_set<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_object_ptr_set<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_set_object_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


// std::set<own_ptr<T>>, std::multiset<own_ptr<T>>, ...
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_set_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_list<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_set_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_list<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_list<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_set_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_own_ptr_set<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_own_ptr_set<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_set_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_own_ptr_set<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_own_ptr_set<T>(_dest, _offset);}
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_set_own_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


//-----------------------------------------------------------------------------
// associated container (std::map<T>, std::multimap<T>, ...)
//-----------------------------------------------------------------------------
// associated container<T>)
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_associative_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_associative<T>(_data); }
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_associative<T>(_data); }
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_associative_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_associative<T>(_data); }
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_associative<T>(_data); }
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_associative_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_object_ptr_container_associative<T>(); }
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_object_ptr_container_associative<T>(_dest); }
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_associative_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset){ return _s.template _front_container_associative<T>(_offset); }
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_container_associative<T>(_dest, _offset); }
							};
template<class T>			class serializer_size_of<T, std::enable_if_t<is_associative_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter.first);
										size += get_size_of(iter.second);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


// associated container<object_ptr<T>>)
template<class B, class T>		class serializer_prepend<B, T, std::enable_if_t<is_associative_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_associative<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_associative<T>(_data);}
							};
template<class B, class T>		class serializer_append<B, T, std::enable_if_t<is_associative_object_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_associative<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_associative<T>(_data);}
							};
template<class B, class T>		class serializer_extract<B, T, std::enable_if_t<is_associative_object_ptr_container<T>::value>>
							{	public:	using  type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_object_ptr_container_associative<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_object_ptr_container_associative<T>(_dest);}
							};
template<class B, class T>		class serializer_peek<B, T, std::enable_if_t<is_associative_object_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_object_ptr_container_associative<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset){ _s.template _front_object_ptr_container_associative<T>(_dest, _offset);}
							};
template<typename T>		class serializer_size_of<T, std::enable_if_t<is_associative_object_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter.first);
										size += get_size_of(iter.second);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


// associated container<own_ptr<T>>)
template<class B, class T>	class serializer_prepend<B, T, std::enable_if_t<is_associative_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_prepend(S& _s, const T& _data) { return _s.template _prepend_container_associative<T>(_data);}
								template<class S> constexpr static type _do_prepend(S& _s, T&& _data) { return _s.template _prepend_container_associative<T>(_data);}
							};
template<class B, class T>	class serializer_append<B, T, std::enable_if_t<is_associative_own_ptr_container<T>::value>>
							{	public:	using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do_append(S& _s, const T& _data) { return _s.template _append_container_associative<T>(_data);}
								template<class S> constexpr static type _do_append(S& _s, T&& _data) { return _s.template _append_container_associative<T>(_data);}
							};
template<class B, class T>	class serializer_extract<B, T, std::enable_if_t<is_associative_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_extract(S& _s) { return _s.template _extract_own_ptr_container_associative<T>();}
								template<class D, class S> constexpr static void _do_extract(D& _dest, S& _s) { _s.template _extract_own_ptr_container_associative<T>(_dest);}
							};
template<class B, class T>	class serializer_peek<B, T, std::enable_if_t<is_associative_own_ptr_container<T>::value>>
							{	public:	using type = T;
								template<class S> constexpr static type _do_peek(const S& _s, int64_t& _offset) { return _s.template _front_own_ptr_container_associative<T>(_offset);}
								template<class D, class S> constexpr static void _do_peek(D& _dest, const S& _s, int64_t& _offset) { _s.template _front_own_ptr_container_associative<T>(_dest, _offset);}
							};
template<typename T>		class serializer_size_of<T, std::enable_if_t<is_associative_own_ptr_container<T>::value>>
							{	public:
								constexpr static std::size_t  _get_append_size(const T& _object)
								{
									auto size = sizeof(COUNT_T);
								
									for (const auto& iter : _object)
									{
										size += get_size_of(iter.first);
										size += get_size_of(iter.second);
									}

									// return )
									return	size;
								}
								template<class S> 
								constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) noexcept
								{
									CGDK_ASSERT_ERROR;
									return 0;
								}
							};


//-----------------------------------------------------------------------------
// aggrigate structure (reflection)
//-----------------------------------------------------------------------------
template <std::size_t ISIZE>	constexpr std::size_t align_offset_pre     (std::size_t _source, std::size_t _add);
template <>						constexpr std::size_t align_offset_pre< 1> (std::size_t _source, std::size_t) { return _source; }
template <>						constexpr std::size_t align_offset_pre< 2> (std::size_t _source, std::size_t _add) { return (!(_source & 0x01) || _add <= 1) ? _source : _source + 1;}
template <>						constexpr std::size_t align_offset_pre< 4> (std::size_t _source, std::size_t _add) { auto remained = (_source & 0x03); return (remained == 0 || ( 4 - remained) >= _add) ? _source : ((_source & (~0x03)) +  4);}
template <>						constexpr std::size_t align_offset_pre< 8> (std::size_t _source, std::size_t _add) { auto remained = (_source & 0x07); return (remained == 0 || ( 8 - remained) >= _add) ? _source : ((_source & (~0x07)) +  8);}
template <>						constexpr std::size_t align_offset_pre<16> (std::size_t _source, std::size_t _add) { auto remained = (_source & 0x0f); return (remained == 0 || (16 - remained) >= _add) ? _source : ((_source & (~0x0f)) + 16);}
template <>						constexpr std::size_t align_offset_pre<32> (std::size_t _source, std::size_t _add) { auto remained = (_source & 0x1f); return (remained == 0 || (32 - remained) >= _add) ? _source : ((_source & (~0x1f)) + 32);}
template <>						constexpr std::size_t align_offset_pre<64> (std::size_t _source, std::size_t _add) { auto remained = (_source & 0x3f); return (remained == 0 || (64 - remained) >= _add) ? _source : ((_source & (~0x3f)) + 64);}

namespace reflection
{
	// - any construct
	struct any_constructor_lref { std::size_t ignore; template <class Type> /*constexpr*/ constexpr operator Type& () const noexcept; };
	struct any_constructor_rref { std::size_t ignore; template <class Type> /*constexpr*/ constexpr operator Type&& () const noexcept; };

	// - enable_is_constructible?
	template <class T, std::size_t... I, class /*ENABLE*/ = std::enable_if_t<std::is_copy_constructible<T>::value>>
	constexpr auto enable_if_constructible_helper(std::index_sequence<I...>) noexcept -> typename std::add_pointer_t<decltype(T{ any_constructor_lref{I}... })>;
	template <class T, std::size_t... I, class /*ENABLE*/ = std::enable_if_t<!std::is_copy_constructible<T>::value>>
	constexpr auto enable_if_constructible_helper(std::index_sequence<I...>) noexcept -> typename std::add_pointer_t<decltype(T{ any_constructor_rref{I}... })>;
	template <class T, std::size_t N, class /*ENABLE*/ = decltype(enable_if_constructible_helper<T>(std::make_index_sequence<N>())) >
	using enable_if_constructible_helper_t = std::size_t;

	template <class T, std::size_t BEGIN, std::size_t MIDDLE>
	constexpr std::size_t 	detect_fields_count(std::true_type, long) noexcept
	{
		return BEGIN;
	}
	template <class T, std::size_t BEGIN, std::size_t MIDDLE>
	constexpr std::size_t	detect_fields_count(std::false_type, int) noexcept;

	template <class T, std::size_t BEGIN, std::size_t MIDDLE>
	constexpr auto			detect_fields_count(std::false_type, long) noexcept -> enable_if_constructible_helper_t<T, MIDDLE>
	{
		constexpr std::size_t next_v = MIDDLE + (MIDDLE - BEGIN + 1) / 2;
		return detect_fields_count<T, MIDDLE, next_v>(std::integral_constant<bool, MIDDLE == next_v>{}, 1L);
	}
	template <class T, std::size_t BEGIN, std::size_t MIDDLE>
	constexpr std::size_t	detect_fields_count(std::false_type, int) noexcept
	{
		constexpr std::size_t next_v = BEGIN + (MIDDLE - BEGIN) / 2;
		return detect_fields_count<T, BEGIN, next_v>(std::integral_constant<bool, BEGIN == next_v>{}, 1L);
	}

	template <class T>
	constexpr std::size_t	get_fields_count() noexcept
	{
		using type = std::remove_const_t<T>;
		constexpr std::size_t max_fields_count = sizeof(type);
		constexpr std::size_t middle = max_fields_count / 2 + 1;
		return detect_fields_count<T, 0, middle>(std::false_type{}, 1L);
	}
}

template <class T>
constexpr std::size_t constexpr_field_count = std::integral_constant<std::size_t, reflection::get_fields_count<T>()>::value;


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------
template <class T>
constexpr std::basic_string<T>	_float_to_string(double _value);
template <>
inline std::basic_string<char> _float_to_string<char>(double _value)
{
#if defined(_STRING_) || defined(_GLIBCXX_STRING)
	return std::to_string(_value);
#else
	static_assert(false, "<string> is not included. include <string>");
	CGDK_ASSERT(false);
	throw std::exception(reinterpret_cast<const char*>("<string> is not included. include <string>"));
#endif
}
template <>
inline std::basic_string<wchar_t> _float_to_string<wchar_t>(double _value)
{
#if defined(_STRING_) || defined(_GLIBCXX_STRING)
	return std::to_wstring(_value);
#else
	static_assert(false, "<string> is not included. include <string>");
	CGDK_ASSERT(false);
	throw std::exception(reinterpret_cast<const char*>("<string> is not included. include <string>"));
#endif
}


}
