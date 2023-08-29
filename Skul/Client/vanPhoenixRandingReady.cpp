#include "vanPhoenixRandingReady.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	PhoenixRandingReady::PhoenixRandingReady()
	{
		// nothing
	}

	PhoenixRandingReady::~PhoenixRandingReady()
	{
		// nothing
	}

	void PhoenixRandingReady::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = PhoenixRandingReadyState::Gen;
	}

	void PhoenixRandingReady::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case PhoenixRandingReadyState::Gen:
			Gen();
			break;
		case PhoenixRandingReadyState::Active:
			Active();
			break;
		case PhoenixRandingReadyState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void PhoenixRandingReady::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void PhoenixRandingReady::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Mage_PhoenixRanding_Ready_Effect", ResourceManager::Find<Texture>(L"Mage_PhoenixRanding_Ready_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(92.0f, 97.0f), 16, math::Vector2::Zero, 0.03F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void PhoenixRandingReady::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void PhoenixRandingReady::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void PhoenixRandingReady::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void PhoenixRandingReady::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = PhoenixRandingReadyState::Active;
		}
	}

	void PhoenixRandingReady::Active()
	{
		GameObject* owner = GetOwner();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			at->PlayAnimation(L"Mage_PhoenixRanding_Ready_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mbEffectFinish = true;
			mState = PhoenixRandingReadyState::Dead;
		}
	}

	void PhoenixRandingReady::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}