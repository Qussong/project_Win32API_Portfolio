#include "vanEnergyBombCharge.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	EnergyBombCharge::EnergyBombCharge()
	{
		// nothing
	}

	EnergyBombCharge::~EnergyBombCharge()
	{
		// nothing
	}

	void EnergyBombCharge::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = EnergyBombChargeState::Gen;
	}

	void EnergyBombCharge::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case EnergyBombChargeState::Gen:
			Gen();
			break;
		case EnergyBombChargeState::Active:
			Active();
			break;
		case EnergyBombChargeState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void EnergyBombCharge::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void EnergyBombCharge::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Yggdrasill_EnergyBomb_Charge", ResourceManager::Find<Texture>(L"Yggdrasill_EnergyBomb_Charge"), math::Vector2(0.0f, 0.0f), math::Vector2(299.0f, 302.0f), 47, math::Vector2::Zero, 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void EnergyBombCharge::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void EnergyBombCharge::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void EnergyBombCharge::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void EnergyBombCharge::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = EnergyBombChargeState::Active;
		}
	}

	void EnergyBombCharge::Active()
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
			mState = EnergyBombChargeState::Dead;
		}
	}

	void EnergyBombCharge::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}