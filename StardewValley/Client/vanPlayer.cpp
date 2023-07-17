#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()에서 Player 객체의 위치 옮겨준다. 때문에 Transform 객체의 값을 수정할 수 있어야 한다.
#include "vanAnimator.h"

namespace van
{
	Player::Player()
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

		// Player 객체의 위치 수정
		
		// 1. Player 객체의 Tranfer Component로 현재 위치값 얻어온다.
		Transform* tr = GetComponent<Transform>();	
		math::Vector2 pos = tr->GetPosition();
		Animator* ani = GetComponent<Animator>();

		// 2. 키 입력을 받아 위치값 수정
		if (Input::GetKey(eKeyCode::W))	// top
		{
			ani->PlayAnimation(L"Skul_Idle_Weapon", true);
			pos.y -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S))	// down
		{
			ani->PlayAnimation(L"Skul_Idle_Weapon", true);
			pos.y += SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::A))	// left
		{
			ani->PlayAnimation(L"Skul_Walk_Left", true);
			pos.x -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))	// right
		{
			ani->PlayAnimation(L"Skul_Walk_Right", true);
			pos.x += SPEED * Time::DeltaTime();
		}

		// 3. 수정된 위치값을 Transfer Component에 넣어준다.
		tr->SetPosition(pos);
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}