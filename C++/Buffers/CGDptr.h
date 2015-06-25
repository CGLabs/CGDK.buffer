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
// CGD::ptr
//
// 1. ptr...
//    1) ptr는 CGD::buffer와 거의 동일한 동작을 하지만 len을 가지고 있지 않고
//       단지 포인터 하나만 가지고 있는 객체이다.
//    2) 따라서 buffer를 읽고 쓰는 것은 모두  현재 Ptr을 기준으로만 읽고 쓰도록
//       동작하며 size()와 같은 키기를 알수 있는 기능은 없다.
//    3) 동작은 CGD::buffer와 유사하지만 현재 주소 ptr 하나의 값만 가지므로 
//       완전히 동일하지 않다.
//    4) 하지만 append/subtract 등의 이름을 CGD::buffer를 대체하여 사용할 경우
//       동일성을 유사하기 CGD::buffer와 동일하게 사용되었다.
//    5) prepend/append과 extract/subtract은 모두 현재 포인터를 기준으로
//       동작된다.
//    6) front() 함수는 있으나 back()함수는 없다.
//
// 2. CGD::ptr의 장단점
//    1) 그에 비해 단점은 길이를 Check하지 않는 관계로 Bounding Check가 수행되지 
//       않는다.
//
//-----------------------------------------------------------------------------
namespace CGD
{

class ptr
{
public:
	// 1) Costructor
			ptr()														{}
			ptr(_In_ void* _Ptr) : m_ptr((char*)_Ptr)					{}
			ptr(_In_ char* _Ptr) : m_ptr(_Ptr)							{}
			ptr(_In_ const ptr& _Ref) : m_ptr(_Ref.get_ptr())			{	_CGD_BOUND_INFO(m_bound=_Ref._get_check_bound());}
			template <class T>
			ptr(const T& _Ref) : m_ptr(_Ref.get_ptr())					{	static_assert(std::is_base_of<CGD::buffer, T>::value || std::is_base_of<CGD::ptr, T>::value, "Must be CGD::buffer or CGD::ptr or derived");  _CGD_BOUND_INFO(m_bound=_Ref._get_check_bound());}
public:
	// 2) exist/empty
			char*				get_ptr() const							{	return m_ptr;}
			bool				exist() const							{	return m_ptr!=nullptr;}
			bool				empty() const							{	return m_ptr==nullptr;}
			char*				clear()									{	char* p=m_ptr; m_ptr=nullptr; return p;}

			void				swap(ptr& _Rhs)							{	char* a=m_ptr; m_ptr=_Rhs.m_ptr; _Rhs.m_ptr=a;}

	// 3) prepend
			template <size_t ISIZE>
			void*				prepend()								{	return _prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					prepend()								{	return *(T*)_prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA sizeof(T));}
			template <class T>
			typename _AF<T>::t	prepend(const T& _Data)					{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T, size_t N>
			typename _AF<T[N]>::t prepend(const T (&_Data)[N])			{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T>
			T*					prepend(_In_reads_(_Count) const T* _Data, _In_ size_t _Count) {	return _prepend_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				prepend(_In_ const std::initializer_list<T>& _List){	_prepend_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _List); return get_front_ptr();}
		#endif
			template<class I> 
			typename std::enable_if<is_iterator<I>::value, size_t>::type 
								prepend(I _First, I _Last)				{	return _Xprepend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				prepend(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)	{	return _prepend_buffer(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer);}

			template <class T>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const T* _Text)			{ return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Text) { return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}
			template <class T>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Text)			{ return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Text) { return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

	// 4) append
			template <size_t ISIZE>
			void*				append()								{	return _append_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					append()								{	return *(T*)_append_skip(_CGD_BOUND_INFO_GET _CGD_COMMA sizeof(T));}
			template <class T>
			typename _AB<T>::t	append(const T& _Data)					{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data); }
			template <class T, size_t N>
			typename _AB<T[N]>::t append(const T(&_Data)[N])			{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data); }
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				append(const std::initializer_list<T>& _List){	void* p=get_back_ptr(); _append_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _List); return p;}
		#endif
			template<class I> 
			typename std::enable_if<is_iterator<I>::value, size_t>::type 
								append(I _First, I _Last)				{	return _Xappend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			template <class T>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const T* _String)			{ return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _String) { return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String.p);}
			template <class T, class F>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}
			template <class T>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const T* _Text)				{ return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Text) { return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const T* _Format, F, ...)	{ va_list templist; va_start(templist, _Format); auto p=_append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

	// 5) extract/subtract
			template <size_t ISIZE>
			void*				extract()								{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			void*				extract(_In_ size_t _Length)			{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}
			template <class T>
			typename _BF<T>::t	extract()								{	return _extract<T>(_CGD_BOUND_INFO_GET);}
			template <class T>
			size_t				extract(__out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=INT_MAX) {	return _extract_string_copy(_CGD_BOUND_INFO_GET _CGD_COMMA _String, _Length_in_words);}
			char*				extract_web_modify()					{	return _extract_web_modify(_CGD_BOUND_INFO_GET);}
			template <class T>
			std::basic_string<T> extract_text(T _Terminal=NULL)			{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal);}
			template <class T>
			T*					extract_text(T _Terminal, T _Modify)	{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal, _Modify);}
			template <class T>
			T&					subtract()								{	return _subtract_general<T>(_CGD_BOUND_INFO_GET);}
			void*				subtract(_In_ size_t _Length)			{	return _subtract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}

	// 6) front
			char*				front(_In_ int _Offset=0) const			{	return _front(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ int _Offset=0) const			{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ POS& _Pos) const				{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Pos.offset);}

	// 7) begin
			ptr					begin(_In_ int _Offset=0) const			{	return _begin(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			
	// 8) Operator Overloading
			// [operator] Overloading ++/--
			ptr&				operator++()							{	++m_ptr; return *this;}
			ptr					operator++(int)							{	return ptr(m_ptr++);}
			ptr&				operator--()							{	--m_ptr; return *this;}
			ptr					operator--(int)							{	return ptr(m_ptr--);}
			// [operator] +/-
			ptr					operator+(size_t _Rhs) const			{	return ptr(m_ptr+_Rhs);}
			ptr					operator+(const SKIP& _Rhs) const		{	return ptr(m_ptr+_Rhs.m_skip);}
			ptr					operator-(size_t _Rhs) const			{	return ptr(m_ptr-_Rhs);}
			size_t				operator-(const ptr& _Rhs) const		{	return m_ptr-_Rhs.m_ptr;}
			// [operator] +=/-=
			ptr&				operator+=(const buffer& _Rhs)			{	_append_buffer(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}
			ptr&				operator+=(size_t _Rhs)					{	m_ptr+=_Rhs; return *this;}
			ptr&				operator+=(const SKIP& _Rhs)			{	m_ptr+=_Rhs.m_skip; return *this;}
			ptr&				operator-=(size_t _Rhs)					{	m_ptr-=_Rhs; return *this;}
			// [operator] =
			template <class T>
			ptr&				operator=(const T& _Rhs)				{	static_assert(std::is_base_of<CGD::buffer, T>::value || std::is_base_of<CGD::ptr, T>::value, "Must be CGD::buffer or CGD::ptr or derived");  m_ptr=_Rhs.get_ptr(); _CGD_BOUND_INFO(m_bound=_Rhs._get_check_bound()); return *this;}
			// [operator] >> - extract
			template <class T>
			ptr&				operator>>(T& _Rhs)						{	_Rhs=_extract<T>(_CGD_BOUND_INFO_GET); return *this;}
			// - Operator << - append
			template <class T>
			ptr&				operator<<(const T& _Rhs)				{	_append(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}
			// [operator] Conversion
								operator const void*() const			{	return (void*)m_ptr;}
								operator const char*() const			{	return m_ptr;}
								operator void*()						{	return (void*)m_ptr;}
								operator char*()						{	return m_ptr;}
public:
	// Push Front) 
			template <class T>
			typename _AF<T>::t	_prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data)			{	return _AF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t _prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N])		{	return _AF<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			void*				_prepend_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size);
			template <class T>
			T&					_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data);
			template <class T> 
			typename std::enable_if<is_memcopy_able<T>::value, void*>::type
								_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T> 
			typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
								_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T>
			void*				_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size=INT32_MAX);
			template <class T>
			void*				_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& p_str);
			template <class T, size_t N>
			void*				_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::const_string<T,N>& _constString);
			template <class T>
			void*				_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList);
			template <class T>
			size_t				_prepend_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String);
			template <class T, size_t N>
			size_t				_prepend_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText);
			template <class T>
			size_t				_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList);
			void*				_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer);
			void*				_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer);
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				_prepend_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::initializer_list<T>& _list)	{	void* v=m_ptr;for(auto& iter:_list){ _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter);} return v;}
		#endif
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template <class T>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Data) { _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Data)); return m_ptr; }
			template <class T, class... TREST>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) { _prepend_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA(const std::tuple<TREST...>&)_Tupple); _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple)); return m_ptr;}
		#endif
	// Push Back) 
			template <class T>
			typename _AB<T>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data)				{	return _AB<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t _append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N])		{	return _AB<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			void*				_append_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
			template <class T>
			T&					_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data);
			template <class T> 
			typename std::enable_if<is_memcopy_able<T>::value, void*>::type
								_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T> 
			typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
								_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T>
			void*				_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String);
			template <class T>
			void*				_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& p_str);
			template <class T, size_t N>
			void*				_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString);
			template <class T>
			void*				_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList);
			template <class T>
			size_t				_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String);
			template <class T, size_t N>
			size_t				_append_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText);
			template <class T>
			size_t				_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList);
			void*				_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer);
			void*				_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer);
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				_append_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA const std::initializer_list<T>& _list)	{	void* v=m_ptr;for(auto& iter:_list){ _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter);} return v;}
		#endif
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template <class T>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Data) { void* p = m_ptr; _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Data)); return p; }
			template <class T, class... TREST>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) { void* p=m_ptr; _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple)); _append_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA(const std::tuple<TREST...>&)_Tupple); return p;}
		#endif
	// extract) 
			template <class T>
			typename _BF<T>::t	_extract(_CGD_BOUND_INFO_PARAM)			{	return _BF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this);}
			void*				_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
			template <class T>
			T*					_extract_string_pointer(_CGD_BOUND_INFO_PARAM);
			template <class T>
			std::basic_string<T> _extract_string(_CGD_BOUND_INFO_PARAM);
			template <class T>
			COUNT_T				_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=INT_MAX);
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template <class T>
			void				_extract_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ std::tuple<T>& _Tupple) { std::get<0>(_Tupple) = _extract<T>(_CGD_BOUND_INFO_PASS); }
			template <class T, class... TREST>
			void				_extract_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ std::tuple<T, TREST...>& _Tupple){	std::get<0>(_Tupple)=_extract<T>(_CGD_BOUND_INFO_PASS); _extract_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA (std::tuple<TREST...>&)_Tupple);}
		#endif
			template <class T>
			std::basic_string<T> _extract_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ T _CharTerminal);
			template <class T>
			T*					_extract_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ T _CharTerminal,  _In_ T _CharChange);
			char*				_extract_web_modify(_CGD_BOUND_INFO_PARAM);
			std::string			_extract_web(_CGD_BOUND_INFO_PARAM);
			char*				_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* p_pstrBuffer, _In_ size_t _Buffer_Size = INT_MAX);
			void*				_extract_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_ void* _Buffer);
			// subtract) 
			template <class T>
			T&					_subtract_general(_CGD_BOUND_INFO_PARAM);
			void*				_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size);
	// front) 
			char*				_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			template <class T>
			typename _RH<T>::t	_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const	{	return _RH<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Offset);}
			template <class T>
			T&					_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			template <class T>
			T*					_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			template <class T>
			std::basic_string<T> _front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			char*				_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
	// begin)
			ptr					_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
	// Etc)
			void				_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA size_t _Offset, size_t _Size, void * _Buffer) const;
public:
			char*				get_front_ptr() const					{	return m_ptr;}
			char*				get_back_ptr() const					{	return m_ptr;}

	// Check Bound) 
		#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
			CGD_CHECK_BOUND		_get_check_bound() const	{	return m_bound;}
			CGD_CHECK_BOUND		m_bound;
		#endif
public:
			char*				m_ptr;
};

}

#include "CGDptr.inl"
