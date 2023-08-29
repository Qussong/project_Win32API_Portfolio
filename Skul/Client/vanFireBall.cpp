#include "vanFireBall.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanWall.h"
#include "vanFloor.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanBoss.h"
#include "vanCollisionManager.h"
#include "vanMage.h"

#define OBJECT_SPEED	400.0f
#define DAMAGE			15.0f

namespace van
{
	FireBall::FireBall()
	{
		// nothing
	}

	FireBall::~FireBall()
	{
		// nothing
	}

	void FireBall::Init()
	{
		Skill::Init();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(25.0f, 25.0f));

		mState = FireBallState::Gen;

		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage_Skill_FireBall, eLayerType::Wall, true);
	}

	void FireBall::Update()
	{
		Skill::Update();

		MakeAnimation();

		switch (mState)
		{
		case FireBallState::Gen:
			Gen();
			break;
		case FireBallState::Active:
			Active();
			break;
		case FireBallState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

	}

	void FireBall::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void FireBall::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Mage_FireBall_Object_L", ResourceManager::Find<Texture>(L"Mage_FireBall_Object_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 28.0f), 12);
		at->CreateAnimation(L"Mage_FireBall_Object_R", ResourceManager::Find<Texture>(L"Mage_FireBall_Object_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 28.0f), 12);
		at->SetScale(math::Vector2(1.5f, 1.5f));
	}

	void FireBall::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Player* player = dynamic_cast<Player*>(obj);
		Floor* floor = dynamic_cast<Floor*>(obj);
		Wall* wall = dynamic_cast<Wall*>(obj);

		if (player != nullptr)
		{
			if (player->GetPlayerState() != Player::PlayerState::Dash
				&& player->GetPlayerState() != Player::PlayerState::DoubleDash)
			{
				// 플레이어에게 데미지를 준다 or 플레이어에게 맞았음을 알려준다.
				player->LoseHp(DAMAGE);
				player->SetPlayerState(Player::PlayerState::Hit);
			}
			// FireBall객체 소멸
			mState = FireBallState::Dead;
		}

		if (floor != nullptr || wall != nullptr)
		{
			mState = FireBallState::Dead;
		}
	}

	void FireBall::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void FireBall::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void FireBall::Gen()
	{
		Animator* at = GetComponent<Animator>();
		GameObject* owner = GetOwner();
		Mage* mage = dynamic_cast<Mage*>(owner);

		if (mage->GetBossAttackDirection() == Mage::BossDirection::Left)
		{
			at->PlayAnimation(L"Mage_FireBall_Object_L", true);
		}
		else
		{
			at->PlayAnimation(L"Mage_FireBall_Object_R", true);
		}

		mState = FireBallState::Active;
	}

	void FireBall::Active()
	{
		SetFireBallMove();
		// nothing
	}

	void FireBall::Dead()
	{
		// FireBall객체 소멸
		Destroy(this);
	}

	void FireBall::SetFireBallMove()
	{
		Boss* owner = dynamic_cast<Boss*>(GetOwner());
		if (owner != nullptr)
		{
			Transform* tr = GetComponent<Transform>();
			Transform* tr_owner = owner->GetComponent<Transform>();
			Transform* tr_target = owner->GetTarget()->GetComponent<Transform>();

			math::Vector2 pos = tr->GetPosition();

			if (mbSetFlag == true)
			{
				mDepartPos = tr_owner->GetPosition();				// 발사지점
				mTargetPos = tr_target->GetPosition();				// 도착지점
				mDirect = (mTargetPos - mDepartPos).Normalize();	// 방향벡터

				mbSetFlag = false;
			}

			pos.x += mDirect.x * OBJECT_SPEED * Time::GetDeltaTime();
			pos.y += mDirect.y * OBJECT_SPEED * Time::GetDeltaTime();

			tr->SetPosition(pos);
		}
	}
}