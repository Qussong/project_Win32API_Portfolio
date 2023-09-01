#include "vanMagicOrbEffect.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	MagicOrbEffect::MagicOrbEffect()
	{
		// nothing
	}

	MagicOrbEffect::~MagicOrbEffect()
	{
		// nothing
	}

	void MagicOrbEffect::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = MagicOrbEffectState::Gen;
	}

	void MagicOrbEffect::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case MagicOrbEffectState::Gen:
			Gen();
			break;
		case MagicOrbEffectState::Active:
			Active();
			break;
		case MagicOrbEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void MagicOrbEffect::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void MagicOrbEffect::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"MagicOrb_Effect", ResourceManager::Find<Texture>(L"Yggdrasill_MagicOrb_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(428.0f, 222.0f), 37, math::Vector2(0.0f, -30.0f), 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void MagicOrbEffect::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MagicOrbEffect::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void MagicOrbEffect::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void MagicOrbEffect::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));

			mState = MagicOrbEffectState::Active;
		}
	}

	void MagicOrbEffect::Active()
	{
		GameObject* owner = GetOwner();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			at->PlayAnimation(L"MagicOrb_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = MagicOrbEffectState::Dead;
		}
	}

	void MagicOrbEffect::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}