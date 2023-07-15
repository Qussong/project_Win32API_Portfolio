#include "vanHomeScene.h"
#include "vanPlayer.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"

#include "vanAnimator.h"

namespace van
{
	HomeScene::HomeScene()
	{
		// nothing
	}

	HomeScene::~HomeScene()
	{
		// nothing
	}

	void HomeScene::Init()
	{
		// 0) BackGround °´Ã¼

		// 1) Player °´Ã¼
		Texture* texture = ResourceManager::Load<Texture>(
			L"Skul"
			, L"..\\MyResources\\skul\\skul\\Idle_3_24.bmp");
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetScale(math::Vector2(1.0f, 1.0f));

		// 2) Monster °´Ã¼
		texture = ResourceManager::Load<Texture>(L"FarmerGirl"
			, L"..\\MyResources\\farmer-girl-base_2.bmp");
		Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		monster->GetComponent<Transform>()->SetPosition(math::Vector2(0, 0));

		Animator* at = monster->AddComponent<Animator>();
		at->CreateAnimation(L"FarmerIdle"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(16.0f, 32.0f)
			, math::Vector2(0.0f, 0.0f)
			, 6
			, 0.1f);
		at->CreateAnimation(L"FarmerRight"
			, texture
			, math::Vector2(0.0f, 32.0f)
			, math::Vector2(16.0f, 32.0f)
			, math::Vector2(0.0f, 0.0f)
			, 6
			, 0.1f);
		at->PlayAnimation(L"FarmerRight", true);
		at->SetAffectedCamera(true);


		// 3) Monster_2
		texture = ResourceManager::Load<Texture>(L"Monster_Cat"
			, L"..\\MyResources\\skul\\cat_1\\Walk_1_24.bmp");
		Monster* monster2 = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		monster2->GetComponent<Transform>()->SetPosition(math::Vector2(0, 0));
		sr = monster2->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetScale(math::Vector2(1.0f, 1.0f));

		Camera::SetTarget(player);	// Ä«¸Þ¶ó Å¸°Ù ¼³Á¤
	}

	void HomeScene::Update()
	{
		Scene::Update();
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ±¸ºÐ
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}