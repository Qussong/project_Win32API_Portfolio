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

	void Entity::SetName(std::wstring& name)
	{
		mName = name;
	}

	std::wstring& Entity::GetName()
	{
		return mName;
	}

}
