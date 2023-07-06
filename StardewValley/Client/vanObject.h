#pragma once
#include "vanScene.h"
#include "vanGameObject.h"
#include "vanSceneManager.h"


namespace van::Object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();	// SceneManger를 통해 현재 화면에 보이고 있는 Scene의 주소를 가져온다.
		scene->AddGameObject(type, gameObject);

		return gameObject;
	}
}
 