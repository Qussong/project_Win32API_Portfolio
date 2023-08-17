#include "vanEndingScene.h"
#include "vanCamera.h"

namespace van
{
	EndingScene::EndingScene()
	{
		// nothing
	}

	EndingScene::~EndingScene()
	{
		// nothing
	}

	void EndingScene::Init()
	{
		Scene::Init();

		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void EndingScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void EndingScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ EndingScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void EndingScene::SceneIN()
	{
		// nothing
	}

	void EndingScene::SceneOut()
	{
		// nothing
	}

	void EndingScene::CameraMove()
	{
		// nothing
	}

	void EndingScene::MakeWorld()
	{
		// nothing
	}

	void EndingScene::MakeFloor()
	{
		// nothing
	}

	void EndingScene::MakeWall()
	{
		// nothing
	}

	void EndingScene::MakeDoor()
	{
		// nothing
	}
}