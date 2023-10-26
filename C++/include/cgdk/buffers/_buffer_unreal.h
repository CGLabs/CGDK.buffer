//*****************************************************************************
//*                                                                           *
//*                               CGDK::buffer                                *
//*                       ver 3.03 / release 2023.10.17                       *
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
#if defined(UE_BUILD_DEBUG) || defined(UE_BUILD_DEVELOPMENT) || defined(UE_BUILD_TEST) || defined(UE_BUILD_SHIPPING)

// FString
class CORE_API FString;

// FStringView
template <typename CharType> 
class TStringViewImpl;


// array - TArray, FArchiveDiffMap, FArrayReader, ... , VectorND
template<typename InElementType, typename InAllocator>
class TArray;

// array - TStaticArray, TShaderResourceParameterArray
template<typename InElementType, uint32 NumElements, uint32 Alignment>
class TStaticArray;

// array - TSparseArray
template<typename InElementType, typename Allocator>
class TSparseArray;

// singly linked list - TList
template<class ElementType>
class TList;

// doubly linked list - TLinkedList, TIntrusiveLinkedList, TLinkedList
template<class ContainerType, class ElementType, template< class, class > class IteratorType>
class TLinkedListBase;
template <class ElementType>
class TIntrusiveLinkedList;

// doubly linked list - TDoubleLinkedList
template <class ElementType>
class TDoubleLinkedList;


// set - TSet, 	FTouchKeySet
template<typename InElementType, typename KeyFuncs, typename Allocator>
class TSet;

// map - TSortableMapBase, TMap, TMultiMap
template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
class TMapBase;

// sorted map - TSortedMap, FAssetDataTagMap
template<typename KeyType, typename ValueType, typename ArrayAllocator, typename SortPredicate>
class TSortedMap;


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// 1) ue4 FString
template<class T, class F = void> struct is_ue4_FString : public std::false_type {};
template<class T> struct is_ue4_FString<T, std::enable_if_t<std::is_base_of_v<FString, T>>> : public std::true_type {};
template <class T> constexpr bool is_ue4_FString_v = is_ue4_FString<T>::value;

// 2) ue4 FStringView
template<class T, class F = void> struct is_ue4_FStringView : public std::false_type {};
template<class A> struct is_ue4_FStringView<TStringViewImpl<A>, void> : public std::true_type {};
template<>        struct is_ue4_FStringView<FStringView, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_FStringView_v = is_ue4_FStringView<T>();

// 3) array - TArray, FArchiveDiffMap, FArrayReader, ... , VectorND
template<class T, class F = void> struct is_ue4_TArray : public std::false_type {};
template<typename A1, typename A2> struct is_ue4_TArray<TArray<A1,A2>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TArray_v = is_ue4_TArray<T>::value;

// 4) array - TStaticArray, TShaderResourceParameterArray
template<class T, class F = void> struct is_ue4_TStaticArray : public std::false_type {};
template<typename A1, uint32_t A2, uint32_t A3> struct is_ue4_TStaticArray<TStaticArray<A1,A2,A3>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TStaticArray_v = is_ue4_TStaticArray<T>::value;

// 5) array - TSparseArray
template<class T, class F = void> struct is_ue4_TSparseArray : public std::false_type {};
template<typename A1, typename A2> struct is_ue4_TSparseArray<TSparseArray<A1,A2>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TSparseArray_v = is_ue4_TSparseArray<T>::value;

// 6) singly linked list - TList
template<class T, class F = void> struct is_ue4_TList : public std::false_type {};
template<typename A1> struct is_ue4_TList<TList<A1>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TList_v = is_ue4_TList<T>::value;

// 7) doubly linked list - TLinkedList, TIntrusiveLinkedList
template<class T, class F = void> struct is_ue4_TLinkedListBase : public std::false_type {};
template<class A1, class A2, template< class, class > class A3> struct is_ue4_TLinkedListBase<TLinkedListBase<A1, A2, A3>, void> : public std::true_type {};
template<class A1> struct is_ue4_TLinkedListBase<TLinkedList<A1>, void> : public std::true_type {};
template<class A1> struct is_ue4_TLinkedListBase<TIntrusiveLinkedList<A1>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TLinkedListBase_v = is_ue4_TLinkedListBase<T>::value;

// 8) set - TSet, 	FTouchKeySet
template<class T, class F = void> struct is_ue4_TSet : public std::false_type {};
template<typename A1, typename A2, typename A3> struct is_ue4_TSet<TSet<A1, A2, A3>, void> : public std::true_type {};
template<>			struct is_ue4_TSet<FTouchKeySet, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TSet_v = is_ue4_TSet<T>::value;

// 9) map - TSortableMapBase, TMap, TMultiMap
template<class T, class F = void> struct is_ue4_TMapBase : public std::false_type {};
template<typename A1, typename A2, typename A3, typename A4> struct is_ue4_TMapBase<TSortableMapBase<A1,A2,A3,A4>, void> : public std::true_type {};
template<typename A1, typename A2, typename A3, typename A4> struct is_ue4_TMapBase<TMap<A1, A2, A3, A4>, void> : public std::true_type {};
template<typename A1, typename A2, typename A3, typename A4> struct is_ue4_TMapBase<TMultiMap<A1, A2, A3, A4>, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TMapBase_v = is_ue4_TMapBase<T>::value;

// 10) sorted map - TSortedMap, FAssetDataTagMap
template<class T, class F = void> struct is_ue4_TSortedMap : public std::false_type {};
template<typename A1, typename A2, typename A3, typename A4> struct is_ue4_TSortedMap<TSortedMap<A1, A2, A3, A4>, void> : public std::true_type {};
template<>													 struct is_ue4_TSortedMap<FAssetDataTagMap, void> : public std::true_type {};
template <class T> constexpr bool is_ue4_TSortedMap_v = is_ue4_TSortedMap<T>::value;


//-----------------------------------------------------------------------------
//
// Includes
//
//-----------------------------------------------------------------------------
namespace CGDK
{


template<class B, class S, class T>
_buffer_view<typename B::element_t> _ue4_prepend_FStringView(S& _s, const TStringViewImpl<T>& _object)
{
	using RET_T = _buffer_view<typename B::element_t>;

	// 1) ...
	auto buf_old = _s.data();

	// 2) String길이를 구한다.(NULL길이까지 포함하므로 +1한다.)
	auto length_string = _object.Len();
	auto size_string = length_string * sizeof(T);

	// check) lower bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() - size_string - sizeof(COUNT_T)) >= _s.get_lower_bound());

	// 3) NULL으르 제일 먼저 넣는다.
	_s.template _prepend_general<T>(0);

	// 4) [문자열]을 [문자열_길이]만큼 복사한다.
	_s._prepend_bytes(size_string, _object.GetData());

	// 5) [문자열_길이]를 써넣는다.
	_s.template _prepend_general<COUNT_T>(static_cast<COUNT_T>(length_string + 1));

	// return) String의 제일 처음 위치를 리턴함!!
	return base_t(_s.data(), buf_old - _s.data());
}

template<class B, class S, class T>
_buffer_view<typename B::element_t> _ue4_append_FStringView(S& _s, const TStringViewImpl<T>& _object)
{
	using RET_T = _buffer_view<typename B::element_t>;

	// 1) [목표_포인터]를 구한다.
	auto buf_dest = _s.data() + _s.size();

	// 2) get values
	auto length_string = _object.Len();	// strnlen(, _buffer_size)
	auto bytes_copy = length_string * sizeof(T);
	auto added_length = sizeof(COUNT_T) + sizeof(T) + bytes_copy;

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((buf_dest + added_length) <= _s.get_upper_bound());

	// declare) 
	auto buf_now = buf_dest;

	// 3) [문자열_길이]를 저장한다. (NULL포함)
	*reinterpret_cast<COUNT_T*>(buf_now) = static_cast<COUNT_T>(length_string + 1);
	buf_now += sizeof(COUNT_T);

	// 4) copy string
	if (bytes_copy != 0)
	{
		memcpy(buf_now, _object.GetData(), bytes_copy);
		buf_now += bytes_copy;
	}

	// 5) NULL을 추가한다.
	*reinterpret_cast<T*>(buf_now) = 0;

	// 6) [버퍼_길이]를 업데이트한다.
	_s.add_size(added_length);

	// return)
	return _buffer_view<typename B::element_t>(buf_dest, added_length);
}

template<class T, class S>
inline T _ue4_extract_FStringView(S& _s)
{
	// 1) [데이터_크기]를 얻어온다.(COUNT_T[문자열_길이]+length(String))
	COUNT_T	str_length = _s.template _get_front_string_length<typename T::ElementType>();

	// check) length가 0보다 작으면 그냥 리턴한다.
	if (str_length == COUNT_T(-1))
	{
		_s += offset(sizeof(COUNT_T));
		return T();
	}

	// 2) 문자열의 제일 앞 포인터를 얻어둔다.
	auto str_string = _s.template data<typename T::ElementType>(sizeof(COUNT_T));

	// 2) sizeOfData 구하기
	auto size_data = static_cast<COUNT_T>(str_length * sizeof(typename T::ElementType) + sizeof(COUNT_T));

	// 3) [원본_버퍼_포인터]와 [원본_버퍼_길이]를 [데이터_크기]만큼 이동시킨다. 
	_s += offset(size_data);

	// return) [문자열_시작_포인터]을 리턴한다.
	return T(str_string, static_cast<int32>(str_length) - 1);
}
inline size_t _ue4_size_of_FStringView(const FStringView& _object)
{
	return sizeof(COUNT_T) + (_object.Len() + 1) * sizeof(TCHAR);
}

//-----------------------------------------------------------------------------
// 1) ue4 - FString
//-----------------------------------------------------------------------------
template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_FString_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const FString& _data)	{ return _ue4_prepend_FStringView<B>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, FString&& _data)			{ return _ue4_prepend_FStringView<B>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_FString_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const FString& _data)	{ return _ue4_append_FStringView<B, S, TCHAR>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, FString&& _data)			{ return _ue4_append_FStringView<B, S, TCHAR>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_FString_v<T>>>
							{	public: using type = std::remove_const_t<T>;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_FStringView<type>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_FString_v<T>>>
							{	public:	using type = std::remove_const_t<T>;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_FStringView<type>(_s, tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_FString_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const FString& _object)					{ return _ue4_size_of_FStringView(_object); }
							};

//-----------------------------------------------------------------------------
// 2) ue4 - FStringView
//-----------------------------------------------------------------------------
template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_FStringView_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const FStringView& _data){ return _ue4_prepend_FStringView<B>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, FStringView&& _data)		{ return _ue4_prepend_FStringView<B>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_FStringView_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const FStringView& _data){ return _ue4_append_FStringView<B>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, FStringView&& _data)		{ return _ue4_append_FStringView<B>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_FStringView_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_FStringView<type>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_FStringView_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_FStringView<type>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_FStringView_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const FStringView& _object)				{ return _ue4_size_of_FStringView(_object); }
							};

//-----------------------------------------------------------------------------
// 3) ue4 - TArray
//-----------------------------------------------------------------------------
template<class S, class TELEMENT>
constexpr std::enable_if_t<is_memcopy_able<TELEMENT>::value, _buffer_view<typename S::element_t>>
_ue4_prepend_TArray(S& _s, const TArray<TELEMENT>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get num
	auto count = _object.Num();

	// check) count가 0이하면 안된다.
	CGDK_ASSERT(count >= 0, throw std::invalid_argument("Num() is invalid [0]"));

	// 1)
	auto buf_old = _object.data();

	// 2) [데이터_갯수]만큼 데이터들을 통채로 복사한다.
	_s.template _prepend_bytes(sizeof(TELEMENT) * _object.Size(), &_object[0]);

	// 3) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_object.data(), count * sizeof(TELEMENT));
}
template <class S, class TELEMENT>
constexpr std::enable_if_t<!is_memcopy_able<TELEMENT>::value, _buffer_view<typename S::element_t>>
_ue4_prepend_TArray(S& _s, const TArray<TELEMENT>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1)
	auto buf_old = _object.data();
	auto count = _object.Num();

	// 2) [데이터_갯수]만큼 데이터들을 추가한다.
	for (int i = (count - 1); i >= 0; --i)
	{
		_s.template _prepend<TELEMENT>(_object[i]);
	}

	// 3) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_object.data(), buf_old - _object.data());
}
template <class S, class TELEMENT>
constexpr std::enable_if_t<!is_memcopy_able<TELEMENT>::value, _buffer_view<typename S::element_t>>
_ue4_append_TArray(S& _s, const TArray<TELEMENT>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() + _s.size_ + sizeof(TELEMENT) * count) <= _s.get_upper_bound());

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 3) [데이터]들을 추가한다.
	for (std::size_t i = 0; i < count; ++i)
	{
		_s.template _append<TELEMENT>(_object[i]);
	}

	// return)
	return RET_T(_object.data() + len_old, _s.size() - len_old);
}
template <class S, class TELEMENT>
constexpr std::enable_if_t<is_memcopy_able<TELEMENT>::value, _buffer_view<typename S::element_t>>
_ue4_append_TArray(S& _s, const TArray<TELEMENT>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// 1) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 2) [데이터]들을 통채로 복사한다.
	return _s._append_bytes(count * sizeof(TELEMENT), _object.GetData());
}

template<class S, class T, class TELEMENT>
constexpr std::enable_if_t<!is_memcopy_able<TELEMENT>::value, T>
_ue4_extract_TArray(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		for (COUNT_T i = 0; i < size_data; ++i)
		{
			result[i] = _s.template _extract<TELEMENT>();
		}
	}

	// return) 
	return result;
}

template<class S, class T, class TELEMENT>
constexpr std::enable_if_t<is_memcopy_able<TELEMENT>::value, T>
_ue4_extract_TArray(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) reserve
	result.Reserve(size_data);

	// 3) memcpy 
	if (size_data != COUNT_T(-1))
	{
		if (size_data > 0)
		{
			memcpy(result.GetData(), _s.data(), size_data * sizeof(TELEMENT));
		}
	}

	// return) 
	return result;
}

template<class T>
size_t _ue4_size_of_TArray(const T& _object)
{
	std::size_t size = sizeof(COUNT_T);
	
	for (const auto& iter : _object)
		size += get_size_of(iter);
	
	return size;
}

template<class B, class T>
							class serializer_prepend<B, T, std::enable_if_t<is_ue4_TArray_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TArray<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TArray<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T>
							class serializer_append<B, T, std::enable_if_t<is_ue4_TArray_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TArray<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TArray<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T>
							class serializer_extract<B, T, std::enable_if_t<is_ue4_TArray_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TArray<S, TX, typename TX::ElementType>(_s); }
							};
template<class B, class T>
							class serializer_peek<B, T, std::enable_if_t<is_ue4_TArray_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TArray<S, TX, typename T::ElementType>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>
							class serializer_size_of<T, std::enable_if_t<is_ue4_TArray_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 4) ue4 - TStaticArray (TStaticArray, TShaderResourceParameterArray)
//-----------------------------------------------------------------------------
template<class S, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<is_memcopy_able<A1>::value, _buffer_view<typename S::element_t>>
_ue4_prepend_TStaticArray(S& _s, const TStaticArray<A1, A2, A3>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// check) count가 0이하면 안된다.
	CGDK_ASSERT(count >= 0, throw std::invalid_argument("count is invalid [0]"));

	// 1)
	auto buf_old = _object.data();

	// 2) [데이터_갯수]만큼 데이터들을 통채로 복사한다.
	_s.template _prepend_bytes(sizeof(A1) * count, _object.GetData());

	// 3) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_object.data(), buf_old - _object.data());
}
template <class S, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<!is_memcopy_able<A1>::value, _buffer_view<typename S::element_t>>
_ue4_prepend_TStaticArray(S& _s, const TStaticArray<A1, A2, A3>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// 2)
	auto buf_old = _object.data();

	// 3) [데이터_갯수]만큼 데이터들을 추가한다.
	for (int i = static_cast<int>(count - 1); i >= 0; --i)
	{
		_s.template _prepend<A1>(_object[i]);
	}

	// 4) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_object.data(), buf_old - _object.data());
}
template <class S, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<!is_memcopy_able<A1>::value, _buffer_view<typename S::element_t>>
_ue4_append_TStaticArray(S& _s, const TStaticArray<A1, A2, A3>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() + _s.size() + sizeof(A1) * count) <= _s.get_upper_bound());

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 3) [데이터]들을 추가한다.
	for (auto i = 0; i < count; ++i)
	{
		_s.template _append<A1>(_object[i]);
	}

	// return)
	return RET_T(_object.data() + len_old, _s.size() - len_old);
}
template <class S, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<is_memcopy_able<A1>::value, _buffer_view<typename S::element_t>>
_ue4_append_TStaticArray(S& _s, const TStaticArray<A1, A2, A3>& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get count
	auto count = _object.Num();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 3) [데이터]들을 통채로 복사한다.
	return _s._append_bytes(count * sizeof(A1), _object.GetData());
}

template<class S, class T, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<!is_memcopy_able<A1>::value, T>
_ue4_extract_TStaticArray(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// check) [데이터_갯수]가 배열의 수보다 커서는 안됀다.
	if (size_data > A2)
		throw std::length_error("overflow array size");

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		for (COUNT_T i = 0; i < size_data; ++i)
		{
			result[i] = _s.template _extract<A1>();
		}
	}

	// return) 
	return result;
}

template<class S, class T, class A1, uint32 A2, uint32 A3>
constexpr std::enable_if_t<is_memcopy_able<A1>::value, T>
_ue4_extract_TStaticArray(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// check) [데이터_갯수]가 배열의 수보다 커서는 안됀다.
	if (size_data > A2)
		throw std::length_error("overflow array size");

	// 2) memcpy 
	if (size_data != COUNT_T(-1))
	{
		if (size_data > 0)
		{
			memcpy(result.GetData(), _s.data(), size_data * sizeof(A1));
		}
	}

	// return)
	return result;
}

template<class B, class A1, uint32 A2, uint32 A3> class serializer_prepend<B, TStaticArray<A1, A2, A3>>
							{	public:
								using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const TStaticArray<A1, A2, A3>& _data)	{ return _ue4_prepend_TStaticArray<S, A1, A2, A3>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, TStaticArray<A1, A2, A3>&& _data)		{ return _ue4_prepend_TStaticArray<S, A1, A2, A3>(_s, _data);}
							};
template<class B, class A1, uint32 A2, uint32 A3> class serializer_append<B, TStaticArray<A1, A2, A3>>
							{	public:
								using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const TStaticArray<A1, A2, A3>& _data)	{ return _ue4_append_TStaticArray<S, A1, A2, A3>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, TStaticArray<A1, A2, A3>&& _data)		{ return _ue4_append_TStaticArray<S, A1, A2, A3>(_s, _data);}
							};
template<class B, class A1, uint32 A2, uint32 A3> class serializer_extract<B, TStaticArray<A1, A2, A3>>
							{	
								public: using type = TStaticArray<A1, A2, A3>;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TStaticArray<S, TStaticArray<A1, A2, A3>, A1, A2, A3>(_s); }
							};
template<class B, class A1, uint32 A2, uint32 A3> class serializer_peek<B, TStaticArray<A1, A2, A3>>
							{	
								public: using type = TStaticArray<A1, A2, A3>;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TStaticArray<S, TStaticArray<A1, A2, A3>, A1, A2, A3>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class A1, uint32 A2, uint32 A3> class serializer_size_of<TStaticArray<A1, A2, A3>>
							{	public:
								constexpr static std::size_t  _do(const TStaticArray<A1, A2, A3>& _object)	{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 5) ue4 - TArray (TSparseArray)
//-----------------------------------------------------------------------------
template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TSparseArray_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TArray<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TArray<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TSparseArray_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TArray<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TArray<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TSparseArray_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TArray<S, typename T::ElementType>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TSparseArray_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TArray<S, typename T::ElementType>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TSparseArray_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 6) ue4 - TList (singly linked list - TList)
//-----------------------------------------------------------------------------
template<class S, class T>
_buffer_view<typename S::element_t> _ue4_prepend_TList(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get number
	auto count = _object.Num();

	// 2)
	auto buf_old = _object.data();

	// 3) [데이터]들을 추가한다.
	for (auto& iter : _object)
	{
		_s.template _append<T::ElementType>(iter);
	}

	// 4) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_object.data(), buf_old - _object.data());
}

template<class S, class T>
_buffer_view<typename S::element_t> _ue4_append_TList(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get number
	auto count = _object.Num();

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() + _s.size() + sizeof(T) * count) <= _s.get_upper_bound());

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 3) [데이터]들을 추가한다.
	for (auto& iter : _object)
	{
		_s.template _append<T::ElementType>(iter);
	}

	// return)
	return RET_T(_object.data() + len_old, _s.size() - len_old);
}

template<class S, class T, class TELEMENT>
T _ue4_extract_TList(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		for (COUNT_T i = 0; i < size_data; ++i)
		{
			result[i] = _s.template _extract<TELEMENT>();
		}
	}

	// return) 
	return result;
}

template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TList_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TList<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TList<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TList_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TList<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TList<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TList_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TList<S, T, typename T::ElementType>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TList_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TList<S, T, typename T::ElementType>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TList_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 7) ue4 - TLinkedListBase (doubly linked list - TLinkedList, TIntrusiveLinkedList, TLinkedList)
//-----------------------------------------------------------------------------
template<class S, class T>
_buffer_view<typename S::element_t> _ue4_prepend_TLinkedListBase(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) count
	auto count = _object.Num();

	// 2)
	auto buf_old = _s.data();

	// 3) [데이터_갯수]만큼 데이터들을 추가한다.
	for (int i = static_cast<int>(count - 1); i >= 0; --i)
	{
		_s.template _prepend<T>(_object[i]);
	}

	// 4) [데이터_갯수]를 써넣는다.
	_s.template _prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_s.data(), buf_old - _object.data());
}

template<class S, class T>
_buffer_view<typename S::element_t> _ue4_append_TLinkedListBase(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1)
	auto count = _object.Num();

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() + _s.size() + sizeof(T) * count) <= _s.get_upper_bound());

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 3) [데이터]들을 추가한다.
	for (std::size_t i = 0; i < count; ++i)
	{
		_s.template _append<T>(_object[i]);
	}

	// return)
	return RET_T(_s.data() + len_old, _s.size() - len_old);
}

template<class S, class T>
T _ue4_extract_TLinkedListBase(S& _s)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		// - first 
		result = _s.template _extract<T::ElementType>();

		// - others
		for (COUNT_T i = 1; i < size_data; ++i)
		{
			result.LinkAfter(new T(_s.template _extract<T::ElementType>()));
		}
	}

	// return) 
	return result;
}

template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TLinkedListBase_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TLinkedListBase<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TLinkedListBase<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TLinkedListBase_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TLinkedListBase<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TLinkedListBase<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TLinkedListBase_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TLinkedListBase<S, typename T::ElementType>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TLinkedListBase_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TLinkedListBase<S, typename T::ElementType>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TLinkedListBase_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 8) ue4 - TSet (set - TSet, 	FTouchKeySet)
//-----------------------------------------------------------------------------
template<class S, class T>
_buffer_view<typename S::element_t> _ue4_prepend_TSet(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get number of data
	auto count = _object.Num();

	// 2)
	auto buf_old = _object.data();

	//// 3) [데이터_갯수]만큼 데이터들을 추가한다.
	//for (int i = static_cast<int>(count - 1); i >= 0; --i)
	//{
	//	_s.template _prepend<T>(_object[i]);
	//}

	//// 4) [데이터_갯수]를 써넣는다.
	//_prepend<COUNT_T>(static_cast<COUNT_T>(count));

	// return) 
	return RET_T(_s.data(), buf_old - _s.data());
}

template<class S, class T>
_buffer_view<typename S::element_t> _ue4_append_TSet(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) get number of data
	auto count = _object.Num();

	// check) upper bound
	_CGD_BUFFER_BOUND_CHECK((_s.data() + _s.size() + sizeof(T) * count) <= _s.get_upper_bound());

	// 2) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 3) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(count));

	// 4) [데이터]들을 추가한다.
	for (auto& iter : _object)
	{
		_s.template _append(iter);
	}

	// return)
	return RET_T(_s.data() + len_old, _s.size() - len_old);
}

template<class S, class T>
T _ue4_extract_TSet(S& _s)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		// - first 
		result = _s.template _extract<T::ElementType>();

		// - others
		for (COUNT_T i = 1; i < size_data; ++i)
		{
			result.Add(_s.template _extract<T::ElementType>());
		}
	}

	// return) 
	return result;
}



template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TSet_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TSet<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TSet<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TSet_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TSet<S, typename T::ElementType>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TSet<S, typename T::ElementType>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TSet_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TSet<S, typename T::ElementType>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TSet_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TSet<S, typename T::ElementType>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TSet_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TArray(_object); }
							};

//-----------------------------------------------------------------------------
// 9) ue4 - TMapBase (map - TSortableMapBase, TMap, TMultiMap)
//-----------------------------------------------------------------------------
template<class S, class T>
_buffer_view<typename S::element_t> _ue4_prepend_TMap(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1)
	auto buf_old = _object.data();

	//// 2) [데이터_갯수]만큼 데이터들을 추가한다.
	//for (auto& iter : _object)
	//{
	//	_prepend<T>(iter.Value);
	//	_prepend<T>(iter.Key);
	//}

	//// 3) [데이터_갯수]를 써넣는다.
	//_prepend<COUNT_T>(static_cast<COUNT_T>(_object.Len()));

	// return) 
	return RET_T(_s.data(), buf_old - _s.data());
}

template<class S, class T>
_buffer_view<typename S::element_t> _ue4_append_TMap(S& _s, const T& _object)
{
	using RET_T = _buffer_view<typename S::element_t>;

	// 1) [원본_버퍼_포인터]를 저장해 놓는다.
	auto len_old = _s.size();

	// 2) [데이터_갯수]를 써넣는다.
	_s.template _append_general<COUNT_T>(static_cast<COUNT_T>(_object.Num()));

	// 3) [데이터]들을 추가한다.
	for (auto& iter: _object)
	{
		_s._append(iter.Key);
		_s._append(iter.Value);
	}

	// return)
	return RET_T(_s.data() + len_old, _s.size() - len_old);
}

template<class S, class T>
T _ue4_extract_TMap(S& _s)
{
	// declare) 
	T result{};

	// 1) [데이터_갯수]를 얻어낸다.
	auto size_data = _s.template _extract<COUNT_T>();

	// 2) [데이터_갯수]만큼 읽어들인다.
	if (size_data != COUNT_T(-1))
	{
		// - reserve
		result.Reserve(size_data);

		// - add
		for (auto i = 0; i < size_data; ++i)
		{
			const auto key = _s.template _extract<typename T::ElementType::KeyType>();
			const auto value = _s.template _extract<typename T::ElementType::ValueType>();

			result.Add(key, value);
		}
	}

	// return) 
	return result;
}

template<class T>
size_t _ue4_size_of_TMap(const T& _object)
{
	std::size_t size = sizeof(COUNT_T);
	
	for (const auto& iter : _object)
	{
		size += get_size_of(iter.Key());
		size += get_size_of(iter.Value());
	}
	
	return size;
}

template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TMapBase_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TMap<S, T>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TMap<S, T>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TMapBase_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TMap<S, T>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TMap<S, T>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TMapBase_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TMap<S, T>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TMapBase_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TMap<S, T>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TMapBase_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TMap(_object); }
							};

//-----------------------------------------------------------------------------
// 10) ue4 - TSortedMap (sorted map - TSortedMap, FAssetDataTagMap)
//-----------------------------------------------------------------------------
template<class B, class T> class serializer_prepend<B, T, std::enable_if_t<is_ue4_TSortedMap_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_prepend_TMap<S, T>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_prepend_TMap<S, T>(_s, _data);}
							};
template<class B, class T> class serializer_append<B, T, std::enable_if_t<is_ue4_TSortedMap_v<T>>>
							{	public: using type = _buffer_view<typename B::element_t>;
								template<class S> constexpr static type _do(S& _s, const T& _data)			{ return _ue4_append_TMap<S, T>(_s, _data);}
								template<class S> constexpr static type _do(S& _s, T&& _data)				{ return _ue4_append_TMap<S, T>(_s, _data);}
							};
template<class B, class T> class serializer_extract<B, T, std::enable_if_t<is_ue4_TSortedMap_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(S& _s)							{ return _ue4_extract_TMap<S, T>(_s); }
							};
template<class B, class T> class serializer_peek<B, T, std::enable_if_t<is_ue4_TSortedMap_v<T>>>
							{	using TX = std::remove_const_t<T>;
								public: using type = TX;
								template<class S> constexpr static type _do(const S& _s, int64_t& _offset)	{ S tb =_s + _offset; auto temp = _ue4_extract_TMap<S, T>(tb); _offset = tb.data() - _s.data(); return temp;}
							};
template<class T>		    class serializer_size_of<T, std::enable_if_t<is_ue4_TSortedMap_v<T>>>
							{	public:
								constexpr static std::size_t  _do(const T& _object)							{ return _ue4_size_of_TMap(_object); }
							};
}

#endif