#include "vanDashSmoke.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"
#include "vanPlayer.h"

namespace van
{
	DashSmoke::DashSmoke()
	{
		// nothing
	}

	DashSmoke::~DashSmoke()
	{
		// nothing
	}

	void DashSmoke::Init()
	{
		Skill::Init();
		MakeAnimation();

		mState = DashSmokeState::Gen;
	}

	void DashSmoke::Update()
	{
		Skill::Update();

		switch (mState)
		{
		case DashSmokeState::Gen:
			Gen();
			break;
		case DashSmokeState::Active:
			Active();
			break;
		case DashSmokeState::Dead:
			Dead();
			break;
		default:
			__noop;
		}
	}

	void DashSmoke::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void DashSmoke::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Dash_Smoke_L", ResourceManager::Find<Texture>(L"Dash_Smoke_L"), math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 27.0f), 4, math::Vector2(0.0f, 0.0f), 0.1F);
		at->CreateAnimation(L"Dash_Smoke_R", ResourceManager::Find<Texture>(L"Dash_Smoke_R"), math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 27.0f), 4, math::Vector2(0.0f, 0.0f), 0.1F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void DashSmoke::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void DashSmoke::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void DashSmoke::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void DashSmoke::Gen()
	{
		Transform* tr = GetComponent<Transform>();

		GameObject* owner = GetOwner();
		if (owner != nullptr)
		{
			Transform* tr_owner = owner->GetComponent<Transform>();
			tr->SetPosition(tr_owner->GetPosition() + math::Vector2(0.0f, 5.0f));

			mState = DashSmokeState::Active;
		}
	}

	void DashSmoke::Active()
	{
		GameObject* owner = GetOwner();
		Player* player = dynamic_cast<Player*>(owner);
		Animator* at = GetComponent<Animator>();

		if (mbSetFlag == false)
		{
			if (player->GetPlayerDirection() == Player::PlayerDirection::Left)
			{
				at->PlayAnimation(L"Dash_Smoke_L", false);
			}
			if (player->GetPlayerDirection() == Player::PlayerDirection::Right)
			{
				at->PlayAnimation(L"Dash_Smoke_R", false);
			}

			mbSetFlag = true;
		}

		if (mbSetFlag == true
			&& at->IsActiveAnimationComplete() == true)
		{
			mbSetFlag = false;
			mState = DashSmokeState::Dead;
		}
	}

	void DashSmoke::Dead()
	{
		// °´Ã¼ ¼Ò¸ê
		Destroy(this);
	}
}