#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()에서 Player 객체의 위치 옮겨준다. 때문에 Transform 객체의 값을 수정할 수 있어야 한다.
#include "vanAnimator.h"

namespace van
{
	Player::Player()
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Left)
	{
		// nothing
	}

	Player::~Player()
	{
		// nothing
	}

	void Player::Init()
	{
		// nothing
	}

	void Player::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case Player::PlayerState::Walk:
			Walk();
			break;
		case Player::PlayerState::Idle:
			Idle();
			break;
		default:
			break;
		}
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Player::Idle()
	{
		// Skul_Walk_Left
		// Skul_Walk_Right
		Animator* animator = GetComponent<Animator>();
		
		if (Input::GetKey(eKeyCode::A))
		{
			animator->PlayAnimation(L"Skul_Walk_Left", true);
			mState = PlayerState::Walk;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			animator->PlayAnimation(L"Skul_Walk_Right", true);
			mState = PlayerState::Walk;
		}
	}

	void Player::Walk()
	{
		// Idle_Left
		// Idle_Right
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= SPEED * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			animator->PlayAnimation(L"Idle_Left", true);
			mState = PlayerState::Idle;
		}
		if(Input::GetKeyUp(eKeyCode::D))
		{
			animator->PlayAnimation(L"Idle_Right", true);
			mState = PlayerState::Idle;
		}

		tr->SetPosition(pos);
	}
}