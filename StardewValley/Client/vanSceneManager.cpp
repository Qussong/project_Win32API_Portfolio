#include "vanSceneManager.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Init()
	{

	}

	void SceneManager::Update()
	{

	}

	void SceneManager::Render(HDC _hdc)
	{

	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		return nullptr;
	}

	Scene* SceneManager::GetActiveScene()
	{
		return mActiveScene;
	}
}