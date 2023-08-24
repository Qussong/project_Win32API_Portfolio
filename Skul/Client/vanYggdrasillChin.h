#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillChin : public GameObject
	{
	public:
		enum class ChinState
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
		YggdrasillChin();
		virtual ~YggdrasillChin();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		void Gen();
		void Idle();
		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		void FistSlam();
		void Swipe();
		void MagicOrbs();
		void Dead();

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		void FollowHeadPos();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* _owner) { mOwner = _owner; }

		ChinState GetState() { return mState; }
		void SetState(ChinState _state) { mState = _state; }

	private:
		GameObject* mOwner;
		ChinState mState = ChinState::None;
		float mTime = 0.0f;
		bool mUpDownFlag = false;
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// Head 기준 초기값(= 초기화용)
		math::Vector2 mAddPos = math::Vector2::Zero;
	};
}


