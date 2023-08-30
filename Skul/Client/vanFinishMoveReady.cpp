#include "vanFinishMoveReady.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"
#include "vanMage.h"

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

		at->CreateAnimation(L"FinishMove_Charge_Effect", ResourceManager::Find<Texture>(L"Mage_FinishMove_Charge_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(142.0f, 98.0f), 22, math::Vector2::Zero, 0.06F);
		at->CreateAnimation(L"FinishMove_Charge_Finish_Effect", ResourceManager::Find<Texture>(L"Mage_FinishMove_Charge_Finish_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(400.0f, 236.0f), 14, math::Vector2::Zero, 0.06F);
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
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();
		GameObject* owner = GetOwner();

		if (owner == nullptr)
		{
			// nothing
		}
		else
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			at->PlayAnimation(L"FinishMove_Charge_Effect", true);

			mState = FinishMoveReadyState::Active;
		}
	}

	void FinishMoveReady::Active()
	{
		GameObject* owner = GetOwner();
		Mage* mage = dynamic_cast<Mage*>(owner);
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mage->GetFinishMoveChargeFlag() == true)
		{
			if (mbPlayAnimation == true)
			{
				at->PlayAnimation(L"FinishMove_Charge_Finish_Effect", false);
				mbPlayAnimation = false;
			}

			if (at->IsActiveAnimationComplete() == true)
			{
				mage->SetFinishMoveEffectFinishFlag(true);	// Mageø° Effect∞° ≥°≥µ¿Ω¿ª æÀ∑¡¡ÿ¥Ÿ.
				mState = FinishMoveReadyState::Dead;
			}
		}
	}

	void FinishMoveReady::Dead()
	{
		// ∞¥√º º“∏Í
		Destroy(this);
	}
}