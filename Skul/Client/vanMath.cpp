#include "vanMath.h"

namespace van::math
{
	Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	Vector2 Vector2::One = Vector2(1.0f, 1.0f);
	Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
	Vector2 Vector2::Up = Vector2(0.0f, -1.0f);

	Vector2::Vector2()
		: x(0.f)
		, y(0.f)
	{
	}

	Vector2::Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vector2::Vector2(float _value)
		: x(_value)
		, y(_value)
	{
	}

	Vector2 Vector2::operator/(const float _value)
	{
		Vector2 temp;
		temp.x = x / _value;
		temp.y = y / _value;

		return temp;
	}
	Vector2 Vector2::operator*(const float _value)
	{
		Vector2 temp;
		temp.x = x * _value;
		temp.y = y * _value;

		return temp;
	}
	Vector2 Vector2::operator+(const float _value)
	{
		Vector2 temp;
		temp.x = x + _value;
		temp.y = y + _value;

		return temp;
	}
	Vector2 Vector2::operator-(const float _value)
	{
		Vector2 temp;
		temp.x = x - _value;
		temp.y = y - _value;

		return temp;
	}

	void Vector2::operator/=(const float _value)
	{
		x /= _value;
		y /= _value;
	}

	void Vector2::operator+=(const float _value)
	{
		x += _value;
		y += _value;
	}
	void Vector2::operator-=(const float _value)
	{
		x -= _value;
		y -= _value;
	}

	Vector2 Vector2::operator/(const Vector2& _value)
	{
		Vector2 temp;
		temp.x = x / _value.x;
		temp.y = y / _value.y;

		return temp;
	}
	Vector2 Vector2::operator*(const Vector2& _value)
	{
		Vector2 temp;
		temp.x = x * _value.x;
		temp.y = y * _value.y;

		return temp;
	}
	Vector2 Vector2::operator+(const Vector2& _value)
	{
		Vector2 temp;
		temp.x = x + _value.x;
		temp.y = y + _value.y;

		return temp;
	}
	Vector2 Vector2::operator-(const Vector2& _value)
	{
		Vector2 temp;
		temp.x = x - _value.x;
		temp.y = y - _value.y;

		return temp;
	}

	void Vector2::operator/=(const Vector2& _value)
	{
		x /= _value.x;
		y /= _value.y;
	}
	void Vector2::operator*=(const Vector2& _value)
	{
		x *= _value.x;
		y *= _value.y;
	}
	Vector2& Vector2::operator+=(const Vector2& _other)
	{
		x += _other.x;
		y += _other.y;

		return *this;
	}
	void Vector2::operator-=(const Vector2& _value)
	{
		x -= _value.x;
		y -= _value.y;
	}

	Vector2& Vector2::operator*=(const float& _value)
	{
		x *= _value;
		y *= _value;

		return *this;
	}

	bool Vector2::operator ==(const Vector2 _other)
	{
		return (x == _other.x && y == _other.y);
	}

	bool Vector2::operator<=(const Vector2 _other)
	{
		return (x <= _other.x && y <= _other.y);
	}

	bool Vector2::operator>=(const Vector2 _other)
	{
		return (x >= _other.x && y >= _other.y);
	}

	Vector2 Vector2::operator-()
	{
		return Vector2(-x, -y);
	}

	void Vector2::Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Vector2::Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 Vector2::Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;

		return *this;
	}
}