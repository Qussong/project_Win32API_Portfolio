#include "vanCarleonRecruit.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanAnimator.h"

#include "vanRigidBody.h"
#include "vanCollider.h"

#include "vanTime.h"
#include "vanTransform.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"

#define WALK_SPEED		150.0f
#define HIT_BUMP_X		50.0f
#define HIT_BUMP_Y		-300.0f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mHitDirection(MonsterDirection::None)
		, mTimer(0.0f)
		, mbPatrol(false)
		, mbPlayAnimation(true)
		, mbHit(false)
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
		GetComponent<RigidBody>()->SetMass(10.0f);
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
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);

		// 충돌한 객체가 Attack 클래스인 경우
		if (attack != nullptr)
		{
			std::set<GameObject*>* list = attack->GetAttackList();
			if (list->find(this) == list->end())
			{
				mbHit = true;
				UINT state = attack->GetOwnerState();
				Player::PlayerDirection playerDirection = (Player::PlayerDirection)(attack->GetOwnerDirection());

				// 공격받은 방향 저장
				if (playerDirection == Player::PlayerDirection::Left)
				{
					// Player의 공격시 방향이 Left 라면
					// Monster 입장에서 Right에서 공격받은거임
					mHitDirection = MonsterDirection::Right;
					mDirection = MonsterDirection::Right;
				}
				else
				{
					mHitDirection = MonsterDirection::Left;
					mDirection = MonsterDirection::Left;
				}

				// Hit 판정
				if (state == (UINT)Player::PlayerState::AttackA
					|| state == (UINT)Player::PlayerState::AttackB
					|| state == (UINT)Player::PlayerState::JumpAttack)
				{
					mState = MonsterState::Hit;
				}

				// 공격판정 범위에 충돌한 충돌체 저장
				list->insert(this);
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
				if (mbHit)
				{
					// Hit 당한 상태에선 Patrol 상태로 넘어갈 때 한번 방향을 바꾸지 않음
					mbHit = false;
				}
				else
				{
					if (mDirection == MonsterDirection::Left)
					{
						mDirection = MonsterDirection::Right;
					}
					else
					{
						mDirection = MonsterDirection::Left;
					}
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
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		if (mHitDirection == MonsterDirection::Left)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_L", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 왼쪽에서 맞았기에 오른쪽으로 날아가야한다.
			velocity.x = HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);
		}
		if (mHitDirection == MonsterDirection::Right)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_R", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 오른쪽에서 맞았기에 왼쪽으로 날아가야한다.
			velocity.x = -HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);
		}

		mHitDirection = MonsterDirection::None;

		// 공격받은 후 땅에 닿으면 Idle 상태
		if (rb->GetGround() == true)
		{
			mState = MonsterState::Idle;
			if (mDirection == MonsterDirection::Left)
			{
				at->PlayAnimation(L"Idle_L", true);
			}
			if (mDirection == MonsterDirection::Right)
			{
				at->PlayAnimation(L"Idle_R", true);
			}
		}
	}
}