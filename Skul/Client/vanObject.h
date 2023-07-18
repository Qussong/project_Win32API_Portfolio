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
		scene->AddGameObject(type, gameObject);			// 현재 Scene의 AddGameObject 함수를 호출하여 
														// 원하는 Layer에 원하는 T타입 객체(=GameObject객체) 추가해준다.
		return gameObject;
	}
}
 