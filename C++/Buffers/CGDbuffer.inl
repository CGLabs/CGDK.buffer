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
namespace CGD
{

// Push Front) 
inline void* buffer::_prepend_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size)
{
	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf-_Size)>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]를 _Size만큼 줄인다.
	buf	 -= _Size;

	// 2) [원본_버퍼_길이]를 _Size만큼 늘린다. 
	len	 += (uint32_t)_Size;
	
	// Return) 
	return (void*)buf;
}

template <class T>
T& buffer::_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) Pointer형이면 안됀다.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeof(T))>=_bound.bound_lower && buf<=_bound.bound_upper);
	
	// 1) [원본_버퍼]에 값을 복사해 넣는다.
	*(T*)(buf-sizeof(T))	 = _Data;
	
	// 2) [원본_버퍼_포인터]의 크기를 sizeof(T)만큼 줄인다.
	buf	-= sizeof(T);
	
	// 3) [원본_버퍼_길이]를 sizeof(T)만큼 늘린다. 
	len	+= sizeof(T);
	
	// Return) 
	return *(T*)buf;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
buffer::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// 1) [데이터_갯수]만큼 데이터들을 통채로 복사한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T)*_Count, _Data);

	// 2) [데이터_갯수]를 써넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	buf;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
buffer::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// 1) [데이터_갯수]만큼 데이터들을 추가한다.
	for(int i=(int)(_Count-1);i>=0;--i)
	{
		_prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// 2) [데이터_갯수]를 써넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	buf;
}

inline void* buffer::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)
{
	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf-_Size)>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]의 크기를 _Size만큼 줄인다.
	char* p	 = buf -_Size;
	
	// Check) _Size가 0이면 끝낸다.
	if(_Size==0) return p;

	// 2) [원본_버퍼_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}

	// 3) [원본_버퍼_포인터]를 갱신한다.
	buf	 = p;

	// 4) [원본_버퍼_길이]를 _Size만큼 늘린다. 
	len	+= (uint32_t)_Size;

	// Return) 
	return (void*)buf;
}

template <class T>
void* buffer::_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size)
{
	// Check) _Buffer_Size가 0이하면 안된다.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// 1) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound 검사를 한다.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) [문자열]을 복사한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String);

	// 3) Size를 넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);
	
	// Return) 첫위치를 리턴함.
	return	buf;
}

template <class T>
void* buffer::_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
	size_t	lengthString = (size_t)_String.length()+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound를 검사한다.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) [문자열]을 [문자열_길이]만큼 복사한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String.c_str());

	// 3) [문자열_길이]를 써넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);

	// Return) String의 제일 처음 위치를 리턴함!!
	return	buf;
}

template <class T, size_t N>
void* buffer::_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// 1) [문자열_길이]와 복사할 크기를 구한다.
	const size_t	lengthString = _constString.size();
	size_t			sizeString	 = lengthString*sizeof(T);

	// 2) 복사할 [버퍼_위치]를 구한다.
	char*	p = buf - sizeString - sizeof(COUNT_T);

	// Check) Lower Bound와 Uppder Bound를 검사한다.
	_CGD_BUFFER_BOUND_CHECK(p>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 3) [문자열_길이]를 저장한다.
	*(COUNT_T*)(p) = (COUNT_T)lengthString;

	// 4) [원본_버퍼_끝_포인터]에 [문자열]을 복사한다.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 5) sizeof(COUNT_T)를 더한다.
	sizeString += sizeof(COUNT_T);

	// 6) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
	buf -= (uint32_t)sizeString;
	len += (uint32_t)sizeString;

	// Return) 
	return	buf;
}


template <class T>
void* buffer::_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _Format이 nullptr이면 안된다.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// Declare)
	const size_t	TEMP_STRING_BUFFER_SIZE		= 2048;

	// 1) [임시_버퍼]를 할당한다
#ifdef MEM_POOL_ALLOC
	CGPTR<ICGBuffer>	pbufferTemp	 = MEM_POOL_ALLOC(TEMP_STRING_BUFFER_SIZE);
	T*	pStringStart = (T*)pbufferTemp.buf;
#else 
	T*	pStringStart = (T*)CGMALLOC(TEMP_STRING_BUFFER_SIZE);
#endif
	// 3) [원본_버퍼_시작_크기]에 [형식_문자열]를 써넣는다.
	size_t	lengthString = _Xvsprintf(pStringStart, _Format, _ArgList)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// 4) [목표_포인터]를 구한다.
	T*	p	 = buf-sizeString;

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((p-sizeof(COUNT_T))>=_bound.bound_lower);
	
	// 6) [문자열]을 복사한다.
	memcpy(p, pStringStart, sizeString);

	// 7) [목표_포인터]를 sizeof(COUNT_T)만큼을 뺀다.
	p	-= sizeof(COUNT_T);

	// 8) [문자열_길이]를 써넣는다.
	*(COUNT_T*)p	 = (COUNT_T)lengthString;

	// 7)[원본_버퍼_포인터]를 업데이트한다.
	buf	 = p;
	len	+= (uint32_t)(sizeString+sizeof(COUNT_T));

	// 6) [임시_버퍼]할당 해제
#ifdef MEM_POOL_ALLOC
#else 
	CGFREE(pStringStart);
#endif

	// Return) 
	return	buf;
}

template <class T>
size_t buffer::_prepend_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// 1) [문자열_길이]를 구한다.
	size_t	lengthString = std::char_traits<T>::length(_String);
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString)>=_bound.bound_lower);

	// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
	T*	p = buf-sizeString;
	
	// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
	if(p!=_String)
	{
		memcpy(p, _String, sizeString);
	}

	// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
	buf		 = p;
	len		+= sizeString;

	// Return) 
	return lengthString;
}

template <class T, size_t N>
size_t buffer::_prepend_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText)
{
	// Declare) 
	const size_t	sizeString = (_constText.size()-1)*sizeof(T);

	// Check) Bound Check
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString)>= _bound.bound_lower && buf<=_bound.bound_upper);

	// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
	char*	p = buf - sizeString;

	// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
	memcpy(p, _constText.p, sizeString);

	// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
	buf		 = p;
	len		+= sizeString;

	// Return) 
	return	_constText.size();
}


template <class T>
size_t buffer::_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list	_ArgList)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// Declare)
	const size_t	TEMP_STRING_BUFFER_SIZE		= 2048;

	// 1) [임시_버퍼]를 할당한다
#ifdef MEM_POOL_ALLOC
	CGPTR<ICGBuffer>	pbufferTemp	 = MEM_POOL_ALLOC(TEMP_STRING_BUFFER_SIZE);
	T*	pStringStart = (T*)pbufferTemp.buf;
#else 
	T*	pStringStart = (T*)CGMALLOC(TEMP_STRING_BUFFER_SIZE);
#endif
	// 2) [원본_버퍼_시작_크기]에 [형식_문자열]를 써넣는다.
	size_t	lengthString	 = _Xvsprintf(pStringStart, _Format, _ArgList);
	size_t	sizeString		 = lengthString*sizeof(T);

	// 3) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
	T*		p	 = buf-sizeString;

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(p>=_bound.bound_lower);

	// 4) [문자열]을 추가한다.
	memcpy(p, pStringStart, sizeString);

	// 5) [임시_버퍼]할당 해제
#ifdef MEM_POOL_ALLOC
#else 
	CGFREE(pStringStart);
#endif

	// 6) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
	buf		 = p;
	len		+= sizeString;

	// Return) 
	return lengthString;
}

inline void* buffer::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer)	
{
	// By Pass)
	return _prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Buffer.len, _Buffer.buf);
}

inline void* buffer::_append_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length가 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+_Length)<=_bound.bound_upper);
	
	// 1) [원본_버퍼_끝_포인터]를 구한다.
	char* p	 = buf+len;
	
	// 2) [원본_버퍼_길이]를 _Length만큼 늘린다. 
	len		+= (uint32_t)_Length;

	// Return) [원본_버퍼_끝_포인터]값을 리턴한다.
	return (void*)p;
}

template <class T>
T& buffer::_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) Pointer형이면 안됀다.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T))<=_bound.bound_upper);

	// 1) [원본_버퍼_끝_포인터]를 구한다.
	T* p	= (T*)(buf+len);
	
	// 2) [원본_버퍼_끝_포인터]에 값(_Data)를 써넣는다.
	*p		= _Data;
	
	// 3) [원본_버퍼_길이]를 sizeof(T)만큼 늘린다. 
	len		+= (uint32_t)sizeof(T);
	
	// Return) [원본_버퍼_끝_값]을 리턴한다.
	return *p;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
buffer::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T)*_Count)<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	T*	p	 = (T*)(buf+len);

	// 1) [데이터_갯수]를 써넣는다.
	_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [데이터]들을 통채로 복사한다.
	_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Count*sizeof(T), _Data);

	// Return) 
	return	p;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
buffer::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T)*_Count)<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	T*	p	 = (T*)(buf+len);

	// 1) [데이터_갯수]를 써넣는다.
	_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [데이터]들을 추가한다.
	for(size_t i=0;i<_Count;++i)
	{
		_append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// Return) 
	return	p;
}

inline void* buffer::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer) 
{
	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+_Size)<=_bound.bound_upper);

	// 1) [원본_버퍼_끝_포인터]를 얻는다.
	char*	p = buf+len; 
	
	// Check) _Size가 0이면 끝낸다.
	if(_Size==0) return p;
	
	// 2) [원본_버퍼_끝_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}
	
	// 3) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
	len		+= (uint32_t)_Size; 
	
	// Return) 
	return (void*)p;
}

template <class T>
void* buffer::_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String)
{
	// 1) 문자열을 복사할 위치를 구한다.
	char*	strDest	 = buf+len;

	// 2) [문자열]을 복사한다.
	size_t	lengthString	 = _Xappend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _String);

	// 3) [문자열_길이]를 저장한다.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [버퍼_길이]를 업데이트한다.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) 리턴
	return	strDest;
}

template <class T>
void* buffer::_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) [목표_포인터]를 구한다.
	char*	strDest	 = buf+len;

	// 2) [문자열]을 [목표_포인터]에 복사한다.
	size_t	lengthString	 = _Xappend_string(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _String.c_str(), _String.length());

	// 3) [문자열_길이]를 써넣는다.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [버퍼_길이]를 업데이트한다.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) 리턴
	return	strDest;
}

template <class T, size_t N>
void* buffer::_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// Constexpr)
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf + len) >= _bound.bound_lower && (buf + len+sizeof(COUNT_T) + sizeString) <= _bound.bound_upper);

	// 1) [원본_버퍼_끝_포인터]를 얻는다.
	char*	p = buf + len;

	// 2) [문자열_길이]를 저장한다.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 3) [원본_버퍼_끝_포인터]에 [문자열]을 복사한다.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 4) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
	len += (uint32_t)(sizeString+sizeof(COUNT_T));

	// Return) 
	return	(void*)p;
}

template <class T>
void* buffer::_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// 1) [문자열]을 복사할 위치를 구한다.
	char*	strDest	 = buf+len;

	// 2) [문자열]을 복사한다.
	const size_t	lengthString	 = _Xappend_string_format(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _Format, _ArgList);

	// 3) [문자열_길이]를 저장한다.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [버퍼]를 업데이트한다.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) 리턴
	return	strDest;
}

template <class T>
size_t buffer::_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower);

	// 1) [문자열]의 길이를 구한다.
	const size_t	lengthString = std::char_traits<T>::length(_String);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len+ sizeString)<=_bound.bound_upper);

	// 2) [문자열]을 복사한다.
	memcpy(buf + len, _String, sizeString);

	// 3) [문자열_길이]만큼 더한다.
	len += (uint32_t)sizeString;

	// Return) 
	return	lengthString;
}

template <class T, size_t N>
size_t buffer::_append_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText)
{
	// Declare) 
	const size_t	lengthString = _constText.size()-1;
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(buf+len >= _bound.bound_lower && (buf+len+sizeString)<_bound.bound_upper);

	// 1) [문자열]을 복사하고 [문자열_길이]만큼 더한다.
	memcpy(buf + len, _constText.p, sizeString);

	// 2) [문자열_길이]만큼 더한다.
	len += (uint32_t)sizeString;

	// Return) 
	return	lengthString;
}

template <class T>
size_t buffer::_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower);

	// 1) [문자열]을 복사할 위치를 저장한다.
	T*	strDest = (T*)(buf + len);

	// 2) [문자열]을 복사한다.
	const size_t	lengthString = _Xvsprintf(strDest, _Format, _ArgList);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 3) [버퍼]를 업데이트한다.
	len += (uint32_t)sizeString;

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+len) <= _bound.bound_upper);

	// Return) 리턴
	return	lengthString;
}

inline void* buffer::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer)
{
	// By-Pass) 
	return _append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Buffer.len, _Buffer.buf);
}

inline void* buffer::_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length가 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower && (buf+_Length)<=_bound.bound_upper);

	// Check) [원본_버퍼_크기]보다 _Length가 커야 한다.
	_CGD_BUFFER_BOUND_CHECK(len>=_Length);
	
	// 1) [원본_버퍼_포인터]의 크기를 임시로 저장한다.
	char* p	 = buf;
	
	// 1) [원본_버퍼_포인터]의 크기를 _Length만큼 늘리고 [원본_버퍼_길이]는 줄인다.
	buf		+= _Length;
	len		-= (uint32_t)_Length;
	
	// Return) [원본_버퍼_처음_포인터]
	return p;
}

template <class T>
COUNT_T buffer::_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(p_iLengthInWords) T* _String, _In_ size_t p_iLengthInWords)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _LengthInWords가 0이하면 안된다.
	CGD_ASSERT(_LengthInWords>=0, throw std::invalid_argument("_LengthInWords is invalid [0] (" __FUNCTION__ ")"));

	// 1) [데이터_크기]를 얻어온다.(COUNT_T[문자열_길이]+length(String))
	COUNT_T	lengthString	 = _get_front_string_length<T>(_CGD_BOUND_INFO_PASS);

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString==(COUNT_T)-1)
	{
		buf		+= sizeof(COUNT_T);
		len		-= sizeof(COUNT_T);
		return	(COUNT_T)-1;
	}

	// Check) [문자열_길이]가 [목표_버퍼_길이]보다 작은 지를 확인한다.
	if(sizeString>=p_iLengthInWords) throw std::length_error("buffer size is too small!! [5] (" __FUNCTION__ ")");

	// 2) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+size(String))
	size_t	sizeString	 = lengthString*sizeof(T);

	// 2) [복사할 위치]를 얻는다.
	const T*	p	 = buf+sizeof(COUNT_T);

	// 3) [원본_버퍼_포인터]에 [문자열을]을 복사한다.
	if(_String!=p)
	{
		memcpy(_String, p, sizeString);
	}

	// 4) 문자열 길이를 sizeof(COUNT_T)만큼 늘린다.
	sizeString	+=sizeof(COUNT_T);

	// 5) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
	buf	+= sizeString;
	len	-= (uint32_t)sizeString;

	// Return) [문자열_길이]를 리턴한다.
	return	lengthString;
}

template <class T>
T* buffer::_extract_string_pointer(_CGD_BOUND_INFO_PARAM)
{
	// 1) [데이터_크기]를 얻어온다.(COUNT_T[문자열_길이]+length(String))
	COUNT_T	sizeData	 = _get_front_string_length<T>(_CGD_BOUND_INFO_PASS);

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(sizeData==(COUNT_T)-1)
	{
		buf		+= sizeof(COUNT_T);
		len		-= sizeof(COUNT_T);
		return	nullptr;
	}

	// 2) 문자열의 제일 앞 포인터를 얻어둔다.
	T*	strString	 = (T*)(buf+sizeof(COUNT_T));

	// 2) sizeOfData 구하기
	sizeData	 = sizeData*sizeof(T)+sizeof(COUNT_T);

	// 3) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
	buf	+= sizeData;

	// 4) [원본_버퍼_길이]를 [데이터_크기]만큼 줄인다.
	len	-= (uint32_t)sizeData;

	// Return) [문자열_시작_포인터]을 리턴한다.
	return	strString;
}

template <class T>
std::basic_string<T> buffer::_extract_string(_CGD_BOUND_INFO_PARAM)
{
	return	std::basic_string<T>(_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS));
}

inline char* buffer::_extract_web(_CGD_BOUND_INFO_PARAM)
{
	// Check) Lower Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = (char*)(buf);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 잠시 buf를 저장해 놓는다.
			char*	pHead	 = buf;

			// - buf를 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			buf		 = (chNow+2);
			len		 = (uint32_t)(pEnd-chNow-1);

			// Return) 
			return	pHead;
		}
	}

	// Return) 실패! Web Message를 완성하지 못했다.
	throw	nullptr;
}

inline void* buffer::_extract_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_ void* _Buffer)
{
	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower && (buf+_Size)<=_bound.bound_upper);

	// Check) 길이가 0이면 그냥 되돌린다.
	if(_Size==0)
	{
		return	(void*)buf;
	}

	// 1) 복사한다.
	memcpy(_Buffer, buf, _Size);

	// Declare)
	void*	p	 = (void*)buf;

	// 2) _Size만큼 더한다.
	buf	+= _Size;
	len -= (uint32_t)_Size;

	// Return) 
	return	p;
}

inline char* buffer::_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* _Buffer, _In_ size_t _Buffer_Size)
{
	// Check) _Buffer_Size가 0이하면 안된다.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = (char*)(buf);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 깅리를 구한다.
			size_t	ilength = chNow - buf;

			// - 최대 버퍼를 넘지않도록 한다.
			if(ilength>(_Buffer_Size-1)) ilength=(_Buffer_Size-1);

			// - 복사한다
			memcpy(_Buffer, buf, ilength);

			// - 마지막에 NULL을 추가한다.
			*(_Buffer+ilength)	 = NULL;

			// - buf를 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			buf		 = (chNow+2);
			len		 = (uint32_t)(pEnd-chNow-1);

			// Return) 
			return	_Buffer;
		}
	}

	// Exception) 
	throw	std::out_of_range("string is too short!! [1] (" __FUNCTION__ ")");
}

template <class T>
COUNT_T buffer::_get_front_string_length(_CGD_BOUND_INFO_PARAM )
{
	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
	if(sizeof(COUNT_T)>(size_t)len) throw std::length_error("buffer is too short [0] (" __FUNCTION__ ")");

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	COUNT_T	lengthString	 = *(COUNT_T*)buf;

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString==(COUNT_T)-1)
	{
		return	(COUNT_T)-1;
	}

	// 2) String의 크기를 구한다.
	size_t	sizeString		 = lengthString*sizeof(T);

	// Check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
	if(sizeString<sizeof(T)) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 3) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+length(String))
	size_t	sizeData	 = sizeof(COUNT_T)+sizeString;

	// Check) Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+sizeData)<=_bound.bound_upper);

	// Check) [데이터_크기]가 [남은_원본_버퍼_길이](len)보다 작은지 검사한다.
	if(sizeData>(size_t)len) throw std::length_error("string is too short!! [2] (" __FUNCTION__ ")");

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(buf+sizeData-sizeof(T)) != NULL) throw std::length_error("it's invalid string! [3] (" __FUNCTION__ ")");

	// Return) [문자열_시작_포인터]을 리턴한다.
	return	lengthString;
}


inline void* buffer::_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length가 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+len-_Length)>=_bound.bound_lower && (buf+len)<=_bound.bound_upper);

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(len<_Length) throw std::length_error("Buffer Overflow!! (" __FUNCTION__ ")");

	// 1) [원본_버퍼_길이]를 _Length만큼 줄인다.
	len		-= (uint32_t)_Length;
	
	// Return) [원본_버퍼_끝_포인터]
	return (buf + len);
}

template <class T>
T& buffer::_subtract_general(_CGD_BOUND_INFO_PARAM)
{
	// Check) Pointer형이면 안됀다.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+len-sizeof(T))>=_bound.bound_lower && (buf+len)<=_bound.bound_upper);

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(len<sizeof(T)) throw std::length_error("Buffer Overflow!! [0] (" __FUNCTION__ ")");

	// 1) [원본_버퍼_길이]를 sizeof(T)만큼 줄인다.
	len		-= (int)sizeof(T);
	
	// Return) [원본_버퍼_처음_값]을 리턴한다.
	return *(T*)(buf + len);
}

inline buffer buffer::_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const	
{
	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	// Return) _Offset 이동한 버퍼 생성후 리턴(RVO)
	return buffer(buf+_Offset, (len>(uint32_t)_Offset) ? len-(uint32_t)_Offset : 0);
}

inline char* buffer::_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	return buf+_Offset;
}

template <typename T>
T& buffer::_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Pointer형이면 안됀다.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+sizeof(T))<=_bound.bound_upper);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	CGD_ASSERT((_Offset+sizeof(T))<=len, );

	// 1) [원본_버퍼_처음_포인터]+[_Offset]을 얻는다.
	T* p	 = (T*)(buf+_Offset);
	
	// 2) Offset을 Sizeof(T)증가시킨다.
	_Offset	+= (int)sizeof(T);  
	
	// Return) [원본_버퍼_처음_포인터]+[_Offset]값을 리턴한다.
	return *p;
}

template<typename T>
T* buffer::_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const 
{
	// Check) Lower Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Check) [문자열_시작_위치]가 [원본_버퍼_길이]보다 길면 안됀다.
	if((_Offset+sizeof(COUNT_T))>(uint32_t)len) throw std::out_of_range("string is too short!! [0] (" __FUNCTION__ ")");

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(buf+_Offset));

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [문자열_시작_위치]를 구한다.
	size_t	posStart	 = _Offset+sizeof(COUNT_T);

	// 3) [문자열_끝_위치]를 구한다.
	size_t	posTail		 = posStart+lengthString*sizeof(T);

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+posTail)<=_bound.bound_upper);

	// Check) [문자열_끝_위치]가 [원본_버퍼_길이]보다 크면 안됀다.
	if(posTail>(size_t)len) throw std::out_of_range("string is to long!! [2] (" __FUNCTION__ ")");

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(buf+posTail-sizeof(T))!=NULL) throw std::out_of_range("Invalid string! [3] (" __FUNCTION__ ")");
	
	// 4) 최종적으로 계산된 Offset값을 업데이트한다.
	_Offset		 = (int)posTail;

	// Return) [문자열_시작_포인터]을 리턴한다.
	return	(T*)(buf+posStart);
}

template<typename T>
std::basic_string<T> buffer::_front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Check) [원본_버퍼_길이]가 최소한 sizeof(unit32_t)보다는 길어야 한다.
	if((_Offset+sizeof(COUNT_T)+sizeof(T))>(int)len) throw std::length_error("string is too short!! [0] (" __FUNCTION__ ")");

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(buf+_Offset));

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [문자열_시작_위치]를 구한다.
	size_t	posStart	 = _Offset+sizeof(COUNT_T);

	// 3) [문자열_끝_위치]를 구한다.
	size_t	posTail		 = posStart+lengthString*sizeof(T);

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+posTail)<=_bound.bound_upper);

	// Check) [문자열_끝_위치]가 [원본_버퍼_길이]보다 크면 안됀다.
	if(posTail>(size_t)len) throw std::out_of_range("string is to long!! [2] (" __FUNCTION__ ")");

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(buf+posTail-sizeof(T))!=NULL) throw std::out_of_range("string is too short!! [3] (" __FUNCTION__ ")");
	
	// 4) 최종적으로 계산된 Offset값을 업데이트한다.
	_Offset		 = (int)posTail;

	// Return) [문자열]을 리턴한다. (RVO)
	return	std::basic_string<T>((T*)(buf+posStart));
}

inline char* buffer::_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
	if((uint32_t)_Offset>(len-1)) throw std::out_of_range("_Offset is Out of Range!! [0] (" __FUNCTION__ ")");

	// Declare)
	char*		chNow	 = (char*)(buf+_Offset);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 잠시 buf를 저장해 놓는다.
			char*	pHead	 = buf;

			// - buf를 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			//buf		 = (chNow+2);
			//len		 = (uint32_t)(pEnd-chNow-1);

			// 5) Offset을 써넣는다.
			_Offset	 = (int)(chNow+2-buf);

			// Return) 
			return	pHead;
		}
	}

	// Return) 실패! Web Message가 완료되지 않았다.
	return	nullptr;
}

inline buffer buffer::_end(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	// Return) [원본_버퍼_끝_포인터]+[_Offset]한 곳을 기준으로 버퍼를 만든다.
	return buffer(buf+len+_Offset, (_Offset<=0) ? (-_Offset) : 0);
}

inline char* buffer::_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	return buf+len+_Offset;
}

template <typename T>
T& buffer::_back_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Pointer형이면 안됀다.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+sizeof(T))<=_bound.bound_upper);

	// 1) [원본_버퍼_끝_포인터]+[_Offset]을 얻는다.
	T* p	 = (T*)(buf+len+_Offset);
	
	// 2) Offset을 Sizeof(T)증가시킨다.
	_Offset	+= (int)sizeof(T);

	// Return) [원본_버퍼_끝_포인터]+[_Offset]값을 리턴한다.
	return *p;
}

inline void buffer::_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ size_t _Offset, _In_ size_t _Size, _In_ void* _Buffer) const
{
	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+_Size)<=_bound.bound_upper);

	// 1) 복사한다.
	memcpy(_Buffer, buf+_Offset, _Size);
}


}
