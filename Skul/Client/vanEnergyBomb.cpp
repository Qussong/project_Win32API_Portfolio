#include "vanEnergyBomb.h"
#include "vanCollider.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanPlayer.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanWall.h"
#include "vanBoss.h"
#include "vanTransform.h"
#include "vanYggdrasill.h"
#include "vanYggdrasillHead.h"
#include "vanMagicOrbEffect.h"
#include "vanObject.h"

#define OBJECT_SPEED	400.0f
#define DAMAGE			20.0f

namespace van
{
	EnergyBomb::EnergyBomb()
	{
		// nothing
	}

	EnergyBomb::~EnergyBomb()
	{
		// nothing
	}

	void EnergyBomb::Init()
	{
		Skill::Init();
		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(150.0f, 150.0f));

		mState = EnergyBombState::Gen;

		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBomb, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBomb, eLayerType::FrontFloor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Skill_EnergyBomb, eLayerType::Wall, true);
	}

	void EnergyBomb::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case EnergyBombState::Gen:
			Gen();
			break;
		case EnergyBombState::Active:
			Active();
			break;
		case EnergyBombState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void EnergyBomb::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void EnergyBomb::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Yggdrasill_EnergyBomb_Object", ResourceManager::Find<Texture>(L"Yggdrasill_EnergyBomb_Object"), math::Vector2(0.0f, 0.0f), math::Vector2(107.0f, 108.0f), 14);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void EnergyBomb::OnCollisionEnter(Collider* _other)
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
			//mState = EnergyBombState::Dead;
		}

		if (floor != nullptr || wall != nullptr)
		{
			if (floor != nullptr)
			{
				MagicOrbEffect* effect = Object::Instantiate<MagicOrbEffect>(enums::eLayerType::Yggdrasill_Effect);
				effect->SetOwner(this);
			}

			mState = EnergyBombState::Dead;
		}
	}

	void EnergyBomb::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void EnergyBomb::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void EnergyBomb::Gen()
	{
		Animator* at = GetComponent<Animator>();
		GameObject* owner = GetOwner();

		at->PlayAnimation(L"Yggdrasill_EnergyBomb_Object", true);

		mState = EnergyBombState::Active;
	}

	void EnergyBomb::Active()
	{
		SetEnergyBombPos();
	}

	void EnergyBomb::Dead()
	{
		// EnergyBomb 객체 소멸
		Destroy(this);
	}

	void EnergyBomb::SetEnergyBombPos()
	{
		YggdrasillHead* owner = dynamic_cast<YggdrasillHead*>(GetOwner());
		if (owner == nullptr)
		{
			int a = 0;
		}
		else
		{
			Yggdrasill* ownerParent = (Yggdrasill*)(owner->GetOwner());
			Transform* tr = GetComponent<Transform>();
			Transform* tr_owner = owner->GetComponent<Transform>();
			Transform* tr_target = ownerParent->GetTarget()->GetComponent<Transform>();

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