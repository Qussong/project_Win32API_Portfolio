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
		// 1) BackGround 객체
		// \MyResources\skul\0_BG\1_BG_Home\Back_01.bmp
		Texture* texture = 
			ResourceManager::Load<Texture>(L"BG_Home_1"
			, L"..\\MyResources\\skul\\0_BG\\1_BG_Home\\Back_01.bmp");				// 이미지 로드
		BackGround* bg=
			Object::Instantiate<BackGround>(enums::eLayerType::BackGround);			// BackGround 객체 생성
		bg->GetComponent<Transform>()
			->SetPosition(math::Vector2(0.0f, -80.0f));								// 위치값 설정
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();					// SpriteRenderer 추가
		bgsr->SetTexture(texture);													// BackGround 객체의 texture 설정
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));									// Scale 설정
		bgsr->SetAffectCamera(true);												// 카메라 영향 여부설정

		// FarmerGirl Example 객체
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
		Monster* npc1 =
			Object::Instantiate<Monster>(enums::eLayerType::Monster);		// Monster 객체 생성
		npc1->GetComponent<Transform>()
			->SetPosition(math::Vector2(-500.0f, 125.0f));					// 위치값 설정
		Animator* at = npc1->AddComponent<Animator>();						// Animator 추가
		at->SetScale(math::Vector2(2.0f, 2.0f));							// Scale 설정
		at->CreateAnimationFolder(L"Tied_Skul_NPC"
			, L"..\\MyResources\\skul\\1_NPC\\Tied_Skul");					// ?
		at->PlayAnimation(L"Tied_Skul_NPC", true);							// ?
		at->SetAffectedCamera(true);										// 카메라 영향 여부설정

		// Cat_idle
		// \MyResources\skul\1_NPC\Cat_Green\Idle
		Monster* cat = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		cat->GetComponent<Transform>()->SetPosition(math::Vector2(-200.0f, 160.0f));
		at = cat->AddComponent<Animator>();
		at->SetScale(math::Vector2(1.5f, 1.5f));
		at->CreateAnimationFolder(L"Cat_idle"
			, L"..\\MyResources\\skul\\1_NPC\\Cat_Green\\Idle"); 
		at->PlayAnimation(L"Cat_idle", true);
		at->SetAffectedCamera(true);

		// 3) Player 객체
		// \MyResources\skul\11_Skul
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(0, 0));;
		at = player->AddComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		math::Vector2 offset = math::Vector2(0.0f, 70.0f);
		at->CreateAnimationFolder(L"Skul_Walk_Left", L"..\\MyResources\\skul\\11_Skul\\Walk_L", offset);
		at->CreateAnimationFolder(L"Skul_Walk_Right", L"..\\MyResources\\skul\\11_Skul\\Walk_R", offset);
		at->CreateAnimationFolder(L"Idle_Left", L"..\\MyResources\\skul\\11_Skul\\Idle_L", offset);
		at->CreateAnimationFolder(L"Idle_Right", L"..\\MyResources\\skul\\11_Skul\\Idle_R", offset);
		at->PlayAnimation(L"Idle_Left", true);
		at->SetAffectedCamera(true);

		SetTarget(player);
		Camera::SetTarget(GetTarget());
	}

	void HomeScene::Update()
	{
		Camera::SetTarget(GetTarget());
		Scene::Update();
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}