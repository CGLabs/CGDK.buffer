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
	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf-_Size)>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 1) [����_����_������]�� _Size��ŭ ���δ�.
	buf	 -= _Size;

	// 2) [����_����_����]�� _Size��ŭ �ø���. 
	len	 += (uint32_t)_Size;
	
	// Return) 
	return (void*)buf;
}

template <class T>
T& buffer::_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) Pointer���̸� �ȉ´�.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeof(T))>=_bound.bound_lower && buf<=_bound.bound_upper);
	
	// 1) [����_����]�� ���� ������ �ִ´�.
	*(T*)(buf-sizeof(T))	 = _Data;
	
	// 2) [����_����_������]�� ũ�⸦ sizeof(T)��ŭ ���δ�.
	buf	-= sizeof(T);
	
	// 3) [����_����_����]�� sizeof(T)��ŭ �ø���. 
	len	+= sizeof(T);
	
	// Return) 
	return *(T*)buf;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
buffer::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// 1) [������_����]��ŭ �����͵��� ��ä�� �����Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T)*_Count, _Data);

	// 2) [������_����]�� ��ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	buf;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
buffer::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// 1) [������_����]��ŭ �����͵��� �߰��Ѵ�.
	for(int i=(int)(_Count-1);i>=0;--i)
	{
		_prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// 2) [������_����]�� ��ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	buf;
}

inline void* buffer::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)
{
	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf-_Size)>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 1) [����_����_������]�� ũ�⸦ _Size��ŭ ���δ�.
	char* p	 = buf -_Size;
	
	// Check) _Size�� 0�̸� ������.
	if(_Size==0) return p;

	// 2) [����_����_������]�� [������]�� [������_ũ��]��ŭ �����Ѵ�.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}

	// 3) [����_����_������]�� �����Ѵ�.
	buf	 = p;

	// 4) [����_����_����]�� _Size��ŭ �ø���. 
	len	+= (uint32_t)_Size;

	// Return) 
	return (void*)buf;
}

template <class T>
void* buffer::_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size)
{
	// Check) _Buffer_Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// 1) String���̸� ���Ѵ�.(NULL���̱��� �����ϹǷ� +1�Ѵ�.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound �˻縦 �Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) [���ڿ�]�� �����Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String);

	// 3) Size�� �ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);
	
	// Return) ù��ġ�� ������.
	return	buf;
}

template <class T>
void* buffer::_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) String���̸� ���Ѵ�.(NULL���̱��� �����ϹǷ� +1�Ѵ�.)
	size_t	lengthString = (size_t)_String.length()+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound�� �˻��Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) [���ڿ�]�� [���ڿ�_����]��ŭ �����Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String.c_str());

	// 3) [���ڿ�_����]�� ��ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);

	// Return) String�� ���� ó�� ��ġ�� ������!!
	return	buf;
}

template <class T, size_t N>
void* buffer::_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// 1) [���ڿ�_����]�� ������ ũ�⸦ ���Ѵ�.
	const size_t	lengthString = _constString.size();
	size_t			sizeString	 = lengthString*sizeof(T);

	// 2) ������ [����_��ġ]�� ���Ѵ�.
	char*	p = buf - sizeString - sizeof(COUNT_T);

	// Check) Lower Bound�� Uppder Bound�� �˻��Ѵ�.
	_CGD_BUFFER_BOUND_CHECK(p>=_bound.bound_lower && buf<=_bound.bound_upper);

	// 3) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)(p) = (COUNT_T)lengthString;

	// 4) [����_����_��_������]�� [���ڿ�]�� �����Ѵ�.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 5) sizeof(COUNT_T)�� ���Ѵ�.
	sizeString += sizeof(COUNT_T);

	// 6) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
	buf -= (uint32_t)sizeString;
	len += (uint32_t)sizeString;

	// Return) 
	return	buf;
}


template <class T>
void* buffer::_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _Format�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// Declare)
	const size_t	TEMP_STRING_BUFFER_SIZE		= 2048;

	// 1) [�ӽ�_����]�� �Ҵ��Ѵ�
#ifdef MEM_POOL_ALLOC
	CGPTR<ICGBuffer>	pbufferTemp	 = MEM_POOL_ALLOC(TEMP_STRING_BUFFER_SIZE);
	T*	pStringStart = (T*)pbufferTemp.buf;
#else 
	T*	pStringStart = (T*)CGMALLOC(TEMP_STRING_BUFFER_SIZE);
#endif
	// 3) [����_����_����_ũ��]�� [����_���ڿ�]�� ��ִ´�.
	size_t	lengthString = _Xvsprintf(pStringStart, _Format, _ArgList)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// 4) [��ǥ_������]�� ���Ѵ�.
	T*	p	 = buf-sizeString;

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((p-sizeof(COUNT_T))>=_bound.bound_lower);
	
	// 6) [���ڿ�]�� �����Ѵ�.
	memcpy(p, pStringStart, sizeString);

	// 7) [��ǥ_������]�� sizeof(COUNT_T)��ŭ�� ����.
	p	-= sizeof(COUNT_T);

	// 8) [���ڿ�_����]�� ��ִ´�.
	*(COUNT_T*)p	 = (COUNT_T)lengthString;

	// 7)[����_����_������]�� ������Ʈ�Ѵ�.
	buf	 = p;
	len	+= (uint32_t)(sizeString+sizeof(COUNT_T));

	// 6) [�ӽ�_����]�Ҵ� ����
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
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// 1) [���ڿ�_����]�� ���Ѵ�.
	size_t	lengthString = std::char_traits<T>::length(_String);
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf-sizeString)>=_bound.bound_lower);

	// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
	T*	p = buf-sizeString;
	
	// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
	if(p!=_String)
	{
		memcpy(p, _String, sizeString);
	}

	// 4) [����_����_������]�� [����_����_����]�� �ű��.
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

	// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
	char*	p = buf - sizeString;

	// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
	memcpy(p, _constText.p, sizeString);

	// 4) [����_����_������]�� [����_����_����]�� �ű��.
	buf		 = p;
	len		+= sizeString;

	// Return) 
	return	_constText.size();
}


template <class T>
size_t buffer::_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list	_ArgList)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(buf<=_bound.bound_upper);

	// Declare)
	const size_t	TEMP_STRING_BUFFER_SIZE		= 2048;

	// 1) [�ӽ�_����]�� �Ҵ��Ѵ�
#ifdef MEM_POOL_ALLOC
	CGPTR<ICGBuffer>	pbufferTemp	 = MEM_POOL_ALLOC(TEMP_STRING_BUFFER_SIZE);
	T*	pStringStart = (T*)pbufferTemp.buf;
#else 
	T*	pStringStart = (T*)CGMALLOC(TEMP_STRING_BUFFER_SIZE);
#endif
	// 2) [����_����_����_ũ��]�� [����_���ڿ�]�� ��ִ´�.
	size_t	lengthString	 = _Xvsprintf(pStringStart, _Format, _ArgList);
	size_t	sizeString		 = lengthString*sizeof(T);

	// 3) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
	T*		p	 = buf-sizeString;

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(p>=_bound.bound_lower);

	// 4) [���ڿ�]�� �߰��Ѵ�.
	memcpy(p, pStringStart, sizeString);

	// 5) [�ӽ�_����]�Ҵ� ����
#ifdef MEM_POOL_ALLOC
#else 
	CGFREE(pStringStart);
#endif

	// 6) [����_����_������]�� [����_����_����]�� �ű��.
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
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+_Length)<=_bound.bound_upper);
	
	// 1) [����_����_��_������]�� ���Ѵ�.
	char* p	 = buf+len;
	
	// 2) [����_����_����]�� _Length��ŭ �ø���. 
	len		+= (uint32_t)_Length;

	// Return) [����_����_��_������]���� �����Ѵ�.
	return (void*)p;
}

template <class T>
T& buffer::_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) Pointer���̸� �ȉ´�.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T))<=_bound.bound_upper);

	// 1) [����_����_��_������]�� ���Ѵ�.
	T* p	= (T*)(buf+len);
	
	// 2) [����_����_��_������]�� ��(_Data)�� ��ִ´�.
	*p		= _Data;
	
	// 3) [����_����_����]�� sizeof(T)��ŭ �ø���. 
	len		+= (uint32_t)sizeof(T);
	
	// Return) [����_����_��_��]�� �����Ѵ�.
	return *p;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
buffer::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T)*_Count)<=_bound.bound_upper);

	// 1) [����_����_������]�� ������ ���´�.
	T*	p	 = (T*)(buf+len);

	// 1) [������_����]�� ��ִ´�.
	_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [������]���� ��ä�� �����Ѵ�.
	_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Count*sizeof(T), _Data);

	// Return) 
	return	p;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
buffer::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+sizeof(T)*_Count)<=_bound.bound_upper);

	// 1) [����_����_������]�� ������ ���´�.
	T*	p	 = (T*)(buf+len);

	// 1) [������_����]�� ��ִ´�.
	_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [������]���� �߰��Ѵ�.
	for(size_t i=0;i<_Count;++i)
	{
		_append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// Return) 
	return	p;
}

inline void* buffer::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer) 
{
	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower && (buf+len+_Size)<=_bound.bound_upper);

	// 1) [����_����_��_������]�� ��´�.
	char*	p = buf+len; 
	
	// Check) _Size�� 0�̸� ������.
	if(_Size==0) return p;
	
	// 2) [����_����_��_������]�� [������]�� [������_ũ��]��ŭ �����Ѵ�.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}
	
	// 3) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
	len		+= (uint32_t)_Size; 
	
	// Return) 
	return (void*)p;
}

template <class T>
void* buffer::_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String)
{
	// 1) ���ڿ��� ������ ��ġ�� ���Ѵ�.
	char*	strDest	 = buf+len;

	// 2) [���ڿ�]�� �����Ѵ�.
	size_t	lengthString	 = _Xappend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _String);

	// 3) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [����_����]�� ������Ʈ�Ѵ�.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) ����
	return	strDest;
}

template <class T>
void* buffer::_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) [��ǥ_������]�� ���Ѵ�.
	char*	strDest	 = buf+len;

	// 2) [���ڿ�]�� [��ǥ_������]�� �����Ѵ�.
	size_t	lengthString	 = _Xappend_string(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _String.c_str(), _String.length());

	// 3) [���ڿ�_����]�� ��ִ´�.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [����_����]�� ������Ʈ�Ѵ�.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) ����
	return	strDest;
}

template <class T, size_t N>
void* buffer::_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// Constexpr)
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf + len) >= _bound.bound_lower && (buf + len+sizeof(COUNT_T) + sizeString) <= _bound.bound_upper);

	// 1) [����_����_��_������]�� ��´�.
	char*	p = buf + len;

	// 2) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 3) [����_����_��_������]�� [���ڿ�]�� �����Ѵ�.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 4) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
	len += (uint32_t)(sizeString+sizeof(COUNT_T));

	// Return) 
	return	(void*)p;
}

template <class T>
void* buffer::_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// 1) [���ڿ�]�� ������ ��ġ�� ���Ѵ�.
	char*	strDest	 = buf+len;

	// 2) [���ڿ�]�� �����Ѵ�.
	const size_t	lengthString	 = _Xappend_string_format(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(strDest+sizeof(COUNT_T)), _Format, _ArgList);

	// 3) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)(buf+len)	 = (COUNT_T)lengthString;

	// 4) [����]�� ������Ʈ�Ѵ�.
	len		+= (uint32_t)(lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) ����
	return	strDest;
}

template <class T>
size_t buffer::_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower);

	// 1) [���ڿ�]�� ���̸� ���Ѵ�.
	const size_t	lengthString = std::char_traits<T>::length(_String);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len+ sizeString)<=_bound.bound_upper);

	// 2) [���ڿ�]�� �����Ѵ�.
	memcpy(buf + len, _String, sizeString);

	// 3) [���ڿ�_����]��ŭ ���Ѵ�.
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

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(buf+len >= _bound.bound_lower && (buf+len+sizeString)<_bound.bound_upper);

	// 1) [���ڿ�]�� �����ϰ� [���ڿ�_����]��ŭ ���Ѵ�.
	memcpy(buf + len, _constText.p, sizeString);

	// 2) [���ڿ�_����]��ŭ ���Ѵ�.
	len += (uint32_t)sizeString;

	// Return) 
	return	lengthString;
}

template <class T>
size_t buffer::_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len)>=_bound.bound_lower);

	// 1) [���ڿ�]�� ������ ��ġ�� �����Ѵ�.
	T*	strDest = (T*)(buf + len);

	// 2) [���ڿ�]�� �����Ѵ�.
	const size_t	lengthString = _Xvsprintf(strDest, _Format, _ArgList);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 3) [����]�� ������Ʈ�Ѵ�.
	len += (uint32_t)sizeString;

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+len) <= _bound.bound_upper);

	// Return) ����
	return	lengthString;
}

inline void* buffer::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer)
{
	// By-Pass) 
	return _append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Buffer.len, _Buffer.buf);
}

inline void* buffer::_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower && (buf+_Length)<=_bound.bound_upper);

	// Check) [����_����_ũ��]���� _Length�� Ŀ�� �Ѵ�.
	_CGD_BUFFER_BOUND_CHECK(len>=_Length);
	
	// 1) [����_����_������]�� ũ�⸦ �ӽ÷� �����Ѵ�.
	char* p	 = buf;
	
	// 1) [����_����_������]�� ũ�⸦ _Length��ŭ �ø��� [����_����_����]�� ���δ�.
	buf		+= _Length;
	len		-= (uint32_t)_Length;
	
	// Return) [����_����_ó��_������]
	return p;
}

template <class T>
COUNT_T buffer::_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(p_iLengthInWords) T* _String, _In_ size_t p_iLengthInWords)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _LengthInWords�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_LengthInWords>=0, throw std::invalid_argument("_LengthInWords is invalid [0] (" __FUNCTION__ ")"));

	// 1) [������_ũ��]�� ���´�.(COUNT_T[���ڿ�_����]+length(String))
	COUNT_T	lengthString	 = _get_front_string_length<T>(_CGD_BOUND_INFO_PASS);

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString==(COUNT_T)-1)
	{
		buf		+= sizeof(COUNT_T);
		len		-= sizeof(COUNT_T);
		return	(COUNT_T)-1;
	}

	// Check) [���ڿ�_����]�� [��ǥ_����_����]���� ���� ���� Ȯ���Ѵ�.
	if(sizeString>=p_iLengthInWords) throw std::length_error("buffer size is too small!! [5] (" __FUNCTION__ ")");

	// 2) [������_ũ��]�� ����Ѵ�.(COUNT_T[���ڿ�_����]+size(String))
	size_t	sizeString	 = lengthString*sizeof(T);

	// 2) [������ ��ġ]�� ��´�.
	const T*	p	 = buf+sizeof(COUNT_T);

	// 3) [����_����_������]�� [���ڿ���]�� �����Ѵ�.
	if(_String!=p)
	{
		memcpy(_String, p, sizeString);
	}

	// 4) ���ڿ� ���̸� sizeof(COUNT_T)��ŭ �ø���.
	sizeString	+=sizeof(COUNT_T);

	// 5) [����_����_������]�� [������_ũ��]��ŭ ���Ѵ�.
	buf	+= sizeString;
	len	-= (uint32_t)sizeString;

	// Return) [���ڿ�_����]�� �����Ѵ�.
	return	lengthString;
}

template <class T>
T* buffer::_extract_string_pointer(_CGD_BOUND_INFO_PARAM)
{
	// 1) [������_ũ��]�� ���´�.(COUNT_T[���ڿ�_����]+length(String))
	COUNT_T	sizeData	 = _get_front_string_length<T>(_CGD_BOUND_INFO_PASS);

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(sizeData==(COUNT_T)-1)
	{
		buf		+= sizeof(COUNT_T);
		len		-= sizeof(COUNT_T);
		return	nullptr;
	}

	// 2) ���ڿ��� ���� �� �����͸� ���д�.
	T*	strString	 = (T*)(buf+sizeof(COUNT_T));

	// 2) sizeOfData ���ϱ�
	sizeData	 = sizeData*sizeof(T)+sizeof(COUNT_T);

	// 3) [����_����_������]�� [������_ũ��]��ŭ ���Ѵ�.
	buf	+= sizeData;

	// 4) [����_����_����]�� [������_ũ��]��ŭ ���δ�.
	len	-= (uint32_t)sizeData;

	// Return) [���ڿ�_����_������]�� �����Ѵ�.
	return	strString;
}

template <class T>
std::basic_string<T> buffer::_extract_string(_CGD_BOUND_INFO_PARAM)
{
	return	std::basic_string<T>(_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS));
}

inline char* buffer::_extract_web(_CGD_BOUND_INFO_PARAM)
{
	// Check) Lower Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = (char*)(buf);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - ��� buf�� ������ ���´�.
			char*	pHead	 = buf;

			// - buf�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
			buf		 = (chNow+2);
			len		 = (uint32_t)(pEnd-chNow-1);

			// Return) 
			return	pHead;
		}
	}

	// Return) ����! Web Message�� �ϼ����� ���ߴ�.
	throw	nullptr;
}

inline void* buffer::_extract_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_ void* _Buffer)
{
	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower && (buf+_Size)<=_bound.bound_upper);

	// Check) ���̰� 0�̸� �׳� �ǵ�����.
	if(_Size==0)
	{
		return	(void*)buf;
	}

	// 1) �����Ѵ�.
	memcpy(_Buffer, buf, _Size);

	// Declare)
	void*	p	 = (void*)buf;

	// 2) _Size��ŭ ���Ѵ�.
	buf	+= _Size;
	len -= (uint32_t)_Size;

	// Return) 
	return	p;
}

inline char* buffer::_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* _Buffer, _In_ size_t _Buffer_Size)
{
	// Check) _Buffer_Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = (char*)(buf);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - �븮�� ���Ѵ�.
			size_t	ilength = chNow - buf;

			// - �ִ� ���۸� �����ʵ��� �Ѵ�.
			if(ilength>(_Buffer_Size-1)) ilength=(_Buffer_Size-1);

			// - �����Ѵ�
			memcpy(_Buffer, buf, ilength);

			// - �������� NULL�� �߰��Ѵ�.
			*(_Buffer+ilength)	 = NULL;

			// - buf�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
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
	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf)>=_bound.bound_lower);

	// Check) [����_����_����]�� �ּ��� sizeof(unit32_t)���ٴ� ���� �Ѵ�.
	if(sizeof(COUNT_T)>(size_t)len) throw std::length_error("buffer is too short [0] (" __FUNCTION__ ")");

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	COUNT_T	lengthString	 = *(COUNT_T*)buf;

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString==(COUNT_T)-1)
	{
		return	(COUNT_T)-1;
	}

	// 2) String�� ũ�⸦ ���Ѵ�.
	size_t	sizeString		 = lengthString*sizeof(T);

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ����(NULL����)�� ũ�� ������ ������!
	if(sizeString<sizeof(T)) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 3) [������_ũ��]�� ����Ѵ�.(COUNT_T[���ڿ�_����]+length(String))
	size_t	sizeData	 = sizeof(COUNT_T)+sizeString;

	// Check) Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+sizeData)<=_bound.bound_upper);

	// Check) [������_ũ��]�� [����_����_����_����](len)���� ������ �˻��Ѵ�.
	if(sizeData>(size_t)len) throw std::length_error("string is too short!! [2] (" __FUNCTION__ ")");

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(buf+sizeData-sizeof(T)) != NULL) throw std::length_error("it's invalid string! [3] (" __FUNCTION__ ")");

	// Return) [���ڿ�_����_������]�� �����Ѵ�.
	return	lengthString;
}


inline void* buffer::_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+len-_Length)>=_bound.bound_lower && (buf+len)<=_bound.bound_upper);

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(len<_Length) throw std::length_error("Buffer Overflow!! (" __FUNCTION__ ")");

	// 1) [����_����_����]�� _Length��ŭ ���δ�.
	len		-= (uint32_t)_Length;
	
	// Return) [����_����_��_������]
	return (buf + len);
}

template <class T>
T& buffer::_subtract_general(_CGD_BOUND_INFO_PARAM)
{
	// Check) Pointer���̸� �ȉ´�.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+len-sizeof(T))>=_bound.bound_lower && (buf+len)<=_bound.bound_upper);

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(len<sizeof(T)) throw std::length_error("Buffer Overflow!! [0] (" __FUNCTION__ ")");

	// 1) [����_����_����]�� sizeof(T)��ŭ ���δ�.
	len		-= (int)sizeof(T);
	
	// Return) [����_����_ó��_��]�� �����Ѵ�.
	return *(T*)(buf + len);
}

inline buffer buffer::_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const	
{
	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	// Return) _Offset �̵��� ���� ������ ����(RVO)
	return buffer(buf+_Offset, (len>(uint32_t)_Offset) ? len-(uint32_t)_Offset : 0);
}

inline char* buffer::_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	return buf+_Offset;
}

template <typename T>
T& buffer::_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Pointer���̸� �ȉ´�.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+sizeof(T))<=_bound.bound_upper);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	CGD_ASSERT((_Offset+sizeof(T))<=len, );

	// 1) [����_����_ó��_������]+[_Offset]�� ��´�.
	T* p	 = (T*)(buf+_Offset);
	
	// 2) Offset�� Sizeof(T)������Ų��.
	_Offset	+= (int)sizeof(T);  
	
	// Return) [����_����_ó��_������]+[_Offset]���� �����Ѵ�.
	return *p;
}

template<typename T>
T* buffer::_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const 
{
	// Check) Lower Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Check) [���ڿ�_����_��ġ]�� [����_����_����]���� ��� �ȉ´�.
	if((_Offset+sizeof(COUNT_T))>(uint32_t)len) throw std::out_of_range("string is too short!! [0] (" __FUNCTION__ ")");

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(buf+_Offset));

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ����(NULL����)�� ũ�� ������ ������!
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [���ڿ�_����_��ġ]�� ���Ѵ�.
	size_t	posStart	 = _Offset+sizeof(COUNT_T);

	// 3) [���ڿ�_��_��ġ]�� ���Ѵ�.
	size_t	posTail		 = posStart+lengthString*sizeof(T);

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+posTail)<=_bound.bound_upper);

	// Check) [���ڿ�_��_��ġ]�� [����_����_����]���� ũ�� �ȉ´�.
	if(posTail>(size_t)len) throw std::out_of_range("string is to long!! [2] (" __FUNCTION__ ")");

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(buf+posTail-sizeof(T))!=NULL) throw std::out_of_range("Invalid string! [3] (" __FUNCTION__ ")");
	
	// 4) ���������� ���� Offset���� ������Ʈ�Ѵ�.
	_Offset		 = (int)posTail;

	// Return) [���ڿ�_����_������]�� �����Ѵ�.
	return	(T*)(buf+posStart);
}

template<typename T>
std::basic_string<T> buffer::_front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Check) [����_����_����]�� �ּ��� sizeof(unit32_t)���ٴ� ���� �Ѵ�.
	if((_Offset+sizeof(COUNT_T)+sizeof(T))>(int)len) throw std::length_error("string is too short!! [0] (" __FUNCTION__ ")");

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(buf+_Offset));

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ����(NULL����)�� ũ�� ������ ������!
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [���ڿ�_����_��ġ]�� ���Ѵ�.
	size_t	posStart	 = _Offset+sizeof(COUNT_T);

	// 3) [���ڿ�_��_��ġ]�� ���Ѵ�.
	size_t	posTail		 = posStart+lengthString*sizeof(T);

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+posTail)<=_bound.bound_upper);

	// Check) [���ڿ�_��_��ġ]�� [����_����_����]���� ũ�� �ȉ´�.
	if(posTail>(size_t)len) throw std::out_of_range("string is to long!! [2] (" __FUNCTION__ ")");

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(buf+posTail-sizeof(T))!=NULL) throw std::out_of_range("string is too short!! [3] (" __FUNCTION__ ")");
	
	// 4) ���������� ���� Offset���� ������Ʈ�Ѵ�.
	_Offset		 = (int)posTail;

	// Return) [���ڿ�]�� �����Ѵ�. (RVO)
	return	std::basic_string<T>((T*)(buf+posStart));
}

inline char* buffer::_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ����(NULL����)�� ũ�� ������ ������!
	if((uint32_t)_Offset>(len-1)) throw std::out_of_range("_Offset is Out of Range!! [0] (" __FUNCTION__ ")");

	// Declare)
	char*		chNow	 = (char*)(buf+_Offset);
	const char*	pEnd	 = (char*)(buf+len-1);

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - ��� buf�� ������ ���´�.
			char*	pHead	 = buf;

			// - buf�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
			//buf		 = (chNow+2);
			//len		 = (uint32_t)(pEnd-chNow-1);

			// 5) Offset�� ��ִ´�.
			_Offset	 = (int)(chNow+2-buf);

			// Return) 
			return	pHead;
		}
	}

	// Return) ����! Web Message�� �Ϸ���� �ʾҴ�.
	return	nullptr;
}

inline buffer buffer::_end(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	// Return) [����_����_��_������]+[_Offset]�� ���� �������� ���۸� �����.
	return buffer(buf+len+_Offset, (_Offset<=0) ? (-_Offset) : 0);
}

inline char* buffer::_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset)<=_bound.bound_upper);

	return buf+len+_Offset;
}

template <typename T>
T& buffer::_back_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) Pointer���̸� �ȉ´�.
	static_assert(!std::is_pointer<T>::value, "Must not be Pointer Type!!");

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+sizeof(T))<=_bound.bound_upper);

	// 1) [����_����_��_������]+[_Offset]�� ��´�.
	T* p	 = (T*)(buf+len+_Offset);
	
	// 2) Offset�� Sizeof(T)������Ų��.
	_Offset	+= (int)sizeof(T);

	// Return) [����_����_��_������]+[_Offset]���� �����Ѵ�.
	return *p;
}

inline void buffer::_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ size_t _Offset, _In_ size_t _Size, _In_ void* _Buffer) const
{
	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((buf+_Offset)>=_bound.bound_lower && (buf+_Offset+_Size)<=_bound.bound_upper);

	// 1) �����Ѵ�.
	memcpy(_Buffer, buf+_Offset, _Size);
}


}
