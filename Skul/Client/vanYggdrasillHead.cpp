#include "vanYggdrasillHead.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

#define INIT_POS_X	-10.0f
#define INIT_POS_Y	-60.0f
#define IDLE_SPEED	15.0f

namespace van
{
	YggdrasillHead::YggdrasillHead()
	{
		// nothing
	}

	YggdrasillHead::~YggdrasillHead()
	{
		// nothing
	}

	void YggdrasillHead::Init()
	{
		GameObject::Init();

		MakeAnimation();

		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Head", true);

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(200.0f, 300.0f));
		col->SetOffset(math::Vector2(25.0f, 40.0f));

		mInitAddPos = math::Vector2(INIT_POS_X, INIT_POS_Y);
		mAddPos = mInitAddPos;
	}

	void YggdrasillHead::Update()
	{
		GameObject::Update();

		FollowBodyPos();

		switch (mState)
		{
		case HeadState::Gen:
			Gen();
			break;
		case HeadState::Idle:
			Idle();
			break;
		case HeadState::FistSlamReady:
			FistSlamReady();
			break;
		case HeadState::SwipeReady:
			SwipeReady();
			break;
		case HeadState::MagicOrbsReady:
			MagicOrbsReady();
			break;
		case HeadState::FistSlam:
			FistSlam();
			break;
		case HeadState::Swipe:
			Swipe();
			break;
		case HeadState::MagicOrbs:
			MagicOrbs();
			break;
		case HeadState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillHead::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillHead::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Head", ResourceManager::Find<Texture>(L"Yggdrasill_Head"), math::Vector2(0.0f, 0.0f), math::Vector2(241.0f, 168.0f), 2, math::Vector2::Zero, 1.0F);

	}
	
	void YggdrasillHead::OnCollisionEnter(Collider* _other)
	{
		// 피격판정
	}

	void YggdrasillHead::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHead::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHead::Gen()
	{
	}

	void YggdrasillHead::Idle()
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
			mAddPos.y += IDLE_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mAddPos.y -= IDLE_SPEED * Time::GetDeltaTime();
		}

	}

	void YggdrasillHead::Dead()
	{
	}

	void YggdrasillHead::FistSlamReady()
	{

	}

	void YggdrasillHead::SwipeReady()
	{
	}

	void YggdrasillHead::MagicOrbsReady()
	{
	}

	void YggdrasillHead::FistSlam()
	{
	}

	void YggdrasillHead::Swipe()
	{
	}

	void YggdrasillHead::MagicOrbs()
	{
	}

	void YggdrasillHead::FollowBodyPos()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();
		math::Vector2 ownerPos = tr_owner->GetPosition();

		math::Vector2 newPos = ownerPos + mAddPos;
		
		tr->SetPosition(newPos);
	}

}