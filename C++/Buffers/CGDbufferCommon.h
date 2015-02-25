//*****************************************************************************
//*                                                                           *
//*                                CGD::buffer                                *
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
//-----------------------------------------------------------------------------
//
// Includes
//
//-----------------------------------------------------------------------------
// 1) C++ Standard Libraries and Common Includes
#include <sal.h>
#include <cstdint>
#include <cwchar>
#include <cstdarg>
#include <cassert>

// 2) 
#include <xmemory>
#include <stdexcept>
#include <malloc.h>

// 3) C++ Standard Template Libraries
namespace std
{
template<class _A, size_t _B> class array;

template<class _A, class _B> class vector;
template<class _A, class _B> class deque;
template<class _A, class _B> class list;
template<class _A, class _B> class deque;

template<class _A, class _B, class _C> class set;
template<class _A, class _B, class _C> class multiset;

template<class _A, class _B, class _C, class _D> class map;
template<class _A, class _B, class _C, class _D> class multimap;

template<class _A, class _B, class _C, class _D> class hash_map;
template<class _A, class _B, class _C, class _D> class hash_multimap;

template<class _A, class _B, class _C, class _D> class unordered_set;
template<class _A, class _B, class _C, class _D> class unordered_multiset;

template<class _A, class _B, class _C, class _D, class _E> class unordered_map;
template<class _A, class _B, class _C, class _D, class _E> class unordered_multimap;
}

namespace CGD
{
template<class _A, size_t _B> class array;
template<class _A, class _B> class circular_list;
}

// Defined in CGBufferClasses
template<class T> class CGPTR;


// 3) 
#include "CGDbufferConfigures.h"


//-----------------------------------------------------------------------------
//
// Disable Warning
//
//-----------------------------------------------------------------------------
// 1) warning C4344: behavior change: use of explicit template arguments results in call to ...
//    - Causes in front function
#pragma warning(disable:4344)


#if _MSC_VER<1700
	#define _In_reads_z_(a)
	#define _In_reads_(a)
	#define _In_reads_bytes_(a)
	#define	_Out_writes_(a)
	#define	_Field_size_bytes_(a)
#endif


//-----------------------------------------------------------------------------
// 
// Memory Definitions
//
//-----------------------------------------------------------------------------
// 1) Definitions
#define	CGMEMPTR		CGD::ptr
#define	CGMALLOC(size)	_aligned_malloc(size, 16)
#define	CGFREE(ptr)		_aligned_free(ptr)

namespace CGD
{

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class...> struct enable_if_exist	{ typedef void type;};
#else
	template<class A, class B=void, class C=void, class D=void, class E=void, class F=void>	struct enable_if_exist	{	typedef void type;};
#endif

template<class, class = void>	struct is_iterator : std::false_type {};
template<class _Ty>				struct is_iterator<_Ty *> : true_type	{};
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

#ifdef _SUPPORT_CPP11_TRAITS
template <typename T> struct is_memcopy_able	{ static const bool value = std::is_trivially_copyable<T>::value && !std::is_pointer<T>::value;};
#else
template <typename T> struct is_memcopy_able	{ static const bool value = std::is_arithmetic<T>::value && !std::is_pointer<T>::value;};
#endif

}


//-----------------------------------------------------------------------------
//
// General Definitions
//
//-----------------------------------------------------------------------------
	// 2) CGD Assert
#define	CGD_ASSERT(condition, state)		if((condition)==false) { _ASSERT(condition); state;}


//-----------------------------------------------------------------------------
//
// 각종 append(<<)와 Extract(>>)용 정의들
//
//-----------------------------------------------------------------------------
namespace CGD
{

	// Protytype) 
	class ptr;
	class buffer;

	// 1) Skip
	class SKIP
	{
	public:
		SKIP(size_t _Amount) : m_skip(_Amount) {}
	public:
		size_t	m_skip;
	};


	// 2) Pointer (T형은 Pointer형이 될수는 없다.)
	template <class T, class TENABLE = std::enable_if<!std::is_pointer<T>::value, void>::type>
	class POINTER
	{
	public:
		POINTER() : ptr(nullptr) {}
	public:
		T*		ptr;

	public:
		T&		operator *() { return *ptr; }
		T*		operator ->() { return ptr; }
	};

	template<class I, class TENABLE = std::enable_if<is_iterator<I>::value, void>::type>
	class _ITERATOR
	{
	public:
		_ITERATOR(const I& _Iter_begin, const I& _Iter_end) : iterFirst(_Iter_begin), iterLast(_Iter_end) {}
	public:
		I		iterFirst;
		I		iterLast;
	};

	template<class I>
	typename std::enable_if<is_iterator<I>::value, _ITERATOR<I, void>>::type
	ITERATOR(const I& _Iter_begin, const I& _Iter_end)
	{
		return	_ITERATOR<I, void>(_Iter_begin, _Iter_end);
	}

	// 3) Web String
	struct WEB {};

	// 4) Text
	template <class T>
	struct text
	{
	public:
		text() {}
		text(const text& _Rhs) : p(_Rhs.p) {}
		text(const T* _zstr) : p(_zstr) {}

	public:
		text&		operator=(const text& _Rhs)		{ p = _Rhs.p; return *this; }
		text&		operator=(const T* _Rhs)		{ p = _Rhs; return *this; }

		bool	operator==(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) == 0; }
		bool	operator==(const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) == 0; }
		bool	operator!=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) != 0; }
		bool	operator!=(const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) != 0; }
		bool	operator>=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) >= 0; }
		bool	operator>=(const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) >= 0; }
		bool	operator> (const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) > 0; }
		bool	operator> (const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) > 0; }
		bool	operator<=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) <= 0; }
		bool	operator<=(const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) <= 0; }
		bool	operator< (const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) < 0; }
		bool	operator< (const T*) const			{ return std::char_traits<T>::compare(p, _Rhs, 0) < 0; }
				operator const T*() const			{ return p; }
	public:
		const T*	p;
	};

	template <class T>
	text<T> _text(const T* _String)
	{
		return text<T>(_String);
	}

	// 7) 
	template<typename T, size_t X>
	struct _RETURN_ARRAY
	{
		_RETURN_ARRAY() {}
		T value[X];

		T&			operator [](size_t _Index)		{	CGD_ASSERT(_Index<X, ); if(_Index>=X) throw std::out_of_range("_Index is Out of Range!!(" __FUNCTION__ ")"); return value[_Index];}
	};

	template<typename T, size_t X>
	struct _STORE_ARRAY
	{
		_STORE_ARRAY(T* p) : value(p) {}
		_STORE_ARRAY&	operator=(const _RETURN_ARRAY<T, X>& rhs) { for (int i = 0; i < X; ++i)value[i] = rhs.value[i]; return *this; }
		T*	value;
	};

	template<typename T, size_t X>
	_STORE_ARRAY<T, X> STORE(T(&p)[X])
	{
		return _STORE_ARRAY<T, X>(p);
	}

	template<size_t X, typename T>
	_STORE_ARRAY<T, X> STORE(T* p)
	{
		return _STORE_ARRAY<T, X>(p);
	}


	class POS
	{
	public:
		POS() : offset(0) {}
		POS(const POS& p) : offset(p.offset) {}
		explicit POS(int p) : offset(p) {}
	public:
		int		get_pos() const { return offset; }
		void	set_pos(int _Offset) { offset = _Offset; }

		POS&	operator=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
		POS&	operator=(int _Rhs) { offset += _Rhs; return *this; }

		bool	operator==(const POS& _Rhs) const { return offset == _Rhs.offset; }
		bool	operator==(int _Rhs) const { return offset == _Rhs; }
		bool	operator!=(const POS& _Rhs) const { return offset != _Rhs.offset; }
		bool	operator!=(int _Rhs) const { return offset != _Rhs; }
		bool	operator>=(const POS& _Rhs) const { return offset >= _Rhs.offset; }
		bool	operator>=(int _Rhs) const { return offset >= _Rhs; }
		bool	operator> (const POS& _Rhs) const { return offset > _Rhs.offset; }
		bool	operator> (int _Rhs) const { return offset > _Rhs; }
		bool	operator<=(const POS& _Rhs) const { return offset <= _Rhs.offset; }
		bool	operator<=(int _Rhs) const { return offset <= _Rhs; }
		bool	operator< (const POS& _Rhs) const { return offset < _Rhs.offset; }
		bool	operator<  (int _Rhs) const { return offset < _Rhs; }

		POS&	operator+=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
		POS&	operator+=(int _Rhs) { offset += _Rhs; return *this; }
		POS&	operator-=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
		POS&	operator-=(int _Rhs) { offset += _Rhs; return *this; }
		POS&	operator*=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
		POS&	operator*=(int _Rhs) { offset += _Rhs; return *this; }
		POS&	operator/=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
		POS&	operator/=(int _Rhs) { offset += _Rhs; return *this; }

		operator int&() { return offset; }
		operator const int&() const { return offset; }
	public:
		int		offset;
	};


	// ----------------------------------------------------------------------------
	// Static
	// ----------------------------------------------------------------------------
	template<size_t N>	_CONSTEXPR size_t const_string_length(const char(&)[N]) { return N - 1; }
	template<size_t N>	_CONSTEXPR size_t const_string_length(const wchar_t(&)[N]) { return N - 1; }
	template<size_t N>	_CONSTEXPR size_t const_string_length(const char16_t(&)[N]) { return N - 1; }
	template<size_t N>	_CONSTEXPR size_t const_string_length(const char32_t(&)[N]) { return N - 1; }

	template<size_t N>	_CONSTEXPR size_t const_string_size(const char(&)[N]) { return (N - 1)*sizeof(char); }
	template<size_t N>	_CONSTEXPR size_t const_string_size(const wchar_t(&)[N]) { return (N - 1)*sizeof(wchar_t); }
	template<size_t N>	_CONSTEXPR size_t const_string_size(const char16_t(&)[N]) { return (N - 1)*sizeof(char16_t); }
	template<size_t N>	_CONSTEXPR size_t const_string_size(const char32_t(&)[N]) { return (N - 1)*sizeof(char32_t); }

	template <class T, size_t N>
	class const_string
	{
	public:
		const T* const	p;

		_CONSTEXPR const_string(const T(&_a)[N]) : p(_a) {}
		_CONSTEXPR std::size_t size() const		{ return N; }

		const_string<T,N>&	operator=(const const_string<T,N>& _Rhs)	{	p=_Rhs.p; return *this;}
	};

	template<class T, size_t N>
	_CONSTEXPR const_string<T, N> _const(const T(&_Str)[N])
	{
		return const_string<T, N>(_Str);
	}
	
	template <class T, size_t N>
	class const_text
	{
	public:
		const T* const	p;

		_CONSTEXPR const_text(const T(&_a)[N]) : p(_a) {}
		_CONSTEXPR std::size_t size() const		{ return N; }

		const_text<T,N>&	operator=(const const_text<T,N>& _Rhs)	{	p=_Rhs.p; return *this;}
	};

	template<class T, size_t N>
	_CONSTEXPR const_text<T, N> _const_text(const T(&_Str)[N])
	{
		return const_text<T, N>(_Str);
	}


	//-----------------------------------------------------------------------------
	//
	// Time
	//
	//-----------------------------------------------------------------------------
	struct DATETIME
	{
	public:
		DATETIME()								{}

	public:
		DATETIME(const tm& _Value)				{	set_time(_Value);}
					operator	tm() const		{	return get_tm();}
		DATETIME&	operator =(const tm& _Rhs)	{	set_time(_Rhs); return *this;}
		void set_time(const tm& _Value)
		{
			wYear			 = (uint16_t)_Value.tm_year+1900;
			wMonth			 = (uint16_t)_Value.tm_mon;
			wDay			 = (uint8_t)_Value.tm_mday;
			wHour			 = (uint8_t)_Value.tm_hour;
			wMinute			 = (uint8_t)_Value.tm_min;
			wSecond			 = (uint8_t)_Value.tm_sec;
			// dwMillisecond	 = 0; // Don't care
		}
		tm get_tm() const
		{
			tm	temp;

			temp.tm_year	= (int)wYear-1900;
			temp.tm_yday	= (int)0;
			temp.tm_mon		= (int)wMonth;
			temp.tm_mday	= (int)wDay;
			temp.tm_wday	= (int)0;
			temp.tm_hour	= (int)wHour;
			temp.tm_min		= (int)wMinute;
			temp.tm_sec		= (int)wSecond;
			temp.tm_isdst	= (int)0;

			return	temp;
		}

#ifdef _MINWINBASE_
		DATETIME(const SYSTEMTIME& _Value)		{	set_time(_Value);}
					operator	SYSTEMTIME() const		{	return get_SYSTEMTIME();}
		DATETIME&	operator =(const SYSTEMTIME& _Rhs)	{	set_time(_Rhs); return *this;}
		void set_time(const SYSTEMTIME& _Value)
		{
			wYear			 = (uint16_t)_Value.wYear;
			wMonth			 = (uint16_t)_Value.wMonth;
			wDay			 = (uint8_t)_Value.wDay;
			wHour			 = (uint8_t)_Value.wHour;
			wMinute			 = (uint8_t)_Value.wMinute;
			wSecond			 = (uint8_t)_Value.wSecond;
			dwMillisecond	 = _Value.wMilliseconds;
		}
		SYSTEMTIME get_SYSTEMTIME() const
		{
			SYSTEMTIME	temp;

			temp.wYear		= (int)wYear;
			temp.wMonth		= (uint16_t)wMonth;
			temp.wDay		= (uint16_t)wDay;
			temp.wDayOfWeek	= (uint16_t)0;
			temp.wHour		= (uint16_t)wHour;
			temp.wMinute	= (uint16_t)wMinute;
			temp.wSecond	= (uint16_t)wSecond;
			temp.wMilliseconds = (uint16_t)dwMillisecond;

			return	temp;
		}
#endif

#ifdef _CGD_TIME
		DATETIME(const CGD::TIME::_POINT& _Value)					{	set_time(_Value);}
		DATETIME(const CGD::TIME::LOCAL::POINT& _Value)				{	set_time((const CGD::TIME::_POINT&)_Value);}
		DATETIME(const CGD::TIME::SYSTEM::POINT& _Value)			{	set_time((const CGD::TIME::_POINT&)_Value);}
					operator	CGD::TIME::_POINT() const			{	return get_CGDTIME();}
					operator	CGD::TIME::LOCAL::POINT() const		{	return (CGD::TIME::LOCAL::POINT&)get_CGDTIME();}
					operator	CGD::TIME::SYSTEM::POINT() const	{	return (CGD::TIME::SYSTEM::POINT&)get_CGDTIME();}
		DATETIME&	operator =(const CGD::TIME::_POINT& _Rhs)		{	set_time(_Rhs); return *this;}
		DATETIME&	operator =(const CGD::TIME::LOCAL::POINT& _Rhs)	{	set_time((const CGD::TIME::_POINT&)_Rhs); return *this;}
		DATETIME&	operator =(const CGD::TIME::SYSTEM::POINT& _Rhs){	set_time((const CGD::TIME::_POINT&)_Rhs); return *this;}
		void set_time(const CGD::TIME::_POINT& _Value)
		{
			wYear			 = (uint16_t)_Value.get_year();
			wMonth			 = (uint16_t)_Value.get_month();
			wDay			 = (uint8_t)_Value.get_day();
			wHour			 = (uint8_t)_Value.get_hour();
			wMinute			 = (uint8_t)_Value.get_minute();
			wSecond			 = (uint8_t)_Value.get_second();
			dwMillisecond	 = (uint32_t)_Value.get_millisecond();
		}
		CGD::TIME::_POINT get_CGDTIME() const
		{
			CGD::TIME::_POINT	temp	 = CGD::TIME::_POINT::create_instance();

			temp.set_year(wYear);
			temp.set_month(wMonth);
			temp.set_day(wDay);
			temp.set_hour(wHour);
			temp.set_minute(wMinute);
			temp.set_second(wSecond);
			temp.set_millisecond(dwMillisecond);

			return	temp;
		}
#endif
	public:
		uint16_t	wYear;
		uint16_t	wMonth;
		uint8_t		wDay;
		uint8_t		wHour;
		uint8_t		wMinute;
		uint8_t		wSecond;
		uint32_t	dwMillisecond;
	};



	//-----------------------------------------------------------------------------
	//
	// 
	//
	//-----------------------------------------------------------------------------
	// 1) Bounding Check를 위한 정보
	struct CGD_CHECK_BOUND
	{
	public:
		void*	bound_lower;
		void*	bound_upper;
	public:
		CGD_CHECK_BOUND() : bound_lower(0), bound_upper((void*)-1) {}
		CGD_CHECK_BOUND(void* a, void* b) : bound_lower(a), bound_upper(b) {}
		void	clear() { bound_lower = 0; bound_upper = (void*)-1; }
	};

	// 2) 
#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
#define _CGD_COMMA						,
#define _CGD_BOUND_INFO_GET				_get_check_bound()
#define _CGD_BOUND_INFO_PARAM			CGD_CHECK_BOUND _bound
#define _CGD_BOUND_INFO_PASS			_bound
#define	_CGD_BOUND_INFO_NOWARNING		_bound;
#define	_CGD_BOUND_INFO(state)			state;
#define _CGD_BUFFER_BOUND_CHECK(condition)	if((condition)==false) { _ASSERT(false);}
#else
#define _CGD_COMMA 
#define _CGD_BOUND_INFO_GET
#define _CGD_BOUND_INFO_PARAM
#define _CGD_BOUND_INFO_PASS
#define	_CGD_BOUND_INFO_NOWARNING		
#define	_CGD_BOUND_INFO(state)
#define _CGD_BUFFER_BOUND_CHECK(condition)
#endif


//-----------------------------------------------------------------------------
//
// Buffer Serialization
//
//-----------------------------------------------------------------------------
#define	CGD_BUFFER_SERIAZABLE(_object)	_object&	operator=(CGD::_PASS& _Rhs)		{	ProcessSerializeIn(*_Rhs.m_pbuffer); return *this;}

	class _PASS
	{
	public:
		_PASS(_CGD_BOUND_INFO_PARAM _CGD_COMMA buffer* v) : m_pbuffer(v) { _CGD_BOUND_INFO(m_bound = _bound;) }
	public:
		buffer*			m_pbuffer;

#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
		CGD_CHECK_BOUND	m_bound;
#endif
	};

	class IBufferSerializable
	{
	public:
		virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer) = 0;
		virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer) = 0;

	public:
		IBufferSerializable&	operator=(_PASS& _Rhs) { ProcessSerializeIn(*_Rhs.m_pbuffer); return *this; }
	};


	//-----------------------------------------------------------------------------
	// Traits
	//-----------------------------------------------------------------------------
	// Is String Type)
	template<class T> struct is_string_type : public std::false_type {};
	template<> struct is_string_type<char> : public std::true_type{};
	template<> struct is_string_type<wchar_t> : public std::true_type{};
	template<> struct is_string_type<char16_t> : public std::true_type{};
	template<> struct is_string_type<char32_t> : public std::true_type{};
	template<> struct is_string_type<const char> : public std::true_type{};
	template<> struct is_string_type<const wchar_t> : public std::true_type{};
	template<> struct is_string_type<const char16_t> : public std::true_type{};
	template<> struct is_string_type<const char32_t> : public std::true_type{};

	// Is not String Type)
	template<class T> struct is_not_string_type : public std::true_type {};
	template<> struct is_not_string_type<char> : public std::false_type{};
	template<> struct is_not_string_type<wchar_t> : public std::false_type{};
	template<> struct is_not_string_type<char16_t> : public std::false_type{};
	template<> struct is_not_string_type<char32_t> : public std::false_type{};
	template<> struct is_not_string_type<const char> : public std::false_type{};
	template<> struct is_not_string_type<const wchar_t> : public std::false_type{};
	template<> struct is_not_string_type<const char16_t> : public std::false_type{};
	template<> struct is_not_string_type<const char32_t> : public std::false_type{};

}


//-----------------------------------------------------------------------------
//
//   Liberal
//
//-----------------------------------------------------------------------------
//#if _MSC_VER>=_MSC_VER_2015
//inline CGD::text<char>		operator"" _z(const char* _Str, const std::size_t _Size)	{ return CGD::text<char>(_Str);}
//inline CGD::text<wchar_t>	operator"" _z(const wchar_t* _Str, const std::size_t _Size) { return CGD::text<wchar_t>(_Str);}
//inline CGD::text<char16_t>	operator"" _z(const char16_t* _Str, const std::size_t _Size){ return CGD::text<char16_t>(_Str);}
//inline CGD::text<char32_t>	operator"" _z(const char32_t* _Str, const std::size_t _Size){ return CGD::text<char32_t>(_Str);}
//#endif

//-----------------------------------------------------------------------------
//
//   
//
//-----------------------------------------------------------------------------
namespace CGD
{
	// Functions for 
#include "CGDbufferFunctions.h"

// Class for prepend)
template<class T, class FLAG=void> class _AF		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T data)						{ return s->_prepend_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t X>	class _AF<T[X], typename std::enable_if<is_not_string_type<T>::value>::type>		
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[X])				{ return s->_prepend_array<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data, X);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _AF<T[], typename std::enable_if<is_not_string_type<T>::value>::type>		
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[])				{ static_assert(false, "CGD::buffer don not support 'prepend' on unsized array (array size must be specified)"); return nullptr;}};
#endif
template<>					class _AF<CGD::buffer>	{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const buffer& data)				{ return _prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<>					class _AF<CGD::SKIP>	{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SKIP& data)					{ return s->_prepend_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA data.m_skip);}};
template<class T,class E>	class _AF<CGD::POINTER<T,E>>{	public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::POINTER<T,E>& data)	{ auto& tmp=const_cast<CGD::POINTER<T,E>&>(data); return tmp.ptr=(T*)s->_prepend_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T));}};
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _AF<std::tuple<T...>> {	public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::tuple<T...>& data)		{ return s->_prepend_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
#endif
template<class T,class E>	class _AF<CGD::_ITERATOR<T,E>>{public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::_ITERATOR<T,E>& data)	{ return _Xprepend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA s, data.iterFirst, data.iterLast);}};
#ifdef _SUPPORT_INITIALIZER_LIST
template<class T>			class _AF<std::initializer_list<T>>{public:	typedef	void *t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::initializer_list<T>& data){ s->_prepend_initializer_list(_CGD_BOUND_INFO_PASS _CGD_COMMA data); return get_front_ptr();}};
#endif

// Class for append)
template<typename T, class FLAG=void>class _AB		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T data)						{ return s->_append_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t X>	class _AB<T[X], typename std::enable_if<is_not_string_type<T>::value>::type>		
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[X])				{ return s->_append_array<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data, X);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _AB<T[], typename std::enable_if<is_not_string_type<T>::value>::type>		
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[])				{ static_assert(false, "CGD::buffer don not support 'append' on unsized array (array size must be specified)"); return nullptr;}};
#endif
template<class T>			class _AB<T, typename std::enable_if<std::is_base_of<CGD::buffer, T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::buffer& data)			{ return s->_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<>					class _AB<CGD::SKIP>	{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::SKIP& data)			{ return s->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA data.m_skip);}};
template<class T,class E>	class _AB<CGD::POINTER<T,E>>{	public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::POINTER<T,E>& data)	{ auto& tmp=const_cast<CGD::POINTER<T,E>&>(data); return tmp.ptr=(T*)s->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T));}};
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _AB<std::tuple<T...>> {	public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::tuple<T...>& data)		{ return s->_append_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
#endif
template<class T,class E>	class _AB<CGD::_ITERATOR<T,E>>{public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::_ITERATOR<T,E>& data)	{ return _Xappend_iterator(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data.iterFirst, data.iterLast);}};
#ifdef _SUPPORT_INITIALIZER_LIST
template<class T>			class _AB<std::initializer_list<T>>{public:	typedef	void *t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::initializer_list<T>& data){ void* p=s->get_back_ptr(); s->_append_initializer_list(_CGD_BOUND_INFO_PASS _CGD_COMMA data); return p;}};
#endif
template<class T>			class _AB<T, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)					{ _CGD_BOUND_INFO_NOWARNING; const_cast<T&>(data).ProcessSerializeOut(*s); return nullptr;}};
template<class T>			class _AB<CGPTR<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ _CGD_BOUND_INFO_NOWARNING; const_cast<T*>(data)->ProcessSerializeOut(*s); return nullptr;}};

// Class for extract)
template<class T, class FLAG=void> class _BF		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return *(T*)s->_extract_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T));}};
template<class T, size_t X>	class _BF<T[X], typename std::enable_if<is_not_string_type<T>::value>::type>
													{	public:	typedef	_RETURN_ARRAY<T,X> t;template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return _Xextract_array<S,T,X>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _BF<T[], typename std::enable_if<is_not_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ static_assert(false, "CGD::buffer don not support 'extract' on unsized array(use 'vector or list' instead)"); return nullptr;}};
#endif
template<>					class _BF<CGD::WEB>		{	public:	typedef	char* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->_extract_web(_CGD_BOUND_INFO_PASS);} };
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _BF<std::tuple<T...>> {	public:	typedef	std::tuple<T...> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ std::tuple<T...> temp; s->_extract_tuple<T...>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return temp;} };
#endif
template<class T>			class _BF<T, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
													{	public:	typedef	CGD::_PASS t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return CGD::_PASS(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<class T>			class _BF<CGPTR<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
													{	public:	typedef	CGD::_PASS t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return CGD::_PASS(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};



// Class for front)
template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};



template<class T, size_t X> class _RH<T[X], typename std::enable_if<is_not_string_type<T>::value>::type>
													{	public:	typedef	_RETURN_ARRAY<T,X> t; template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; auto temp=_Xextract_array<S,T,X>(_CGD_BOUND_INFO_PASS _CGD_COMMA &tempBuffer); _Offset=tempBuffer.get_front_ptr()-s->get_front_ptr(); return temp;}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _RH<T[], typename std::enable_if<is_not_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ static_assert(false, "CGD::buffer don not support 'front' on unsized array(use 'vector or list' instead)"); return nullptr;}};
#endif
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _RH<std::tuple<T...>> {	public:	typedef	std::tuple<T...> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ S tempBuffer=*s+(size_t)_Offset; std::tuple<T...> temp; tempBuffer._extract_tuple<T...>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); _Offset=tempBuffer.get_front_ptr()-s->get_front_ptr(); return temp;} };
#endif

//
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//
//
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//template<class T, class FLAG=void> class _RH		{	public:	typedef	T &t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_general<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
//












//-----------------------------------------------------------------------------
//
// For Strings
//-----------------------------------------------------------------------------
// Class for prepend)
template<class T>			class _AF<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->_prepend_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t N>	class _AF<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->_prepend_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data);}};
template<class T, size_t N>	class _AF<CGD::const_string<T, N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_string<T, N>& data){ return s->_prepend_const_string<T,N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T>			class _AF<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::text<T>& data)			{ return s->_prepend_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data.p);} };
template<class T, size_t N>	class _AF<CGD::const_text<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_text<T,N>& data){ return s->_prepend_const_text<T, N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };
template<class T>			class _AF<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::basic_string<T>& data)	{ return s->_prepend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};

// Class for append)
template<class T>			class _AB<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->_append_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t N>	class _AB<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->_append_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data);}};
template<class T, size_t N>	class _AB<CGD::const_string<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_string<T, N>& data){ return s->_append_const_string<T, N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T>			class _AB<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::text<T>& data)			{ return s->_append_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data.p);} };
template<class T, size_t N>	class _AB<CGD::const_text<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_text<T,N>& data)	{ return s->_append_const_text<T, N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };
template<class T>			class _AB<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::basic_string<T>& data)	{ return s->_append_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };

// Class for extract)
template<class T>			class _BF<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS);}};
template<class T, size_t N>	class _BF<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS);}};
template<class T>			class _BF<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return s->_extract_string<T>(_CGD_BOUND_INFO_PASS);} };

// Class for front)
template<class T>			class _RH<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
template<class T>			class _RH<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return s->_front_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
template<>					class _RH<CGD::WEB>		{	public:	typedef	char* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_web(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};


//-----------------------------------------------------------------------------
//
// With Push_back only (list, deque, circular_list, ...)
//-----------------------------------------------------------------------------
// Linear container<T>)
template<class T> struct is_linear_container : public std::false_type {};
template<class A, class B> struct is_linear_container<std::list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::deque<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<CGD::circular_list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::list<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::deque<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<CGD::circular_list<CGPTR<A>, B>> : public std::false_type {};
// std::list<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_linear_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_linear_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_linear_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};

// Linear container<CGPTR<T>>)
template<class T> struct is_linear_CGPTR_container : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::deque<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<CGD::circular_list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::list<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::deque<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_CGPTR_container<CGD::circular_list<CGPTR<A>, B>> : public std::true_type {};
// std::list<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGPTR_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_CGPTR_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};




//-----------------------------------------------------------------------------
//
// With Push_back and Reserve (vector, ...)
//-----------------------------------------------------------------------------
// Associated container<T>)
template<class T> struct is_linear_container_with_reserve : public std::false_type {};
template<class A, class B> struct is_linear_container_with_reserve<std::vector<A, B>> : public std::true_type {};
template<class A, size_t B> struct is_linear_container_with_reserve<CGD::array<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container_with_reserve<std::vector<CGPTR<A>, B>> : public std::false_type {};
template<class A, size_t B> struct is_linear_container_with_reserve<CGD::array<CGPTR<A>, B>> : public std::false_type {};
// std::vector<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_array<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Associated container<CGPTR<T>>)
template<class T> struct is_linear_CGPTR_container_with_reserve : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container_with_reserve<std::vector<A, B>> : public std::false_type {};
template<class A, size_t B> struct is_linear_CGPTR_container_with_reserve<CGD::array<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container_with_reserve<std::vector<CGPTR<A>, B>> : public std::true_type {};
template<class A, size_t B> struct is_linear_CGPTR_container_with_reserve<CGD::array<CGPTR<A>, B>> : public std::true_type {};
// std::vector<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_array<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGPTR_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_vector<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


														
//-----------------------------------------------------------------------------
//
// With Insert
//-----------------------------------------------------------------------------
// Set container<T>)
template<class T> struct is_set_container : public std::false_type {};
template<class A, class B, class C> struct is_set_container<std::set<A, B, C>> : public std::true_type {};
template<class A, class B, class C> struct is_set_container<std::multiset<A, B, C>> : public std::true_type {};
template<class A, class B, class C> struct is_set_container<std::set<CGPTR<A>, B, C>> : public std::false_type {};
template<class A, class B, class C> struct is_set_container<std::multiset<CGPTR<A>, B, C>> : public std::false_type {};

// std::set<T>/ std::multiset<T>
template<typename T>		class _AF<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};

// Set container<T>)
template<class T> struct is_set_CGPTR_container : public std::false_type {};
template<class A, class B, class C> struct is_set_CGPTR_container<std::set<A, B, C>> : public std::false_type {};
template<class A, class B, class C> struct is_set_CGPTR_container<std::multiset<A, B, C>> : public std::false_type {};
template<class A, class B, class C> struct is_set_CGPTR_container<std::set<CGPTR<A>, B, C>> : public std::true_type {};
template<class A, class B, class C> struct is_set_CGPTR_container<std::multiset<CGPTR<A>, B, C>> : public std::true_type {};
// std::set<T>/ std::multiset<T>
template<typename T>		class _AF<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGPTR_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


//-----------------------------------------------------------------------------
//
// For Associated Container
//-----------------------------------------------------------------------------
// Associated container<T>)
template<class T> struct is_associative_container : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::map<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::multimap<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::unordered_set<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::unordered_multiset<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E> struct is_associative_container<std::unordered_map<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E> struct is_associative_container<std::unordered_multimap<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::map<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::multimap<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::unordered_set<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_container<std::unordered_multiset<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E> struct is_associative_container<std::unordered_map<A, CGPTR<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E> struct is_associative_container<std::unordered_multimap<A, CGPTR<B>, C, D, E>> : public std::false_type {};


// Associated container<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};

template<class T> struct is_associative_CGPTR_container : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::map<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::multimap<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::unordered_set<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::unordered_multiset<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E> struct is_associative_CGPTR_container<std::unordered_map<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E> struct is_associative_CGPTR_container<std::unordered_multimap<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::map<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::multimap<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::unordered_set<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D> struct is_associative_CGPTR_container<std::unordered_multiset<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E> struct is_associative_CGPTR_container<std::unordered_map<A, CGPTR<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E> struct is_associative_CGPTR_container<std::unordered_multimap<A, CGPTR<B>, C, D, E>> : public std::true_type {};
// Associated container<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGPTR_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


}
