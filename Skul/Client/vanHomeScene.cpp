#include "vanHomeScene.h"
#include "vanTiedSkul.h"
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
#include "vanRigidBody.h"

#include "vanFloor.h"

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
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, -80.0f));			// 위치값 설정
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_1"));						// BackGround 객체의 texture 설정
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale 설정
		bgsr->SetAffectCamera(true);														// 카메라 영향 여부설정
		
		// 2) Tied_Skul_NPC
		TiedSkul* tiedSkul = Object::Instantiate<TiedSkul>(enums::eLayerType::Monster);		
		Animator* at = tiedSkul->GetComponent<Animator>();
		tiedSkul->GetComponent<Transform>()->SetPosition(math::Vector2(-500.0f, 125.0f));
		tiedSkul->MakeAnimation();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Tied_Skul_NPC", true);
		at->SetAffectedCamera(true);

		// 3) Player 객체
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(0, 140));
		player->MakeAnimation();
		at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Idle_Weapon_R", true);
		at->SetAffectedCamera(true);

		// 4) Floor 객체 
		Floor* floor = Object::Instantiate<Floor>(eLayerType::Floor);
		Collider* col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(1500.0f, 50.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 200.0f));

		// Player 레이어와 Monster 레이어의 충돌 체크여부(true) 설정
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);

		SetSceneTarget(player);
		Camera::SetTarget(GetSceneTarget());
	}

	void HomeScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
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