#include "vanPhoenixLanding.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"
#include "vanMage.h"

#define DAMAGE			25.0f

namespace van
{
	PhoenixLanding::PhoenixLanding()
	{
		// nothing
	}

	PhoenixLanding::~PhoenixLanding()
	{
		// nothing
	}

	void PhoenixLanding::Init()
	{
		Skill::Init();
		mState = PhoenixLandingState::Wait;
	}

	void PhoenixLanding::Update()
	{
		Skill::Update();

		MakeAnimation();

		switch (mState)
		{
		case PhoenixLandingState::Wait:
			Wait();
			break;
		case PhoenixLandingState::LandingReady:
			LandingReady();
			break;
		default:
			__noop;
		}
	}

	void PhoenixLanding::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void PhoenixLanding::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		
		at->CreateAnimation(L"Attack_Ready_Effect_PhoenixLanding", ResourceManager::Find<Texture>(L"Mage_PhoenixRanding_Ready_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(62.0f, 109.0f), 16, math::Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"Attack_Effect_PhoenixLanding", ResourceManager::Find<Texture>(L"Mage_PhoenixRanding_Land_Effect"), math::Vector2(0.0f, 0.0f), math::Vector2(149.0f, 135.0f), 41, math::Vector2(0.0f, 0.0f));

		int a = 0;
	}

	void PhoenixLanding::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr
			&& (mState == PhoenixLandingState::LandingReadyEnd
				|| mState == PhoenixLandingState::Landing))
		{
			// 플레이어에게 데미지를 준다 or 플레이어에게 맞았음을 알려준다.
		}
	}

	void PhoenixLanding::OnCollisionStay(Collider* _other)
	{

	}

	void PhoenixLanding::OnCollisionExit(Collider* _other)
	{

	}

	void PhoenixLanding::Wait()
	{
		// nothing
	}

	void PhoenixLanding::LandingReady()
	{

	}

	void PhoenixLanding::LandingReadyEnd()
	{

	}

	void PhoenixLanding::Landing()
	{

	}

	void PhoenixLanding::LandingEnd()
	{

	}
}