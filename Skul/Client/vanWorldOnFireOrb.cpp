#include "vanWorldOnFireOrb.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	WorldOnFireOrb::WorldOnFireOrb()
	{
		// nothing
	}

	WorldOnFireOrb::~WorldOnFireOrb()
	{
		// nothing
	}

	void WorldOnFireOrb::Init()
	{
		Skill::Init();
		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(120.0f, 120.0f));

		mState = OrbState::Gen;
	}

	void WorldOnFireOrb::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case OrbState::Gen:
			Gen();
			break;
		case OrbState::Active:
			Active();
			break;
		case OrbState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void WorldOnFireOrb::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void WorldOnFireOrb::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"WorldOnFire_Orb_Object", ResourceManager::Find<Texture>(L"Mage_WorldOnFire_Orb_Object"), math::Vector2(0.0f, 0.0f), math::Vector2(120.0f, 122.0f), 50);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void WorldOnFireOrb::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void WorldOnFireOrb::Gen()
	{
		Animator* at = GetComponent<Animator>();
		GameObject* owner = GetOwner();

		if (owner != nullptr)
		{
			// GenEffect 애니메이션 출력
			at->PlayAnimation(L"WorldOnFire_Orb_Object", true);
			mState = OrbState::Active;
		}
	}

	void WorldOnFireOrb::Active()
	{
		// FireBall 2발 발사
		
		// FireBall 발사할때마다 FireBall Shoot Effect 출력

	}

	void WorldOnFireOrb::Dead()
	{
		// EnergyBomb 객체 소멸
		Destroy(this);
	}
}