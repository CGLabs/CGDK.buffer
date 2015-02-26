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
	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-_Size)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 1) [����_����_������]�� _Size��ŭ ���δ�.
	m_ptr	-= _Size;

	// Return) 
	return (void*)m_ptr;
}

template <class T>
T& ptr::_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeof(T))>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);
	
	// 1) [����_����_������]�� ũ�⸦ sizeof(T)��ŭ ���δ�.
	m_ptr	-= sizeof(T);
	
	// 2) [����_����_����]�� sizeof(T)��ŭ �ø���. 
	*(T*)m_ptr	 = _Data; 
	
	// Return) 
	return *(T*)m_ptr;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
ptr::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// 1) [������_����]��ŭ �����͵��� �߰��Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T)*_Count, _Data);

	// 2) [������_����]�� ��ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	m_ptr;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
ptr::_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// 1) [������_����]��ŭ �����͵��� �߰��Ѵ�.
	for(int i=(int)(_Count-1);i>=0;--i)
	{
		_prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);
	}

	// 2) [������_����]�� ��ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// Return) 
	return	m_ptr;
}

inline void* ptr::_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)
{
	// Check) Buffer�� Size�� 0�̸� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-_Size)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 1) [����_����_������]�� ũ�⸦ _Size��ŭ ���δ�.
	char* p	 = m_ptr -_Size;
	
	// Check) _Size�� 0�̸� ������.
	if(_Size==0) return p;
	
	// 2) [����_����_������]�� [������]�� [������_ũ��]��ŭ �����Ѵ�.
	if(_Buffer!=nullptr && _Buffer!=p)
	{
		memcpy(p, _Buffer, _Size);
	}

	// 3) [����_����_������]�� ������Ʈ�Ѵ�.
	m_ptr	 = p;
	
	// Return) 
	return (void*)p;
}

template <class T>
void* ptr::_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size)
{
	// Check) Buffer�� Size�� 0�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [1] (" __FUNCTION__ ")"));
	
	// Check) 
	if(_String==nullptr) throw std::invalid_argument("string is nullptr (" __FUNCTION__ ")");

	// 1) String���̸� ���Ѵ�.(NULL���̱��� �����ϹǷ� +1�Ѵ�.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;	// strnlen(, _Buffer_Size)
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound �˻縦 �Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString-sizeof(COUNT_T))>=_bound.bound_lower);

	// 2) String������ �����Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String);

	// 3) Size�� �ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);
	
	// Return) ù��ġ�� ������.
	return	m_ptr;
}

template <class T>
void* ptr::_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) String���̸� ���Ѵ�.(NULL���̱��� �����ϹǷ� +1�Ѵ�.)
	size_t	lengthString = (size_t)_String.length()*sizeof(T)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString-sizeof(COUNT_T))>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// 2) String������ �����Ѵ�.
	_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeString, _String.c_str());

	// 3) Size�� �ִ´�.
	_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)lengthString);

	// Return) String�� ���� ó�� ��ġ�� ������!!
	return	m_ptr;
}

template <class T, size_t N>
void* ptr::_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString)
{
	// 1) [���ڿ�_����]�� ������ ũ�⸦ ���Ѵ�.
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 2) ������ [����_��ġ]�� ���Ѵ�.
	char*	p = m_ptr - sizeString - sizeof(COUNT_T);

	// Check) Lower Bound�� Uppder Bound�� �˻��Ѵ�.
	_CGD_BUFFER_BOUND_CHECK(p >= _bound.bound_lower && m_ptr <= _bound.bound_upper);

	// 1) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 2) [����_����_��_������]�� [���ڿ�]�� �����Ѵ�.
	memcpy(p + sizeof(COUNT_T), _constString.p, sizeString);

	// 3) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
	m_ptr -= (sizeof(COUNT_T)+sizeString);

	// Return) 
	return	m_ptr;
}

template <class T>
void* ptr::_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

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
	size_t	lengthString = _Xvsprintf(pStringStart, _Format, _ArgList)+1;
	int		sizeString	 = lengthString*sizof(T);

	// 3) ������ ��ġ�� ���Ѵ�.
	T*	p	 = m_ptr-sizeString;

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((p-sizeof(COUNT_T))>=_bound.bound_lower);
	
	// 4) [���ڿ�]�� �����Ѵ�.
	memcpy(p, pStringStart, sizeString);

	// 5) [��ǥ_������]�� sizeof(COUNT_T)��ŭ�� ����.
	p	-= sizeof(COUNT_T);

	// 6) [���ڿ�_����]�� ��ִ´�.
	*(COUNT_T*)p	 = lengthString;

	// 7)[����_����_������]�� ������Ʈ�Ѵ�.
	m_ptr	 = p;

	// 8) [�ӽ�_����]�Ҵ� ����
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
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

	// 1) [���ڿ�_����]�� ���Ѵ�.
	size_t	lengthString = std::char_traits<char>::length(_String);
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr-sizeString)>=_bound.bound_lower);

	// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
	T*	p = m_ptr-sizeString;
	
	// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
	if(p!=_String)
	{
		memcpy(p, _String, sizeString);
	}

	// 4) [����_����_������]�� [����_����_����]�� �ű��.
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

	// 2) [����_����_������]�� [���ڿ� ����] ��ŭ �� [��ǥ_������]�� ���Ѵ�..
	char*	p = m_ptr - sizeString;

	// 3) [����_����_������]�� ���ڿ��� [���ڿ� ����] ��ŭ �����Ѵ�.
	memcpy(p, _constText.p, sizeString);

	// 4) [����_����_������]�� [����_����_����]�� �ű��.
	m_ptr = p;

	// Return) 
	return	_constText.size();
}

template <class T>
size_t ptr::_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr<=_bound.bound_upper);

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
	T*		p	 = m_ptr-sizeString;

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
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);
	
	// 1) [����_����_��_������]�� ���Ѵ�.
	void*	p = m_ptr;
	
	// 2) [����_����_������]�� _Length��ŭ �ø���. 
	m_ptr	+= _Length;
	
	// Return) [����_����_��_������]���� �����Ѵ�.
	return	p;
}

template <class T>
T& ptr::_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T))<=_bound.bound_upper);
	
	// 1) [����_����_������]�� ���Ѵ�.
	T*	p	 = (T*)m_ptr;
	
	// 2) [����_����_������]�� ��(_Data)�� ��ִ´�.
	*p		 = _Data;
	
	// 3) [����_����_������]�� sizeof(T)��ŭ �ø���. 
	m_ptr	+= sizeof(T);
	
	// Return) [����_����_��_��]�� �����Ѵ�.
	return *p;
}

template <class T> 
typename std::enable_if<is_memcopy_able<T>::value, void*>::type
ptr::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T)*_Count)<=_bound.bound_upper);

	// Declare) �ӽ�
	ptr	temp	 = *this;

	// 1) [������_����]�� ����.
	temp._append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [������]���� ��ä�� �����Ѵ�.
	_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _Count*sizeof(T), _Data);

	// 3) [����_����_������]�� ������ ���´�.
	void* p = m_ptr;

	// 4) ����� �����͸� ������Ʈ
	m_ptr	 = temp.m_ptr;

	// Return) 
	return	p;
}

template <class T> 
typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
ptr::_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count)
{
	// Check) _Data�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Data!=nullptr, throw std::invalid_argument("_Data is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Count�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Count>=0, throw std::invalid_argument("_Count is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+sizeof(T)*_Count)<=_bound.bound_upper);

	// Declare) �ӽ�
	ptr	temp	 = *this;

	// 1) [������_����]�� ����.
	temp._append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Count);

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(size_t i=0;i<_Count;++i)
	{
		temp._append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Data[i]);

	}

	// 3) [����_����_������]�� ������ ���´�.
	void* p = m_ptr;

	// 4) ����� �����͸� ������Ʈ
	m_ptr	 = temp.m_ptr;

	// Return) 
	return	p;
}

inline void* ptr::_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer) 
{
	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [1] (" __FUNCTION__ ")"));

	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Size)<=_bound.bound_upper);

	// Check) _Size�� 0�̸� ������.
	if(_Size==0) return m_ptr;
	
	// 1) _Buffer�� null�� �ƴϸ� �����͸� �����Ѵ�.
	if(_Buffer!=nullptr && _Buffer!=m_ptr)
	{
		memcpy(m_ptr, _Buffer, _Size);
	}
	
	// 2) [����_����_������]�� ������ ���´�.
	void* p	 = m_ptr; 
	
	// 3) ���̸�ŭ �����͸� ������Ų��.
	m_ptr	+= _Size; 
	
	// Return) 
	return p;
}

template <class T>
void* ptr::_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String)
{
	// 1) ���ڿ��� ������ ��ġ�� ���Ѵ�.
	void*	strDest	 = m_ptr;

	// 2) [���ڿ�]�� �����Ѵ�.
	size_t	lengthString	 = _Xappend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(T*)(m_ptr + sizeof(COUNT_T)), _String);

	// 3) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [����]�� ������Ʈ�Ѵ�.
	m_ptr	+= lengthString*sizeof(T)+sizeof(COUNT_T);

	// Return) ����
	return	strDest;
}

template <class T>
void* ptr::_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& _String)
{
	// 1) [��ǥ_������]�� ���Ѵ�.
	void*	strDest	 = m_ptr;

	// 2) [���ڿ�]�� [��ǥ_������]�� �����Ѵ�.
	size_t	lengthString	 = _Xappend_string(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)(m_ptr + sizeof(COUNT_T)), _String.c_str(), _String.length());

	// 3) [���ڿ�_����]�� ��ִ´�.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [����_������]�� ������Ʈ�Ѵ�.
	m_ptr	+= (lengthString*sizeof(T)+sizeof(COUNT_T));

	// Return) ����
	return	strDest;
}

template <class T, size_t N>
void* ptr::_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T, N>& _constString)
{
	// Constexpr)
	const size_t	lengthString = _constString.size();
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && (m_ptr+sizeof(COUNT_T) + sizeString) <= _bound.bound_upper);

	// 1) [����_����_��_������]�� ��´�.
	char*	p = m_ptr;

	// 2) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)p = (COUNT_T)(lengthString);

	// 3) [����_����_��_������]�� [���ڿ�]�� �����Ѵ�.
	memcpy(p+sizeof(COUNT_T), _constString.p, sizeString);

	// 4) [����_����_����]�� [������_����]��ŭ ���Ѵ�.
	m_ptr += sizeString+sizeof(COUNT_T);

	// Return) 
	return	p;
}

template <class T>
void* ptr::_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// 1) [���ڿ�]�� ������ ��ġ�� ���Ѵ�.
	char*	strDest	 = m_ptr;

	// 2) [���ڿ�]�� �����Ѵ�.
	const size_t	lengthString	 = _Xappend_string_format(_CGD_BOUND_INFO_PASS _CGD_COMMA(T*)(m_ptr + sizeof(COUNT_T)), _Format, _ArgList);

	// 3) [���ڿ�_����]�� �����Ѵ�.
	*(COUNT_T*)m_ptr	 = (COUNT_T)lengthString;

	// 4) [����]�� ������Ʈ�Ѵ�.
	m_ptr	 = (char*)(lengthString*sizeof(T)+string_length);

	// Return) 
	return	(T*)strDest;
}

template<class T>
size_t ptr::_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr) >= _bound.bound_lower);

	// 1) [���ڿ�]�� ���̸� ���Ѵ�.
	const size_t	lengthString = std::char_traits<T>::length(_String);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr + sizeString) <= _bound.bound_upper);

	// 2) [���ڿ�]�� �����Ѵ�.
	memcpy(m_ptr, _String, sizeString);

	// 3) [����_������]�� ���̸�ŭ ���Ѵ�.
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

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && m_ptr+sizeString<_bound.bound_upper);

	// 1) [���ڿ�]�� �����ϰ� [���ڿ�_����]��ŭ ���Ѵ�.
	memcpy(m_ptr, _constText.p, sizeString);

	// 2) [���ڿ�_����]��ŭ ���Ѵ�.
	m_ptr += sizeString;

	// Return) 
	return	lengthString;
}

template <class T>
size_t ptr::_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, va_list _ArgList)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower);

	// 1) [���ڿ�]�� ������ ��ġ�� �����Ѵ�.
	T*	strDest	 = (T*)m_ptr;

	// 2) [���ڿ�]�� �����Ѵ�.
	const size_t	lengthString = _Xvsprintf(strDest, _Format, _ArgList);
	const size_t	sizeString	 = lengthString*sizeof(T);

	// 3) String ���̸�ŭ...
	m_ptr += sizeString;

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
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
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);

	// 1) [����_����_������]�� ũ�⸦ �ӽ÷� �����Ѵ�.
	char*	p	 = m_ptr;
	
	// 1) [����_����_������]�� ũ�⸦ _Length��ŭ �ø���.
	m_ptr	+= _Length;
	
	// Return) [����_����_ó��_������]
	return p;
}

template <class T>
COUNT_T ptr::_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(p_iLengthInWords) T* _String, _In_ size_t p_iLengthInWords)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("string pointer is nullptr! [0] (" __FUNCTION__ ")"));

	// Check) Buffer�� Size�� 0�̸� �ȵȴ�.
	CGD_ASSERT(p_iLengthInWords>=0, throw std::invalid_argument("length of word is zero or less! [1] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower);

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	COUNT_T	lengthString	 = *(COUNT_T*)m_ptr;

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString==(COUNT_T)-1)
	{
		m_ptr	+= sizeof(COUNT_T);
		return	(COUNT_T)-1;
	}

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ���� (NULL����)�� ũ�� ������ ������!
	if(lengthString<1) throw std::length_error("buffer size is too small!! [5] (" __FUNCTION__ ")");

	// 2) [������_ũ��]�� ����Ѵ�.(COUNT_T[���ڿ�_����]+size(String))
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) [������_ũ��]�� UPper Bound�� �Ѿ���� �˻��Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+sizeData)<=_bound.bound_upper);

	// Check) [���ڿ�]�� �������� NULL�ΰ��� Ȯ���Ѵ�.
	if(*(T*)(m_ptr+sizeString+sizeof(COUNT_T)-sizeof(T)) != NULL) throw std::length_error("it's invalid string!! [6] (" __FUNCTION__ ")");

	// 3) ���ڿ��� �����Ѵ�.
	memcpy(_String, m_ptr+sizeof(COUNT_T), sizeString);

	// 4) [����_����_������]�� [������_ũ��]��ŭ ���Ѵ�.
	m_ptr	+= (sizeData+sizeof(COUNT_T));

	// Return) String���̸� return�Ѵ�.
	return	lengthString;
}

template <class T>
T* ptr::_extract_string_pointer(_CGD_BOUND_INFO_PARAM)
{
	// Check) [����_����_������]�� lower Bound���ٴ� Ŀ���Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower);

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	size_t	sizeString	 = (size_t)(*(COUNT_T*)m_ptr);

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(sizeString<0)
	{
		return	nullptr;
	}

	// Check) [���ڿ�_����]�� �ּ� ���ڿ��� ����(NULL����)�� ũ�� ������ ������!
	if(sizeString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [������_ũ��]�� ����Ѵ�.(COUNT_T[���ڿ�_����]+length(String))
	size_t	sizeBuffer	 = sizeString*sizeof(T)+sizeof(COUNT_T);

	// Check) [������_ũ��]�� UPper Bound�� �Ѿ���� �˻��Ѵ�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+sizeBuffer)<=_bound.bound_upper);

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(m_ptr+sizeBuffer-sizeof(T)) != NULL) throw std::length_error("it's invalid string! [1] (" __FUNCTION__ ")");

	// 3) ���ڿ��� ���� �� �����͸� ���д�.
	T*	strString	 = (T*)(m_ptr+sizeof(COUNT_T));

	// 4) [����_����_������]�� [������_ũ��]��ŭ ���Ѵ�.
	m_ptr	+= sizeBuffer;

	// Return) [���ڿ�_����_������]�� �����Ѵ�.
	return	strString;
}

template <class T>
std::basic_string<T> ptr::_extract_string(_CGD_BOUND_INFO_PARAM)
{
	// Return) [���ڿ�]�� �����Ѵ�. (RVO)
	return	std::basic_string<T>(_extract_string_pointer<T>(_CGD_BOUND_INFO_PASS));
}

inline char* ptr::_extract_web(_CGD_BOUND_INFO_PARAM)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr;
	const char*	pEnd	 = m_ptr+UINT_MAX;

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - ��� m_ptr�� ������ ���´�.
			char*	pHead	 = m_ptr;

			// - m_ptr�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
			m_ptr		 = (chNow+2);
			//len		 = (COUNT_T)(pEnd-chNow-1);

			// Return) 
			return	pHead;
		}
	}

	// Return) ����! Web Message�� �ϼ����� ���ߴ�.
	throw	nullptr;
}

inline char* ptr::_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* p_pstrBuffer, _In_ size_t _Buffer_Size)
{
	// Check) 
	CGD_ASSERT(p_pstrBuffer!=nullptr, throw std::invalid_argument("_format string is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Buffer_Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Buffer_Size>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Buffer_Size)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr;
	const char*	pEnd	 = m_ptr+UINT_MAX;

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - �븮�� ���Ѵ�.
			size_t	ilength = chNow - m_ptr;

			// - �ִ� ���۸� �����ʵ��� �Ѵ�.
			if(ilength>(_Buffer_Size-1)) ilength=(_Buffer_Size-1);

			// - �����Ѵ�
			memcpy(p_pstrBuffer, m_ptr, ilength);

			// - �������� NULL�� �߰��Ѵ�.
			*(p_pstrBuffer+ilength)	 = NULL;

			// - m_ptr�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
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
	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Size)<=_bound.bound_upper);

	// Check) ���̰� 0�̸� �׳� �ǵ�����.
	if(_Size==0)
	{
		return	(void*)m_ptr;
	}

	// 1) �����Ѵ�.
	memcpy(_Buffer, m_ptr, _Size);

	// Declare)
	void*	p	 = (void*)m_ptr;

	// 2) _Size��ŭ ���Ѵ�.
	m_ptr	+= _Size;

	// Return) 
	return	p;
}

inline void* ptr::_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length)
{
	// Check) _Length�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Length>=0, throw std::invalid_argument("_Length is invalid [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr)>=_bound.bound_lower && (m_ptr+_Length)<=_bound.bound_upper);

	// 1) [����_����_����]�� _Length��ŭ ���δ�.
	m_ptr	-= _Length;
	
	// Return) [����_����_��_������]
	return (void*)m_ptr;
}

template <class T>
T& ptr::_subtract_general(_CGD_BOUND_INFO_PARAM)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(m_ptr>=_bound.bound_lower && (m_ptr+sizeof(T))<=_bound.bound_upper);
	
	// 1) [����_����_����]�� sizeof(T)��ŭ ���δ�.
	m_ptr	-= sizeof(T);
	
	// Return) [����_����_ó��_��]�� �����Ѵ�.
	return *(T*)m_ptr;
}

inline char* ptr::_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Return) _Offset��ŭ �̵��� ��ġ�� �����Ѵ�.
	return m_ptr+_Offset;
}

inline ptr ptr::_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Return) _Offset��ŭ �̵��� ���� ������ ����(RVO)
	return ptr(m_ptr+_Offset);
}

template <typename T>
T& ptr::_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset+sizeof(T))<=_bound.bound_upper);

	// 1) [����_����_ó��_������]+[_Offset]�� ��´�.
	T* p	 = (T*)(m_ptr+_Offset);
	
	// 2) Offset�� Sizeof(T)������Ų��.
	_Offset	+= sizeof(T);
	
	// Return) [����_����_������]+[_Offset]���� �����Ѵ�.
	return *p;
}

template<typename T>
T* ptr::_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const 
{
	// Check) [���ڿ�_��_��ġ]�� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower);

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(m_ptr+_Offset));

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString<0)
	{
		return	nullptr;
	}

	// Check) String�� ���̰� sizeof(T)���� ������ ������!  (nullptr�� ���ԵǹǷ� �ּ��� sizeof(T)��ŭ�� �Ǿ� �Ѵ�.
	if(lengthString<1) throw std::length_error("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [���ڿ�_����_��ġ]�� ���Ѵ�.
	size_t	posStart = _Offset+sizeof(COUNT_T);

	// 3) [���ڿ�_��_��ġ]�� ���Ѵ�.
	size_t	posTail	 = posStart+lengthString*sizeof(T);

	// Check) [���ڿ�_��_��ġ]�� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+posTail)<=_bound.bound_upper);

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(m_ptr+posTail-sizeof(T))!=NULL) throw std::out_of_range("Invalid string! [2] (" __FUNCTION__ ")");
	
	// 3) Offset�� ���Ѵ�.
	_Offset		 = (int)posTail;

	// Return) String�� ��ġ�� return�Ѵ�.
	return	(T*)(m_ptr+posStart);
}

template<typename T>
std::basic_string<T>  ptr::_front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) [���ڿ�_��_��ġ]�� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower);

	// 1) [���ڿ�_����]�� ����.(���� ó�� 4Byte�� ���ڿ��� ���̴�.)
	size_t	lengthString	 = (size_t)(*(COUNT_T*)(m_ptr+_Offset));

	// Check) length�� 0���� ������ �׳� �����Ѵ�.
	if(lengthString<0)
	{
		return	std::basic_string<T>();
	}

	// Check) String�� ���̰� sizeof(T)���� ������ ������!(nullptr�� ���ԵǹǷ� �ּ��� sizeof(T)��ŭ�� �Ǿ� �Ѵ�.
	if(lengthString<1) throw std::out_of_range("string is too short!! [1] (" __FUNCTION__ ")");

	// 2) [���ڿ�_����_��ġ]�� ���Ѵ�.
	size_t	posStart = _Offset+sizeof(COUNT_T);

	// 3) [���ڿ�_��_��ġ]�� ���Ѵ�.
	size_t	posTail	 = posStart+lengthString*sizeof(T);

	// Check) [���ڿ�_��_��ġ]�� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+posTail)<=_bound.bound_upper);

	// Check) ���ڿ��� ���� ���� NULL���� Ȯ���Ѵ�.
	if(*(T*)(m_ptr+posTail-sizeof(T))!=NULL) throw std::out_of_range("string is too short!! [3] (" __FUNCTION__ ")");

	// 4) ���������� ���� Offset���� ������Ʈ�Ѵ�.
	_Offset		 = (int)posTail;

	// Return) [���ڿ�]�� �����Ѵ�. (RVO)
	return	std::basic_string<T>((T*)(m_ptr+posStart));
}

inline char* ptr::_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset)<=_bound.bound_upper);

	// Definition)
	const uint16_t	wCompare	 = ('\n'<<8) | '\r';

	// Declare)
	char*		chNow	 = m_ptr+_Offset;
	const char*	pEnd	 = m_ptr+_Offset+INT_MAX;

	// 1) /r/n�� ã�´�.
	for(; chNow<pEnd; ++chNow)
	{
		if(*(uint16_t*)chNow==wCompare)
		{
			// - ��� m_ptr�� ������ ���´�.
			char*	pHead	 = m_ptr;

			// - m_ptr�� chNow+2�� �����Ѵ�. (/r/n�κ��� ��������+2�� ��.)
			//m_ptr		 = (chNow+2);
			//len		 = (COUNT_T)(pEnd-chNow-1);

			// 5) Offset�� ��ִ´�.
			_Offset	 = (int)(chNow+2-m_ptr);

			// Return) 
			return	pHead;
		}
	}

	// Return) ����! Web Message�� �Ϸ���� �ʾҴ�.
	return	nullptr;
}

inline void ptr::_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA size_t _Offset, size_t _Size, void * _Buffer) const
{
	// Check) _Buffer�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Buffer!=nullptr, throw std::invalid_argument("_Buffer is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_Size>=0, throw std::invalid_argument("_Size is invalid [1] (" __FUNCTION__ ")"));

	// Check) Lower Bound & Upper Bound Ȯ��
	_CGD_BUFFER_BOUND_CHECK((m_ptr+_Offset)>=_bound.bound_lower && (m_ptr+_Offset+_Size)<=_bound.bound_upper);

	// 1) �����Ѵ�.
	memcpy(_Buffer, m_ptr+_Offset, _Size);
}


}