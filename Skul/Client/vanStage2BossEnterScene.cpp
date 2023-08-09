#include "vanStage2BossEnterScene.h"
#include "vanCamera.h"

namespace van
{
	Stage2BossEnterScene::Stage2BossEnterScene()
	{
		// nothing
	}

	Stage2BossEnterScene::~Stage2BossEnterScene()
	{
		// nothing
	}

	void Stage2BossEnterScene::Init()
	{
		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage2BossEnterScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage2BossEnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage2BossEnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}