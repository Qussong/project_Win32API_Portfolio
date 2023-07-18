#include "vanComponent.h"

namespace van
{
	Component::Component(enums::eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{

	}

	Component::~Component()
	{

	}

	void Component::Init()
	{
		// nothing
	}

	void Component::Update()
	{
		// nothing
	}

	void Component::Render(HDC _hdc)
	{
		// nothing
	}
}