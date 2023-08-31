#include "vanYggdrasillChin.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanYggdrasill.h"
#include "vanYggdrasillHead.h"


#define INIT_POS_X	30.0f
#define INIT_POS_Y	140.0f
#define IDLE_SPEED	-30.0f
#define SHOOT_MAGICORB_SHAKE_SPEED 80.0f

namespace van
{
	YggdrasillChin::YggdrasillChin()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillChin::~YggdrasillChin()
	{
		// nothing
	}

	void YggdrasillChin::Init()
	{
		GameObject::Init();	// 아무것도 안함

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Chin"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(230.0f, 110.0f));
		col->SetOffset(math::Vector2(0.0f, -50.0f));

		mInitAddPos = math::Vector2(INIT_POS_X, INIT_POS_Y);
		mAddPos = mInitAddPos;
	}

	void YggdrasillChin::Update()
	{
		GameObject::Update();	// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.
		ChkNextPhase();
		if (mState != ChinState::Dead)
		{
			FollowHeadPos();
		}

		if (mPastState != mState)
		{
			mbPlayAnimation = true;
			// 행동패턴의 수행이 끝났음을 알리는 mbEnd를 초기화
			if (mbEnd == true)
			{
				mbEnd = false;
			}
		}

		switch (mState)
		{
		case ChinState::Gen:
			Gen();
			break;
		case ChinState::Idle:
			Idle();
			break;
		case ChinState::AttackReady:
			AttackReady();
			break;
		case ChinState::Attack:
			Attack();
			break;
		case ChinState::AttackEnd:
			AttackEnd();
			break;
		case ChinState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		mPastState = mState;	// 현재의 상태와 미래의 상태를 비교하여 애니메이션 재생여부를 결정한다.(다르면 mPlayAnimation = true)
	}

	void YggdrasillChin::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);	// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
	}

	void YggdrasillChin::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::Gen()
	{
	}

	void YggdrasillChin::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		mTime += Time::GetDeltaTime();
		if (mTime >= 0.7f)
		{
			mTime = 0.0f;
			if (mUpDownFlag == false)
			{
				mUpDownFlag = true;
			}
			else
			{
				mUpDownFlag = false;
			}
		}

		if (mUpDownFlag == true)
		{
			mAddPos.y += IDLE_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mAddPos.y -= IDLE_SPEED * Time::GetDeltaTime();
		}
	}

	void YggdrasillChin::AttackReady()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamReady();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeReady();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsReady();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillChin::Attack()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamAttack();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeAttack();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsAttack();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillChin::AttackEnd()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamEnd();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeEnd();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillChin::FistSlamReady()
	{
	}

	void YggdrasillChin::SwipeReady()
	{
	}

	void YggdrasillChin::MagicOrbsReady()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (mbEnd == false)
		{
			mAddPos.y -= 100.0f * Time::GetDeltaTime();

			float gap = fabs(mInitAddPos.y - mAddPos.y);
			if (gap >= 10.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillChin::FistSlamAttack()
	{
	}

	void YggdrasillChin::SwipeAttack()
	{
	}

	void YggdrasillChin::MagicOrbsAttack()
	{
		Transform* tr = GetComponent<Transform>();

		if (mbEnd == false)
		{
			mAddPos.y += 100.0f * Time::GetDeltaTime();

			float gap = mInitAddPos.y - mAddPos.y;
			if (gap <= -20.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillChin::FistSlamEnd()
	{
	}

	void YggdrasillChin::SwipeEnd()
	{
	}

	void YggdrasillChin::MagicOrbsEnd()
	{
		Transform* tr = GetComponent<Transform>();

		if (mbEnd == false)
		{
			mAddPos = mInitAddPos;
			mbFinish = true;
			mbEnd = true;
		}
	}

	void YggdrasillChin::Dead()
	{
		if (mbFinish == false)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPosition(math::Vector2(660.0f, 490.0f));

			mbFinish = true;
			//Destroy(this);
		}
	}

	void YggdrasillChin::FollowHeadPos()
	{
		Transform* tr = GetComponent<Transform>();
		YggdrasillHead* ownerHead = dynamic_cast<Yggdrasill*>(GetOwner())->GetHead();
		Transform* tr_head = ownerHead->GetComponent<Transform>();
		math::Vector2 headPos = tr_head->GetPosition();

		math::Vector2 newPos = headPos + mAddPos;

		tr->SetPosition(newPos);
	}

	void YggdrasillChin::ChkNextPhase()
	{
		Yggdrasill* ygg = dynamic_cast<Yggdrasill*>(GetOwner());
		if (mbCPhaseonfirm == true)
		{
			if (ygg->GetNextPhaseFlag() == true)
			{
				SpriteRenderer* sr = GetComponent<SpriteRenderer>();
				sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Chin_2Phase"));
			}
			mbCPhaseonfirm = false;
		}
	}

}