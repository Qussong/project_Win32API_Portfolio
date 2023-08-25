#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"

#define INIT_POS_X		Window_X / 2
#define INIT_POS_Y		Window_Y / 2
#define FIST_SLAM_CNT	2
#define SWIPE_CNT		2

namespace van
{
	Yggdrasill::Yggdrasill()
	{
		// nothing
	}

	Yggdrasill::~Yggdrasill()
	{
		// nothing
	}

	void Yggdrasill::Init()
	{
		Boss::Init();		// 아무것도 안함

		MakeAnimation();	// 아무것도 안함

		//SetBossState(BossState::Gen);
		mState = BossState::Idle;
		SetBossDirection(BossDirection::Center);
		mInitPos = math::Vector2(INIT_POS_X, INIT_POS_Y);

		mBody = Object::Instantiate<YggdrasillBody>(enums::eLayerType::Yggdrasill_Body);
		mHead = Object::Instantiate<YggdrasillHead>(enums::eLayerType::Yggdrasill_Head);
		mChin = Object::Instantiate<YggdrasillChin>(enums::eLayerType::Yggdrasill_Chin);
		mHandLeft = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		mHandRight = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);

		mBody->SetOwner(this);
		mHead->SetOwner(this);
		mChin->SetOwner(this);
		mHandLeft->SetOwner(this);
		mHandRight->SetOwner(this);
		
		mHandLeft->SetHandPos(YggdrasillHand::HandPos::Left);
		mHandRight->SetHandPos(YggdrasillHand::HandPos::Right);

		mBody->SetPos(mInitPos);
	}

	void Yggdrasill::Update()
	{
		Boss::Update();	// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.

		switch (mState)
		{
		case BossState::Gen:
			Gen();
			break;
		case BossState::Idle:
		{
			Idle();
			break;
		}
		case BossState::AttackReady:
			AttackReady();
			break;
		case BossState::Attack:
			Attack();
			break;
		case BossState::AttackEnd:
			AttackEnd();
			break;
		case BossState::Hit:
			Hit();
			break;
		case BossState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void Yggdrasill::Render(HDC _hdc)
	{
		Boss::Render(_hdc);	// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
	}

	void Yggdrasill::MakeAnimation()
	{
		// nothing
	}

	void Yggdrasill::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::Gen()
	{

	}

	void Yggdrasill::Idle()
	{
		mBody->SetState(YggdrasillBody::BodyState::Idle);
		mHead->SetState(YggdrasillHead::HeadState::Idle);
		mChin->SetState(YggdrasillChin::ChinState::Idle);
		mHandLeft->SetState(YggdrasillHand::HandState::Idle);
		mHandRight->SetState(YggdrasillHand::HandState::Idle);

		mTime += Time::GetDeltaTime();
		// Idle --(3초)--> Attack Ready
		if (mTime >= 3.0f)
		{
			mTime = 0.0f;
			mState = BossState::AttackReady;
		}
	}

	void Yggdrasill::AttackReady()
	{
		if (mbChooseSkill == false)
		{
			/*
				FistSlam,	// 0
				Swipe,		// 1
				MagicOrbs,	// 2
			*/
			srand((UINT)time(NULL));
			//mAttackCase = (BossSkill)(rand() % 3);
			mAttackCase = (BossSkill)(0);
			mbChooseSkill = true;
		}

		if (mbChooseSkill == true)
		{
			switch (mAttackCase)
			{
			case BossSkill::FistSlam:
				FistSlamReady();
				break;
			case BossSkill::Swipe:
				SwipeReady();
				break;
			case BossSkill::MagicOrbs:
				MagicOrbsReady();
				break;
			default:
				__noop;
			}
		}
	}

	void Yggdrasill::Attack()
	{
		switch (mAttackCase)
		{
		case BossSkill::FistSlam:
			FistSlamAttack();
			break;
		case BossSkill::Swipe:
			SwipeAttack();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbsAttack();
			break;
		default:
			__noop;
		}
	}

	void Yggdrasill::AttackEnd()
	{
		switch (mAttackCase)
		{
		case BossSkill::FistSlam:
		{
			FistSlamEnd();
			break;
		}
		case BossSkill::Swipe:
			SwipeEnd();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
	}

	void Yggdrasill::Hit()
	{

	}

	void Yggdrasill::Dead()
	{

	}

	void Yggdrasill::FistSlamReady()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);

			mState = BossState::Attack;
		}
	}
	
	void Yggdrasill::SwipeReady()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);

			mState = BossState::Attack;
		}
	}

	void Yggdrasill::MagicOrbsReady()
	{

	}

	void Yggdrasill::FistSlamAttack()
	{
		// 각 부위별 상태값 변경
		mHandLeft->SetState(YggdrasillHand::HandState::Attack);
		mHandRight->SetState(YggdrasillHand::HandState::Attack);

		GameObject* target = GetTarget();
		math::Vector2 targetPos = target->GetComponent<Transform>()->GetPosition();
		math::Vector2 ownPos = GetComponent<Transform>()->GetPosition();

		// 공격할 Hand 방향 선택
		if(mAttackDir == AttackHandDir::None)
		{
			// target 이 own 보다 왼쪽에 있을 때 (target.x < own.x)
			if (targetPos.x <= ownPos.x)
			{
				mAttackDir = AttackHandDir::Left;
			}
			// target 이 own 보다 오른쪽에 있을 때 (target.x > own.x)
			if (targetPos.x > ownPos.x)
			{
				mAttackDir = AttackHandDir::Right;
			}
		}

		// 정해진 횟수만큼 공격수행
		if (mFistSlamCnt < FIST_SLAM_CNT
			&& mAttackDir != AttackHandDir::None)
		{
			if (mAttackDir == AttackHandDir::Left)
			{
				mHandLeft->FistSlam();
				// 수행 완료시 공격횟수 카운트
				if (mHandLeft->GetFistSlamFlag() == true)
				{
					mHandLeft->SetFistSlamFlag(false);
					mAttackDir = AttackHandDir::None;
					++mFistSlamCnt;
				}
			}
			if (mAttackDir == AttackHandDir::Right)
			{
				mHandRight->FistSlam();
				// 수행 완료시 공격횟수 카운트
				if (mHandRight->GetFistSlamFlag() == true)
				{
					mHandRight->SetFistSlamFlag(false);
					mAttackDir = AttackHandDir::None;
					++mFistSlamCnt;
				}
			}
		}
		// 공격을 완료했을 때
		else
		{
			mHandLeft->FistSlamAfter();
			mHandRight->FistSlamAfter();

			if (mHandLeft->GetFinishFlag() == true
				&& mHandRight->GetFinishFlag() == true)
			{
				// 초기화
				mFistSlamCnt = 0;
				mHandLeft->SetFinishFlag(false);
				mHandRight->SetFinishFlag(false);
				// 상태변경 (Attack --> Attack End)
				mState = BossState::AttackEnd;
			}
		}
	}

	void Yggdrasill::SwipeAttack()
	{
		GameObject* target = GetTarget();
		math::Vector2 targetPos = target->GetComponent<Transform>()->GetPosition();
		math::Vector2 ownPos = GetComponent<Transform>()->GetPosition();

		// 각 부위별 상태값 변경
		mHandLeft->SetState(YggdrasillHand::HandState::Attack);
		mHandRight->SetState(YggdrasillHand::HandState::Attack);

		// 공격할 Hand 방향 선택
		if (mAttackDir == AttackHandDir::None)
		{
			// target 이 own 보다 왼쪽에 있을 때 (target.x < own.x)
			if (targetPos.x <= ownPos.x)
			{
				mAttackDir = AttackHandDir::Right;
			}
			// target 이 own 보다 오른쪽에 있을 때 (target.x > own.x)
			if (targetPos.x > ownPos.x)
			{
				mAttackDir = AttackHandDir::Left;
			}
		}

		// 정해진 횟수만큼 공격수행
		if (mSwipCnt < FIST_SLAM_CNT
			&& mAttackDir != AttackHandDir::None)
		{
			if (mAttackDir == AttackHandDir::Left)
			{
				mHandLeft->Swip();
				// 수행 완료시 공격횟수 카운트
				if (mHandLeft->GetSwipeFlag() == true)
				{
					mHandLeft->SetSwipeFlag(false);
					mAttackDir = AttackHandDir::None;
					++mSwipCnt;
				}
			}
			if (mAttackDir == AttackHandDir::Right)
			{
				mHandRight->Swip();
				// 수행 완료시 공격횟수 카운트
				if (mHandRight->GetSwipeFlag() == true)
				{
					mHandRight->SetSwipeFlag(false);
					mAttackDir = AttackHandDir::None;
					++mSwipCnt;
				}
			}
		}
		// 공격을 완료했을 때
		else
		{
			mSwipCnt = 0;
			// 상태변경 (Attack --> Attack End)
			mState = BossState::AttackEnd;
		}

	}

	void Yggdrasill::MagicOrbsAttack()
	{

	}

	void Yggdrasill::FistSlamEnd()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackEnd);
		mHandRight->SetState(YggdrasillHand::HandState::AttackEnd);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			// 초기화
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);
			mbChooseSkill = false;
			// 상태변경 (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::SwipeEnd()
	{
		mHandLeft->SetState(YggdrasillHand::HandState::AttackEnd);
		mHandRight->SetState(YggdrasillHand::HandState::AttackEnd);

		if (mHandLeft->GetFinishFlag() == true
			&& mHandRight->GetFinishFlag() == true)
		{
			// 초기화
			mHandLeft->SetFinishFlag(false);
			mHandRight->SetFinishFlag(false);
			mbChooseSkill = false;

			// 상태변경 (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::MagicOrbsEnd()
	{
	}
}