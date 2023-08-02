#include "vanSceneManager.h"
#include "vanTitleScene.h"
#include "vanLoadingScene.h"
#include "vanHomeScene.h"
#include "vanStageScene.h"
#include "vanBossScene.h"
#include "CommonInclude.h"
#include "vanCamera.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Init()
	{
		CreateScene<LoadingScene>(L"LoadingScene");
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<HomeScene>(L"HomeScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<BossScene>(L"BossScene");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		// 화면 전환
		if (Input::GetKey(eKeyCode::Q))
		{
			LoadScene(L"TitleScene");
		}
		if (Input::GetKey(eKeyCode::W))
		{
			LoadScene(L"LoadingScene");
		}
		if (Input::GetKey(eKeyCode::E))
		{
			LoadScene(L"HomeScene");
		}
		if (Input::GetKey(eKeyCode::R))
		{
			LoadScene(L"StageScene");
		}
		if (Input::GetKey(eKeyCode::T))
		{
			LoadScene(L"BossScene");
		}

		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);	
		// find(key) : 해당 키 값을 가진 pair 타입 값을 반환한다.
		// 만약 찾지 못하면 map.end() 를 반환한다.

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;
	}
}