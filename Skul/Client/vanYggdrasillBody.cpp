#include "vanYggdrasillBody.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanTransform.h"

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
		//col->SetSize(math::Vector2(418.0f * 2, 341.0f * 2));
		col->SetSize(math::Vector2(700.0f, 600.0f));
	}

	void YggdrasillBody::Update()
	{
		GameObject::Update();

		SetOwnerPos();

		switch (mState)
		{
		case BodyState::Gen:
			Gen();
			break;
		case BodyState::Idle:
			Idle();
			break;
		case BodyState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
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

	void YggdrasillBody::FistSlamReady()
	{
	}

	void YggdrasillBody::SwipeReady()
	{
	}

	void YggdrasillBody::MagicOrbsReady()
	{
	}

	void YggdrasillBody::FistSlam()
	{
	}

	void YggdrasillBody::Swipe()
	{
	}

	void YggdrasillBody::MagicOrbs()
	{
	}

	void YggdrasillBody::Dead()
	{

	}

	void YggdrasillBody::SetOwnerPos()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();
		tr_owner->SetPosition(tr->GetPosition());
	}
}