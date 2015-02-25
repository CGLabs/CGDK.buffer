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
// Common Functions
//
//-----------------------------------------------------------------------------
inline size_t _Xvsprintf(_Inout_z_ char* _Dest, _In_z_ const char* _Format, _In_ va_list _Args)
{
	#pragma warning(disable:4996)
	return	std::vsprintf(_Dest, _Format, _Args);
	#pragma warning(default:4996)
}

inline size_t _Xvsprintf(_Inout_z_ wchar_t* _Dest, _In_z_ const wchar_t* _Format, _In_ va_list _Args)
{
	#pragma warning(disable:4996)
	return	std::vswprintf(_Dest, _Format, _Args);
	#pragma warning(default:4996)
}

template <class T>
size_t _Xappend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_z_count_(_StringLength) const T* _String, _In_ size_t _StringLength)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Buffer_Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_StringLength>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// 1) [����_����]�� ���Ѵ�.(NULL���̱��� �����ϹǷ� +sizeof(T)�Ѵ�.)
	size_t	lengthString = _StringLength+1;	// strnlen(, _Buffer_Size)
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower and Upper Bound
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower && ((char*)_Dest+sizeString+sizeof(COUNT_T))<=_bound.bound_upper);

	// 5) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
	memcpy(_Dest, _String, sizeString);

	// Return) [����_����]�� ������
	return	lengthString;
}

template <class T>
size_t _Xappend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const T* _String)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower);

	// 1) [����_����]�� ���Ѵ�.(NULL���̱��� �����ϹǷ� +sizeof(T)�Ѵ�.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;	// strnlen(, _Buffer_Size)
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Upper Bound
	_CGD_BUFFER_BOUND_CHECK(((char*)_Dest+sizeString)<=_bound.bound_upper);

	// 5) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
	memcpy((void*)_Dest, (const void*)_String, sizeString);

	// Return) [����_����]�� ������
	return	lengthString;
}

template <class T>
size_t _Xappend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const T* _Format, _In_ const std::va_list& _Va_list)
{
	// Check) _Format�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower);

	// 1) String ����!!!
	size_t	lengthString = _Xvsprintf(_Dest, _Format, _Va_list)+1;
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(((char*)_Dest+sizeString)<=_bound.bound_upper);

	// Return) 
	return	lengthString;
}

#ifdef _SUPPORT_SYSTEMTIME
template <class T>
void _Xappend_systemtime(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const SYSTEMTIME& _Datetime)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower && ((char*)_Dest+sizeof(uint32_t)*3)<=_bound.bound_upper);

	// 1) String ����!!!
	_Dest->_append_general<uint32_t>((_Datetime.wYear << 16) | (_Datetime.wMonth << 16));
	_Dest->_append_general<uint32_t>(((uint32_t)_Datetime.wDay << 24) | ((uint32_t)_Datetime.wHour << 16) | ((uint32_t)_Datetime.wMinute << 8) | ((uint32_t)_Datetime.wSecond));
	_Dest->_append_general<uint32_t>(_Datetime.wMilliseconds);
}

template <class S>
SYSTEMTIME _Xextract_systemtime(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	uint32_t	yearmonth		 = _Source->_extract_general<uint32_t>(_CGD_BOUND_INFO_PASS);
	uint32_t	dayhourminsec	 = _Source->_extract_general<uint32_t>(_CGD_BOUND_INFO_PASS);
	uint32_t	tickMillisecond	 = _Source->_extract_general<uint32_t>(_CGD_BOUND_INFO_PASS);

	SYSTEMTIME	tempTime;

	tempTime.wYear			 = (yearmonth>>16);
	tempTime.wMonth			 = yearmonth & 0xffff;
	tempTime.wDay			 = dayhourminsec>>24 & 0xff;
	tempTime.wDayOfWeek		 = 0;
	tempTime.wHour			 = dayhourminsec>>16 & 0xff;
	tempTime.wMinute		 = dayhourminsec>>8 & 0xff;
	tempTime.wSecond		 = dayhourminsec & 0xff;

	return	tempTime;
}
#endif

template <class T>
void _Xappend_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const tm& _tm)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest->get_back_ptr())>=_bound.bound_lower && ((char*)_Dest->get_back_ptr()+sizeof(uint32_t)*3)<=_bound.bound_upper);

	// 1) String ����!!!
	_Dest->_append_general<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA ((_tm.tm_year+1900) << 16) | (_tm.tm_mon << 16));
	_Dest->_append_general<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA ((uint32_t)_tm.tm_mday << 24) | ((uint32_t)_tm.tm_hour << 16) | ((uint32_t)_tm.tm_min << 8) | ((uint32_t)_tm.tm_sec));
}

template <class S>
tm _Xextract_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	uint32_t	yearmonth		 = _Source->_extract<uint32_t>(_CGD_BOUND_INFO_PASS);
	uint32_t	dayhourminsec	 = _Source->_extract<uint32_t>(_CGD_BOUND_INFO_PASS);
	uint32_t	tickMillisecond	 = _Source->_extract<uint32_t>(_CGD_BOUND_INFO_PASS);

	tm	tempTime;

	tempTime.tm_year	 = (yearmonth>>16)-1900;
	tempTime.tm_yday	 = 0;
	tempTime.tm_mon		 = yearmonth & 0xffff;
	tempTime.tm_mday	 = dayhourminsec>>24 & 0xff;
	tempTime.tm_wday	 = 0;
	tempTime.tm_hour	 = dayhourminsec>>16 & 0xff;
	tempTime.tm_min		 = dayhourminsec>>8 & 0xff;
	tempTime.tm_sec		 = dayhourminsec & 0xff;
	tempTime.tm_isdst	 = 0;

	return	tempTime;
}



template <class S, class T>
typename T::value_type* _Xprepend_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) Begin/End Iterator
	auto	riter	 = _container.rbegin();
	auto	riterEnd = _container.rend();

	// 2) [������]���� ��ִ´�.
	for(; riter!=riterEnd; ++riter)
	{
		_Source->_prepend<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *riter);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, typename T::value_type*>::type
 _Xprepend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������]���� �ٷ� memcopy�Ѵ�.
	_Source->_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _container.size()*sizeof(T::value_type), &_container.front());

	// 2) [������_����]�� ��ִ´�.
	_Source->_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, typename T::value_type*>::type
 _Xprepend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) Begin/End Iterator
	auto	riter	 = _container.rbegin();
	auto	riterEnd = _container.rend();

	// 2) [������]���� ��ִ´�.
	for(; riter!=riterEnd; ++riter)
	{
		_Source->_prepend<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *riter);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template<class S, class RI> 
typename std::enable_if<is_iterator<RI>::value, int>::type _Xprepend_iterator(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ RI _Reverse_first, _In_ RI _Reverse_last)
{
	// Declare)
	COUNT_T iCount	 = 0;

	// 1) �����͵��� �����Ѵ�.
	for(; _Reverse_first!=_Reverse_last; ++_Reverse_first, ++iCount)
	{
		_Source->_prepend<typename RI::value_type>(_CGD_BOUND_INFO_PASS *_Reverse_first);
	}

	// 2) ũ�⸦ ����� ��ġ ����
	_Source->_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iCount);

	// Return) 
	return	iCount;
}

template <class S, class T>
typename T::value_type* _Xappend_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������_����]�� ��ִ´�.
	_Source->_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_container.size());

	// 2) [����_����_��_������]�� �����´�.
	//typename T::value_type*	pret = (typename T::value_type*)(buf+len);
	typename T::value_type*	pret = nullptr;	// �ӽ�

	// 3) [������]���� ��ִ´�.
	auto iter=_container.begin();
	auto iterEnd=_container.end();

	for(; iter!=iterEnd; ++iter)
	{
		_Source->_append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, void*>::type
 _Xappend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������_����]�� ��ִ´�.
	_Source->_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_container.size());

	// 2) [����_����_��_������]�� �����´�.
	//typename T::value_type*	pret = (typename T::value_type*)(buf+len);
	typename T::value_type*	pret = nullptr;	// �ӽ�

	// 3) [������]���� ��ִ´�.
	_Source->_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA _container.size()*sizeof(T::value_type), &_container.front());

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, void*>::type
_Xappend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [����_����_��_������]�� �����´�.
	void*	pret = (void*)_Source->get_back_ptr();

	// 2) [������_����]�� ��ִ´�.
	_Source->_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_container.size());

	// 3) [������]���� ��ִ´�.
	auto iter=_container.begin();
	auto iterEnd=_container.end();

	for(; iter!=iterEnd; ++iter)
	{
		_Source->_append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template<class S, class I> 
typename std::enable_if<is_iterator<I>::value, int>::type _Xappend_iterator(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ I _First, _In_ I _Last)
{
	// 1) [������_����]�� ��ִ´�.
	COUNT_T*	pCount = (COUNT_T*)_Source->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(COUNT_T));

	// Declare)
	COUNT_T iCount	 = 0;

	// 3) [������]���� ��ִ´�.
	for(; _First!=_Last; ++_First, ++iCount)
	{
		_Source->_append<typename I::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *_First);
	}

	// 3) ������ ���� ��ġ�� ������ ��ִ´�.
	*pCount	 = iCount;

	// Return) 
	return	iCount;
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, T>::type
_Xextract_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<0)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ vector�� Resize�� �Ѵ�.
	container.resize(countData);

	// 3) [������_����]��ŭ ��°�� ����
	_Source->_extract_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA countData*sizeof(T::value_type), &container.front());

	// Return) 
	return	std::move(container);
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, T>::type
_Xextract_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<0)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_Source->_extract<T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xextract_container_CGPTR_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<0)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->_extract<T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.push_back(pObject);
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xextract_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData=_Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}
	
	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_Source->_extract<typename T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xextract_container_CGPTR_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;
	
	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(pObject);
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xextract_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.insert(_Source->_extract<T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xextract_CGPTR_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T		countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->_extract<T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.insert(pObject);
	}

	// Return) 
	return	std::move(container);
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, T>::type
_Xfront_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ vector�� Resize�Ѵ�.
	container.resize(countData);

	// 4) [������_����]��ŭ ��°�� �о���δ�.
	_Source->_copy_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset, countData*sizeof(T::value_type), &container.front());

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset+countData*sizeof(T::value_type);

	// Return) 
	return	std::move(container);
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, T>::type
_Xfront_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 4) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xfront_CGPTR_vector(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 4) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(pObject);
	}

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xfront_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T		container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xfront_container_CGPTR_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T		container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(pObject);
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xfront_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.insert(_RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template <class S, class T>
T _Xfront_CGPTR_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		CGPTR<typename T::value_type::_pointer_type>	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.insert(pObject);
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

template<class S, class T>
void* _Xprepend_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _Container)
{
	// 1) Begin/End Iterator
	auto	iter	 = _Container.begin();
	auto	iterEnd = _Container.end();

	// 2) [������]���� ��ִ´�.
	for(; iter!=iterEnd; ++iter)
	{
		// - Value�� ��ִ´�.
		_Source->_prepend<typename T::mapped_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->second);
		// _ Key�� ��ִ´�.
		_Source->_prepend<typename T::key_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->first);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->_prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Container.size());

	// Return) 
	return	(typename T::mapped_type*)_Source->get_ptr();
}

template<class S, class T>
void* _Xappend_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _Container)
{
	// 1) [����_����_��_������]�� �����´�.
	void*	pret = _Source->get_back_ptr();

	// 2) [������_����]�� ��ִ´�.
	_Source->_append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Container.size());

	// 3) [������]���� ��ִ´�.
	for(auto iter=_Container.begin(); iter!=_Container.end(); ++iter)
	{
		// _ Key�� ��ִ´�.
		_Source->_append<typename T::key_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->first);
		// - Value�� ��ִ´�.
		_Source->_append<typename T::mapped_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->second);
	}

	// Return) 
	return	(typename T::mapped_type*)pret;
}

template<class S, class T, size_t X>
CGD::_RETURN_ARRAY<T,X> _Xextract_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	_RETURN_ARRAY<T,X>	arrayTemp;

	// 1) [������_������ ���� �о���δ�.]
	size_t	count	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) [������_����]�� X���� ũ�� Exception�� ������. (Overflow ����!)
	if(count>X) throw std::length_error("Array is too small [0] (" __FUNCTION__ ")");

	// 2) [������_����]��ŭ �о���δ�.
	for(size_t i=0; i<count; ++i)
	{
		arrayTemp.value[i]	 = _Source->_extract<T>(_CGD_BOUND_INFO_PASS);
	}

	// Return) 
	return	arrayTemp;
}

template<class S, class T>
T _Xextract_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		typename T::key_type	tempKey		 = _Source->_extract<typename T::key_type>(_CGD_BOUND_INFO_PASS);
		typename T::mapped_type	tempMapped	 = _Source->_extract<typename T::mapped_type>(_CGD_BOUND_INFO_PASS);

		// _ Key�� ���� ��ִ´�.
		container.insert(std::make_pair(std::move(tempKey), std::move(tempMapped)));
	}

	// Return) 
	return	std::move(container);
}

template<class S, class T>
T _Xextract_CGPTR_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->_extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		return	std::move(container);
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		typename T::key_type	tempKey		 = _Source->_extract<typename T::key_type>(_CGD_BOUND_INFO_PASS);

		// - Create
		CGPTR<(typename T::mapped_type)::_pointer_type>	pObject	 = NEW<(typename T::mapped_type)::_pointer_type>();
		
		// - pop...
		pObject	 = _Source->_extract<typename T::mapped_type>(_CGD_BOUND_INFO_PASS);

		// _ Key�� ���� ��ִ´�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// Return) 
	return	std::move(container);
}

template<class S, class T>
T _Xfront_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _In_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		typename T::key_type	tempKey		 = _RH<typename T::key_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);
		typename T::mapped_type	tempMapped	 = _RH<typename T::mapped_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		container.insert(std::make_pair(std::move(tempKey), std::move(tempMapped)));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}


template<class S, class T>
T _Xfront_CGPTR_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _In_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T)-1)
	{
		_Offset		 = tempOffset;
		return	std::move(container);
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		typename T::key_type	tempKey		 = _RH<typename T::key_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Create
		CGPTR<(typename T::mapped_type)::_pointer_type>	pObject	 = NEW<(typename T::mapped_type)::_pointer_type>();

		// - pop...
		pObject	 = _RH<typename T::mapped_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Key�� ���� �߰��Ѵ�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	std::move(container);
}

