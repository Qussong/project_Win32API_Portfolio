#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanCollider.h"
#include "vanFloor.h"
#include "vanTime.h"
#include "vanPlayerAttack.h"
#include "vanCollisionManager.h"
#include "vanSkull.h"
#include "vanSound.h"
#include "vanHitSign.h"
#include "vanDashSmoke.h"
#include "vanDoubleJumpSmoke.h"

#define DASH_FORCE_X		700.0f
#define DASH_LIMIT			180.0f
#define JUMP_FORCE_Y		950.0f
#define WALK_SPEED			300.0f
#define HEAD_SPEED			900.0f
#define SKILL_COOL_TIME		5.0f
#define SKILL_HEAD_TIME		4.0f

#define HIT_BUMP_X			200.0f

// Z : Dash / X : Attack / C : Jump
namespace van
{
	Player::Player()
		: mState(PlayerState::Idle)
		, mDirection(PlayerDirection::Right)
		, mbDoubleKey(false)
		, mJumpCnt(0)
		, mDashCnt(0)
		, mbCombo(false)
		, mbAttackMove(false)
		, mbAttackMove2(false)
		, attackBox(nullptr)
		, mHp(100.0f)
		, mCoin(0.0f)
		, mBone(0.0f)
		, mJewelry(0.0f)
		, mbSkullLess(false)
		, mbSkillFlag(false)
		, mHeadTime(0.0f)
		, mCoolTime(SKILL_COOL_TIME)
		, head(nullptr)
	{
		AddComponent<RigidBody>()->SetMass(50.0f);
		mDashSound = ResourceManager::Load<Sound>(L"Dash", L"..\\MyResources\\skul\\Sound\\Skul_Dash.wav");
		mJumpSound = ResourceManager::Load<Sound>(L"Jump", L"..\\MyResources\\skul\\Sound\\Skul_Jump.wav");
		mDoubleJumpSound = ResourceManager::Load<Sound>(L"DoubleJump", L"..\\MyResources\\skul\\Sound\\Skul_Double_Jump.wav");
		mLandingSound = ResourceManager::Load<Sound>(L"DoubleJump", L"..\\MyResources\\skul\\Sound\\Skul_Landing.wav");
		mAttackASound = ResourceManager::Load<Sound>(L"AttackA", L"..\\MyResources\\skul\\Sound\\Skul_AttackA.wav");
		mAttackBSound = ResourceManager::Load<Sound>(L"AttackB", L"..\\MyResources\\skul\\Sound\\Skul_AttackB.wav");
		mJumpAttackSound = ResourceManager::Load<Sound>(L"JumpAttack", L"..\\MyResources\\skul\\Sound\\Skul_Jump_Attack.wav");
		mSkullThrowingSound = ResourceManager::Load<Sound>(L"JumpAttack", L"..\\MyResources\\skul\\Sound\\Skul_SkullThrowing.wav");
	}

	Player::~Player()
	{
		// nothing
	}

	void Player::Init()
	{
		MakeAnimation();

		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Idle_R", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(50.0f, 70.0f));

		attackBox = Object::Instantiate<PlayerAttack>(enums::eLayerType::Range_Attack);	// PlayerAttack 클래스 객체 생성
		attackBox->SetOwner(this);														// PlayerAttack 클래스의 소유자 설정
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(50.0f, 70.0f));		// PlayerAttack 클래스의 충돌체 크기 설정

		mHitSign = Object::Instantiate<HitSign>(enums::eLayerType::UI_HitSign);
	}

	void Player::Update()
	{
		GameObject::Update();

		Skill();

		if (mState == PlayerState::Hit)
		{
			Hit();
		}
		else
		{
			mPasteState = mState;

			switch (mState)
			{
			case Player::PlayerState::Idle:
				Idle();
				break;
			case Player::PlayerState::Walk:
				Walk();
				break;
			case Player::PlayerState::Jump:
				Jump();
				break;
			case Player::PlayerState::Dash:
				Dash();
				break;
			case Player::PlayerState::AttackA:
				AttackA();
				break;
			case Player::PlayerState::AttackB:
				AttackB();
				break;
			case Player::PlayerState::JumpAttack:
				JumpAttack();
				break;
			case Player::PlayerState::DoubleJump:
				DoubleJump();
				break;
			case Player::PlayerState::DoubleDash:
				DoubleDash();
				break;
			case Player::PlayerState::Fall:
				Fall();
				break;
			default:
				__noop;
			}
		}

		if (mPasteState != mState)
		{
			mbPlayAnimation = true;
		}
		
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
		ShowStatus(_hdc);
	}

	void Player::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Player::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Player::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Player::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();
		math::Vector2 offset = GetOffset();	// 기본값 math::Vector2::Zero
		// Head
		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"Idle_L"), math::Vector2::Zero, math::Vector2(44.0f, 37.0f), 4, offset);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"Idle_R"), math::Vector2::Zero, math::Vector2(44.0f, 37.0f), 4, offset);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"Walk_L"), math::Vector2::Zero, math::Vector2(44.0f, 36.0f), 8, offset);
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"Walk_R"), math::Vector2::Zero, math::Vector2(44.0f, 36.0f), 8, offset);
		animator->CreateAnimation(L"AttackA_L", ResourceManager::Find<Texture>(L"AttackA_L"), math::Vector2::Zero, math::Vector2(63.0f, 57.0f), 5, offset + math::Vector2(0.0f, -5.0f));
		animator->CreateAnimation(L"AttackA_R", ResourceManager::Find<Texture>(L"AttackA_R"), math::Vector2::Zero, math::Vector2(63.0f, 57.0f), 5, offset + math::Vector2(0.0f, -5.0f));
		animator->CreateAnimation(L"AttackB_L", ResourceManager::Find<Texture>(L"AttackB_L"), math::Vector2::Zero, math::Vector2(62.0f, 65.0f), 4, offset + math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"AttackB_R", ResourceManager::Find<Texture>(L"AttackB_R"), math::Vector2::Zero, math::Vector2(62.0f, 65.0f), 4, offset + math::Vector2(0.0f, -2.0f));
		animator->CreateAnimation(L"Jump_L", ResourceManager::Find<Texture>(L"Jump_L"), math::Vector2::Zero, math::Vector2(22.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Jump_R", ResourceManager::Find<Texture>(L"Jump_R"), math::Vector2::Zero, math::Vector2(22.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Jump_Attack_L", ResourceManager::Find<Texture>(L"Jump_Attack_L"), math::Vector2::Zero, math::Vector2(61.0f, 60.0f), 4, offset);
		animator->CreateAnimation(L"Jump_Attack_R", ResourceManager::Find<Texture>(L"Jump_Attack_R"), math::Vector2::Zero, math::Vector2(61.0f, 60.0f), 4, offset);
		animator->CreateAnimation(L"Dash_L", ResourceManager::Find<Texture>(L"Dash_L"), math::Vector2::Zero, math::Vector2(42.0f, 28.0f), 1, offset);
		animator->CreateAnimation(L"Dash_R", ResourceManager::Find<Texture>(L"Dash_R"), math::Vector2::Zero, math::Vector2(42.0f, 28.0f), 1, offset);
		animator->CreateAnimation(L"Fall_L", ResourceManager::Find<Texture>(L"Fall_L"), math::Vector2::Zero, math::Vector2(34.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Fall_R", ResourceManager::Find<Texture>(L"Fall_R"), math::Vector2::Zero, math::Vector2(34.0f, 36.0f), 2, offset);
		animator->CreateAnimation(L"Fall_Repeat_L", ResourceManager::Find<Texture>(L"Fall_Repeat_L"), math::Vector2::Zero, math::Vector2(40.0f, 40.0f), 3, offset);
		animator->CreateAnimation(L"Fall_Repeat_R", ResourceManager::Find<Texture>(L"Fall_Repeat_R"), math::Vector2::Zero, math::Vector2(40.0f, 40.0f), 3, offset);
		// NoHead
		animator->CreateAnimation(L"NoHead_Idle_L", ResourceManager::Find<Texture>(L"NoHead_Idle_L"), math::Vector2::Zero, math::Vector2(44.0f, 29.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_Idle_R", ResourceManager::Find<Texture>(L"NoHead_Idle_R"), math::Vector2::Zero, math::Vector2(44.0f, 29.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_Walk_L", ResourceManager::Find<Texture>(L"NoHead_Walk_L"), math::Vector2::Zero, math::Vector2(44.0f, 40.0f), 8, offset);
		animator->CreateAnimation(L"NoHead_Walk_R", ResourceManager::Find<Texture>(L"NoHead_Walk_R"), math::Vector2::Zero, math::Vector2(44.0f, 40.0f), 8, offset);
		animator->CreateAnimation(L"NoHead_AttackA_L", ResourceManager::Find<Texture>(L"NoHead_AttackA_L"), math::Vector2::Zero, math::Vector2(63.0f, 57.0f), 5, offset);
		animator->CreateAnimation(L"NoHead_AttackA_R", ResourceManager::Find<Texture>(L"NoHead_AttackA_R"), math::Vector2::Zero, math::Vector2(63.0f, 57.0f), 5, offset);
		animator->CreateAnimation(L"NoHead_AttackB_L", ResourceManager::Find<Texture>(L"NoHead_AttackB_L"), math::Vector2::Zero, math::Vector2(62.0f, 65.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_AttackB_R", ResourceManager::Find<Texture>(L"NoHead_AttackB_R"), math::Vector2::Zero, math::Vector2(62.0f, 65.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_Jump_L", ResourceManager::Find<Texture>(L"NoHead_Jump_L"), math::Vector2::Zero, math::Vector2(22.0f, 28.0f), 2, offset);
		animator->CreateAnimation(L"NoHead_Jump_R", ResourceManager::Find<Texture>(L"NoHead_Jump_R"), math::Vector2::Zero, math::Vector2(22.0f, 28.0f), 2, offset);
		animator->CreateAnimation(L"NoHead_Jump_Attack_L", ResourceManager::Find<Texture>(L"NoHead_Jump_Attack_L"), math::Vector2::Zero, math::Vector2(61.0f, 60.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_Jump_Attack_R", ResourceManager::Find<Texture>(L"NoHead_Jump_Attack_R"), math::Vector2::Zero, math::Vector2(61.0f, 60.0f), 4, offset);
		animator->CreateAnimation(L"NoHead_Dash_L", ResourceManager::Find<Texture>(L"NoHead_Dash_L"), math::Vector2::Zero, math::Vector2(35.0f, 24.0f), 1, offset);
		animator->CreateAnimation(L"NoHead_Dash_R", ResourceManager::Find<Texture>(L"NoHead_Dash_R"), math::Vector2::Zero, math::Vector2(35.0f, 24.0f), 1, offset);
		animator->CreateAnimation(L"NoHead_Fall_L", ResourceManager::Find<Texture>(L"NoHead_Fall_L"), math::Vector2::Zero, math::Vector2(34.0f, 33.0f), 2, offset);
		animator->CreateAnimation(L"NoHead_Fall_R", ResourceManager::Find<Texture>(L"NoHead_Fall_R"), math::Vector2::Zero, math::Vector2(34.0f, 33.0f), 2, offset);
		animator->CreateAnimation(L"NoHead_Fall_Repeat_L", ResourceManager::Find<Texture>(L"NoHead_Fall_Repeat_L"), math::Vector2::Zero, math::Vector2(40.0f, 40.0f), 3, offset);
		animator->CreateAnimation(L"NoHead_Fall_Repeat_R", ResourceManager::Find<Texture>(L"NoHead_Fall_Repeat_R"), math::Vector2::Zero, math::Vector2(40.0f, 40.0f), 3, offset);
	}

	void Player::ShowStatus(HDC _hdc)
	{
		const int SIZE = 100;
		wchar_t szFloat[SIZE] = {};
		// State
		swprintf_s(szFloat, SIZE, L"state : %d", (UINT)mState);
		int strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 50, szFloat, strLen);
		// JumpCnt
		swprintf_s(szFloat, SIZE, L"JumpCnt : %d", mJumpCnt);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 70, szFloat, strLen);
		// DashCnt
		swprintf_s(szFloat, SIZE, L"DashCnt : %d", mDashCnt);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 90, szFloat, strLen);
		// Position
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		swprintf_s(szFloat, SIZE, L"X : %f | Y : %f", pos.x, pos.y);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 110, szFloat, strLen);
		// Velocity
		math::Vector2 velocity = GetComponent<RigidBody>()->GetVelocity();
		swprintf_s(szFloat, SIZE, L"Velocity.X : %f | Velocity.Y : %f", velocity.x, velocity.y);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 130, szFloat, strLen);
		// Ground
		bool ground = GetComponent<RigidBody>()->GetGround();
		swprintf_s(szFloat, SIZE, L"Ground : %d (0 = Sky , 1 = Ground)", ground);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 150, szFloat, strLen);
		// Key
		bool input = Input::CheckGetKey();
		swprintf_s(szFloat, SIZE, L"Input : %d (0 = No , 1 = Yes)", input);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 170, szFloat, strLen);
		// HP
		float hp = mHp;
		swprintf_s(szFloat, SIZE, L"HP : %f", hp);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 190, szFloat, strLen);
		// COIN
		float coin = mCoin;
		swprintf_s(szFloat, SIZE, L"Coin : %f", coin);
		strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 10, 210, szFloat, strLen);

	}

	void Player::Idle()
	{
		mJumpCnt = 0;	// Jump || DoubleJump -> Idle
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		
		// Walk_L
		if (Input::GetKey(eKeyCode::Left) 
			&& !Input::GetKey(eKeyCode::Right) 
			&& !Input::GetKeyDown(eKeyCode::Z))
		{
			if (!mbDoubleKey)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Walk_L", true);
				}
				else 
				{
					animator->PlayAnimation(L"Walk_L", true);
				}
				// Logic
				// State
				mDirection = PlayerDirection::Left;
				mState = PlayerState::Walk;
			}
		}

		// Walk_R
		if (Input::GetKey(eKeyCode::Right) 
			&& !Input::GetKey(eKeyCode::Left) 
			&& !Input::GetKeyDown(eKeyCode::Z))
		{
			if (!mbDoubleKey)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Walk_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Walk_R", true);
				}
				// Logic
				// State
				mDirection = PlayerDirection::Left;
				mState = PlayerState::Walk;
			}
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::C))
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_L", false);
				}
				else
				{
					animator->PlayAnimation(L"Jump_L", false);
				}
			}
			else if (mDirection == PlayerDirection::Right)
			{

				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_R", false);
				}
				else
				{
					animator->PlayAnimation(L"Jump_R", false);
				}
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;		// 윗방향 초기 속도(v0)
			rb->SetVelocity(velocity);		// 속도 setter
			rb->SetGround(false);			// 점프했기에 공중에 있음을 표시 (mGround = false -> 공중)
			// State
			++mJumpCnt;						// 점프횟수 + 1 (최대 2 회)
			mState = PlayerState::Jump;
		}

		// AttackA
		if (Input::GetKeyDown(eKeyCode::X))
		{
			// Sound
			mAttackASound->Play(false);

			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_AttackA_L", false);
				}
				else
				{
					animator->PlayAnimation(L"AttackA_L", false);
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_AttackA_R", false);
				}
				else
				{
					animator->PlayAnimation(L"AttackA_R", false);
				}
			}

			mState = PlayerState::AttackA;
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::Z) 
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			mDashX1 = pos.x;
			if (mDirection == PlayerDirection::Left)
			{

				// Animmator
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_L");
				}
				else
				{
					animator->PlayAnimation(L"Dash_L");
				}
				// Logic
				velocity.x -= DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Animator
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_R");
				}
				else
				{
					animator->PlayAnimation(L"Dash_R");
				}
				// Logic
				velocity.x += DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			// State
			++mDashCnt;
			mState = PlayerState::Dash;
		}

		// 동시키 입력 해제
		if (mbDoubleKey)
		{
			if (Input::GetKeyUp(eKeyCode::Right))
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Walk_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Walk_L", true);
				}
				mState = PlayerState::Walk;
				mbDoubleKey = false;
			}

			if (Input::GetKeyUp(eKeyCode::Left))
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Walk_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Walk_R", true);
				}
				mState = PlayerState::Walk;
				mbDoubleKey = false;
			}
		}
	}

	void Player::Walk()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		
		// Walk_Left
		if (Input::GetKey(eKeyCode::Left) 
			&& !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Left;
			tr->SetPosition(pos);
		}

		// Walk_Right
		if (Input::GetKey(eKeyCode::Right) 
			&& !Input::GetKey(eKeyCode::Left))
		{
			pos.x += WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Right;
			tr->SetPosition(pos);
		}

		// Walk_L + Dash
		if (Input::GetKeyDown(eKeyCode::Z) 
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_L");
			}
			else
			{
				animator->PlayAnimation(L"Dash_L");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x -= DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Dash;
		}

		// Walk_R + Dash
		if (Input::GetKeyDown(eKeyCode::Z) 
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_R");
			}
			else
			{
				animator->PlayAnimation(L"Dash_R");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x += DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Dash;
		}

		// Walk_L + Jump
		if (Input::GetKey(eKeyCode::Left)
			&& Input::GetKeyDown(eKeyCode::C))
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_L");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Jump;
		}

		// Walk_R + Jump
		if (Input::GetKey(eKeyCode::Right)
			&& Input::GetKeyDown(eKeyCode::C))
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_R");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Jump;
		}

		// Idle_Right
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Idle_R", true);
			}
			else
			{
				animator->PlayAnimation(L"Idle_R", true);
			}
			mState = PlayerState::Idle;
		}

		// Idle_Left
		if (Input::GetKeyUp(eKeyCode::Left))
		{
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Idle_L", true);
			}
			else
			{
				animator->PlayAnimation(L"Idle_L", true);
			}
			mState = PlayerState::Idle;
		}

		// Walk + AttackA
		if (Input::GetKeyDown(eKeyCode::X))
		{
			// Sound
			mAttackASound->Play(false);

			mAttackDashX1 = pos.x;
			if (mDirection == PlayerDirection::Left)
			{
				velocity.x -= DASH_FORCE_X;
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_AttackA_L", false);
				}
				else
				{
					animator->PlayAnimation(L"AttackA_L", false);
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				velocity.x += DASH_FORCE_X;
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_AttackA_R", false);
				}
				else
				{
					animator->PlayAnimation(L"AttackA_R", false);
				}
			}
			rb->SetVelocity(velocity);
			// State
			mbAttackMove = true;
			mState = PlayerState::AttackA;
		}

		// Fall
		if (rb->GetGround() == false)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}

			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::Fall;
		}

		// 동시키 입력(방향키)
		if (Input::GetKey(eKeyCode::Right) 
			&& Input::GetKey(eKeyCode::Left))
		{
			if (!mbDoubleKey)
			{
				if (mDirection == PlayerDirection::Right)
				{
					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_Idle_R", true);
					}
					else
					{
						animator->PlayAnimation(L"Idle_R", true);
					}
					mState = PlayerState::Idle;
				}

				if (mDirection == PlayerDirection::Left)
				{
					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_Idle_L", true);
					}
					else
					{
						animator->PlayAnimation(L"Idle_L", true);
					}
					mState = PlayerState::Idle;
				}
				mbDoubleKey = true;
			}
		}
	}

	void Player::Jump()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		bool isGround = rb->GetGround();

		// Direction_L_Animator
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			// Sound
			mJumpSound->Play(false);

			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_L");
			}
		}

		// Direction_R_Animator
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			// Sound
			mJumpSound->Play(false);

			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_R");
			}
		}

		// Direction_L
		if (Input::GetKey(eKeyCode::Left)
			&& !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Left;
			tr->SetPosition(pos);
		}

		// Direction_R
		if (Input::GetKey(eKeyCode::Right)
			&& !Input::GetKey(eKeyCode::Left))
		{
			pos.x += WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Right;
			tr->SetPosition(pos);
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::Z)
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			if (mDirection == PlayerDirection::Left)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_L");
				}
				else
				{
					animator->PlayAnimation(L"Dash_L");
				}
				// Logic
				mDashX1 = pos.x;
				velocity.x -= DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_R");
				}
				else
				{
					animator->PlayAnimation(L"Dash_R");
				}
				// Logic
				mDashX1 = pos.x;
				velocity.x += DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mState = PlayerState::Dash;
		}

		// Dash + Direction_L
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_L");
			}
			else
			{
				animator->PlayAnimation(L"Dash_L");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x -= DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Dash;
		}

		// Dash + Direction_R
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_R");
			}
			else
			{
				animator->PlayAnimation(L"Dash_R");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x += DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Dash;
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::X)
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_L");
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_L
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_L");
			}
			// Logic
			// State
			mDirection = PlayerDirection::Left;
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_R
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_R");
			}
			// Logic
			// State
			mDirection = PlayerDirection::Right;
			mState = PlayerState::JumpAttack;
		}

		// DoubleJump
		if (Input::GetKeyDown(eKeyCode::C) && mJumpCnt == 1)	
		{
			// Sound
			mJumpSound->Play(false);
			// Effect
			DoubleJumpSmoke* doubleJumpEffect = Object::Instantiate<DoubleJumpSmoke>(enums::eLayerType::Player_Effect);
			doubleJumpEffect->SetOwner(this);
			
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_L");
				}
			}
			else if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_R");
				}
			}
			else
			{
				__noop;
			}

			// Logic
			RigidBody* rb = GetComponent<RigidBody>();
			math::Vector2 velocity = rb->GetVelocity();
			velocity.y = -JUMP_FORCE_Y;		// up Velocity
			rb->SetVelocity(velocity);		// Velocity Setter
			rb->SetGround(false);

			// State
			++mJumpCnt;
			mState = PlayerState::DoubleJump;
		}

		// Fall
		if (velocity.y >= 0.0f 
			&& !isGround)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}
			
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::Fall;
		}

		// Idle
		if (velocity.y == 0.0f
			&& isGround)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L");
				}
				else
				{
					animator->PlayAnimation(L"Idle_L");
				}
			}

			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R");
				}
				else
				{
					animator->PlayAnimation(L"Idle_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::Idle;
		}
	}

	void Player::Dash()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		bool isSky = rb->GetSkyDash();

		// Dash 거리 제한
		mDashX2 = pos.x;
		float distance = abs(mDashX2 - mDashX1);
		if (distance > DASH_LIMIT)
		{
			rb->SetVelocity(math::Vector2(0.0f, velocity.y));
			mDashX1 = 0.0f;
			mDashX2 = 0.0f;
		}

		// DoubleDash
		if (velocity.x != 0
			&& Input::GetKeyDown(eKeyCode::Z)
			&& !Input::CheckGetDirectionKey())
		{
			if (mDirection == PlayerDirection::Left)
			{
				// Sound
				mDashSound->Play(false);
				// Effect
				DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
				dashSmoke->SetOwner(this);

				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_L");
				}
				else
				{
					animator->PlayAnimation(L"Dash_L");
				}
				// Logic
				mDashX1 = pos.x;
				velocity.x = 0.0f;
				rb->SetVelocity(velocity);
				velocity.x -= DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Sound
				mDashSound->Play(false);

				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_R");
				}
				else
				{
					animator->PlayAnimation(L"Dash_R");
				}
				// Logic
				mDashX1 = pos.x;
				velocity.x = 0.0f;
				rb->SetVelocity(velocity);
				velocity.x += DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			// State
			++mDashCnt;
			mState = PlayerState::DoubleDash;
		}

		// DoubleDash + Direction_L
		if (velocity.x != 0
			&& Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_L");
			}
			else
			{
				animator->PlayAnimation(L"Dash_L");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x = -DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			mDirection = PlayerDirection::Left;
			mState = PlayerState::DoubleDash;
		}

		// DoubleDash + Direction_R
		if(velocity.x != 0
			&& Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_R");
			}
			else
			{
				animator->PlayAnimation(L"Dash_R");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x = DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			mDirection = PlayerDirection::Right;
			mState = PlayerState::DoubleDash;
		}

		// Idle
		if (velocity.x == 0 && !isSky)
		{
			// Animation
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_R", true);
				}
			}
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_L", true);
				}
			}
			// Logic
			// State
			mDashCnt = 0;
			mState = PlayerState::Idle;
		}

		// fall
		if (velocity.x == 0 && isSky)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}

			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic
			// State
			mDashCnt = 0;
			rb->SetSkyDash(false);
			mState = PlayerState::Fall;
		}
	}

	void Player::AttackA()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// 어택과 동시에 방향키를 누른경우 공격시 일정거리 이동한다.
		if (mbAttackMove)
		{
			mAttackDashX2 = pos.x;
			float distance = abs(mAttackDashX2 - mAttackDashX1);
			if (distance >= 50.0f)
			{
				rb->SetVelocity(math::Vector2(0.0f, velocity.y));
				mbAttackMove = false;
			}
		}

		// 콤보공격(AttackB)으로 연결될지 확인
		if (Input::GetKeyDown(eKeyCode::X)
			&& !Input::CheckGetDirectionKey())
		{
			mbCombo = true;
		}

		// AttackB + Move Flag
		// 콤보공격시 방향키를 누르고 있으면 일정거리 이동하면서 공격
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::CheckGetDirectionKey())
		{
			mbCombo = true;
			mbAttackMove2 = true;
		}

		// Attack Action
		if (animator->IsActiveAnimationComplete())
		{
			// AttackB로 이어져야 할때
			if (mbCombo == true)
			{
				// 이동공격이라면 이동시켜준다.
				if (mbAttackMove2 == true)
				{
					mAttackDashX1 = pos.x;
					if (Input::GetKey(eKeyCode::Left))
					{
						velocity.x -= DASH_FORCE_X;
						mDirection = PlayerDirection::Left;
					}
					if (Input::GetKey(eKeyCode::Right))
					{
						velocity.x += DASH_FORCE_X;
						mDirection = PlayerDirection::Right;
					}
					rb->SetVelocity(velocity);
				}

				// Animation
				if (mDirection == PlayerDirection::Left)
				{
					// Sound
					mAttackBSound->Play(false);

					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_AttackB_L", false);
					}
					else
					{
						animator->PlayAnimation(L"AttackB_L", false);
					}
				}
				if (mDirection == PlayerDirection::Right)
				{
					// Sound
					mAttackBSound->Play(false);

					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_AttackB_R", false);
					}
					else
					{
						animator->PlayAnimation(L"AttackB_R", false);
					}
				}
				// Logic
				// State
				mbCombo = false;
				mState = PlayerState::AttackB;
			}
			// AttackA 후 콤보공격으로 이어지지 않고 Idle 상태로 이어질 때
			else 
			{
				// Animation
				if (mDirection == PlayerDirection::Left)
				{
					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_Idle_L", true);
					}
					else
					{
						animator->PlayAnimation(L"Idle_L", true);
					}
				}
				else if (mDirection == PlayerDirection::Right)
				{
					if (mbSkullLess)
					{
						animator->PlayAnimation(L"NoHead_Idle_R", true);
					}
					else
					{
						animator->PlayAnimation(L"Idle_R", true);
					}
				}
				// Logic
				// State
				mState = PlayerState::Idle;
			}
		}
	}

	void Player::AttackB()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		if (mbAttackMove2)
		{
			mAttackDashX2 = pos.x;
			float distance = abs(mAttackDashX2 - mAttackDashX1);
			if (distance >= 50.0f)
			{
				rb->SetVelocity(math::Vector2(0.0f, velocity.y));
				mbAttackMove2 = false;
			}
		}

		if (animator->IsActiveAnimationComplete())
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_L", true);
				}
			}
			else if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_R", true);
				}
			}
			// Logic
			// State
			mState = PlayerState::Idle;
		}
	}

	void Player::JumpAttack()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		// Direction_L
		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Left;
			tr->SetPosition(pos);
		}

		// Direction_R
		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Right;
			tr->SetPosition(pos);
		}

		// Idle
		if (rb->GetGround())
		{
			if (mDirection == PlayerDirection::Left)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_L", true);
				}
			}
			if(mDirection == PlayerDirection::Right)
			{ 
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_R", true);
				}
			}
			// Logic
			// State
			mState = PlayerState::Idle;
		}

		// Fall
		if (animator->IsActiveAnimationComplete())
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::Fall;
		}
	}

	void Player::DoubleJump()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		bool isGround = rb->GetGround();

		// Direction_L_Animation
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			// Sound
			mDoubleJumpSound->Play(false);

			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_L");
			}
		}

		// Direction_R_Animation
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			// Sound
			mDoubleJumpSound->Play(false);

			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_R");
			}
		}

		// Direction_L_Logic
		if (Input::GetKey(eKeyCode::Left)
			&& !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Left;
			tr->SetPosition(pos);
		}

		// Direction_R_Logic
		if (Input::GetKey(eKeyCode::Right)
			&& !Input::GetKey(eKeyCode::Left))
		{
			pos.x += WALK_SPEED * Time::GetDeltaTime();
			mDirection = PlayerDirection::Right;
			tr->SetPosition(pos);
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::Z)
			&& !Input::CheckGetDirectionKey())
		{
			mDashX1 = pos.x;
			if (mDirection == PlayerDirection::Left)
			{
				// Sound
				mDashSound->Play(false);
				// Effect
				DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
				dashSmoke->SetOwner(this);

				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_L");
				}
				else
				{
					animator->PlayAnimation(L"Dash_L");
				}
				// Logic
				velocity.x -= DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Sound
				mDashSound->Play(false);
				// Effect
				DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
				dashSmoke->SetOwner(this);

				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_R");
				}
				else
				{
					animator->PlayAnimation(L"Dash_R");
				}
				// Logic
				velocity.x += DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mState = PlayerState::Dash;
		}

		// Dash + Direction_L
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_L");
			}
			else
			{
				animator->PlayAnimation(L"Dash_L");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x -= DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Dash;
		}

		// Dash + Direction_R
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_R");
			}
			else
			{
				animator->PlayAnimation(L"Dash_R");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x += DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Dash;
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::X)
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_L");
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_L
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_L");
			}
			// Logic
			// State
			mDirection = PlayerDirection::Left;
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_R
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_R");
			}
			// Logic

			// State
			mDirection = PlayerDirection::Right;
			mState = PlayerState::JumpAttack;
		}

		// Fall
		if (velocity.y >= 0.0f 
			&& !isGround)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic

			// State
			mState = PlayerState::Fall;
		}

		// Idle
		if (velocity.y == 0.0f
			&& isGround)
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L");
				}
				else
				{
					animator->PlayAnimation(L"Idle_L");
				}
			}

			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R");
				}
				else
				{
					animator->PlayAnimation(L"Idle_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::Idle;
		}
	}

	void Player::DoubleDash()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		bool isSky = rb->GetSkyDash();

		// Dash 거리 제한
		mDashX2 = pos.x;
		float distance = abs(mDashX2 - mDashX1);
		if (distance > DASH_LIMIT)
		{
			rb->SetVelocity(math::Vector2(0.0f, velocity.y));
			mDashX1 = 0.0f;
			mDashX2 = 0.0f;
		}

		// Idle
		if (velocity.x == 0
			&& !isSky)
		{
			// Animation
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_R", true);
				}
				mState = PlayerState::Idle;
			}
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_L", true);
				}
				mState = PlayerState::Idle;
			}
			// Logic
			// State
			mDashCnt = 0;
			mState = PlayerState::Idle;
		}

		// Fall
		if (velocity.x == 0
			&& isSky
			&& !Input::CheckGetDirectionKey())
		{
			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_L");
				}
				else
				{
					animator->PlayAnimation(L"Fall_L");
				}
			}

			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Fall_R");
				}
				else
				{
					animator->PlayAnimation(L"Fall_R");
				}
			}
			// Logic
			// State
			mDashCnt = 0;
			rb->SetSkyDash(false);
			mState = PlayerState::Fall;
		}

		// Fall + Direction_L
		if (velocity.x == 0
			&& isSky
			&& Input::GetKey(eKeyCode::Left))
		{
			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Fall_L");
			}
			else
			{
				animator->PlayAnimation(L"Fall_L");
			}
			// Logic
			// State
			mDashCnt = 0;
			rb->SetSkyDash(false);
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Fall;
		}
		
		// Fall + Direction_R
		if (velocity.x == 0
			&& isSky
			&& Input::GetKey(eKeyCode::Right))
		{
			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Fall_R");
			}
			else
			{
				animator->PlayAnimation(L"Fall_R");
			}
			// Logic
			// State
			mDashCnt = 0;
			rb->SetSkyDash(false);
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Fall;
		}
	}

	void Player::Fall()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();
		bool isGround = rb->GetGround();

		// Idle
		if (isGround == true)
		{
			// Sound
			mLandingSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_R", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_R", true);
				}
			}
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Idle_L", true);
				}
				else
				{
					animator->PlayAnimation(L"Idle_L", true);
				}
			}
			// Logic
			// State
			rb->SetGround(true);
			mState = PlayerState::Idle;
		}

		// Fall_Repeat Animation
		if (animator->IsActiveAnimationComplete())
		{
			if (mbSkullLess)
			{
				if (mDirection == PlayerDirection::Left)
				{
					animator->PlayAnimation(L"NoHead_Fall_Repeat_L", true);
				}
				else if (mDirection == PlayerDirection::Right)
				{
					animator->PlayAnimation(L"NoHead_Fall_Repeat_R", true);
				}
			}
			else
			{
				if (mDirection == PlayerDirection::Left)
				{
					animator->PlayAnimation(L"Fall_Repeat_L", true);
				}
				else if (mDirection == PlayerDirection::Right)
				{
					animator->PlayAnimation(L"Fall_Repeat_R", true);
				}
			}
		}

		// Direction_L Fall_Repeat Animation
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Fall_Repeat_L", true);
			}
			else
			{
				animator->PlayAnimation(L"Fall_Repeat_L", true);
			}
		}

		// Direction_R Fall_Repeat Animation
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Fall_Repeat_R", true);
			}
			else
			{
				animator->PlayAnimation(L"Fall_Repeat_R", true);
			}
		}

		// Direction_L_Logic
		if (Input::GetKey(eKeyCode::Left)
			&& !Input::GetKey(eKeyCode::Right))
		{
			pos.x -= WALK_SPEED * Time::GetDeltaTime();
			tr->SetPosition(pos);
			// State
			mDirection = PlayerDirection::Left;
		}

		// Direction_R_Logic
		if (Input::GetKey(eKeyCode::Right)
			&& !Input::GetKey(eKeyCode::Left))
		{
			pos.x += WALK_SPEED * Time::GetDeltaTime();
			tr->SetPosition(pos);
			// State
			mDirection = PlayerDirection::Right;
		}
		
		// Dash
		if (Input::GetKeyDown(eKeyCode::Z)
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			mDashX1 = pos.x;
			if (mDirection == PlayerDirection::Left)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_L");
				}
				else
				{
					animator->PlayAnimation(L"Dash_L");
				}
				// Logic
				velocity.x -= DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			if (mDirection == PlayerDirection::Right)
			{
				// Animation
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Dash_R");
				}
				else
				{
					animator->PlayAnimation(L"Dash_R");
				}
				// Logic
				velocity.x += DASH_FORCE_X;
				rb->SetVelocity(velocity);
			}
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mState = PlayerState::Dash;
		}

		// Dash + Direction_L
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_L");
			}
			else
			{
				animator->PlayAnimation(L"Dash_L");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x -= DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Dash;
		}

		// Dash + Direction_R
		if (Input::GetKeyDown(eKeyCode::Z)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mDashSound->Play(false);
			// Effect
			DashSmoke* dashSmoke = Object::Instantiate<DashSmoke>(enums::eLayerType::Player_Effect);
			dashSmoke->SetOwner(this);

			// Animmator
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Dash_R");
			}
			else
			{
				animator->PlayAnimation(L"Dash_R");
			}
			// Logic
			mDashX1 = pos.x;
			velocity.x += DASH_FORCE_X;
			rb->SetVelocity(velocity);
			// State
			++mDashCnt;
			rb->SetSkyDash(true);
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Dash;
		}

		// ★ Double Jump 로직이 Jump로직의 위에 있어야한다. ★
		// DoubleJump
		if (Input::GetKeyDown(eKeyCode::C)
			&& !Input::CheckGetDirectionKey()
			&& !isGround
			&& mJumpCnt == 1)
		{
			// Sound
			mJumpSound->Play(false);
			// Effect
			DoubleJumpSmoke* doubleJumpEffect = Object::Instantiate<DoubleJumpSmoke>(enums::eLayerType::Player_Effect);
			doubleJumpEffect->SetOwner(this);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_L");
				}
			}
			else if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_R");
				}
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mState = PlayerState::DoubleJump;
		}

		// DoubleJump + Direction_L
		if (Input::GetKeyDown(eKeyCode::C)
			&& Input::GetKey(eKeyCode::Left)
			&& !isGround
			&& mJumpCnt == 1)
		{
			// Sound
			mJumpSound->Play(false);
			// Effect
			DoubleJumpSmoke* doubleJumpEffect = Object::Instantiate<DoubleJumpSmoke>(enums::eLayerType::Player_Effect);
			doubleJumpEffect->SetOwner(this);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_L");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Left;
			mState = PlayerState::DoubleJump;
		}

		// DoubleJump + Direction_R
		if (Input::GetKeyDown(eKeyCode::C)
			&& Input::GetKey(eKeyCode::Right)
			&& !isGround
			&& mJumpCnt == 1)
		{
			// Sound
			mJumpSound->Play(false);
			// Effect
			DoubleJumpSmoke* doubleJumpEffect = Object::Instantiate<DoubleJumpSmoke>(enums::eLayerType::Player_Effect);
			doubleJumpEffect->SetOwner(this);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_R");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Right;
			mState = PlayerState::DoubleJump;
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::C)
			&& !Input::CheckGetDirectionKey()
			&& !isGround
			&& mJumpCnt == 0)
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_L");
				}
			}
			else if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_R");
				}
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mState = PlayerState::Jump;
		}

		// Jump + Direction_L
		if (Input::GetKeyDown(eKeyCode::C)
			&& Input::GetKey(eKeyCode::Left)
			&& !isGround
			&& mJumpCnt == 0)
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_L");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Left;
			mState = PlayerState::Jump;
		}

		// Jump + Direction_R
		if (Input::GetKeyDown(eKeyCode::C)
			&& Input::GetKey(eKeyCode::Right)
			&& !isGround
			&& mJumpCnt == 0)
		{
			// Sound
			mJumpSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_R");
			}
			// Logic
			velocity.y = -JUMP_FORCE_Y;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			// State
			++mJumpCnt;
			mDirection = PlayerDirection::Right;
			mState = PlayerState::Jump;
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::X)
			&& !Input::CheckGetDirectionKey())
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mDirection == PlayerDirection::Left)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_L");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_L");
				}
			}
			if (mDirection == PlayerDirection::Right)
			{
				if (mbSkullLess)
				{
					animator->PlayAnimation(L"NoHead_Jump_Attack_R");
				}
				else
				{
					animator->PlayAnimation(L"Jump_Attack_R");
				}
			}
			// Logic
			// State
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_L
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Left))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_L");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_L");
			}
			// Logic
			// State
			mDirection = PlayerDirection::Left;
			mState = PlayerState::JumpAttack;
		}

		// JumpAttack + Direction_R
		if (Input::GetKeyDown(eKeyCode::X)
			&& Input::GetKey(eKeyCode::Right))
		{
			// Sound
			mJumpAttackSound->Play(false);

			// Animation
			if (mbSkullLess)
			{
				animator->PlayAnimation(L"NoHead_Jump_Attack_R");
			}
			else
			{
				animator->PlayAnimation(L"Jump_Attack_R");
			}
			// Logic
			// State
			mDirection = PlayerDirection::Right;
			mState = PlayerState::JumpAttack;
		}
	}

	void Player::Hit()
	{
		Animator* at = GetComponent<Animator>();
		RigidBody* rb = GetComponent<RigidBody>();
		math::Vector2 velocity = rb->GetVelocity();

		rb->SetSkyDash(false);

		// 피격 애니메이션
		if (mbPlayAnimation == true)
		{
			mHitSign->GetComponent<Animator>()->PlayAnimation(L"UI_Player_HitSign", false);
			// Monster가 왼쪽에서 공격받았을 경우
			if (mDamageDirection == PlayerDirection::Left)
			{
				at->PlayAnimation(L"Idle_L", true);
				// 왼쪽에서 맞았기에 오른쪽으로 날아가야한다.
				velocity.x = HIT_BUMP_X;
				rb->SetVelocity(velocity);

				mDirection = PlayerDirection::Left;
			}
			// 몬스터가 오른쪽에서 공격받았을 경우
			if (mDamageDirection == PlayerDirection::Right)
			{
				at->PlayAnimation(L"Idle_R", true);
				// 오른쪽에서 맞았기에 왼쪽으로 날아가야한다.
				velocity.x = -HIT_BUMP_X;
				rb->SetVelocity(velocity);

				mDirection = PlayerDirection::Right;
				mbPlayAnimation = false;
			}
			// 몬스터가 공격받은 방향을 초기화해준다.
			mDamageDirection == PlayerDirection::None;

			mState = PlayerState::Idle;
		}

		//if (rb->GetGround() == true)
		//{
		//	mState = PlayerState::Idle;
		//}
	}

	void Player::Skill()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetComponent<RigidBody>();

		// [머리발사 스킬]
		if (Input::GetKeyDown(eKeyCode::A)
			&& mbSkillFlag == false)
		{
			// Sound
			mSkullThrowingSound->Play(false);

			// 머리 없음 설정
			mbSkullLess = true;
			// 스킬 발동
			mbSkillFlag = true;
			// 투사체 생성
			head = Object::Instantiate<Skull>(enums::eLayerType::Skill);
			// 날아갈 방향 설정
			if (mDirection == PlayerDirection::Left)
			{
				head->SetDirection(Skull::HeadDirection::Left);
			}
			if(mDirection == PlayerDirection::Right)
			{
				head->SetDirection(Skull::HeadDirection::Right);
			}
			// 머리 유지시간 4초
			mHeadTime = SKILL_HEAD_TIME;
		}

		// 스킬 쿨타임 카운트
		if (mbSkillFlag == true)
		{
			mCoolTime -= Time::GetDeltaTime();
			if (mCoolTime <= 0.0f)
			{
				mbSkillFlag = false;
				mCoolTime = SKILL_COOL_TIME;
			}
		}

		// 머리 유지시간 카운트
		if (mbSkullLess == true)
		{
			mHeadTime -= Time::GetDeltaTime();
			if (mHeadTime <= 0.0f)
			{
				mbSkullLess = false;
				Destroy(head);
			}
		}

		// 투사체 날아가는 로직
		if (head != nullptr
			&& head->GetCollision() == false 
			&& mbSkullLess == true)
		{
			// 투사체가 생성되었고 어디에도 부딪히지 않은 상태일 때
			Transform* tr_head = head->GetComponent<Transform>();
			math::Vector2 pos_head = tr_head->GetPosition();
			if (head->GetDirection() == Skull::HeadDirection::Left)
			{
				pos_head.x -= HEAD_SPEED * Time::GetDeltaTime();
				tr_head->SetPosition(pos_head);
			}
			if (head->GetDirection() == Skull::HeadDirection::Right)
			{
				pos_head.x += HEAD_SPEED * Time::GetDeltaTime();
				tr_head->SetPosition(pos_head);
			}
		}

		// [위치 이동 스킬] (전제조건 : 머리발사 스킬을 먼저 사용해야함)
		if (Input::GetKeyDown(eKeyCode::S)
			&& mbSkullLess == true)
		{
			// 머리객체 소멸
			Destroy(head);
			// 머리상태 복구
			mbSkullLess == false;
			mHeadTime = 0.0f;
			// 스킬 쿨타임 줄이기
			mCoolTime -= 3.0f;	

			// 플레이어 위치 이동
			math::Vector2 pos_head = head->GetComponent<Transform>()->GetPosition();
			math::Vector2 col_size = GetComponent<Collider>()->GetSize();
			math::Vector2 newPos = pos_head - math::Vector2(0.0f, col_size.y / 2);
			tr->SetPosition(newPos);
			// 속도 제거
			rb->SetGround(false);
			rb->SetVelocity(math::Vector2(0.0f, -500.0f));
			mState = PlayerState::Jump;
		}
	}
}