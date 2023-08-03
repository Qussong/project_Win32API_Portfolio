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

		__forceinline void AddForce(math::Vector2 _force) { mForce += _force; }
		__forceinline void SetMass(float _mass) { mMass = _mass; }

		__forceinline void SetGround(bool _ground) { mbGround = _ground; }
		__forceinline bool GetGround() { return mbGround; }

		__forceinline void SetSkyDash(bool _skyDash) { mbSkyDash = _skyDash; }
		__forceinline bool GetSkyDash() { return mbSkyDash; }

		__forceinline void SetHit(bool _hit) { mbHit = _hit; }
		__forceinline bool GetHit() { return mbHit; }

		__forceinline math::Vector2 GetVelocity() { return mVelocity; }
		__forceinline void SetVelocity(math::Vector2 _velocity) { mVelocity = _velocity; }

		__forceinline void SetGravity(math::Vector2 _gravity) { mGravity = _gravity; }
		__forceinline math::Vector2 GetGravity() { return mGravity; }

	private:
		float mMass;
		float mFriction;
		//float mStaticFriction;	// Á¤Áö¸¶Âû·Â
		//float mKineticFriction;	// ¿îµ¿¸¶Âû·Â
		//float mCoefficentFriction;

		math::Vector2 mForce;
		math::Vector2 mAccelation;
		math::Vector2 mVelocity;
		math::Vector2 mGravity;
		math::Vector2 mLimitedVelocity;

		bool mbGround;
		bool mbSkyDash;
		bool mbHit;
	};
}

