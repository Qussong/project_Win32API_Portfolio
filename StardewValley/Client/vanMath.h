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

		float x;
		float y;
	};
}