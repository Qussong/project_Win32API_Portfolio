#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillHead : public GameObject
	{
	public:
		enum class HeadState
		{
			Gen,
			Idle,
			AttackReady,
			Attack,
			AttackEnd,
			Dead,
			None,
		};

	public:
		YggdrasillHead();
		virtual ~YggdrasillHead();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		void Gen();
		void Idle();
		void AttackReady();
		void Attack();
		void AttackEnd();
		void Dead();

		// AttackReady
		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		// Attack
		void FistSlamAttack();
		void SwipeAttack();
		void MagicOrbsAttack();
		// AttackEnd
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		void FollowBodyPos();
		// MagicOrb
		void ShakeHead();
		void ShootEnerge();
		void InitHeadPos();

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline HeadState GetState() { return mState; }
		__forceinline void SetState(HeadState _state) { mState = _state; }

		__forceinline bool GetFinishFlag() { return mbFinish; }
		__forceinline void SetFinishFlag(bool _flag) { mbFinish = _flag; }

		__forceinline void ResetMagicOrbShootMotionValue() { mMagicOrbShootMotion = 0; }
		__forceinline bool GetMagicOrbShootFlag() { return mbMagicOrbShoot; }
		__forceinline void SetMagicOrbShootFlag(bool _flag) { mbMagicOrbShoot = _flag; }

	private:
		GameObject* mOwner;
		HeadState mState = HeadState::None;
		HeadState mPastState = HeadState::None;

		bool mbFinish = false;						// 본체에 수행이 끝났음을 알려준다.
		bool mbEnd = false;
		bool mbPlayAnimation = true;

		// Idle
		float mTime = 0.0f;
		bool mUpDownFlag = false;
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// Body 기준 초기값(= 초기화용)
		math::Vector2 mAddPos = math::Vector2::Zero;

		// MagicOrb Ready

		// MagicOrb Attack
		int mMagicOrbShootMotion = 0;
		bool mbMagicOrbShoot = false;

		// MagicOrb End

	};
}

