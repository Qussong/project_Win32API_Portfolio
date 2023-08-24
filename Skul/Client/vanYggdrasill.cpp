#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"

#define INIT_POS_X	Window_X / 2
#define INIT_POS_Y	Window_Y / 2

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
			Idle();
			break;
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
			FistSlam();
			break;
		case BossSkill::Swipe:
			Swipe();
			break;
		case BossSkill::MagicOrbs:
			MagicOrbs();
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
	}

	void Yggdrasill::Hit()
	{

	}

	void Yggdrasill::Dead()
	{

	}

	void Yggdrasill::FistSlamReady()
	{
		//mBody->SetState(YggdrasillBody::BodyState::FistSlamReady);
		//mHead->SetState(YggdrasillHead::HeadState::FistSlamReady);
		//mChin->SetState(YggdrasillChin::ChinState::FistSlamReady);
		mHandLeft->SetState(YggdrasillHand::HandState::FistSlamReady);
		mHandRight->SetState(YggdrasillHand::HandState::FistSlamReady);

		if (mHandLeft->GetReadyFinishFlag() == true
			&& mHandRight->GetReadyFinishFlag() == true)
		{
			mHandLeft->SetReadyFinishFlag(false);
			mHandRight->SetReadyFinishFlag(false);

			mState = BossState::Attack;
		}
	}

	void Yggdrasill::SwipeReady()
	{
	}

	void Yggdrasill::MagicOrbsReady()
	{
	}

	void Yggdrasill::FistSlam()
	{
		//mBody->SetState(YggdrasillBody::BodyState::FistSlam);
		//mHead->SetState(YggdrasillHead::HeadState::FistSlam);
		//mChin->SetState(YggdrasillChin::ChinState::FistSlam);
		mHandLeft->SetState(YggdrasillHand::HandState::FistSlam);
		mHandRight->SetState(YggdrasillHand::HandState::FistSlam);

		if (mHandLeft->GetEndFinishFlag() == true
			&& mHandRight->GetEndFinishFlag() == true)
		{
			// 초기화
			mHandLeft->SetEndFinishFlag(false);
			mHandRight->SetEndFinishFlag(false);
			mFistSlamCnt = 0;

			mState = BossState::AttackEnd;
		}
	}

	void Yggdrasill::Swipe()
	{

	}

	void Yggdrasill::MagicOrbs()
	{
	}
	void Yggdrasill::FistSlamEnd()
	{
		//mBody->SetState(YggdrasillBody::BodyState::FistSlamEnd);
		//mHead->SetState(YggdrasillHead::HeadState::FistSlamEnd);
		//mChin->SetState(YggdrasillChin::ChinState::FistSlamEnd);
		mHandLeft->SetState(YggdrasillHand::HandState::FistSlamEnd);
		mHandRight->SetState(YggdrasillHand::HandState::FistSlamEnd);

		if (mHandLeft->GetEndFinishFlag() == true
			&& mHandRight->GetEndFinishFlag() == true)
		{
			// 초기화
			mHandLeft->SetEndFinishFlag(false);
			mHandRight->SetEndFinishFlag(false);
			mbChooseSkill = false;
			mState = BossState::Idle;
		}

	}
	void Yggdrasill::SwipeEnd()
	{
	}
	void Yggdrasill::MagicOrbsEnd()
	{
	}
}