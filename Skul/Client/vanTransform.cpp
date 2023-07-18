#include "vanTransform.h"
#include "vanInput.h"
#include "vanTime.h"

namespace van
{
	Transform::Transform()
		: Component(enums::eComponentType::Transform)
	{
		// nothing
	}

	Transform::~Transform()
	{
		// nothing
	}

	void Transform::Init()
	{
		// nothing
	}

	void Transform::Update()
	{
		// nothing
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