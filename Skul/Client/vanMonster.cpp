#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanObject.h"
#include "vanMonsterTrace.h"
#include "vanMonsterAttack.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanGold.h"
#include "vanSkull.h"

#define WALK_SPEED			150.0f
#define HIT_BUMP_X			50.0f
#define HIT_BUMP_Y			-300.0f
#define WALL_BUMP_X			20.0f
#define WALL_BUMP_Y			-100.0f
#define ATTACK_READY_DELAY	1.0f
namespace van
{
	Monster::Monster()
		: mTarget(nullptr)
		, mState(MonsterState::None)
		, mPastState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mPastDirection(MonsterDirection::None)
		, mHitDirection(MonsterDirection::None)
		, mTimer(0.0f)
		, mbPatrol(false)
		, mbTrace(false)
		, mbAttack(false)
		, mbPlayAnimation(true)
		, mbWallFlag(false)
		, mTraceBox(nullptr)
		, mAttackBox(nullptr)
		, mAttackCnt(0)
	{
		AddComponent<RigidBody>();
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
	}

	Monster::~Monster()
	{
		Destroy(mTraceBox);
		Destroy(mAttackBox);
	}

	void Monster::Init()
	{
		SceneManager::GetActiveScene()->AddMonsterCnt();
	}

	void Monster::Update()
	{
		GameObject::Update();

		// Animation 재생여부 판정_1
		SetMonsterPastState(GetMonsterState());			// 현재 몬스터의 상태를 저장
		SetMonsterPastDirection(GetMonsterDirection());	// 현재 몬스터의 방향을 저장

		switch (GetMonsterState())
		{
		case MonsterState::Gen:
			Gen();
			break;
		case MonsterState::Idle:
			Idle();
			break;
		case MonsterState::Walk:
			Walk();
			break;
		case MonsterState::Patrol:
			Patrol();
			break;
		case MonsterState::Trace:
			Trace();
			break;
		case MonsterState::AttackReady:
			AttackReady();
			break;
		case MonsterState::Attack:
			Attack();
			break;
		case MonsterState::AttackEnd:
			AttackEnd();
			break;
		case MonsterState::Hit:
			Hit();
			break;
		case MonsterState::Dead:
			Dead();
			break;
		case MonsterState::Wall:
			Wall();
			break;
		default:
			__noop;
		}

		// 피격횟수 2회면 죽음
		if (mAttackCnt > 2)
		{
			SetMonsterState(MonsterState::Dead);
		}

		// Animation 재생여부 판정_2
		// 만약 몬스터의 상태,방향이 바꼈다면
		if (GetMonsterState() != GetMonsterPastState()
			|| GetMonsterDirection() != GetMonsterPastDirection())
		{
			SetPlayAnimation(true);
		}
	}

	void Monster::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Monster::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(L"Monster_Generate", ResourceManager::Find<Texture>(L"Monster_Generate"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
		animator->CreateAnimation(L"Monster_Destroy", ResourceManager::Find<Texture>(L"Monster_Destroy"), math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 105.0f), 5);
	}

	void Monster::OnCollisionEnter(Collider* _other)
	{
		// 기본 스컬 머리 스킬에 공격받았을 경우
		GameObject* obj = _other->GetOwner();
		Skull* head = dynamic_cast<Skull*>(obj);
		
		if (head != nullptr)
		{
			Skull::HeadDirection headDirection = head->GetDirection();
			// 공격받은 방향 저장
			if (headDirection == Skull::HeadDirection::Left)
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

			AddAttackCnt();
			SetMonsterState(MonsterState::Hit);
		}
	}

	void Monster::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		van::PlayerAttack* attack = dynamic_cast<van::PlayerAttack*>(obj);	// 충돌한 객체가 Attack 클래스인지 확인

		// 충돌한 객체가 PlayerAttack 클래스인 경우 == 피격(Hit)판정
		if (attack != nullptr
			&& GetMonsterState() != MonsterState::Dead)
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
					AddAttackCnt();
					SetMonsterState(MonsterState::Hit);
					// Hit 판정을 받으면 Patrol 상태가 아니기에 Patrol Flag를 꺼준다.
					SetPatrolFlag(false);
				}

				// 공격판정 범위에 충돌한 충돌체 저장
				list->insert(this);
			}
		}
	}

	void Monster::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Monster::Gen()
	{
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Monster_Generate");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			SetMonsterDirection(MonsterDirection::Left);	// 방향
			SetMonsterState(MonsterState::Patrol);			// 상태
		}
	}

	void Monster::Idle()
	{
		Animator* at = GetComponent<Animator>();

		if (GetWallFlag() == false)
		{
			// Patrol 상태일 때 
			if (GetPatrolFlag() == true
				&& GetWallFlag() == false)
			{
				// Trace 범위에 Player가 들어왔을 경우 Trace 상태로 전환
				if (GetTraceFlag() == true)
				{
					// Patrol 행동 패턴에 사용했던 Timer는 초기화해준다.
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Trace);
					return;
				}
				// 시간 누적
				AddTimer(Time::GetDeltaTime());
				// Patrol상태시 Idle는 2초간 진행
				// Idle 상태가 2초 이상 유지되었을 때
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);							// 누적시간 0초로 초기화
					SetMonsterState(MonsterState::Walk);	// Walk 로 상태 변경
					// 방향전환
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						SetMonsterDirection(MonsterDirection::Right);
					}
					else
					{
						SetMonsterDirection(MonsterDirection::Left);
					}
					return;
				}
				// 누적된 시간이 3초 이상이 아니라면
				else
				{
					// Idle_L
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						if (GetPlayAnimation() == true)
						{
							at->PlayAnimation(L"Idle_L", true);
							SetPlayAnimation(false);
						}
					}
					// Idle_R
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
			// Attack 상태일 때
			else if (GetAttackFlag() == true)
			{
				// 시간 누적
				AddTimer(Time::GetDeltaTime());
				// Attack상태시 Idle는 0.5초간 진행
				if (GetTimer() >= 0.5f)
				{
					SetTimer(0.0f);								// 누적시간 0초로 초기화
					SetMonsterState(MonsterState::AttackReady);	//	AttackReady로 상태 변경
				}
				// 누적된 시간이 0.5초 이상이 아니라면
				else
				{
					// Idle_L
					if (GetMonsterDirection() == MonsterDirection::Left)
					{
						if (GetPlayAnimation() == true)
						{
							at->PlayAnimation(L"Idle_L", true);
							SetPlayAnimation(false);
						}
					}
					// Idle_R
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
		else
		{
			SetMonsterState(MonsterState::Wall);
		}
	}

	void Monster::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		if (GetWallFlag() == false)
		{
			// Patrol 상태일 때 
			if (GetPatrolFlag() == true)
			{
				// Trace 범위에 Player가 들어왔을 경우
				if (GetTraceFlag() == true)
				{
					// Patrol 행동 패턴에 사용했던 Timer는 초기화해준다.
					SetTimer(0.0f);
					// Trace 상태로 바로 전환
					SetMonsterState(MonsterState::Trace);
					return;
				}
				// 시간 누적
				AddTimer(Time::GetDeltaTime());
				// Patrol상태시 Walk는 2초간 진행
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);
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
			else if (GetTraceFlag() == true)
			{
				// Trace 범위에 Player가 들어왔을 경우
				if (GetAttackFlag() == true)
				{
					// AttackReady 상태로 바로 전환
					SetMonsterState(MonsterState::AttackReady);
					return;
				}

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
			// Patrol, Trace 상태가 아닐때
			else
			{
				__noop;
			}
		}
		else
		{
			SetMonsterState(MonsterState::Wall);
		}
	}

	void Monster::Patrol()
	{
		// 몬스터가 모든 상태에서 Patrol 행동을 보이도록 설정
		SetPatrolFlag(true);
		// Patrol시 Idle 부터 시작하도록 한다.
		SetMonsterState(MonsterState::Idle);
	}

	void Monster::Trace()
	{
		// Trace 상태로 전환됐기에 Patrol, Attack Flag는 꺼준다.
		SetPatrolFlag(false);
		// Trace시 Target을 쫓아가기에 Walk 부터 시작
		SetMonsterState(MonsterState::Walk);
	}

	void Monster::AttackReady()
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
		// 카운트중에 피격되면 Timer 리셋 (AttackReadyFlag == false)
		AddTimer(Time::GetDeltaTime());

		// 카운트 완료 (Attack Ready를 완료)
		if (GetTimer() >= ATTACK_READY_DELAY)
		{
			// 1) AttackReadyFlag = true
			attackBox->SetAttackReadyFlag(true);
			// 2) Timer 리셋
			SetTimer(0.0f);
			// 3) Attack 상태로 넘어간다
			SetMonsterState(Monster::MonsterState::Attack);
		}
	}

	void Monster::Attack()
	{
		Animator* ani = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		Monster::MonsterDirection direction = GetMonsterDirection();
		math::Vector2 velocity = rb->GetVelocity();
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		MonsterAttack* attackBox = GetMonsterAttackBox();
		std::set<GameObject*>* list = attackBox->GetMonsterAttackList();

		// Attack Animation재생
		if (GetPlayAnimation() == true)
		{
			// Monster Direction == Left 인 경우
			if (direction == Monster::MonsterDirection::Left)
			{
				ani->PlayAnimation(L"Attack_L", false);
			}
			// Monster Direction == Right 인 경우
			else
			{
				ani->PlayAnimation(L"Attack_R", false);
			}

			SetPlayAnimation(false);
		}

		// 공격 완료
		// 조건 : Attack Animation 재생 완료
		if (ani->IsActiveAnimationComplete() == true)
		{
			// 공격을 수행했기에 Attack Ready Flag = false 로 전환
			attackBox->SetAttackReadyFlag(false);
			// 동일 대상에대한 공격이 가능하도록 AttacList 초기화
			list->clear();
			// 대상을 재설정 할 수 있도록 공격대상을 풀어준다.
			SetMonsterTarget(nullptr);
			// Attack End 상태 만들기
			SetMonsterState(MonsterState::AttackEnd);
		}
	}

	void Monster::AttackEnd()
	{
		if (GetAttackFlag() == true)
		{
			// Idel 상태 갔다가 0.5초 후에 공격 재준비
			SetMonsterState(MonsterState::Idle);
		}
		else if (GetTraceFlag() == true)
		{
			SetMonsterState(MonsterState::Trace);
		}
		else
		{
			SetMonsterState(MonsterState::Patrol);
		}
	}

	void Monster::Hit()
	{
		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// AttackReady중에 피격당하면 mTimer를 0.0f로 초기화 
		SetTimer(0.0f);

		// 피격 애니메이션
		// Monster가 왼쪽에서 공격받았을 경우
		if (GetMonsterHitDirection() == MonsterDirection::Left)
		{
			at->PlayAnimation(L"Hit_L", false);
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
			at->PlayAnimation(L"Hit_R", false);
			rb->SetHit(true);
			rb->SetGround(false);
			// 오른쪽에서 맞았기에 왼쪽으로 날아가야한다.
			velocity.x = -HIT_BUMP_X;
			velocity.y = HIT_BUMP_Y;
			rb->SetVelocity(velocity);

			SetMonsterDirection(MonsterDirection::Right);
		}
		// 몬스터가 공격받은 방향을 초기화해준다.
		SetMonsterHitDirection(MonsterDirection::None);

		if (rb->GetGround() == true)
		{
			rb->SetHit(false);
			SetMonsterState(MonsterState::AttackReady);
		}
	}

	void Monster::Dead()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		if (GetPlayAnimation() == true)
		{
			// 소멸 애니메이션 재생
			at->PlayAnimation(L"Monster_Destroy");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			// 코인 떨구기 구현
			Gold* gold = Object::Instantiate<Gold>(enums::eLayerType::Drop);
			gold->GetComponent<Transform>()->SetPosition(tr->GetPosition());
			// 해당 Scene의 몬스터 숫자 감소시켜주기
			SceneManager::GetActiveScene()->LoseMonsterCnt();
			// 객체 소멸
			Destroy(this);
		}
	}

	void Monster::Wall()
	{
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		SetWallFlag(false);
		rb->SetHit(true);
		velocity.x = -WALL_BUMP_X;
		velocity.y = WALL_BUMP_Y;
		rb->SetVelocity(velocity);

		if (rb->GetGround() == true)
		{
			rb->SetHit(false);
			SetMonsterState(MonsterState::Patrol);
		}
	}
}
