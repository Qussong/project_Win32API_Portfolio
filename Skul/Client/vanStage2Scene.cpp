#include "vanStage2Scene.h"
#include "vanCamera.h"

namespace van
{
	Stage2Scene::Stage2Scene()
	{
		// nothing
	}

	Stage2Scene::~Stage2Scene()
	{
		// nothing
	}

	void Stage2Scene::Init()
	{
		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage2Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage2Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage2Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage2Scene::SceneIN()
	{
	}
	void Stage2Scene::SceneOut()
	{
	}
}