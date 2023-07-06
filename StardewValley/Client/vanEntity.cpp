#include "vanEntity.h"

namespace van
{
	Entity::Entity()
		: mName(L"")
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::SetName(const std::wstring& name)
	{
		mName = name;
	}

	std::wstring& Entity::GetName()
	{
		return mName;
	}

}
