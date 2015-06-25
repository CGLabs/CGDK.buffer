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
// CGBuffer
//
// 1. CGD::buffer는...
//    1) buf, lne을 가진 buffer이다.
//    2) prepend/pushback을 사용해 buffer에 데이터를 추가할수 있고
//    3) extract/subtract을 사용해 buffer에 데이터를 추출해 올 수 있다.
//    4) front/back함수를 사용헤 데이터를 읽어올 수 있다.
//    5) WIN32의 WSABUF를 완전히 대체할 수 있도록 제작되었다.
//
// 주의) CGD:buffer는 debug 모드일 때에는 Bound Check 기능이 있다.
//       Release 모드에서는 그 기능이 제거되도록 설정되어 있다. Bounding Check
//       과정은 추가적 부하를 유발할 수 있으므로 Release모드엣는 사용하지 않는다.
//
//-----------------------------------------------------------------------------
namespace CGD
{

class  buffer
{
public:
	// 1) Costructor
			buffer() : len(0), buf(nullptr) {}
			buffer(_In_opt_ void* _Ptr, _In_ uint32_t _Len=0) : len(_Len), buf((char*)_Ptr) {}
			buffer(_In_ const buffer& _Buffer) : len(_Buffer.len), buf(_Buffer.buf) {}
public:
	// 2) exist/empty
			char*				get_ptr() const							{	return buf;}
			bool				exist() const							{	return buf!=nullptr;}
			bool				empty() const							{	return buf==nullptr;}
			size_t				size() const							{	return (size_t)len;}
			size_t				length() const							{	return (size_t)len;}
			char*				clear()									{	char* p=buf; buf=nullptr; len=0; return p;}
			void				set_buffer(_In_opt_ void* _Ptr, _In_ uint32_t _Len=0) {	buf=(char*)_Ptr; len=_Len;}

			void				swap(buffer& _Rhs)						{	char* a=buf;uint32_t b=len; buf=_Rhs.buf; len=_Rhs.len; _Rhs.buf=a; _Rhs.len=b;}
			void				copy(const buffer& _Source)				{	memcpy(buf, _Source.buf, _Source.len); len=_Source.len;}
			buffer				clone()									{	buffer a((char*)CGMALLOC(len), len); memcpy(a.buf, buf, len); return std::move(a); }
			buffer				split(uint32_t _Offset)					{	if(len<_Offset) _Offset=len; uint32_t newSize=len-_Offset; len=_Offset; return buffer(buf+_Offset, newSize);}

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
			void*				prepend(_In_ const std::initializer_list<T>& _list){	_prepend_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _list); return get_front_ptr();}
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
			typename _AB<T>::t	append(const T& _Data)					{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t append(const T(&_Data)[N])			{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T>
			void*				append(_In_reads_(_Count) const T* _Data, _In_ size_t _Count) {	return _append_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				append(const std::initializer_list<T>& _List){	void* p=get_back_ptr(); _append_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _List); return p;}
		#endif
			template<class I> 
			typename std::enable_if<is_iterator<I>::value, size_t>::type
								append(I _First, I _Last)				{	return _Xappend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				append(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)	{	return _append_buffer(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer);}

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
			size_t				extract(__out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=INT_MAX)	{	return _extract_string_copy(_String, _Length_in_words);}
			char*				extract_web_modify()					{	return _extract_web_modify(_CGD_BOUND_INFO_GET);}
			template <class T>
			std::basic_string<T> extract_text(T _Terminal=NULL)			{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal);}
			template <class T>
			T*					extract_text(T _Terminal, T _Modify)	{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal, _Modify);}
			template <class T>
			T&					subtract()								{	return _subtract_general<T>(_CGD_BOUND_INFO_GET);}
			void*				subtract(_In_ size_t _Length)			{	return _subtract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}

	// 6) front/back
			char*				front(_In_ int _Offset=0) const			{	return _front(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ int _Offset=0) const			{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ POS& _Pos) const				{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Pos.offset);}
			char*				back(_In_ int _Offset=0) const			{	return _back(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	back(_In_ int _Offset=0) const			{	return _back<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	back(_In_ POS& _Pos) const				{	return _back<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Pos.offset);}

	// 7) begin/end
			buffer				begin(_In_ int _Offset=0) const			{	return _begin(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			buffer				end(_In_ int _Offset=0) const			{	return _end(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}

	// 8) Operator Overloading
			// [operator] Overloading ++/--
			buffer&				operator++()							{	++buf; --len; return *this;}
			buffer				operator++(int)							{	return buffer(buf++, len--);}
			buffer&				operator--()							{	--buf; ++len; return *this;}
			buffer				operator--(int)							{	return buffer(buf--, len++);}
			// [operator] +/-
			buffer				operator+(size_t _Rhs) const			{	return buffer(buf+_Rhs, (len>(uint32_t)_Rhs) ? (len-(uint32_t)_Rhs) : 0);}
			buffer				operator+(const SKIP& _Rhs) const		{	return buffer(buf+_Rhs.m_skip, (len>(uint32_t)_Rhs.m_skip) ? (len-(uint32_t)_Rhs.m_skip) : 0);}
			buffer				operator-(size_t _Rhs) const			{	return buffer(buf-_Rhs, len+(uint32_t)_Rhs);}
			// [operator] +=/-=
			buffer&				operator+=(size_t _Rhs)					{	buf+=_Rhs; len-=(uint32_t)_Rhs; return *this;}
			buffer&				operator+=(const SKIP& _Rhs)			{	buf+=_Rhs.m_skip; len-=(uint32_t)_Rhs.m_skip; return *this;}
			buffer&				operator+=(const buffer& _Rhs)			{	_append_buffer(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}
			buffer&				operator-=(size_t _Rhs)					{	buf-=_Rhs; len+=(uint32_t)_Rhs; return *this;}
			// [operator] =
			buffer&				operator=(const buffer& _Rhs)			{	buf=_Rhs.buf; len=_Rhs.len; return *this;}
			// [operator] >> - extract
			template <class T>
			buffer&				operator>>(T& _Rhs)						{	_Rhs=_extract<T>(_CGD_BOUND_INFO_GET); return *this;}
			// - Operator << - append
			template <class T>
			buffer&				operator<<(const T& _Rhs)				{	_append(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}
			// [operator] Conversion
public:
	// Push Front) 
			template <class T>
			typename _AF<T>::t	_prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data) {	return _AF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AF<T[N]>::t	_prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N]) {	return _AF<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
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
			template <class T>
			void*				_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String, _In_ size_t _Length);
			template <class T, size_t N>
			void*				_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::const_string<T,N>& _constString);
			template <class T>
			void*				_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list	_ArgList);
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
			size_t				_prepend_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::initializer_list<T>& _list) {	int i=0;for(auto& iter:_list){ _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter); ++i;} return i;}
		#endif
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template <class T>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Data) { _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Data)); return m_buf; }
			template <class T, class... TREST>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) {	_prepend_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA (const std::tuple<TREST...>&)_Tupple); _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple));; return m_buf;}
		#endif
	// Push Back) 
			template <class T>
			typename _AB<T>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data) {	return _AB<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N]) {	return _AB<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T>
			typename _AB<T>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const CGPTR<T>& _Data) {	return _AB<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, *_Data);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			size_t				_append_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::initializer_list<T>& _list) {	int i=0;for(auto& iter:_list){ _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter); ++i;} return i;}
		#endif
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
			template <class T>
			void*				_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String, _In_ size_t _Length);
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
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template<class T>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Data) { void* p = buf + len; _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Data)); return p; }
			template<class T, class... TREST>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) { void* p = buf + len; _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple)); _append_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA(const std::tuple<TREST...>&)_Tupple); return p; }
		#endif
	// extract) 
			template <class T>
			typename _BF<T>::t	_extract(_CGD_BOUND_INFO_PARAM)								{	return _BF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this);}
			void*				_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
			template <class T>
			T*					_extract_string_pointer(_CGD_BOUND_INFO_PARAM);
			template <class T>
			std::basic_string<T> _extract_string(_CGD_BOUND_INFO_PARAM);
			template <class T>
			COUNT_T				_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=INT_MAX);
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template<class T>
			void				_extract_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ std::tuple<T>& _Tupple) { std::get<0>(_Tupple) = _extract<T>(_CGD_BOUND_INFO_PASS); }
			template<class T, class... TREST>
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
			void*				_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
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
	// back)
			char*				_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			template <class T>
			typename _RH<T>::t	_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const	{	int _temp=len+_Offset;return _RH<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _temp);}
			template <class T>
			T&					_back_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
	// begin)
			buffer				_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			buffer				_end(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
	// Etc)
			template <class T>
			COUNT_T				_get_front_string_length(_CGD_BOUND_INFO_PARAM);
			void				_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ size_t _Offset, _In_ size_t _Size, _In_ void* _Buffer) const;

public:
			char*				get_front_ptr() const					{	return buf;}
			char*				get_back_ptr() const					{	return buf+len;}

	// Check Bound) 
		#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
			CGD_CHECK_BOUND		_get_check_bound() const	{	return CGD_CHECK_BOUND();}
		#endif
public:
			uint32_t			len;
			_Field_size_bytes_(len) char*	buf;
};

}

#include "CGDbuffer.inl"
