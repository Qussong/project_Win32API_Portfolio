#include "vanBossScene.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanPlayer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"

#include "vanMonster.h"
#include "vanTransform.h"
#include "vanAnimator.h"

namespace van
{
	BossScene::BossScene()
	{
		// nothing
	}

	BossScene::~BossScene()
	{
		// nothing
	}

	void BossScene::Init()
	{

		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void BossScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ BossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}
