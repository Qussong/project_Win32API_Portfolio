#include "vanStage1BossEnterScene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"

namespace van
{
	Stage1BossEnterScene::Stage1BossEnterScene()
	{
		// nothing
	}

	Stage1BossEnterScene::~Stage1BossEnterScene()
	{
		// nothing
	}

	void Stage1BossEnterScene::Init()
	{
		// 1) BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, -80.0f));			// 위치값 설정
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Boss_Enter"));				// BackGround 객체의 texture 설정
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale 설정
		bgsr->SetAffectCamera(true);

		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1BossEnterScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1BossEnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1BossEnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage1BossEnterScene::SceneIN()
	{
	}
	void Stage1BossEnterScene::SceneOut()
	{
	}
}
