#include "vanGold.h"
#include "vanSpriteRenderer.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanRigidBody.h"
#include "vanPlayer.h"
#include "vanCollisionManager.h"

namespace van
{
	Gold::Gold()
		: mState(GoldState::None)
		, mPastState(GoldState::None)
		, mbPlayAnimation(true)
	{
		AddComponent<RigidBody>()->SetGround(false);
	}

	Gold::~Gold()
	{
		// nothing
	}

	void Gold::Init()
	{
		GameObject::Init();

		MakeAnimation();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Gold"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(true);

		SetGoldState(GoldState::Gen);
		GetComponent<Collider>()->SetSize(math::Vector2(20, 20));
	}

	void Gold::Update()
	{
		GameObject::Update();

		// Animation 재생여부 판정_1
		SetGoldPastState(GetGoldState());			// 현재 몬스터의 상태를 저장

		switch (GetGoldState())
		{
		case GoldState::Gen:
			Gen();
			break;
		case GoldState::Idle:
			Idle();
			break;
		case GoldState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		// Animation 재생여부 판정_2
		// 만약 몬스터의 상태,방향이 바꼈다면
		if (GetGoldState() != GetGoldPastState())
		{
			SetPlayAnimation(true);
		}
	}

	void Gold::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Gold::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->CreateAnimation(L"Gold_Idle", ResourceManager::Find<Texture>(L"Gold_Idle"), math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 30.0f), 9);
		at->CreateAnimation(L"Gold_Dead", ResourceManager::Find<Texture>(L"Gold_Dead"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 54.0f), 29, math::Vector2::Zero, 0.02F);
	}

	void Gold::OnCollisionEnter(Collider* _other)
	{
		// Player와 충돌했을 때 사라짐
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)
		{
			// Player 골드 획득
			player->AddCoin(100.0f);
			// 골드 객체 삭제
			SetGoldState(GoldState::Dead);
			SetPlayAnimation(true);
		}

	}

	void Gold::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Gold::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Gold::Gen()
	{
		// 튀어 올랐다가 땅에 떨어질때까지의 상태
		RigidBody* rb = GetComponent<RigidBody>();
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		if (rb->GetGround() == true)
		{
			sr->SetTexture(ResourceManager::Find<Texture>(L"Gold_Disappear"));
			SetGoldState(GoldState::Idle);
		}
	}

	void Gold::Idle()
	{
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Drop, true);

		// 땅에 붙어있을때의 상태
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Gold_Idle", true);	
			SetPlayAnimation(false);
		}
	}

	void Gold::Dead()
	{
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Drop, false);

		// 유저와 충돌하였을 때의 상태
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->SetScale(math::Vector2(2.0f, 2.0f));
			at->PlayAnimation(L"Gold_Dead", false);
			SetPlayAnimation(false);
		}
		if (at->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}