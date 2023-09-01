#include "vanDoubleJumpSmoke.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	DoubleJumpSmoke::DoubleJumpSmoke()
	{
		// nothing
	}

	DoubleJumpSmoke::~DoubleJumpSmoke()
	{
		// nothing
	}

	void DoubleJumpSmoke::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = DoubleJumpSmokeState::Gen;
	}

	void DoubleJumpSmoke::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case DoubleJumpSmokeState::Gen:
			Gen();
			break;
		case DoubleJumpSmokeState::Active:
			Active();
			break;
		case DoubleJumpSmokeState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void DoubleJumpSmoke::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void DoubleJumpSmoke::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"DoubleJump_Smoke", ResourceManager::Find<Texture>(L"DoubleJump_Smoke"), math::Vector2(0.0f, 0.0f), math::Vector2(95.0f, 25.0f), 10, math::Vector2(0.0f, 0.0f), 0.1F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void DoubleJumpSmoke::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void DoubleJumpSmoke::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void DoubleJumpSmoke::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void DoubleJumpSmoke::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));

			mState = DoubleJumpSmokeState::Active;
		}
	}

	void DoubleJumpSmoke::Active()
	{
		GameObject* owner = GetOwner();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			at->PlayAnimation(L"DoubleJump_Smoke", false);
			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = DoubleJumpSmokeState::Dead;
		}
	}

	void DoubleJumpSmoke::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}