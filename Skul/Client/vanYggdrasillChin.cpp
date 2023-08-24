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

		FollowHeadPos();

		switch (mState)
		{
		case ChinState::Gen:
			Gen();
			break;
		case ChinState::Idle:
			Idle();
			break;
		case ChinState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
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

	void YggdrasillChin::FistSlamReady()
	{
	}

	void YggdrasillChin::SwipeReady()
	{
	}

	void YggdrasillChin::MagicOrbsReady()
	{
	}

	void YggdrasillChin::FistSlam()
	{
	}

	void YggdrasillChin::Swipe()
	{
	}

	void YggdrasillChin::MagicOrbs()
	{
	}

	void YggdrasillChin::Dead()
	{
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
}