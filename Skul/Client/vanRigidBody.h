#pragma once
#include "vanComponent.h"

namespace van
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		void AddForce(math::Vector2 _force) { mForce += _force; }
		void SetMass(float _mass) { mMass = _mass; }
		void SetGround(bool _ground) { mbGround = _ground; }

	private:
		float mMass;

		float mFriction;
		//float mStaticFriction;
		//float mKineticFriction;
		//float mCoefficentFriction;

		math::Vector2 mForce;
		math::Vector2 mAccelation;
		math::Vector2 mVelocity;
		math::Vector2 mGravity;
		math::Vector2 mLimitedVelocity;

		bool mbGround;
	};
}

