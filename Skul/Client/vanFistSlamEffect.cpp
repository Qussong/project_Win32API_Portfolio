#include "vanFistSlamEffect.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	FistSlamEffect::FistSlamEffect()
	{
		// nothing
	}

	FistSlamEffect::~FistSlamEffect()
	{
		// nothing
	}

	void FistSlamEffect::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = FistSlamEffectState::Gen;
	}

	void FistSlamEffect::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case FistSlamEffectState::Gen:
			Gen();
			break;
		case FistSlamEffectState::Active:
			Active();
			break;
		case FistSlamEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void FistSlamEffect::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void FistSlamEffect::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"FistSlam_Effect", ResourceManager::Find<Texture>(L"Yggdrasill_FistSlam_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(415.0f, 260.0f), 28, math::Vector2(0.0f, -35.0f), 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void FistSlamEffect::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void FistSlamEffect::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void FistSlamEffect::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void FistSlamEffect::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));

			mState = FistSlamEffectState::Active;
		}
	}

	void FistSlamEffect::Active()
	{
		GameObject* owner = GetOwner();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			at->PlayAnimation(L"FistSlam_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = FistSlamEffectState::Dead;
		}
	}

	void FistSlamEffect::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}