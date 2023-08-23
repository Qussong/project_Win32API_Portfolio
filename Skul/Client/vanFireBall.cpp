#include "vanFireBall.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanWall.h"
#include "vanFloor.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanSceneManager.h"
#include "vanBoss.h"

#define OBJECT_SPEED	200.0f

namespace van
{
	FireBall::FireBall()
	{
		AddComponent<RigidBody>();
	}

	FireBall::~FireBall()
	{
		// nothing
	}

	void FireBall::Init()
	{
		Skill::Init();

		RigidBody* rb = GetComponent<RigidBody>();
		rb->SetProjectiveBody(true);		// 투사체관련 로직을 타도록 설정

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(25.0f, 25.0f));

		mState = FireBallState::Gen;
	}

	void FireBall::Update()
	{
		Skill::Update();

		MakeAnimation();

		switch (mState)
		{
		case FireBallState::Gen:
			Gen();
			break;
		case FireBallState::Active:
			Active();
			break;
		case FireBallState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

	}

	void FireBall::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void FireBall::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"Mage_FireBall", ResourceManager::Find<Texture>(L"Mage_FireBall"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 28.0f), 12);
	}

	void FireBall::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Player* player = dynamic_cast<Player*>(obj);
		Floor* floor = dynamic_cast<Floor*>(obj);
		Wall* wall = dynamic_cast<Wall*>(obj);

		if (player != nullptr)
		{
			// 플레이어에게 데미지를 준다 or 플레이어에게 맞았음을 알려준다.

			// FireBall객체 소멸
			mState = FireBallState::Dead;
		}

		if (floor != nullptr || wall != nullptr)
		{
			mState = FireBallState::Dead;
		}
	}

	void FireBall::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void FireBall::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void FireBall::Gen()
	{
		SetFireBallMove();

		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Mage_FireBall", true);

		mState = FireBallState::Active;
	}

	void FireBall::Active()
	{
		// nothing
	}

	void FireBall::Dead()
	{
		// FireBall객체 소멸
		Destroy(this);
	}

	void FireBall::SetFireBallMove()
	{
		RigidBody* rb = GetComponent<RigidBody>();
		Boss* owner = dynamic_cast<Boss*>(GetOwner());

		Transform* tr = owner->GetComponent<Transform>();
		Transform* tr_target = owner->GetTarget()->GetComponent<Transform>();

		math::Vector2 pos = tr->GetPosition();					// 발사지점
		math::Vector2 pos_target = tr_target->GetPosition();	// 도착지점
		math::Vector2 dir = pos_target - pos;					// 방향
		math::Vector2 speed = math::Vector2::Zero;				// 투사체 속도
		if (dir.x < 0)
		{
			if (dir.y < 0)
			{
				speed = math::Vector2(-OBJECT_SPEED, -OBJECT_SPEED);
			}
			else
			{
				speed = math::Vector2(-OBJECT_SPEED, OBJECT_SPEED);
			}

		}
		else
		{
			if (dir.y < 0)
			{
				speed = math::Vector2(OBJECT_SPEED, -OBJECT_SPEED);
			}
			else
			{
				speed = math::Vector2(OBJECT_SPEED, OBJECT_SPEED);
			}
		}

		rb->SetProjectiveDirection(dir);						// RigidBody 속성에 방향벡터값 설정
		rb->SetVelocity(speed);									// 속도값 설정
	}
}