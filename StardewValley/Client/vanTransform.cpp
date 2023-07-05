#include "vanTransform.h"
#include "vanInput.h"
#include "vanTime.h"

namespace van
{
	Transform::Transform()
		: Component(enums::eComponentType::Transform)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Init()
	{
		// nothing
	}
	void Transform::Update()
	{
		// 키 입력
		if (Input::GetKey(eKeyCode::W))	// 상
		{
			if (mPosition.y > 0)
				mPosition.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// 하
		{
			if (mPosition.y < FHD_Y - DIAMETER)
				mPosition.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// 좌
		{
			if (mPosition.x > 0)
				mPosition.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// 우
		{
			if (mPosition.x < FHD_X - DIAMETER)
				mPosition.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}
	}
	void Transform::Render(HDC _hdc)
	{
		// nothing
	}
	void Transform::SetPosition(math::Vector2 position)
	{
		mPosition = position;
	}
	math::Vector2 Transform::GetPosition()
	{
		return mPosition;
	}
}