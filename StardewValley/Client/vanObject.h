#pragma once
#include "CommonInclude.h"

namespace van
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = ScenManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);

		return gameObject;
	}
}
