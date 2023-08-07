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

#define WALK_SPEED		150.0f
#define HIT_BUMP_X		50.0f
#define HIT_BUMP_Y		-300.0f
#define DASH_FORCE_X	700.0f
	
namespace van
{
	CarleonRecruit::CarleonRecruit()
		: mTimer(0.0f)
		, mTraceBox(nullptr)
		, mAttackBox(nullptr)
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

		// Monster 초기설정
		SetMonsterDirection(MonsterDirection::Left);	// 방향
		SetMonsterState(MonsterState::Patrol);			// 상태
		GetComponent<Collider>()->SetSize(math::Vector2(60.0f, 110.0f));	// 충돌체 크기 설정
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정

		// mTraaceBox의 초기값 설정
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);	// 객체생성
		mTraceBox->SetOwner(this);																// 소유자 설정
		mTraceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 110.0f));			// traceBox 충돌체의 크기 설정
		mTraceBox->SetOffset(math::Vector2::Zero);

		// mAttackBox의 초기값 설정
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
		mAttackBox->SetOwner(this);
		mAttackBox->GetComponent<Collider>()->SetSize(math::Vector2(50.0f, 110.0f));
		mAttackBox->SetOffset(math::Vector2(55.0f, 0.0f));
	}

	void CarleonRecruit::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		// mTraceBox 값세팅
		mTraceBox->SetOwnerPos(pos);
		mTraceBox->SetOwnerState((UINT)GetMonsterState());
		mTraceBox->SetOwnerDirection((UINT)GetMonsterDirection());

		// mAttackBox 값세팅
		mAttackBox->SetOwnerPos(pos);
		mAttackBox->SetOwnerState((UINT)GetMonsterState());
		mAttackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		SetMonsterPastState(GetMonsterState());	// 현재 몬스터의 상태를 저장
		SetMonsterPastDirection(GetMonsterDirection());	// 현재 몬스터의 방향을 저장

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
			AttackReady();
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

		// 만약 몬스터의 상태,방향이 바꼈다면
		if (GetMonsterState() != GetMonsterPastState()
			|| GetMonsterDirection() != GetMonsterPastDirection())
		{
			SetPlayAnimation(true);
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
		// nothing
	}

	void CarleonRecruit::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);	// 충돌한 객체가 Attack 클래스인지 확인

		// 충돌한 객체가 PlayerAttack 클래스인 경우 == 피격(Hit)판정
		if (attack != nullptr)
		{
			// PlayerAttack 클래스의 충돌체 저장 정보를 가져온다
			std::set<GameObject*>* list = attack->GetAttackList();
			
			// 해당 클래스의 정보가 충돌체 저장 list에 존재하지 않고 Attack상태가 아니면 Hit 판정
			if (list->find(this) == list->end() 
				&& GetMonsterState() != Monster::MonsterState::Attack)
			{
				//SetHitFlag(true);
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
					// Hit 판정을 받으면 Patrol 상태가 아니기에 Patrol Flag를 꺼준다.
					SetPatrolFlag(false);
				}

				// 공격판정 범위에 충돌한 충돌체 저장
				list->insert(this);
			}
		}
	}

	void CarleonRecruit::OnCollisionExit(Collider* _other)
	{
		 // nothing
	}

	void CarleonRecruit::Idle()
	{
		Animator* at = GetComponent<Animator>();

		// Patrol 상태일 때 
		if (GetPatrolFlag() == true)
		{
			// 시간 누적
			mTimer += Time::GetDeltaTime();

			// 누적된 시간이 3초 이상이되면
			if (mTimer >= 3.0f)				
			{
				mTimer = 0.0f;							// 누적시간 0초로 초기화
				SetMonsterState(MonsterState::Walk);	// Monster의 상태를 Walk 로 변경

				// 방향전환
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					SetMonsterDirection(MonsterDirection::Right);
				}
				else
				{
					SetMonsterDirection(MonsterDirection::Left);
				}
			}
			// 누적된 시간이 3초 이상이 아니라면
			else
			{
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Idle_L", true);
						SetPlayAnimation(false);
					}
				}
				else
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Idle_R", true);
						SetPlayAnimation(false);
					}
				}
			}
		}
		// Patrol 상태가 아닐때
		else
		{
			__noop;
		}
	}

	void CarleonRecruit::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		// Patrol 상태일 때 
		if (GetPatrolFlag() == true)
		{
			// 시간 누적
			mTimer += Time::GetDeltaTime();

			// 누적된 시간이 2초 이상이되면
			if (mTimer >= 2.0f)
			{
				mTimer = 0.0f;
				SetMonsterState(MonsterState::Idle);
			}
			// 누적된 시간이 2초 이상이 아니라면
			else
			{
				// Walk_L
				if (GetMonsterDirection() == MonsterDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Walk_L", true);
						SetPlayAnimation(false);
					}
					pos.x -= (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
				// Walk_R
				if (GetMonsterDirection() == MonsterDirection::Right)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Walk_R", true);
						SetPlayAnimation(false);
					}
					pos.x += (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
			}
		}
		// Trace 상태일 때
		else if(GetTraceFlag() == true)
		{
			// Monster 기준으로 Target의 위치탐색
			math::Vector2 targetPos = GetMonsterTarget()->GetComponent<Transform>()->GetPosition();	// Target의 위치
			math::Vector2 monsterPos = GetComponent<Transform>()->GetPosition();					// Monster의 위치
			// Target이 Monster의 Left에 있을 때
			if (targetPos.x < monsterPos.x)
			{
				// Monster의 이동 방향을 Left로 변경
				SetMonsterDirection(Monster::MonsterDirection::Left);
			}
			// Target이 Monster의 Right에 있을 때
			else
			{
				// Monster의 이동 방향을 Right로 변경
				SetMonsterDirection(Monster::MonsterDirection::Right);
			}

			// Walk_L
			if (GetMonsterDirection() == MonsterDirection::Left)
			{
				if (GetPlayAnimation() == true)
				{
					at->PlayAnimation(L"Walk_L", true);
					SetPlayAnimation(false);
				}
				pos.x -= (WALK_SPEED * Time::GetDeltaTime());
				tr->SetPosition(pos);
			}
			// Walk_R
			if (GetMonsterDirection() == MonsterDirection::Right)
			{
				if (GetPlayAnimation() == true)
				{
					at->PlayAnimation(L"Walk_R", true);
					SetPlayAnimation(false);
				}
				pos.x += (WALK_SPEED * Time::GetDeltaTime());
				tr->SetPosition(pos);
			}
		}
		// Attack 상태일 때
		else if (GetAttackFlag() == true)
		{
			SetMonsterState(MonsterState::AttackReady);
		}
		// Patrol, Trace, Attack 상태가 아닐때
		else
		{
			__noop;
		}
	}

	void CarleonRecruit::Patrol()
	{
		// 몬스터가 모든 상태에서 Patrol 행동을 보이도록 설정
		SetPatrolFlag(true);
		// Patrol 상태로 전환됐기에 Trace Flag는 꺼준다.
		SetTraceFlag(false);
		// Patrol시 Idle 부터 시작하도록 한다.
		SetMonsterState(MonsterState::Idle);
	}

	void CarleonRecruit::Trace()
	{
		// 몬스터가 모든 상태에서 Trace 행동을 보이도록 설정
		SetTraceFlag(true);
		// Trace 상태로 전환됐기에 Patrol Flag는 꺼준다.
		SetPatrolFlag(false);
		// Patrol 행동 패턴에 사용했던 Timer는 초기화해준다.
		mTimer = 0.0f;	

		// Trace시 Target을 쫓아가기에 Walk 부터 시작
		SetMonsterState(MonsterState::Walk);

		// Monster의 Attack 영역에 Player가 들어오지 않았을 경우
		//if (GetAttackFlag() == false)
		//{
		//	// Trace시 Target을 쫓아가기에 Walk 부터 시작
		//	SetMonsterState(MonsterState::Walk);
		//}
		//// Monster의 Attack 영역에 Player가 들어왔을 경우
		//else
		//{
		//	// Attack 수행하기에 Trace Flag 꺼준다.
		//	SetTraceFlag(false);
		//	// Attack Ready로 상태변경
		//	SetMonsterState(MonsterState::AttackReady);
		//}
	}

	void CarleonRecruit::AttackReady()
	{
		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();

		// Attack Ready 재생
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

		// Timer로 1~2초 카운트
		// 카운트중에 피격되면 Timer 리셋, AttackReadyFlag = false ( Hit()에서 수행 )
		mTimer += Time::GetDeltaTime();
		
		// 카운트 완료시 Attack 상태로 넘어간다, Timer 리셋
		if (mTimer >= 2.0f)
		{
			mTimer = 0.0f;
			SetMonsterState(Monster::MonsterState::Attack);
			mAttackDashX1 = pos.x;	// Attack Dash 시 시작위치
		}
	}

	void CarleonRecruit::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		std::set<GameObject*>* list = mAttackBox->GetMonsterAttackList();
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
		if (distance >= 30.0f)
		{
			rb->SetVelocity(math::Vector2(0.0f, velocity.y));	// x방향 속도 0으로 만들기
			// 값 초기화
			mAttackDashX1 = 0.0f;
			mAttackDashX2 = 0.0f;
			moveComplete = true;
		}


		// Animation 재생이 완료 && 일정거리 이동 완료시 
		// 1) AttackReadyFlag = false
		// 2) AttacList 초기화
		// 3) Attack Flag false 전환
		// 4) Trace Flag true 전환, Trace 상태로 전환
		if (ani->IsActiveAnimationComplete() == true
			&& moveComplete == true)
		{

			mAttackBox->SetAttackReadyFlag(false);

			list->clear();

			SetAttackFlag(false);

			//SetTraceFlag(true);
			//SetMonsterState(MonsterState::Trace);

			SetPatrolFlag(true);
			SetMonsterState(MonsterState::Patrol);
		}
	}

	void CarleonRecruit::Hit()
	{
		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// AttackReady중에 피격당하면 
		// 1) mTimer를 0.0f로 초기화 
		// 2) AttackReady수행여부를 false로 변경
		// 3) mbAttack을 false로 변경
		mTimer = 0.0f;
		mAttackBox->SetAttackReadyFlag(false);
		SetAttackFlag(false);
			
		// Monster가 왼쪽에서 공격받았을 경우
		if (GetMonsterHitDirection() == MonsterDirection::Left)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_L", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 왼쪽에서 맞았기에 오른쪽으로 날아가야한다.
			velocity.x = HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);

			SetMonsterDirection(MonsterDirection::Left);
		}
		// 몬스터가 오른쪽에서 공격받았을 경우
		if (GetMonsterHitDirection() == MonsterDirection::Right)
		{
			at->PlayAnimation(L"CarleonRecruit_Hit_R", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 오른쪽에서 맞았기에 왼쪽으로 날아가야한다.
			velocity.x = -HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);

			SetMonsterDirection(MonsterDirection::Right);
		}
		// 몬스터의 공격받은 방향을 초기화해준다.
		SetMonsterHitDirection(MonsterDirection::None);

		// 공격받은 후 땅에 닿으면 Trace 상태로 전환
		if (rb->GetGround() == true)
		{
			//SetMonsterState(MonsterState::Idle);
			//if (GetMonsterDirection() == MonsterDirection::Left)
			//{
			//	at->PlayAnimation(L"Idle_L", true);
			//}
			//if (GetMonsterDirection() == MonsterDirection::Right)
			//{
			//	at->PlayAnimation(L"Idle_R", true);
			//}
			SetMonsterState(MonsterState::Trace);
		}
	}
}