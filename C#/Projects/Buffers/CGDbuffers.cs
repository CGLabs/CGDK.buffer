//*****************************************************************************
//*                                                                           *
//*                                CGD.buffer                                 *
//*                      Ver 2.0pre / Release 2015.01.05                      *
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
//  class CGD.buffer
//
//
//
//
//----------------------------------------------------------------------------
namespace CGD
{

public struct buffer
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
	public buffer(byte[] _Buffer, int _Offset = 0, int _Count = 0)
	{
		m_Buffer = _Buffer;
		m_iOffset = _Offset;
		m_iCount = _Count;
	}
	public buffer(buffer _Buffer)
	{
		m_Buffer	 = _Buffer.m_Buffer;
		m_iOffset	 = _Buffer.m_iOffset;
		m_iCount	 = _Buffer.m_iCount;
	}
	public buffer(int _Size)
	{
		m_Buffer = new byte[_Size];
		m_iOffset = 0;
		m_iCount = 0;
	}

	public buffer clone()
	{
		// 1) 새로운 버퍼를 생성한다.
		byte[]	temp = new byte[capacity];
		
		// 2) [문자열]을 복사해 넣는다.
		Buffer.BlockCopy(m_Buffer, 0, temp, 0, capacity);

		// 3) 적용한다.
		return	new buffer(temp, m_iOffset, m_iCount);
	}


// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
	public const uint	SIZE_OF_CRC	 = sizeof(uint);
			

// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
// 1) 생성/버퍼설정
	public void		alloc(int _Size)
	{
		m_Buffer	 = new byte[_Size];
		m_iOffset	 = 0;
		m_iCount	 = 0;
	}
	public void		set_buffer(byte[] _Buffer, int _Offset, int _Length)
	{
		// Check) _Offset+_Length가 _Buffer의 크기보다 크면 안됀다.
		Debug.Assert((_Offset+_Length) <= _Buffer.Length);

		// Check) _Offset이나 _Length의 길이가 _Buffer의 크기를 초과할 경우 Exception을 던진다.
		if ((_Offset+_Length) > _Buffer.Length)
		{
			throw new Exception();
		}

		// 1) 값을 적용
		m_Buffer	 = _Buffer;
		m_iOffset	 = _Offset;
		m_iCount	 = _Length;
	}
	public void		set_buffer(byte[] _Buffer, int _Offset)
	{
		// Check) _Offset+_Length가 _Buffer의 크기보다 크면 안됀다.
		Debug.Assert(_Offset <= _Buffer.Length);

		// Check) _Offset이나 _Length의 길이가 _Buffer의 크기를 초과할 경우 Exception을 던진다.
		if (_Offset>_Buffer.Length)
		{
			throw new Exception();
		}

		// 1) 값을 적용한다.
		m_Buffer	 = _Buffer;
		m_iOffset	 = _Offset;
		m_iCount	 = _Buffer.Length-_Offset;
	}
	public byte[]	clear()
	{
		// 1) 임시로 보관
		byte[]	temp = m_Buffer;

		// 2) Reset한다.
		m_Buffer	 = null;
		m_iOffset	 = 0;
		m_iCount	 = 0;

		// 3) 저장되어 있던 byte[]를 리턴해 준다.
		return temp;
	}

// 2) Basic operations
	public bool		empty()									{ return m_Buffer==null;}
	public int		get_remained()							{ return m_Buffer.Length - m_iOffset - m_iCount; }

	public int capacity { get { return m_Buffer.Length; } }

	// - for General User
	public byte[]	buf										{	get { return m_Buffer;}		set { m_Buffer=value;}}
	public int		offset									{	get { return m_iOffset;}	set { m_iOffset=value;}}
	public int		len										{	get { return m_iCount;}		set {m_iCount=value;}}

	// - for C# User
	public byte[] Array { get { return m_Buffer; } set { m_Buffer = value; } }
	public int		Offset									{	get { return m_iOffset;}	set { m_iOffset=value;}}
	public int		Count									{	get { return m_iCount;}		set {m_iCount=value;}}

	public static buffer operator +(buffer _Lhs, int _Rhs)	{ return new buffer(_Lhs.Array, _Lhs.Offset+_Rhs, _Lhs.Count-_Rhs);}
	public static buffer operator -(buffer _Lhs, int _Rhs)	{ return new buffer(_Lhs.Array, _Lhs.Offset - _Rhs, _Lhs.Count + _Rhs); }
	public static implicit operator ArraySegment<byte>(buffer _Rhs){ return new ArraySegment<byte>(_Rhs.Array, _Rhs.Offset, _Rhs.Count);}
	public static explicit operator buffer(ArraySegment<byte> _Rhs){ return new buffer(_Rhs.Array, _Rhs.Offset, _Rhs.Count);}

// 3) append(붙이기)
	public void		append_skip(int _Amount)				{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=_Amount);	m_iCount += _Amount; }
	public void		append(buffer _Data)					{ _append_buffer(_Data);}
	public void		append(char _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(char));		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(char); }
	public void		append(sbyte _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(sbyte));	m_Buffer[m_iOffset+m_iCount]=(byte)_Data; m_iCount+=sizeof(sbyte); }
	public void		append(byte _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(byte));		m_Buffer[m_iOffset + m_iCount] = _Data; m_iCount += sizeof(byte); }
	public void		append(short _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(short));	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(short); }
	public void		append(ushort _Data)					{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(ushort));	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(ushort); }
	public void		append(int _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(int));		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(int); }
	public void		append(uint _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(uint));		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(uint); }
	public void		append(long _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(long));		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(long); }
	public void		append(ulong _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(ulong));	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(ulong); }
	public void		append(float _Data)						{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(float));	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(float); }
	public void		append(double _Data)					{ Debug.Assert((m_Buffer.Length-m_iOffset-m_iCount)>=sizeof(double));	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset + m_iCount); m_iCount += sizeof(double); }
	public void		append(DateTime _Data)					{ 	uint	tempA	 = (((uint)_Data.Month)<<16) |(uint)_Data.Year;
																uint	tempB	 = ((uint)_Data.Second)<<24 | ((uint)_Data.Minute)<<16 | ((uint)_Data.Hour)<<8 | ((uint)_Data.Day);

																append<uint>(tempA);
																append<uint>(tempB);
																append<int>(_Data.Millisecond);
															}

	public void		append<T>(char _Data) where T:struct	{ if(typeof(T)==typeof(char))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(sbyte _Data) where T:struct	{ if(typeof(T)==typeof(sbyte))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(byte _Data) where T:struct	{ if(typeof(T)==typeof(byte))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(short _Data) where T:struct	{ if(typeof(T)==typeof(short))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(ushort _Data) where T:struct	{ if(typeof(T)==typeof(ushort))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(int _Data) where T:struct		{ if(typeof(T)==typeof(int))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(uint _Data) where T:struct	{ if(typeof(T)==typeof(uint))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(long _Data) where T:struct	{ if(typeof(T)==typeof(long))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(ulong _Data) where T:struct	{ if(typeof(T)==typeof(ulong))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(float _Data) where T:struct	{ if(typeof(T)==typeof(float))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(double _Data) where T:struct	{ if(typeof(T)==typeof(double))	{ append(_Data);} else { append((T)Convert.ChangeType(_Data, typeof(T)));}}
	public void		append<T>(string _Data)
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_Buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr	 = (long)pinnedArray.AddrOfPinnedObject();
		long Offset	 = m_iOffset + m_iCount;

		try
		{
			// 3) 추가한다.
			_append<string>(ptr, ref Offset, _Data);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_iCount	 = (int)Offset;
		}
		catch (Exception e)
		{
			// Trace) 
			Debug.WriteLine("CGD.buffer extract<T>(ICollection<string>): " + e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}

	public void		append<T>(object _Data) where T:struct
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_Buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr	 = (long)pinnedArray.AddrOfPinnedObject();
		long Offset	 = m_iOffset + m_iCount;

		try
		{
			Type tmp = _Data.GetType();

			if (tmp.IsPrimitive)
			{
				Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)");

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				Marshal.StructureToPtr(_Data, new IntPtr(ptr + Offset), false); Offset += Marshal.SizeOf(tmp);
			#else
				_append_Primitive(ptr, ref Offset, _Data);
			#endif
			}
			else if(typeof(DateTime).Equals(tmp))
			{
				_append_datetime(ptr, ref Offset, _Data);
			}
			else
			{
				_append_Value(ptr, ref Offset, _Data);
			}

			// 5) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_iCount	 = (int)Offset;
		}
		catch (Exception e)
		{
			// Trace) 
			Debug.WriteLine("CGD.buffer extract<T>(ICollection<string>): " + e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}
	public void		append(object _Data)
	{
		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_Buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr	 = (long)pinnedArray.AddrOfPinnedObject();
		long Offset	 = m_iOffset + m_iCount;

		try
		{
			// Check) null 일 경우 -1만 쓰고 끝냄
			if (_Data == null)
			{
				append((short)-1);
				return;
			}

			// 3) 추가한다.
			_append(ptr, ref Offset, _Data);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			m_iCount	 = (int)Offset;
		}
		catch (Exception e)
		{
			// Trace) 
			Debug.WriteLine("CGD.buffer extract<T>(ICollection<string>): " + e.Message);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// Reraise) 
			throw;
		}
	}

	private void _append_buffer(buffer _Data)
	{
		Debug.Assert((m_Buffer.Length - m_iOffset - m_iCount) >= _Data.m_iCount);
		
		System.Buffer.BlockCopy(_Data.m_Buffer, _Data.m_iOffset, m_Buffer, m_iOffset + m_iCount, _Data.m_iCount); 
		
		m_iCount += _Data.m_iCount; 
	}
	public void append_text(string _Data)
	{
		// 1) 문자열을 배열로 변경하고 길이를 구한다.
		var tempArray = _Data.ToCharArray();
		var iStringLength = tempArray.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert((m_iOffset + m_iCount + iStringLength * sizeof(char)) <= m_Buffer.Length);

		// 1) [문자열]을 복사해 넣는다.
		Buffer.BlockCopy(tempArray, 0, m_Buffer, m_iOffset + m_iCount, iStringLength * sizeof(char));

		// 2) [버퍼_길이]를 더해준다.
		m_iCount += (iStringLength * sizeof(char));
	}
	public void append_text(ICollection<string> _Collection)
	{
		// 2) 데이터들을 저장한다.
		foreach (var iter in _Collection)
		{
			append_text(iter);
		}
	}
	public void append_text(params string[] _Array)
	{
		foreach (var iter in _Array)
		{
			append_text(iter);
		}
	}
	public void append_CRC()
	{
		//_append<uint>(0);
		m_iCount	+= sizeof(uint);
	}
	private void _append<T>(long _Ptr, ref long _Offset, T _Data) where T:struct
	{
	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr(_Data, new IntPtr(_Ptr + _Offset), false); _Offset += Marshal.SizeOf(typeof(T));
	#else
		_append_Primitive(_Ptr, ref _Offset, _Data);
	#endif
	}
	private void _append<T>(long _Ptr,ref long _Offset,string _Data) 
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_Data == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.StructureToPtr((short)-1, new IntPtr(_Ptr + _Offset), false);
			_Offset += sizeof(short);
			return;
		}

		// 1) [문자열]을 [문자배열]로 변경하고 길이를 구한다.
		var tempArray		 = _Data.ToCharArray();
		var	iStringLength	 = tempArray.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert((_Offset+sizeof(short)+iStringLength*sizeof(char))<=m_Buffer.Length);

		// 2) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
		Marshal.StructureToPtr((short)(iStringLength+1), new IntPtr(_Ptr+_Offset), false);

		// 3) [문자열]을 복사해 넣는다.
		Buffer.BlockCopy(tempArray, 0, m_Buffer, (int)_Offset+sizeof(short), iStringLength*sizeof(char));

		// 4) [버퍼_길이]를 더해준다. (NULL문자열의 길이까지 포함한다.)
		_Offset	+= (sizeof(short)+(iStringLength+1)*sizeof(char));

		// 5) [NULL]을 넣는다.
		Marshal.StructureToPtr((char)0, new IntPtr(_Ptr+_Offset-sizeof(char)), false);
	}
	private void _append<T>(long _Ptr, ref long _Offset, params string[] _Array)
	{
		foreach (var iter in _Array)
		{
			_append<string>(_Ptr, ref _Offset, iter);
		}
	}
	private void _append(long _Ptr, ref long _Offset, object _Data)
	{
		// 1) Type을 읽는다.
		Type tempType = _Data.GetType();

		if (tempType.IsPrimitive)
		{
		#if _USE_INLINE_PRIMITIVE_FUNCTION
			Marshal.StructureToPtr(_Data, new IntPtr(_Ptr + _Offset), false); _Offset += Marshal.SizeOf(tempType);
		#else
			_append_Primitive(_Ptr, ref _Offset, _Data);
		#endif
		}
		else if (tempType.IsValueType)
		{
			if(typeof(DateTime).Equals(tempType))
			{
				_append_datetime(_Ptr, ref _Offset, _Data);
			}
			else
			{
				_append_Value(_Ptr, ref _Offset, _Data);
			}
		}
		else if (tempType.IsArray)
		{
			_append_Collection(_Ptr, ref _Offset, _Data as System.Collections.ICollection, _Data.GetType().GetElementType());
		}
		else if (typeof(string).Equals(tempType))
		{
			_append<string>(_Ptr, ref _Offset, _Data as string);
		}
		else 
		{
			{
				System.Collections.IDictionary tempObject=_Data as System.Collections.IDictionary;
				if (tempObject!=null)
				{
					_append_Dictionary(_Ptr, ref _Offset, tempObject, tempType.GetGenericArguments());
					return;
				}
			}
			{
				System.Collections.ICollection	tempObject	 = _Data as System.Collections.ICollection;
				if (tempObject !=null)
				{
					_append_Collection(_Ptr, ref _Offset, tempObject, _Data.GetType().GetGenericArguments()[0]);
					return;
				}
				else
				{
					// Check) 지원되지 않는 Type이다.
					Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

					// Throw) 
					throw	new Exception();
				}
			}
		}
	}
	private void _append_Primitive(long _Ptr, ref long _Offset, object _Data)
	{
		// Check) m_iCount가 남은 크기보다 작으면 Exception을 던진다.
		if (Marshal.SizeOf(_Data)+_Offset > m_Buffer.Length)
		{
			throw new Exception();
		}

		// 1) [버퍼_포인터]에 [데이터]를 복사한다.
		Marshal.StructureToPtr(_Data, new IntPtr(_Ptr+_Offset), false);	

		// 2) m_iCount의 길이를 더한다.
		_Offset	 += Marshal.SizeOf(_Data);
	}
	private void _append_Value(long _Ptr, ref long _Offset, object _Data)
	{
		Type	tempType	 = _Data.GetType();
		var		tempFields		 = tempType.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		foreach(var iter in tempFields)
		{
			object	temp	 = iter.GetValue(_Data);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				_append(_Ptr, ref _Offset, temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				Marshal.StructureToPtr((short)-1, new IntPtr(_Ptr + _Offset), false);
				_Offset += sizeof(short);
				continue;
			}
		}
	}
	public void	 _append_datetime(long _Ptr,ref long _Offset, DateTime _Data)
	{
		uint		tempA	 = (((uint)_Data.Month)<<16) |(uint)_Data.Year;
		uint		tempB	 = ((uint)_Data.Second)<<24 | ((uint)_Data.Minute)<<16 | ((uint)_Data.Hour)<<8 | ((uint)_Data.Day);

		_append<uint>(_Ptr, ref _Offset, tempA);
		_append<uint>(_Ptr, ref _Offset, tempB);
		_append<int>(_Ptr, ref _Offset, _Data.Millisecond);
	}

	public void	 _append_datetime(long _Ptr,ref long _Offset, object _Data)
	{
		DateTime	tempTime = (DateTime)Convert.ChangeType(_Data, typeof(DateTime));

		uint		tempA	 = (((uint)tempTime.Month)<<16) |(uint)tempTime.Year;
		uint		tempB	 = ((uint)tempTime.Second)<<24 | ((uint)tempTime.Minute)<<16 | ((uint)tempTime.Hour)<<8 | ((uint)tempTime.Day);

		_append<uint>(_Ptr, ref _Offset, tempA);
		_append<uint>(_Ptr, ref _Offset, tempB);
		_append<int>(_Ptr, ref _Offset, tempTime.Millisecond);
	}

	private void _append_Dictionary(long _Ptr,ref long _Offset,System.Collections.IDictionary _Data, Type[] _Types) 
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_Data==null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.StructureToPtr((short)-1, new IntPtr(_Ptr + _Offset), false);
			_Offset += sizeof(short);
			return;
		}

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr((short)_Data.Count, new IntPtr(_Ptr + _Offset), false); _Offset += Marshal.SizeOf(typeof(short));
	#else
		_append_Primitive(_Ptr,ref _Offset,(short)_Data.Count);
	#endif

		// 2) [데이터]들을 써넣는다.
		if (_Types[0].IsPrimitive)
		{
			if (_Types[1].IsPrimitive)
			{
				var tempEnum = _Data.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);
				int Size1	 = Marshal.SizeOf(_Types[1]);

				while (tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);

				while(tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			#else
				while(tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType1	 = _Types[1].GetElementType();

				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);

				while(tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			#endif
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);

				while(tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			#endif
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);

				while(tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			#endif
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size0	 = Marshal.SizeOf(_Types[0]);

				while(tempEnum.MoveNext())
				{
					Marshal.StructureToPtr(tempEnum.Key, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Key);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			#endif
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else if (_Types[0].IsValueType)
		{
			if (_Types[1].IsPrimitive)
			{
				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int	Size1	 = Marshal.SizeOf(_Types[1]);

				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while (tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType1	 = _Types[1].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Key);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else if (_Types[0].IsArray)
		{
			if (_Types[1].IsPrimitive)
			{
				 var	tempType0	 = _Types[0].GetElementType();

				var tempEnum = _Data.GetEnumerator();

			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int Size1 = Marshal.SizeOf(_Types[1]);

				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				 var	tempType0	 = _Types[0].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType0	 = _Types[0].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, _Types[1].GetElementType());
				}
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetElementType();
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetElementType();
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else if (typeof(string).Equals(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int Size1 = Marshal.SizeOf(_Types[1]);

				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType1	 = _Types[1].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append<string>(_Ptr, ref _Offset, tempEnum.Key as string);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int Size1 = Marshal.SizeOf(_Types[1]);

				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();
				 var	tempType1	 = _Types[1].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments();
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Key as System.Collections.IDictionary, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
			#if _USE_INLINE_PRIMITIVE_FUNCTION
				int Size1 = Marshal.SizeOf(_Types[1]);

				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					Marshal.StructureToPtr(tempEnum.Value, new IntPtr(_Ptr + _Offset), false); _Offset += Size1;
				}
			#else
				while (tempEnum.MoveNext())
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Primitive(_Ptr, ref _Offset, tempEnum.Value);
				}
			#endif
			}
			else if(_Types[1].IsValueType)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Value(_Ptr,ref _Offset,tempEnum.Value);
				}
			}
			else if(_Types[1].IsArray)
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];
				 var	tempType1	 = _Types[1].GetElementType();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else if (typeof(string).Equals(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append<string>(_Ptr, ref _Offset, tempEnum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];
				 var	tempType1	 = _Types[1].GetGenericArguments();

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Dictionary(_Ptr, ref _Offset, tempEnum.Value as System.Collections.IDictionary, tempType1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_Types[1]))
			{
				 var	tempType0	 = _Types[0].GetGenericArguments()[0];
				 var	tempType1	 = _Types[1].GetGenericArguments()[0];

				var tempEnum = _Data.GetEnumerator();
				while(tempEnum.MoveNext()) 
				{
					_append_Collection(_Ptr, ref _Offset, tempEnum.Key as System.Collections.ICollection, tempType0);
					_append_Collection(_Ptr, ref _Offset, tempEnum.Value as System.Collections.ICollection, tempType1);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

			// Throw) 
			throw	new Exception();
		}
	}
	private void _append_Collection(long _Ptr, ref long _Offset, System.Collections.ICollection _Data, Type _Type)
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_Data == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.StructureToPtr((short)-1, new IntPtr(_Ptr + _Offset), false);
			_Offset += sizeof(short);
			return;
		}

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
	#if _USE_INLINE_PRIMITIVE_FUNCTION
		Marshal.StructureToPtr((short)_Data.Count, new IntPtr(_Ptr + _Offset), false); _Offset += Marshal.SizeOf(typeof(short));
	#else
		_append_Primitive(_Ptr, ref _Offset, (short)_Data.Count);
	#endif

		// 3) [데이터]들을 써넣는다.
		if (_Type.IsPrimitive)
		{
			var tempEnum = _Data.GetEnumerator();

		#if _USE_INLINE_PRIMITIVE_FUNCTION
			int Size0 = Marshal.SizeOf(_Type);

			while (tempEnum.MoveNext())
			{
				Marshal.StructureToPtr(tempEnum.Current, new IntPtr(_Ptr + _Offset), false); _Offset += Size0;
			}
		#else
			while (tempEnum.MoveNext())
			{
				_append_Primitive(_Ptr, ref _Offset, tempEnum.Current);
			}
		#endif
		}
		else if (_Type.IsValueType)
		{
			if(typeof(DateTime).Equals(_Type))
			{
				var tempEnum = _Data.GetEnumerator();
				while (tempEnum.MoveNext())
				{
					_append_datetime(_Ptr, ref _Offset, tempEnum.Current);
				}
			}
			else
			{
				var tempEnum = _Data.GetEnumerator();
				while (tempEnum.MoveNext())
				{
					_append_Value(_Ptr, ref _Offset, tempEnum.Current);
				}
			}
		}
		else if(_Type.IsArray)
		{
			Type tmpType =	 _Type.GetElementType();

			var tempEnum = _Data.GetEnumerator();
			while (tempEnum.MoveNext())
			{
				_append_Collection(_Ptr, ref _Offset, tempEnum.Current as System.Collections.ICollection, tmpType);
			}
		}
		else if (typeof(string).Equals(_Type))
		{
			var tempEnum = _Data.GetEnumerator();
			while (tempEnum.MoveNext())
			{
				_append<string>(_Ptr, ref _Offset, tempEnum.Current as string);
			}
		}
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Type))
		{
			Type[]	tempType	 = _Type.GetGenericArguments();

			var tempEnum = _Data.GetEnumerator();
			while (tempEnum.MoveNext())
			{
				_append_Dictionary(_Ptr, ref _Offset, tempEnum.Current as System.Collections.IDictionary, tempType);
			}
		}
		else if (typeof(System.Collections.ICollection).IsAssignableFrom(_Type))
		{
			Type tmpType =		 _Type.GetGenericArguments()[0];

			var tempEnum = _Data.GetEnumerator();
			while (tempEnum.MoveNext())
			{
				_append_Collection(_Ptr, ref _Offset, tempEnum.Current as System.Collections.ICollection, tmpType);
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

			// Throw) 
			throw	new Exception();
		}
	}

// 5) extract관련(뽑아내기)
	public T extract<T>()
	{
		// 1) [버퍼]를 고정(Pinned) 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_Buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr	 = (long)pinnedArray.AddrOfPinnedObject()+m_iOffset;
		long Offset	 = 0;

		try
		{
			Type tmp = typeof(T);

			T	temp;

			if (tmp.IsPrimitive)
			{
				temp = _extract_Primitive<T>(ptr, ref Offset);
			}
			else if (tmp.IsValueType)
			{
				if(typeof(DateTime).Equals(tmp))
				{
					temp	 = (T)Convert.ChangeType(_extract_datetime(ptr, ref Offset), tmp);
				}
				else
				{
					temp = (T)Convert.ChangeType(_extract_Value(ptr, ref Offset, tmp), tmp);
				}
			}
			else if (typeof(string).Equals(tmp))
			{
				temp = (T)Convert.ChangeType(_extract_string(ptr, ref Offset), tmp);
			}
			else if (tmp.IsArray)
			{
				temp = (T)Convert.ChangeType(_extract_array(ptr, ref Offset, tmp.GetElementType()), tmp);
			}
			// Case) Dictionary
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(tmp))
			{
				temp	 = (T)Convert.ChangeType(_extract_DictionaryX(ptr, ref Offset, tmp, tmp.GetGenericArguments()), tmp);
			}
			else if(typeof(System.Collections.IList).IsAssignableFrom(tmp))
			{
				// return) 
				temp	 = (T)Convert.ChangeType(_extract_ListX(ptr, ref Offset, tmp, tmp.GetGenericArguments()[0]), tmp);
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
			
			// 5) [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// 6) Buffer Pointer를 증가시킨다.
			m_iCount	-= (int)Offset;
			m_iOffset	+= (int)Offset;

			// Return)
			return	temp;
		}
		catch(Exception e)
		{
			// Trace) 
			Debug.WriteLine("CGD.buffer extract<T>(): " + e.Message);

			// - [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// Reraise)
			throw;
		}
	}

	public object extract(Type _Type)
	{
		// 1) [버퍼]를 고정(Pinned) 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_Buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr	 = (long)pinnedArray.AddrOfPinnedObject()+m_iOffset;
		long Offset	 = 0;

		try
		{
			// Declare) 
			object	temp;

			// 3) 
			temp	 = _extract(ptr, ref Offset, _Type);

			// 5) [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// 6) Buffer Pointer를 증가시킨다.
			m_iCount	-= (int)Offset;
			m_iOffset	+= (int)Offset;

			// Return)
			return	temp;
		}
		catch(Exception e)
		{
			// Trace) 
			Debug.WriteLine("CGD.buffer extract<T>(): " + e.Message);

			// - [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// Reraise)
			throw;
		}
	}

	public object _extract(long _Ptr, ref long _Offset, Type _Type)
	{
		// Case) Primitive Type
		if (_Type.IsPrimitive)
		{
			return	_extract_Primitive(_Ptr, ref _Offset, _Type);
		}
		// Case) Value Type
		else if (_Type.IsValueType)
		{
			if(typeof(DateTime).Equals(_Type))
			{
				return	_extract_datetime(_Ptr, ref _Offset);
			}
			else
			{
				return	_extract_Value(_Ptr, ref _Offset, _Type);
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_Type))
		{
			return	_extract_string(_Ptr, ref _Offset);
		}
		// Case) Array
		else if (_Type.IsArray)
		{
			return	_extract_array(_Ptr, ref _Offset, _Type.GetElementType());
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Type))
		{
			// Return)
			return	_extract_DictionaryX(_Ptr, ref _Offset, _Type, _Type.GetGenericArguments());
		}
		else if(typeof(System.Collections.IList).IsAssignableFrom(_Type))
		{
			// return) 
			return _extract_ListX(_Ptr, ref _Offset, _Type, _Type.GetGenericArguments()[0]);
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

			// Throw) 
			throw	new Exception();
		}
	}
	private T _extract_Primitive<T>(long _Ptr, ref long _Offset)
	{
		// Check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_Offset+Marshal.SizeOf(typeof(T)) > m_iCount)
		{
			throw new Exception();
		}

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		T obj = (T)Marshal.PtrToStructure(new IntPtr(_Ptr+_Offset), typeof(T));

		// 2) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_Offset += Marshal.SizeOf(typeof(T));

		// Return) 
		return obj;
	}
	private object _extract_Primitive(long _Ptr, ref long _Offset, Type _Type)
	{
		// Check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_Offset+Marshal.SizeOf(_Type) > m_iCount)
		{
			throw new Exception();
		}

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		object obj = Marshal.PtrToStructure(new IntPtr(_Ptr+_Offset), _Type);

		// 2) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_Offset += Marshal.SizeOf(_Type);

		// Return) 
		return obj;
	}
	private object _extract_Value(long _Ptr, ref long _Offset, Type _Type)
	{
		// 1) Field 정보를 얻는다.
		var tempFields = _Type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		// 2) 객체를 생성한다.
		object	tempObject	 = Activator.CreateInstance(_Type);

		// 3) 각 Field값을 읽어 써넣는다.
		foreach (var iter in tempFields)
		{
			iter.SetValue(tempObject, _extract(_Ptr, ref _Offset, iter.FieldType));
		}

		// Return) 
		return	tempObject;
	}

	private DateTime _extract_datetime(long _Ptr, ref long _Offset)
	{
		// 1) 값을 읽어들인다.
		uint	tempyearmonth		 = _extract_Primitive<uint>(_Ptr, ref _Offset);
		uint	tempDayHourMinSec	 = _extract_Primitive<uint>(_Ptr, ref _Offset);
        int     tempMillisecond      = _extract_Primitive<int>(_Ptr, ref _Offset);

		// 2) 객체를 생성한다.
		DateTime	tempObject	 = new DateTime(
			(int)((tempyearmonth & 0xffff)),		// year
			(int)((tempyearmonth & 0xffff0000)>>16),// month
			(int)(tempDayHourMinSec & 0xff),		// day
			(int)((tempDayHourMinSec >> 8) & 0xff),	// hour
			(int)((tempDayHourMinSec >> 16) & 0xff),// min
			(int)((tempDayHourMinSec >> 24) & 0xff),	// sec
            (int)((tempMillisecond))	// tempMillisecond

		);

		// Return) 
		return	tempObject;
	}

	private string _extract_string(long _Ptr, ref long _Offset)
	{
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
		Debug.Assert(sizeof(short)<=m_iCount);

		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
		if(sizeof(short)>m_iCount) 
		{
			throw new Exception();
		}

		// 1) String의 길이를 얻는다.
		int lengthString = (int)(short)Marshal.PtrToStructure(new IntPtr(_Ptr+_Offset), typeof(short));

		// Check) length가 -1이면 null을 리턴한다.
		if(lengthString==-1)
		{
			_Offset	+= sizeof(short);
			return	null;
		}

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
		Debug.Assert((lengthString*sizeof(char)+sizeof(short))<=m_iCount);

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
		if((lengthString*sizeof(char)+sizeof(short))>m_iCount) 
		{
			throw new Exception();
		}

		// 2) 복사할 [문자열_길이]를 구한다. (NULL문자는 뺀다.)
		int sizeCopy = (lengthString - 1) * sizeof(char);

		// Check) [문자열]의 제일 끝이 NULL인지 확인한다.
		if(m_Buffer[m_iOffset+_Offset+sizeof(short)+sizeCopy+0]!=0 ||m_Buffer[m_iOffset+_Offset+sizeof(short)+sizeCopy+1]!=0) 
		{
			throw new Exception();
		}

		// 3) [문자열]을 복사한다.
		char[] charTemp = new char[lengthString - 1];
		System.Buffer.BlockCopy(m_Buffer, m_iOffset+(int)_Offset + sizeof(short), charTemp, 0, sizeCopy);

		// 4) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
		_Offset	+= (sizeof(short) + sizeCopy + sizeof(char));

		// 5) [string]로 변환해 최종 리턴한다.
		return	new string(charTemp);
	}
	private Array _extract_array(long _Ptr, ref long _Offset, Type _Type)
	{
		// 1) [데이터 갯수]를 읽어들인다.
		short iCount = _extract_Primitive<short>(_Ptr, ref _Offset);

		// Check) length가 -1이면 null을 리턴한다.
		if (iCount == -1)
		{
			return null;
		}

		Array	tempArray	 = System.Array.CreateInstance(_Type, iCount);

		// Case) Primitive Type
		if (_Type.IsPrimitive)
		{
			for (int i=0; i<iCount; ++i)
			{
				tempArray.SetValue(_extract_Primitive(_Ptr, ref _Offset, _Type), i);
			}
		}
		// Case) Value Type
		else if (_Type.IsValueType)
		{
			if(typeof(DateTime).Equals(_Type))
			{
				for (int i=0; i<iCount; ++i)
				{
					tempArray.SetValue(_extract_datetime(_Ptr, ref _Offset), i);
				}
			}
			else
			{
				for (int i=0; i<iCount; ++i)
				{
					tempArray.SetValue(_extract_Value(_Ptr, ref _Offset, _Type), i);
				}
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_Type))
		{
			for (int i=0; i<iCount; ++i)
			{
				tempArray.SetValue(_extract_string(_Ptr, ref _Offset), i);
			}
		}
		// Case) Array
		else if (_Type.IsArray)
		{
			for (int i=0; i<iCount; ++i)
			{
				tempArray.SetValue(_extract_array(_Ptr, ref _Offset, _Type.GetElementType()), i);
			}
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_Type))
		{
			var	tempType	 = _Type.GetGenericArguments();

			for (int i=0; i<iCount; ++i)
			{
				// - [데이터 갯수]를 읽어들인다.
				short countItem = _extract_Primitive<short>(_Ptr, ref _Offset);

				// Check) iCount가 -1이면 null을 리턴한다.
				if (countItem == -1)
					continue;

				object tempObject = Activator.CreateInstance(_Type);
				_extract_Dictionary(_Ptr, ref _Offset, tempObject as System.Collections.IDictionary, countItem, tempType);
				tempArray.SetValue(tempObject, i);
			}
		}
		else if(typeof(System.Collections.IList).IsAssignableFrom(_Type))
		{
			var	tempType	 = _Type.GetGenericArguments()[0];

			for (int i=0; i<iCount; ++i)
			{
				// - [데이터 갯수]를 읽어들인다.
				short countItem = _extract_Primitive<short>(_Ptr, ref _Offset);

				// Check) iCount가 -1이면 null을 리턴한다.
				if(countItem==-1)
					continue;

				object tempObject = Activator.CreateInstance(_Type);
				_extract_List(_Ptr, ref _Offset, tempObject as System.Collections.IList, countItem, tempType);
				tempArray.SetValue(tempObject, i);
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

			// Throw) 
			throw	new Exception();
		}

		return tempArray;
	}

	private object _extract_DictionaryX(long _Ptr, ref long _Offset, Type _TypeCreate, Type[] _Types) 
	{
		// 1) [데이터 갯수]를 읽어들인다.
		short countItem = _extract_Primitive<short>(_Ptr, ref _Offset);

		// Check) iCount가 -1이면 null을 리턴한다.
		if (countItem != -1)
		{
			// - Instance를 생성한다.
			object	objValue = Activator.CreateInstance(_TypeCreate);

			// - Dictionary 내용을 읽어들인다.
			_extract_Dictionary(_Ptr, ref _Offset, objValue as System.Collections.IDictionary, countItem, _Types);

			// Return) 생성된 객체를 Return한다.
			return	objValue;
		}
		else
		{
			return	null;
		}
	}


	private void _extract_Dictionary(long _Ptr, ref long _Offset, System.Collections.IDictionary _Data, short _Count, Type[] _Types) 
	{
		// 1) [데이터]들을 써넣는다.
		if (_Types[0].IsPrimitive)
		{
			if (_Types[1].IsPrimitive)
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Primitive(_Ptr, ref _Offset, _Types[0]),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				if (typeof(DateTime).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_Primitive(_Ptr, ref _Offset, _Types[0]),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_Primitive(_Ptr, ref _Offset, _Types[0]),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Primitive(_Ptr, ref _Offset, _Types[0]),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Primitive(_Ptr, ref _Offset, _Types[0]),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_Primitive(_Ptr, ref _Offset, _Types[0]);
					object	objValue = _extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1);

					_Data.Add(objKey, objValue);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_Primitive(_Ptr, ref _Offset, _Types[0]);
					object	objValue = _extract_ListX(_Ptr, ref _Offset, _Types[0], tempType1);

					_Data.Add(objKey, objValue);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		// Case) Value Type
		else if (_Types[0].IsValueType)
		{
			if (_Types[1].IsPrimitive)
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Value(_Ptr, ref _Offset, _Types[0]),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				if (typeof(string).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_Value(_Ptr, ref _Offset, _Types[0]),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_Value(_Ptr, ref _Offset, _Types[0]),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Value(_Ptr, ref _Offset, _Types[0]),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_Value(_Ptr, ref _Offset, _Types[0]),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_Value(_Ptr, ref _Offset, _Types[0]);
					object objValue = _extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1);

					_Data.Add(objKey, objValue);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_Value(_Ptr, ref _Offset, _Types[0]);
					object	objValue = _extract_ListX(_Ptr, ref _Offset, _Types[1], tempType1);
		
					_Data.Add(objKey, objValue);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_string(_Ptr, ref _Offset),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				if(typeof(DateTime).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_string(_Ptr, ref _Offset),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_string(_Ptr, ref _Offset),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_string(_Ptr, ref _Offset),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_string(_Ptr, ref _Offset),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_string(_Ptr, ref _Offset);
					object objValue = _extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1);

					_Data.Add(objKey, objValue);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_string(_Ptr, ref _Offset);
					object	objValue = _extract_ListX(_Ptr, ref _Offset, _Types[1], tempType1);

					_Data.Add(objKey, objValue);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		// Case) Array
		else if (_Types[0].IsArray)
		{
			if (_Types[1].IsPrimitive)
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_array(_Ptr, ref _Offset, tempType0),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				if(typeof(DateTime).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_array(_Ptr, ref _Offset, tempType0),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{

					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_array(_Ptr, ref _Offset, tempType0),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_array(_Ptr, ref _Offset, tempType0),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_array(_Ptr, ref _Offset, tempType0),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_array(_Ptr, ref _Offset, tempType0);
					object objValue =  _extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1);;

					_Data.Add(objKey, objValue);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					object	objKey	 = _extract_array(_Ptr, ref _Offset, tempType0);
					object	objValue = _extract_ListX(_Ptr, ref _Offset, _Types[1], tempType1);
		
					_Data.Add(objKey, objValue);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		// Case) Dictionary
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				var	tempType0	 = _Types[0].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				var	tempType0	 = _Types[0].GetGenericArguments();
				if(typeof(DateTime).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType0	 = _Types[0].GetGenericArguments();
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments();
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1)
					);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments();
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					// - 데이터를 추가한다.
					_Data.Add(	_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_DictionaryX(_Ptr, ref _Offset, _Types[0], tempType0)
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[0]))
		{
			if (_Types[1].IsPrimitive)
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_Primitive(_Ptr, ref _Offset, _Types[1])
					);
				}
			}
			// Case) Value Type
			else if (_Types[1].IsValueType)
			{
				var tempType0 = _Types[0].GetGenericArguments()[0];

				if(typeof(DateTime).Equals(_Types[1]))
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
									_extract_datetime(_Ptr, ref _Offset)
						);
					}
				}
				else
				{
					for (; _Count > 0; --_Count)
					{
						_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
									_extract_Value(_Ptr, ref _Offset, _Types[1])
						);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_string(_Ptr, ref _Offset)
					);
				}
			}
			// Case) Array
			else if (_Types[1].IsArray)
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetElementType();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_array(_Ptr, ref _Offset, tempType1)
					);
				}
			}

			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					// - 데이터를 추가한다.
					_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_DictionaryX(_Ptr, ref _Offset, _Types[1], tempType1)
					);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Types[1]))
			{
				var	tempType0	 = _Types[0].GetGenericArguments()[0];
				var	tempType1	 = _Types[1].GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(	_extract_ListX(_Ptr, ref _Offset, _Types[0], tempType0),
								_extract_ListX(_Ptr, ref _Offset, _Types[1], tempType1)
					);
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
				// Throw) 
				throw	new Exception();
			}
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");
		
			// Throw) 
			throw	new Exception();
		}
	}

	private object _extract_ListX(long _Ptr, ref long _Offset, Type _TypeCreate, Type _Type)
	{
		// - [데이터 갯수]를 읽어들인다.
		short countItem = _extract_Primitive<short>(_Ptr, ref _Offset);

		// Check) iCount가 -1이면 null을 리턴한다.
		if (countItem != -1)
		{
			object	objValue = Activator.CreateInstance(_TypeCreate);

			_extract_List(_Ptr, ref _Offset, objValue as System.Collections.IList, countItem, _Type);

			return objValue;
		}
		else
		{
			return	null;
		}
	}
	private void _extract_List(long _Ptr, ref long _Offset, System.Collections.IList _Data, short _Count, Type _Type)
	{
		// 2) [데이터]들을 써넣는다.
		if (_Type.IsPrimitive)
		{
			for (; _Count > 0; --_Count)
			{
				_Data.Add(_extract_Primitive(_Ptr, ref _Offset, _Type));
			}
		}
		// Case) Value Type
		else if (_Type.IsValueType)
		{
			if(typeof(DateTime).Equals(_Type))
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(_extract_datetime(_Ptr, ref _Offset));
				}
			}
			else
			{
				for (; _Count > 0; --_Count)
				{
					_Data.Add(_extract_Value(_Ptr, ref _Offset, _Type));
				}
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_Type))
		{
			for (; _Count > 0; --_Count)
			{
				_Data.Add(_extract_string(_Ptr, ref _Offset));
			}
		}
		// Case) Array
		else if (_Type.IsArray)
		{
			var	tempType	 = _Type.GetElementType();

			for (; _Count > 0; --_Count)
			{
				_Data.Add(_extract_array(_Ptr, ref _Offset, tempType));
			}
		}
		// Case) Dictionary
		else
		{
			if (typeof(System.Collections.IDictionary).IsAssignableFrom(_Type))
			{
				var	tempType	 = _Type.GetGenericArguments();

				for (; _Count > 0; --_Count)
				{
					_Data.Add(_extract_DictionaryX(_Ptr, ref _Offset, _Type, tempType));
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_Type))
			{
				var	tempType	 = _Type.GetGenericArguments()[0];

				for (; _Count > 0; --_Count)
				{
					_Data.Add(_extract_ListX(_Ptr, ref _Offset, _Type, tempType));
				}
			}
			else
			{
				// Check) 지원되지 않는 Type이다.
				Debug.Assert(false, "[CGD.buffer] Not Supported TYPE.");

				// Throw) 
				throw	new Exception();
			}
		}
	}

	public void		extract_skip(int _Amount)									{ m_iOffset+=_Amount; m_iCount-=_Amount;}
	public char		extract_char()												{ Debug.Assert(sizeof(char)<=m_iCount); if(sizeof(char)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(char); m_iCount-=sizeof(char); return (char)m_Buffer[iPosition];}
	public sbyte	extract_sbyte()												{ Debug.Assert(sizeof(sbyte)<=m_iCount); if(sizeof(sbyte)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(sbyte); m_iCount-=sizeof(sbyte); return (sbyte)m_Buffer[iPosition];}
	public byte		extract_byte()												{ Debug.Assert(sizeof(byte)<=m_iCount); if(sizeof(byte)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(byte); m_iCount-=sizeof(byte); return m_Buffer[iPosition];}
	public short	extract_short()												{ Debug.Assert(sizeof(short)<=m_iCount); if(sizeof(short)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(short); m_iCount-=sizeof(short); return BitConverter.ToInt16(m_Buffer, iPosition);}
	public ushort	extract_ushort()											{ Debug.Assert(sizeof(ushort)<=m_iCount); if(sizeof(ushort)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(ushort); m_iCount-=sizeof(ushort); return BitConverter.ToUInt16(m_Buffer, iPosition);}
	public int		extract_int()												{ Debug.Assert(sizeof(int)<=m_iCount); if(sizeof(int)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(int); m_iCount-=sizeof(int); return BitConverter.ToInt32(m_Buffer, iPosition);}
	public uint		extract_uint()												{ Debug.Assert(sizeof(uint)<=m_iCount); if(sizeof(uint)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(uint); m_iCount-=sizeof(uint); return BitConverter.ToUInt32(m_Buffer, iPosition);}
	public long		extract_long()												{ Debug.Assert(sizeof(long)<=m_iCount); if(sizeof(long)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(long); m_iCount-=sizeof(long); return BitConverter.ToInt64(m_Buffer, iPosition);}
	public ulong	extract_ulong()												{ Debug.Assert(sizeof(ulong)<=m_iCount); if(sizeof(ulong)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(ulong); m_iCount-=sizeof(ulong); return BitConverter.ToUInt64(m_Buffer, iPosition);}
	public float	extract_float()												{ Debug.Assert(sizeof(float)<=m_iCount); if(sizeof(float)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(float); m_iCount-=sizeof(float); return BitConverter.ToSingle(m_Buffer, iPosition);}
	public double	extract_double()											{ Debug.Assert(sizeof(double)<=m_iCount); if(sizeof(double)>m_iCount) throw new Exception(); int iPosition=m_iOffset; m_iOffset+=sizeof(double); m_iCount-=sizeof(double); return BitConverter.ToDouble(m_Buffer, iPosition);}
	public string	extract_string()											{ return extract<string>();}

// 3) set_front (값 써넣기)
    public void		set_front<T>(char _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(char))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(sbyte _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(sbyte))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(byte _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(byte))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(short _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(short))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(ushort _Data, int _Offset=0) where T:struct	{ if(typeof(T)==typeof(ushort)) { set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(int _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(int))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(uint _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(uint))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(long _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(long))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(ulong _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(ulong))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(float _Data, int _Offset=0) where T:struct		{ if(typeof(T)==typeof(float))	{ set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}
	public void		set_front<T>(double _Data, int _Offset=0) where T:struct	{ if(typeof(T)==typeof(double)) { set_front(_Data, _Offset);} else { set_front(Convert.ChangeType(_Data, typeof(T)), _Offset);}}

	public void		set_front(byte[] _Data, int _Offset_src, int _Count, int _Offset=0) { Debug.Assert((m_iOffset+m_iCount+_Count)<=m_Buffer.Length); System.Buffer.BlockCopy(_Data, _Offset_src, m_Buffer, m_iOffset+_Offset, _Count);}
	public void		set_front(buffer _Data, int _Offset = 0)					{ Debug.Assert((m_iOffset + m_iCount + _Data.m_iCount) <= m_Buffer.Length); System.Buffer.BlockCopy(_Data.m_Buffer, _Data.m_iOffset, m_Buffer, m_iOffset + _Offset, _Data.m_iCount);}
    public void		set_front(char _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(char))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(sbyte _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(sbyte))<=m_Buffer.Length);		m_Buffer[m_iOffset+_Offset]=(byte)_Data;}
	public void		set_front(byte _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(byte))<=m_Buffer.Length);		m_Buffer[m_iOffset+_Offset]=_Data;}
	public void		set_front(short _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(short))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(ushort _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(ushort))<=m_Buffer.Length);	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(int _Data, int _Offset=0)							{ Debug.Assert((m_iOffset+_Offset+sizeof(int))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(uint _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(uint))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(long _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(long))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(ulong _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(ulong))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(float _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(float))<=m_Buffer.Length);		BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(double _Data, int _Offset=0)						{ Debug.Assert((m_iOffset+_Offset+sizeof(double))<=m_Buffer.Length);	BitConverter.GetBytes(_Data).CopyTo(m_Buffer, m_iOffset+_Offset);}
	public void		set_front(object _Data, int _Offset=0)
					{
						buffer	temp	 = new buffer(m_Buffer, m_iOffset+_Offset, 0);
						temp.append(_Data);
					}

// 4) get_front( 값 읽기)
	public T		get_front<T>(int _Offset = 0)								{ buffer temp = new buffer(m_Buffer, m_iOffset+_Offset, m_iCount-_Offset); return temp.extract<T>();}
	public void		get_front<T>(ref T _Data, int _Offset = 0)					{ _Data = get_front<T>(_Offset); }
	public void		get_front<T>(ref char _Data, int _Offset=0)					{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_char(_Offset); }
	public void		get_front<T>(ref sbyte _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_sbyte(_Offset); }
    public void		get_front<T>(ref byte _Data, int _Offset=0)					{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_byte(_Offset); }
    public void		get_front<T>(ref short _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_short(_Offset); }
    public void		get_front<T>(ref ushort _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_ushort(_Offset); }
    public void		get_front<T>(ref int _Data, int _Offset=0)					{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_int(_Offset); }
    public void		get_front<T>(ref uint _Data, int _Offset=0)					{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_uint(_Offset); }
    public void		get_front<T>(ref long _Data, int _Offset=0)					{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_long(_Offset); }
    public void		get_front<T>(ref ulong _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_ulong(_Offset); }
    public void		get_front<T>(ref float _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_float(_Offset); }
    public void		get_front<T>(ref double _Data, int _Offset=0)				{ Debug.Assert(Marshal.SizeOf(typeof(T))==Marshal.SizeOf(_Data), "[CGD.buffer] parameter is different with T (Must be casted as T)"); _Data = get_front_double(_Offset); }

    public char		get_front_char(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(char))<=m_Buffer.Length); return BitConverter.ToChar(m_Buffer, m_iOffset+_Offset);}
	public sbyte	get_front_sbyte(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(sbyte))<=m_Buffer.Length); return (sbyte)m_Buffer[m_iOffset+_Offset];}
	public byte		get_front_byte(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(byte))<=m_Buffer.Length); return m_Buffer[m_iOffset+_Offset]; }
	public short	get_front_short(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(short))<=m_Buffer.Length); return BitConverter.ToInt16(m_Buffer, m_iOffset+_Offset);}
	public ushort	get_front_ushort(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(ushort))<=m_Buffer.Length); return BitConverter.ToUInt16(m_Buffer, m_iOffset+_Offset);}
	public int		get_front_int(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(int))<=m_Buffer.Length); return BitConverter.ToInt32(m_Buffer, m_iOffset+_Offset);}
	public uint		get_front_uint(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(uint))<=m_Buffer.Length); return BitConverter.ToUInt32(m_Buffer, m_iOffset+_Offset);}
	public long		get_front_long(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(long))<=m_Buffer.Length); return BitConverter.ToInt64(m_Buffer, m_iOffset+_Offset);}
	public ulong	get_front_ulong(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(ulong))<=m_Buffer.Length); return BitConverter.ToUInt64(m_Buffer, m_iOffset+_Offset);}
	public float	get_front_float(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(float))<=m_Buffer.Length); return BitConverter.ToSingle(m_Buffer, m_iOffset+_Offset);}
	public double	get_front_double(int _Offset=0)								{ Debug.Assert((_Offset+sizeof(double))<=m_Buffer.Length); return BitConverter.ToDouble(m_Buffer, m_iOffset+_Offset);}
	public void		get_front_array(byte[] _Data, int _Offset_src, int _Count, int _Offset=0)	{ Debug.Assert((m_iOffset+m_iCount+_Data.Length)<=m_Buffer.Length); System.Buffer.BlockCopy(m_Buffer, m_iOffset+_Offset, _Data, _Offset_src, _Count);}
	public void		get_front_buffer(buffer _Data, int _Offset = 0)				{ Debug.Assert((m_iOffset + m_iCount + _Data.m_iCount) <= m_Buffer.Length); System.Buffer.BlockCopy(m_Buffer, m_iOffset + _Offset, _Data.m_Buffer, _Data.m_iOffset, _Data.m_iCount); }
	public uint		get_front_CRC()												{ return	0;}

		
// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
	// 1) Buffer
	private byte[]	m_Buffer;

	// 2) Buffer중 시작 위치
	private int		m_iOffset;

	// 3) 사용 길이 (m_iOffset부터 Buffer중 사용하는 끝까지의 길이)
	private int		m_iCount;
}


}
