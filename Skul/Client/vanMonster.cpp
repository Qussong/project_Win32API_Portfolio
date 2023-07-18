#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"

van::Monster::Monster()
{
	// nothing
}

van::Monster::~Monster()
{
	// nothing
}

void van::Monster::Init()
{
	// nothing
}

void van::Monster::Update()
{
	GameObject::Update();
	/*
	Transform* tr = GetComponent<Transform>();
	math::Vector2 pos = tr->GetPosition();

	if (Input::GetKey(eKeyCode::W))	// top
	{
		if (pos.y > 0)
			pos.y -= SPEED * Time::DeltaTime();
		else
			__noop;
	}
	if (Input::GetKey(eKeyCode::S))	// down
	{
		if (pos.y < Window_Y - DIAMETER)
			pos.y += SPEED * Time::DeltaTime();
		else
			__noop;
	}
	if (Input::GetKey(eKeyCode::A))	// left
	{
		if (pos.x > 0)
			pos.x -= SPEED * Time::DeltaTime();
		else
			__noop;
	}
	if (Input::GetKey(eKeyCode::D))	// right
	{
		if (pos.x < Window_X - DIAMETER)
			pos.x += SPEED * Time::DeltaTime();
		else
			__noop;
	}

	tr->SetPosition(pos);
	*/
}

void van::Monster::Render(HDC _hdc)
{
	GameObject::Render(_hdc);
	/*
	HGDIOBJ origin = 
		SelectObject(_hdc, GetStockObject(DC_PEN));		// 펜 기본 색상 저장
	Transform* tr = GetComponent<Transform>();
	math::Vector2 pos = tr->GetPosition();

	SetDCPenColor(_hdc, RGB(255, 0, 255));				// 핑크색
	Rectangle(_hdc, pos.x, pos.y, pos.x + DIAMETER, pos.y + DIAMETER);
	SelectObject(_hdc, origin);							// 펜색상 원복
	*/
}
