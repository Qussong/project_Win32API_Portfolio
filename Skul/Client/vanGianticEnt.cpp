#include "vanGianticEnt.h"
#include "vanCollider.h"
#include "vanRigidBody.h"
#include "vanAnimator.h"
#include "vanMonsterAttack.h"
#include "vanTransform.h"
#include "vanResourceManager.h"
#include "vanTexture.h"



namespace van
{
	GianticEnt::GianticEnt()
	{
		// nothing
	}

	GianticEnt::~GianticEnt()
	{
		// nothing
	}

	void GianticEnt::Init()
	{
		Monster::Init();

		MakeAnimation();

		// Monster 초기설정
		SetMonsterState(MonsterState::Gen);									// 상태
		GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 200.0f));	// 충돌체 크기 설정
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// 이미지 스케일 설정

		// attackBox의 초기값 설정
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->SetNotifyFlag(true);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(600.0f, 250.0f));
		attackBox->SetOffset(math::Vector2(0.0f, -25.0f));
	}

	void GianticEnt::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// attackBox 값세팅
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		GameObject::Update();

		switch (GetMonsterState())
		{
		case MonsterState::Gen:
			Gen();
			break;
		case MonsterState::Idle:
			Idle();
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
		default:
			__noop;
		}

		// 피격횟수 2회면 죽음
		if (GetAttackCnt() > 2)
		{
			SetMonsterState(MonsterState::Dead);
		}
	}

	void GianticEnt::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void GianticEnt::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Idle", ResourceManager::Find<Texture>(L"GianticEnt_Idle"), math::Vector2(0.0f, 0.0f), math::Vector2(115.0f, 114.0f), 5);
		animator->CreateAnimation(L"Attack_Melee_Ready", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Melee_Ready"), math::Vector2(0.0f, 0.0f), math::Vector2(140.0f, 112.0f), 4);
		animator->CreateAnimation(L"Attack_Melee", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Melee"), math::Vector2(0.0f, 0.0f), math::Vector2(140.0f, 112.0f), 4);
		animator->CreateAnimation(L"Attack_Range_Ready", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Range_Ready"), math::Vector2(0.0f, 0.0f), math::Vector2(134.0f, 115.0f), 2);
		animator->CreateAnimation(L"Attack_Range", ResourceManager::Find<Texture>(L"GianticEnt_Attack_Range"), math::Vector2(0.0f, 0.0f), math::Vector2(134.0f, 115.0f), 2);
	}

	void GianticEnt::OnCollisionEnter(Collider* _other)
	{
		Monster::OnCollisionEnter(_other);
	}

	void GianticEnt::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void GianticEnt::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void GianticEnt::Gen()
	{
		Animator* at = GetComponent<Animator>();
		if (GetPlayAnimation() == true)
		{
			at->PlayAnimation(L"Monster_Generate");
			SetPlayAnimation(false);
		}

		if (at->IsActiveAnimationComplete())
		{
			SetMonsterDirection(MonsterDirection::Center);	// 방향
			SetMonsterState(MonsterState::Idle);			// 상태
			SetPlayAnimation(true);
		}
	}

	void GianticEnt::Idle()
	{
		Animator* at = GetComponent<Animator>();

		if (GetPlayAnimation())
		{
			at->PlayAnimation(L"Idle", true);
			SetPlayAnimation(false);
		}
		if (mbAttackEnd == true)
		{
			AddTimer(Time::GetDeltaTime());
			if (GetTimer() >= 1.0f)
			{
				SetTimer(0.0f);
				mbAttackEnd = false;
			}
		}
		else
		{
			// Attack 범위에 플레이어가 들어오면 Attack Ready 수행
			if (GetAttackFlag() == true)
			{
				SetMonsterState(MonsterState::AttackReady);
				SetPlayAnimation(true);
			}
		}
	}

	void GianticEnt::Walk()
	{
		// notjing
	}

	void GianticEnt::Patrol()
	{
		// notjing
	}

	void GianticEnt::Trace()
	{
		// notjing
	}

	void GianticEnt::AttackReady()
	{
		// Melee || Range 랜덤으로 선택
		if (mbChooseSkill == false)
		{
			srand((UINT)time(NULL));
			mAttackCase = (MonsterSkill)(rand() % 2);	// 0 = Melee , 1 = Range
			mbChooseSkill = true;
		}

		// 해당하는 공격유형의 준비자세를 수행
		// 일정 시간이 지나면 Attack 상태로 넘어감
		switch (mAttackCase)
		{
		case MonsterSkill::Melee:
			AttackMeleeReady();
			break;
		case MonsterSkill::Range:
			AttackRangeReady();
			break;
		default:
			__noop;
		}
	}

	void GianticEnt::Attack()
	{
		// 해당하는 공격유형의 공격을 수행
		switch (mAttackCase)
		{
		case MonsterSkill::Melee:
			AttackMelee();
			break;
		case MonsterSkill::Range:
			AttackRange();
			break;
		default:
			__noop;
		}
	}

	void GianticEnt::AttackEnd()
	{
		// Idle 상태로 넘기고 
		// 1초 유지하다가 다시 공격범위안에 있다면 공격수행
		mbAttackEnd = true;
		SetMonsterState(MonsterState::Idle);
		SetPlayAnimation(true);
		// 공격스킬을 다시 선택해야하기에 false로 설정
		mbChooseSkill = false;
	}

	void GianticEnt::Hit()
	{
		SetPlayAnimation(true);
	}

	void GianticEnt::Dead()
	{
		Monster::Dead();
	}

	void GianticEnt::Wall()
	{
		// nothing
	}

	void GianticEnt::AttackMeleeReady()
	{
		Animator* at = GetComponent<Animator>();
		// 공격 준비상태일 때
		if (GetMonsterState() == Monster::MonsterState::AttackReady)
		{
			// Attack Ready 애니메이션 재생
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Melee_Ready", false);
				SetPlayAnimation(false);
			}
			// Attack 상태로 전환
			if (at->IsActiveAnimationComplete() == true)
			{
				// 시간 카운트
				AddTimer(Time::GetDeltaTime());
				// 2초 이상이 되면 공격상태로 전환
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Attack);
					SetPlayAnimation(true);
				}
			}
		}
	}

	void GianticEnt::AttackMelee()
	{
		Animator* at = GetComponent<Animator>();
		// 공격 상태일 때
		if (GetMonsterState() == Monster::MonsterState::Attack)
		{
			// Attack Ready 애니메이션 재생
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Melee", false);
				SetPlayAnimation(false);
			}

			if (at->IsActiveAnimationComplete())
			{
				SetMonsterState(MonsterState::AttackEnd);
			}
		}
	}

	void GianticEnt::AttackRangeReady()
	{
		Animator* at = GetComponent<Animator>();
		// 공격 준비상태일 때
		if (GetMonsterState() == Monster::MonsterState::AttackReady)
		{
			// Attack Ready 애니메이션 재생
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Range_Ready", false);
				SetPlayAnimation(false);
			}

			// Attack 상태로 전환
			if (at->IsActiveAnimationComplete() == true)
			{
				// 시간 카운트
				AddTimer(Time::GetDeltaTime());
				// 2초 이상이 되면 공격상태로 전환
				if (GetTimer() >= 2.0f)
				{
					SetTimer(0.0f);
					SetMonsterState(MonsterState::Attack);
					SetPlayAnimation(true);
				}
			}
		}
	}

	void GianticEnt::AttackRange()
	{
		Animator* at = GetComponent<Animator>();
		// 공격 상태일 때
		if (GetMonsterState() == Monster::MonsterState::Attack)
		{
			// Attack Ready 애니메이션 재생
			if (GetPlayAnimation() == true)
			{
				at->PlayAnimation(L"Attack_Range", false);
				SetPlayAnimation(false);
			}
		
			if (at->IsActiveAnimationComplete())
			{
				SetMonsterState(MonsterState::AttackEnd);
			}
		}
	}

}