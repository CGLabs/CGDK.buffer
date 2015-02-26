#include "CGDptr.h"
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
inline void* ptr::_prepend_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size)
{
	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-_Size)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]를 _Size만큼 줄인다.
	m_ptr	-= _Size;

	// Return) 
	return (void*)m_ptr;
}

template <class T>
T& ptr::_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeof(T))>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);
	
	// 1) [원본_버퍼_포인터]의 크기를 sizeof(T)만큼 줄인다.
	m_ptr	-= sizeof(T);
	
	// 2) [원본_버퍼_길이]를 sizeof(T)만큼 늘린다. 
	*(T*)m_ptr	 = _Data; 
	
	// Return) 
	return *(T*)m_ptr;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
ptr::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// 1) [데이터_갯수]만큼 데이터들을 추가한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T)*_Count, _Data);

	// 2) [데이터_갯수]를 써넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	m_ptr;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
ptr::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// 1) [데이터_갯수]만큼 데이터들을 추가한다.
	for(int i=(int)(_Count-1);i>=0;--i)
	{
		_prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// 2) [데이터_갯수]를 써넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	m_ptr;
}

inline void* ptr::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)
{
	// Check) Buffer의 Size가 0이면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-_Size)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]의 크기를 _Size만큼 줄인다.
	char* p	 = m_ptr -_Size;
	
	// Check) _Size가 0이면 끝낸다.
	if(_Size==0) return p;
	
	// 2) [원본_버퍼_포인터]에 [데이터]를 [데이터_크기]만큼 복사한다.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}

	// 3) [원본_버퍼_포인터]을 업데이트한다.
	m_ptr	 = p;
	
	// Return) 
	return (void*)p;
}

template <class T>
void* ptr::_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size)
{
	// Check) Buffer의 Size가 0이면 안된다.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));
	
	// Check) 
	if(_String==nullptr) throw std::invalid_argument("string is nullptr (" __FUNCTION__ ")");

	// 1) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;	// strnlen(, _Buffer_Size)
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound 검사를 한다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) String내용을 복사한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String);

	// 3) Size를 넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);
	
	// Return) 첫위치를 리턴함.
	return	m_ptr;
}

template <class T>
void* ptr::_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
	size_t	lengthString = (size_t)_String.length()*sizeof(T)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString-sizeof(COUNT_T))>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 2) String내용을 복사한다.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String.c_str());

	// 3) Size를 넣는다.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);

	// Return) String의 제일 처음 위치를 리턴함!!
	return	m_ptr;
}

template <class T, size_t N>
void* ptr::_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// 1) [문자열_길이]와 복사할 크기를 구한다.
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 2) 복사할 [버퍼_위치]를 구한다.
	char*	p = m_ptr - sizeString - sizeof(COUNT_T);

	// Check) Lower Bound와 Uppder Bound를 검사한다.
	_CGD_BUFFER_BOUND_CHECK(p >= _bound.bound_lower && m_ptr <= _bound.bound_upper);

	// 1) [문자열_길이]를 저장한다.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 2) [원본_버퍼_끝_포인터]에 [문자열]을 복사한다.
	memcpy(p + sizeof(COUNT_T), _constString.p, sizeString);

	// 3) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
	m_ptr -= (sizeof(COUNT_T)+sizeString);

	// Return) 
	return	m_ptr;
}

template <class T>
void* ptr::_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

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
	size_t	lengthString = _Xvsprintf(pStringStart, _Format, _ArgList)+1;
	int		sizeString	 = lengthString*sizof(T);

	// 3) 복사할 위치를 구한다.
	T*	p	 = m_ptr-sizeString;

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((p-sizeof(COUNT_T))>=_bound.bound_lower);
	
	// 4) [문자열]을 복사한다.
	memcpy(p, pStringStart, sizeString);

	// 5) [목표_포인터]를 sizeof(COUNT_T)만큼을 뺀다.
	p	-= sizeof(COUNT_T);

	// 6) [문자열_길이]를 써넣는다.
	*(COUNT_T*)p	 = lengthString;

	// 7)[원본_버퍼_포인터]를 업데이트한다.
	m_ptr	 = p;

	// 8) [임시_버퍼]할당 해제
#ifdef MEM_POOL_ALLOC
#else 
	CGFREE(pStringStart);
#endif

	// Return) 
	return	p;
}

template<class T>
size_t ptr::_prepend_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

	// 1) [문자열_길이]를 구한다.
	size_t	lengthString = std::char_traits<char>::length(_String);
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString)>=_bound.bound_lower);

	// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
	T*	p = m_ptr-sizeString;
	
	// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
	if(p!=_String)
	{
		memcpy(p, _String, sizeString);
	}

	// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
	m_ptr	 = p;

	// Return) 
	return	lengthString;
}

template <class T, size_t N>
size_t ptr::_prepend_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText)
{
	// Declare) 
	const size_t	sizeString = (_constText.size()-1)*sizeof(T);

	// Check) Bound Check
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString) >= _bound.bound_lower && m_ptr<=_bound.bound_upper);

	// 2) [원본_버퍼_포인터]를 [문자열 길이] 만큼 뺀 [목표_포인터]를 구한다..
	char*	p = m_ptr - sizeString;

	// 3) [원본_버퍼_포인터]에 문자열을 [문자열 길이] 만큼 복사한다.
	memcpy(p, _constText.p, sizeString);

	// 4) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 옮긴다.
	m_ptr = p;

	// Return) 
	return	_constText.size();
}

template <class T>
size_t ptr::_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

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
	T*		p	 = m_ptr-sizeString;

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
	m_ptr	 = p;

	// Return) 
	return lengthString;
}

inline void* ptr::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer)
{
	// By Pass) 
	return _prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Buffer.len, _Buffer.buf);
}

inline void* ptr::_append_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length가 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);
	
	// 1) [원본_버퍼_끝_포인터]를 구한다.
	void*	p = m_ptr;
	
	// 2) [원본_버퍼_포인터]를 _Length만큼 늘린다. 
	m_ptr	+= _Length;
	
	// Return) [원본_버퍼_끝_포인터]값을 리턴한다.
	return	p;
}

template <class T>
T& ptr::_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T))<=_bound.bound_upper);
	
	// 1) [원본_버퍼_포인터]를 구한다.
	T*	p	 = (T*)m_ptr;
	
	// 2) [원본_버퍼_포인터]에 값(_Data)를 써넣는다.
	*p		 = _Data;
	
	// 3) [원본_버퍼_포인터]를 sizeof(T)만큼 늘린다. 
	m_ptr	+= sizeof(T);
	
	// Return) [원본_버퍼_끝_값]을 리턴한다.
	return *p;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
ptr::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T)*_Count)<=_bound.bound_upper);

	// Declare) 임시
	ptr	temp	 = *this;

	// 1) [데이터_갯수]를 얻어낸다.
	temp._append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [데이터]들을 통채로 복사한다.
	_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Count*sizeof(T), _Data);

	// 3) [원본_버퍼_포인터]를 저장해 놓는다.
	void* p = m_ptr;

	// 4) 변경된 포인터를 업데이트
	m_ptr	 = temp.m_ptr;

	// Return) 
	return	p;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
ptr::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Data이 nullptr이면 안된다.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Count가 0이하면 안된다.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T)*_Count)<=_bound.bound_upper);

	// Declare) 임시
	ptr	temp	 = *this;

	// 1) [데이터_갯수]를 얻어낸다.
	temp._append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [데이터_갯수]만큼 읽어 들여 저장한다.
	for(size_t i=0;i<_Count;++i)
	{
		temp._append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);

	}

	// 3) [원본_버퍼_포인터]를 저장해 놓는다.
	void* p = m_ptr;

	// 4) 변경된 포인터를 업데이트
	m_ptr	 = temp.m_ptr;

	// Return) 
	return	p;
}

inline void* ptr::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer) 
{
	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Size)<=_bound.bound_upper);

	// Check) _Size가 0이면 끝낸다.
	if(_Size==0) return m_ptr;
	
	// 1) _Buffer가 null이 아니면 데이터를 복사한다.
	if(_Buffer!=nullptr && _Buffer!=m_ptr)
	{
		memcpy(m_ptr, _Buffer, _Size);
	}
	
	// 2) [원본_버퍼_포인터]를 저장해 놓는다.
	void* p	 = m_ptr; 
	
	// 3) 길이만큼 포인터를 증가시킨다.
	m_ptr	+= _Size; 
	
	// Return) 
	return p;
}

template <class T>
void* ptr::_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String)
{
	// 1) 문자열을 복사할 위치를 구한다.
	void*	strDest	 = m_ptr;

	// 2) [문자열]을 복사한다.
	size_t	lengthString	 = _Xappend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(T*)(m_ptr + sizeof(COUNT_T)), _String);

	// 3) [문자열_길이]를 저장한다.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [버퍼]를 업데이트한다.
	m_ptr	+= lengthString*sizeof(T)+sizeof(COUNT_T);

	// Return) 리턴
	return	strDest;
}

template <class T>
void* ptr::_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) [목표_포인터]를 구한다.
	void*	strDest	 = m_ptr;

	// 2) [문자열]을 [목표_포인터]에 복사한다.
	size_t	lengthString	 = _Xappend_string(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(m_ptr + sizeof(COUNT_T)), _String.c_str(), _String.length());

	// 3) [문자열_길이]를 써넣는다.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [버퍼_포인터]를 업데이트한다.
	m_ptr	+= (lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) 리턴
	return	strDest;
}

template <class T, size_t N>
void* ptr::_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T, N>& _constString)
{
	// Constexpr)
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && (m_ptr+sizeof(COUNT_T) + sizeString) <= _bound.bound_upper);

	// 1) [원본_버퍼_끝_포인터]를 얻는다.
	char*	p = m_ptr;

	// 2) [문자열_길이]를 저장한다.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 3) [원본_버퍼_끝_포인터]에 [문자열]을 복사한다.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 4) [원본_버퍼_길이]에 [데이터_길이]만큼 더한다.
	m_ptr += sizeString+sizeof(COUNT_T);

	// Return) 
	return	p;
}

template <class T>
void* ptr::_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// 1) [문자열]을 복사할 위치를 구한다.
	char*	strDest	 = m_ptr;

	// 2) [문자열]을 복사한다.
	const size_t	lengthString	 = _Xappend_string_format(_CGD_BOUND_INFO_PASS _CGD_COMMA(T*)(m_ptr + sizeof(COUNT_T)), _Format, _ArgList);

	// 3) [문자열_길이]를 저장한다.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [버퍼]를 업데이트한다.
	m_ptr	 = (char*)(lengthString*sizeof(T)+string_length);

	// Return) 
	return	(T*)strDest;
}

template<class T>
size_t ptr::_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr) >= _bound.bound_lower);

	// 1) [문자열]의 길이를 구한다.
	const size_t	lengthString = std::char_traits<T>::length(_String);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr + sizeString) <= _bound.bound_upper);

	// 2) [문자열]을 복사한다.
	memcpy(m_ptr, _String, sizeString);

	// 3) [버퍼_포인터]를 길이만큼 더한다.
	m_ptr += sizeString;

	// Return) 
	return	lengthString;
}

template <class T, size_t N>
size_t ptr::_append_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText)
{
	// Declare) 
	const size_t	lengthString = _constText.size()-1;
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && m_ptr+sizeString<_bound.bound_upper);

	// 1) [문자열]을 복사하고 [문자열_길이]만큼 더한다.
	memcpy(m_ptr, _constText.p, sizeString);

	// 2) [문자열_길이]만큼 더한다.
	m_ptr += sizeString;

	// Return) 
	return	lengthString;
}

template <class T>
size_t ptr::_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower);

	// 1) [문자열]을 복사할 위치를 저장한다.
	T*	strDest	 = (T*)m_ptr;

	// 2) [문자열]을 복사한다.
	const size_t	lengthString = _Xvsprintf(strDest, _Format, _ArgList);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 3) String 길이만큼...
	m_ptr += sizeString;

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr <= _bound.bound_upper);

	// Return) 
	return	lengthString;
}

inline void* ptr::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer)
{
	// By-Pass) 
	return _append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Buffer.len, _Buffer.buf);
}

inline void* ptr::_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length이 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);

	// 1) [원본_버퍼_포인터]의 크기를 임시로 저장한다.
	char*	p	 = m_ptr;
	
	// 1) [원본_버퍼_포인터]의 크기를 _Length만큼 늘린다.
	m_ptr	+= _Length;
	
	// Return) [원본_버퍼_처음_포인터]
	return p;
}

template <class T>
COUNT_T ptr::_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(p_iLengthInWords) T* _String, _In_ size_t p_iLengthInWords)
{
	// Check) _String이 nullptr이면 안된다.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("string pointer is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Buffer의 Size가 0이면 안된다.
	CGD_ASSERT(p_iLengthInWords>=0, throw std::invalid_argument("length of word is zero or less! [1] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower);

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	COUNT_T	lengthString	 = *(COUNT_T*)m_ptr;

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString==(COUNT_T)-1)
	{
		m_ptr	+= sizeof(COUNT_T);
		return	(COUNT_T)-1;
	}

	// Check) [문자열_길이]가 최소 문자열의 길이 (NULL문자)의 크기 작으면 오류다!
	if(lengthString<1) throw std::length_error("buffer size is too small!! [5] (" __FUNCTION__ ")");

	// 2) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+size(String))
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) [데이터_크기]가 UPper Bound를 넘어가는지 검사한다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+sizeData)<=_bound.bound_upper);

	// Check) [문자열]의 마지막이 NULL인가를 확인한다.
	if(*(T*)(m_ptr+sizeString+sizeof(COUNT_T)-sizeof(T)) != NULL) throw std::length_error("it's invalid string!! [6] (" __FUNCTION__ ")");

	// 3) 문자열을 복사한다.
	memcpy(_String, m_ptr+sizeof(COUNT_T), sizeString);

	// 4) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
	m_ptr	+= (sizeData+sizeof(COUNT_T));

	// Return) String길이를 return한다.
	return	lengthString;
}

template <class T>
T* ptr::_extract_string_pointer(_CGD_BOUND_INFO_PARAM)
{
	// Check) [원본_버퍼_포인터]는 lower Bound보다는 커야한다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower);

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	size_t	sizeString	 = (size_t)(*(COUNT_T*)m_ptr);

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(sizeString<0)
	{
		return	nullptr;
	}

	// Check) [문자열_길이]가 최소 문자열의 길이(NULL문자)의 크기 작으면 오류다!
	if(sizeString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [데이터_크기]를 계산한다.(COUNT_T[문자열_길이]+length(String))
	size_t	sizeBuffer	 = sizeString*sizeof(T)+sizeof(COUNT_T);

	// Check) [데이터_크기]가 UPper Bound를 넘어가는지 검사한다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+sizeBuffer)<=_bound.bound_upper);

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(m_ptr+sizeBuffer-sizeof(T)) != NULL) throw std::length_error("it's invalid string! [1] (" __FUNCTION__ ")");

	// 3) 문자열의 제일 앞 포인터를 얻어둔다.
	T*	strString	 = (T*)(m_ptr+sizeof(COUNT_T));

	// 4) [원본_버퍼_포인터]를 [데이터_크기]만큼 더한다.
	m_ptr	+= sizeBuffer;

	// Return) [문자열_시작_포인터]을 리턴한다.
	return	strString;
}

template <class T>
std::basic_string<T> ptr::_extract_string(_CGD_BOUND_INFO_PARAM)
{
	// Return) [문자열]을 리턴한다. (RVO)
	return	std::basic_string<T>(_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS));
}

inline char* ptr::_extract_web(_CGD_BOUND_INFO_PARAM)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr;
	const char*	pEnd	 = m_ptr+UINT_MAX;

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 잠시 m_ptr를 저장해 놓는다.
			char*	pHead	 = m_ptr;

			// - m_ptr를 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			m_ptr		 = (chNow+2);
			//len		 = (COUNT_T)(pEnd-chNow-1);

			// Return) 
			return	pHead;
		}
	}

	// Return) 실패! Web Message를 완성하지 못했다.
	throw	nullptr;
}

inline char* ptr::_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* p_pstrBuffer, _In_ size_t _Buffer_Size)
{
	// Check) 
	CGD_ASSERT(p_pstrBuffer!=nullptr, throw std::invalid_argument("_format string is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Buffer_Size가 0이하면 안된다.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Buffer_Size)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr;
	const char*	pEnd	 = m_ptr+UINT_MAX;

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 깅리를 구한다.
			size_t	ilength = chNow - m_ptr;

			// - 최대 버퍼를 넘지않도록 한다.
			if(ilength>(_Buffer_Size-1)) ilength=(_Buffer_Size-1);

			// - 복사한다
			memcpy(p_pstrBuffer, m_ptr, ilength);

			// - 마지막에 NULL을 추가한다.
			*(p_pstrBuffer+ilength)	 = NULL;

			// - m_ptr를 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			m_ptr	 = (chNow+2);
			//len		 = (COUNT_T)(pEnd-chNow-1);

			// Return) 
			return	p_pstrBuffer;
		}
	}

	// Exception) 
	throw	std::out_of_range("string is too short!! [1] (" __FUNCTION__ ")");
}

inline void * ptr::_extract_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_ void* _Buffer)
{
	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Size)<=_bound.bound_upper);

	// Check) 길이가 0이면 그냥 되돌린다.
	if(_Size==0)
	{
		return	(void*)m_ptr;
	}

	// 1) 복사한다.
	memcpy(_Buffer, m_ptr, _Size);

	// Declare)
	void*	p	 = (void*)m_ptr;

	// 2) _Size만큼 더한다.
	m_ptr	+= _Size;

	// Return) 
	return	p;
}

inline void* ptr::_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length가 0이하면 안된다.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);

	// 1) [원본_버퍼_길이]를 _Length만큼 줄인다.
	m_ptr	-= _Length;
	
	// Return) [원본_버퍼_끝_포인터]
	return (void*)m_ptr;
}

template <class T>
T& ptr::_subtract_general(_CGD_BOUND_INFO_PARAM)
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && (m_ptr+sizeof(T))<=_bound.bound_upper);
	
	// 1) [원본_버퍼_길이]를 sizeof(T)만큼 줄인다.
	m_ptr	-= sizeof(T);
	
	// Return) [원본_버퍼_처음_값]을 리턴한다.
	return *(T*)m_ptr;
}

inline char* ptr::_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Return) _Offset만큼 이동한 위치를 리턴한다.
	return m_ptr+_Offset;
}

inline ptr ptr::_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Return) _Offset만큼 이동한 버퍼 생성후 리턴(RVO)
	return ptr(m_ptr+_Offset);
}

template <typename T>
T& ptr::_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset+sizeof(T))<=_bound.bound_upper);

	// 1) [원본_버퍼_처음_포인터]+[_Offset]을 얻는다.
	T* p	 = (T*)(m_ptr+_Offset);
	
	// 2) Offset을 Sizeof(T)증가시킨다.
	_Offset	+= sizeof(T);
	
	// Return) [원본_버퍼_포인터]+[_Offset]값을 리턴한다.
	return *p;
}

template<typename T>
T* ptr::_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const 
{
	// Check) [문자열_끝_위치]가 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower);

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(m_ptr+_Offset));

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) String의 길이가 sizeof(T)보다 작으면 오류다!  (nullptr이 포함되므로 최소한 sizeof(T)만큼은 되야 한다.
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [문자열_시작_위치]를 구한다.
	size_t	posStart = _Offset+sizeof(COUNT_T);

	// 3) [문자열_끝_위치]를 구한다.
	size_t	posTail	 = posStart+lengthString*sizeof(T);

	// Check) [문자열_끝_위치]가 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+posTail)<=_bound.bound_upper);

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(m_ptr+posTail-sizeof(T))!=NULL) throw std::out_of_range("Invalid string! [2] (" __FUNCTION__ ")");
	
	// 3) Offset을 더한다.
	_Offset		 = (int)posTail;

	// Return) String의 위치를 return한다.
	return	(T*)(m_ptr+posStart);
}

template<typename T>
std::basic_string<T>  ptr::_front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) [문자열_끝_위치]가 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower);

	// 1) [문자열_길이]를 얻어낸다.(제일 처음 4Byte가 문자열의 길이다.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(m_ptr+_Offset));

	// Check) length가 0보다 작으면 그냥 리턴한다.
	if(lengthString<0)
	{
		return	std::basic_string<T>();
	}

	// Check) String의 길이가 sizeof(T)보다 작으면 오류다!(nullptr이 포함되므로 최소한 sizeof(T)만큼은 되야 한다.
	if(lengthString<1) throw std::out_of_range("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [문자열_시작_위치]를 구한다.
	size_t	posStart = _Offset+sizeof(COUNT_T);

	// 3) [문자열_끝_위치]를 구한다.
	size_t	posTail	 = posStart+lengthString*sizeof(T);

	// Check) [문자열_끝_위치]가 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+posTail)<=_bound.bound_upper);

	// Check) 문자열의 제일 끝이 NULL인지 확인한다.
	if(*(T*)(m_ptr+posTail-sizeof(T))!=NULL) throw std::out_of_range("string is too short!! [3] (" __FUNCTION__ ")");

	// 4) 최종적으로 계산된 Offset값을 업데이트한다.
	_Offset		 = (int)posTail;

	// Return) [문자열]을 리턴한다. (RVO)
	return	std::basic_string<T>((T*)(m_ptr+posStart));
}

inline char* ptr::_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) 새로 추가되는 크기는 Upper Bound를 넘어서는 안됀다.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr+_Offset;
	const char*	pEnd	 = m_ptr+_Offset+INT_MAX;

	// 1) /r/n을 찾는다.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - 잠시 m_ptr을 저장해 놓는다.
			char*	pHead	 = m_ptr;

			// - m_ptr을 chNow+2로 설정한다. (/r/n부분을 빼기위해+2를 함.)
			//m_ptr		 = (chNow+2);
			//len		 = (COUNT_T)(pEnd-chNow-1);

			// 5) Offset을 써넣는다.
			_Offset	 = (int)(chNow+2-m_ptr);

			// Return) 
			return	pHead;
		}
	}

	// Return) 실패! Web Message가 완료되지 않았다.
	return	nullptr;
}

inline void ptr::_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA size_t _Offset, size_t _Size, void * _Buffer) const
{
	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size가 0이하면 안된다.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound 확인
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset+_Size)<=_bound.bound_upper);

	// 1) 복사한다.
	memcpy(_Buffer, m_ptr+_Offset, _Size);
}


}