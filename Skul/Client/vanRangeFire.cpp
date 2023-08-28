#include "vanRangeFire.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanBoss.h"
#include "vanTransform.h"
#include "vanCollisionManager.h"

#define DAMAGE			10.0f

namespace van
{
	RangeFire::RangeFire()
	{
		AddComponent<SpriteRenderer>();
	}

	RangeFire::~RangeFire()
	{
		// nothing
	}

	void RangeFire::Init()
	{
		Skill::Init();
		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(110.0f, 110.0f));

		mState = RangeFireState::Gen;
	}

	void RangeFire::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case RangeFireState::Gen:
			Gen();
			break;
		case RangeFireState::Active:
			Active();
			break;
		case RangeFireState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void RangeFire::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void RangeFire::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Mage_RangeFire", ResourceManager::Find<Texture>(L"Mage_RangeFire"), math::Vector2(0.0f, 0.0f), math::Vector2(200.0f, 200.0f), 24, math::Vector2::Zero, 0.02);
	}

	void RangeFire::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)
		{
			// 플레이어에게 데미지를 준다 or 플레이어에게 맞았음을 알려준다.
			player->LoseHp(DAMAGE);
			player->SetPlayerState(Player::PlayerState::Hit);
		}
	}

	void RangeFire::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void RangeFire::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void RangeFire::Gen()
	{
		SetRangeFirePos();

		//  공격범위 알려준다.
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Mage_RangeFire_Sign"));
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_RangeFire, eLayerType::Player, false);

		mState = RangeFireState::Active;
	}

	void RangeFire::Active()
	{
		Animator* at = GetComponent<Animator>();

		if (mbPlayAnimation == true)
		{
			mDelay += Time::GetDeltaTime();
		}

		// 애니메이션 재생
		if (mbPlayAnimation == true
			&& mDelay >= 0.3f)
		{
			mDelay = 0.0f;
			mbPlayAnimation = false;
			CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_RangeFire, eLayerType::Player, true);
			at->PlayAnimation(L"Mage_RangeFire", false);
		}

		// 애니메이션 재생 완료시 Dead
		if (at->IsActiveAnimationComplete())
		{
			CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_RangeFire, eLayerType::Player, false);
			mbPlayAnimation = true;
			mState = RangeFireState::Dead;
		}
	}

	void RangeFire::Dead()
	{
		// 객체 소멸
		Destroy(this);
	}

	void RangeFire::SetRangeFirePos()
	{
		Boss* owner = dynamic_cast<Boss*>(GetOwner());	// RangeFire 스킬을 소유한 몬스터

		Transform* tr = GetComponent<Transform>();		
		Transform* tr_target = owner->GetTarget()->GetComponent<Transform>();
		math::Vector2 pos_target = tr_target->GetPosition();	// 타겟의 위치

		tr->SetPosition(pos_target);
	}

}
