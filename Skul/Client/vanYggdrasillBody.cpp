#include "vanYggdrasillBody.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanTransform.h"

#include "vanYggdrasill.h"

#define IDLE_SPEED	20.0f

namespace van
{
	YggdrasillBody::YggdrasillBody()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillBody::~YggdrasillBody()
	{
		// nothing
	}

	void YggdrasillBody::Init()
	{
		GameObject::Init();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Body"));

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(700.0f, 600.0f));
	}

	void YggdrasillBody::Update()
	{
		GameObject::Update();

		SetOwnerPos();

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
		case BodyState::Gen:
			Gen();
			break;
		case BodyState::Idle:
			Idle();
			break;
		case BodyState::AttackReady:
			AttackReady();
			break;
		case BodyState::Attack:
			Attack();
			break;
		case BodyState::AttackEnd:
			AttackEnd();
			break;
		case BodyState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		mPastState = mState;	// 현재의 상태와 미래의 상태를 비교하여 애니메이션 재생여부를 결정한다.(다르면 mPlayAnimation = true)
	}

	void YggdrasillBody::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillBody::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void YggdrasillBody::Gen()
	{

	}

	void YggdrasillBody::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		mTime += Time::GetDeltaTime();
		if (mTime >= 1.0f)
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
			pos.y += IDLE_SPEED * Time::GetDeltaTime();
			tr->SetPosition(pos);
		}
		else
		{
			pos.y -= IDLE_SPEED * Time::GetDeltaTime();
			tr->SetPosition(pos);
		}
	}

	void YggdrasillBody::AttackReady()
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

	void YggdrasillBody::Attack()
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

	void YggdrasillBody::AttackEnd()
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

	void YggdrasillBody::FistSlamReady()
	{
		// nothing
	}

	void YggdrasillBody::SwipeReady()
	{
		// nothing
	}

	void YggdrasillBody::MagicOrbsReady()
	{
		Transform* tr = GetComponent<Transform>();
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		math::Vector2 pos = tr->GetPosition();

		if (owner == nullptr)
		{
			return;
		}

		if (mbEnd == false)
		{
			pos.y += 150.0f * Time::GetDeltaTime();
			tr->SetPosition(pos);
		
			float gap = fabs(owner->GetInitPos().y - pos.y);
			if (gap >= 50.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillBody::FistSlamAttack()
	{
		// nothing
	}

	void YggdrasillBody::SwipeAttack()
	{
		// nothing
	}

	void YggdrasillBody::MagicOrbsAttack()
	{
		Transform* tr = GetComponent<Transform>();
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		math::Vector2 pos = tr->GetPosition();

		if (owner == nullptr)
		{
			return;
		}

		if (mbEnd == false)
		{
			pos.y -= 300.0f * Time::GetDeltaTime();
			tr->SetPosition(pos);

			float gap = owner->GetInitPos().y - pos.y;
			if (gap >= 0.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillBody::FistSlamEnd()
	{
		// nothing
	}

	void YggdrasillBody::SwipeEnd()
	{
		// nothing
	}

	void YggdrasillBody::MagicOrbsEnd()
	{
		Transform* tr = GetComponent<Transform>();
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());

		if (owner == nullptr)
		{
			return;
		}

		if (mbEnd == false)
		{
			tr->SetPosition(owner->GetInitPos());
			mbEnd = true;
			mbFinish = true;
		}
	}

	void YggdrasillBody::Dead()
	{
		if (mbFinish == false)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPosition(math::Vector2(640.0f, 360.0f));

			mbFinish = true;
			//Destroy(this);
		}
	}

	void YggdrasillBody::SetOwnerPos()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();
		tr_owner->SetPosition(tr->GetPosition());
	}
}