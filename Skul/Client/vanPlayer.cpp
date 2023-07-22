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
	{
		animator = AddComponent<Animator>();
		MakeAnimation();
	}

	Player::Player(math::Vector2 _offset)
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Left)
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

		// StillSameState();

		// z : Dash, x : Attack , c : Jump
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
			, math::Vector2(53.0f, 57.0f)
			, 5
			, _offset);
		// Attack_A_R
		texture = ResourceManager::Load<Texture>(L"Attack_A_R"
			, L"..\\MyResources\\skul\\11_Skul\\Attack_A_R\\Attack_A_R.bmp");
		animator->CreateAnimation(L"Attack_A_R"
			, texture
			, math::Vector2::Zero
			, math::Vector2(53.0f, 57.0f)
			, 5
			, _offset);

		// Attack_A_L
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

		animator->Reset();	// animator 세팅 최기화
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
			break;
		case van::Player::PlayerState::Idle:
			break;
		default:
			break;
		}

		mState = _state;

		// 특정 상태에 들어갈 때 벌어져야 한다면 여기서 특정함수 호출
		switch (_state)
		{
		case van::Player::PlayerState::Walk:

			break;
		case van::Player::PlayerState::Idle:

			break;
		default:
			break;
		}
	}

	void Player::StillSameState()
	{
		// 해당 상태일 때 또 뭘 해줘야 하면 여기서 특정함수 호출
		switch (mState)
		{
		case van::Player::PlayerState::Walk:

			break;
		case van::Player::PlayerState::Idle:

			break;
		default:
			break;
		}
	}
	
	void Player::Idle()
	{
		if (Input::GetKey(eKeyCode::Up))
		{
			// nothing
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			animator->PlayAnimation(L"Walk_Weapon_L", true);
			ChangeState(PlayerState::Walk);
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			animator->PlayAnimation(L"Walk_Weapon_R", true);
			ChangeState(PlayerState::Walk);
		}

		if (Input::GetKey(eKeyCode::Z))
		{

		}
		if (Input::GetKey(eKeyCode::X))
		{

		}
		if (Input::GetKey(eKeyCode::C))
		{

		}
	}
	
	void Player::Walk()
	{
		// 위치 변경
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::Up))
		{
			// nothing
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= SPEED * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += SPEED * Time::DeltaTime();
		}

		// 애니메이션 변경
		if (Input::GetKey(eKeyCode::Up))
		{
			// nothing
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			// nothing
		}
		if (Input::GetKeyUp(eKeyCode::Left))
		{
			animator->PlayAnimation(L"Idle_Weapon_L", true);
			mState = PlayerState::Idle;
		}
		if(Input::GetKeyUp(eKeyCode::Right))
		{
			animator->PlayAnimation(L"Idle_Weapon_R", true);
			mState = PlayerState::Idle;
		}

		tr->SetPosition(pos);
	}
}