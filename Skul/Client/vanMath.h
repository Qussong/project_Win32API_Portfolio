#pragma once

/*
	[ 실수형 ]
	실수 타입엔 double 과 float 이 있다.
		- double : 8 Byte
		- float : 4 Byte
	float 타입으로 실수 값을 사용하고자 한다면 값 뒤에 'f'를 붙여줘야 한다.
*/

namespace van::math
{
	struct Vector2
	{
	public:
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

	public:
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{
		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{
		}
		
		Vector2 operator-(const Vector2 _other)
		{
			Vector2 temp;
			temp.x = x - _other.x;
			temp.y = y - _other.y;
			return temp;
		}

		Vector2 operator/(const float _value)
		{
			Vector2 temp;
			temp.x = x / _value;
			temp.y = y / _value;
			return temp;
		}

		Vector2 operator+(const Vector2 _other)
		{
			Vector2 temp;
			temp.x = x + _other.x;
			temp.y = y + _other.y;
			return temp;
		}

		bool operator==(const Vector2 _other)
		{
			if (x == _other.x && y == _other.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator!=(const Vector2 _other)
		{
			if (x == _other.x && y == _other.y)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	public:
		float x;
		float y;
	};
}