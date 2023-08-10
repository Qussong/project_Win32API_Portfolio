#pragma once
#include <cmath>

/*
	[ 실수형 ]
	실수 타입엔 double 과 float 이 있다.
		- double : 8 Byte
		- float : 4 Byte
	float 타입으로 실수 값을 사용하고자 한다면 값 뒤에 'f'를 붙여줘야 한다.
*/

#define PI 3.141592f

namespace van::math
{
	struct Vector2
	{
	public:
		Vector2();
		Vector2(float _x, float _y);
		Vector2(float _value);

		// 사칙연산 연산자 재정의
		// float값을 받을 경우 Vector2의 x,y 성분에 전달받은 값을 사칙연산하여 반환한다.
		Vector2 operator/(const float _value);
		Vector2 operator*(const float _value);
		Vector2 operator+(const float _value);
		Vector2 operator-(const float _value);

		void operator/=(const float _value);
		void operator+=(const float _value);
		void operator-=(const float _value);

		// Vector2를 받을 경우 전달받은 Vector2의 각각의 성분을
		// 내 각각의 성분에 사칙연산하여 반환한다.
		Vector2 operator/(const Vector2& _value);
		Vector2 operator*(const Vector2& _value);
		Vector2 operator+(const Vector2& _value);
		Vector2 operator-(const Vector2& _value);

		void operator/=(const Vector2& _value);
		void operator*=(const Vector2& _value);
		void operator-=(const Vector2& _value);
		Vector2& operator*=(const float& _value);
		Vector2& operator+=(const Vector2& _other);

		bool operator ==(const Vector2 _other);
		bool operator<=(const Vector2 _other);
		bool operator>=(const Vector2 _other);

		Vector2 operator-();

		void Clear();
		float Length();
		Vector2 Normalize();

		float x;
		float y;

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;
	};

	inline Vector2 Rotate(Vector2 _vector, float _degree)
	{
		float radian = (_degree / 180.0f) * PI;
		_vector.Normalize();
		float x = cosf(radian) * _vector.x - sinf(radian) * _vector.y;
		float y = sinf(radian) * _vector.x + cosf(radian) * _vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& _v1, Vector2& _v2)	// 내적?
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	inline float Cross(Vector2 _v1, Vector2 _v2)	// 외적?
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}
}