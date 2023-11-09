//*****************************************************************************
//*                                                                           *
//*                                CGDK.buffer                                *
//*                        Ver 3.0 / Release 2022.07.10                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@cgcii.co.kr        *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                    (C) 2008 CGLabs All right reserved.                    *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
#define _USE_INLINE_PRIMITIVE_FUNCTION

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;


//----------------------------------------------------------------------------
//  CGDK.CGMemoryClasses
//
//  class CGDK.buffer
//
//
//
//
//----------------------------------------------------------------------------
namespace CGDK
{

namespace Attribute
{
	public class Serializable : System.Attribute
	{
		public Serializable()
		{
		}
	}
}
	
namespace Exception
{
	public class Serialize : System.Exception
	{
		public Serialize(long _offset)
		{
			m_Offset=_offset;
		}
		public Serialize(long _offset, string _message) : base(_message)
		{
			m_Offset=_offset;
		}

		public long Offset	{ get {return m_Offset;}}

		private long m_Offset;
	}
}


public struct buffer
{
// constructor/destructor) 
	public buffer(byte[] _buffer, int _offset = 0, int _count = 0)
	{
		m_buffer = _buffer;
		m_offset = _offset;
		m_count = _count;
	}
	public buffer(buffer _buffer)
	{
		m_buffer	 = _buffer.m_buffer;
		m_offset	 = _buffer.m_offset;
		m_count	 = _buffer.m_count;
	}
	public buffer(int _Size)
	{
		m_buffer = new byte[_Size];
		m_offset = 0;
		m_count = 0;
	}

	public buffer clone()
	{
		// 1) 새로운 버퍼를 생성한다.
		byte[]	temp = new byte[capacity];

		// 2) [문자열]을 복사해 넣는다.
		System.Buffer.BlockCopy(m_buffer, 0, temp, 0, capacity);

		// 3) 적용한다.
		return	new buffer(temp, m_offset, m_count);
	}

// definitions) 
	public const uint	SIZE_OF_CRC	 = sizeof(uint);

	private static bool _is_serializable_type(Type _type)
	{
		if(_type.IsSerializable==true)
			return	true;

		return _type.GetCustomAttributes(typeof(CGDK.Attribute.Serializable), false).Length != 0;
	}


// publics) 
// 1) 생성/버퍼설정
	public void		alloc(int _Size)
	{
		m_buffer	 = new byte[_Size];
		m_offset	 = 0;
		m_count	 = 0;
	}
	public void		set_buffer(byte[] _buffer, int _offset, int _length)
	{
		// Check) _offset+_length가 _buffer의 크기보다 크면 안됀다.
		Debug.Assert((_offset+_length) <= _buffer.Length);

		// Check) _offset이나 _length의 길이가 _buffer의 크기를 초과할 경우 Exception을 던진다.
		if ((_offset+_length) > _buffer.Length)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) 값을 적용
		m_buffer	 = _buffer;
		m_offset	 = _offset;
		m_count	 = _length;
	}
	public void		set_buffer(byte[] _buffer, int _offset)
	{
		// Check) _offset+_length가 _buffer의 크기보다 크면 안됀다.
		Debug.Assert(_offset <= _buffer.Length);

		// Check) _offset이나 _length의 길이가 _buffer의 크기를 초과할 경우 Exception을 던진다.
		if (_offset>_buffer.Length)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) 값을 적용한다.
		m_buffer = _buffer;
		m_offset = _offset;
		m_count = _buffer.Length-_offset;
	}
	public byte[]	clear()
	{
		// 1) 임시로 보관
		byte[]	temp = m_buffer;

		// 2) Reset한다.
		m_buffer = null;
		m_offset = 0;
		m_count = 0;

		// 3) 저장되어 있던 byte[]를 리턴해 준다.
		return temp;
	}

// 2) Basic operations
	public bool		empty()														{ return m_buffer==null;}
	public int		get_remained()												{ return m_buffer.Length - m_offset - m_count; }

	public int		capacity
	{
			get { return m_buffer.Length; }
	}

	// - for C++ User
	public byte[]	data														{	get { return m_buffer;} set { m_buffer = value;}}
	public int		offset														{	get { return m_offset;}	set { m_offset = value;}}
	public int		size														{	get { return m_count;} set {m_count = value;}}

	// - for C# User
	public byte[]	Buffer														{	get { return m_buffer; } set { m_buffer = value; } }
	public byte[]	Array														{	get { return m_buffer; } set { m_buffer = value; } }
	public int		Offset														{	get { return m_offset;}	set { m_offset = value;}}
	public int		Count														{	get { return m_count;} set { m_count = value;}}

	public static buffer operator +(buffer _lhs, int _rhs)						{ return new buffer(_lhs.Array, _lhs.Offset+_rhs, _lhs.Count-_rhs);}
	public static buffer operator -(buffer _lhs, int _rhs)						{ return new buffer(_lhs.Array, _lhs.Offset - _rhs, _lhs.Count + _rhs); }
	public static buffer operator ^(buffer _lhs, int _rhs)						{ return new buffer(_lhs.Array, _lhs.Offset, _rhs);}
	public static implicit operator ArraySegment<byte>(buffer _rhs)				{ return new ArraySegment<byte>(_rhs.Array, _rhs.Offset, _rhs.Count);}
	public static explicit operator buffer(ArraySegment<byte> _rhs)				{ return new buffer(_rhs.Array, _rhs.Offset, _rhs.Count);}

// 3) append(붙이기)
	public void		append_skip				(int _amount)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=_amount);	m_count += _amount; }
	public void		append					(buffer _object)					{ _append_buffer(_object);}
	public void		append					(char _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(char));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(char); }
	public void		append					(sbyte _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(sbyte));	m_buffer[m_offset+m_count]=(byte)_object; m_count+=sizeof(sbyte); }
	public void		append					(byte _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(byte));	m_buffer[m_offset + m_count] = _object; m_count += sizeof(byte); }
	public void		append					(short _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(short));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(short); }
	public void		append					(ushort _object)					{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(ushort));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(ushort); }
	public void		append					(int _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(int));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(int); }
	public void		append					(uint _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(uint));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(uint); }
	public void		append					(long _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(long));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(long); }
	public void		append					(ulong _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(ulong));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(ulong); }
	public void		append					(float _object)						{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(float));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(float); }
	public void		append					(double _object)					{ Debug.Assert((m_buffer.Length-m_offset-m_count)>=sizeof(double));	BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + m_count); m_count += sizeof(double); }
	public void		append					(DateTime _object)					{ this.append<long>(_object.Ticks);	}

	public void		append<T>()													{ this.append<T>(default(T));}
	public void		append<T>				(char _object) where T:struct		{ if(typeof(T)==typeof(char))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(sbyte _object) where T:struct		{ if(typeof(T)==typeof(sbyte))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(byte _object) where T:struct		{ if(typeof(T)==typeof(byte))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(short _object) where T:struct		{ if(typeof(T)==typeof(short))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(ushort _object) where T:struct		{ if(typeof(T)==typeof(ushort))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(int _object) where T:struct		{ if(typeof(T)==typeof(int))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(uint _object) where T:struct		{ if(typeof(T)==typeof(uint))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(long _object) where T:struct		{ if(typeof(T)==typeof(long))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(ulong _object) where T:struct		{ if(typeof(T)==typeof(ulong))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(float _object) where T:struct		{ if(typeof(T)==typeof(float))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	public void		append<T>				(double _object) where T:struct		{ if(typeof(T)==typeof(double))	{ append(_object);} else { this.append((T)Convert.ChangeType(_object, typeof(T)));}}
	//public void		append<T>				(char _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(char));	append(_object);}
	//public void		append<T>				(sbyte _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(sbyte));	append(_object);}
	//public void		append<T>				(byte _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(byte));	append(_object);}
	//public void		append<T>				(short _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(short));	append(_object);}
	//public void		append<T>				(ushort _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(ushort));append(_object);}
	//public void		append<T>				(int _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(int));	append(_object);}
	//public void		append<T>				(uint _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(uint));	append(_object);}
	//public void		append<T>				(long _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(long));	append(_object);}
	//public void		append<T>				(ulong _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(ulong));	append(_object);}
	//public void		append<T>				(float _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(float));	append(_object);}
	//public void		append<T>				(double _object) where T:struct		{ Debug.Assert(typeof(T) == typeof(double));append(_object);}


	public void		append<T>				(string _object)
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long Offset = m_offset + m_count;

		try
		{
			// 3) 추가한다.
			_append<string>(ptr, ref Offset, _object);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_count	 = (int)Offset;
		}
		catch (System.Exception _e)
		{
			// Trace) 
			Debug.WriteLine("CGDK.buffer extract<T>(ICollection<string>): " + _e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}

	public void		append<T>				(object _object)
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long Offset = m_offset + m_count;

		try
		{
			Type tmp = _object.GetType();
                
			if (tmp.IsPrimitive)
			{
				Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)");

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				Marshal.StructureToPtr(_object, new IntPtr(ptr + Offset), false);
				Offset += Marshal.SizeOf(tmp);
			#else
				_append_Primitive(ptr, ref Offset, _object);
			#endif
			}
			else if (tmp.IsEnum)
			{
				var	type_enum = tmp.GetFields()[0].FieldType;

				Marshal.StructureToPtr(Convert.ChangeType(_object, type_enum), new IntPtr(ptr + Offset), false);

				Offset += Marshal.SizeOf(type_enum);
			}
			else if (tmp.IsValueType)
			{
				if(typeof(DateTime).Equals(tmp))
				{
					_append_datetime(ptr, ref Offset, _object);
				}
				else if(typeof(CGDK.buffer).Equals(tmp))
				{
					_append_buffer(ptr, ref Offset, (buffer)_object);
				}
				else
				{
					_append_value(ptr, ref Offset, _object);
				}
			}
			else if (tmp.IsArray)
			{
				_append_Collection(ptr, ref Offset, _object as System.Collections.ICollection, _object.GetType().GetElementType());
			}
			else if (typeof(string).Equals(tmp))
			{
				_append<string>(ptr, ref Offset, _object as string);
			}
			else
			{
				System.Collections.IDictionary temp_object = _object as System.Collections.IDictionary;
				if (temp_object != null)
				{
					_append_Dictionary(ptr, ref Offset, temp_object, tmp.GetGenericArguments());
				}
				else
				{
					System.Collections.ICollection tempObject2 = _object as System.Collections.ICollection;

					if (tempObject2 != null)
					{
						_append_Collection(ptr, ref Offset, tempObject2, _object.GetType().GetGenericArguments()[0]);
						return;
					}
					else if (tmp.IsClass)
					{
						_append_class(ptr, ref Offset, _object);
					}
					else
					{
						_append_value(ptr, ref Offset, _object);
					}
				}
			}

			// 5) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_count	 = (int)Offset;
		}
		catch (System.Exception _e)
		{
			// Trace) 
			Debug.WriteLine("CGDK.buffer extract<T>(ICollection<string>): " + _e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}
	public void		append					(object _object)
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long Offset = m_offset + m_count;

		try
		{
			// Check) null 일 경우 -1만 쓰고 끝냄
			if (_object == null)
			{
				append((short)-1);
				return;
			}

			// 3) 추가한다.
			_append(ptr, ref Offset, _object);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_count = (int)Offset;
		}
		catch (System.Exception _e)
		{
			// Trace) 
			Debug.WriteLine("CGDK.buffer extract<T>(ICollection<string>): " + _e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}

	public void		append					(byte[] _buffer, int _offset, int _count)
	{
		Debug.Assert((m_buffer.Length - m_offset - m_count) >= _count);

		System.Buffer.BlockCopy(_buffer, _offset, m_buffer, m_offset + m_count, _count);

		m_count += _count; 
	}

	public void		append_text				(string _object)
	{
		// 1) 문자열을 배열로 변경하고 길이를 구한다.
		var temp_array = _object.ToCharArray();
		var iStringLength = temp_array.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert((m_offset + m_count + iStringLength * sizeof(char)) <= m_buffer.Length);

		// 2) [문자열]을 복사해 넣는다.
		System.Buffer.BlockCopy(temp_array, 0, m_buffer, m_offset + m_count, iStringLength * sizeof(char));

		// 3) [버퍼_길이]를 더해준다.
		m_count += (iStringLength * sizeof(char));
	}
	public void		append_text				(ICollection<string> _Collection)
	{
		// 2) 데이터들을 저장한다.
		foreach (var iter in _Collection)
		{
			append_text(iter);
		}
	}
	public void		append_text				(params string[] _Array)
	{
		foreach (var iter in _Array)
		{
			append_text(iter);
		}
	}
	public void		append_CRC				()
	{
		//_append<uint>(0);
		m_count	+= sizeof(uint);
	}

	private void	_append_buffer			(buffer _object)
	{
		Debug.Assert((m_buffer.Length - m_offset - m_count) >= _object.m_count);
		
		append<UInt32>((UInt32)_object.size);

		System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, m_buffer, m_offset + m_count, _object.m_count); 
		
		m_count += _object.m_count; 
	}

	private void	_append_buffer			(long _ptr, ref long _offset, buffer _object)
	{
		Debug.Assert((m_buffer.Length - m_offset - m_count) >= sizeof(UInt32)+_object.m_count);

	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr(_object.size, new IntPtr(_ptr + _offset), false); _offset += sizeof(UInt32);
	#else
		_append<UInt32>(_ptr, ref _offset, _object.len);
	#endif

		System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, m_buffer, (int)_offset, _object.size); _offset+=_object.m_count; 
	}

	private void	_append<T>				(long _ptr, ref long _offset, T _object) where T:struct
	{
	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr(_object, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(typeof(T));
	#else
		_append_Primitive(_ptr, ref _offset, _object);
	#endif
	}
	private void	_append<T>				(long _ptr,ref long _offset,string _object) 
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
			_offset += sizeof(short);
			return;
		}

		// 1) [문자열]을 [문자배열]로 변경하고 길이를 구한다.
		var temp_array = _object.ToCharArray();
		var	iStringLength = temp_array.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert((_offset+sizeof(short)+iStringLength*sizeof(char))<=m_buffer.Length);

		// 2) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
		Marshal.StructureToPtr((short)(iStringLength+1), new IntPtr(_ptr+_offset), false);

		// 3) [문자열]을 복사해 넣는다.
		System.Buffer.BlockCopy(temp_array, 0, m_buffer, (int)_offset+sizeof(short), iStringLength*sizeof(char));

		// 4) [버퍼_길이]를 더해준다. (NULL문자열의 길이까지 포함한다.)
		_offset	+= (sizeof(short)+(iStringLength+1)*sizeof(char));

		// 5) [NULL]을 넣는다.
		Marshal.StructureToPtr((short)0, new IntPtr(_ptr+_offset-sizeof(char)), false);
	}
	private void	_append<T>				(long _ptr, ref long _offset, params string[] _Array)
	{
		foreach (var iter in _Array)
		{
			_append<string>(_ptr, ref _offset, iter);
		}
	}
	private void	_append					(long _ptr, ref long _offset, object _object)
	{
		// 1) Type을 읽는다.
		Type temp_type = _object.GetType();

		if (temp_type.IsPrimitive)
		{
		#if _USE_INLINE_PRIMITIVE_FUNCTION
			Marshal.StructureToPtr(_object, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(temp_type);
		#else
			_append_Primitive(_ptr, ref _offset, _object);
		#endif
		}
		else if(temp_type.IsEnum)
		{
			var	type_enum = temp_type.GetFields()[0].FieldType;

			Marshal.StructureToPtr(Convert.ChangeType(_object, type_enum), new IntPtr(_ptr + _offset), false);

			_offset += Marshal.SizeOf(type_enum);
		}
		else if (temp_type.IsValueType)
		{
			if(typeof(DateTime).Equals(temp_type))
			{
				_append_datetime(_ptr, ref _offset, _object);
			}
			else if(typeof(CGDK.buffer).Equals(temp_type))
			{
				_append_buffer(_ptr, ref _offset, (buffer)_object);
			}
			else
			{
				_append_value(_ptr, ref _offset, _object);
			}
		}
		else if (temp_type.IsArray)
		{
			_append_Collection(_ptr, ref _offset, _object as System.Collections.ICollection, _object.GetType().GetElementType());
		}
		else if (typeof(string).Equals(temp_type))
		{
			_append<string>(_ptr, ref _offset, _object as string);
		}
		else 
		{
			{
				System.Collections.IDictionary temp_object=_object as System.Collections.IDictionary;
				if (temp_object != null)
				{
					_append_Dictionary(_ptr, ref _offset, temp_object, temp_type.GetGenericArguments());
					return;
				}
			}
			{
				System.Collections.ICollection	temp_object	 = _object as System.Collections.ICollection;
				if (temp_object != null)
				{
					_append_Collection(_ptr, ref _offset, temp_object, _object.GetType().GetGenericArguments()[0]);
					return;
				}
				else if(temp_type.IsClass)
				{
					_append_class(_ptr, ref _offset, _object);
				}
				else
				{
					// Check) 지원되지 않는 Type이다.
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

					// Throw) 
					throw	new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
				}
			}
		}
	}
	private void	_append_Primitive		(long _ptr, ref long _offset, object _object)
	{
		// Check) m_iCount가 남은 크기보다 작으면 Exception을 던진다.
		if (Marshal.SizeOf(_object)+_offset > m_buffer.Length)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) [버퍼_포인터]에 [데이터]를 복사한다.
		Marshal.StructureToPtr(_object, new IntPtr(_ptr+_offset), false);	

		// 2) m_iCount의 길이를 더한다.
		_offset	 += Marshal.SizeOf(_object);
	}
	private void	_append_class			(long _ptr, ref long _offset, object _object, Type _base_type = null)
	{
        // 1) Get Type ( 재귀용 _base_type 이 존재한다면 그걸쓰고 아니라면 Data 를 쓴다.  )
		Type temp_type = _base_type != null ? _base_type : _object.GetType();

		// Check) Serializable이 아니면 리턴한다.
		if (_is_serializable_type(temp_type) == false)
			return;

        // 2) 부모의 부모가 nullptr이면 object를 제외하고 최고 부모 클래스다.
        if(temp_type.BaseType.BaseType != null)
        {
            _append_class(_ptr, ref _offset, _object, temp_type.BaseType);
        }

        // 3) 변수들을 얻는다.
		var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly);

		// 4) 최상위 부모의 맴버부터 차례대로 buffer 에 append 한다
		foreach (var iter in temp_field)
		{
			// Check) 
			if (iter.IsNotSerialized == true)
				continue;

			// Check)
			if (iter.GetCustomAttributes(typeof(CGDK.Attribute.Serializable), false) == null)
				continue;

			// declare) 
			object temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				_append(_ptr, ref _offset, temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
				_offset += sizeof(short);
			}
		}
	}
	private void	_append_value			(long _ptr, ref long _offset, object _object)
	{
		Type temp_type = _object.GetType();
		var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		foreach(var iter in temp_field)
		{
			// Check)
			if(iter.IsNotSerialized == true)
				continue;

			object temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				_append(_ptr, ref _offset, temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
				_offset += sizeof(short);
				continue;
			}
		}
	}
	public void		_append_datetime		(long _ptr, ref long _offset, DateTime _object)
	{
		_append<long>(_ptr, ref _offset, _object.Ticks);
	}

	public void		_append_datetime		(long _ptr,ref long _offset, object _object)
	{
		DateTime tempTime = (DateTime)Convert.ChangeType(_object, typeof(DateTime));
		_append<long>(_ptr, ref _offset, tempTime.Ticks);
	}

	private void	_append_Dictionary		(long _ptr,ref long _offset,System.Collections.IDictionary _object, Type[] _types) 
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
			_offset += sizeof(short);
			return;
		}

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr((short)_object.Count, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(typeof(short));
	#else
		_append_Primitive(_ptr,ref _offset,(short)_object.Count);
	#endif

		// 2) [데이터]들을 써넣는다.
		if (_types[0].IsPrimitive)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
			#endif
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			#else
				while(temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#endif
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			#endif
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			#endif
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
#endif
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
#else
				while(temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
#endif
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if(_types[0].IsEnum)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Key, _types[0].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				var size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Key,   _types[0].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			#else
				while(temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#endif
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			#endif
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			#endif
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			#endif
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			#else
				while(temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Key);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			#endif
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsValueType)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				var	size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
#if _USE_INLINE_PRIMITIVE_FUNCTION
				var	size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
#else
				while (temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_value(_ptr, ref _offset, temp_enum.Key);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsArray)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, _types[1].GetElementType());
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				 var temp_type_0 = _types[0].GetElementType();
				 var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (typeof(string).Equals(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				 var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append<string>(_ptr, ref _offset, temp_enum.Key as string);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsClass && _is_serializable_type(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			#else
				while (temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				var size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;

				}
			#else
				while (temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_Primitive(_ptr, ref _offset, temp_enum.Value);
				}
			#endif
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_value(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					_append_class(_ptr, ref _offset, temp_enum.Key);
					_append_class(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}
	}
	private void	_append_Collection		(long _ptr, ref long _offset, System.Collections.ICollection _object, Type _type)
	{
		if (_type.IsArray == false)
		{
			// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
			if (_object == null)
			{
				// - -1을 쓰고 끝낸다.
				Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
				_offset += sizeof(short);
				return;
			}

			// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		#if _USE_INLINE_PRIMITIVE_FUNCTION
			Marshal.StructureToPtr((short)_object.Count, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(typeof(short));
		#else
			_append_Primitive(_ptr, ref _offset, (short)_object.Count);
		#endif

			// 3) [데이터]들을 써넣는다.
			if (_type.IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_0 = Marshal.SizeOf(_type);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Current, new IntPtr(_ptr + _offset), false); _offset += size_0;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Current);
				}
			#endif
			}
			else if (_type.IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int size_0 = Marshal.SizeOf(_type.GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Current, _type.GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;
				}
			#else
				while (temp_enum.MoveNext())
				{
					_append_Primitive(_ptr, ref _offset, temp_enum.Current);
				}
			#endif
			}
			else if (_type.IsValueType)
			{
				if(typeof(DateTime).Equals(_type))
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						_append_datetime(_ptr, ref _offset, temp_enum.Current);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_type))
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						_append_buffer(_ptr, ref _offset, (buffer)temp_enum.Current);
					}
				}
				else
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						_append_value(_ptr, ref _offset, temp_enum.Current);
					}
				}
			}
			else if (typeof(string).Equals(_type))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					_append<string>(_ptr, ref _offset, temp_enum.Current as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
			{
				var temp_type = _type.GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					_append_Dictionary(_ptr, ref _offset, temp_enum.Current as System.Collections.IDictionary, temp_type);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_type))
			{
				var tmp_type =	_type.GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					_append_Collection(_ptr, ref _offset, temp_enum.Current as System.Collections.ICollection, tmp_type);
				}
			}
			else if (_type.IsClass && _is_serializable_type(_type))
			{
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					_append_class(_ptr, ref _offset, temp_enum.Current);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else
		{
			// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
			if (_object == null)
			{
				// - -1을 쓰고 끝낸다.
				Marshal.StructureToPtr((short)-1, new IntPtr(_ptr + _offset), false);
				_offset += sizeof(short);
				return;
			}

			// - Element Type에 따라 처리...
			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				_append(_ptr, ref _offset, temp_enum.Current);
			}
		}
	}

// 5) extract관련(뽑아내기)
	public object	extract					(Type _type)
	{
		// 1) [버퍼]를 고정(Pinned) 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject()+m_offset;
		long Offset = 0;

		try
		{
			// 3) 
			var temp = _extract(ptr, ref Offset, _type, null, 0);

			// 5) [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// 6) Buffer Pointer를 증가시킨다.
			m_count -= (int)Offset;
			m_offset += (int)Offset;

			// Return)
			return temp;
		}
		catch(System.Exception _e)
		{
			// Trace) 
			Debug.WriteLine("CGDK.buffer extract<T>(): " + _e.Message);

			// - [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// Reraise)
			throw;
		}
	}

	public T		extract<T>				()
	{
		// declare) 
		Type tmp = typeof(T);

		if(tmp.IsPrimitive)
		{
				 if(tmp == typeof(char))   return (T)Convert.ChangeType(extract_char(), tmp);
			else if(tmp == typeof(sbyte))  return (T)Convert.ChangeType(extract_sbyte(), tmp);
			else if(tmp == typeof(byte))   return (T)Convert.ChangeType(extract_byte(), tmp);
			else if(tmp == typeof(short))  return (T)Convert.ChangeType(extract_short(), tmp);
			else if(tmp == typeof(ushort)) return (T)Convert.ChangeType(extract_ushort(), tmp);
			else if(tmp == typeof(int))    return (T)Convert.ChangeType(extract_int(), tmp);
			else if(tmp == typeof(uint))   return (T)Convert.ChangeType(extract_uint(), tmp);
			else if(tmp == typeof(long))   return (T)Convert.ChangeType(extract_long(), tmp);
			else if(tmp == typeof(ulong))  return (T)Convert.ChangeType(extract_ulong(), tmp);
			else if(tmp == typeof(float))  return (T)Convert.ChangeType(extract_float(), tmp);
			else if(tmp == typeof(double)) return (T)Convert.ChangeType(extract_double(), tmp);
			else throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] buffer size is short");
		}
		else
		{
			// 1) [버퍼]를 고정(Pinned) 시킨다.
			GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

			// 2) [버퍼_포인터]를 얻는다.
			long ptr = (long)pinnedArray.AddrOfPinnedObject() + m_offset;
			long Offset = 0;

			try
			{
				T temp = default(T);

				if (tmp.IsEnum)
				{
					temp = (T)_extract_enum(ptr, ref Offset, tmp);
				}
				else if (tmp.IsValueType)
				{
					if(typeof(DateTime).Equals(tmp))
					{
						temp = (T)Convert.ChangeType(_extract_datetime(ptr, ref Offset), tmp);
					}
					else if(typeof(CGDK.buffer).Equals(tmp))
					{
						temp = (T)Convert.ChangeType(_extract_buffer(ptr, ref Offset), tmp);
					}
					else
					{
						temp = (T)Convert.ChangeType(_extract_value(ptr, ref Offset, tmp), tmp);
					}
				}
				else if (typeof(string).Equals(tmp))
				{
					temp = (T)Convert.ChangeType(_extract_string(ptr, ref Offset), tmp);
				}
				// Case) Array
				else if (tmp.IsArray)
				{
					// - _extact_array
					temp = (T)Convert.ChangeType(_extract_array(ptr, ref Offset, tmp.GetElementType(), null, 0), tmp);
				}
				// Case) Dictionary
				else if(typeof(System.Collections.IDictionary).IsAssignableFrom(tmp))
				{
					temp = (T)Convert.ChangeType(_extract_DictionaryX(ptr, ref Offset, tmp, tmp.GetGenericArguments()), tmp);
				}
				// Case) List
				else if(typeof(System.Collections.IList).IsAssignableFrom(tmp))
				{
					// return) 
					temp = (T)Convert.ChangeType(_extract_ListX(ptr, ref Offset, tmp, tmp.GetGenericArguments()[0]), tmp);
				}
				// Case) Class
				else if (tmp.IsClass)
				{
					temp = (T)Convert.ChangeType(_extract_class(ptr, ref Offset, tmp), tmp);
				}
				else
				{
					// Check) 지원되지 않는 Type이다.
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

					// Throw) 
					throw new CGDK.Exception.Serialize(Offset, "[CGDK.buffer] Not Supported TYPE.");
				}
			
				// 5) [버퍼]의 고정(Pinned)을 Free한다.
				pinnedArray.Free();

				// 6) Buffer Pointer를 증가시킨다.
				m_count	-= (int)Offset;
				m_offset += (int)Offset;

				// Return)
				return temp;
			}
			catch(System.Exception _e)
			{
				// Trace) 
				Debug.WriteLine("CGDK.buffer extract<T>(): " + _e.Message);

				// - [버퍼]의 고정(Pinned)을 Free한다.
				pinnedArray.Free();

				// Reraise)
				throw;
			}
		}
	}

	private object	_extract				(long _ptr, ref long _offset, Type _type, int[] _static_size, int _dimension)
	{
		// Case) Primitive Type
		if (_type.IsPrimitive)
		{
			return _extract_primitive(_ptr, ref _offset, _type);
		}
		// Case) Enum Type
		else if (_type.IsEnum)
		{
			return _extract_enum(_ptr, ref _offset, _type);
		}
		// Case) Value Type
		else if (_type.IsValueType)
		{
			if(typeof(DateTime).Equals(_type))
			{
				return _extract_datetime(_ptr, ref _offset);
			}
			else if(typeof(CGDK.buffer).Equals(_type))
			{
				return _extract_buffer(_ptr, ref _offset);
			}
			else
			{
				return _extract_value(_ptr, ref _offset, _type);
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_type))
		{
			return _extract_string(_ptr, ref _offset);
		}
		// Case) Array
		else if (_type.IsArray)
		{
			return _extract_array(_ptr, ref _offset, _type.GetElementType(), _static_size, _dimension+1);
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			// Return)
			return _extract_DictionaryX(_ptr, ref _offset, _type, _type.GetGenericArguments());
		}
		else if(typeof(System.Collections.IList).IsAssignableFrom(_type))
		{
			// return) 
			return _extract_ListX(_ptr, ref _offset, _type, _type.GetGenericArguments()[0]);
		}
		// Case) Array
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			return _extract_class(_ptr, ref _offset, _type);
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}
	}
	private T		_extract_primitive<T>	(long _ptr, ref long _offset)
	{
		// 1) Type의 크기를 구한다.
		var	sizeType = Marshal.SizeOf(typeof(T));

		// Check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_offset+ sizeType > m_count)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		T obj = (T)Marshal.PtrToStructure(new IntPtr(_ptr+_offset), typeof(T));

		// 2) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += sizeType;

		// Return) 
		return obj;
	}
	private object	_extract_enum			(long _ptr, ref long _offset, Type _type)
	{
		// 1) Enum의 Type을 얻는다.
		var	type_enum = _type.GetFields()[0].FieldType;
		var	size_enum = Marshal.SizeOf(type_enum);

		// Check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
			if (_offset + size_enum > m_count)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 2) [버퍼]로 부터 [데이터]를 복사해 온다.
		var obj = Marshal.PtrToStructure(new IntPtr(_ptr+_offset), type_enum);

		// 3) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += size_enum;

		// Return) 
		return obj;
	}
	private object	_extract_primitive		(long _ptr, ref long _offset, Type _type)
	{
		// 1) Type의 크기를 구한다.
		var	sizeType = Marshal.SizeOf(_type);

		// Check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_offset+ sizeType > m_count)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		var obj = Marshal.PtrToStructure(new IntPtr(_ptr+_offset), _type);

		// 2) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += sizeType;

		// Return) 
		return obj;
	}
	private object	_extract_value			(long _ptr, ref long _offset, Type _type)
	{
		// 1) Field 정보를 얻는다.
		var temp_field = _type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		// 2) 객체를 생성한다.
		var temp_object = Activator.CreateInstance(_type);

		// 3) 각 Field값을 읽어 써넣는다.
		foreach (var iter in temp_field)
		{
			if(iter.IsNotSerialized)
				continue;

			iter.SetValue(temp_object, _extract(_ptr, ref _offset, iter.FieldType, null, 0));
		}

		// Return) 
		return	temp_object;
	}
	private object	_extract_class			(long _ptr, ref long _offset, Type _type, object _instance_object = null)
	{
        // 1) 생성된 객체가 없다면 객체를 생성한다.
        if(_instance_object == null)
            _instance_object = Activator.CreateInstance(_type);

        // Check) Serializable Attribute가 없으면 그냥 끝낸다.
        if (_is_serializable_type(_type) == false)
            return null;

        // 2) 부모가 없는객체가 나올때까지 재귀를 돌린다.
        if(_type.BaseType.BaseType != null)
        {
            _extract_class(_ptr, ref _offset, _type.BaseType, _instance_object);
        }

        // 3) Field 정보를 얻는다.
        var temp_field = _type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public | BindingFlags.DeclaredOnly);

		// 4) 각 Field값을 읽어 써넣는다.
		foreach (var iter in temp_field)
		{
			// Check) NotSerialized일 경우는 진행하지 않는다.
			if (iter.IsNotSerialized==true)
				continue;

			iter.SetValue(_instance_object, _extract(_ptr, ref _offset, iter.FieldType, null, 0));
		}

		// Return) 
		return _instance_object;
	}

	private DateTime _extract_datetime		(long _ptr, ref long _offset)
	{
		return new DateTime(_extract_primitive<long>(_ptr, ref _offset));
	}

	private buffer	_extract_buffer			(long _ptr, ref long _offset)
	{
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
		Debug.Assert(sizeof(UInt32)<=m_count);

		// Check) Buffer의 길이가 UInt32 최소크기보다 작을 경우 Exception
		if(sizeof(UInt32) >m_count) 
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// Declare) 
		CGDK.buffer temp_object = new CGDK.buffer();

		// 1) String의 길이를 얻는다.
		temp_object.size = (int)(UInt32)Marshal.PtrToStructure(new IntPtr(_ptr+_offset), typeof(UInt32));

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
		Debug.Assert((temp_object.size + sizeof(UInt32))<=m_count);

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
		if ((temp_object.size + sizeof(UInt32)) > m_count)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}

		// 2) [문자열]을 복사한다.
		temp_object.data = new byte[temp_object.size];
		System.Buffer.BlockCopy(m_buffer, m_offset + (int)_offset + sizeof(short), temp_object.data, 0, temp_object.size);

		// 3) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
		_offset += (sizeof(UInt32) + temp_object.size);

		// Return)
		return temp_object;
	}

	private string	_extract_string			(long _ptr, ref long _offset)
	{
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
		Debug.Assert(sizeof(short)<=m_count);

		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
		if(sizeof(short)>m_count) 
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}

		// 1) String의 길이를 얻는다.
		var length_string = (int)(short)Marshal.PtrToStructure(new IntPtr(_ptr+_offset), typeof(short));

		// Check) length가 -1이면 null을 리턴한다.
		if(length_string == -1)
		{
			_offset	+= sizeof(short);
			return null;
		}

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
		Debug.Assert((length_string * sizeof(char) + sizeof(short)) <= m_count);

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
		if((length_string * sizeof(char) + sizeof(short)) > m_count) 
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}

		// 2) 복사할 [문자열_길이]를 구한다. (NULL문자는 뺀다.)
		int size_copy = (length_string - 1) * sizeof(char);

		// Check) [문자열]의 제일 끝이 NULL인지 확인한다.
		if(m_buffer[m_offset + _offset + sizeof(short) + size_copy] != 0 ||m_buffer[m_offset + _offset + sizeof(short) + size_copy + 1] != 0) 
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] string terminate No-'NULL' value");
		}

		// 3) [문자열]을 복사한다.
		char[] charTemp = new char[length_string - 1];
		System.Buffer.BlockCopy(m_buffer, m_offset+(int)_offset + sizeof(short), charTemp, 0, size_copy);

		// 4) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
		_offset	+= (sizeof(short) + size_copy + sizeof(char));

		// 5) [string]로 변환해 최종 리턴한다.
		return	new string(charTemp);
	}
	private Array	_extract_array			(long _ptr, ref long _offset, Type _type, int[] _static_size, int _dimension)
	{
		// Declare)
		int temp_count = 0;

		if (_static_size == null)
		{
			// 1) [데이터 갯수]를 읽어들인다.
			temp_count = _extract_primitive<short>(_ptr, ref _offset);

			// Check) length가 -1이면 null을 리턴한다.
			if (temp_count == -1)
			{
				return null;
			}
		}
		else
		{
			temp_count = _static_size[_dimension-1];
		}

		// 2) Array 객체를 생성한다.
		Array temp_array = System.Array.CreateInstance(_type, temp_count);

		// Case) Primitive Type
		if (_type.IsPrimitive)
		{
			for (int i=0; i<temp_count; ++i)
			{
				temp_array.SetValue(_extract_primitive(_ptr, ref _offset, _type), i);
			}
		}
		// Case) Enum Type
		else if (_type.IsEnum)
		{
			for (int i=0; i<temp_count; ++i)
			{
				temp_array.SetValue(_extract_enum(_ptr, ref _offset, _type), i);
			}
		}
		// Case) Value Type
		else if (_type.IsValueType)
		{
			if(typeof(DateTime).Equals(_type))
			{
				for (int i=0; i<temp_count; ++i)
				{
					temp_array.SetValue(_extract_datetime(_ptr, ref _offset), i);
				}
			}
			else if(typeof(CGDK.buffer).Equals(_type))
			{
				for (int i=0; i<temp_count; ++i)
				{
					temp_array.SetValue(_extract_buffer(_ptr, ref _offset), i);
				}
			}
			else
			{
				for (int i=0; i<temp_count; ++i)
				{
					temp_array.SetValue(_extract_value(_ptr, ref _offset, _type), i);
				}
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_type))
		{
			for (int i=0; i<temp_count; ++i)
			{
				temp_array.SetValue(_extract_string(_ptr, ref _offset), i);
			}
		}
		// Case) Array
		else if (_type.IsArray)
		{
			for (int i=0; i<temp_count; ++i)
			{
				temp_array.SetValue(_extract_array(_ptr, ref _offset, _type.GetElementType(), _static_size, _dimension), i);
			}
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments();

			for (int i = 0; i < temp_count; ++i)
			{
				// - [데이터 갯수]를 읽어들인다.
				short count_item = _extract_primitive<short>(_ptr, ref _offset);

				// Check) temp_count가 -1이면 null을 리턴한다.
				if (count_item == -1)
					continue;

				object temp_object = Activator.CreateInstance(_type);
				_extract_Dictionary(_ptr, ref _offset, temp_object as System.Collections.IDictionary, count_item, temp_type);
				temp_array.SetValue(temp_object, i);
			}
		}
		// Case) List
		else if(typeof(System.Collections.IList).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments()[0];

			for (int i=0; i<temp_count; ++i)
			{
				// - [데이터 갯수]를 읽어들인다.
				short count_item = _extract_primitive<short>(_ptr, ref _offset);

				// Check) temp_count가 -1이면 null을 리턴한다.
				if(count_item == -1)
					continue;

				object temp_object = Activator.CreateInstance(_type);
				_extract_List(_ptr, ref _offset, temp_object as System.Collections.IList, count_item, temp_type);
				temp_array.SetValue(temp_object, i);
			}
		}
		// Case) Class
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			for (int i = 0; i < temp_count; ++i)
			{
				temp_array.SetValue(_extract_class(_ptr, ref _offset, _type), i);
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}

		return temp_array;
	}
	private object	_extract_DictionaryX	(long _ptr, ref long _offset, Type _type_create, Type[] _types) 
	{
		// 1) [데이터 갯수]를 읽어들인다.
		short count_item = _extract_primitive<short>(_ptr, ref _offset);

		// Check) temp_count가 -1이면 null을 리턴한다.
		if (count_item != -1)
		{
			// - Instance를 생성한다.
			object obj_value = Activator.CreateInstance(_type_create);

			// - Dictionary 내용을 읽어들인다.
			_extract_Dictionary(_ptr, ref _offset, obj_value as System.Collections.IDictionary, count_item, _types);

			// Return) 생성된 객체를 Return한다.
			return obj_value;
		}
		else
		{
			return null;
		}
	}
	private void	_extract_Dictionary		(long _ptr, ref long _offset, System.Collections.IDictionary _object, int _count, Type[] _types) 
	{
		// 1) [데이터]들을 읽어들인다.
		if (_types[0].IsPrimitive)
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if (typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
								_extract_array(_ptr, ref _offset, temp_type_1, null, 0)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					object obj_key = _extract_primitive(_ptr, ref _offset, _types[0]);
					object obj_value = _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					object obj_key = _extract_primitive(_ptr, ref _offset, _types[0]);
					object obj_value = _extract_ListX(_ptr, ref _offset, _types[0], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_primitive(_ptr, ref _offset, _types[0]),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsEnum)
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if (typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
								_extract_array(_ptr, ref _offset, temp_type_1, null, -1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key	 = _extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = _extract_ListX(_ptr, ref _offset, _types[0], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_enum(_ptr, ref _offset, _types[0]),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		// Case) Value Type
		else if (_types[0].IsValueType)
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(string).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(	_extract_value(_ptr, ref _offset, _types[0]),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
								_extract_array(_ptr, ref _offset, temp_type_1, null, 0)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_value(_ptr, ref _offset, _types[0]);
					var obj_value = _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_value(_ptr, ref _offset, _types[0]);
					var obj_value = _extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);
		
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _types[0]),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_string(_ptr, ref _offset),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_string(_ptr, ref _offset),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_string(_ptr, ref _offset),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_string(_ptr, ref _offset),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_string(_ptr, ref _offset),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_string(_ptr, ref _offset),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_string(_ptr, ref _offset),
								_extract_array(_ptr, ref _offset, temp_type_1, null, 0)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					object obj_key = _extract_string(_ptr, ref _offset);
					object obj_value	 = _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					object	obj_key = _extract_string(_ptr, ref _offset);
					object	obj_value = _extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_string(_ptr, ref _offset),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		// Case) Array
		else if (_types[0].IsArray)
		{
			if (_types[1].IsPrimitive)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];
				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{

					for (; _count > 0; --_count)
					{
						_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0	= _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
								_extract_array(_ptr, ref _offset, temp_type_1, null, 0)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var obj_value = _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);;

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) List
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var obj_value = _extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);
		
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				// - 
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_array(_ptr, ref _offset, temp_type_0, null, 0),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		// Case) Dictionary
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments();
				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_array(_ptr, ref _offset, temp_type_1, null, -1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1	 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1)
					);
				}
			}
			// Case) List
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - 데이터를 추가한다.
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0)
					);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				// - 
				var	temp_type_0 = _types[0].GetGenericArguments();

				// - 
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (typeof(System.Collections.IList).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_array(_ptr, ref _offset, temp_type_1, null, -1)
					);
				}
			}

			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					// - 데이터를 추가한다.
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1)
					);
				}
			}
			// Case) List
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_ListX(_ptr, ref _offset, _types[1], temp_type_1)
					);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				// - 
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				// - 
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_ListX(_ptr, ref _offset, _types[0], temp_type_0),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsClass && _is_serializable_type(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
								_extract_primitive(_ptr, ref _offset, _types[1])
					);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
								_extract_enum(_ptr, ref _offset, _types[1])
					);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
									_extract_datetime(_ptr, ref _offset)
						);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
									_extract_buffer(_ptr, ref _offset)
						);
					}
				}
				else
				{

					for (; _count > 0; --_count)
					{
						_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
									_extract_value(_ptr, ref _offset, _types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
								_extract_string(_ptr, ref _offset)
					);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
								_extract_array(_ptr, ref _offset, temp_type_1, null, -1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value =  _extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);;

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) List
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1	 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = _extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = _extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);
		
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					_object.Add(_extract_class(_ptr, ref _offset, temp_type_0),
								_extract_class(_ptr, ref _offset, _types[1])
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");
		
			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}
	}
	private object	_extract_ListX			(long _ptr, ref long _offset, Type _type_create, Type _type)
	{
		// - [데이터 갯수]를 읽어들인다.
		short count_item = _extract_primitive<short>(_ptr, ref _offset);

		// Check) temp_count가 -1이면 null을 리턴한다.
		if (count_item != -1)
		{
			object obj_value = Activator.CreateInstance(_type_create);

			_extract_List(_ptr, ref _offset, obj_value as System.Collections.IList, count_item, _type);

			return obj_value;
		}
		else
		{
			return null;
		}
	}
	private void	_extract_List			(long _ptr, ref long _offset, System.Collections.IList _object, int _count, Type _type)
	{
		// 2) [데이터]들을 읽어들인다.
		if (_type.IsPrimitive)
		{
			for (; _count > 0; --_count)
			{
				_object.Add(_extract_primitive(_ptr, ref _offset, _type));
			}
		}
		else if (_type.IsEnum)
		{
			for (; _count > 0; --_count)
			{
				_object.Add(_extract_enum(_ptr, ref _offset, _type));
			}
		}
		// Case) Value Type
		else if (_type.IsValueType)
		{
			if(typeof(DateTime).Equals(_type))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_datetime(_ptr, ref _offset));
				}
			}
			else if(typeof(CGDK.buffer).Equals(_type))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_buffer(_ptr, ref _offset));
				}
			}
			else
			{
				for (; _count > 0; --_count)
				{
					_object.Add(_extract_value(_ptr, ref _offset, _type));
				}
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_type))
		{
			for (; _count > 0; --_count)
			{
				_object.Add(_extract_string(_ptr, ref _offset));
			}
		}
		// Case) Array
		else if (_type.IsArray)
		{
			var	temp_type = _type.GetElementType();

			for (; _count > 0; --_count)
			{
				_object.Add(_extract_array(_ptr, ref _offset, temp_type, null, -1));
			}
		}
		// Case) Dictionary
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments();

			for (; _count > 0; --_count)
			{
				_object.Add(_extract_DictionaryX(_ptr, ref _offset, _type, temp_type));
			}
		}
		// Case) List
		else if (typeof(System.Collections.IList).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments()[0];

			for (; _count > 0; --_count)
			{
				_object.Add(_extract_ListX(_ptr, ref _offset, _type, temp_type));
			}
		}
		// Case) Class
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			for (; _count > 0; --_count)
			{
				_object.Add(_extract_class(_ptr, ref _offset, _type));
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}
	}

	public void		extract_skip(int _amount)									{ m_offset+=_amount; m_count-=_amount;}
	public char		extract_char()												{ Debug.Assert(sizeof(char) <= m_count); if(sizeof(char) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(char); m_count -= sizeof(char); return (char)m_buffer[iPosition];}
	public sbyte	extract_sbyte()												{ Debug.Assert(sizeof(sbyte) <= m_count); if(sizeof(sbyte) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(sbyte); m_count -= sizeof(sbyte); return (sbyte)m_buffer[iPosition];}
	public byte		extract_byte()												{ Debug.Assert(sizeof(byte) <= m_count); if(sizeof(byte) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(byte); m_count -= sizeof(byte); return m_buffer[iPosition];}
	public short	extract_short()												{ Debug.Assert(sizeof(short) <= m_count); if(sizeof(short) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(short); m_count -= sizeof(short); return BitConverter.ToInt16(m_buffer, iPosition);}
	public ushort	extract_ushort()											{ Debug.Assert(sizeof(ushort) <= m_count); if(sizeof(ushort) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(ushort); m_count -= sizeof(ushort); return BitConverter.ToUInt16(m_buffer, iPosition);}
	public int		extract_int()												{ Debug.Assert(sizeof(int) <= m_count); if(sizeof(int) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(int); m_count -= sizeof(int); return BitConverter.ToInt32(m_buffer, iPosition);}
	public uint		extract_uint()												{ Debug.Assert(sizeof(uint) <= m_count); if(sizeof(uint) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(uint); m_count -= sizeof(uint); return BitConverter.ToUInt32(m_buffer, iPosition);}
	public long		extract_long()												{ Debug.Assert(sizeof(long) <= m_count); if(sizeof(long) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(long); m_count -= sizeof(long); return BitConverter.ToInt64(m_buffer, iPosition);}
	public ulong	extract_ulong()												{ Debug.Assert(sizeof(ulong) <= m_count); if(sizeof(ulong) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(ulong); m_count -= sizeof(ulong); return BitConverter.ToUInt64(m_buffer, iPosition);}
	public float	extract_float()												{ Debug.Assert(sizeof(float) <= m_count); if(sizeof(float) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(float); m_count -= sizeof(float); return BitConverter.ToSingle(m_buffer, iPosition);}
	public double	extract_double()											{ Debug.Assert(sizeof(double) <= m_count); if(sizeof(double) > m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = m_offset; m_offset += sizeof(double); m_count -= sizeof(double); return BitConverter.ToDouble(m_buffer, iPosition);}
	public string	extract_string()											{ return extract<string>();}

// 3) set_front (값 써넣기)
    public void		set_front<T>(char _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(char))	{ set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(sbyte _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(sbyte)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(byte _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(byte))	{ set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(short _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(short)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(ushort _object, int _offset = 0) where T:struct{ if(typeof(T) == typeof(ushort)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(int _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(int)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(uint _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(uint)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(long _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(long)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(ulong _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(ulong)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(float _object, int _offset = 0) where T:struct	{ if(typeof(T) == typeof(float)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(double _object, int _offset = 0) where T:struct{ if(typeof(T) == typeof(double)) { set_front(_object, _offset);} else { set_front(Convert.ChangeType(_object, typeof(T)), _offset);}}
	public void		set_front<T>(T _object, int _offset = 0) where T:struct		{ set_front(Convert.ChangeType(_object, typeof(T)), _offset);}

	public void		set_front(byte[] _object, int _offset_src, int _count, int _offset = 0) { Debug.Assert((m_offset+m_count+_count)<=m_buffer.Length); System.Buffer.BlockCopy(_object, _offset_src, m_buffer, m_offset+_offset, _count);}
	public void		set_front(buffer _object, int _offset = 0)					{ Debug.Assert((m_offset + m_count + _object.m_count) <= m_buffer.Length); System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, m_buffer, m_offset + _offset, _object.m_count);}
    public void		set_front(char _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(char)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(sbyte _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(sbyte)) <= m_buffer.Length); m_buffer[m_offset + _offset] = (byte)_object;}
	public void		set_front(byte _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(byte)) <= m_buffer.Length); m_buffer[m_offset + _offset] = _object;}
	public void		set_front(short _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(short)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(ushort _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(ushort)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(int _object, int _offset = 0)						{ Debug.Assert((m_offset + _offset + sizeof(int)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(uint _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(uint)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(long _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(long)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(ulong _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(ulong)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(float _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(float)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(double _object, int _offset = 0)					{ Debug.Assert((m_offset + _offset + sizeof(double)) <= m_buffer.Length); BitConverter.GetBytes(_object).CopyTo(m_buffer, m_offset + _offset);}
	public void		set_front(object _object, int _offset = 0)					{ buffer temp = new buffer(m_buffer, m_offset + _offset, 0); temp.append(_object); }													 

// 4) get_front( 값 읽기)
	public T		get_front<T>(int _offset = 0)								{ buffer temp = new buffer(m_buffer, m_offset+_offset, m_count-_offset); return temp.extract<T>();}
	public void		get_front<T>(ref T _object, int _offset = 0)				{ _object = get_front<T>(_offset); }
	public void		get_front<T>(ref char _object, int _offset = 0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_char(_offset); }
	public void		get_front<T>(ref sbyte _object, int _offset = 0)			{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_sbyte(_offset); }
    public void		get_front<T>(ref byte _object, int _offset = 0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_byte(_offset); }
    public void		get_front<T>(ref short _object, int _offset = 0)			{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_short(_offset); }
    public void		get_front<T>(ref ushort _object, int _offset = 0)			{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_ushort(_offset); }
    public void		get_front<T>(ref int _object, int _offset = 0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_int(_offset); }
    public void		get_front<T>(ref uint _object, int _offset = 0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_uint(_offset); }
    public void		get_front<T>(ref long _object, int _offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_long(_offset); }
    public void		get_front<T>(ref ulong _object, int _offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_ulong(_offset); }
    public void		get_front<T>(ref float _object, int _offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_float(_offset); }
    public void		get_front<T>(ref double _object, int _offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = get_front_double(_offset); }

    public char		get_front_char(int _offset = 0)								{ Debug.Assert((_offset + sizeof(char)) <= m_buffer.Length); return BitConverter.ToChar(m_buffer, m_offset + _offset);}
	public sbyte	get_front_sbyte(int _offset = 0)							{ Debug.Assert((_offset + sizeof(sbyte)) <= m_buffer.Length); return (sbyte)m_buffer[m_offset + _offset];}
	public byte		get_front_byte(int _offset = 0)								{ Debug.Assert((_offset + sizeof(byte)) <= m_buffer.Length); return m_buffer[m_offset + _offset]; }
	public short	get_front_short(int _offset = 0)							{ Debug.Assert((_offset + sizeof(short)) <= m_buffer.Length); return BitConverter.ToInt16(m_buffer, m_offset + _offset);}
	public ushort	get_front_ushort(int _offset = 0)							{ Debug.Assert((_offset + sizeof(ushort)) <= m_buffer.Length); return BitConverter.ToUInt16(m_buffer, m_offset + _offset);}
	public int		get_front_int(int _offset = 0)								{ Debug.Assert((_offset + sizeof(int)) <= m_buffer.Length); return BitConverter.ToInt32(m_buffer, m_offset + _offset);}
	public uint		get_front_uint(int _offset = 0)								{ Debug.Assert((_offset + sizeof(uint)) <= m_buffer.Length); return BitConverter.ToUInt32(m_buffer, m_offset + _offset);}
	public long		get_front_long(int _offset = 0)								{ Debug.Assert((_offset + sizeof(long)) <= m_buffer.Length); return BitConverter.ToInt64(m_buffer, m_offset + _offset);}
	public ulong	get_front_ulong(int _offset = 0)							{ Debug.Assert((_offset + sizeof(ulong)) <= m_buffer.Length); return BitConverter.ToUInt64(m_buffer, m_offset + _offset);}
	public float	get_front_float(int _offset = 0)							{ Debug.Assert((_offset + sizeof(float)) <= m_buffer.Length); return BitConverter.ToSingle(m_buffer, m_offset + _offset);}
	public double	get_front_double(int _offset = 0)							{ Debug.Assert((_offset + sizeof(double)) <= m_buffer.Length); return BitConverter.ToDouble(m_buffer, m_offset + _offset);}
	public void		get_front_array(byte[] _object, int _offset_src, int _count, int _offset = 0) { Debug.Assert((m_offset + m_count + _object.Length) <= m_buffer.Length); System.Buffer.BlockCopy(m_buffer, m_offset+_offset, _object, _offset_src, _count);}
	public void		get_front_buffer(buffer _object, int _offset = 0)			{ Debug.Assert((m_offset + m_count + _object.m_count) <= m_buffer.Length); System.Buffer.BlockCopy(m_buffer, m_offset + _offset, _object.m_buffer, _object.m_offset, _object.m_count); }
	public uint		get_front_CRC()												{ return 0;}

	public static int	get_size_of(object _object)								{ return _size_of(_object);}

	private static int	_size_of(object _object)
	{
		// Declare) 
		int	size = 0;

		try
		{
			Type tmp = _object.GetType();
                
			if (tmp.IsPrimitive)
			{
				size += Marshal.SizeOf(tmp);
			}
			else if(tmp.IsEnum)
			{
				size += Marshal.SizeOf(tmp.GetFields()[0].FieldType);
			}
			else if (tmp.IsValueType)
			{
				if(typeof(DateTime).Equals(tmp))
				{
					size += _SizeOf_DateTime();
				}
				else if(typeof(CGDK.buffer).Equals(tmp))
				{
					size += _size_of_buffer((buffer)_object);
				}
				else
				{
					size += _size_of_value(_object);
				}
			}
			else if (tmp.IsArray)
			{
				size += _size_of_Collection(_object as System.Collections.ICollection, _object.GetType().GetElementType());
			}
			else if (typeof(string).Equals(tmp))
			{
				size += _size_of_string(_object as string);
			}
			else
			{
				System.Collections.IDictionary tempObject1 = _object as System.Collections.IDictionary;
				if (tempObject1!=null)
				{
					size += _size_of_Dictionary(tempObject1, tmp.GetGenericArguments());
				}
				else
				{
					System.Collections.ICollection tempObject2 = _object as System.Collections.ICollection;

					if (tempObject2 !=null)
					{
						size += _size_of_Collection(tempObject2, _object.GetType().GetGenericArguments()[0]);
					}
					else if(tmp.IsClass)
					{
						size += _SizeOf_class(_object);
					}
					else
					{
						size += _size_of_value(_object);
					}
				}
			}
		}
		catch (System.Exception _e)
		{
			// Trace) 
			Debug.WriteLine("CGDK.buffer size_of<T>(ICollection<string>): " + _e.Message);

			// Reraise) 
			throw;
		}

		// Return0 
		return	size;
	}

	private static int	_SizeOf_DateTime()
	{
		return sizeof(long);
	}

	private static int _size_of_buffer(CGDK.buffer _buffer)
	{
		return (_buffer.data!=null) ? sizeof(UInt32) + _buffer.size : sizeof(UInt32);
	}

	private static int	_size_of_Dictionary(System.Collections.IDictionary _object, Type[] _types)
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			return sizeof(short);
		}

		// Declaere)
		int	size = 0;

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		size += sizeof(short);

		// 2) [데이터]들을 써넣는다.
		if (_types[0].IsPrimitive)
		{
			if (_types[1].IsPrimitive)
			{
				int size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1]);

				size += _object.Count*(size_0 + size_1);
			}
			else if (_types[1].IsEnum)
			{
				int size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				size += _object.Count*(size_0 + size_1);
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				int size_0 = Marshal.SizeOf(_types[0]);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsEnum)
		{
			if (_types[1].IsPrimitive)
			{
				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				int size_1 = Marshal.SizeOf(_types[1]);

				size += _object.Count*(size_0 + size_1);
			}
			else if (_types[1].IsEnum)
			{
				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				size += _object.Count*(size_0 + size_1);
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += size_0;
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsValueType)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Key);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsArray)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, _types[1].GetElementType());
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (typeof(string).Equals(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_string(temp_enum.Key as string);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Dictionary(temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					_size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					_size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else if (_types[0].IsClass && _is_serializable_type(_types[0]))
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_class(temp_enum.Key);
					size += _SizeOf_class(temp_enum.Value);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// Throw) 
				throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
		}

		return size;
	}
	private static int	_size_of_Collection(System.Collections.ICollection _object, Type _type)
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			return sizeof(short);
		}

		// Declare) 
		int	size = 0;

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		size	+= sizeof(short);

		// 3) [데이터]들을 써넣는다.
		if (_type.IsPrimitive)
		{
			var temp_enum = _object.GetEnumerator();

			size += Marshal.SizeOf(_type)*_object.Count;
		}
		else if (_type.IsEnum)
		{
			var temp_enum = _object.GetEnumerator();

			size += Marshal.SizeOf(_type.GetFields()[0].FieldType) *_object.Count;
		}
		else if (_type.IsValueType)
		{
			if (typeof(DateTime).Equals(_type))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _SizeOf_DateTime();
				}
			}
			if (typeof(DateTime).Equals(_type))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_buffer((buffer)temp_enum.Current);
				}
			}
			else
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_value(temp_enum.Current);
				}
			}
		}
		else if (_type.IsArray)
		{
			Type tmp_type = _type.GetElementType();

			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				size += _size_of_Collection(temp_enum.Current as System.Collections.ICollection, tmp_type);
			}
		}
		else if (typeof(string).Equals(_type))
		{
			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				size += _size_of_string(temp_enum.Current as string);
			}
		}
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			Type[] temp_type = _type.GetGenericArguments();

			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				size += _size_of_Dictionary(temp_enum.Current as System.Collections.IDictionary, temp_type);
			}
		}
		else if (typeof(System.Collections.ICollection).IsAssignableFrom(_type))
		{
			Type tmp_type = _type.GetGenericArguments()[0];

			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				size += _size_of_Collection(temp_enum.Current as System.Collections.ICollection, tmp_type);
			}
		}
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				size += _SizeOf_class(temp_enum.Current);
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(size, "[CGDK.buffer] Not Supported TYPE.");
		}

		//_append_Collection
		return	size;
	}
	private static int	_SizeOf_class(object _object, Type _base_type = null)
	{
       // 1) Get Type ( 재귀용 _base_type 이 존재한다면 그걸쓰고 아니라면 Data 를 쓴다.  )
		Type temp_type = _base_type != null ? _base_type : _object.GetType();

		// Check) Serializable이 아니면 리턴한다.
		if (_is_serializable_type(temp_type) == false)
			return 0;

		// Declare)
		int	size = 0;

        // 2) 부모가 없는객체가 나올때까지 재귀를 돌린다.
        if(temp_type.BaseType != null)
        {
            size += _SizeOf_class(_object, temp_type.BaseType);
        }
        // 부모가 없는건 Object 클래스 이므로 패스한다.
        else
        {
            return 0;
        }

        // 3) 변수들을 얻는다.
        var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly);

        // 4) 최상위 부모의 맴버부터 차례대로 buffer 에 append 한다
		foreach(var iter in temp_field)
		{
			// Check) 
			if (iter.IsNotSerialized==true)
				continue;

			// Check)
			if (iter.GetCustomAttributes(typeof(CGDK.Attribute.Serializable), false) == null)
				continue;

			object temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				size += _size_of(temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				size += sizeof(short);
				continue;
			}
		}
		return	size;
	}
	private static int	_size_of_value(object _object)
	{
		// Declare)
		int	size = 0;

		Type temp_type = _object.GetType();
		var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		foreach(var iter in temp_field)
		{
			// Check)
			if(iter.IsNotSerialized==true)
				continue;

			object temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				size += _size_of(temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				size += sizeof(short);
				continue;
			}
		}

		return	size;
	}
	private static int _size_of_string(string _string)
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_string == null)
		{
			// Return) -1을 쓰고 끝낸다.
			return	sizeof(short);
		}

		// 1) [문자열]을 [문자배열]로 변경하고 길이를 구한다.
		var temp_array = _string.ToCharArray();
		var	iStringLength = temp_array.Length;

		// Return) [버퍼_길이]를 리턴한다.
		return	(sizeof(short)+(iStringLength+1)*sizeof(char));
	}


// 1) Buffer
		private byte[]	m_buffer;

	// 2) Buffer중 시작 위치
	private int		m_offset;

	// 3) 사용 길이 (m_iOffset부터 Buffer중 사용하는 끝까지의 길이)
	private int		m_count;
}


}
