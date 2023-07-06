#include "vanSceneManager.h"
#include "vanTitleScene.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Init()
	{
		CreateScene<TitleScene>(L"TitleScene");
		//CreateScene<TitleScene>(L"StageScene");
		//CreateScene<TitleScene>(L"EndingScene");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);	// find(key) : 해당 키 값을 가진 pair 타입 값을 반환한다.
									// 만약 찾지 못하면 map.end() 를 반환한다.
		
		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;
	}

	Scene* SceneManager::GetActiveScene()
	{
		return mActiveScene;
	}
}