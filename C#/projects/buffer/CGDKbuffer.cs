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
			this.m_Offset=_offset;
		}
		public Serialize(long _offset, string _message) : base(_message)
		{
			this.m_Offset=_offset;
		}

		public long offset	{ get {return this.m_Offset;}}

		private long m_Offset;
	}
}

public struct buffer
{
// constructor/destructor) 
#if NET
	public buffer(byte[]? _buffer, int _offset = 0, int _count = 0)
#else
	public buffer(byte[] _buffer, int _offset = 0, int _count = 0)
#endif
	{
		this.m_buffer = _buffer;
		this.m_offset = _offset;
		this.m_count = _count;
	}
	public buffer(buffer _buffer)
	{
		this.m_buffer = _buffer.m_buffer;
		this.m_offset = _buffer.m_offset;
		this.m_count = _buffer.m_count;
	}
	public buffer(int _Size)
	{
		this.m_buffer = new byte[_Size];
		this.m_offset = 0;
		this.m_count = 0;
	}

	public buffer clone()
	{
		// 1) 새로운 버퍼를 생성한다.
		byte[] temp = new byte[capacity];

		// 2) [문자열]을 복사해 넣는다.
		if(this.m_buffer != null)
			System.Buffer.BlockCopy(this.m_buffer, 0, temp, 0, capacity);

		// 3) 적용한다.
		return new buffer(temp, m_offset, m_count);
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
		this.m_buffer = new byte[_Size];
		this.m_offset = 0;
		this.m_count = 0;
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
		this.m_buffer = _buffer;
		this.m_offset = _offset;
		this.m_count = _length;
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
		this.m_buffer = _buffer;
		this.m_offset = _offset;
		this.m_count = _buffer.Length-_offset;
	}
#if NET
	public byte[]?	clear()
#else
	public byte[] clear()
#endif
	{
		// 1) 임시로 보관
		var temp = this.m_buffer;

		// 2) Reset한다.
		this.m_buffer = null;
		this.m_offset = 0;
		this.m_count = 0;

		// 3) 저장되어 있던 byte[]를 리턴해 준다.
		return temp;
	}

// 2) Basic operations
	public bool		empty()														{ return this.m_buffer==null;}
	public int		get_remained()												{ return (this.m_buffer!=null) ? (this.m_buffer.Length - this.m_offset - this.m_count) : 0; }

	public int		capacity
	{
			get { return (this.m_buffer!=null) ? this.m_buffer.Length : 0; }
	}

		// - for C++ User
#if NET
	public byte[]?	data														{ get { return this.m_buffer;} set { this.m_buffer = value;}}
#else
	public byte[]	data														{ get { return this.m_buffer;} set { this.m_buffer = value;}}
#endif
	public int		offset														{ get { return this.m_offset;} set { this.m_offset = value;}}
	public int		size														{ get { return this.m_count;} set { this.m_count = value;}}
																				  
	// - for C# User															  
#if NET
	public byte[]?	Buffer														{ get { return this.m_buffer; } set { this.m_buffer = value; } }
	public byte[]?	Array														{ get { return this.m_buffer; } set { this.m_buffer = value; } }
#else
	public byte[]	Buffer														{ get { return this.m_buffer; } set { this.m_buffer = value; } }
	public byte[]	Array														{ get { return this.m_buffer; } set { this.m_buffer = value; } }
#endif

	public int		Offset														{ get { return this.m_offset;}	set { this.m_offset = value;}}
	public int		Count														{ get { return this.m_count;} set { this.m_count = value;}}

	public static buffer operator +(buffer _lhs, int _rhs)						
	{
		// check) 
		Debug.Assert(_lhs.m_buffer != null && _rhs<=_lhs.Count); 

		// check)
		if(_lhs.Array == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if(_rhs > _lhs.Count)
			throw new System.OverflowException("buffer overflow");

		// 1) create
		return new buffer(_lhs.Array, _lhs.offset + _rhs, _lhs.Count - _rhs);
	}
	public static buffer operator -(buffer _lhs, int _rhs)
	{
		// check) 
		Debug.Assert(_lhs.m_buffer != null && _lhs.offset >= _rhs && _rhs <= (_lhs.capacity - _lhs.Count)); 

		// check)
		if(_lhs.Array == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if(_lhs.offset < _rhs || _rhs > (_lhs.capacity - _lhs.Count))
			throw new System.OverflowException("buffer overflow");

		// 1) create
		return new buffer(_lhs.Array, _lhs.offset - _rhs, _lhs.Count + _rhs);
	}
	public static buffer operator ^(buffer _lhs, int _rhs)		
	{
		// check) 
		Debug.Assert(_lhs.m_buffer != null && _rhs <= _lhs.capacity); 

		// check)
		if(_lhs.Array == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if(_rhs > _lhs.capacity)
			throw new System.OverflowException("buffer overflow");

		// 1) create 
		return new buffer(_lhs.Array, _lhs.offset, _rhs);
	}
	public static implicit operator ArraySegment<byte>(buffer _rhs)
	{
		// check) 
		Debug.Assert(_rhs.Array != null); 
		
		// 1) create 
		return new ArraySegment<byte>(_rhs.Array, _rhs.offset, _rhs.Count);
	}
	public static explicit operator buffer(ArraySegment<byte> _rhs)
	{
		// 1) create 
		return new buffer(_rhs.Array, _rhs.Offset, _rhs.Count);
	}

// 3) append(붙이기)
	public void		append_skip				(int _amount)						{ Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= _amount);	this.m_count += _amount; }
	public void		append					(buffer _object)					{ this._append_buffer(_object);}
	public void		append					(char _object)						
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(char));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(char))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);

		// 2) add size
		this.m_count += sizeof(char);
	}
	public void		append					(sbyte _object)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(sbyte));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(sbyte))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) copy
		this.m_buffer[this.m_offset+this.m_count]=(byte)_object; 
			
		// 2) add size
		this.m_count+=sizeof(sbyte); 
	}
	public void		append					(byte _object)						
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(byte));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(byte))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		this.m_buffer[this.m_offset + this.m_count] = _object; 
			
		// 2) add size
		this.m_count += sizeof(byte); 
	}
	public void		append					(short _object)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(short)); 

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(short))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 
		
		// 2) add size
		this.m_count += sizeof(short); 
	}
	public void		append					(ushort _object)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(ushort));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(ushort))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 
			
		// 2) add size
		this.m_count += sizeof(ushort); 
	}
	public void		append					(int _object)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(int));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(int))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);

		// 2) add size
		this.m_count += sizeof(int); 
	}
	public void		append					(uint _object)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(uint));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(uint))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 
			
		// 2) add size
		this.m_count += sizeof(uint);
	}
	public void		append					(long _object)						
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(long));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(long))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 

		// 2) add size
		this.m_count += sizeof(long); 
	}
	public void		append					(ulong _object)
	{
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(ulong));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(ulong))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 
			
		// 2) add size
		this.m_count += sizeof(ulong);
	}
	public void		append					(float _object)						
	{
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(float));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(float))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 
			
		// 2) add size
		this.m_count += sizeof(float); 
	}
	public void		append					(double _object)
	{
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(double));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(double))
			throw new System.OverflowException("buffer overflow");
	#endif
			
		// 1) copy 
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count); 

		// 2) add size
		this.m_count += sizeof(double);
	}
	public void		append					(DateTime _object)
	{
		this.append(_object.Ticks);
	}

	public void		append<T>()													
	{
		// 1) make temporary object
		var temp = default(T);

		// check) 
		Debug.Assert(temp != null);

		// 2) append
		this.append<T>(temp);
	}
	public unsafe void		append<T>(char _object) where T : unmanaged
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_buffer.Length-this.m_offset-this.m_count)>=sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) write 
		if (type == typeof(char))
		{ 
			// - copy
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);

			// - add count
			this.m_count += sizeof(T);
		}
		else
		{ 
			// - [버퍼] Pinned 시킨다.
			GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

			// - [버퍼_포인터]를 얻는다.
			var ptr = pinnedArray.AddrOfPinnedObject();

			try
			{
				// - casting
				object temp = Convert.ChangeType(_object, type);

				// - write
				Marshal.StructureToPtr(temp, ptr, false);

				// - Pinned된 [버퍼]를 Free한다.
				pinnedArray.Free();

				// - add count
				this.m_count += sizeof(T);
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

	}
	private unsafe void append_primitive(object _object, Type _type)
		{
		// - [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// - [버퍼_포인터]를 얻는다.
		var ptr = pinnedArray.AddrOfPinnedObject();

		try
		{
			// - casting
			object temp = Convert.ChangeType(_object, _type);

			// - write
			Marshal.StructureToPtr(temp, ptr, false);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();
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

	public unsafe void append<T>				(sbyte _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(sbyte))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void append<T>				(byte _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");

		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(byte))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(short _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");

		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(short))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(ushort _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");

		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(ushort))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(int _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");

		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(ushort))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(uint _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(uint))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(long _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(long))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void append<T>				(ulong _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(ulong))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void append<T>				(float _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(float))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public unsafe void		append<T>				(double _object) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(double))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + this.m_count);
		else
			this.append_primitive(_object, type);

		// 3) add count
		this.m_count += sizeof(T);
	}

	public void		append<T>				(string _object) where T: System.IComparable<string>
	{
	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long offset = this.m_offset + this.m_count;

		try
		{
			// 3) 추가한다.
			this._append<string>(ptr, ref offset, _object);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			this.m_count = (int)offset - this.m_offset;
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
	public void		append<T>				(ICollection<T> _object) where T: struct
	{
	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long offset = this.m_offset + this.m_count;

		try
		{
			// 3) 추가한다.
			this._append_Collection(ptr, ref offset, _object as System.Collections.ICollection, typeof(T));

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			this.m_count = (int)offset;
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
#if NET
	public void		append<K,V>				(Dictionary<K,V> _object) where K:notnull
#else
	public void		append<K,V>				(Dictionary<K,V> _object)
#endif

	{
	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
	#endif

		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long offset = this.m_offset + this.m_count;

		try
		{
			// 3) 추가한다.
			this._append_Dictionary(ptr, ref offset, _object as System.Collections.IDictionary, _object.GetType().GetGenericArguments());

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			this.m_count = (int)offset;
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
		// check) 
		Debug.Assert(this.m_buffer != null);

#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
#endif

		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long offset = this.m_offset + this.m_count;

		try
		{
			Type tmp = _object.GetType();
                
			if (tmp.IsPrimitive)
			{
				Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)");

				Marshal.StructureToPtr(_object, new IntPtr(ptr + offset), false);

				offset += Marshal.SizeOf(tmp);
			}
			else if (tmp.IsEnum)
			{
				var	type_enum = tmp.GetFields()[0].FieldType;

				Marshal.StructureToPtr(Convert.ChangeType(_object, type_enum), new IntPtr(ptr + offset), false);

				offset += Marshal.SizeOf(type_enum);
			}
			else if (tmp.IsValueType)
			{
				if(typeof(DateTime).Equals(tmp))
				{
					this._append_datetime(ptr, ref offset, _object);
				}
				else if(typeof(CGDK.buffer).Equals(tmp))
				{
					this._append_buffer(ptr, ref offset, (buffer)_object);
				}
				else
				{
					this._append_struct(ptr, ref offset, _object);
				}
			}
			else if (tmp.IsArray)
			{
				this._append_Collection(ptr, ref offset, _object as System.Collections.ICollection, _object.GetType().GetElementType());
			}
			else if (typeof(string).Equals(tmp))
			{
                this._append<string>(ptr, ref offset, _object as string);
			}
			else
			{
				var temp_object = _object as System.Collections.IDictionary;

				if (temp_object != null)
				{
					this._append_Dictionary(ptr, ref offset, temp_object, tmp.GetGenericArguments());
				}
				else
				{
					var tempObject2 = _object as System.Collections.ICollection;

					if (tempObject2 != null)
					{
						this._append_Collection(ptr, ref offset, tempObject2, _object.GetType().GetGenericArguments()[0]);
						return;
					}
					else if (tmp.IsClass)
					{
						this._append_class(ptr, ref offset, _object);
					}
					else
					{
						this._append_struct(ptr, ref offset, _object);
					}
				}
			}

			// 5) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			this.m_count = (int)offset;
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
		// check)
		Debug.Assert(this.m_buffer != null);

#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");
#endif

		// 1) [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject();
		long offset = this.m_offset + this.m_count;

		try
		{
			// Check) null 일 경우 -1만 쓰고 끝냄
			if (_object == null)
			{
				this.append((int) -1);
				return;
			}

			// 3) 추가한다.
			this._append(ptr, ref offset, _object);

			// 4) Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();

			// 5) 크기차를 구한다.
			this.m_count = (int)offset - this.m_offset;
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
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= _count);

#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < _count)
			throw new System.OverflowException("buffer overflow");
#endif

		// 1) block copy
		System.Buffer.BlockCopy(_buffer, _offset, this.m_buffer, this.m_offset + this.m_count, _count);

		this.m_count += _count; 
	}
	public void		append_text				(string _object)
	{
		// 1) 문자열을 배열로 변경하고 길이를 구한다.
		var temp_array = _object.ToCharArray();
		var iStringLength = temp_array.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert(this.m_buffer != null && (this.m_offset + this.m_count + iStringLength * sizeof(char)) <= this.m_buffer.Length);

#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - this.m_count) < iStringLength)
			throw new System.OverflowException("buffer overflow");
#endif

		// 2) [문자열]을 복사해 넣는다.
		System.Buffer.BlockCopy(temp_array, 0, this.m_buffer, this.m_offset + this.m_count, iStringLength * sizeof(char));

		// 3) [버퍼_길이]를 더해준다.
		this.m_count += (iStringLength * sizeof(char));
	}
	public void		append_text				(ICollection<string> _Collection)
	{
		// 2) 데이터들을 저장한다.
		foreach (var iter in _Collection)
		{
			this.append_text(iter);
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
		// check) sorce
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= (sizeof(ulong) + _object.m_count));

		// check) destination
		Debug.Assert(_object.m_buffer != null );
		
		// 1) append buffer size
		this.append<ulong>((ulong)_object.size);

		// 2) block copy
		System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, this.m_buffer, this.m_offset + this.m_count, _object.m_count); 
		
		this.m_count += _object.m_count; 
	}
	private void	_append_buffer			(long _ptr, ref long _offset, buffer _object)
	{
		// check) 
        Debug.Assert(_object.m_buffer != null);

		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= sizeof(UInt64)+_object.m_count);

		// 1) append buffer size
		Marshal.WriteInt64(new IntPtr(_ptr + _offset), _object.size); _offset += sizeof(UInt64);

		// 2) block copy
		System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, this.m_buffer, (int)_offset, _object.size); _offset+=_object.m_count;
	}
	private void	_append<T>				(long _ptr, ref long _offset, T _object) where T:struct
	{
		Marshal.StructureToPtr(_object, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(typeof(T));
	}
#if NET
	private void	_append<T>				(long _ptr,ref long _offset, string? _object) 
#else
	private void	_append<T>				(long _ptr,ref long _offset, string _object) 
#endif
	{
		// check) 
        Debug.Assert(this.m_buffer != null);

        // Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
        if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.WriteInt32(new IntPtr(_ptr + _offset), (int) -1);
			_offset += sizeof(int);
			return;
		}

		// 1) [문자열]을 [문자배열]로 변경하고 길이를 구한다.
		var temp_array = _object.ToCharArray();
		var	iStringLength = temp_array.Length;

		// Check) 버퍼의 크기가 충분한가 확인한다.
		Debug.Assert((_offset+sizeof(int) +iStringLength*sizeof(char))<=this.m_buffer.Length);

		// 2) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
		Marshal.WriteInt32(new IntPtr(_ptr + _offset), (int)(iStringLength+1));

		// 3) [문자열]을 복사해 넣는다.
		System.Buffer.BlockCopy(temp_array, 0, m_buffer, (int)_offset+sizeof(int), iStringLength*sizeof(char));

		// 4) [버퍼_길이]를 더해준다. (NULL문자열의 길이까지 포함한다.)
		_offset	+= (sizeof(int)+(iStringLength+1)*sizeof(char));

		// 5) [NULL]을 넣는다.
		Marshal.WriteInt16(new IntPtr(_ptr + _offset - sizeof(char)), (int)0);
	}
	private void	_append<T>				(long _ptr, ref long _offset, params string[] _Array)
	{
		foreach (var iter in _Array)
		{
			this._append<string>(_ptr, ref _offset, iter);
		}
	}
	private void	_append					(long _ptr, ref long _offset, object _object)
	{
		// 1) Type을 읽는다.
		Type temp_type = _object.GetType();

		// 2) primitive type일 경우
		if (temp_type.IsPrimitive)
		{
			Marshal.StructureToPtr(_object, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(_object);
		}
		// 3) enum일 경우
		else if(temp_type.IsEnum)
		{
			var	type_enum = temp_type.GetFields()[0].FieldType;

			Marshal.StructureToPtr(Convert.ChangeType(_object, type_enum), new IntPtr(_ptr + _offset), false);

			_offset += Marshal.SizeOf(type_enum);
		}
		// 4) 구조체 일 경우
		else if (temp_type.IsValueType)
		{
			if(typeof(DateTime).Equals(temp_type))
			{
				this._append_datetime(_ptr, ref _offset, _object);
			}
			else if(typeof(CGDK.buffer).Equals(temp_type))
			{
				this._append_buffer(_ptr, ref _offset, (buffer)_object);
			}
			else
			{
				this._append_struct(_ptr, ref _offset, _object);
			}
		}
		// 5) 배열일 경우
		else if (temp_type.IsArray)
		{
			this._append_Collection(_ptr, ref _offset, _object as System.Collections.ICollection, _object.GetType().GetElementType());
		}
		// 6) 문자열일 경우
		else if (typeof(string).Equals(temp_type))
		{
			this._append<string>(_ptr, ref _offset, _object as string);
		}
		// 7) 기다
		else 
		{
			// - Dictionary인 경우
			{
				var temp_object = _object as System.Collections.IDictionary;
				if (temp_object != null)
				{
					this._append_Dictionary(_ptr, ref _offset, temp_object, temp_type.GetGenericArguments());
					return;
				}
			}

			{
				// - Collection인 경우
				var temp_object = _object as System.Collections.ICollection;
				if (temp_object != null)
				{
					this._append_Collection(_ptr, ref _offset, temp_object, _object.GetType().GetGenericArguments()[0]);
					return;
				}
				// - 일반 class 인 경우
				else if(temp_type.IsClass)
				{
					this._append_class(_ptr, ref _offset, _object);
				}
				else
				{
					// Check) 지원되지 않는 Type이다.
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

					// Throw) 
					throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
				}
			}
		}
	}
	private unsafe void	_append_Primitive		(long _ptr, ref long _offset, object _object)
	{
		// 설명) 기본형(byte, sbyte, short, ushort, char, int, uint ... 인 경우 append 처리
		//       성능을 위해 pointer를 사용해 unsafe로 작성한다.

        // check) 
        Debug.Assert(this.m_buffer != null);

	#if _USE_BOUND_CHECK
        // Check) m_iCount가 남은 크기보다 작으면 Exception을 던진다.
        if (Marshal.SizeOf(_object)+_offset > this.m_buffer.Length)
		{
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		}
	#endif

		// 1) ptr을 얻는다.
		var ptr = new IntPtr(_ptr + _offset);

		// 2) primitive 종류에 따라 append
		var tmp = _object.GetType();
		if (tmp == typeof(long)) *(long*)ptr = (long)_object;
		else if (tmp == typeof(ulong)) *(long*)ptr = (long)_object;
		else if (tmp == typeof(double)) *(double*)ptr = (double)_object;
		else if (tmp == typeof(int)) *(int*)ptr = (int)_object;
		else if (tmp == typeof(uint)) *(ulong*)ptr = (ulong)_object;
		else if (tmp == typeof(float)) *(float*)ptr = (float)_object;
		else if (tmp == typeof(short)) *(short*)ptr = (short)_object;
		else if (tmp == typeof(ushort)) *(ushort*)ptr = (ushort)_object;
		else if (tmp == typeof(char)) *(char*)ptr = (char)_object; 
		else if (tmp == typeof(sbyte)) *(sbyte*)ptr = (sbyte)_object;
		else if (tmp == typeof(byte)) *(byte*)ptr = (byte)_object;
		else throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] buffer size is short");

		// 3) m_iCount의 길이를 더한다.
		_offset += Marshal.SizeOf(_object);
	}
#if NET
	private void	_append_class			(long _ptr, ref long _offset, object? _object, Type? _base_type = null)
#else
	private void	_append_class			(long _ptr, ref long _offset, object _object, Type _base_type = null)
#endif
	{
        // check)
		Debug.Assert(_object != null);

        // 1) Get Type ( 재귀용 _base_type 이 존재한다면 그걸쓰고 아니라면 Data 를 쓴다.  )
        Type temp_type = _base_type != null ? _base_type : _object.GetType();

		// Check) Serializable이 아니면 리턴한다.
		if (_is_serializable_type(temp_type) == false)
			return;

		// check) 
        Debug.Assert(temp_type.BaseType != null);

        // 2) 부모의 부모가 nullptr이면 object를 제외하고 최고 부모 클래스다.
        if(temp_type.BaseType.BaseType != null)
        {
            this._append_class(_ptr, ref _offset, _object, temp_type.BaseType);
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
			var temp = iter.GetValue(_object);

			// - null일 경우 그냥 -1만 쓰고 끝낸다.
			if (temp == null)
			{
				Marshal.WriteInt32(new IntPtr(_ptr + _offset), -1);
				_offset += sizeof(int);
				continue;
			}

			// - append
			this._append(_ptr, ref _offset, temp);
		}
	}
	private void	_append_struct			(long _ptr, ref long _offset, object _object)
	{
		// check) 
        Debug.Assert(_object != null);

		Type temp_type = _object.GetType(); 
		var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);
			

		foreach (var iter in temp_field)
		{
			// Check)
			if(iter.IsNotSerialized == true)
				continue;

			var temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp == null)
			{
				// - -1을 쓰고 끝낸다.
				Marshal.WriteInt32(new IntPtr(_ptr + _offset), -1);
				_offset += sizeof(int);
				continue;
			}

			// - append data
			//this._append(_ptr, ref _offset, temp);

			var field_type = iter.FieldType;

			if (field_type.IsPrimitive)
			{
				Marshal.StructureToPtr(temp, new IntPtr(_ptr + _offset), false); _offset += Marshal.SizeOf(field_type);
			}
			else if(field_type.IsEnum)
			{
				var	type_enum = field_type.GetFields()[0].FieldType;

				Marshal.StructureToPtr(Convert.ChangeType(temp, type_enum), new IntPtr(_ptr + _offset), false);

				_offset += Marshal.SizeOf(type_enum);
			}
			else if (field_type.IsValueType)
			{
				if (typeof(DateTime).Equals(field_type))
				{
					this._append_datetime(_ptr, ref _offset, temp);
				}
				else if (typeof(CGDK.buffer).Equals(field_type))
				{
					this._append_buffer(_ptr, ref _offset, (buffer)temp);
				}
				else
				{
					this._append_struct(_ptr, ref _offset, temp);
				}
			}
			else if (field_type.IsArray)
			{
				this._append_Collection(_ptr, ref _offset, temp as System.Collections.ICollection, temp.GetType().GetElementType());
			}
			else if (typeof(string).Equals(field_type))
			{
				this._append<string>(_ptr, ref _offset, temp as string);
			}
			else
			{
				{
					var temp_object = temp as System.Collections.IDictionary;
					if (temp_object != null)
					{
						this._append_Dictionary(_ptr, ref _offset, temp_object, field_type.GetGenericArguments());
						continue;
					}
				}
				{
					var temp_object = temp as System.Collections.ICollection;
					if (temp_object != null)
					{
						this._append_Collection(_ptr, ref _offset, temp_object, temp.GetType().GetGenericArguments()[0]);
						continue;
					}

					if (field_type.IsClass)
					{
						this._append_class(_ptr, ref _offset, temp);
					}
					else
					{
						// Check) 지원되지 않는 Type이다.
						Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

						// Throw) 
						throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
					}
				}
			}
		}
	}
	public void		_append_datetime		(long _ptr, ref long _offset, DateTime _object)
	{
		this._append<long>(_ptr, ref _offset, _object.Ticks);
	}
	public void		_append_datetime		(long _ptr, ref long _offset, object _object)
	{
		DateTime tempTime = (DateTime)_object;
		this._append<long>(_ptr, ref _offset, tempTime.Ticks);
	}

#if NET
	private void	_append_Dictionary		(long _ptr,ref long _offset,System.Collections.IDictionary? _object, Type[] _types) 
#else
	private void	_append_Dictionary		(long _ptr,ref long _offset,System.Collections.IDictionary _object, Type[] _types) 
#endif
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			Marshal.WriteInt32(new IntPtr(_ptr + _offset), -1);
			_offset += sizeof(int);
			return;
		}

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		Marshal.WriteInt32(new IntPtr(_ptr + _offset), _object.Count); _offset += Marshal.SizeOf(typeof(int));

		// 2) [데이터]들을 써넣는다.
		if (_types[0].IsPrimitive)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;

                    // check) 
                    Debug.Assert(temp_enum.Value != null);

					// - append value
                    Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0]);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
		else if(_types[0].IsEnum)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				int size_1 = Marshal.SizeOf(_types[1]);

				while (temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Key, _types[0].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);
				var size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Key,   _types[0].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					// - append key
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				var	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				int	size_0 = Marshal.SizeOf(_types[0].GetFields()[0].FieldType);

				while(temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Key, new IntPtr(_ptr + _offset), false); _offset += size_0;
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
		else if (_types[0].IsValueType)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_enum = _object.GetEnumerator();
				var	size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_struct(_ptr, ref _offset, temp_enum.Key);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();
				var	size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_struct(_ptr, ref _offset, temp_enum.Key);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_struct(_ptr, ref _offset, temp_enum.Key);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_struct(_ptr, ref _offset, temp_enum.Key);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_struct(_ptr, ref _offset, temp_enum.Key);
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_struct(_ptr, ref _offset, temp_enum.Key);
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_struct(_ptr, ref _offset, temp_enum.Key);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_struct(_ptr, ref _offset, temp_enum.Key);
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
		else if (_types[0].IsArray)
		{
			if (_types[1].IsPrimitive)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();
				int size_1 = Marshal.SizeOf(_types[1]);

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append vlaue3
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, _types[1].GetElementType());
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				 var temp_type_0 = _types[0].GetElementType();
				 var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();
				var temp_enum = _object.GetEnumerator();

				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
				int size_1 = Marshal.SizeOf(_types[1]);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Key as string);
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
				int size_1 = Marshal.SizeOf(_types[1]);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append vlaue
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					_append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetElementType();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Key as System.Collections.IDictionary, temp_type_0);
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
				int size_1 = Marshal.SizeOf(_types[1]);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

                    // check) 
                    Debug.Assert(temp_enum.Value != null);

					// - append value
                    Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
				}
			}
			else if(_types[1].IsArray)
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetElementType();

				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append<string>(_ptr, ref _offset, temp_enum.Value as string);
				}
			}
			else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if(typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_0 = _types[0].GetGenericArguments()[0];
				var temp_type_1 = _types[1].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_Collection(_ptr, ref _offset, temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if(_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Key as System.Collections.ICollection, temp_type_0);
					this._append_class(_ptr,ref _offset,temp_enum.Value);
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
				int	size_1 = Marshal.SizeOf(_types[1]);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append
					this._append_class(_ptr, ref _offset, temp_enum.Key);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - marshal
					Marshal.StructureToPtr(temp_enum.Value, new IntPtr(_ptr + _offset), false); _offset += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					_append_class(_ptr, ref _offset, temp_enum.Key);

                    // check) 
                    Debug.Assert(temp_enum.Value != null);

					// - append value
                    Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Value, _types[1].GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_1;

				}
			}
			else if(_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while(temp_enum.MoveNext()) 
				{
					// - append key
					this._append_class(_ptr, ref _offset, temp_enum.Key);

					// check) 
					Debug.Assert(temp_enum.Value != null);

					// - append value
					this._append_struct(_ptr,ref _offset,temp_enum.Value);
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
#if NET
	private void	_append_Collection		(long _ptr, ref long _offset, System.Collections.ICollection? _object, Type? _type)
#else
	private unsafe void	_append_Collection		(long _ptr, ref long _offset, System.Collections.ICollection _object, Type _type)
#endif
	{
		// check) 
		Debug.Assert(_type != null);

		if (_type.IsArray == false)
		{
			// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
			if (_object == null)
			{
				// - -1을 쓰고 끝낸다.
				Marshal.WriteInt32(new IntPtr(_ptr + _offset), -1);
				_offset += sizeof(int);
				return;
			}

			// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
			Marshal.WriteInt32(new IntPtr(_ptr + _offset), _object.Count); _offset += Marshal.SizeOf(typeof(int));

			// 2) [데이터]들을 써넣는다.
			if (_type.IsPrimitive)
			{
				int size_0 = Marshal.SizeOf(_type);
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(temp_enum.Current, new IntPtr(_ptr + _offset), false); _offset += size_0;
				}
			}
			else if (_type.IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

				int size_0 = Marshal.SizeOf(_type.GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					Marshal.StructureToPtr(Convert.ChangeType(temp_enum.Current, _type.GetFields()[0].FieldType), new IntPtr(_ptr + _offset), false); _offset += size_0;
				}
			}
			else if (_type.IsValueType)
			{
				if(typeof(DateTime).Equals(_type))
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						this._append_datetime(_ptr, ref _offset, temp_enum.Current);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_type))
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						this._append_buffer(_ptr, ref _offset, (buffer)temp_enum.Current);
					}
				}
				else
				{
					var temp_enum = _object.GetEnumerator();
					while (temp_enum.MoveNext())
					{
						this._append_struct(_ptr, ref _offset, temp_enum.Current);
					}
				}
			}
			else if (typeof(string).Equals(_type))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					this._append<string>(_ptr, ref _offset, temp_enum.Current as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
			{
				var temp_type = _type.GetGenericArguments();
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					this._append_Dictionary(_ptr, ref _offset, temp_enum.Current as System.Collections.IDictionary, temp_type);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_type))
			{
				var tmp_type =	_type.GetGenericArguments()[0];
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					this._append_Collection(_ptr, ref _offset, temp_enum.Current as System.Collections.ICollection, tmp_type);
				}
			}
			else if (_type.IsClass && _is_serializable_type(_type))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					this._append_class(_ptr, ref _offset, temp_enum.Current);
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
			// check)
			Debug.Assert(_object != null);

			// - Element Type에 따라 처리...
			var temp_enum = _object.GetEnumerator();
			while (temp_enum.MoveNext())
			{
				this._append(_ptr, ref _offset, temp_enum.Current);
			}
		}
	}

// 5) extract관련(뽑아내기)
#if NET
	public object?	extract					(Type _type)
#else
	public object	extract					(Type _type)
#endif
	{
		// 1) [버퍼]를 고정(Pinned) 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

		// 2) [버퍼_포인터]를 얻는다.
		long ptr = (long)pinnedArray.AddrOfPinnedObject()+m_offset;
		long offset = 0;

		try
		{
			// 3) 
			var temp = _extract(ptr, ref offset, _type, null, 0);

			// 5) [버퍼]의 고정(Pinned)을 Free한다.
			pinnedArray.Free();

			// 6) Buffer Pointer를 증가시킨다.
			this.m_count -= (int)offset;
			this.m_offset += (int)offset;

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
		Type tmp = typeof(T);
			
		if (tmp.IsPrimitive)
		{
			if (tmp == typeof(long)) return (T)(object)extract_long();
			else if (tmp == typeof(ulong)) return (T)(object)extract_ulong();
			else if (tmp == typeof(double)) return (T)(object)extract_double();
			else if (tmp == typeof(int)) return (T)(object)extract_int();
			else if (tmp == typeof(uint)) return (T)(object)extract_uint();
			else if (tmp == typeof(float)) return (T)(object)extract_float();
			else if (tmp == typeof(short)) return (T)(object)extract_short();
			else if (tmp == typeof(ushort)) return (T)(object)extract_ushort();
			else if (tmp == typeof(sbyte)) return (T)(object)extract_sbyte();
			else if (tmp == typeof(byte)) return (T)(object)extract_byte();
			else if (tmp == typeof(char)) return (T)(object)extract_char();
			else throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] buffer size is short");
		}
		else
		{
			// 1) [버퍼]를 고정(Pinned) 시킨다.
			GCHandle pinnedArray = GCHandle.Alloc(m_buffer, GCHandleType.Pinned);

			// 2) [버퍼_포인터]를 얻는다.
			long ptr = (long)pinnedArray.AddrOfPinnedObject() + this.m_offset;
			long offset = 0;

			try
			{
				var temp = default(T);

				if (tmp.IsEnum)
				{
					temp = (T)_extract_enum(ptr, ref offset, tmp);
				}
				else if (tmp.IsValueType)
				{
					if (typeof(DateTime).Equals(tmp))
					{
						temp = (T)this._extract_datetime(ptr, ref offset);
					}
					else if (typeof(CGDK.buffer).Equals(tmp))
					{
						temp = (T)this._extract_buffer(ptr, ref offset);
					}
					else
					{
						temp = (T)this._extract_struct(ptr, ref offset, tmp);
					}
				}
				else if (tmp == typeof(string))
				{
					var value_string = this._extract_string(ptr, ref offset);

					if (value_string != null)
						temp = (T)(object)value_string;
				}
				// Case) Array
				else if (tmp.IsArray)
				{
					// - get element
					var element_type = tmp.GetElementType();

					// check)
					Debug.Assert(element_type != null);

					// - _extact_array
					var temp_object_array = this._extract_array(ptr, ref offset, element_type, null, 0);

					// - set value
					if (temp_object_array != null)
						temp = (T)(object)temp_object_array;
				}
				// Case) Dictionary
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(tmp))
				{
					var value_dictionary = this._extract_DictionaryX(ptr, ref offset, tmp, tmp.GetGenericArguments());

					if (value_dictionary != null)
						temp = (T)Convert.ChangeType(value_dictionary, tmp);
				}
				// Case) List
				else if (typeof(System.Collections.IList).IsAssignableFrom(tmp))
				{
					// - extract list
					var temp_bject_list = this._extract_ListX(ptr, ref offset, tmp, tmp.GetGenericArguments()[0]);

					// - set value
					if (temp_bject_list != null)
						temp = (T)temp_bject_list;
				}
				// Case) Class
				else if (tmp.IsClass)
				{
					var value_class = this._extract_class(ptr, ref offset, tmp);

					if (value_class != null)
						temp = (T)Convert.ChangeType(value_class, tmp);
				}
				else
				{
					// Check) 지원되지 않는 Type이다.
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

					// Throw) 
					throw new CGDK.Exception.Serialize(offset, "[CGDK.buffer] Not Supported TYPE.");
				}

				// 5) [버퍼]의 고정(Pinned)을 Free한다.
				pinnedArray.Free();

				// 6) Buffer Pointer를 증가시킨다.
				this.m_count -= (int)offset;
				this.m_offset += (int)offset;

				// debug)
				Debug.Assert(temp != null);

				// Return)
				return temp;
			}
			catch (System.Exception _e)
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

#if NET
	private object?	_extract				(long _ptr, ref long _offset, Type _type, int[]? _static_size, int _dimension)
#else
	private object	_extract				(long _ptr, ref long _offset, Type _type, int[] _static_size, int _dimension)
#endif
	{
		// Case) Primitive Type
		if (_type.IsPrimitive)
		{
			return this._extract_primitive(_ptr, ref _offset, _type);
		}
		// Case) Enum Type
		else if (_type.IsEnum)
		{
			return this._extract_enum(_ptr, ref _offset, _type);
		}
		// Case) Value Type
		else if (_type.IsValueType)
		{
			if(typeof(DateTime).Equals(_type))
			{
				return this._extract_datetime(_ptr, ref _offset);
			}
			else if(typeof(CGDK.buffer).Equals(_type))
			{
				return this._extract_buffer(_ptr, ref _offset);
			}
			else
			{
				return this._extract_struct(_ptr, ref _offset, _type);
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_type))
		{
			return this._extract_string(_ptr, ref _offset);
		}
		// Case) Array
		else if (_type.IsArray)
		{
			// - get element type
			var temp_type = _type.GetElementType();

			// check) 
			Debug.Assert(temp_type != null);

			// - extract array
			return this._extract_array(_ptr, ref _offset, temp_type, _static_size, _dimension+1);
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			// Return)
			return this._extract_DictionaryX(_ptr, ref _offset, _type, _type.GetGenericArguments());
		}
		else if(typeof(System.Collections.IList).IsAssignableFrom(_type))
		{
			// return) 
			return this._extract_ListX(_ptr, ref _offset, _type, _type.GetGenericArguments()[0]);
		}
		// Case) Array
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			return this._extract_class(_ptr, ref _offset, _type);
		}
		else
		{
			// Check) 지원되지 않는 Type이다.
			Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

			// Throw) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
		}
	}
	private unsafe object	_extract_primitive		(long _ptr, ref long _offset, Type _type)
		{
		// 1) Type의 크기를 구한다.
		var	sizeType = Marshal.SizeOf(_type);

	#if _USE_BOUND_CHECK
		// check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_offset+ sizeType > m_count)
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
	#endif

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		IntPtr ptr = new IntPtr(_ptr + _offset);

		// declar) 
		object obj;

		if (_type == typeof(long)) obj = *(long*)ptr;
		else if (_type == typeof(ulong)) obj = *(ulong*)ptr;
		else if (_type == typeof(double)) obj = *(double*)ptr;
		else if (_type == typeof(int)) obj = *(int*)ptr;
		else if (_type == typeof(uint)) obj = *(uint*)ptr;
		else if (_type == typeof(float)) obj = *(float*)ptr;
		else if (_type == typeof(short)) obj = *(short*)ptr;
		else if (_type == typeof(ushort)) obj = *(ushort*)ptr;
		else if (_type == typeof(sbyte)) obj = *(sbyte*)ptr;
		else if (_type == typeof(byte)) obj = *(byte*)ptr;
		else if (_type == typeof(char)) obj = *(char*)ptr; 
		else throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] buffer size is short");

		// check) 
		Debug.Assert(obj != null);

		// 2) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += sizeType;

		// Return) 
		return obj;
	}
	private unsafe T		_extract_primitive<T>	(long _ptr, ref long _offset) where T:unmanaged
	{
		// check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
		if (_offset + sizeof(T) > m_count)
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");

		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		IntPtr ptr = new IntPtr(_ptr + _offset);

		// 2) [버퍼]로 부터 [데이터]를 복사해 온다.
		var obj = *(T*)ptr;

		// 3) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += sizeof(T);

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
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");

		// 2) [버퍼]로 부터 [데이터]를 복사해 온다.
		var obj = Marshal.PtrToStructure(new IntPtr(_ptr+_offset), type_enum);

		// check) 
		Debug.Assert(obj != null);

		// 3) [버퍼_길이]와 [버퍼_어프셋]을 업데이트한다.
		_offset += size_enum;

		// Return) 
		return obj;
	}
	private object	_extract_struct			(long _ptr, ref long _offset, Type _type)
	{
		// 1) Field 정보를 얻는다.
		var temp_field = _type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		// 2) 객체를 생성한다.
		var temp_object = Activator.CreateInstance(_type);

		// check) 
		Debug.Assert(temp_object != null);

		// 3) 각 Field값을 읽어 써넣는다.
		foreach (var iter in temp_field)
		{
			if(iter.IsNotSerialized)
				continue;

			iter.SetValue(temp_object, _extract(_ptr, ref _offset, iter.FieldType, null, 0));
		}

		// Return) 
		return temp_object;
	}
#if NET
	private object?	_extract_class			(long _ptr, ref long _offset, Type _type, object? _instance_object=null)
#else
	private object	_extract_class			(long _ptr, ref long _offset, Type _type, object _instance_object=null)
#endif
	{
        // 1) 생성된 객체가 없다면 객체를 생성한다.
        if(_instance_object == null)
            _instance_object = Activator.CreateInstance(_type);

        // Check) Serializable Attribute가 없으면 그냥 끝낸다.
        if (_is_serializable_type(_type) == false)
            return null;

		// check) 
		Debug.Assert(_type.BaseType != null);

        // 2) 부모가 없는객체가 나올때까지 재귀를 돌린다.
        if(_type.BaseType.BaseType != null)
        {
            this._extract_class(_ptr, ref _offset, _type.BaseType, _instance_object);
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

	private unsafe object _extract_datetime		(long _ptr, ref long _offset)
	{
		// 1) [버퍼]로 부터 [데이터]를 복사해 온다.
		IntPtr ptr = new IntPtr(_ptr + _offset);

		// 2) add size
		_offset += sizeof(long);

		// 3) get DateTime
		return new DateTime(*(long*)ptr);
	}

	private object _extract_buffer			(long _ptr, ref long _offset)
	{
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
		Debug.Assert(sizeof(UInt64)<=m_count);

		// check) 
		Debug.Assert(this.m_buffer != null);

	#if _USE_BOUND_CHECK
		// Check) Buffer의 길이가 UInt32 최소크기보다 작을 경우 Exception
		if(sizeof(UInt32) >m_count) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
	#endif

		// Declare) 
		CGDK.buffer temp_object = new CGDK.buffer();

		// 1) buffer길이를 얻는다.
		var temp_size = Marshal.ReadInt64(new IntPtr(_ptr + _offset));

		// 2) String의 길이를 설정한다.
		temp_object.size = (int)temp_size;

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
		Debug.Assert((temp_object.size + sizeof(UInt64))<=this.m_count);

	#if _USE_BOUND_CHECK
		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
		if ((temp_object.size + sizeof(UInt64)) > this.m_count)
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
	#endif

		// 2) [문자열]을 복사한다.
		temp_object.data = new byte[temp_object.size];
		System.Buffer.BlockCopy(this.m_buffer, this.m_offset + (int)_offset + sizeof(UInt64), temp_object.data, 0, temp_object.size);

		// 3) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
		_offset += (sizeof(UInt64) + temp_object.size);

		// Return)
		return temp_object;
	}

#if NET
	private string?	_extract_string			(long _ptr, ref long _offset)
#else
	private string	_extract_string			(long _ptr, ref long _offset)
#endif
	{
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
		Debug.Assert(sizeof(int) <=this.m_count);

		// check) 
		Debug.Assert(this.m_buffer != null);

	#if _USE_BOUND_CHECK
		// Check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
		if(sizeof(int)>this.m_count) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
	#endif

		// 1) extract  String length
		var length_string = Marshal.ReadInt32(new IntPtr(_ptr + _offset));

		// Check) length가 -1이면 null을 리턴한다.
		if (length_string == -1)
		{
			_offset	+= sizeof(int);
			return null;
		}

		// Check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
		Debug.Assert((length_string * sizeof(char) + sizeof(int)) <= this.m_count);

	#if _USE_BOUND_CHECK
		// check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
		if((length_string * sizeof(char) + sizeof(int)) > this.m_count) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] Not Supported TYPE.");
	#endif

		// 3) 복사할 [문자열_길이]를 구한다. (NULL문자는 뺀다.)
		int size_copy = (length_string - 1) * sizeof(char);

		// Check) [문자열]의 제일 끝이 NULL인지 확인한다.
		if(this.m_buffer[this.m_offset + _offset + sizeof(int) + size_copy] != 0 || this.m_buffer[this.m_offset + _offset + sizeof(int) + size_copy + 1] != 0) 
			throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] string terminate No-'NULL' value");

		// 4) [문자열]을 복사한다.
		char[] charTemp = new char[length_string - 1];
		System.Buffer.BlockCopy(this.m_buffer, this.m_offset + (int)_offset + sizeof(int), charTemp, 0, size_copy);

		// 5) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.		
		_offset	+= (sizeof(int) + size_copy + sizeof(char));

		// 6) [string]로 변환해 최종 리턴한다.
		return new string(charTemp);
	}
#if NET
	private Array?	_extract_array			(long _ptr, ref long _offset, Type _type, int[]? _static_size, int _dimension)
#else
	private Array	_extract_array			(long _ptr, ref long _offset, Type _type, int[] _static_size, int _dimension)
#endif
	{
		// Declare)
		int temp_count = 0;

		if (_static_size == null)
		{
			// 1) [데이터 갯수]를 읽어들인다.
			temp_count = _extract_primitive<int>(_ptr, ref _offset);

			// Check) length가 -1이면 null을 리턴한다.
			if (temp_count == -1)
				return null;
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
					temp_array.SetValue(_extract_struct(_ptr, ref _offset, _type), i);
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
				// - get element type
				var temp_type = _type.GetElementType();

				// check) 
				Debug.Assert(temp_type != null);

				// - extract
				temp_array.SetValue(_extract_array(_ptr, ref _offset, temp_type, _static_size, _dimension), i);
			}
		}
		// Case) Dictionary
		else if(typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments();

			for (int i = 0; i < temp_count; ++i)
			{
				// - [데이터 갯수]를 읽어들인다.
				int count_item = _extract_primitive<int>(_ptr, ref _offset);

				// Check) temp_count가 -1이면 null을 리턴한다.
				if (count_item == -1)
					continue;

				// - create object
				var temp_object = Activator.CreateInstance(_type);

				// - get value
				var temp_object_dictionary = temp_object as System.Collections.IDictionary;

				// check)
				Debug.Assert(temp_object_dictionary != null);


				this._extract_Dictionary(_ptr, ref _offset, temp_object_dictionary, count_item, temp_type);
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
				int count_item = _extract_primitive<int>(_ptr, ref _offset);

				// Check) temp_count가 -1이면 null을 리턴한다.
				if(count_item == -1)
					continue;

				// - create object
				var temp_object = Activator.CreateInstance(_type);

				// - get value
				var temp_object_list = temp_object as System.Collections.IList;

				// check)
				Debug.Assert(temp_object_list != null);

				this._extract_List(_ptr, ref _offset, temp_object_list, count_item, temp_type);
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
#if NET
	private object?	_extract_DictionaryX	(long _ptr, ref long _offset, Type _type_create, Type[] _types) 
#else
	private object	_extract_DictionaryX	(long _ptr, ref long _offset, Type _type_create, Type[] _types) 
#endif
	{
		// 1) [데이터 갯수]를 읽어들인다.
		int count_item = _extract_primitive<int>(_ptr, ref _offset);

		// Check) temp_count가 -1이면 null을 리턴한다.
		if (count_item == -1)
			return null;

        // 2) Instance를 생성한다.
        var obj_value = Activator.CreateInstance(_type_create);

		// 3) get value
		var obj_value_dictionary = obj_value as System.Collections.IDictionary;

		// check)
		Debug.Assert(obj_value_dictionary != null);

		// 3) Dictionary 내용을 읽어들인다.
		this._extract_Dictionary(_ptr, ref _offset, obj_value_dictionary, count_item, _types);

		// Return) 생성된 객체를 Return한다.
		return obj_value;
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
					_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
								this._extract_primitive(_ptr, ref _offset, _types[1]));
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
								this._extract_enum(_ptr, ref _offset, _types[1]));
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
									this._extract_datetime(_ptr, ref _offset));
					}
				}
				else if (typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
									this._extract_buffer(_ptr, ref _offset));
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
									this._extract_struct(_ptr, ref _offset, _types[1]));
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
								this._extract_string(_ptr, ref _offset));
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
								this._extract_array(_ptr, ref _offset, temp_type_1, null, 0));
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_primitive(_ptr, ref _offset, _types[0]),
								this._extract_class(_ptr, ref _offset, _types[1]));
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
		// Case) Value type
		else if (_types[0].IsEnum)
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
								this._extract_primitive(_ptr, ref _offset, _types[1]));
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
								this._extract_enum(_ptr, ref _offset, _types[1]));
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
									this._extract_datetime(_ptr, ref _offset));
					}
				}
				else if (typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
									this._extract_buffer(_ptr, ref _offset));
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
									this._extract_struct(_ptr, ref _offset, _types[1]));
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
								this._extract_string(_ptr, ref _offset));
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
								this._extract_array(_ptr, ref _offset, temp_type_1, null, -1));
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key	 = this._extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_primitive(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_enum(_ptr, ref _offset, _types[0]),
								this._extract_class(_ptr, ref _offset, _types[1]));
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
		// Case) Value Type
		else if (_types[0].IsValueType)
		{
			if (_types[1].IsPrimitive)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
								this._extract_primitive(_ptr, ref _offset, _types[1]));
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
								this._extract_enum(_ptr, ref _offset, _types[1]));
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if (typeof(string).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
									this._extract_datetime(_ptr, ref _offset));
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
									this._extract_struct(_ptr, ref _offset, _types[1]));
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
								this._extract_string(_ptr, ref _offset));
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				// check)
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
								this._extract_array(_ptr, ref _offset, temp_type_1, null, 0));
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_struct(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_struct(_ptr, ref _offset, _types[0]);
					var obj_value = this._extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);
		
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _types[0]),
								this._extract_class(_ptr, ref _offset, _types[1]));
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
					// - get key and value
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_primitive(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			else if (_types[1].IsEnum)
			{
				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_enum(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Value Type
			else if (_types[1].IsValueType)
			{
				if(typeof(DateTime).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						// - get key and value
						var obj_key = this._extract_string(_ptr, ref _offset);
						var obj_value = this._extract_datetime(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						// - get key and value
						var obj_key = this._extract_string(_ptr, ref _offset);
						var obj_value = this._extract_buffer(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						// - get key and value
						var obj_key = this._extract_string(_ptr, ref _offset);
						var obj_value = this._extract_struct(_ptr, ref _offset, _types[1]);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_string(_ptr, ref _offset);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_1	 = _types[1].GetElementType();

				// check)
				Debug.Assert(temp_type_1!= null);

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_array(_ptr, ref _offset, temp_type_1, null, 0);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					_object.Add(obj_key, obj_value);
				}
			}
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_1	 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					var	obj_key = this._extract_string(_ptr, ref _offset);
					var	obj_value = this._extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_string(_ptr, ref _offset);
					var obj_value = this._extract_class(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
					// - get key values
					var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var	obj_value = this._extract_primitive(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var	obj_value = this._extract_enum(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
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
						// - get key values
						var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
						var	obj_value = this._extract_datetime(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						// - get key values
						var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
						var	obj_value = this._extract_buffer(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
				else
				{

					for (; _count > 0; --_count)
					{
						// - get key values
						var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
						var	obj_value = this._extract_struct(_ptr, ref _offset, _types[1]);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0	= _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var	obj_value = this._extract_string(_ptr, ref _offset);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var	obj_value = this._extract_array(_ptr, ref _offset, temp_type_1, null, 0);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);;

					// check)
					Debug.Assert(obj_key != null);

					// - add
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
					// - get key and value
					var obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var obj_value = this._extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					// - add
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
					// - get key and value
					var	obj_key = this._extract_array(_ptr, ref _offset, temp_type_0, null, 0);
					var	obj_value = this._extract_class(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
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
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_primitive(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0	 = _types[0].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_enum(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
						// - get key and value
						var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
						var obj_value = this._extract_datetime(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						// - get key and value
						var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
						var obj_value = this._extract_buffer(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						// - get key and value
						var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
						var obj_value = this._extract_struct(_ptr, ref _offset, _types[1]);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_string(_ptr, ref _offset);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1 = _types[1].GetElementType();

				// check)
				Debug.Assert(temp_type_0 != null);

				// check)
				Debug.Assert(temp_type_1 != null);

                for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_array(_ptr, ref _offset, temp_type_1, null, -1);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1	 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) List
			else if (typeof(System.Collections.IList).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments();
				var	temp_type_1 = _types[1].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
					// - get key and value
					var obj_key = this._extract_DictionaryX(_ptr, ref _offset, _types[0], temp_type_0);
					var obj_value = this._extract_class(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_primitive(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_enum(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
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
						// - get key values
						var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
						var	obj_value = this._extract_datetime(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						// - get key values
						var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
						var	obj_value = this._extract_buffer(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
				else
				{
					for (; _count > 0; --_count)
					{
						// - get key values
						var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
						var	obj_value = this._extract_struct(_ptr, ref _offset, _types[1]);

						// check)
						Debug.Assert(obj_key != null);

						// - add
						_object.Add(obj_key, obj_value);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_string(_ptr, ref _offset);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				// debug
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_array(_ptr, ref _offset, temp_type_1, null, -1);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
				}
			}

			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					// - add
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
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
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
					// - get key values
					var	obj_key = this._extract_ListX(_ptr, ref _offset, _types[0], temp_type_0);
					var	obj_value = this._extract_class(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add
					_object.Add(obj_key, obj_value);
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
				// - get type
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_primitive(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);

				}
			}
			else if (_types[1].IsEnum)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_enum(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
						// - get key and value
						var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
						var obj_value = this._extract_datetime(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						// - add 
						_object.Add(obj_key, obj_value);
					}
				}
				else if(typeof(CGDK.buffer).Equals(_types[1]))
				{
					for (; _count > 0; --_count)
					{
						var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
						var obj_value = this._extract_buffer(_ptr, ref _offset);

						// check)
						Debug.Assert(obj_key != null);

						_object.Add(obj_key, obj_value);
					}
				}
				else
				{

					for (; _count > 0; --_count)
					{
						var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
						var obj_value = this._extract_struct(_ptr, ref _offset, _types[1]);

						// check)
						Debug.Assert(obj_key != null);

						_object.Add(obj_key, obj_value);
					}
				}
			}
			// Case) STRING
			else if (typeof(string).Equals(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_string(_ptr, ref _offset);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Array
			else if (_types[1].IsArray)
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_1 != null);

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_array(_ptr, ref _offset, temp_type_1, null, -1);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Dictionary
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];
				var	temp_type_1 = _types[1].GetGenericArguments();

				for (; _count > 0; --_count)
				{
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_DictionaryX(_ptr, ref _offset, _types[1], temp_type_1);;

					// check)
					Debug.Assert(obj_key != null);

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
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_ListX(_ptr, ref _offset, _types[1], temp_type_1);
		
					// check)
					Debug.Assert(obj_key != null);

					_object.Add(obj_key, obj_value);
				}
			}
			// Case) Class
			else if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var	temp_type_0 = _types[0].GetGenericArguments()[0];

				for (; _count > 0; --_count)
				{
					// - get key and value
					var obj_key = this._extract_class(_ptr, ref _offset, temp_type_0);
					var obj_value = this._extract_class(_ptr, ref _offset, _types[1]);

					// check)
					Debug.Assert(obj_key != null);

					// - add 
					_object.Add(obj_key, obj_value);
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
#if NET
	private object?	_extract_ListX			(long _ptr, ref long _offset, Type _type_create, Type _type)
#else
	private object	_extract_ListX			(long _ptr, ref long _offset, Type _type_create, Type _type)
#endif
	{
		// - [데이터 갯수]를 읽어들인다.
		int count_item = _extract_primitive<int>(_ptr, ref _offset);

		// Check) temp_count가 -1이면 null을 리턴한다.
		if (count_item != -1)
		{
			// - get values
			var obj_value = Activator.CreateInstance(_type_create);
			var obj_value_list = obj_value as System.Collections.IList;

			// debug)
			Debug.Assert(obj_value_list != null);

			// - extract list
			this._extract_List(_ptr, ref _offset, obj_value_list, count_item, _type);

			return obj_value;
		}
		else
		{
			return null;
		}
	}
	private unsafe void	_extract_List			(long _ptr, ref long _offset, System.Collections.IList _object, int _count, Type _type)
	{
		// 2) [데이터]들을 읽어들인다.
		if (_type.IsPrimitive)
		{
			// - Type의 크기를 구한다.
			var	sizeType = Marshal.SizeOf(_type);

		#if _USE_BOUND_CHECK
			// check) [버퍼_길이]가 T의 크기보다 작으면 Exception을 던진다.
			if (_offset + (sizeType * _count) > this.m_count)
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
		#endif

			// - copy
			if (_type == typeof(long))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(long*)(ptr));
				}
			}
			else if (_type == typeof(ulong))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(ulong*)(ptr));
				}
			}
			else if (_type == typeof(double))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(double*)(ptr));
				}
			}
			else if (_type == typeof(int))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(int*)(ptr));
				}
			}
			else if (_type == typeof(uint))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(uint*)(ptr));
				}
			}
			else if (_type == typeof(float))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(float*)(ptr));
				}
			}
			else if (_type == typeof(short))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(short*)(ptr));
				}
			}
			else if (_type == typeof(ushort))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(ushort*)(ptr));
				}
			}
			else if (_type == typeof(char))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(char*)(ptr));
				}
			}
			else if (_type == typeof(sbyte))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(sbyte*)(ptr));
				}
			}
			else if (_type == typeof(byte))
			{
				for (var offset_end = _offset + sizeType * _count; _offset < offset_end; _offset +=_count)
				{
					IntPtr ptr = new IntPtr(_ptr + _offset);
					_object.Add(*(byte*)(ptr));
				}
			}
			else
				throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] buffer size is short");

		}
		else if (_type.IsEnum)
		{
			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_enum(_ptr, ref _offset, _type));
			}
		}
		// Case) Value Type
		else if (_type.IsValueType)
		{
			if(typeof(DateTime).Equals(_type))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_datetime(_ptr, ref _offset));
				}
			}
			else if(typeof(CGDK.buffer).Equals(_type))
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_buffer(_ptr, ref _offset));
				}
			}
			else
			{
				for (; _count > 0; --_count)
				{
					_object.Add(this._extract_struct(_ptr, ref _offset, _type));
				}
			}
		}
		// Case) STRING
		else if (typeof(string).Equals(_type))
		{
			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_string(_ptr, ref _offset));
			}
		}
		// Case) Array
		else if (_type.IsArray)
		{
			var	temp_type = _type.GetElementType();

			// check)
			Debug.Assert(temp_type!= null);

			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_array(_ptr, ref _offset, temp_type, null, -1));
			}
		}
		// Case) Dictionary
		else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments();

			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_DictionaryX(_ptr, ref _offset, _type, temp_type));
			}
		}
		// Case) List
		else if (typeof(System.Collections.IList).IsAssignableFrom(_type))
		{
			var	temp_type = _type.GetGenericArguments()[0];

			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_ListX(_ptr, ref _offset, _type, temp_type));
			}
		}
		// Case) Class
		else if (_type.IsClass && _is_serializable_type(_type))
		{
			for (; _count > 0; --_count)
			{
				_object.Add(this._extract_class(_ptr, ref _offset, _type));
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

	public void		extract_skip(int _amount)									{ this.m_offset+=_amount; this.m_count-=_amount;}
	public char		extract_char()												{ Debug.Assert(this.m_buffer != null && sizeof(char) <= this.m_count); if(sizeof(char) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(char); this.m_count -= sizeof(char); return (char)this.m_buffer[iPosition];}
	public sbyte	extract_sbyte()												{ Debug.Assert(this.m_buffer != null && sizeof(sbyte) <= this.m_count); if(sizeof(sbyte) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(sbyte); this.m_count -= sizeof(sbyte); return (sbyte)this.m_buffer[iPosition];}
	public byte		extract_byte()												{ Debug.Assert(this.m_buffer != null && sizeof(byte) <= this.m_count); if(sizeof(byte) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(byte); this.m_count -= sizeof(byte); return this.m_buffer[iPosition];}
	public short	extract_short()												{ Debug.Assert(this.m_buffer != null && sizeof(short) <= this.m_count); if(sizeof(short) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(short); this.m_count -= sizeof(short); return BitConverter.ToInt16(m_buffer, iPosition);}
	public ushort	extract_ushort()											{ Debug.Assert(this.m_buffer != null && sizeof(ushort) <= this.m_count); if(sizeof(ushort) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(ushort); this.m_count -= sizeof(ushort); return BitConverter.ToUInt16(m_buffer, iPosition);}
	public int		extract_int()												{ Debug.Assert(this.m_buffer != null && sizeof(int) <= this.m_count); if(sizeof(int) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(int); this.m_count -= sizeof(int); return BitConverter.ToInt32(this.m_buffer, iPosition);}
	public uint		extract_uint()												{ Debug.Assert(this.m_buffer != null && sizeof(uint) <= this.m_count); if(sizeof(uint) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(uint); this.m_count -= sizeof(uint); return BitConverter.ToUInt32(this.m_buffer, iPosition);}
	public long		extract_long()												{ Debug.Assert(this.m_buffer != null && sizeof(long) <= this.m_count); if(sizeof(long) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(long); this.m_count -= sizeof(long); return BitConverter.ToInt64(this.m_buffer, iPosition);}
	public ulong	extract_ulong()												{ Debug.Assert(this.m_buffer != null && sizeof(ulong) <= this.m_count); if(sizeof(ulong) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(ulong); this.m_count -= sizeof(ulong); return BitConverter.ToUInt64(this.m_buffer, iPosition);}
	public float	extract_float()												{ Debug.Assert(this.m_buffer != null && sizeof(float) <= this.m_count); if(sizeof(float) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(float); this.m_count -= sizeof(float); return BitConverter.ToSingle(this.m_buffer, iPosition);}
	public double	extract_double()											{ Debug.Assert(this.m_buffer != null && sizeof(double) <= this.m_count); if(sizeof(double) > this.m_count) throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Buffer size is not enougth (required , count)"); int iPosition = this.m_offset; this.m_offset += sizeof(double); this.m_count -= sizeof(double); return BitConverter.ToDouble(this.m_buffer, iPosition);}
	public string	extract_string()											{ return extract<string>();}

// 3) set_front (값 써넣기)
	private unsafe void set_front_primitive(object _object, int _offset, Type _type)
		{
		// - [버퍼] Pinned 시킨다.
		GCHandle pinnedArray = GCHandle.Alloc(this.m_buffer, GCHandleType.Pinned);

		// - [버퍼_포인터]를 얻는다.
		var ptr = pinnedArray.AddrOfPinnedObject() + this.m_offset + _offset;

		try
		{
			// - casting
			object temp = Convert.ChangeType(_object, _type);

			// - write
			Marshal.StructureToPtr(temp, ptr, false);

			// - Pinned된 [버퍼]를 Free한다.
			pinnedArray.Free();
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

    public unsafe void	set_front<T>(char _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(char))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(sbyte _object, int _offset = 0) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(sbyte))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(byte _object, int _offset = 0) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(byte))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(short _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(short))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(ushort _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(ushort))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(int _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(int))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(uint _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(uint))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void set_front<T>(long _object, int _offset = 0) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(long))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void		set_front<T>(ulong _object, int _offset = 0) where T : unmanaged
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(ulong))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void		set_front<T>(float _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(float))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}
	public unsafe void		set_front<T>(double _object, int _offset = 0) where T : unmanaged 
	{
		// check)
		Debug.Assert(this.m_buffer != null);

		// check)
		Debug.Assert((this.m_buffer.Length - this.m_offset - _offset) >= sizeof(T));

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_buffer.Length - this.m_offset - _offset) < sizeof(T))
			throw new System.OverflowException("buffer overflow");
	#endif

		// 1) get type
		var type = typeof(T);

		// 2) copy
		if (type == typeof(double))
			BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
		else
			this.set_front_primitive(_object, _offset, type);
	}

	public void		set_front(byte[] _object, int _offset_src, int _count, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_offset+this.m_count+_count)<=this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_offset + this.m_count + _count) > this.m_buffer.Length)
			throw new System.OverflowException("out of range");
	#endif
		
		// 1) copy
		System.Buffer.BlockCopy(_object, _offset_src, this.m_buffer, this.m_offset+_offset, _count);
	}
	public void		set_front(buffer _object, int _offset = 0)					
	{
		// check)
		Debug.Assert(this.m_buffer != null && (this.m_offset + this.m_count + _object.m_count) <= this.m_buffer.Length); 

		// check)
		Debug.Assert(_object.m_buffer != null); 
			
	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_offset + this.m_count + _object.m_count) > this.m_buffer.Length)
			throw new System.OverflowException("out of range");
	#endif

		// 1) block copy
		System.Buffer.BlockCopy(_object.m_buffer, _object.m_offset, this.m_buffer, this.m_offset + _offset, _object.m_count);
	}
    public void		set_front(char _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer != null && (this.m_offset + _offset + sizeof(char)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(char))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(sbyte _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(sbyte)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(sbyte))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(byte _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(byte)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(byte))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(short _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(short)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(short))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(ushort _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(ushort)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(ushort))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(int _object, int _offset = 0)
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(int)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(int))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(uint _object, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(uint)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(uint))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(long _object, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(long)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(long))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(ulong _object, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(ulong)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(ulong))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(float _object, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(float)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(float))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}
	public void		set_front(double _object, int _offset = 0) 
	{
		// check) 
		Debug.Assert(this.m_buffer!=null && (this.m_offset + _offset + sizeof(double)) <= this.m_buffer.Length);

	#if _USE_BOUND_CHECK
		// check)
		if(this.m_buffer == null)
			throw new System.NullReferenceException("buffer is not allocated");

		// check)
		if((this.m_count + _offset) < sizeof(double))
			throw new System.OverflowException("out of range");
	#endif

		// 1) copy
		BitConverter.GetBytes(_object).CopyTo(this.m_buffer, this.m_offset + _offset);
	}

// 4) get_front( 값 읽기)
	public T		get_front<T>(int _offset = 0)								{ buffer temp = new buffer(this.m_buffer, this.m_offset+_offset, m_count-_offset); return temp.extract<T>();}
	public void		get_front<T>(ref T _object, int _offset = 0)				{ _object = this.get_front<T>(_offset); }
	public void		get_front<T>(ref char _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_char(_offset); }
	public void		get_front<T>(ref sbyte _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_sbyte(_offset); }
    public void		get_front<T>(ref byte _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_byte(_offset); }
    public void		get_front<T>(ref short _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_short(_offset); }
    public void		get_front<T>(ref ushort _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_ushort(_offset); }
    public void		get_front<T>(ref int _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_int(_offset); }
    public void		get_front<T>(ref uint _object, int _offset = 0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_uint(_offset); }
    public void		get_front<T>(ref long _object, int _offset=0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_long(_offset); }
    public void		get_front<T>(ref ulong _object, int _offset=0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_ulong(_offset); }
    public void		get_front<T>(ref float _object, int _offset=0) where T : unmanaged { Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_float(_offset); }
    public void		get_front<T>(ref double _object, int _offset=0) where T : unmanaged	{ Debug.Assert(Marshal.SizeOf(typeof(T)) == Marshal.SizeOf(_object), "[CGDK.buffer] parameter is different with T (Must be casted as T)"); _object = this.get_front_double(_offset); }

    public char		get_front_char(int _offset = 0)								{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(char)) <= this.m_buffer.Length); return BitConverter.ToChar(this.m_buffer, this.m_offset + _offset);}
	public sbyte	get_front_sbyte(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(sbyte)) <= this.m_buffer.Length); return (sbyte)this.m_buffer[this.m_offset + _offset];}
	public byte		get_front_byte(int _offset = 0)								{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(byte)) <= this.m_buffer.Length); return this.m_buffer[this.m_offset + _offset]; }
	public short	get_front_short(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(short)) <= this.m_buffer.Length); return BitConverter.ToInt16(this.m_buffer, this.m_offset + _offset);}
	public ushort	get_front_ushort(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(ushort)) <= this.m_buffer.Length); return BitConverter.ToUInt16(this.m_buffer, this.m_offset + _offset);}
	public int		get_front_int(int _offset = 0)								{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(int)) <= this.m_buffer.Length); return BitConverter.ToInt32(this.m_buffer, this.m_offset + _offset);}
	public uint		get_front_uint(int _offset = 0)								{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(uint)) <= this.m_buffer.Length); return BitConverter.ToUInt32(this.m_buffer, this.m_offset + _offset);}
	public long		get_front_long(int _offset = 0)								{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(long)) <= this.m_buffer.Length); return BitConverter.ToInt64(this.m_buffer, this.m_offset + _offset);}
	public ulong	get_front_ulong(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(ulong)) <= this.m_buffer.Length); return BitConverter.ToUInt64(this.m_buffer, this.m_offset + _offset);}
	public float	get_front_float(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(float)) <= this.m_buffer.Length); return BitConverter.ToSingle(this.m_buffer, this.m_offset + _offset);}
	public double	get_front_double(int _offset = 0)							{ Debug.Assert(this.m_buffer != null && (_offset + sizeof(double)) <= this.m_buffer.Length); return BitConverter.ToDouble(this.m_buffer, this.m_offset + _offset);}
	public void		get_front_array(byte[] _object, int _offset_src, int _count, int _offset = 0) { Debug.Assert(this.m_buffer != null && (this.m_offset + this.m_count + _object.Length) <= this.m_buffer.Length); System.Buffer.BlockCopy(this.m_buffer, this.m_offset+_offset, _object, _offset_src, _count);}
	public void		get_front_buffer(buffer _object, int _offset = 0)			{ Debug.Assert(this.m_buffer != null && (this.m_offset + this.m_count + _object.m_count) <= this.m_buffer.Length); Debug.Assert(_object.m_buffer != null); System.Buffer.BlockCopy(this.m_buffer, this.m_offset + _offset, _object.m_buffer, _object.m_offset, _object.m_count); }
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
					size += _size_of_DateTime();
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
				// - get element type
				var temp_element_type = _object.GetType().GetElementType();

				// check)
				Debug.Assert(temp_element_type != null);

				// - get size
				size += _size_of_Collection(_object as System.Collections.ICollection, temp_element_type);
			}
			else if (typeof(string).Equals(tmp))
			{
				size += _size_of_string(_object as string);
			}
			else
			{
				var tempObject1 = _object as System.Collections.IDictionary;
				if (tempObject1!=null)
				{
					size += _size_of_Dictionary(tempObject1, tmp.GetGenericArguments());
				}
				else
				{
					var tempObject2 = _object as System.Collections.ICollection;

					if (tempObject2 !=null)
					{
						size += _size_of_Collection(tempObject2, _object.GetType().GetGenericArguments()[0]);
					}
					else if(tmp.IsClass)
					{
						size += _size_Of_class(_object);
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

	private static int	_size_of_DateTime()
	{
		return sizeof(long);
	}

	private static int _size_of_buffer(CGDK.buffer _buffer)
	{
		return (_buffer.data!=null) ? sizeof(UInt64) + _buffer.size : sizeof(UInt64);
	}

#if NET
	private static int	_size_of_Dictionary(System.Collections.IDictionary? _object, Type[] _types)
#else
	private static int	_size_of_Dictionary(System.Collections.IDictionary _object, Type[] _types)
#endif
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			// - -1을 쓰고 끝낸다.
			return sizeof(int);
		}

		// Declaere)
		int	size = 0;

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		size += sizeof(int);

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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_0 != null);

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

				// debug)
				Debug.Assert(temp_type_0 != null);

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

				// debug)
				Debug.Assert(temp_type_0 != null);

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
				var temp_type_1 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_0 != null);

				// debug)
				Debug.Assert(temp_type_1 != null);

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_type_0 = _types[0].GetElementType();

				// debug)
				Debug.Assert(temp_type_0 != null);

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

				// debug)
				Debug.Assert(temp_type_0 != null);

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

				// debug)
				Debug.Assert(temp_type_0 != null);

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

				// debug)
				Debug.Assert(temp_type_0 != null);

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_of_Collection(temp_enum.Key as System.Collections.ICollection, temp_type_0);
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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

				// debug)
				Debug.Assert(temp_type_1 != null);

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
					size += _size_Of_class(temp_enum.Value);
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
					size += _size_Of_class(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsEnum)
			{
				var temp_enum = _object.GetEnumerator();

				int size_1 = Marshal.SizeOf(_types[1].GetFields()[0].FieldType);

				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += size_1;
				}
			}
			else if (_types[1].IsValueType)
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_of_value(temp_enum.Value);
				}
			}
			else if (_types[1].IsArray)
			{
				var temp_type_1 = _types[1].GetElementType();

				// debug)
				Debug.Assert(temp_type_1 != null);

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			else if (typeof(string).Equals(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_of_string(temp_enum.Value as string);
				}
			}
			else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments();

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_of_Dictionary(temp_enum.Value as System.Collections.IDictionary, temp_type_1);
				}
			}
			else if (typeof(System.Collections.ICollection).IsAssignableFrom(_types[1]))
			{
				var temp_type_1 = _types[1].GetGenericArguments()[0];

				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_of_Collection(temp_enum.Value as System.Collections.ICollection, temp_type_1);
				}
			}
			if (_types[1].IsClass && _is_serializable_type(_types[1]))
			{
				var temp_enum = _object.GetEnumerator();
				while (temp_enum.MoveNext())
				{
					size += _size_Of_class(temp_enum.Key);
					size += _size_Of_class(temp_enum.Value);
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
#if NET
	private static int	_size_of_Collection(System.Collections.ICollection? _object, Type _type)
#else
	private static int	_size_of_Collection(System.Collections.ICollection _object, Type _type)
#endif
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_object == null)
		{
			return sizeof(int);
		}

		// Declare) 
		int	size = 0;

		// 1) [데이터 갯수]를 써넣는다. (NULL을 포함한 문자열의 길이)
		size += sizeof(int);

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
					size += _size_of_DateTime();
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
			var tmp_type = _type.GetElementType();

			// debug)
			Debug.Assert(tmp_type != null);

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
				size += _size_Of_class(temp_enum.Current);
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
#if NET
	private static int	_size_Of_class(object? _object, Type? _base_type = null)
#else
	private static int	_size_Of_class(object _object, Type _base_type = null)
#endif
	{
        // check)
        if (_object == null)
            throw new System.Exception("[CGDK.buffer] _object is null");

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
            size += _size_Of_class(_object, temp_type.BaseType);
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

			var temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				size += _size_of(temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				size += sizeof(int);
				continue;
			}
		}
		return	size;
	}
#if NET
	private static int	_size_of_value(object? _object)
#else
	private static int	_size_of_value(object _object)
#endif
	{
		// check)
		if(_object == null)
			throw new System.Exception("[CGDK.buffer] _object is null");

		// Declare)
		int	size = 0;

		Type temp_type = _object.GetType();
		var temp_field = temp_type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

		foreach(var iter in temp_field)
		{
			// Check)
			if(iter.IsNotSerialized==true)
				continue;

			var temp = iter.GetValue(_object);

			// - null이 아닐 경우에만 씀
			if (temp != null)
			{
				size += _size_of(temp);
			}
			// - null일 경우 그냥 -1만 쓰고 끝냄
			else
			{
				// - -1을 쓰고 끝낸다.
				size += sizeof(int);
				continue;
			}
		}

		return	size;
	}
#if NET
	private static int _size_of_string(string? _string)
#else
	private static int _size_of_string(string _string)
#endif
	{
		// Check) 쓰려고 하는 데이터가 null일 경우 -1만 쓰고 끝냄.
		if (_string == null)
		{
			// Return) -1을 쓰고 끝낸다.
			return sizeof(int);
		}

		// 1) [문자열]을 [문자배열]로 변경하고 길이를 구한다.
		var temp_array = _string.ToCharArray();
		var	iStringLength = temp_array.Length;

		// Return) [버퍼_길이]를 리턴한다.
		return	(sizeof(int) +(iStringLength+1)*sizeof(char));
	}


// 1) Buffer
#if NET
	private byte[]?	m_buffer;
#else
	private byte[]	m_buffer;
#endif

	// 2) Buffer중 시작 위치
	private int		m_offset;

	// 3) 사용 길이 (m_iOffset부터 Buffer중 사용하는 끝까지의 길이)
	private int		m_count;
}


}
