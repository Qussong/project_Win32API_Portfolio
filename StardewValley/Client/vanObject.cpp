#include "vanObject.h"

namespace van
{
	Object::Object()
		:x1(0)
		, y1(0)
		, x2(0)
		, y2(0)
		, directNum(0)
		, delta(0)
	{
	}
	Object::Object(int _x1, int _y1, int _x2, int _y2)
		: x1(_x1)
		, y1(_y1)
		, x2(_x2)
		, y2(_y2)
		, directNum(0)
		, delta(0)
	{
	}
	void Object::Init()
	{
		randomize();
		directNum = random(8);
	}
	void Object::Update()
	{
		switch (directNum)
		{
		case (int)Direction::Top:
			MoveTop();
			break;
		case (int)Direction::Bottom:
			MoveBottom();
			break;
		case (int)Direction::Left:
			MoveLeft();
			break;
		case (int)Direction::Right:
			MoveRight();
			break;
		case (int)Direction::TopLeft:
			MoveTopLeft();
			break;
		case (int)Direction::TopRight:
			MoveTopRight();
			break;
		case (int)Direction::BottomLeft:
			MoveBottomLeft();
			break;
		case (int)Direction::BottomRight:
			MoveBottomRight();
			break;
		default:
			__noop;
		}
	}
	void Object::Render(HDC _hdc)
	{
		Ellipse(_hdc, x1, y1, x2, y2);
	}
	void Object::setDelta(float _delta)
	{
		delta = _delta;
	}
}