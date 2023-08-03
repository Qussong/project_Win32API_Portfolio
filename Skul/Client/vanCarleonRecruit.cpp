#include "vanCarleonRecruit.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanAnimator.h"

#include "vanRigidBody.h"
#include "vanCollider.h"

#include "vanTime.h"
#include "vanTransform.h"
#include "vanAttack.h"
#include "vanPlayer.h"

#define WALK_SPEED		150.0f

namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mTimer(0.0f)
		, mbPatrol(false)
		, mbPlayAnimation(true)
	{
		AddComponent<RigidBody>();
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		MakeAnimation();
		mDirection = MonsterDirection::Left;
		mState = MonsterState::Patrol;
		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));
	}

	void CarleonRecruit::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case CarleonRecruit::MonsterState::Idle:
			Idle();
			break;
		case CarleonRecruit::MonsterState::Walk:
			Walk();
			break;
		case CarleonRecruit::MonsterState::Patrol:
			Patrol();
			break;
		case CarleonRecruit::MonsterState::AttackReady:
			Attack();
			break;
		case CarleonRecruit::MonsterState::Attack:
			Attack();
			break;
		case CarleonRecruit::MonsterState::Hit:
			Hit();
			break;
		default:
			__noop;
		}
	}

	void CarleonRecruit::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void CarleonRecruit::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));

		animator->CreateAnimation(L"CarleonRecruit_Hit_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Hit_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Dead_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		animator->CreateAnimation(L"CarleonRecruit_Dead_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);

	}

	void CarleonRecruit::OnCollisionEnter(Collider* _other)
	{

	}

	void CarleonRecruit::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		van::Attack* attack = dynamic_cast<van::Attack*>(obj);

		if (attack != nullptr)
		{
			UINT state = attack->GetOwnerState();
			if (state == (UINT)Player::PlayerState::AttackA
				|| state == (UINT)Player::PlayerState::AttackB)
			{
				mState = MonsterState::Hit;
			}
		}
	}

	void CarleonRecruit::OnCollisionExit(Collider* _other)
	{

	}

	void CarleonRecruit::Idle()
	{
		Animator* at = GetComponent<Animator>();

		if (mbPatrol)
		{
			mTimer += Time::GetDeltaTime();
			if (mTimer >= 3.0f)
			{
				mTimer = 0.0f;
				mState = MonsterState::Walk;
				mbPlayAnimation = true;
				if (mDirection == MonsterDirection::Left)
				{
					mDirection = MonsterDirection::Right;
				}
				else
				{
					mDirection = MonsterDirection::Left;
				}

				return;
			}
		}

		if (mDirection == MonsterDirection::Left)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Idle_L", true);
				mbPlayAnimation = false;
			}
		}

		if (mDirection == MonsterDirection::Right)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Idle_R", true);
				mbPlayAnimation = false;
			}
		}
	}

	void CarleonRecruit::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		if (mbPatrol)
		{
			mTimer += Time::GetDeltaTime();
			if (mTimer >= 2.0f)
			{
				mTimer = 0.0f;
				mState = MonsterState::Idle;
				mbPlayAnimation = true;

				return;
			}
		}

		// Walk_L
		if (mDirection == MonsterDirection::Left)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Walk_L", true);
				mbPlayAnimation = false;
			}
			pos.x -= (WALK_SPEED * Time::GetDeltaTime());
			tr->SetPosition(pos);
		}

		// Walk_R
		if (mDirection == MonsterDirection::Right)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Walk_R", true);
				mbPlayAnimation = false;
			}
			pos.x += (WALK_SPEED * Time::GetDeltaTime());
			tr->SetPosition(pos);
		}
	}

	void CarleonRecruit::Patrol()
	{
		mbPatrol = true;
		mState = MonsterState::Walk;
	}

	void CarleonRecruit::AttackReady()
	{

	}

	void CarleonRecruit::Attack()
	{

	}

	void CarleonRecruit::Hit()
	{
		Animator* at = GetComponent<Animator>();

		if (mDirection == MonsterDirection::Left)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_L", false);
		}
		if (mDirection == MonsterDirection::Right)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_R", false);
		}
	}
}