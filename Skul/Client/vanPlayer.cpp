#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()에서 Player 객체의 위치 옮겨준다. 때문에 Transform 객체의 값을 수정할 수 있어야 한다.

#include "vanAnimator.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Player::Player()
		: mState(PlayerState::None)
		, mDirection(PlayerDirection::None)
		, mbDoubleKey(false)
	{
		animator = AddComponent<Animator>();
		MakeAnimation();
	}

	Player::Player(math::Vector2 _offset)
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Left)
		, mbDoubleKey(false)
	{
		animator = AddComponent<Animator>();
		MakeAnimation(_offset);
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

		 StillSameState();

		// z : Dash, x : Attack , c : Jump
		switch (mState)
		{
		case Player::PlayerState::Idle:
			Idle();
			break;
		case Player::PlayerState::Walk:
			Walk();
			break;
		case Player::PlayerState::Attack:
			Attack();
			break;
		case Player::PlayerState::Jump:
			Jump();
			break;
		case Player::PlayerState::Dash:
			Dash();
			break;
		default:
			__noop;
			break;
		}
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Player::ChangeState(PlayerState _state)
	{
		if (_state == mState)
		{
			return;
		}

		// 상태에서 빠져나갈 때 무언가 벌어져야 한다면... 여기서 특정함수 호출
		switch (mState)
		{
		case van::Player::PlayerState::Walk:
		{
			break;
		}
		case van::Player::PlayerState::Idle:
		{
			break;
		}
		default:
			break;
		}

		mState = _state;

		// 특정 상태에 들어갈 때 벌어져야 한다면 여기서 특정함수 호출
		switch (_state)
		{
		case van::Player::PlayerState::Walk:
		{
			break;
		}
		case van::Player::PlayerState::Idle:
		{
			break;
		}
		default:
			break;
		}
	}

	void Player::MakeAnimation(math::Vector2 _offset)
	{
		//math::Vector2 offset = math::Vector2(0.0f, 70.0f);

		// Idle_L
		Texture* texture = ResourceManager::Load<Texture>(L"Idle_Weapon_L"
			, L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_L\\Idle_Weapon_L.bmp");
		animator->CreateAnimation(L"Idle_Weapon_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(44.0f, 37.0f)
			, 4
			, _offset);
		// Idle_R
		texture = ResourceManager::Load<Texture>(L"Idle_Weapon_R"
			, L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_R\\Idle_Weapon_R.bmp");
		animator->CreateAnimation(L"Idle_Weapon_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(44.0f, 37.0f)
			, 4
			, _offset);

		// Walk_Weapon_L
		texture = ResourceManager::Load<Texture>(L"Walk_Weapon_L"
			, L"..\\MyResources\\skul\\11_Skul\\Walk_Weapon_L\\Walk_Weapon_L.bmp");
		animator->CreateAnimation(L"Walk_Weapon_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(44.0f, 36.0f)
			, 8
			, _offset);
		// Walk_Weapon_R
		texture = ResourceManager::Load<Texture>(L"Walk_Weapon_R"
			, L"..\\MyResources\\skul\\11_Skul\\Walk_Weapon_R\\Walk_Weapon_R.bmp");
		animator->CreateAnimation(L"Walk_Weapon_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(44.0f, 36.0f)
			, 8
			, _offset);

		// Attack_A_L
		texture = ResourceManager::Load<Texture>(L"Attack_A_L"
			, L"..\\MyResources\\skul\\11_Skul\\Attack_A_L\\Attack_A_L.bmp");
		animator->CreateAnimation(L"Attack_A_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(63.0f, 65.0f)
			, 5
			, _offset);
		// Attack_A_R
		texture = ResourceManager::Load<Texture>(L"Attack_A_R"
			, L"..\\MyResources\\skul\\11_Skul\\Attack_A_R\\Attack_A_R.bmp");
		animator->CreateAnimation(L"Attack_A_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(63.0f, 65.0f)	// pos.y = 57->65
			, 5
			, _offset);

		// Attack_B_L
		texture = ResourceManager::Load<Texture>(L"Attack_B_L"
			, L"..\\MyResources\\skul\\11_Skul\\Attack_B_L\\Attack_B_L.bmp");
		animator->CreateAnimation(L"Attack_B_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(62.0f, 59.0f)
			, 4
			, _offset);
		// Attack_B_R
		texture = ResourceManager::Load<Texture>(L"Attack_B_R"
			, L"..\\MyResources\\skul\\11_Skul\\Attack_B_R\\Attack_B_R.bmp");
		animator->CreateAnimation(L"Attack_B_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(62.0f, 59.0f)
			, 4
			, _offset);
		
		// Jump_L
		texture = ResourceManager::Load<Texture>(L"Jump_L"
			, L"..\\MyResources\\skul\\11_Skul\\Jump_L\\Jump_L.bmp");
		animator->CreateAnimation(L"Jump_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(22.0f, 36.0f)
			, 2
			, _offset);
		// Jump_R
		texture = ResourceManager::Load<Texture>(L"Jump_R"
			, L"..\\MyResources\\skul\\11_Skul\\Jump_R\\Jump_R.bmp");
		animator->CreateAnimation(L"Jump_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(22.0f, 36.0f)
			, 2
			, _offset);

		// Jump_Attack_L
		texture = ResourceManager::Load<Texture>(L"Jump_Attack_L"
			, L"..\\MyResources\\skul\\11_Skul\\Jump_Attack_L\\Jump_Attack_L.bmp");
		animator->CreateAnimation(L"Jump_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(61.0f, 57.0f)
			, 4
			, _offset);
		// Jump_Attack_R
		texture = ResourceManager::Load<Texture>(L"Jump_Attack_R"
			, L"..\\MyResources\\skul\\11_Skul\\Jump_Attack_R\\Jump_Attack_R.bmp");
		animator->CreateAnimation(L"Jump_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(61.0f, 57.0f)
			, 4
			, _offset);

		// Dash_L
		texture = ResourceManager::Load<Texture>(L"Dash_L"
			, L"..\\MyResources\\skul\\11_Skul\\Dash_L\\Dash_L.bmp");
		animator->CreateAnimation(L"Dash_L"
			, texture
			, math::Vector2::Zero
			, math::Vector2(78.0f, 28.0f)
			, 4
			, _offset);
		// Dash_R
		texture = ResourceManager::Load<Texture>(L"Dash_R"
			, L"..\\MyResources\\skul\\11_Skul\\Dash_R\\Dash_R.bmp");
		animator->CreateAnimation(L"Dash_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(78.0f, 28.0f)
			, 4
			, _offset);

		animator->Reset();	// animator 세팅 최기화
	}

	void Player::StillSameState()
	{
		// 해당 상태일 때 또 뭘 해줘야 하면 여기서 특정함수 호출
		switch (mState)
		{
		case van::Player::PlayerState::Walk:
		{

			break;
		}
		case van::Player::PlayerState::Idle:
		{

			break;
		}
		case van::Player::PlayerState::Jump:
		{

			break;
		}
		case van::Player::PlayerState::Attack:
		{

			break;
		}
		default:
			break;
		}
	}

	void Player::Idle()
	{
		/*if(mDirection == PlayerDirection::Left)
			animator->PlayAnimation(L"Idle_Weapon_L", true);
		if (mDirection == PlayerDirection::Right)
			animator->PlayAnimation(L"Idle_Weapon_R", true);*/

		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}

		// Walk_L
		if (Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			if (!mbDoubleKey)
			{
				animator->PlayAnimation(L"Walk_Weapon_L", true);
				ChangeState(PlayerState::Walk);
			}
		}
		// Walk_R
		if (Input::GetKey(eKeyCode::Right) && !Input::GetKey(eKeyCode::Left))
		{
			if (!mbDoubleKey)
			{
				animator->PlayAnimation(L"Walk_Weapon_R", true);
				ChangeState(PlayerState::Walk);
			}
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::C))
		{
			if (mDirection == PlayerDirection::Left)
			{
				animator->PlayAnimation(L"Jump_L", true);
				ChangeState(PlayerState::Jump);
			}
			else if (mDirection == PlayerDirection::Right)
			{
				animator->PlayAnimation(L"Jump_R", true);
				ChangeState(PlayerState::Jump);
			}
		}

		// Attack
		if (Input::GetKeyDown(eKeyCode::X))
		{
			ChangeState(PlayerState::Attack);
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			ChangeState(PlayerState::Dash);
		}

		// 동시키 입력 해제
		if (mbDoubleKey)
		{
			if (Input::GetKeyUp(eKeyCode::Right))
			{
				animator->PlayAnimation(L"Walk_Weapon_L", true);
				ChangeState(PlayerState::Walk);
				mbDoubleKey = false;
			}
			if (Input::GetKeyUp(eKeyCode::Left))
			{
				animator->PlayAnimation(L"Walk_Weapon_R", true);
				ChangeState(PlayerState::Walk);
				mbDoubleKey = false;
			}
		}
	}

	void Player::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Down) && Input::GetKey(eKeyCode::C))
		{
			// 아래점프
		}
		
		// Walk_Right
		if (Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= SPEED * Time::DeltaTime();
			mDirection = PlayerDirection::Left;
		}
		// Walk_Left
		if (Input::GetKey(eKeyCode::Right) && !Input::GetKey(eKeyCode::Left))
		{
			pos.x += SPEED * Time::DeltaTime();
			mDirection = PlayerDirection::Right;
		}

		// 동시입력(방향키)
		if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
		{
			if (!mbDoubleKey)
			{
				if (mDirection == PlayerDirection::Right)
				{
					animator->PlayAnimation(L"Idle_Weapon_R", true);
					mState = PlayerState::Idle;
				}
				if (mDirection == PlayerDirection::Left)
				{
					animator->PlayAnimation(L"Idle_Weapon_L", true);
					mState = PlayerState::Idle;
				}
				mbDoubleKey = true;
			}
		}

		// Attack
		/*if (Input::GetKeyDown(eKeyCode::X))
		{
			ChangeState(PlayerState::Attack);
		}*/

		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}
		// Walk_Right
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			animator->PlayAnimation(L"Idle_Weapon_R", true);
			mState = PlayerState::Idle;
		}
		// Walk_Right
		if (Input::GetKeyUp(eKeyCode::Left))
		{
			animator->PlayAnimation(L"Idle_Weapon_L", true);
			mState = PlayerState::Idle;
		}

		tr->SetPosition(pos);
	}

	void Player::Jump()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos.y -= 100.0f;
		tr->SetPosition(pos);
		ChangeState(PlayerState::Idle);
	}

	void Player::Attack()
	{
		if (mDirection == PlayerDirection::Left)
		{
			animator->PlayAnimation(L"Attack_A_L", false);
			ChangeState(PlayerState::Idle);
		}
		if (mDirection == PlayerDirection::Right)
		{
			animator->PlayAnimation(L"Attack_A_R", false);
			ChangeState(PlayerState::Idle);
		}
	}

	void Player::Dash()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		if (mDirection == PlayerDirection::Left)
		{
			animator->PlayAnimation(L"Dash_L");
			//pos.x -= 200.0f;
			tr->SetPosition(pos);
			ChangeState(PlayerState::Idle);
		}
		if (mDirection == PlayerDirection::Right)
		{
			//pos.x += 200.0f;
			tr->SetPosition(pos);
			ChangeState(PlayerState::Idle);
			animator->PlayAnimation(L"Dash_R");
		}
	}
}