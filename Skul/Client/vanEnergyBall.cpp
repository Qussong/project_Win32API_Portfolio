#include "vanEnergyBall.h"
#include "vanEnergyBallObject.h"
#include "vanObject.h"
#include "vanTransform.h"

#define BALL_CNT	8
#define PI			3.141592

van::EnergyBall::EnergyBall()
{
	// nothing
}

van::EnergyBall::~EnergyBall()
{
	// nothing
}

void van::EnergyBall::Init()
{
	Skill::Init();

	mState = EnergyBallState::Gen;
}

void van::EnergyBall::Update()
{
	Skill::Update();

	switch (mState)
	{
	case EnergyBallState::Gen:
		Gen();
		break;
	case EnergyBallState::Active:
		Active();
		break;
	case EnergyBallState::Dead:
		Dead();
		break;
	default:
		__noop;
	}
}

void van::EnergyBall::Render(HDC _hdc)
{
	Skill::Render(_hdc);
}

void van::EnergyBall::MakeAnimation()
{
	// nothing
}

void van::EnergyBall::OnCollisionEnter(Collider* _other)
{
	// nothing
}

void van::EnergyBall::OnCollisionStay(Collider* _other)
{
	// nothing
}

void van::EnergyBall::OnCollisionExit(Collider* _other)
{
	// nothing
}

void van::EnergyBall::Gen()
{
	GameObject* owner = GetOwner();

	if (owner != nullptr)
	{
		// EnergyBall 객체 8개 생성
		for (int i = 0; i < BALL_CNT; ++i)
		{
			float radian = (45.0f * i) / 180.0f * PI;

			// EnergyBall 객체 생성
			EnergyBallObject* ball = Object::Instantiate<EnergyBallObject>(enums::eLayerType::Yggdrasill_Skill_EnergyBall);
			// 생성시 위치/방향 설정
			ball->SetOwner(this);
			//ball->SetDirect(dir);
			ball->SetRadian(radian);
		}

		mState = EnergyBallState::Active;
	}
}

void van::EnergyBall::Active()
{
	// EnergyBall 개수 파악
	if (mDestroyBallCnt == BALL_CNT)
	{
		// 전부 소멸시 Dead 상태로 전환
		mState = EnergyBallState::Dead;
	}
}

void van::EnergyBall::Dead()
{
	// EnergyBall 객체 소멸
	Destroy(this);
}
