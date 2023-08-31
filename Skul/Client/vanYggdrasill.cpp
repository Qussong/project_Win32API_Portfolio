#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanEnergyBomb.h"
#include "vanEnergyBombCharge.h"

#define MAX_HP			800.0f
#define INIT_POS_X		Window_X / 2
#define INIT_POS_Y		Window_Y / 2
#define FIST_SLAM_CNT	2
#define SWIPE_CNT		2
#define MAGIC_ORB_CNT	2
#define MAGIC_ORB_DELAY	1.5f
#define DAMAGE_PERCENT	0.5f

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
		SetMaxHp(MAX_HP);
		SetHp(MAX_HP);

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

		// 강제로 데미지 주기
		CmdDamage();

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

		CmdSkill();	// 강제 커맨드 스킬
	}

	void Yggdrasill::AttackReady()
	{
		if (mbChooseSkill == false)
		{
			if (mbCmd == true)
			{
				mAttackCase = (BossSkill)mCmdSkill;
			}
			else
			{
				/*
					FistSlam,	// 0
					Swipe,		// 1
					MagicOrbs,	// 2
				*/
				((UINT)time(NULL));
				mAttackCase = (BossSkill)(rand() % 3);
				//mAttackCase = (BossSkill)(1);
			}
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
			FistSlamEnd();
			break;
		case BossSkill::Swipe:
			SwipeEnd();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
		// 초기화
		mbCmd = false;
		mCmdSkill = 0;
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
		mBody->SetState(YggdrasillBody::BodyState::AttackReady);
		mHead->SetState(YggdrasillHead::HeadState::AttackReady);
		mChin->SetState(YggdrasillChin::ChinState::AttackReady);
		mHandLeft->SetState(YggdrasillHand::HandState::AttackReady);
		mHandRight->SetState(YggdrasillHand::HandState::AttackReady);

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true
			&& mbShakeFlag == false)
		{
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);

			mbShakeFlag = true;
			mCharge = Object::Instantiate<EnergyBombCharge>(enums::eLayerType::Yggdrasill_Effect);
			mCharge->SetOwner(mHead);
		}

		if (mbShakeFlag == true)
		{
			mHead->ShakeHead();

			if (mCharge->GetChargeFinishFlag() == true)
			{
				mCharge = nullptr;
				mbShakeFlag = false;
				mState = BossState::Attack;
			}
		}
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
		mBody->SetState(YggdrasillBody::BodyState::Attack);
		mHead->SetState(YggdrasillHead::HeadState::Attack);
		mChin->SetState(YggdrasillChin::ChinState::Attack);

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true
			&& mbMagicOrbShootFlag == false)
		{
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);

			mbMagicOrbShootFlag = true;
		}

		if (mbMagicOrbShootFlag == true
			&& mMagicOrbCnt <= MAGIC_ORB_CNT)
		{
			if (mHead->GetMagicOrbShootFlag() == false)
			{
				mTime += Time::GetDeltaTime();
				if (mTime >= MAGIC_ORB_DELAY)
				{
					mTime = 0.0f;
					mbShootDelay = true;
				}

				if (mbShootDelay == true)
				{
					mHead->ShootEnerge();
				}
			}
			else
			{
				// EnergyBomb 생성 & 발사
				ShootEnergyBomb();

				mbShootDelay = false;
				++mMagicOrbCnt;
				mHead->SetMagicOrbShootFlag(false);
				mHead->ResetMagicOrbShootMotionValue();
			}
		}

		if (mMagicOrbCnt > MAGIC_ORB_CNT)
		{
			mMagicOrbCnt = 0;
			mBody->SetFinishFlag(false);
			mState = BossState::AttackEnd;
		}
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
		mBody->SetState(YggdrasillBody::BodyState::AttackEnd);
		mHead->SetState(YggdrasillHead::HeadState::AttackEnd);
		mChin->SetState(YggdrasillChin::ChinState::AttackEnd);

		if (mHead->GetFinishFlag() == true)
		{
			int a = 0;
		}

		if (mBody->GetFinishFlag() == true
			&& mHead->GetFinishFlag() == true
			&& mChin->GetFinishFlag() == true)
		{
			// 초기화
			mBody->SetFinishFlag(false);
			mHead->SetFinishFlag(false);
			mChin->SetFinishFlag(false);
			mbChooseSkill = false;

			// 상태변경 (Attack End --> Idle)
			mState = BossState::Idle;
		}
	}

	void Yggdrasill::ShootEnergyBomb()
	{
		Transform* tr_head = mHead->GetComponent<Transform>();

		EnergyBomb* energyBomb = Object::Instantiate<EnergyBomb>(enums::eLayerType::Yggdrasill_Skill_EnergyBomb);
		energyBomb->SetOwner(mHead);
		energyBomb->GetComponent<Transform>()->SetPosition(tr_head->GetPosition());
	}

	void Yggdrasill::CmdDamage()
	{
		// FistSlam
		if (Input::GetKey(eKeyCode::M)
			&& Input::GetKeyDown(eKeyCode::D))
		{
			LoseHp(MAX_HP * DAMAGE_PERCENT);
		}
	}

	void Yggdrasill::CmdSkill()
	{
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::W))
		{
			mbCmd = true;
			mCmdSkill = 0;
		}
		// Swipe
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::E))
		{
			mbCmd = true;
			mCmdSkill = 1;
		}
		// MagicOrb
		if (Input::GetKey(eKeyCode::Q)
			&& Input::GetKeyDown(eKeyCode::R))
		{
			mbCmd = true;
			mCmdSkill = 2;
		}
	}
}