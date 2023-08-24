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
			FistSlamReady,
			SwipeReady,
			MagicOrbsReady,
			FistSlam,
			Swipe,
			MagicOrbs,
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
		void Dead();
		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		void FistSlam();
		void Swipe();
		void MagicOrbs();

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		void FollowBodyPos();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* _owner) { mOwner = _owner; }

		HeadState GetState() { return mState; }
		void SetState(HeadState _state) { mState = _state; }

	private:
		GameObject* mOwner;
		HeadState mState = HeadState::None;
		float mTime = 0.0f;
		bool mUpDownFlag = false;
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// Body 기준 초기값(= 초기화용)
		math::Vector2 mAddPos = math::Vector2::Zero;
	};
}

