#include "vanExplosionEffect.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	ExplosionEffect::ExplosionEffect()
	{
		// nothing
	}

	ExplosionEffect::~ExplosionEffect()
	{
		// nothing
	}

	void ExplosionEffect::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = ExplosionEffectState::Gen;
	}

	void ExplosionEffect::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case ExplosionEffectState::Gen:
			Gen();
			break;
		case ExplosionEffectState::Active:
			Active();
			break;
		case ExplosionEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void ExplosionEffect::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void ExplosionEffect::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Explosion_Effect", ResourceManager::Find<Texture>(L"Mage_Explosion_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(88.0f, 116.0f), 30, math::Vector2::Zero, 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void ExplosionEffect::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void ExplosionEffect::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void ExplosionEffect::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void ExplosionEffect::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));

			mState = ExplosionEffectState::Active;
		}
	}

	void ExplosionEffect::Active()
	{
		GameObject* owner = GetOwner();
		//Transform* tr = GetComponent<Transform>();
		//Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			//tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			at->PlayAnimation(L"Explosion_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = ExplosionEffectState::Dead;
		}
	}

	void ExplosionEffect::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}