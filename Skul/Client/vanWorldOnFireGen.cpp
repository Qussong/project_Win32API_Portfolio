#include "vanWorldOnFireGen.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

namespace van
{
	WorldOnFireGen::WorldOnFireGen()
	{
		// nothing
	}

	WorldOnFireGen::~WorldOnFireGen()
	{
		// nothing
	}

	void WorldOnFireGen::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = WorldOnFireGenEffectState::Gen;
	}

	void WorldOnFireGen::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case WorldOnFireGenEffectState::Gen:
			Gen();
			break;
		case WorldOnFireGenEffectState::Active:
			Active();
			break;
		case WorldOnFireGenEffectState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void WorldOnFireGen::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void WorldOnFireGen::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"WorldOnFire_Orb_Gen_Effect", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_Orb_Gen_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(159.0f, 161.0f), 24, math::Vector2::Zero, 0.06F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void WorldOnFireGen::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireGen::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireGen::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireGen::Gen()
	{
		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			mState = WorldOnFireGenEffectState::Active;
		}
	}

	void WorldOnFireGen::Active()
	{
		GameObject* owner = GetOwner();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = owner->GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 0.0f));
			at->PlayAnimation(L"WorldOnFire_Orb_Gen_Effect", false);

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = WorldOnFireGenEffectState::Dead;
		}
	}

	void WorldOnFireGen::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}
