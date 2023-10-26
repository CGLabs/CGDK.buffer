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
namespace std
{
	[[nodiscard]] constexpr auto begin(CGDK::buffer_view& _buf) -> decltype(_buf.get_front_ptr()) { return _buf.get_front_ptr(); }
	[[nodiscard]] constexpr auto cbegin(const CGDK::buffer_view& _buf) -> decltype(_buf.get_front_ptr()) { return _buf.get_front_ptr(); }
	[[nodiscard]] constexpr auto rbegin(CGDK::buffer_view& _buf) -> decltype(_buf.get_back_ptr()) { return _buf.get_back_ptr(); }
	[[nodiscard]] constexpr auto crbegin(const CGDK::buffer_view& _buf) -> decltype(_buf.get_back_ptr()) { return _buf.get_back_ptr(); }
	[[nodiscard]] constexpr auto end(CGDK::buffer_view& _buf) -> decltype(_buf.get_back_ptr()) { return _buf.get_back_ptr(); }
	[[nodiscard]] constexpr auto cend(const CGDK::buffer_view& _buf) -> decltype(_buf.get_back_ptr()) { return _buf.get_back_ptr(); }
	[[nodiscard]] constexpr auto rend(CGDK::buffer_view& _buf) -> decltype(_buf.get_front_ptr()) { return _buf.get_front_ptr(); }
	[[nodiscard]] constexpr auto crend(const CGDK::buffer_view& _buf) -> decltype(_buf.get_front_ptr()) { return _buf.get_front_ptr(); }
	[[nodiscard]] constexpr auto size(CGDK::buffer_view& _buf) -> decltype(_buf.size()) { return _buf.size(); }
	[[nodiscard]] constexpr bool empty(CGDK::buffer_view& _buf) { return _buf.size() == 0; }
}

namespace CGDK
{

template <class B, std::size_t INDEX, std::size_t IALIGN>
struct any_constructor_extract
{
	_buffer_view<typename B::element_t>& buf_source;
	
	template <class Type>
	constexpr operator Type() const 
	{
		return buf_source.template extract<std::decay_t<Type>>();
	}
};

template <class B, class T, std::size_t... I>
constexpr T extract_member_impl(_buffer_view<typename B::element_t>& _buf_source, std::index_sequence<I...>)
{
	return T{ any_constructor_extract<B, I, alignof(T)>{_buf_source}... };
}

template <class B, class T, std::size_t... I>
constexpr void extract_member_impl(T& _dest, _buffer_view<typename B::element_t>& _buf_source, std::index_sequence<I...>)
{
	_dest = T{ any_constructor_extract<B, I, alignof(T)>{_buf_source}... };
}

template<class B, class T>
class serializer_extract<B, T, std::enable_if_t<is_struct_serializable_v<T>>>
{
public:	using type = T;
	template<class S>
	constexpr static type _do_extract(S& _source)
	{
		// check)
		static_assert(!std::is_base_of_v<Ibuffer_serializable, T>, "''Ibuffer_serializable' class has priority");

		// check)
		static_assert(!std::is_polymorphic<T>::value, "'struct_serializable' class must not be polymorphic (no virtual fuction)");

		// check)
		static_assert(std::is_default_constructible<T>::value, "'struct_serializable' class must have default constructor (remove construtor)");

		return extract_member_impl<B,T>(_source, std::make_index_sequence<constexpr_field_count<T>>());
	}
	template<class D, class S>
	constexpr static void _do_extract(D& _dest, S& _source)
	{
		// check)
		static_assert(!std::is_base_of_v<Ibuffer_serializable, T>, "''Ibuffer_serializable' class has priority");

		// check)
		static_assert(!std::is_polymorphic<T>::value, "'struct_serializable' class must not be polymorphic (no virtual fuction)");

		// check)
		static_assert(std::is_default_constructible<T>::value, "'struct_serializable' class must have default constructor (remove construtor)");

		extract_member_impl<B,T>(_dest, _source, std::make_index_sequence<constexpr_field_count<T>>());
	}
};

template <class B>
struct _Sfromt_member_auto_close
{
	constexpr _Sfromt_member_auto_close(const _buffer_view<typename B::element_t>& _source,  int64_t& _offset) noexcept :
		buf_extract(_source + CGDK::offset(_offset)),
		buf_source(_source.data()),
		offset(_offset)
	{}
	~_Sfromt_member_auto_close() noexcept { offset = buf_extract.template data<const char>() - buf_source;}

	_buffer_view<typename B::element_t> buf_extract;
	const char*	buf_source;
	int64_t& offset;
};

template <class B, class T, std::size_t... I>
constexpr T front_member_impl(_Sfromt_member_auto_close<B> _source, std::index_sequence<I...>)
{
	return T{ any_constructor_extract<B, I, alignof(T)>{_source.buf_extract}... };
}

template <class B, class T, std::size_t... I>
constexpr void front_member_impl(T& _dest, _Sfromt_member_auto_close<B> _source, std::index_sequence<I...>)
{
	_dest = T{ any_constructor_extract<B, I, alignof(T)>{_source.buf_extract}... };
}

template <std::size_t INDEX, std::size_t IALIGN>
struct member_size_of
{
	const char* source;
	std::size_t& offset;
	std::size_t& size_object;

	template <class Type>
	constexpr operator Type () const noexcept
	{
		// 1) pre-offset
		offset = align_offset_pre<IALIGN>(offset, sizeof(Type));

		// 2) get get_size_of source
		size_object += get_size_of<std::size_t, std::decay_t<Type>>(*reinterpret_cast<const Type*>(source + offset));

		// 3) add offset
		offset += sizeof(Type);

		// return) 
		return Type();
	}
};

// 5) for structure (reflection)
template <class T, std::size_t... I>
constexpr std::size_t size_of_member_impl(const char* _source, std::index_sequence<I...>)
{
	std::size_t offset = 0;
	std::size_t	size_object = 0;
	T{ member_size_of<I, alignof(T)>{_source, offset, size_object}... };
	return size_object;
}


template<class B, class T>
class serializer_peek<B, T, std::enable_if_t<is_struct_serializable_v<T>>>
{	
public:	using type = T;
	template<class S> 
	constexpr static type _do_peek(const S& _source, int64_t& _offset)
	{
		// check) T must be default construcable
		static_assert(std::is_default_constructible<T>::value, "T must be default constructable");

		// check) 'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute
		static_assert(!std::is_base_of_v<Ibuffer_serializable, T>, "'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute");

		// check) T must have 'is_struct_serializable' attribute
		static_assert(is_struct_serializable_v<T>, "T must derive 'is_struct_serializable' class");

		// check) T must be 'is_default_constructible_v<T>' attribute
		static_assert(std::is_default_constructible_v<T>, "'is_struct_serializable' class must have default constructor (remove construtor)");

		// return) front member
		return front_member_impl<B, T>(_Sfromt_member_auto_close<S>(_source, _offset), std::make_index_sequence<constexpr_field_count<T>>());
	}
	template<class D, class S>
	constexpr static void _do_peek(D& _dest, const S& _source, int64_t& _offset)
	{
		// check) T must be default construcable
		static_assert(std::is_default_constructible<T>::value, "T must be default constructable");

		// check) 'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute
		static_assert(!std::is_base_of_v<Ibuffer_serializable, T>, "'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute");

		// check) T must have 'is_struct_serializable' attribute
		static_assert(is_struct_serializable_v<T>, "T must derive 'is_struct_serializable' class");

		// check) T must be 'is_default_constructible_v<T>' attribute
		static_assert(std::is_default_constructible_v<T>, "'is_struct_serializable' class must have default constructor (remove construtor)");

		// return) front member
		front_member_impl<B, T>(_dest, _Sfromt_member_auto_close<S>(_source, _offset), std::make_index_sequence<constexpr_field_count<T>>());
	}
};
template<class T>
class serializer_size_of<T, std::enable_if_t<is_struct_serializable_v<T>>>
{
public:
	constexpr static std::size_t  _get_append_size(const T& _object)
	{
		// check) T must be default construcable
		static_assert(std::is_default_constructible<T>::value, "T must be default constructable");

		// check) 'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute
		static_assert(!std::is_base_of_v<Ibuffer_serializable, T>, "'Ibuffer_serializable' attribue is priorier than 'struct_serializable' attribute");

		// check) T must derive 'is_struct_serializable_v'
		static_assert(is_struct_serializable_v<T>, "T must defined 'ENABLE_STRUCT_SERIALIZABLE'");

		// check) T must be 'std::is_default_constructable_v<T>' attribute
		static_assert(std::is_default_constructible_v<T>, "'struct_serializable' attribute must have default constructor (remove construtor)");

		// 1) get size 0f mebsers
		return size_of_member_impl<T>(reinterpret_cast<const char*>(&_object), std::make_index_sequence<constexpr_field_count<T>>());
	}
	template<class S> 
	constexpr static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset)
	{
		CGDK_ASSERT(false);
		return 0;
	}
};


}