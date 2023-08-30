#include "vanWorldOnFireOrb.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanWorldOnFireGen.h"
#include "vanObject.h"
#include "vanBoss.h"
#include "vanWorldOnFireFireBall.h"
#include "vanTransform.h"

#define FIREBALL_MAX_CNT	3

namespace van
{
	WorldOnFireOrb::WorldOnFireOrb()
	{
		// nothing
	}

	WorldOnFireOrb::~WorldOnFireOrb()
	{
		// nothing
	}

	void WorldOnFireOrb::Init()
	{
		Skill::Init();
		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(120.0f, 120.0f));

		mState = OrbState::Gen;
	}

	void WorldOnFireOrb::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case OrbState::Gen:
			Gen();
			break;
		case OrbState::Active:
			Active();
			break;
		case OrbState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void WorldOnFireOrb::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void WorldOnFireOrb::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"WorldOnFire_Orb_Object", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_Orb_Object"), math::Vector2(0.0f, 0.0f), math::Vector2(120.0f, 122.0f), 50);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void WorldOnFireOrb::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::Gen()
	{
		Animator* at = GetComponent<Animator>();
		GameObject* owner = GetOwner();

		if (owner != nullptr)
		{
			// GenEffect 애니메이션 출력
			WorldOnFireGen* effect = Object::Instantiate<WorldOnFireGen>(enums::eLayerType::Boss_Mage_Effect);
			effect->SetOwner(this);

			// Target 설정
			Boss* boss = dynamic_cast<Boss*>(owner);
			mTarget = boss->GetTarget();

			// Orb 애니메이션 출력
			at->PlayAnimation(L"WorldOnFire_Orb_Object", true);

			// Orb 상태 변경
			mState = OrbState::Active;
		}
	}

	void WorldOnFireOrb::Active()
	{
		Transform* tr = GetComponent<Transform>();

		// FireBall 딜레이
		if (mbShoot == false)
		{
			mShootDelay += Time::GetDeltaTime();

			if (mShootDelay >= 1.5f)
			{
				mShootDelay = 0.0f;
				mbShoot = true;
			}
		}

		// FireBall 생성
		if (mFireBallCnt < FIREBALL_MAX_CNT
			&& mbShoot == true)
		{
			WorldOnFireFireBall* fireBall = Object::Instantiate<WorldOnFireFireBall>(enums::eLayerType::Boss_Mage_Skill_FireBall);
			fireBall->SetOwner(this);
			fireBall->GetComponent<Transform>()->SetPosition(tr->GetPosition());

			++mFireBallCnt;
			mbShoot = false;
		}

		// FireBall 종료조건
		// FireBall 이 전부 소멸했는지 확인
		if (mFireBallCnt == FIREBALL_MAX_CNT
			&& mFireBallDeadCnt == FIREBALL_MAX_CNT)
		{
			mFireBallCnt = 0;
			mbShoot = true;
			mState = OrbState::Dead;
		}
	}

	void WorldOnFireOrb::Dead()
	{
		// EnergyBomb 객체 소멸
		Destroy(this);
	}
}