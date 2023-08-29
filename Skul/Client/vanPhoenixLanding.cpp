#include "vanPhoenixLanding.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"
#include "vanMage.h"
#include "vanTransform.h"
#include "vanCollider.h"

#define DAMAGE			30.0f

namespace van
{
	PhoenixLanding::PhoenixLanding()
	{
		// nothing
	}

	PhoenixLanding::~PhoenixLanding()
	{
		// nothing
	}

	void PhoenixLanding::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = PhoenixLandingState::Gen;
	}

	void PhoenixLanding::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case PhoenixLandingState::Gen:
			Gen();
			break;
		case PhoenixLandingState::Active:
			Active();
			break;
		case PhoenixLandingState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void PhoenixLanding::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void PhoenixLanding::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		
		at->CreateAnimation(L"Attack_Effect_PhoenixLanding", ResourceManager::Find<Texture>(L"Mage_PhoenixRanding_Land_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(149.0f, 135.0f), 41, math::Vector2(0.0f, 0.0f), 0.02F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void PhoenixLanding::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr
			&& player->GetPlayerState() != Player::PlayerState::Dash
			&& player->GetPlayerState() != Player::PlayerState::DoubleDash)
		{
			// 플레이어에게 데미지를 준다 or 플레이어에게 맞았음을 알려준다.
			player->LoseHp(DAMAGE);
			player->SetPlayerState(Player::PlayerState::Hit);
		}
	}

	void PhoenixLanding::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void PhoenixLanding::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void PhoenixLanding::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = PhoenixLandingState::Active;
		}
	}

	void PhoenixLanding::Active()
	{
		GameObject* owner = GetOwner();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Collider* col = GetComponent<Collider>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_PhoenixLanding, eLayerType::Player, true);

			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			col->SetSize(math::Vector2(300.0f, 135.0f / 2));
			col->SetOffset(math::Vector2(0.0f, 135.0f / 4));
			at->PlayAnimation(L"Attack_Effect_PhoenixLanding", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_PhoenixLanding, eLayerType::Player, false);
			dynamic_cast<Mage*>(owner)->SetPhoenixLandingEffectFlag(true);
			mbSetFlag = false;
			mbEffectFinish = true;
			mState = PhoenixLandingState::Dead;
		}
	}

	void PhoenixLanding::Dead()
	{
		// 객체 소멸
		Destroy(this);
	}

}