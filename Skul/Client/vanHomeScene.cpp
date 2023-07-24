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

#include "vanCollider.h"
#include "vanCollisionManager.h"


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
		
		// 2) Tied_Skul_NPC
		Monster* npc1 =
			Object::Instantiate<Monster>(enums::eLayerType::Monster);		// Monster 객체 생성
		npc1->GetComponent<Transform>()
			->SetPosition(math::Vector2(-500.0f, 125.0f));					// 위치값 설정
		Animator* at = npc1->GetComponent<Animator>();						// Animator 추가
		at->SetScale(math::Vector2(2.0f, 2.0f));							// Scale 설정
		at->CreateAnimationFolder(L"Tied_Skul_NPC"
			, L"..\\MyResources\\skul\\1_NPC\\Tied_Skul");					
		at->PlayAnimation(L"Tied_Skul_NPC", true);							
		at->SetAffectedCamera(true);										// 카메라 영향 여부설정

		Collider* col = npc1->AddComponent<Collider>();
		col->SetSize(math::Vector2(50.0f, 70.0f));
		col->SetOffset(math::Vector2(0.0f, 0.0f));

		// 3) Player 객체
		math::Vector2 offset = math::Vector2(0.0f, 70.0f);
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player, offset);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(0, 0));;
		at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Idle_Weapon_R", true);
		at->SetAffectedCamera(true);
		
		col = player->AddComponent<Collider>();
		col->SetSize(math::Vector2(50.0f, 70.0f));
		col->SetOffset(math::Vector2(0.0f, 140.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);	// Player 레이어와 Monster 레이어의 충돌 체크여부(true) 설정
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