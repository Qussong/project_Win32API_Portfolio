#include "vanFinishMoveReady.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	FinishMoveReady::FinishMoveReady()
	{
		// nothing
	}

	FinishMoveReady::~FinishMoveReady()
	{
		// nothing
	}

	void FinishMoveReady::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = FinishMoveReadyState::Gen;
	}

	void FinishMoveReady::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case FinishMoveReadyState::Gen:
			Gen();
			break;
		case FinishMoveReadyState::Active:
			Active();
			break;
		case FinishMoveReadyState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void FinishMoveReady::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void FinishMoveReady::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		//at->CreateAnimation(L"Yggdrasill_EnergyBomb_Charge", ResourceManager::Find<Texture>(L"Yggdrasill_EnergyBomb_Charge"), math::Vector2(0.0f, 0.0f), math::Vector2(299.0f, 302.0f), 47, math::Vector2::Zero, 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void FinishMoveReady::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void FinishMoveReady::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void FinishMoveReady::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void FinishMoveReady::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = FinishMoveReadyState::Active;
		}
	}

	void FinishMoveReady::Active()
	{
		GameObject* owner = GetOwner();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(10.0f, 0.0f));
			at->PlayAnimation(L"Yggdrasill_EnergyBomb_Charge", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mbChargeFinish = true;
			mState = FinishMoveReadyState::Dead;
		}
	}

	void FinishMoveReady::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}