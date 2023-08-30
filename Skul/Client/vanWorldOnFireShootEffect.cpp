#include "vanWorldOnFireShootEffect.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	WorldOnFireShootEffect::WorldOnFireShootEffect()
	{
		// nothing
	}

	WorldOnFireShootEffect::~WorldOnFireShootEffect()
	{
		// nothing
	}

	void WorldOnFireShootEffect::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = WorldOnFireShootEffectState::Gen;
	}

	void WorldOnFireShootEffect::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case WorldOnFireShootEffectState::Gen:
			Gen();
			break;
		case WorldOnFireShootEffectState::Active:
			Active();
			break;
		case WorldOnFireShootEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void WorldOnFireShootEffect::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void WorldOnFireShootEffect::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"WorldOnFire_FireBall_Shoot_Effect", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_FireBall_Shoot_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(181.0f, 182.0f), 21, math::Vector2::Zero, 0.06F);
		at->SetScale(math::Vector2(3.0f, 3.0f));
	}

	void WorldOnFireShootEffect::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireShootEffect::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireShootEffect::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireShootEffect::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = WorldOnFireShootEffectState::Active;
		}
	}

	void WorldOnFireShootEffect::Active()
	{
		GameObject* owner = GetOwner();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			at->PlayAnimation(L"WorldOnFire_FireBall_Shoot_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = WorldOnFireShootEffectState::Dead;
		}
	}

	void WorldOnFireShootEffect::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}