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
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{
		}

	public:
		float x;
		float y;
	};
}