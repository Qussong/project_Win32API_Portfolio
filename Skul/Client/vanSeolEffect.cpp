#include "vanSeolEffect.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	SeolEffect::SeolEffect()
	{
		// nothing
	}

	SeolEffect::~SeolEffect()
	{
		// nothing
	}

	void SeolEffect::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = SeolEffectState::Gen;
	}

	void SeolEffect::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case SeolEffectState::Gen:
			Gen();
			break;
		case SeolEffectState::Active:
			Active();
			break;
		case SeolEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void SeolEffect::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void SeolEffect::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Seol_Effect", ResourceManager::Find<Texture>(L"Cat_Seol_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(45.0f, 43.0f), 27, math::Vector2(0.0f, -15.0f), 0.06F);
		//at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void SeolEffect::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void SeolEffect::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void SeolEffect::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void SeolEffect::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));

			mState = SeolEffectState::Active;
		}
	}

	void SeolEffect::Active()
	{
		GameObject* owner = GetOwner();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			at->PlayAnimation(L"Seol_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = SeolEffectState::Dead;
		}
	}

	void SeolEffect::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}