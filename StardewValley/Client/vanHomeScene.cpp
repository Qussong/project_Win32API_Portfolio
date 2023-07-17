#include "vanHomeScene.h"
#include "vanPlayer.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"
#include "vanAnimator.h"
#include "vanBackGround.h"

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
		// 1) BackGround 按眉
		// \MyResources\skul\0_BG\1_BG_Home\Back_01.bmp
		Texture* texture = ResourceManager::Load<Texture>(
			L"BG_Home_1"
			, L"..\\MyResources\\skul\\0_BG\\1_BG_Home\\Back_01.bmp");
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetTexture(texture);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);

		// FarmerGirl Example 按眉
		/*
		texture = ResourceManager::Load<Texture>(L"FarmerGirl"
			, L"..\\MyResources\\farmer-girl-base.bmp");
		Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		monster->GetComponent<Transform>()->SetPosition(math::Vector2(0, 0));

		Animator* at = monster->AddComponent<Animator>();
		at->CreateAnimation(L"FarmerIdle"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(16.0f, 32.0f)
			, 6
			, math::Vector2(0.0f, 0.0f)
			, 0.1f);
		at->CreateAnimation(L"FarmerRight"
			, texture
			, math::Vector2(0.0f, 32.0f)
			, math::Vector2(16.0f, 32.0f)
			, 6
			, math::Vector2(0.0f, 0.0f)
			, 0.1f);
		at->PlayAnimation(L"FarmerRight", true);
		at->SetAffectedCamera(true);
		*/
		
		// 2) Tied_Skul_NPC
		// \MyResources\skul\1_NPC\Tied_Skul
		Monster* npc1 = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		Transform* tr = npc1->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(-500.0f, 230.0f));
		Animator* at = npc1->AddComponent<Animator>();
		at->CreateAnimationFolder(L"Tied_Skul_NPC"
			, L"..\\MyResources\\skul\\1_NPC\\Tied_Skul");
		at->PlayAnimation(L"Tied_Skul_NPC", true);
		at->SetAffectedCamera(true);

		// Cat_idle
		// \MyResources\skul\1_NPC\Cat_Green\Idle
		Monster* cat = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		tr = cat->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(-300.0f, 240.0f));
		at = cat->AddComponent<Animator>();
		at->CreateAnimationFolder(L"Cat_idle"
			, L"..\\MyResources\\skul\\1_NPC\\Cat_Green\\Idle");
		//Animation* an =  
		at->PlayAnimation(L"Cat_idle", true);
		at->SetAffectedCamera(true);

		// 3) Player 按眉
		// \MyResources\skul\11_Skul
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		tr = player->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(0, 0));
		at = player->AddComponent<Animator>();
		at->CreateAnimationFolder(L"Skul_Idle_Weapon_Left", L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_L");
		at->CreateAnimationFolder(L"Skul_Idle_Weapon_Right", L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_R");
		at->CreateAnimationFolder(L"Skul_Walk_Left", L"..\\MyResources\\skul\\11_Skul\\Walk_L");
		at->CreateAnimationFolder(L"Skul_Walk_Right", L"..\\MyResources\\skul\\11_Skul\\Walk_R");
		at->PlayAnimation(L"Skul_Idle_Weapon_Left", true);
		at->SetAffectedCamera(true);

		Camera::SetTarget(player);
	}

	void HomeScene::Update()
	{
		Scene::Update();
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 备盒
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}