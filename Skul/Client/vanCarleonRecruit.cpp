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
#include "vanMonsterAttack.h"
#include "vanGold.h"

#define DASH_FORCE_X		900.0f
#define DASH_DISTANCE_X		50.0f
#define ATTACK_READY_DELAY	0.6f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
	{
		// nothing
	}

	CarleonRecruit::~CarleonRecruit()
	{
		// nothing
	}

	void CarleonRecruit::Init()
	{
		Monster::Init();

		// 애니메이션 생성
		MakeAnimation();

		// Monster 초기설정
		SetMonsterState(MonsterState::Gen);									// 상태
		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));	// 충돌체 크기 설정
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// 이미지 스케일 설정

		// traceBox의 초기값 설정
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwner(this);
		traceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 110.0f));
		traceBox->SetOffset(math::Vector2::Zero);

		// attackBox의 초기값 설정
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 110.0f));	// 사정거리 40
		attackBox->SetOffset(math::Vector2(20.0f, 0.0f));
	}

	void CarleonRecruit::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// traceBox 값세팅
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwnerPos(pos);
		traceBox->SetOwnerState((UINT)GetMonsterState());
		traceBox->SetOwnerDirection((UINT)GetMonsterDirection());
		// attackBox 값세팅
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		Monster::Update();
	}

	void CarleonRecruit::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void CarleonRecruit::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(34.0f, 57.0f), 6);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 50.0f), 8, math::Vector2(0.0f, 5.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(38.0f, 67.0f), 1, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(58.0f, 67.0f), 5, math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Hit_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"Hit_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 51.0f), 1);
		animator->CreateAnimation(L"Dead_L", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		animator->CreateAnimation(L"Dead_R", ResourceManager::Find<Texture>(L"CarleonRecruit_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 47.0f), 1);
		
	}

	void CarleonRecruit::OnCollisionEnter(Collider* _other)
	{
		Monster::OnCollisionEnter(_other);
	}

	void CarleonRecruit::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void CarleonRecruit::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void CarleonRecruit::Gen()
	{
		Monster::Gen();
	}

	void CarleonRecruit::Idle()
	{
		Monster::Idle();
	}

	void CarleonRecruit::Walk()
	{
		Monster::Walk();
	}

	void CarleonRecruit::Patrol()
	{
		Monster::Patrol();
	}

	void CarleonRecruit::Trace()
	{
		Monster::Trace();
	}

	void CarleonRecruit::AttackReady()
	{
		// Attack 상태로 전환됐기에 Patrol, Trace Flag는 꺼준다.
		SetPatrolFlag(false);
		SetTraceFlag(false);

		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();

		// Attack Ready 애니메이션 재생
		if (GetPlayAnimation() == true)
		{
			// Monster의 방향이 Left인 경우
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_Ready_L", false);
			}
			// Monster의 방향이 Right인 경우
			else
			{
				ani->PlayAnimation(L"Attack_Ready_R", false);
			}
			SetPlayAnimation(false);
		}

		// 카운트 시작
		// 1) 카운트중에 피격되면 Timer 리셋
		// 2) AttackReadyFlag = false ( Hit()에서 수행 )
		AddTimer(Time::GetDeltaTime());

		// 카운트 완료시 
		// 1) Attack Ready를 완료했음
		// 2) Attack 상태로 넘어간다
		// 3) Timer 리셋
		// 4) Attack Dash 시작지점 저장
		if (GetTimer() >= ATTACK_READY_DELAY)
		{
			attackBox->SetAttackReadyFlag(true);
			SetTimer(0.0f);
			mAttackDashX1 = pos.x;	// Attack Dash 시 시작위치
			SetMonsterState(Monster::MonsterState::Attack);
		}
	}

	void CarleonRecruit::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();
		std::set<GameObject*>* list = attackBox->GetMonsterAttackList();
		bool moveComplete = false;

		// Attack시 이동
		if (direction == MonsterDirection::Left)
		{
			velocity.x -= DASH_FORCE_X;
		}
		if (direction == MonsterDirection::Right)
		{
			velocity.x += DASH_FORCE_X;
		}
		rb->SetVelocity(velocity);

		// Attack Animation재생
		if (GetPlayAnimation() == true)
		{
			// Monster의 방향이 Left인 경우
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_L", false);
			}
			// Monster의 방향이 Right인 경우
			else
			{
				ani->PlayAnimation(L"Attack_R", false);
			}
			SetPlayAnimation(false);
		}

		// 일정거리 이동시 멈춤
		mAttackDashX2 = pos.x;									// Attack Dash 현재위치
		float distance = abs(mAttackDashX2 - mAttackDashX1);	// 공격수행으로 인한 이동거리
		if (distance >= DASH_DISTANCE_X)
		{
			rb->SetVelocity(math::Vector2(0.0f, velocity.y));	// x방향 속도 0으로 만들기
			// 값 초기화
			mAttackDashX1 = 0.0f;
			mAttackDashX2 = 0.0f;
			moveComplete = true;
		}

		// 공격 완료
		// 조건 : Animation 재생이 완료 && 일정거리 이동 완료 || 벽과의 충돌
		// 1) AttackReadyFlag = false
		// 2) AttacList 초기화
		// 3) Attack Flag false 전환
		// 4) Trace Flag true 전환, Trace 상태로 전환
		if (ani->IsActiveAnimationComplete() == true
			&& moveComplete == true)
		{
			// 공격을 수행했기에 다시 Attack Ready를 해줘야한다.
			attackBox->SetAttackReadyFlag(false);
			// 동일 대상에대한 공격이 가능하도록해준다.
			list->clear();
			// Attack 을 수행했기에 mbAttack 을 false로 변경
			SetAttackFlag(false);
			// Trace 상태가 될 수 있도록 대상 풀어준다.
			SetMonsterTarget(nullptr);
			// Attack End 상태 만들기
			SetMonsterState(MonsterState::AttackEnd);
		}
	}

	void CarleonRecruit::AttackEnd()
	{
		Monster::AttackEnd();
	}

	void CarleonRecruit::Hit()
	{
		Monster::Hit();
	} 

	void CarleonRecruit::Dead()
	{
		Monster::Dead();
	}
}