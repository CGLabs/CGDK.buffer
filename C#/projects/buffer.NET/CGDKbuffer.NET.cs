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
using System.Collections;
using System.Data;
using System.Diagnostics;
using System.Numerics;
using System.Reflection;
using System.Runtime.CompilerServices;


//----------------------------------------------------------------------------
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
		[System.AttributeUsage(System.AttributeTargets.Class, Inherited = true)]
		public class Serializable : System.Attribute
		{
			public Serializable()
			{
			}
		}
		[System.AttributeUsage(System.AttributeTargets.Field)]
		public class Field : System.Attribute
		{
			private readonly bool _is_serializable;

			public Field(bool is_serializable= true)
			{
				this._is_serializable = is_serializable;
			}

			public bool IsSerializable
			{
				get => _is_serializable;
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

			public long Offset	{ get {return this.m_Offset;}}

			private readonly long m_Offset;
		}
	}

	public struct Offset
	{
		public Offset() { this.amount = 0; }
		public Offset(in int _amount) { this.amount = _amount; }
		public int amount;
	}
	public struct Size
	{
		public Size() { this.amount = 0; }
		public Size(in int _amount) { this.amount = _amount; }
		public int amount;
	}

	public struct buffer
	{
		public buffer(in byte[]? _buffer, in int _offset = 0, in int _count = 0)
		{
			this.m_buffer = _buffer;
			this.m_offset = _offset;
			this.m_count = _count;
		}
		public buffer(in buffer _buffer)
		{
			this.m_buffer = _buffer.m_buffer;
			this.m_offset = _buffer.m_offset;
			this.m_count = _buffer.m_count;
		}
		public buffer(in int _Size)
		{
			this.m_buffer = new byte[_Size];
			this.m_offset = 0;
			this.m_count = 0;
		}

		public readonly buffer Clone()
		{
			// 1(
			if (this.m_buffer == null)
				return new buffer();

			// 1) get capacity
			var temp_capacity = this.m_buffer.Length;

			// 2) 새로운 버퍼를 생성한다.
			byte[] temp = new byte[temp_capacity];

			// 3) [문자열]을 복사해 넣는다.
			if(this.m_buffer != null)
				System.Buffer.BlockCopy(this.m_buffer, 0, temp, 0, temp_capacity);

			// 4) 적용한다.
			return new buffer(temp, m_offset, m_count);
		}

		// definitions) 
		public const int	SIZE_OF_CRC	 = sizeof(uint);

		// 1) 생성/버퍼설정
		public void			Alloc(in int _Size)
		{
			this.m_buffer = new byte[_Size];
			this.m_offset = 0;
			this.m_count = 0;
		}
		public void			SetBuffer(byte[] _buffer, in int _offset, in int _length)
		{
			// check) _offset+_length가 _buffer의 크기보다 크면 안됀다.
			Debug.Assert((_offset+_length) <= _buffer.Length);

			// check) _offset이나 _length의 길이가 _buffer의 크기를 초과할 경우 Exception을 던진다.
			if ((_offset+_length) > _buffer.Length)
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");

			// 1) 값을 적용
			this.m_buffer = _buffer;
			this.m_offset = _offset;
			this.m_count = _length;
		}
		public void			SetBuffer(byte[] _buffer, in int _offset)
		{
			// check) _offset+_length가 _buffer의 크기보다 크면 안됀다.
			Debug.Assert(_offset <= _buffer.Length);

			// check) _offset이나 _length의 길이가 _buffer의 크기를 초과할 경우 Exception을 던진다.
			if (_offset>_buffer.Length)
				throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");

			// 1) 값을 적용한다.
			this.m_buffer = _buffer;
			this.m_offset = _offset;
			this.m_count = _buffer.Length-_offset;
		}
		public byte[]?		Clear()
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
		public readonly bool IsEmpty() { return this.m_buffer==null;}
		public readonly int Capacity { get { return (this.m_buffer != null) ? this.m_buffer.Length : 0; } }
		public readonly int RemainedSize() { return (this.m_buffer!=null) ? (this.m_buffer.Length - this.m_offset - this.m_count) : 0; }

		public readonly byte[]? Data { get { return this.m_buffer;}}
		public int			Offset { readonly get { return this.m_offset;} set { this.m_offset = value;}}
		public int			Size { readonly get { return this.m_count;} set { this.m_count = value;}}
		public int			Count { readonly get { return this.m_count;} set { this.m_count = value;}}
																				  
		// - for C# User															  
		public byte[]?		Array { readonly get { return this.m_buffer; } set { this.m_buffer = value; } }

// ----------------------------------------------------------------
// 연산자 Overload
// ----------------------------------------------------------------
// 1) +offset (Offset 만큼 버퍼를 extract한 새로운 버퍼를 받는다. offset만큼 _offset는 증가하고 count는 뺀 버퍼. 음수도 가능)
public static		buffer operator + (in buffer _lhs, in Offset _offset)
		{
			// check)
			if(_lhs.Array == null)
				throw new System.NullReferenceException("buffer is not allocated");

			// check) 
			Debug.Assert((_offset.amount > 0) ? (_offset.amount <= _lhs.Count) : (-_offset.amount <= _lhs.Offset));

			// check)
			if((_offset.amount > 0) ? (_offset.amount > _lhs.Count) : (-_offset.amount > _lhs.Offset))
				throw new System.OverflowException("buffer overflow");

			// 1) create
			return new buffer(_lhs.Array, _lhs.Offset + _offset.amount, _lhs.Count - _offset.amount);
		}
		// 2) -offset (Offset 만큼 버퍼를 앞으로 늘린(prepend)한 버퍼를 받는다. _offset만큼 offset을 빼고 count를 늘린 버퍼. 음수도 가능)
		public static		buffer operator - (in buffer _lhs, in Offset _offset)
		{
			// check)
			if(_lhs.Array == null)
				throw new System.NullReferenceException("buffer is not allocated");

			// check) 
			Debug.Assert((_offset.amount > 0) ? (-_offset.amount <= _lhs.Offset) : (-_offset.amount <= _lhs.Count) );

			// check)
			if((_offset.amount > 0) ? (-_offset.amount > _lhs.Offset) : (-_offset.amount > _lhs.Count))
				throw new System.OverflowException("buffer overflow");

			// 1) create
			return new buffer(_lhs.Array, _lhs.Offset - _offset.amount, _lhs.Count + _offset.amount);
		}
		// 3) +count (count 만큼 크기(count)를 늘린 새로운 버퍼. 음수도 가능)
		public static		buffer operator + (in buffer _lhs, in Size _rhs)
		{
			// check) 
			Debug.Assert(_lhs.m_buffer != null && _lhs.Offset >= _rhs.amount && _rhs.amount <= (_lhs.Capacity - _lhs.Count)); 

			// check)
			if(_lhs.Array == null)
				throw new System.NullReferenceException("buffer is not allocated");

			// check)
			if(_lhs.Offset < _rhs.amount || _rhs.amount > (_lhs.Capacity - _lhs.Count))
				throw new System.OverflowException("buffer overflow");

			// 1) create
			return new buffer(_lhs.Array, _lhs.Offset, _lhs.Count + _rhs.amount);
		}
		// 4) -count (count 만큼 크기(count)를 줄인 새로운 버퍼. 음수도 가능)
		public static		buffer operator - (in buffer _lhs, in Size _rhs)
		{
			// check) 
			Debug.Assert(_lhs.m_buffer != null && _lhs.Offset >= _rhs.amount && _rhs.amount <= (_lhs.Capacity - _lhs.Count)); 

			// check)
			if(_lhs.Array == null)
				throw new System.NullReferenceException("buffer is not allocated");

			// check)
			if(_lhs.Offset < _rhs.amount || _rhs.amount > (_lhs.Capacity - _lhs.Count))
				throw new System.OverflowException("buffer overflow");

			// 1) create
			return new buffer(_lhs.Array, _lhs.Offset, _lhs.Count + _rhs.amount);
		}
		// 5) Offset값만 교체한 새로운 버퍼(_lhs에서 Offset값만 교체한 버퍼를 받는다.)
		public static		buffer operator ^(in buffer _lhs, in Offset _offset)
		{
			// check) 
			Debug.Assert(_lhs.IsEmpty() == false && _offset.amount >= 0 && (_offset.amount + _lhs.Count) <= _lhs.Capacity);

			// check)
			if (_lhs.IsEmpty())
				throw new System.NullReferenceException("buffer not allocated");

			// check)
			if (_offset.amount < 0 || (_offset.amount + _lhs.Count) > _lhs.Capacity)
				throw new System.NullReferenceException("'offset' out of range");

			// 1) create 
			return new buffer(_lhs.Array, _lhs.Offset, _offset.amount);
		}
		// 6) Count값만 교체한 새로운 버퍼(_lhs에서 Count만 교체한 버퍼를 받는다.)
		public static		buffer operator ^(in buffer _lhs, in Size _count)
		{
			// check) 
			Debug.Assert(_lhs.m_buffer != null && _count.amount >= 0 && (_lhs.Offset + _count.amount) <= _lhs.Capacity);

			// check)
			if (_lhs.IsEmpty())
				throw new System.NullReferenceException("buffer not allocated");

			// check)
			if (_count.amount < 0 || (_lhs.Offset + _count.amount) > _lhs.Capacity)
				throw new System.NullReferenceException("'offset' out of range");

			// 1) create 
			return new buffer(_lhs.Array, _lhs.Offset, _count.amount);
		}
		// 7) offset/count를 함께 교체한 새로운 버퍼
		public static		buffer operator ^(in buffer _lhs, in (Offset offset,Size size) _rhs)
		{
			// check) 
			Debug.Assert(_lhs.m_buffer != null && _rhs.offset.amount >= 0 && _rhs.size.amount >= 0 && (_rhs.offset.amount + _rhs.size.amount <= _lhs.Capacity));

			// check)
			if (_lhs.IsEmpty())
				throw new System.NullReferenceException("buffer not allocated");

			// check)
			if (_rhs.offset.amount < 0 || _rhs.size.amount < 0 || (_rhs.offset.amount + _rhs.size.amount) > _lhs.Capacity)
				throw new System.NullReferenceException("'offset' out of range");

			// 1) create 
			return new buffer(_lhs.Array, _rhs.offset.amount, _rhs.size.amount);
		}

		// ----------------------------------------------------------------
		//  직렬화
		//
		//  1. 먼저해당 Serializer를 얻어 온다.(이것은 처음에 생성해 static 변수에 저장해 놓고 계속 사용한다.
		//     (BufferSerializer.Get_List<T>.instance 가 Caching된 Serializer)
		//  2. 처음 Serialize가 생성될 때만 Reflection을 사용해 T 클래스에 적합한 Serialize를 생성한다.
		//  3. Serializer가 Extract나 GetSizeOf 과정에서 만들어 질 수도 있다.
		//  4. 직렬화에 필요한 파라미터들을 얻는다.
		//
		//     ptr_pre   -> ProcessAppend 함수가 수행된 후 쓰여진 길이를 구하기 위해 저장해 놓는다.
		//     ptr_now   -> 쓰여질 위치 포인터. 버퍼에서 쓰여진 멘 끝을 가르킨다.(m_buffer + m_offset + m_count)
		//    ptr_bound -> 할당된 버퍼의 제일 끝을 가르킨다. bound 검사에 사용된다.
		//
		//  5. Serializer에 이 파라미터들을 넘겨 ProcessAppend를 호출하면 직렬화를 시작한다.
		//  6. 직렬화가 모두 끝난후 ptr_now - ptr_pre를 해서 쓰여진 길이를 구해 m_count에 더해 준다.
		//  7. 직렬화 끝!
		// ----------------------------------------------------------------
		public unsafe void	Append<T>(in T _value)
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

		#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
		#endif
			fixed (byte* ptr = this.m_buffer)
			{
				// 1) calculare ptr_now & ptr_bound
				var ptr_pre = ptr + this.m_offset + this.m_count;
				var ptr_now = ptr_pre;
				var ptr_bound = ptr + this.m_buffer.Length;

				// 2) append
				BufferSerializer.Get<T>.instance.ProcessAppend(ref ptr_now, ptr_bound, _value);

				// 3) update offset & count
				this.m_count += (int)(ptr_now - ptr_pre);
			}
		}
		public void			Append (in byte[] _buffer, in int _offset, in int _count)
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
		// ----------------------------------------------------------------
		// raw 문자열 Append
		//
		//  1. string을 append할 경우 먼저 Int32크기의 문자열 길이를 저장한 후 문자열을 저장한다.
		//     하지만 AppendText는 문자열의 길이 정보(Int32)를 쓰지 않고 그냥 바로 문자열 정보만 저장해 놓는다.
		//  2. 여러 문자열을 합쳐야 할 경우 혹은 문자열 데이터만 만들어야 할 경우(대표적으로 Web)에서 유용한다.			        
		// ----------------------------------------------------------------
		public void			AppendText (in string _object)
		{
			// 1) 문자열을 배열로 변경하고 길이를 구한다.
			var temp_array = _object.ToCharArray();
			var iStringLength = temp_array.Length;

			// check) 버퍼의 크기가 충분한가 확인한다.
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
		// ----------------------------------------------------------------
		// raw 문자열 Append 함수 (Connection)
		// ----------------------------------------------------------------
		public void			AppendText (in ICollection<string> _Collection)
		{
			foreach (var iter in _Collection)
			{
				this.AppendText(iter);
			}
		}
		// ----------------------------------------------------------------
		// raw 문자열 Append 함수 (Params)
		// ----------------------------------------------------------------
		public void			AppendText (params string[] _Array)
		{
			foreach (var iter in _Array)
			{
				this.AppendText(iter);
			}
		}
		// ----------------------------------------------------------------
		// 전체 버퍼 데이타에 대한 CRC 추가 (지원안함)
		// ----------------------------------------------------------------
		public void			AppendCRC ()
		{
			// (!) 이 버전에서는 지원하지 않는다.
			Debug.Assert(false);

			// 1) 길이만 늘려준다.
			this.m_count += SIZE_OF_CRC;
		}
		// ----------------------------------------------------------------
		// 전체 버퍼 데이타에 대한 CRC 추가 (지원안함)
		// ----------------------------------------------------------------
		public unsafe void	Append<K, V>(in Dictionary<K, V> _value) where K : notnull
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

		#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
		#endif

			fixed (byte* ptr = this.m_buffer)
			{
				// 1) calculare ptr_now & ptr_bound
				var ptr_pre = ptr + this.m_offset + this.m_count;
				var ptr_now = ptr_pre;
				var ptr_bound = ptr + this.m_buffer.Length;

				// 2) append
				BufferSerializer.Get_Dictionary<K, V>.instance.ProcessAppend(ref ptr_now, ptr_bound, _value);

				// 3) update offset & count
				this.m_count += (int)(ptr_now - ptr_pre);
			}
		}
		public unsafe void	Append<T>(in List<T> _value)
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
#endif
			// 설명) 직렬화 함수 (역직렬화는 Extract<T> 함수)
			//       1. 먼저해당 Serializer를 얻어 온다.(이것은 처음에 생성해 static 변수에 저장해 놓고 계속 사용한다.
			//          (BufferSerializer.Get_List<T>.instance 가 Caching된 Serializer)
			//       2. 처음 Serialize가 생성될 때만 Reflection을 사용해 T 클래스에 적합한 Serialize를 생성한다.
			//       3. Serializer가 Extract나 GetSizeOf 과정에서 만들어 질 수도 있다.
			//       4. 직렬화에 필요한 파라미터들을 얻는다.
			//          ptr_pre   -> ProcessAppend 함수가 수행된 후 쓰여진 길이를 구하기 위해 저장해 놓는다.
			//          ptr_now   -> 쓰여질 위치 포인터. 버퍼에서 쓰여진 멘 끝을 가르킨다.(m_buffer + m_offset + m_count)
			//	   	    ptr_bound -> 할당된 버퍼의 제일 끝을 가르킨다. bound 검사에 사용된다.
			//       5. Serializer에 이 파라미터들을 넘겨 ProcessAppend를 호출하면 이 함수에서 실직적으로 직렬화를 수행한다.
			//       6. 직렬화가 모두 끝난후 ptr_now - ptr_pre를 해서 쓰여진 길이를 구해 m_count에 더해 준다.
			//       7. 직렬화 끝!
			fixed (byte* ptr = this.m_buffer)
			{
				// 1) calculare ptr_now & ptr_bound
				var ptr_pre = ptr + this.m_offset + this.m_count;
				var ptr_now = ptr_pre;
				var ptr_bound = ptr + this.m_buffer.Length;

				// 2) append
				BufferSerializer.Get_List<T>.instance.ProcessAppend(ref ptr_now, ptr_bound, _value);

				// 3) update offset & count
				this.m_count += (int)(ptr_now - ptr_pre);
			}
		}
		public static implicit operator ArraySegment<byte>(in buffer _rhs)
		{
			// check) 
			Debug.Assert(_rhs.Array != null);

			// 1) create 
			return new ArraySegment<byte>(_rhs.Array, _rhs.Offset, _rhs.Count);
		}
		public static explicit operator buffer(in ArraySegment<byte> _rhs)
		{
			// 1) create 
			return new buffer(_rhs.Array, _rhs.Offset, _rhs.Count);
		}

		// ----------------------------------------------------------------
		// Skip Append (_amount만큼 띄우기)
		// ----------------------------------------------------------------
		public void AppendSkip(in int _amount)
		{
			// check) 
			Debug.Assert(this.m_buffer != null && (this.m_buffer.Length - this.m_offset - this.m_count) >= _amount);

			// 1) add size			
			this.m_count += _amount;
		}

		// ----------------------------------------------------------------
		// 역직렬화
		// 
		//  1. 먼저 해당 Serializer를 얻어 온다.(이것은 처음에 생성해 static 변수에 저장해 놓고 계속 사용한다.
		//     (BufferSerializer.Get_List<T>.instance 가 Caching된 Serializer)
		//  2. 처음 Serialize가 생성될 때만 Reflection을 사용해 T 클래스에 적합한 Serialize를 생성한다.
		//  3. Serializer가 Append나 GetSizeOf 과정에서 만들어 질 수도 있다.
		//  4. 역직렬화에 필요한 파라미터들을 얻는다.
		//
		//     ptr_now -> 현재 읽어낼 위치 버퍼 데이터의 제일 처음을 가르킨다.(m_buffer + m_offset)
		//	   count -> 현재 남은 데이터의 길이. Bound 체크 정보로 사용한다.
		//
		//  5. Serializer에 이 파라미터들을 넘겨 ProcessExtract를 호출하면 직렬화를 시작한다.
		//  6. 역직렬화가 모두 끝아면 return값으로 역직렬화한 데이터가 넘어 온다.
		//  7. 역직렬화가 읽어낸 만큼 m_offert 값을 옮겨주모 _count는 그대로 m_cout에 저장한다.
		//  8. 역직렬화 끝!
		// ----------------------------------------------------------------
		public unsafe T?	Extract<T>()
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

		#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
		#endif
			var count = this.m_count;

			fixed (byte* ptr = this.m_buffer)
			{
				// 1) prepare extract
				var ptr_now = ptr + this.m_offset;

				// 2) extract
				var temp = BufferSerializer.Get<T>.instance.ProcessExtract(ref ptr_now, ref count);

				// 3) update offset & count
				this.m_offset = (int)(ptr_now - ptr);
				this.m_count = count;

				// check)
				Debug.Assert(temp != null);

				// retrn) 
				return temp;
			}
		}
		// 3) set_front (값 써넣기/읽기)
		// ----------------------------------------------------------------
		// 설명) Poke함수
		//       1. 버퍼 데이터의 크기에는 아무런 영향없이 특정 위치의 데이터를 써넣을 때 사용횐다.
		//       2. _offset 만큼 떠어진 위치에 데이터를 써넣는다.
		//       3. 이 함수는 Append기능이 아니므로 써넣은 이후 버퍼의 Offset이나 Count값에 영향을 주지 않는다.ㄴ
		//       4. 버퍼의 데이터가 존재하는 영역 내에서만 쓰기가 가능하다.
		//           즉 m_buffer + m_offset 에서 m_bufer + m_offset + m_count 안에만 변경할 수 있다.
		//       5. 써넣는 데이터는 임의의 자료형도 모두 가능하지만 자료형 안정성(Type Safe)는 제공하지 않는다.
		// ----------------------------------------------------------------
		public unsafe void	SetFront<T>(in T _object, in int _offset = 0)
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

		#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
		#endif
			fixed (byte* ptr = this.m_buffer)
			{
				// 1) calculare ptr_now & ptr_bound
				var ptr_now = ptr + this.m_offset + _offset;
				var ptr_bound = ptr + this.m_buffer.Length;

				// 2) append
				BufferSerializer.Get<T>.instance.ProcessAppend(ref ptr_now, ptr_bound, _object);
			}
		}
		// ----------------------------------------------------------------
		// 설명) Peek함수
		//       1. 버퍼 데이터의 크기에는 아무런 영향없이 특정 위치의 데이터를 읽어 올 때  사용횐다.
		//       2. _offset 만큼 떠어진 위치에 데이터를 읽어 온다.
		//       3. 이 함수는 Extract가 아니므로 Offset이나 Count값에 영향을 주지 않는다.
		//       4. 버퍼의 데이터가 존재하는 영역 내에서만 쓰기가 가능하다.
		//           즉 m_buffer + m_offset 에서 m_bufer + m_offset + m_count 안에만 변경할 수 있다.
		//       5. 읽어내는 데이터는 임의의 자료형도 모두 가능하지만 자료형 안정성(Type Safe)는 제공하지 않는다.
		// ----------------------------------------------------------------
		public unsafe T?	GetFront<T>(in int _offset = 0)
		{
			// check) 
			Debug.Assert(this.m_buffer != null);

		#if _USE_BOUND_CHECK
			// check)
			if(this.m_buffer == null)
				throw new System.NullReferenceException("buffer is not allocated");
		#endif

			// 1) get count
			var count = this.m_count;

			fixed (byte* ptr = this.m_buffer)
			{
				// 2) prepare extract
				var ptr_now = ptr + this.m_offset + _offset;

				// 3) extract
				return BufferSerializer.Get<T>.instance.ProcessExtract(ref ptr_now, ref count);
			}
		}

		// ----------------------------------------------------------------
		// Static) 직렬화 크기 구하는 정적(static)함수
		//  1. _object를 직렬화했을 때 메모리 크기를 구한다.
		//  2. 정적함수이므로 객체 없이 클래스명으로 바로 실행이 가능하다.
		//  3. 데이터의 크기가 실시간으로 계산되므로 성능에는 영향을 미친다.
		// ----------------------------------------------------------------
		public static int	GetSizeOf<T>(in T _object)
		{
			return BufferSerializer.Get<T>.instance.ProcessGetSizeOf(_object);
		}

		// 1) Buffer
		private byte[]?		m_buffer;

		// 2) Buffer중 시작 위치
		private int			m_offset;

		// 3) 사용 길이 (m_iOffset부터 Buffer중 사용하는 끝까지의 길이)
		private int			m_count;
	}

	namespace BufferSerializer
	{
		public interface IBase<T>
		{
			unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object);
			unsafe T? ProcessExtract(ref byte* _ptr, ref int _count);
			unsafe int ProcessGetSizeOf(T? _object);
		}

		public class SerializerPrimitive<T> : IBase<T> where T : unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T _object)
			{
				// 1) write
				Unsafe.Write<T>(_ptr, _object);

				// 2) update ptr
				_ptr += sizeof(T);
			}
			public unsafe T ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) read
				var p = Unsafe.Read<T>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(T);
				_count -= sizeof(T);

				// return) 
				return p;
			}
			public unsafe int ProcessGetSizeOf(T _object) { return sizeof(T); }
		}
		public class SerializerPrimitive_object<T> : IBase<object> where T : unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) write
				Unsafe.Write<T>(_ptr, (T)_object);

				// 2) update ptr
				_ptr += sizeof(T);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) read
				var p = Unsafe.Read<T>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(T);
				_count -= sizeof(T);

				// return) 
				return p;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return sizeof(T);
			}
		}
		public class SerializerDateTime : IBase<DateTime>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, DateTime _object) { Unsafe.AsRef<long>(_ptr) = _object.Ticks; _ptr += sizeof(long); }
			public unsafe DateTime ProcessExtract(ref byte* _ptr, ref int _count) { var p = _ptr; _ptr += sizeof(long); _count -= sizeof(long); return new DateTime(Unsafe.AsRef<long>(p)); }
			public unsafe int ProcessGetSizeOf(DateTime _object) { return sizeof(long); }
		}
		public class Serialize_DateTime_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object) { Debug.Assert(_object != null); Unsafe.AsRef<long>(_ptr) = ((DateTime)_object).Ticks; _ptr += sizeof(long); }
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count) { var p = _ptr; _ptr += sizeof(long); _count -= sizeof(long); return new DateTime(Unsafe.AsRef<long>(p)); }
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(long); }
		}
		public class SerializerVector2 : IBase<Vector2>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Vector2 _object)
			{
				// 2) write
				*(float*)_ptr = _object.X; _ptr += sizeof(float);
				*(float*)_ptr = _object.Y; _ptr += sizeof(float);
			}
			public unsafe Vector2 ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector2(
						*(float*)(_ptr +  0),
						*(float*)(_ptr +  4)
					);

				// 3) update count
				_ptr += sizeof(float) * 2;
				_count -= sizeof(float) * 2;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Vector2 _object) { return sizeof(float) * 2; }
		}
		public class SerializerVector2_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				Vector2 temp = (Vector2)_object;

				// 2) write
				*(float*)_ptr = temp.X; _ptr += sizeof(float);
				*(float*)_ptr = temp.Y; _ptr += sizeof(float);
			}
			public unsafe object ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector2(
						*(float*)(_ptr +  0),
						*(float*)(_ptr +  4)
					);

				// 2) update count
				_ptr += sizeof(float) * 2;
				_count -= sizeof(float) * 2;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(float) * 2; }
		}
		public class SerializerVector3 : IBase<Vector3>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Vector3 _object)
			{
				// 1) write
				*(float*)_ptr = _object.X; _ptr += sizeof(float);
				*(float*)_ptr = _object.Y; _ptr += sizeof(float);
				*(float*)_ptr = _object.Z; _ptr += sizeof(float);
			}
			public unsafe Vector3 ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector3(
						*(float*)(_ptr +  0),
						*(float*)(_ptr +  4),
						*(float*)(_ptr +  8)
					);

				// 2) update count
				_ptr += sizeof(float) * 3;
				_count -= sizeof(float) * 3;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Vector3 _object) { return sizeof(float) * 3; }
		}
		public class SerializerVector3_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				Vector3 temp = (Vector3)_object;

				// 2) write
				*(float*)_ptr = temp.X; _ptr += sizeof(float);
				*(float*)_ptr = temp.Y; _ptr += sizeof(float);
				*(float*)_ptr = temp.Z; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector3(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8)
					);

				// 2) update count
				_ptr += sizeof(float) * 3;
				_count -= sizeof(float) * 3;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(float) * 3; }
		}
		public class SerializerVector4 : IBase<Vector4>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Vector4 _object)
			{
				// 2) write
				*(float*)_ptr = _object.X; _ptr += sizeof(float);
				*(float*)_ptr = _object.Y; _ptr += sizeof(float);
				*(float*)_ptr = _object.Z; _ptr += sizeof(float);
				*(float*)_ptr = _object.W; _ptr += sizeof(float);
			}
			public unsafe Vector4 ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector4(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Vector4 _object) { return sizeof(float) * 4; }
		}
		public class SerializerVector4_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				Vector4 temp = (Vector4)_object;

				// 2) write
				*(float*)_ptr = temp.X; _ptr += sizeof(float);
				*(float*)_ptr = temp.Y; _ptr += sizeof(float);
				*(float*)_ptr = temp.Z; _ptr += sizeof(float);
				*(float*)_ptr = temp.W; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Vector4(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(float) * 4; }
		}
		public class SerializerPlane : IBase<Plane>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Plane _object)
			{
				// 2) write
				*(float*)_ptr = _object.Normal.X; _ptr += sizeof(float);
				*(float*)_ptr = _object.Normal.Y; _ptr += sizeof(float);
				*(float*)_ptr = _object.Normal.Z; _ptr += sizeof(float);
				*(float*)_ptr = _object.D; _ptr += sizeof(float);
			}
			public unsafe Plane ProcessExtract(ref byte* _ptr, ref int _count)
			{
				var temp = new Plane(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Plane _object) { return sizeof(float) * 4; }
		}
		public class SerializerPlane_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				Plane temp = (Plane)_object;

				// 2) write
				*(float*)_ptr = temp.Normal.X; _ptr += sizeof(float);
				*(float*)_ptr = temp.Normal.Y; _ptr += sizeof(float);
				*(float*)_ptr = temp.Normal.Z; _ptr += sizeof(float);
				*(float*)_ptr = temp.D; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				var temp = new Plane(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(float) * 4; }
		}
		public class SerializerQuaternion : IBase<Quaternion>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Quaternion _object)
			{
				// 2) write
				*(float*)_ptr = _object.X; _ptr += sizeof(float);
				*(float*)_ptr = _object.Y; _ptr += sizeof(float);
				*(float*)_ptr = _object.Z; _ptr += sizeof(float);
				*(float*)_ptr = _object.W; _ptr += sizeof(float);
			}
			public unsafe Quaternion ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Quaternion(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Quaternion _object) { return sizeof(float) * 4; }
		}
		public class SerializerQuaternion_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				Quaternion temp = (Quaternion)_object;

				// 2) write
				*(float*)_ptr = temp.X; _ptr += sizeof(float);
				*(float*)_ptr = temp.Y; _ptr += sizeof(float);
				*(float*)_ptr = temp.Z; _ptr += sizeof(float);
				*(float*)_ptr = temp.W; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Quaternion(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12)
					);

				// 2) update count
				_ptr += sizeof(float) * 4;
				_count -= sizeof(float) * 4;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object) { return sizeof(float) * 4; }
		}
		public class SerializerMatrix3x2 : IBase<Matrix3x2>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Matrix3x2 _object)
			{
				// 1) write data
				*(float*)_ptr = _object.M11; _ptr += sizeof(float);
				*(float*)_ptr = _object.M12; _ptr += sizeof(float);

				*(float*)_ptr = _object.M21; _ptr += sizeof(float);
				*(float*)_ptr = _object.M22; _ptr += sizeof(float);

				*(float*)_ptr = _object.M31; _ptr += sizeof(float);
				*(float*)_ptr = _object.M32; _ptr += sizeof(float);
			}
			public unsafe Matrix3x2 ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Matrix3x2(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),

						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12),

						*(float*)(_ptr + 16),
						*(float*)(_ptr + 20)
					);

				// 2) update count
				_ptr += sizeof(float) * 6;
				_count -= sizeof(float) * 6;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Matrix3x2 _object)
			{
				return sizeof(float) * 6;
			}
		}
		public class SerializerMatrix3x2_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				var temp = (Matrix3x2)_object;

				// 2) write data
				*(float*)_ptr = temp.M11; _ptr += sizeof(float);
				*(float*)_ptr = temp.M12; _ptr += sizeof(float);

				*(float*)_ptr = temp.M21; _ptr += sizeof(float);
				*(float*)_ptr = temp.M22; _ptr += sizeof(float);

				*(float*)_ptr = temp.M31; _ptr += sizeof(float);
				*(float*)_ptr = temp.M32; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Matrix3x2(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),

						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12),

						*(float*)(_ptr + 16),
						*(float*)(_ptr + 20)
					);

				// 2) update count
				_ptr += sizeof(float) * 6;
				_count -= sizeof(float) * 6;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return sizeof(float) * 6;
			}
		}
		public class SerializerMatrix4x4 : IBase<Matrix4x4>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Matrix4x4 _object)
			{
				// 1) write data
				*(float*)_ptr = _object.M11; _ptr += sizeof(float);
				*(float*)_ptr = _object.M12; _ptr += sizeof(float);
				*(float*)_ptr = _object.M13; _ptr += sizeof(float);
				*(float*)_ptr = _object.M14; _ptr += sizeof(float);

				*(float*)_ptr = _object.M21; _ptr += sizeof(float);
				*(float*)_ptr = _object.M22; _ptr += sizeof(float);
				*(float*)_ptr = _object.M23; _ptr += sizeof(float);
				*(float*)_ptr = _object.M24; _ptr += sizeof(float);

				*(float*)_ptr = _object.M31; _ptr += sizeof(float);
				*(float*)_ptr = _object.M32; _ptr += sizeof(float);
				*(float*)_ptr = _object.M33; _ptr += sizeof(float);
				*(float*)_ptr = _object.M34; _ptr += sizeof(float);

				*(float*)_ptr = _object.M41; _ptr += sizeof(float);
				*(float*)_ptr = _object.M42; _ptr += sizeof(float);
				*(float*)_ptr = _object.M43; _ptr += sizeof(float);
				*(float*)_ptr = _object.M44; _ptr += sizeof(float);
			}
			public unsafe Matrix4x4 ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Matrix4x4(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12),

						*(float*)(_ptr + 16),
						*(float*)(_ptr + 20),
						*(float*)(_ptr + 24),
						*(float*)(_ptr + 28),

						*(float*)(_ptr + 32),
						*(float*)(_ptr + 36),
						*(float*)(_ptr + 40),
						*(float*)(_ptr + 44),

						*(float*)(_ptr + 48),
						*(float*)(_ptr + 52),
						*(float*)(_ptr + 56),
						*(float*)(_ptr + 60)
					);

				// 2) update count
				_ptr += sizeof(float) * 16;
				_count -= sizeof(float) * 16;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(Matrix4x4 _object)
			{
				return sizeof(float) * 16;
			}
		}
		public class SerializerMatrix4x4_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) casting
				var temp = (Matrix4x4)_object;

				// 2) write data
				*(float*)_ptr = temp.M11; _ptr += sizeof(float);
				*(float*)_ptr = temp.M12; _ptr += sizeof(float);
				*(float*)_ptr = temp.M13; _ptr += sizeof(float);
				*(float*)_ptr = temp.M14; _ptr += sizeof(float);

				*(float*)_ptr = temp.M21; _ptr += sizeof(float);
				*(float*)_ptr = temp.M22; _ptr += sizeof(float);
				*(float*)_ptr = temp.M23; _ptr += sizeof(float);
				*(float*)_ptr = temp.M24; _ptr += sizeof(float);

				*(float*)_ptr = temp.M31; _ptr += sizeof(float);
				*(float*)_ptr = temp.M32; _ptr += sizeof(float);
				*(float*)_ptr = temp.M33; _ptr += sizeof(float);
				*(float*)_ptr = temp.M34; _ptr += sizeof(float);

				*(float*)_ptr = temp.M41; _ptr += sizeof(float);
				*(float*)_ptr = temp.M42; _ptr += sizeof(float);
				*(float*)_ptr = temp.M43; _ptr += sizeof(float);
				*(float*)_ptr = temp.M44; _ptr += sizeof(float);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) make 
				var temp = new Matrix4x4(
						*(float*)(_ptr + 0),
						*(float*)(_ptr + 4),
						*(float*)(_ptr + 8),
						*(float*)(_ptr + 12),

						*(float*)(_ptr + 16),
						*(float*)(_ptr + 20),
						*(float*)(_ptr + 24),
						*(float*)(_ptr + 28),

						*(float*)(_ptr + 32),
						*(float*)(_ptr + 36),
						*(float*)(_ptr + 40),
						*(float*)(_ptr + 44),

						*(float*)(_ptr + 48),
						*(float*)(_ptr + 52),
						*(float*)(_ptr + 56),
						*(float*)(_ptr + 50)
					);

				// 2) update count
				_ptr += sizeof(float) * 16;
				_count -= sizeof(float) * 16;

				// return) 
				return temp;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return sizeof(float) * 16;
			}
		}

		public class SerializerEnum<T> : IBase<T>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				Debug.Assert(_object != null);

				// 1) write
				Unsafe.Write<T>(_ptr, _object);

				// 2) update ptr
				_ptr += sizeof(int);
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) read
				var p = Unsafe.Read<T>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(int);
				_count -= sizeof(int);

				// return) 
				return p;
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				Debug.Assert(_object != null);

				return sizeof(int);
			}
		}
		public class SerializerEnum_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_object != null);

				// 1) copy
				*(int*)_ptr = (int)_object;

				// 2) add ptr
				_ptr += sizeof(int);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// 1) store pointer
				var p = _ptr;

				// 2) update ptr & count
				_ptr += sizeof(int);
				_count -= sizeof(int);

				// return) 
				return *(int*)p;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return sizeof(int);
			}
		}

		public class SerializerBuffer : IBase<buffer>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, buffer _object)
			{
				// Attention) buffer의 size는 int64이다.

				// 1) get buffer
				var buf = _object.Array;

				// check)
				if (buf == null)
				{
					// - 0을 쓰고 끝낸다.
					Unsafe.AsRef<Int64>(_ptr) = 0;
					_ptr += sizeof(Int64);
					return;
				}

				fixed (byte* buf_source = buf)
				{
					// check)
					Debug.Assert(_ptr + sizeof(Int64) + _object.Size <= _ptr_bound);

					// 1) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
					Unsafe.AsRef<Int64>(_ptr) = _object.Size;
					_ptr += sizeof(Int64);

					// check)
					if (_object.Size == 0)
						return;

					// 3) 복사해 붙인다.
					System.Buffer.MemoryCopy(buf_source, _ptr, _ptr_bound - _ptr, _object.Size); // NULL 포함 복사

					// 6) [버퍼_길이]를 더해준다. (NULL문자열의 길이까지 포함한다.)
					_ptr += _object.Size;
				}
			}
			public unsafe buffer ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// Attention) buffer의 size는 int64이다.

				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
				Debug.Assert(sizeof(Int64) <= _count);

			#if _USE_BOUND_CHECK
				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
				if(sizeof(int)>this.m_count) 
					throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
			#endif

				// 1) extract  string length
				var size_temp = Unsafe.AsRef<Int64>(_ptr);
				var buf_size = (int)size_temp;

				// 2) update ptr & count
				_ptr += sizeof(Int64);
				_count -= sizeof(Int64);

				// check) length가 -1이면 null을 리턴한다.
				if (buf_size <= 0)
					return new buffer();

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
				Debug.Assert(buf_size <= _count);

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
				if (buf_size > _count)
					throw new CGDK.Exception.Serialize(_count, "[CGDK.buffer] Not Supported TYPE.");

				// 3) alloc buffer
				var new_buf = new byte[buf_size];

				// 4) block copy
				fixed (byte* buf_dest = new_buf)
				{
					System.Buffer.MemoryCopy(_ptr, buf_dest, buf_size, buf_size);
				}

				// 5) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
				_ptr += buf_size;
				_count -= buf_size;

				// 6) [string]로 변환해 최종 리턴한다.
				return new buffer(new_buf, 0, buf_size);
			}
			public unsafe int ProcessGetSizeOf(buffer _object)
			{
				return sizeof(Int64) + _object.Size;
			}
		}
		public class SerializerBuffer_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// Attention) buffer의 size는 int64이다.

				// check)
				Debug.Assert(_object == null);

				// 1) casting to 
				var temp = (buffer?)_object;

				// check)
				Debug.Assert(temp != null);

				// 2) get buf
				var temp_buf = temp.Value;

				// check)
				Debug.Assert(temp_buf.Size >= 0);

				// 3) get buffer
				var buf = temp_buf.Array;

				// check)
				if (buf == null || temp_buf.Size <= 0)
				{
					// - 0을 쓰고 끝낸다.
					Unsafe.AsRef<Int64>(_ptr) = 0;
					_ptr += sizeof(Int64);
					return;
				}

				// 4) write to buffer
				fixed (byte* buf_source = buf)
				{
					// check)
					Debug.Assert(_ptr + sizeof(Int64) + temp_buf.Size <= _ptr_bound);

					// 3) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
					Unsafe.AsRef<Int64>(_ptr) = temp_buf.Size;
					_ptr += sizeof(Int64);

					// check)
					if (temp_buf.Size == 0)
						return;

					// 4) 복사해 붙인다.
					System.Buffer.MemoryCopy(buf_source, _ptr, _ptr_bound - _ptr, temp_buf.Size); // NULL 포함 복사

					// 5) [버퍼_길이]를 더해준다. (NULL문자열의 길이까지 포함한다.)
					_ptr += temp_buf.Size;
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// Attention) buffer의 size는 int64이다.

				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
				Debug.Assert(sizeof(Int64) <= _count);

			#if _USE_BOUND_CHECK
				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
				if(sizeof(int)>this.m_count) 
					throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
			#endif

				// 1) extract  string length
				var size_temp = Unsafe.AsRef<Int64>(_ptr);
				var buf_size = (int)size_temp;

				// 2) update ptr & count
				_ptr += sizeof(Int64);
				_count -= sizeof(Int64);

				// check) length가 -1이면 null을 리턴한다.
				if (buf_size <= 0)
					return new buffer();

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
				Debug.Assert(buf_size <= _count);

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
				if (buf_size > _count)
					throw new CGDK.Exception.Serialize(_count, "[CGDK.buffer] Not Supported TYPE.");

				// 3) alloc buffer
				var new_buf = new byte[buf_size];

				// 4) block copy
				fixed (byte* buf_dest = new_buf)
				{
					System.Buffer.MemoryCopy(_ptr, buf_dest, buf_size, buf_size);
				}

				// 5) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
				_ptr += buf_size;
				_count -= buf_size;

				// 6) [string]로 변환해 최종 리턴한다.
				return new buffer(new_buf, 0, buf_size);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// 1) casting to 
				var temp_buf = (buffer?)_object;

				// check)
				Debug.Assert(temp_buf != null);

				// return) 
				return sizeof(Int64) + temp_buf.Value.Size;
			}
		}

		public class SerializerString : IBase<string>
		{
			public static unsafe void XProcessAppend(ref byte* _ptr, byte* _ptr_bound, string? _object)
			{
				// check) 데이터가 null이면 -1만 쓰고 끝냄.
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 2) [문자열]을 [문자배열]로 변경하고 길이를 구한다.(NULL은 뺀 크기)
				var string_length = _object.Length * sizeof(char);

				// check)
				Debug.Assert(_ptr + sizeof(Int32) + string_length + sizeof(char) <= _ptr_bound);

				// 3) [문자열 길이]를 써넣는다. (NULL을 포함한 문자열의 길이)
				Unsafe.AsRef<Int32>(_ptr) = _object.Length + 1;

				// 4) add size
				_ptr += sizeof(Int32);

				// 5) [문자열]을 복사해 넣는다.
				fixed (char* str = (string?)_object)
				{

					System.Buffer.MemoryCopy(str, _ptr, _ptr_bound - _ptr, string_length + sizeof(char)); // NULL 포함 복사
				}

				// 6) 써넣은 bytes만큼 더해준다. (NULL문자열의 길이까지 포함)
				_ptr += string_length + sizeof(char);
			}
			public static unsafe string? XProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Assert!
				Debug.Assert(sizeof(Int32) <= _count);

			#if _USE_BOUND_CHECK
				// check) Buffer의 길이가 String 최소크기보다 작을 경우 Exception
				if(sizeof(int)>this.m_count) 
					throw new CGDK.Exception.Serialize(_offset, "[CGDK.buffer] buffer size is short");
			#endif
				// 1) extract  string length
				var length_string = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check) length가 -1이면 null을 리턴한다.
				if (length_string == -1)
					return null;

				// 3) 복사할 [문자열_길이]를 구한다. (NULL문자는 뺀다.)
				int size_copy = length_string * sizeof(char);

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Assert!
				Debug.Assert(size_copy <= _count);

				// check) String 길이에 비해 Buffer의 길이가 짧으면 Exception!
				if (size_copy > _count)
					throw new CGDK.Exception.Serialize(_count, "[CGDK.buffer] Not Supported TYPE.");

				// check) [문자열]의 제일 끝이 NULL인지 확인한다.
				if (*(char*)(_ptr + size_copy - sizeof(char)) != 0)
					throw new CGDK.Exception.Serialize(_count, "[CGDK.buffer] string terminate No-'NULL' value");

				// 4) get '_ptr' before update
				var p = _ptr;

				// 5) [버퍼_길이]와 [버퍼_어프셋]을 갱신한다.
				_ptr += size_copy;
				_count -= size_copy;

				// 6) [string]로 변환해 최종 리턴한다.
				return new string((char*)p, 0, length_string - 1);
			}
			public static unsafe int XProcessGetSizeOf(string? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) process get size of
				return sizeof(Int32) + (_object.Length + 1) * sizeof(char);
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, string? _object)
			{
				XProcessAppend(ref _ptr, _ptr_bound, _object);
			}
			public unsafe string? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				return XProcessExtract(ref _ptr, ref _count);
			}
			public unsafe int ProcessGetSizeOf(string? _object)
			{
				return XProcessGetSizeOf(_object);
			}
		}
		public class SerializerString_object : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				SerializerString.XProcessAppend(ref _ptr, _ptr_bound, (string?)_object);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				return SerializerString.XProcessExtract(ref _ptr, ref _count);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return SerializerString.XProcessGetSizeOf((string?)_object);
			}
		}

		public class SerializerArray_typed<V> : IBase<V[]>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, V[]? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = _object.Length;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, (V?)iter_item.Current);
				}
			}
			public unsafe V[]? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj_array = (V[]?)Activator.CreateInstance(typeof(V[]), item_count);

				// check)
				Debug.Assert(obj_array != null);

				// 4) write items
				for (int i = 0; i < item_count; ++i)
				{
					// - get item
					var item = (V?)serializer_value.ProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_array.SetValue(item, i);
				}

				// check)
				Debug.Assert(obj_array != null);

				// return) 
				return obj_array;
			}
			public unsafe int ProcessGetSizeOf(V[]? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) 'items'
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf((V?)iter_item.Current);
				}

				// return) 
				return size;
			}

			private static readonly IBase<V>? serializer_value = Builder.ProcessGetSerializer<V>();
		}
		public class SerializerArray_typed_primitive<V> : IBase<V[]> where V:unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, V[]? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = _object.Length;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write
				fixed(void* ptr_src = _object)
				{
					System.Buffer.MemoryCopy(ptr_src, _ptr, _ptr_bound - _ptr,  sizeof(V) * _object.Length); // NULL 포함 복사
				}
			}
			public unsafe V[]? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj_array = (V[]?)Activator.CreateInstance(typeof(V[]), item_count);

				// check)
				Debug.Assert(obj_array != null);

				// 4) write items
				fixed (void* ptr_dest = obj_array)
				{
					System.Buffer.MemoryCopy(_ptr, ptr_dest, _count, sizeof(V) * item_count); // NULL 포함 복사
				}

				// 5) update count
				_count -= sizeof(Int32) * item_count;

				// check)
				Debug.Assert(obj_array != null);

				// return) 
				return obj_array;
			}
			public unsafe int ProcessGetSizeOf(V[]? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// return 
				return sizeof(Int32) + _object.Length * sizeof(V);
			}
		}
		public class SerializerArray_no_typed<T> : IBase<T>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<IList>(_object);

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = (T?)Activator.CreateInstance(typeof(T), item_count);

				// check)
				Debug.Assert(obj != null);

				// 4) casting to IList
				var obj_list = Unsafe.As<IList>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_list.Add(item);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj != null);

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) casting to IList
				var obj_list = Unsafe.As<IList>(_object);

				// check)
				Debug.Assert(obj_list != null);

				// 2) 'items'
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf(iter_item.Current);
				}

				// return) 
				return size;
			}

			private static readonly IBase<object>? serializer_value = (IBase<object>?)Builder.ProcessGetSerializer_object(typeof(T).GetGenericArguments()[0]);
		}
		public class SerializerArray_object_typed<V> : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<V[]>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Length;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write all items
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, (V?)iter_item.Current);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj_array = (V[]?)Activator.CreateInstance(typeof(V[]), item_count);

				// check)
				Debug.Assert(obj_array != null);

				// 5) read all items
				for (int i = 0; i < item_count; ++i)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// -set value
					obj_array.SetValue(item, i);
				}

				// check)
				Debug.Assert(obj_array != null);

				// return) 
				return obj_array;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'item count'
				int size = sizeof(Int32);

				// 2) cast to 'List<V>;
				var obj_array = Unsafe.As<V[]>(_object);

				// check)
				Debug.Assert(obj_array != null);

				// 2) add size of 'items'
				var iter_item = obj_array.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf((V?)iter_item.Current);
				}

				// return) 
				return size;
			}

			private readonly IBase<V>? serializer_value = Builder.ProcessGetSerializer<V>();
		}
		public class SerializerArray_object_typed_primitive<V> : IBase<object> where V : unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_array= Unsafe.As<V[]>(_object);

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = obj_array.Length;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write
				fixed (void* ptr_src = obj_array)
				{
					System.Buffer.MemoryCopy(ptr_src, _ptr, _ptr_bound - _ptr, sizeof(V) * obj_array.Length); // NULL 포함 복사
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj_array = (V[]?)Activator.CreateInstance(typeof(V[]), item_count);

				// check)
				Debug.Assert(obj_array != null);

				// 4) write items
				fixed (void* ptr_dest = obj_array)
				{
					System.Buffer.MemoryCopy(_ptr, ptr_dest, _count, sizeof(V) * item_count); // NULL 포함 복사
				}

				// 5) update count
				_count -= sizeof(Int32) * item_count;

				// check)
				Debug.Assert(obj_array != null);

				// return) 
				return obj_array;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) casting to list
				var obj_array = Unsafe.As<V[]>(_object);

				// return 
				return sizeof(Int32) + obj_array.Length * sizeof(V);
			}
		}
		public class SerializerArray_object_no_typed : IBase<object>
		{
			public SerializerArray_object_no_typed(Type? _type_create, IBase<object>? _serializer_value)
			{
				this.type_create = _type_create;
				this.serializer_value = _serializer_value;

				// check)
				Debug.Assert(this.serializer_value != null);
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<IList>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(type_create != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = Activator.CreateInstance(type_create, item_count);

				// 4) casting to IList
				var obj_list = Unsafe.As<IList>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_list.Add(item);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj != null);

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) 'items'
				var iter_item = Unsafe.As<IList>(_object).GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf(iter_item.Current);
				}

				// return) 
				return size;
			}

			private readonly Type? type_create;
			private readonly IBase<object>? serializer_value;
		}

		public class SerializerDictionary<K, V> : IBase<Dictionary<K, V>> where K : notnull
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Dictionary<K, V>? _object)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = _object.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(_object != null);

				// 4) write items
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					// - write key & value
					serializer_key.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current.Key);
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current.Value);
				}
			}
			public unsafe Dictionary<K, V>? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj_create = (Dictionary<K, V>?)Activator.CreateInstance(typeof(Dictionary<K, V>));

				// check)
				Debug.Assert(obj_create != null);

				// 4) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = serializer_key.ProcessExtract(ref _ptr, ref _count);
					var item_value = serializer_value.ProcessExtract(ref _ptr, ref _count)!;

					// check) 
					Debug.Assert(item_key != null);

					// - add item(key & value)
					obj_create.Add((K)item_key, item_value);

					// - count down!
					--item_count;
				}

				// return) 
				return obj_create;
			}
			public unsafe int ProcessGetSizeOf(Dictionary<K, V>? _object)
			{
				// chaeck)
				Debug.Assert(serializer_key != null);

				// chaeck)
				Debug.Assert(serializer_value != null);

				// 1) get header size
				int size = sizeof(Int32);

				// check)
				if (_object == null)
					return size;

				// 3) get Dictionary
				var iter_item = _object.GetEnumerator();

				// 4) add size of items
				while (iter_item.MoveNext())
				{
					// - add size of 'key' & 'value'
					size += serializer_key.ProcessGetSizeOf(iter_item.Current.Key);
					size += serializer_value.ProcessGetSizeOf(iter_item.Current.Value);
				}

				// return) 
				return size;

			}

			private static readonly IBase<K>? serializer_key = Builder.ProcessGetSerializer<K>();
			private static readonly IBase<V>? serializer_value = Builder.ProcessGetSerializer<V>();
		}
		public class SerializerDictionary_primitive_primitive<K,V> : IBase<Dictionary<K, V>> where K : unmanaged where V : unmanaged
		{
			public static unsafe void Xprocess_append(ref byte* _ptr, byte* _ptr_bound, Dictionary<K,V>? _object)
			{
				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = _object.Count;

				// check)
				Debug.Assert((_ptr + sizeof(Int32) + (sizeof(K) + sizeof(V)) * _object.Count) <= _ptr_bound);

			#if _USE_BOUND_CHECK
				// check)
				if((_ptr + sizeof(Int32) + (sizeof(K) + sizeof(V)) * _object.Count) > _ptr_bound)
					throw new System.OverflowException("buffer overflow");
			#endif

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write items
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					// - write key & value
					*(K*)_ptr = iter_item.Current.Key;
					_ptr += sizeof(K);

					*(V*)_ptr = iter_item.Current.Value;
					_ptr += sizeof(V);
				}
			}

			public static unsafe Dictionary<K,V>? Xprocess_extract(ref byte* _ptr, ref int _count)
			{
				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj_create = (Dictionary<K, V>?)Activator.CreateInstance(typeof(Dictionary<K, V>));

				// check)
				Debug.Assert(obj_create != null);

				// check)
				Debug.Assert((sizeof(K) + sizeof(V)) * item_count <= _count);

			#if _USE_BOUND_CHECK
				// check)
				if(((sizeof(K) + sizeof(V)) * item_count > _count)
					throw new System.OverflowException("buffer overflow");
			#endif
				// 4) count
				_count -= (sizeof(K) + sizeof(V)) * item_count;

				// 5) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = *(K*)_ptr; 
					_ptr += sizeof(K);

					var item_value = *(V*)_ptr;
					_ptr += sizeof(V);

					// - add item(key & value)
					obj_create.Add((K)item_key, item_value);

					// - count down!
					--item_count;
				}

				// return) 
				return obj_create;
			}
			public static unsafe int Xprocess_get_size_of(Dictionary<K, V>? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) get Dictionary
				return sizeof(UInt32) + (sizeof(K) + sizeof(V)) * _object.Count;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, Dictionary<K, V>? _object)
			{
				Xprocess_append(ref _ptr, _ptr_bound, _object);
			}
			public unsafe Dictionary<K,V>? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				return Xprocess_extract(ref _ptr, ref _count);
			}
			public unsafe int ProcessGetSizeOf(Dictionary<K,V>? _object)
			{
				return Xprocess_get_size_of(_object);
			}
		}
		public class SerializerDictionary<T, K, V> : IBase<T> where K : notnull
		{
			public SerializerDictionary(IBase<K>? _serializer_key, IBase<V> _serializer_value) 
			{
				this.serializer_key = _serializer_key;
				this.serializer_value = _serializer_value;

				// check)
				Debug.Assert(this.serializer_key != null);
				Debug.Assert(this.serializer_value != null);
			}
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting
				var dictionary_object = (IDictionary)_object;

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = dictionary_object.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(dictionary_object != null);

				// 4) write items
				var iter_item = dictionary_object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					// - write key & value
					serializer_key.ProcessAppend(ref _ptr, _ptr_bound, (K)iter_item.Key);
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, (V?)iter_item.Value);
				}
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj_create = (T?)Activator.CreateInstance(typeof(T));

				// check)
				Debug.Assert(obj_create != null);

				// 4) casting
				var dictionary_object = (IDictionary)obj_create;

				// 5) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = serializer_key.ProcessExtract(ref _ptr, ref _count);
					var item_value = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// check) 
					Debug.Assert(item_key != null);

					// - add item(key & value)
					dictionary_object.Add(item_key, item_value);

					// - count down!
					--item_count;
				}

				// return) 
				return obj_create;
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				// chaeck)
				Debug.Assert(serializer_key != null);

				// chaeck)
				Debug.Assert(serializer_value != null);

				// 1) get header size
				int size = sizeof(Int32);

				// check)
				if (_object == null)
					return size;

				// 2) casting
				var dictionary_object = (IDictionary)_object;

				// 3) get Dictionary
				var iter_item = dictionary_object.GetEnumerator();

				// 4) add size of items
				while (iter_item.MoveNext())
				{
					// - add size of 'key' & 'value'
					size += serializer_key.ProcessGetSizeOf((K)iter_item.Key);
					size += serializer_value.ProcessGetSizeOf((V?)iter_item.Value);
				}

				// return) 
				return size;
			}

			private readonly IBase<K>? serializer_key;
			private readonly IBase<V>? serializer_value;
		}
		public class SerializerDictionary_object_typed<K, V> : IBase<object> where K : notnull
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_dictionary = Unsafe.As<Dictionary<K, V>>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_dictionary.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 4) write
				var iter_item = obj_dictionary.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_key.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current.Key);
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current.Value);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = (Dictionary<K, V>?)Activator.CreateInstance(typeof(Dictionary<K, V>));

				// check)
				Debug.Assert(obj != null);

				// 4) get Dictionary
				var obj_dictionary = Unsafe.As<Dictionary<K, V>>(obj);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = serializer_key.ProcessExtract(ref _ptr, ref _count);
					var item_value = serializer_value.ProcessExtract(ref _ptr, ref _count)!;

					// check)
					Debug.Assert(item_key != null);

					// - add item
					obj_dictionary.Add(item_key, item_value);

					// - count down
					--item_count;
				}

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get header size
				int size = sizeof(Int32);

				// check)
				if (_object == null)
					return size;

				// 3) get Dictionary
				var iter_item = Unsafe.As<Dictionary<K, V>>(_object).GetEnumerator();

				// 4) add size of items
				while (iter_item.MoveNext())
				{
					size += serializer_key.ProcessGetSizeOf(iter_item.Current.Key);
					size += serializer_value.ProcessGetSizeOf(iter_item.Current.Value);
				}

				// return) 
				return size;
			}

			private readonly IBase<K>? serializer_key = Builder.ProcessGetSerializer<K>();
			private readonly IBase<V>? serializer_value = Builder.ProcessGetSerializer<V>();
		}
		public class SerializerDictionary_object_primitive_primitive<K, V> : IBase<object> where K : unmanaged where V : unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				SerializerDictionary_primitive_primitive<K, V>.Xprocess_append(ref _ptr, _ptr_bound, (Dictionary<K, V>?)_object);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				return SerializerDictionary_primitive_primitive<K, V>.Xprocess_extract(ref _ptr, ref _count);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				return SerializerDictionary_primitive_primitive<K, V>.Xprocess_get_size_of((Dictionary<K, V>?)_object);
			}
		}
		public class SerializerDictionary_object_no_typed<K, V> : IBase<object>
		{
			public SerializerDictionary_object_no_typed(Type? _type_create, IBase<K>? _serializer_key, IBase<V>? _serializer_value)
			{
				this.type_create = _type_create;
				this.serializer_key = _serializer_key;
				this.serializer_value = _serializer_value;

				// check)
				Debug.Assert(this.serializer_key != null);
				Debug.Assert(this.serializer_value != null);
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_dictionary = Unsafe.As<IDictionary>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_dictionary.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 4) write
				var iter_item = obj_dictionary.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_key.ProcessAppend(ref _ptr, _ptr_bound, (K)iter_item.Key);
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, (V?)iter_item.Value);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check)
				Debug.Assert(type_create != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = Activator.CreateInstance(type_create);

				// check)
				Debug.Assert(obj != null);

				// 4) get Dictionary
				var obj_dictionary = Unsafe.As<IDictionary>(obj);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = serializer_key.ProcessExtract(ref _ptr, ref _count);
					var item_value = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// check)
					Debug.Assert(item_key != null);

					// - add item
					obj_dictionary.Add(item_key, item_value);

					// - count down
					--item_count;
				}

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get header size
				int size = sizeof(Int32);

				// check)
				if (_object == null)
					return size;

				// 3) get Dictionary
				var iter_item = Unsafe.As<IDictionary>(_object).GetEnumerator();

				// 4) add size of items
				while (iter_item.MoveNext())
				{
					size += serializer_key.ProcessGetSizeOf((K)iter_item.Key);
					size += serializer_value.ProcessGetSizeOf((V?)iter_item.Value);
				}

				// return) 
				return size;
			}

			private readonly Type? type_create;
			private readonly IBase<K>? serializer_key;
			private readonly IBase<V>? serializer_value;
		}
		public class SerializerDictionary_object : IBase<object>
		{
			public SerializerDictionary_object(Type? _type_create, IBase<object>? _serializer_key, IBase<object>? _serializer_value)
			{
				this.type_create = _type_create;
				this.serializer_key = _serializer_key;
				this.serializer_value = _serializer_value;

				// check)
				Debug.Assert(this.serializer_key != null);
				Debug.Assert(this.serializer_value != null);
			}
			public static unsafe void XProcessAppend<X, Y>(ref byte* _ptr, byte* _ptr_bound, object? _object, IBase<X> _serializer_key, IBase<Y> _serializer_value)
			{
				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_dictionary = Unsafe.As<IDictionary>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_dictionary.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 4) write
				var iter_item = obj_dictionary.GetEnumerator();
				while (iter_item.MoveNext())
				{
					_serializer_key.ProcessAppend(ref _ptr, _ptr_bound, (X)iter_item.Key);
					_serializer_value.ProcessAppend(ref _ptr, _ptr_bound, (Y?)iter_item.Value);
				}
			}
			public static unsafe object? XProcessExtract<X, Y>(ref byte* _ptr, ref int _count, Type _Type_create, IBase<X> _serializer_key, IBase<Y> _serializer_value)
			{
				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = Activator.CreateInstance(_Type_create);

				// check)
				Debug.Assert(obj != null);

				// 4) casting to IList
				var obj_dictionary = Unsafe.As<IDictionary>(obj);

				// check)
				Debug.Assert(obj_dictionary != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get key & value
					var item_key = _serializer_key.ProcessExtract(ref _ptr, ref _count);
					var item_value = _serializer_value.ProcessExtract(ref _ptr, ref _count);

					// check)
					Debug.Assert(item_key != null);

					// - add item
					obj_dictionary.Add(item_key, item_value);

					// - count down
					--item_count;
				}

				// return) 
				return obj;
			}
			public static unsafe int XProcessGetSizeOf<X, Y>(object? _object, IBase<X> _serializer_key, IBase<Y> _serializer_value)
			{
				// 1) get header size
				int size = sizeof(Int32);

				// check)
				if (_object == null)
					return size;

				// 3) get Dictionary
				var iter_item = Unsafe.As<IDictionary>(_object).GetEnumerator();

				// 4) add size of items
				while (iter_item.MoveNext())
				{
					size += _serializer_key.ProcessGetSizeOf((X)iter_item.Key);
					size += _serializer_value.ProcessGetSizeOf((Y?)iter_item.Value);
				}

				// return) 
				return size;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) press append
				XProcessAppend(ref _ptr, _ptr_bound, _object, serializer_key, serializer_value);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(type_create != null);

				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) process extract
				return XProcessExtract(ref _ptr, ref _count, type_create, serializer_key, serializer_value);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_key != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) process get size of
				return XProcessGetSizeOf(_object, serializer_key, serializer_value);
			}

			private readonly Type? type_create;
			private readonly IBase<object>? serializer_key;
			private readonly IBase<object>? serializer_value;
		}

		public class SerializerList_typed<V> : IBase<List<V>>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, List<V>? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<List<V>>(_object);

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe List<V>? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = Activator.CreateInstance(typeof(List<V>));

				// 4) casting to IList
				var obj_list = Unsafe.As<List<V>>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count)!;

					// - add item
					obj_list.Add(item);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj_list != null);

				// return) 
				return obj_list;
			}
			public unsafe int ProcessGetSizeOf(List<V>? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) 'items'
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf(iter_item.Current);
				}

				// return) 
				return size;
			}

			private static readonly IBase<V>? serializer_value = Builder.ProcessGetSerializer<V>();
		}
		public class SerializerList_typed_primitive<V> : IBase<List<V>> where V: unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, List<V>? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = _object.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					// - copy
					*(V*)_ptr = iter_item.Current;

					// - add ptr
					_ptr += sizeof(V);
				}
			}
			public unsafe List<V>? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = Activator.CreateInstance(typeof(List<V>));

				// 4) casting to IList
				var obj_list = Unsafe.As<List<V>>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) sub count
				_count -= sizeof(V) * item_count;

				// 6) write items
				while (item_count > 0)
				{
					// - add item
					obj_list.Add(*(V*)_ptr);

					// - update ptr
					_ptr += sizeof(V);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj_list != null);

				// return) 
				return obj_list;
			}
			public unsafe int ProcessGetSizeOf(List<V>? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// return) 
				return sizeof(Int32) + _object.Count * sizeof(V);
			}
		}
		public class SerializerList_string : IBase<List<string>>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, List<string>? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) write -1 
				Unsafe.AsRef<Int32>(_ptr) = _object.Count;

				// 2) update ptr
				_ptr += sizeof(Int32);

				// 3) write
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					SerializerString.XProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe List<string>? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = Activator.CreateInstance(typeof(List<string>));

				// 4) casting to IList
				var obj_list = Unsafe.As<List<string>>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get 
					var item_string = SerializerString.XProcessExtract(ref _ptr, ref _count)!;

					// - add item
					obj_list.Add(item_string);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj_list != null);

				// return) 
				return obj_list;
			}
			public unsafe int ProcessGetSizeOf(List<string>? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'item count'
				int size = sizeof(Int32);

				// 2) add size of 'items'
				var iter_item = _object.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += SerializerString.XProcessGetSizeOf(iter_item.Current);
				}

				return size;
			}
		}
		public class SerializerList_no_typed<T> : IBase<T>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<IList>(_object);

				// 2) write count 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = (T?)Activator.CreateInstance(typeof(T));

				// check)
				Debug.Assert(obj != null);

				// 4) casting to IList
				var obj_list = Unsafe.As<IList>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_list.Add(item);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj != null);

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) casting to IList
				var obj_list = Unsafe.As<IList>(_object);

				// check)
				Debug.Assert(obj_list != null);

				// 2) 'items'
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf(iter_item.Current);
				}

				// return) 
				return size;
			}

			private static readonly IBase<object>? serializer_value = (IBase<object>?)Builder.ProcessGetSerializer_object(typeof(T).GetGenericArguments()[0]);
		}
		public class SerializerList_object_typed_primitive<V> : IBase<object> where V : unmanaged
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<List<V>>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write all items
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					// - copy
					*(V*)_ptr = iter_item.Current;

					// - add ptr
					_ptr += sizeof(V);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = Activator.CreateInstance(typeof(List<V>));

				// 4) casting to IList
				var obj_list = Unsafe.As<List<V>>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) sub count
				_count -= sizeof(V) * item_count;

				// 6) read all items
				while (item_count > 0)
				{
					// - add item
					obj_list.Add(*(V*)_ptr);

					// - update ptr
					_ptr += sizeof(V);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj != null);

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 4) casting to IList
				var obj_list = Unsafe.As<List<V>>(_object);

				// return) 
				return sizeof(Int32) + obj_list.Count * sizeof(V);
			}
		}
		public class SerializerList_obejct_string : IBase<object>
		{
			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<List<string>>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					SerializerString.XProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return default;

				// 3) create list
				var obj = Activator.CreateInstance(typeof(List<string>));

				// 4) casting to IList
				var obj_list = Unsafe.As<List<string?>>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get 
					var item_string = SerializerString.XProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_list.Add(item_string);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj_list != null);

				// return) 
				return obj_list;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'item count'
				int size = sizeof(Int32);

				// 4) casting to IList
				var obj_list = Unsafe.As<List<string>>(_object);

				// 2) add size of 'items'
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += SerializerString.XProcessGetSizeOf(iter_item.Current);
				}

				return size;
			}
		}

		public class SerializerList_object_no_typed : IBase<object>
		{
			public SerializerList_object_no_typed(Type? _type_create, IBase<object>? _serializer_value)
			{
				this.type_create = _type_create;
				this.serializer_value = _serializer_value;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(serializer_value != null);

				// check) is null?
				if (_object == null)
				{
					// - write -1
					Builder.ProcessAppend_Empty(ref _ptr);

					// return) 
					return;
				}

				// 1) casting to list
				var obj_list = Unsafe.As<IList>(_object);

				// 2) write -1 
				Unsafe.AsRef<Int32>(_ptr) = obj_list.Count;

				// 3) update ptr
				_ptr += sizeof(Int32);

				// check)
				Debug.Assert(obj_list != null);

				// 4) write
				var iter_item = obj_list.GetEnumerator();
				while (iter_item.MoveNext())
				{
					serializer_value.ProcessAppend(ref _ptr, _ptr_bound, iter_item.Current);
				}
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(type_create != null);

				// check)
				Debug.Assert(serializer_value != null);

				// 1) get count of list
				Int32 item_count = Unsafe.AsRef<Int32>(_ptr);

				// 2) update ptr & count
				_ptr += sizeof(Int32);
				_count -= sizeof(Int32);

				// check)
				if (item_count == -1)
					return null;

				// 3) create list
				var obj = Activator.CreateInstance(type_create);

				// 4) casting to IList
				var obj_list = Unsafe.As<IList>(obj);

				// check)
				Debug.Assert(obj_list != null);

				// 5) write items
				while (item_count > 0)
				{
					// - get item
					var item = serializer_value.ProcessExtract(ref _ptr, ref _count);

					// - add item
					obj_list.Add(item);

					// - count down
					--item_count;
				}

				// check)
				Debug.Assert(obj != null);

				// return) 
				return obj;
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(serializer_value != null);

				// check)
				if (_object == null)
					return sizeof(Int32);

				// 1) 'count'
				int size = sizeof(Int32);

				// 2) 'items'
				var iter_item = Unsafe.As<IList>(_object).GetEnumerator();
				while (iter_item.MoveNext())
				{
					size += serializer_value.ProcessGetSizeOf(iter_item.Current);
				}

				// return) 
				return size;
			}

			private readonly Type? type_create;
			private readonly IBase<object>? serializer_value;
		}

		public readonly struct MemberSerializationInfo
		{
			public readonly FieldInfo field_info;
			public readonly IBase<object> serializer;
			public readonly int offset;

			public MemberSerializationInfo(FieldInfo _field_info, IBase<object> _serializer, int _offset)
			{
				this.field_info = _field_info;
				this.serializer = _serializer;
				this.offset = _offset;
			}
		}
		public class SerializerClass<T> : IBase<T>
		{
			public SerializerClass(List<MemberSerializationInfo> _list_member_serialization_info)
			{
				this.list_member_serialization_info = _list_member_serialization_info;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) append - members
				SerializerClass_object.Xprocess_append(ref _ptr, _ptr_bound, _object, list_member_serialization_info);
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) extract - members
				return (T?)SerializerClass_object.XProcessExtract(ref _ptr, ref _count, typeof(T), list_member_serialization_info);
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process get_size_of - memeber
				return SerializerClass_object.XProcessGetSizeOf(_object, list_member_serialization_info);
			}

			public readonly List<MemberSerializationInfo> list_member_serialization_info;
		}
		public class SerializerClass_object : IBase<object>
		{
			public SerializerClass_object(Type? _type_create, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				this.type_create = _type_create;
				this.list_member_serialization_info = _list_member_serialization_info;
			}

			public static unsafe void Xprocess_append(ref byte* _ptr, byte* _ptr_bound, object? _object, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 1) append all members
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
					iter_member.Current.serializer.ProcessAppend(ref _ptr, _ptr_bound, iter_member.Current.field_info.GetValue(_object));
			}
			public static unsafe object? XProcessExtract(ref byte* _ptr, ref int _count, Type _type_create, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// 1) 객체를 생성한다.
				var temp_object = Activator.CreateInstance(_type_create);

				// check) 
				Debug.Assert(temp_object != null);

				// 2) 각 Field값을 읽어 써넣는다.
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
					iter_member.Current.field_info.SetValue(temp_object, iter_member.Current.serializer.ProcessExtract(ref _ptr, ref _count));

				// return) 
				return temp_object;
			}
			public static unsafe int XProcessGetSizeOf(object? _object, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// check)
				if (_object == null)
					return sizeof(Int32);

				// declare)
				int size = 0;

				// 1) add all member size
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
					size += iter_member.Current.serializer.ProcessGetSizeOf(iter_member.Current.field_info.GetValue(_object));

				// return) 
				return size;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// 1) process append
				Xprocess_append(ref _ptr, _ptr_bound, _object, list_member_serialization_info);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(type_create != null);

				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process extract
				return XProcessExtract(ref _ptr, ref _count, type_create, list_member_serialization_info);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// 1) process get size of
				return XProcessGetSizeOf(_object, list_member_serialization_info);
			}

			private readonly Type? type_create;
			private readonly List<MemberSerializationInfo> list_member_serialization_info;
		}

		public class SerializerStruct<T> : IBase<T>
		{
			public SerializerStruct(List<MemberSerializationInfo> _list_member_serialization_info)
			{
				this.list_member_serialization_info = _list_member_serialization_info;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, T? _object)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process append
				SerializerStruct_object.Xprocess_append(ref _ptr, _ptr_bound, _object, list_member_serialization_info);
			}
			public unsafe T? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process extract
				return (T?)SerializerStruct_object.XProcessExtract(ref _ptr, ref _count, typeof(T), list_member_serialization_info);
			}
			public unsafe int ProcessGetSizeOf(T? _object)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process get size of
				return SerializerStruct_object.XProcessGetSizeOf(_object, list_member_serialization_info);
			}

			private readonly List<MemberSerializationInfo> list_member_serialization_info;
		}
		public class SerializerStruct_object : IBase<object>
		{
			public SerializerStruct_object(Type? _type_create, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				this.type_create = _type_create;
				this.list_member_serialization_info = _list_member_serialization_info ;
			}

			public static unsafe void Xprocess_append(ref byte* _ptr, byte* _ptr_bound, object? _object, List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// check) is null?
				if (_object == null)
				{
					Builder.ProcessAppend_Empty(ref _ptr);
					return;
				}

				// 1) append all members
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
				{
					iter_member.Current.serializer.ProcessAppend(ref _ptr, _ptr_bound, iter_member.Current.field_info.GetValue(_object));
				}
			}
			public static unsafe object XProcessExtract(ref byte* _ptr, ref int _count, Type _Type_create, List<MemberSerializationInfo>? _list_member_serialization_info)
			{
				// 1) 객체를 생성한다.
				var temp_object = Activator.CreateInstance(_Type_create);

				// check) 
				Debug.Assert(temp_object != null);

				// check) 
				Debug.Assert(_list_member_serialization_info != null);

				// 2) 각 Field값을 읽어 써넣는다.
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
				{
					iter_member.Current.field_info.SetValue(temp_object, iter_member.Current.serializer.ProcessExtract(ref _ptr, ref _count));
				}

				// return) 
				return temp_object;
			}
			public static unsafe int XProcessGetSizeOf(object? _object, List<MemberSerializationInfo>? _list_member_serialization_info)
			{
				if (_object == null)
					return sizeof(Int32);

				// check) 
				Debug.Assert(_list_member_serialization_info != null);

				// declare) 
				int size = 0;

				// 1) add all member size
				var iter_member = _list_member_serialization_info.GetEnumerator();
				while (iter_member.MoveNext())
				{
					size += iter_member.Current.serializer.ProcessGetSizeOf(iter_member.Current.field_info.GetValue(_object));
				}

				// return) 
				return size;
			}

			public unsafe void ProcessAppend(ref byte* _ptr, byte* _ptr_bound, object? _object)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(_ptr_bound != null);

				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process append
				Xprocess_append(ref _ptr, _ptr_bound, _object, list_member_serialization_info);
			}
			public unsafe object? ProcessExtract(ref byte* _ptr, ref int _count)
			{
				// check)
				Debug.Assert(_ptr != null);

				// check)
				Debug.Assert(type_create != null);

				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process extract
				return XProcessExtract(ref _ptr, ref _count, type_create, list_member_serialization_info);
			}
			public unsafe int ProcessGetSizeOf(object? _object)
			{
				// check)
				Debug.Assert(list_member_serialization_info != null);

				// 1) process get size of
				return XProcessGetSizeOf(_object, list_member_serialization_info);
			}

			private readonly Type? type_create;
			private readonly List<MemberSerializationInfo> list_member_serialization_info = new();
		}

		public class Builder
		{
			public static unsafe void ProcessAppend_Empty(ref byte* ptr)
			{
				Unsafe.AsRef<int>(ptr) = -1;
				ptr += sizeof(int);
			}

			private static bool IsSerializableType(Type _type)
			{
				// check) 
			#if NET5_0_OR_GREATER
				object obj = System.Runtime.CompilerServices.RuntimeHelpers.GetUninitializedObject(_type);
			#else
				object obj = System.Runtime.Serialization.FormatterServices.GetUninitializedObject(_type);
			#endif
				// check) 
				if (obj == null)
					return false;

				// 1) get attribute list
				var list_att = _type.GetCustomAttributes(typeof(CGDK.Attribute.Serializable), true);

				// return) get Attribute
				return list_att.Length != 0;
			}

			private static readonly Dictionary<Type, object> dictionary_serializer = new();
			private static readonly Dictionary<Type, object> dictionary_serializer_object = new();

			private static object BuildSerialize<T>()
			{
				// 1) get type
				Type type = typeof(T);

				// declare) 
				object? result = null;

				// 1) build by type
				if (type.IsPrimitive)
					result = BuildSerailizer_Primitive(type);
				else if (type.IsEnum)
					result = new SerializerEnum<T>();
				else if (type.IsValueType)
					result = BuildSerailizer_ValueType<T>(type);
				else if (typeof(string).Equals(type))
					result = new SerializerString();
				else if (type.IsArray)
					result = BuildSerializer_Array<T>();
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(type))
					result = BuildSerailizer_Dictionary<T>();
				else if (typeof(System.Collections.IList).IsAssignableFrom(type))
					result = BuildSerailizer_List<T>();
				else if (typeof(System.Collections.ICollection).IsAssignableFrom(type))
					result = BuildSerailizer_Collection<T>();
				else if (type.IsClass && IsSerializableType(type))
					result = BuildSerializer_Class<T>();
				else
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// check)
				Debug.Assert(result != null);

				// check) 
				if (result == null)
					throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Not Supported TYPE.");

				// return) 
				return result;
			}
			private static object BuildSerialize_object(Type _type)
			{
				// declare) 
				object? result = null;

				// 1) build by type
				if (_type.IsPrimitive)
					result = BuildSerailizer_Primitive_object(_type);
				else if (_type.IsEnum)
					result = new SerializerEnum_object();
				else if (_type.IsValueType)
					result = BuildSerailizer_ValueType_object(_type);
				else if (typeof(string).Equals(_type))
					result = new SerializerString_object();
				else if (_type.IsArray)
					result = BuildSerializer_Array_object(_type);
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type))
					result = BuildSerializer_Dictionary_object(_type);
				else if (typeof(System.Collections.IList).IsAssignableFrom(_type))
					result = BuildSerailizer_List_object(_type);
				else if (typeof(System.Collections.ICollection).IsAssignableFrom(_type))
					result = BuildSerailizer_Collection_object();
				else if (_type.IsClass && IsSerializableType(_type))
					result = BuildSerializer_Class_object(_type);
				else
					Debug.Assert(false, "[CGDK.buffer] Not Supported TYPE.");

				// check)
				Debug.Assert(result != null);

				// check) 
				if (result == null)
					throw new CGDK.Exception.Serialize(0, "[CGDK.buffer] Not Supported TYPE.");

				// return) 
				return result;
			}

			private static object? BuildSerailizer_Primitive(Type _type)
			{
				if (_type == typeof(long))
					return new SerializerPrimitive<long>();
				else if (_type == typeof(ulong))
					return new SerializerPrimitive<ulong>();
				else if (_type == typeof(double))
					return new SerializerPrimitive<double>();
				else if (_type == typeof(int))
					return new SerializerPrimitive<int>();
				else if (_type == typeof(uint))
					return new SerializerPrimitive<uint>();
				else if (_type == typeof(float))
					return new SerializerPrimitive<float>();
				else if (_type == typeof(short))
					return new SerializerPrimitive<short>();
				else if (_type == typeof(ushort))
					return new SerializerPrimitive<ushort>();
				else if (_type == typeof(sbyte))
					return new SerializerPrimitive<sbyte>();
				else if (_type == typeof(byte))
					return new SerializerPrimitive<byte>();
				else if (_type == typeof(char))
					return new SerializerPrimitive<char>();
				else
					return null;
			}
			private static object? BuildSerailizer_Primitive_object(Type _type)
			{
				if (_type == typeof(long))
					return new SerializerPrimitive_object<long>();
				else if (_type == typeof(ulong))
					return new SerializerPrimitive_object<ulong>();
				else if (_type == typeof(double))
					return new SerializerPrimitive_object<double>();
				else if (_type == typeof(int))
					return new SerializerPrimitive_object<int>();
				else if (_type == typeof(uint))
					return new SerializerPrimitive_object<uint>();
				else if (_type == typeof(float))
					return new SerializerPrimitive_object<float>();
				else if (_type == typeof(short))
					return new SerializerPrimitive_object<short>();
				else if (_type == typeof(ushort))
					return new SerializerPrimitive_object<ushort>();
				else if (_type == typeof(sbyte))
					return new SerializerPrimitive_object<sbyte>();
				else if (_type == typeof(byte))
					return new SerializerPrimitive_object<byte>();
				else if (_type == typeof(char))
					return new SerializerPrimitive_object<char>();
				else
					return null;
			}

			private static object? BuildSerailizer_ValueType<T>(Type _type)
			{
				if (typeof(DateTime).Equals(_type))
					return new SerializerDateTime();
				else if (typeof(CGDK.buffer).Equals(_type))
					return new SerializerBuffer();
				else if (typeof(Vector2).Equals(_type))
					return new SerializerVector2();
				else if (typeof(Vector3).Equals(_type))
					return new SerializerVector3();
				else if (typeof(Vector4).Equals(_type))
					return new SerializerVector4();
				else if (typeof(Plane).Equals(_type))
					return new SerializerPlane();
				else if (typeof(Quaternion).Equals(_type))
					return new SerializerQuaternion();
				else if (typeof(Matrix3x2).Equals(_type))
					return new SerializerMatrix3x2();
				else if (typeof(Matrix4x4).Equals(_type))
					return new SerializerMatrix4x4();
				else
					return BuildSerializer_struct<T>();
			}
			private static object? BuildSerailizer_ValueType_object(Type _type)
			{
				if (typeof(DateTime).Equals(_type))
					return new Serialize_DateTime_object();
				else if (typeof(CGDK.buffer).Equals(_type))
					return new SerializerBuffer_object();
				else if (typeof(Vector2).Equals(_type))
					return new SerializerVector2_object();
				else if (typeof(Vector3).Equals(_type))
					return new SerializerVector3_object();
				else if (typeof(Vector4).Equals(_type))
					return new SerializerVector4_object();
				else if (typeof(Plane).Equals(_type))
					return new SerializerPlane_object();
				else if (typeof(Quaternion).Equals(_type))
					return new SerializerQuaternion_object();
				else if (typeof(Matrix3x2).Equals(_type))
					return new SerializerMatrix3x2_object();
				else if (typeof(Matrix4x4).Equals(_type))
					return new SerializerMatrix4x4_object();
				else
					return BuildSerializer_struct_object(_type);
			}

			private static void BuildSerializer_struct_serailization_list(Type _type, ref List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// 1) Field 정보를 얻는다.
				var temp_field = _type.GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);

				// 2) 각 Field값을 읽어 써넣는다.
				foreach (var iter in temp_field)
				{
					// check)
					if (iter.GetCustomAttributes(typeof(CGDK.Attribute.Field), false).Where(x => ((CGDK.Attribute.Field)x).IsSerializable == false).Any())
						continue;

					// - ger serializer
					var serializer = (IBase<object>?)ProcessGetSerializer_object(iter.FieldType);

					// check)
					Debug.Assert(serializer != null);

					// - set
					var temp_membeer_serialization_info = new MemberSerializationInfo(iter, serializer, 0);  //temp_membeer_serialization_info.offset = Marshal.OffsetOf(typeof(T), iter.Name).ToInt32();

					// - add serializer
					_list_member_serialization_info.Add(temp_membeer_serialization_info);
				}
			}

			private static SerializerStruct<T> BuildSerializer_struct<T>()
			{
				// 1) create list field info
				var list_member_serialization_info = new List<MemberSerializationInfo>();

				// 2) get serilization list
				BuildSerializer_struct_serailization_list(typeof(T), ref list_member_serialization_info);

				// 3) create and return
				return new SerializerStruct<T>(list_member_serialization_info);
			}
			private static SerializerStruct_object BuildSerializer_struct_object(Type _type)
			{
				// 1) create member_serialization_info
				var list_member_serialization_info = new List<MemberSerializationInfo>();

				// 2) get serilization list
				BuildSerializer_struct_serailization_list(_type, ref list_member_serialization_info);

				// 3) create BufferSerializer and return
				return new SerializerStruct_object (_type, list_member_serialization_info);
			} 

			private static object? BuildSerailizer_Dictionary<T>()
			{
				// declare) 
				object? result;

				// 1) try make knowed parametered
				result = BuildSerializer_Dictionary_typed<T>() 
					  ?? BuildSerializer_Dictionary_typed_o_o<T>();

				// return)
				return result;
			}
			private static object? BuildSerializer_Dictionary_typed<T>()
			{
				// 2) get argument type
				var types = typeof(T).GetGenericArguments();
				var type_key = types[0];
				var type_value = types[1];

				if (type_key == typeof(char))
					return BuildSerializer_Dictionary_typed_key_primitive<T, char>(type_value);
				else if (type_key == typeof(sbyte))
					return BuildSerializer_Dictionary_typed_key_primitive<T, sbyte>(type_value);
				else if (type_key == typeof(byte))
					return BuildSerializer_Dictionary_typed_key_primitive<T, byte>(type_value);
				else if (type_key == typeof(short))
					return BuildSerializer_Dictionary_typed_key_primitive<T, short>(type_value);
				else if (type_key == typeof(ushort))
					return BuildSerializer_Dictionary_typed_key_primitive<T, ushort>(type_value);
				else if (type_key == typeof(int))
					return BuildSerializer_Dictionary_typed_key_primitive<T, int>(type_value);
				else if (type_key == typeof(uint))
					return BuildSerializer_Dictionary_typed_key_primitive<T, uint>(type_value);
				else if (type_key == typeof(long))
					return BuildSerializer_Dictionary_typed_key_primitive<T, long>(type_value);
				else if (type_key == typeof(ulong))
					return BuildSerializer_Dictionary_typed_key_primitive<T, ulong>(type_value);
				else if (type_key == typeof(float))
					return BuildSerializer_Dictionary_typed_key_primitive<T, float>(type_value);
				else if (type_key == typeof(double))
					return BuildSerializer_Dictionary_typed_key_primitive<T, double>(type_value);
				else if (type_key == typeof(string))
					return BuildSerializer_Dictionary_typed_key_string<T>(type_value);
				else
					return BuildSerializer_Dictionary_typed_o<T>(type_value);
			}
			private static object? BuildSerializer_Dictionary_typed_key_primitive<T, K>(Type _type_second) where K : unmanaged
			{
				if (_type_second == typeof(char))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, char>();
				else if (_type_second == typeof(sbyte))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, sbyte>();
				else if (_type_second == typeof(byte))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, byte>();
				else if (_type_second == typeof(short))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, short>();
				else if (_type_second == typeof(ushort))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, ushort>();
				else if (_type_second == typeof(int))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, int>();
				else if (_type_second == typeof(uint))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, uint>();
				else if (_type_second == typeof(long))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, long>();
				else if (_type_second == typeof(ulong))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, ulong>();
				else if (_type_second == typeof(float))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, float>();
				else if (_type_second == typeof(double))
					return BuildSerializer_Dictionary_typed_key_value_primitive<K, double>();
				else if (_type_second == typeof(string))
					return BuildSerializer_Dictionary_typed_key_value<K, string>();
				else if (typeof(System.Collections.IList).IsAssignableFrom(_type_second))
					return BuildSerializer_Dictionary_typed_key_List<T, K>(_type_second);
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type_second))
					return BuildSerializer_Dictionary_typed_key_Directory<T, K>();
				else
					return BuildSerializer_Dictionary_typed_key_o<T, K>();
			}
			private static object? BuildSerializer_Dictionary_typed_key_string<T>(Type _type_second)
			{
				if (_type_second == typeof(char))
					return BuildSerializer_Dictionary_typed_key_value<string, char>();
				else if (_type_second == typeof(sbyte))
					return BuildSerializer_Dictionary_typed_key_value<string, sbyte>();
				else if (_type_second == typeof(byte))
					return BuildSerializer_Dictionary_typed_key_value<string, byte>();
				else if (_type_second == typeof(short))
					return BuildSerializer_Dictionary_typed_key_value<string, short>();
				else if (_type_second == typeof(ushort))
					return BuildSerializer_Dictionary_typed_key_value<string, ushort>();
				else if (_type_second == typeof(int))
					return BuildSerializer_Dictionary_typed_key_value<string, int>();
				else if (_type_second == typeof(uint))
					return BuildSerializer_Dictionary_typed_key_value<string, uint>();
				else if (_type_second == typeof(long))
					return BuildSerializer_Dictionary_typed_key_value<string, long>();
				else if (_type_second == typeof(ulong))
					return BuildSerializer_Dictionary_typed_key_value<string, ulong>();
				else if (_type_second == typeof(float))
					return BuildSerializer_Dictionary_typed_key_value<string, float>();
				else if (_type_second == typeof(double))
					return BuildSerializer_Dictionary_typed_key_value<string, double>();
				else if (_type_second == typeof(string))
					return BuildSerializer_Dictionary_typed_key_value<string, string>();
				else if (typeof(System.Collections.IList).IsAssignableFrom(_type_second))
					return BuildSerializer_Dictionary_typed_key_List<T, string>(_type_second);
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(_type_second))
					return BuildSerializer_Dictionary_typed_key_Directory<T, string>();
				else
					return BuildSerializer_Dictionary_typed_key_o<T, string>();
			}
			private static object? BuildSerializer_Dictionary_typed_key_List<T, K>(Type _type_second) where K : notnull
			{
				// 1) get type of param
				var type_param = _type_second.GetGenericArguments()[0];

				// 2) create builder by type
				if (type_param == typeof(char))
					return BuildSerializer_Dictionary_typed_key_value<K, List<char>>();
				else if (type_param == typeof(sbyte))
					return BuildSerializer_Dictionary_typed_key_value<K, List<sbyte>>();
				else if (type_param == typeof(byte))
					return BuildSerializer_Dictionary_typed_key_value<K, List<byte>>();
				else if (type_param == typeof(short))
					return BuildSerializer_Dictionary_typed_key_value<K, List<short>>();
				else if (type_param == typeof(ushort))
					return BuildSerializer_Dictionary_typed_key_value<K, List<ushort>>();
				else if (type_param == typeof(int))
					return BuildSerializer_Dictionary_typed_key_value<K, List<int>>();
				else if (type_param == typeof(uint))
					return BuildSerializer_Dictionary_typed_key_value<K, List<uint>>();
				else if (type_param == typeof(long))
					return BuildSerializer_Dictionary_typed_key_value<K, List<long>>();
				else if (type_param == typeof(ulong))
					return BuildSerializer_Dictionary_typed_key_value<K, List<ulong>>();
				else if (type_param == typeof(float))
					return BuildSerializer_Dictionary_typed_key_value<K, List<float>>();
				else if (type_param == typeof(double))
					return BuildSerializer_Dictionary_typed_key_value<K, List<double>>();
				else if (type_param == typeof(string))
					return BuildSerializer_Dictionary_typed_key_value<K, List<string>>();
				else
					return BuildSerializer_Dictionary_typed_key_o<T, K>();
			}
			private static object? BuildSerializer_Dictionary_typed_key_Directory<T, K>() where K : notnull
			{
				return BuildSerializer_Dictionary_typed_key_o<T, K>();
			}
			private static object? BuildSerializer_Dictionary_typed_o<T>(Type _type_second)
			{
				if (_type_second == typeof(char))
					return BuildSerializer_Dictionary_typed_o_value<T, char>();
				else if (_type_second == typeof(sbyte))
					return BuildSerializer_Dictionary_typed_o_value<T, sbyte>();
				else if (_type_second == typeof(byte))
					return BuildSerializer_Dictionary_typed_o_value<T, byte>();
				else if (_type_second == typeof(short))
					return BuildSerializer_Dictionary_typed_o_value<T, short>();
				else if (_type_second == typeof(ushort))
					return BuildSerializer_Dictionary_typed_o_value<T, ushort>();
				else if (_type_second == typeof(int))
					return BuildSerializer_Dictionary_typed_o_value<T, int>();
				else if (_type_second == typeof(uint))
					return BuildSerializer_Dictionary_typed_o_value<T, uint>();
				else if (_type_second == typeof(long))
					return BuildSerializer_Dictionary_typed_o_value<T, long>();
				else if (_type_second == typeof(ulong))
					return BuildSerializer_Dictionary_typed_o_value<T, ulong>();
				else if (_type_second == typeof(float))
					return BuildSerializer_Dictionary_typed_o_value<T, float>();
				else if (_type_second == typeof(double))
					return BuildSerializer_Dictionary_typed_o_value<T, double>();
				else if (_type_second == typeof(string))
					return BuildSerializer_Dictionary_typed_o_value<T, string>();
				else
					return null;
			}
			private static object? BuildSerializer_Dictionary_object(Type _type)
			{
				return BuildSerializer_Dictionary_object_typed(_type) 
					?? BuildSerializer_Dictionary_object_o_o(_type);
			}
			private static object? BuildSerializer_Dictionary_object_typed(Type _type_object)
			{
				// 1) get argument type
				var types = _type_object.GetGenericArguments();
				var type_key = types[0];

				if (type_key == typeof(char))
					return BuildSerializer_Dictionary_object_typed_key_primitive<char>(_type_object);
				else if (type_key == typeof(sbyte))
					return BuildSerializer_Dictionary_object_typed_key_primitive<sbyte>(_type_object);
				else if (type_key == typeof(byte))
					return BuildSerializer_Dictionary_object_typed_key_primitive<byte>(_type_object);
				else if (type_key == typeof(short))
					return BuildSerializer_Dictionary_object_typed_key_primitive<short>(_type_object);
				else if (type_key == typeof(ushort))
					return BuildSerializer_Dictionary_object_typed_key_primitive<ushort>(_type_object);
				else if (type_key == typeof(int))
					return BuildSerializer_Dictionary_object_typed_key_primitive<int>(_type_object);
				else if (type_key == typeof(uint))
					return BuildSerializer_Dictionary_object_typed_key_primitive<uint>(_type_object);
				else if (type_key == typeof(long))
					return BuildSerializer_Dictionary_object_typed_key_primitive<long>(_type_object);
				else if (type_key == typeof(ulong))
					return BuildSerializer_Dictionary_object_typed_key_primitive<ulong>(_type_object);
				else if (type_key == typeof(float))
					return BuildSerializer_Dictionary_object_typed_key_primitive<float>(_type_object);
				else if (type_key == typeof(double))
					return BuildSerializer_Dictionary_object_typed_key_primitive<double>(_type_object);
				else if (type_key == typeof(string))
					return BuildSerializer_Dictionary_object_typed_key_string(_type_object);
				else
					return null;
			}
			private static object? BuildSerializer_Dictionary_object_typed_key_primitive<K>(Type _type_object) where K : unmanaged
			{
				// 2) get argument type
				var types = _type_object.GetGenericArguments();
				var type_value = types[1];

				// 2) create builder by type
				if (type_value == typeof(char))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, char>();
				else if (type_value == typeof(sbyte))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, sbyte>();
				else if (type_value == typeof(byte))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, byte>();
				else if (type_value == typeof(short))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, short>();
				else if (type_value == typeof(ushort))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, ushort>();
				else if (type_value == typeof(int))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, int>();
				else if (type_value == typeof(uint))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, uint>();
				else if (type_value == typeof(long))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, long>();
				else if (type_value == typeof(ulong))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, ulong>();
				else if (type_value == typeof(float))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, float>();
				else if (type_value == typeof(double))
					return BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, double>();
				else if (type_value == typeof(string))
					return BuildSerializer_Dictionary_object_typed_key_value<K, string>();
				else if (typeof(System.Collections.IList).IsAssignableFrom(type_value))
					return BuildSerializer_Dictionary_object_typed_key_List<K>(_type_object);
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(type_value))
					return BuildSerializer_Dictionary_object_typed_key_Directory<K>();
				else
					return BuildSerializer_Dictionary_object_key_o<K>(type_value); ;
			}
			private static object? BuildSerializer_Dictionary_object_typed_key_string(Type _type_object)
			{
				// 1) get argument type
				var types = _type_object.GetGenericArguments();
				var type_value = types[1];

				// 2) create builder by type
				if (type_value == typeof(char))
					return BuildSerializer_Dictionary_object_typed_key_value<string, char>();
				else if (type_value == typeof(sbyte))
					return BuildSerializer_Dictionary_object_typed_key_value<string, sbyte>();
				else if (type_value == typeof(byte))
					return BuildSerializer_Dictionary_object_typed_key_value<string, byte>();
				else if (type_value == typeof(short))
					return BuildSerializer_Dictionary_object_typed_key_value<string, short>();
				else if (type_value == typeof(ushort))
					return BuildSerializer_Dictionary_object_typed_key_value<string, ushort>();
				else if (type_value == typeof(int))
					return BuildSerializer_Dictionary_object_typed_key_value<string, int>();
				else if (type_value == typeof(uint))
					return BuildSerializer_Dictionary_object_typed_key_value<string, uint>();
				else if (type_value == typeof(long))
					return BuildSerializer_Dictionary_object_typed_key_value<string, long>();
				else if (type_value == typeof(ulong))
					return BuildSerializer_Dictionary_object_typed_key_value<string, ulong>();
				else if (type_value == typeof(float))
					return BuildSerializer_Dictionary_object_typed_key_value<string, float>();
				else if (type_value == typeof(double))
					return BuildSerializer_Dictionary_object_typed_key_value<string, double>();
				else if (type_value == typeof(string))
					return BuildSerializer_Dictionary_object_typed_key_value<string, string>();
				else if (typeof(System.Collections.IList).IsAssignableFrom(type_value))
					return BuildSerializer_Dictionary_object_typed_key_List<string>(_type_object);
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(type_value))
					return BuildSerializer_Dictionary_object_typed_key_Directory<string>();
				else
					return BuildSerializer_Dictionary_object_key_o<string>(type_value); ;
			}
			private static object? BuildSerializer_Dictionary_object_typed_key_List<K>(Type _type_object) where K : notnull
			{
				// 1) get argument type
				var types = _type_object.GetGenericArguments();
				var type_value = types[1];
				var type_param = type_value.GetGenericArguments()[0];

				// 2) create builder by type
				if (type_param == typeof(char))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<char>>();
				else if (type_param == typeof(sbyte))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<sbyte>>();
				else if (type_param == typeof(byte))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<byte>>();
				else if (type_param == typeof(short))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<short>>();
				else if (type_param == typeof(ushort))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<ushort>>();
				else if (type_param == typeof(int))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<int>>();
				else if (type_param == typeof(uint))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<uint>>();
				else if (type_param == typeof(long))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<long>>();
				else if (type_param == typeof(ulong))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<ulong>>();
				else if (type_param == typeof(float))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<float>>();
				else if (type_param == typeof(double))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<double>>();
				else if (type_param == typeof(string))
					return BuildSerializer_Dictionary_object_typed_key_value<K, List<string>>();
				else
					return BuildSerializer_Dictionary_object_key_o<K>(_type_object);
			}
			private static object? BuildSerializer_Dictionary_object_typed_key_Directory<K>() where K : notnull
			{
				return null;
			}
			private static SerializerDictionary<K, V> BuildSerializer_Dictionary_typed_key_value<K, V>() where K : notnull
			{
				return new SerializerDictionary<K, V>();
			}
			private static SerializerDictionary_primitive_primitive<K, V> BuildSerializer_Dictionary_typed_key_value_primitive<K, V>() where K:unmanaged where V:unmanaged
			{
				return new SerializerDictionary_primitive_primitive<K, V>();
			}
			private static SerializerDictionary<T, K, object> BuildSerializer_Dictionary_typed_key_o<T, K>() where K : notnull
			{
				return new SerializerDictionary<T, K, object> (
					ProcessGetSerializer<K>(),
					(IBase<object>?)ProcessGetSerializer_object(typeof(T).GetGenericArguments()[1])!
				);
			}

			private static SerializerDictionary<T, object, V> BuildSerializer_Dictionary_typed_o_value<T, V>()
			{
				return new SerializerDictionary<T, object, V> (
					(IBase<object>?)ProcessGetSerializer_object(typeof(T).GetGenericArguments()[0]),
					ProcessGetSerializer<V>());
			}
			private static SerializerDictionary<T, object, object> BuildSerializer_Dictionary_typed_o_o<T>()
			{
				var types_argument = typeof(T).GetGenericArguments();
				return new SerializerDictionary<T, object, object> (
						(IBase<object>?)ProcessGetSerializer_object(types_argument[0]),
						(IBase<object>?)ProcessGetSerializer_object(types_argument[1])!
					);
			}
			private static SerializerDictionary_object_typed<K, V> BuildSerializer_Dictionary_object_typed_key_value<K, V>() where K : notnull
			{
				return new SerializerDictionary_object_typed<K, V>();
			}
			private static SerializerDictionary_object_primitive_primitive<K, V> BuildSerializer_Dictionary_object_typed_key_value_primitivie<K, V>() where K : unmanaged where V : unmanaged
			{
				return new SerializerDictionary_object_primitive_primitive<K, V>();
			}
			private static SerializerDictionary_object_no_typed<K, object> BuildSerializer_Dictionary_object_key_o<K>(Type _type) where K : notnull
			{
				return new SerializerDictionary_object_no_typed<K, object>(
					_type,
					ProcessGetSerializer<K>(),
					(IBase<object>?)ProcessGetSerializer_object(_type.GetGenericArguments()[1])
				);
			}
			private static SerializerDictionary_object BuildSerializer_Dictionary_object_o_o(Type _type)
			{
				return new SerializerDictionary_object (
						_type,
						(IBase<object>?)ProcessGetSerializer_object(_type.GetGenericArguments()[0]),
						(IBase<object>?)ProcessGetSerializer_object(_type.GetGenericArguments()[1])
					);
			}

			private static object? BuildSerializer_Array<T>()
			{
				// 1) try make knowed parametered
				return BuildSerializer_Array(typeof(T))
					   ?? BuildSerailizer_Array_no_typed<T>();
			}
			private static object? BuildSerializer_Array_object(Type _type)
			{
				// 1) try make knowed parametered
				return BuildSerializer_Array_object_primitive(_type)
					   ?? BuildSerailizer_Array_object_no_typed(_type);
			}
			private static object? BuildSerializer_Array(Type _type)
			{
				// 1) get argument type
				var type_param = _type.GetElementType();

				if (type_param == typeof(char))
					return BuildSerailizer_Array_typed_primitive<char>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_Array_typed_primitive<sbyte>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_Array_typed_primitive<byte>();
				else if (type_param == typeof(short))
					return BuildSerailizer_Array_typed_primitive<short>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_Array_typed_primitive<ushort>();
				else if (type_param == typeof(int))
					return BuildSerailizer_Array_typed_primitive<int>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_Array_typed_primitive<uint>();
				else if (type_param == typeof(long))
					return BuildSerailizer_Array_typed_primitive<long>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_Array_typed_primitive<ulong>();
				else if (type_param == typeof(float))
					return BuildSerailizer_Array_typed_primitive<float>();
				else if (type_param == typeof(double))
					return BuildSerailizer_Array_typed_primitive<double>();
				else if (type_param == typeof(string))
					return BuildSerailizer_Array_typed<string>();
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(type_param))
					return BuildSerailizer_Array_typed_Dictionary();
				else if (typeof(System.Collections.IList).IsAssignableFrom(type_param))
					return BuildSerailizer_Array_typed_List(_type);
				else
					return null;
			}
			private static object? BuildSerailizer_Array_typed_Dictionary()
			{
				return null;
			}
			private static object? BuildSerailizer_Array_typed_List(Type _type)
			{
				// 1) get argument type
				var type_value = _type.GetElementType();

				// check)
				Debug.Assert(type_value != null);

				// 2) get template argment type
				var type_param = type_value.GetGenericArguments()[0];

				// 3) ...
				if (type_param == typeof(char))
					return BuildSerailizer_Array_typed<char[]>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_Array_typed<sbyte[]>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_Array_typed<byte[]>();
				else if (type_param == typeof(short))
					return BuildSerailizer_Array_typed<short[]>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_Array_typed<ushort[]>();
				else if (type_param == typeof(int))
					return BuildSerailizer_Array_typed<int[]>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_Array_typed<uint[]>();
				else if (type_param == typeof(long))
					return BuildSerailizer_Array_typed<long[]>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_Array_typed<ulong[]>();
				else if (type_param == typeof(float))
					return BuildSerailizer_Array_typed<float[]>();
				else if (type_param == typeof(double))
					return BuildSerailizer_Array_typed<double[]>();
				else if (type_param == typeof(string))
					return BuildSerailizer_Array_typed<string[]>();
				else
					return null;
			}
			private static object? BuildSerializer_Array_object_primitive(Type _type)
			{
				// 1) get argument type
				var type_param = _type.GetElementType();

				// 2) ...
				if (type_param == typeof(char))
					return BuildSerailizer_Array_object_typed_primitive<char>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_Array_object_typed_primitive<sbyte>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_Array_object_typed_primitive<byte>();
				else if (type_param == typeof(short))
					return BuildSerailizer_Array_object_typed_primitive<short>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_Array_object_typed_primitive<ushort>();
				else if (type_param == typeof(int))
					return BuildSerailizer_Array_object_typed_primitive<int>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_Array_object_typed_primitive<uint>();
				else if (type_param == typeof(long))
					return BuildSerailizer_Array_object_typed_primitive<long>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_Array_object_typed_primitive<ulong>();
				else if (type_param == typeof(float))
					return BuildSerailizer_Array_object_typed_primitive<float>();
				else if (type_param == typeof(double))
					return BuildSerailizer_Array_object_typed_primitive<double>();
				else if (type_param == typeof(string))
					return BuildSerailizer_Array_object_typed<string>();
				else
					return null;
			}
			private static SerializerArray_typed<V> BuildSerailizer_Array_typed<V>()
			{
				return new SerializerArray_typed<V>();
			}
			private static SerializerArray_typed_primitive<V> BuildSerailizer_Array_typed_primitive<V>() where V : unmanaged
			{
				return new SerializerArray_typed_primitive<V>();
			}
			private static SerializerArray_no_typed<T> BuildSerailizer_Array_no_typed<T>()
			{
				return new SerializerArray_no_typed<T>();
			}
			private static SerializerArray_object_typed<V> BuildSerailizer_Array_object_typed<V>()
			{
				return new SerializerArray_object_typed<V>();
			}
			private static SerializerArray_object_typed_primitive<V> BuildSerailizer_Array_object_typed_primitive<V>() where V:unmanaged
			{
				var created = new SerializerArray_object_typed_primitive<V>();
				return created;
			}
			private static SerializerArray_object_no_typed BuildSerailizer_Array_object_no_typed(Type _type)
			{
				return new SerializerArray_object_no_typed (
						_type,
						(IBase<object>?)ProcessGetSerializer_object(_type.GetGenericArguments()[0])
					);
			}

			private static object? BuildSerailizer_List<T>()
			{
				return BuildSerializer_List_primitive(typeof(T))
					   ?? BuildSerailizer_List_no_typed<T>();
			}
			private static object? BuildSerailizer_List_object(Type _type)
			{
				// 1) try make knowed parametered
				return BuildSerializer_List_object_primitive(_type)
					   ?? BuildSerailizer_List_object_no_typed(_type);
			}
			private static object? BuildSerializer_List_primitive(Type _type)
			{
				// 1) get argument type
				var type_param = _type.GetGenericArguments()[0];

				// 2) 
				if (type_param == typeof(char))
					return BuildSerailizer_List_typed_primitive<char>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_List_typed_primitive<sbyte>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_List_typed_primitive<byte>();
				else if (type_param == typeof(short))
					return BuildSerailizer_List_typed_primitive<short>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_List_typed_primitive<ushort>();
				else if (type_param == typeof(int))
					return BuildSerailizer_List_typed_primitive<int>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_List_typed_primitive<uint>();
				else if (type_param == typeof(long))
					return BuildSerailizer_List_typed_primitive<long>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_List_typed_primitive<ulong>();
				else if (type_param == typeof(float))
					return BuildSerailizer_List_typed_primitive<float>();
				else if (type_param == typeof(double))
					return BuildSerailizer_List_typed_primitive<double>();
				else if (type_param == typeof(string))
					return BuildSerailizer_List_string();
				else if (typeof(System.Collections.IDictionary).IsAssignableFrom(type_param))
					return BuildSerailizer_List_typed_Dictionary();
				else if (typeof(System.Collections.IList).IsAssignableFrom(type_param))
					return BuildSerailizer_List_typed_List(_type);
				else
					return null;
			}
			private static object? BuildSerailizer_List_typed_Dictionary()
			{
				return null;
			}
			private static object? BuildSerailizer_List_typed_List(Type _type)
			{
				// 1) get argument type
				var type_value = _type.GetGenericArguments()[0];

				// check)
				Debug.Assert(type_value != null);

				// 2) get template argment type
				var type_param = type_value.GetGenericArguments()[0];

				if (type_param == typeof(char))
					return BuildSerailizer_List_typed<List<char>>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_List_typed<List<sbyte>>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_List_typed<List<byte>>();
				else if (type_param == typeof(short))
					return BuildSerailizer_List_typed<List<short>>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_List_typed<List<ushort>>();
				else if (type_param == typeof(int))
					return BuildSerailizer_List_typed<List<int>>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_List_typed<List<uint>>();
				else if (type_param == typeof(long))
					return BuildSerailizer_List_typed<List<long>>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_List_typed<List<ulong>>();
				else if (type_param == typeof(float))
					return BuildSerailizer_List_typed<List<float>>();
				else if (type_param == typeof(double))
					return BuildSerailizer_List_typed<List<double>>();
				else if (type_param == typeof(string))
					return BuildSerailizer_List_typed<List<string>>();
				else
					return null;
			}
			private static object? BuildSerializer_List_object_primitive(Type _type)
			{
				// 1) get argument type
				var type_param = _type.GetGenericArguments()[0];

				if (type_param == typeof(char))
					return BuildSerailizer_List_object_typed_primitive<char>();
				else if (type_param == typeof(sbyte))
					return BuildSerailizer_List_object_typed_primitive<sbyte>();
				else if (type_param == typeof(byte))
					return BuildSerailizer_List_object_typed_primitive<byte>();
				else if (type_param == typeof(short))
					return BuildSerailizer_List_object_typed_primitive<short>();
				else if (type_param == typeof(ushort))
					return BuildSerailizer_List_object_typed_primitive<ushort>();
				else if (type_param == typeof(int))
					return BuildSerailizer_List_object_typed_primitive<int>();
				else if (type_param == typeof(uint))
					return BuildSerailizer_List_object_typed_primitive<uint>();
				else if (type_param == typeof(long))
					return BuildSerailizer_List_object_typed_primitive<long>();
				else if (type_param == typeof(ulong))
					return BuildSerailizer_List_object_typed_primitive<ulong>();
				else if (type_param == typeof(float))
					return BuildSerailizer_List_object_typed_primitive<float>();
				else if (type_param == typeof(double))
					return BuildSerailizer_List_object_typed_primitive<double>();
				else if (type_param == typeof(string))
					return BuildSerailizer_List_object_string();
				else
					return null;
			}
			private static SerializerList_typed<V> BuildSerailizer_List_typed<V>()
			{
				return new SerializerList_typed<V>();
			}
			private static SerializerList_string BuildSerailizer_List_string()
			{
				return new SerializerList_string();
			}

			private static SerializerList_typed_primitive<V> BuildSerailizer_List_typed_primitive<V>() where V : unmanaged
			{
				return new SerializerList_typed_primitive<V>();
			}
			private static SerializerList_no_typed<T> BuildSerailizer_List_no_typed<T>()
			{
				return new SerializerList_no_typed<T>();
			}
			private static SerializerList_object_typed_primitive<V> BuildSerailizer_List_object_typed_primitive<V>() where V:unmanaged
			{
				return new SerializerList_object_typed_primitive<V>();
			}
			private static SerializerList_obejct_string BuildSerailizer_List_object_string()
			{
				return new SerializerList_obejct_string();
			}

			private static SerializerList_object_no_typed BuildSerailizer_List_object_no_typed(Type _type)
			{
				return new SerializerList_object_no_typed (
						_type,
						(IBase<object>?)ProcessGetSerializer_object(_type.GetGenericArguments()[0])
					);
			}

			private static object? BuildSerailizer_Collection<T>()
			{
				return null;
			}
			private static object? BuildSerailizer_Collection_object()
			{
				return null;
			}

			private static void BuildSerializer_Class(Type _type, ref List<MemberSerializationInfo> _list_member_serialization_info)
			{
				// check)
				if (IsSerializableType(_type) == false)
					throw new System.NullReferenceException("class is not CGDK.serializable");

				// 2) 부모의 부모가 nullptr이면 object를 제외하고 최고 부모 클래스다.
				if (_type.BaseType != null && _type.BaseType.BaseType != null)
				{
					// - process parent class
					BuildSerializer_Class(_type.BaseType, ref _list_member_serialization_info);
				}

				// 3) member변수들을 얻는다.
				var temp_field = _type.GetFields(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly);

				// 4) 최상위 부모의 맴버부터 차례대로 buffer 에 append 한다
				foreach (var iter in temp_field)
				{
					// check)
					if (iter.GetCustomAttributes(typeof(CGDK.Attribute.Field), false).Where(x => ((CGDK.Attribute.Field)x).IsSerializable).Any() == false)
						continue;

					// - set serializer
					var temp_membeer_serialization_info = new MemberSerializationInfo (
							iter,
							(IBase<object>?)ProcessGetSerializer_object(iter.FieldType)!,
							0
						);

					// check)
					Debug.Assert(temp_membeer_serialization_info.serializer != null);

					// - add serializer
					_list_member_serialization_info.Add(temp_membeer_serialization_info);
				}
			}

			private static SerializerClass<T> BuildSerializer_Class<T>()
			{
				// 1) 
				var list_member_serialization_info = new List<MemberSerializationInfo>();

				// 2) build class info
				BuildSerializer_Class(typeof(T), ref list_member_serialization_info);

				// 3) create and return 
				return new SerializerClass<T>(list_member_serialization_info);
			}
			private static SerializerClass_object BuildSerializer_Class_object(Type _type)
			{
				// check)
				if (IsSerializableType(_type) == false)
					throw new System.NullReferenceException("class is not CGDK.serializable");

				// 1) allloc List<member_inf>
				var temp_list_member_serialization_info = new List<MemberSerializationInfo>();

				// check)
				Debug.Assert(temp_list_member_serialization_info != null);
	
				// 2) build class info
				BuildSerializer_Class(_type, ref temp_list_member_serialization_info);

				// chekck)
				if (temp_list_member_serialization_info.Count == 0)
					throw new System.NullReferenceException("None member field serializable use 'CGDK.Attribute.Field'");

				// return) create and return 
				return new SerializerClass_object (	_type, temp_list_member_serialization_info);
			}

			public static IBase<T> ProcessGetSerializer<T>()
			{
				// declare) 
				object? result = null;

				// 2) get type
				var type = typeof(T);

				lock (dictionary_serializer)
				{
					// 3) 이미 존재하는 가?
					var is_exist = dictionary_serializer.TryGetValue(type, out result);

					// 4) 존재하지 않으면 새로 만든다.
					if (is_exist == false)
					{
						// - 종류에 다라 생성
						result = BuildSerialize<T>();

						// - add to dictionary (내부적으로 Initializer 하면서 추가하는 것이 있으므로 이렇게 할 필요가 있다.
						if (dictionary_serializer.ContainsKey(type) == false)
						{
							dictionary_serializer.Add(type, result);
						}
					}
				}

				// 4) casting
				var result_casted = (IBase<T>?)result;

				// check)
				Debug.Assert(result_casted != null);

				// return) 
				return result_casted;
			}
			public static IBase<Dictionary<K,V>> ProcessGetSerializer_Dictionary<K, V>() where K : notnull
			{
				// declare) 
				object? result = null;

				// 2) get type
				var type = typeof(Dictionary<K, V>);

				lock (dictionary_serializer)
				{
					// 3) 이미 존재하는 가?
					var is_exist = dictionary_serializer.TryGetValue(type, out result);

					// 4) type을 확인한다.
					if (is_exist == true)
					{
						// - 아니라면 교체
						if (result is IBase<Dictionary<K, V>>)
						{
							is_exist = false;
						}
					}

					// 4) 존재하지 않으면 새로 만든다.
					if (is_exist == false)
					{
						// - 먼저 시돈
						result = BuildSerializer_Dictionary_typed<Dictionary<K, V>>()
							   ?? BuildSerializer_Dictionary_typed_key_value<K, V>();

						// check)
						Debug.Assert(result != null);

						// - 무조건 삽입 혹은 교체
						dictionary_serializer[type] = result;
					}
				}

				// 4) casting
				var result_casted = Unsafe.As<IBase<Dictionary<K, V>>?>(result);

				// check)
				Debug.Assert(result_casted != null);

				// return) 
				return result_casted;
			}
			public static IBase<List<V>> ProcessSerializer_List<V>()
			{
				// declare) 
				object? result = null;

				// 2) get type
				var type = typeof(List<V>);

				lock (dictionary_serializer)
				{
					// 3) 이미 존재하는 가?
					var is_exist = dictionary_serializer.TryGetValue(type, out result);

					// 4) type을 확인한다.
					if (is_exist == true)
					{
						// - 같은 type이 아니면 교체
						if (result is SerializerList_typed<V>)
						{
							is_exist = false;
						}
					}

					// 4) 존재하지 않으면 새로 만든다.
					if (is_exist == false)
					{
						// - build
						result = BuildSerializer_List_primitive(typeof(List<V>))
							     ?? BuildSerailizer_List_typed<V>();

						// check)
						Debug.Assert(result != null);

						// - 무조건 삽입 혹은 교체
						dictionary_serializer[type] = result;
					}
				}

				// 4) casting
				var result_casted = Unsafe.As<IBase<List<V>>?>(result);

				// check)
				Debug.Assert(result_casted != null);

				// return) 
				return result_casted;
			}
			public static object? ProcessGetSerializer_object(Type _type)
			{
				// declare) 
				object? result = null;

				lock (dictionary_serializer_object)
				{
					// 1) 이미 존재하는 가?
					var is_exist = dictionary_serializer_object.TryGetValue(_type, out result);

					// 3) 존재하지 않으면 새로 만든다.
					if (is_exist == false)
					{
						// - 종류에 다라 생성
						result = BuildSerialize_object(_type);

						// - add to dictionary
						dictionary_serializer_object.Add(_type, result);
					}
				}

				// check)
				Debug.Assert(result != null);

				// return) 
				return result;
			}
		}

		public static class Get<T>
		{
			static public readonly IBase<T> instance = Builder.ProcessGetSerializer<T>();
		}
		public static class Get_Dictionary<K,V> where K : notnull
		{
			static public readonly IBase<Dictionary<K,V>> instance = Builder.ProcessGetSerializer_Dictionary<K, V>();
		}
		public static class Get_List<V>
		{
			static public readonly IBase<List<V>> instance = Builder.ProcessSerializer_List<V>();
		}
	}
}
