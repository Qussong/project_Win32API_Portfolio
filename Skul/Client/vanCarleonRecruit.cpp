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

#include "vanMonsterTrace.h"
#include "vanObject.h"

#define WALK_SPEED		150.0f
#define HIT_BUMP_X		50.0f
#define HIT_BUMP_Y		-300.0f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mTimer(0.0f)
		, mbPlayAnimation(true)
		, traceBox(nullptr)
	{
		AddComponent<RigidBody>();
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		MakeAnimation();	// 애니메이션 생성

		// Monaster 초기설정
		SetMonsterDirection(MonsterDirection::Left);	// 방향
		SetMonsterState(MonsterState::Idle);			// 상태

		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));	// 충돌체 크기 설정
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정

		// MonsterTrace 클래스 값 설정 (변수명 : traceBox)
		traceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Trace);	// 객체생성
		traceBox->SetOwner(this);														// 소유자 설정
		traceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 110.0f));		// traceBox 충돌체의 크기 설정
	}

	void CarleonRecruit::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		// TraceBox 값세팅
		traceBox->SetOwnerPos(pos);
		traceBox->SetOwnerState((UINT)GetMonsterState());
		traceBox->SetOwnerDirection((UINT)GetMonsterDirection());
		traceBox->SetOffset(math::Vector2::Zero);

		switch (GetMonsterState())
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
		case CarleonRecruit::MonsterState::Trace:
			Trace();
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
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);	// 충돌한 객체가 Attack 클래스인지 확인

		// 충돌한 객체가 PlayerAttack 클래스인 경우 = 피격(Hit)판정
		if (attack != nullptr)
		{
			// PlayerAttack 클래스의 충돌체 저장 정보를 가져온다
			std::set<GameObject*>* list = attack->GetAttackList();
			
			// 해당 클래스의 정보가 충돌체 저장 list에 존재하지 않는다면 Hit 판정
			if (list->find(this) == list->end())
			{
				SetHitFlag(true);
				UINT state = attack->GetOwnerState();
				Player::PlayerDirection playerDirection = (Player::PlayerDirection)(attack->GetOwnerDirection());

				// 공격받은 방향 저장
				if (playerDirection == Player::PlayerDirection::Left)
				{
					// Player의 공격시 방향이 Left 라면
					// Monster 입장에서 Right에서 공격받은거임
					SetMonsterHitDirection(MonsterDirection::Right);
					SetMonsterDirection(MonsterDirection::Right);
				}
				else
				{
					SetMonsterHitDirection(MonsterDirection::Left);
					SetMonsterDirection(MonsterDirection::Left);
				}

				// Hit 판정
				if (state == (UINT)Player::PlayerState::AttackA
					|| state == (UINT)Player::PlayerState::AttackB
					|| state == (UINT)Player::PlayerState::JumpAttack)
				{
					SetMonsterState(MonsterState::Hit);
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

		if (GetPatroFlag())
		{
			mTimer += Time::GetDeltaTime();

			if (mTimer >= 3.0f)
			{
				mTimer = 0.0f;
				SetMonsterState(MonsterState::Walk);
				mbPlayAnimation = true;
				if (GetHitFlag())
				{
					// Hit 당한 상태에선 Patrol 상태로 넘어갈 때 한번 방향을 바꾸지 않음
					SetHitFlag(false);
				}
				else
				{
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						SetMonsterDirection(MonsterDirection::Right);
					}
					else
					{
						SetMonsterDirection(MonsterDirection::Left);
					}
				}
				return;
			}
		}

		if (GetMonsterDirection() == MonsterDirection::Left)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Idle_L", true);
				mbPlayAnimation = false;
			}
		}
		else
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

		if (GetPatroFlag())
		{
			mTimer += Time::GetDeltaTime();
			if (mTimer >= 2.0f)
			{
				mTimer = 0.0f;
				SetMonsterState(MonsterState::Idle);
				mbPlayAnimation = true;

				return;
			}
		}

		// Walk_L
		if (GetMonsterDirection() == MonsterDirection::Left)
		{
			// Patrol 상태일때
			if (GetPatroFlag() && mbPlayAnimation == true)
			{
				at->PlayAnimation(L"Walk_L", true);
				mbPlayAnimation = false;
			}

			pos.x -= (WALK_SPEED * Time::GetDeltaTime());
			tr->SetPosition(pos);
		}

		// Walk_R
		if (GetMonsterDirection() == MonsterDirection::Right)
		{
			// Patrol 상태일때
			if (GetPatroFlag() && mbPlayAnimation == true)
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
		SetPatroFlag(true);
		SetMonsterState(MonsterState::Walk);
	}

	void CarleonRecruit::Trace()
	{
		// Trace 로직 구현
		SetPatroFlag(false);
		SetMonsterState(MonsterState::Walk);
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

		if (GetMonsterHitDirection() == MonsterDirection::Left)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_L", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 왼쪽에서 맞았기에 오른쪽으로 날아가야한다.
			velocity.x = HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);
		}
		if (GetMonsterHitDirection() == MonsterDirection::Right)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_R", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 오른쪽에서 맞았기에 왼쪽으로 날아가야한다.
			velocity.x = -HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);
		}

		SetMonsterHitDirection(MonsterDirection::None);

		// 공격받은 후 땅에 닿으면 Idle 상태
		if (rb->GetGround() == true)
		{
			SetMonsterState(MonsterState::Idle);
			if (GetMonsterDirection() == MonsterDirection::Left)
			{
				at->PlayAnimation(L"Idle_L", true);
			}
			if (GetMonsterDirection() == MonsterDirection::Right)
			{
				at->PlayAnimation(L"Idle_R", true);
			}
		}
	}
}