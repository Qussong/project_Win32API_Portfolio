#include "vanGhost.h"
#include "vanInput.h"
#include "vanTransform.h"

namespace van
{
	Ghost::Ghost()
	{
		// npthing
	}

	Ghost::~Ghost()
	{
		// npthing
	}

	void Ghost::Init()
	{
		// npthing
	}

	void Ghost::Update()
	{
		GameObject::Update();

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
	}

	void Ghost::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		Rectangle(_hdc, pos.x, pos.y, pos.x + DIAMETER, pos.y + DIAMETER);
		Ellipse(_hdc, pos.x, pos.y, pos.x + DIAMETER, pos.y + DIAMETER);

	}
}