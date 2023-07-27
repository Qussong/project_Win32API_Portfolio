#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanObject.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(enums::eComponentType::RigidBody)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mForce(math::Vector2::Zero)
		, mAccelation(math::Vector2::Zero)
		, mVelocity(math::Vector2::Zero)
		, mGravity(math::Vector2(0.0f, 2000.0f))
		, mLimitedVelocity(math::Vector2(2000.0f, 2000.0f))
		, mbGround(false)
	{
	}

	RigidBody::~RigidBody()
	{
		// nothing
	}

	void RigidBody::Init()
	{
		// nothing
	}

	void RigidBody::Update()
	{
		
		mAccelation = mForce / mMass;	// F = m * a -> a = F / m
		mVelocity += mAccelation * Time::GetDeltaTime();	// v1 = v0 + at


		if (mbGround)	// GameObject가 땅위에 있을 때
		{
			math::Vector2 gravity = mGravity;			// 중력 초기값 -> x = 0, y = 980
			gravity.normalize();						// 중력 -> x = 0, y = 1
			float dot = math::Dot(mVelocity, gravity);	// dot = mVelocity.y
			math::Vector2 val = gravity * dot;
			mVelocity -= val;					// mVelocity -= Vector2(0, mVelocity.y)
												// mVelocity 에 x성분만 남는다.
		}
		else  // GameObject가 공중에 있을 때
		{
			mVelocity += mGravity * Time::GetDeltaTime();
		}

		// 최대 속도 제한
		math::Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		math::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// 마찰력 조건 (적용된 힘이 없고 속독 0이 아닐 경우)
		if (!(mVelocity == math::Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::GetDeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.length() < friction.length())
			{
				// 속도를 0 로 만든다.
				mVelocity = math::Vector2(0.0f, 0.0f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::GetDeltaTime();
		tr->SetPosition(pos);
		mForce.clear();
	}

	void RigidBody::Render(HDC _hdc)
	{
		// nothing
	}
}