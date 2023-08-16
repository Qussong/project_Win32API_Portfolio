#pragma once
#include "vanGameObject.h"

namespace van
{
	class Gold : public GameObject
	{
	public:
		enum class GoldState
		{
			Gen,
			Idle,
			Dead,
			None,
		};

	public:
		Gold();
		virtual ~Gold();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		__forceinline GoldState GetGoldState() { return mState; }
		__forceinline void SetGoldState(GoldState _state) { mState = _state; }

		__forceinline GoldState GetGoldPastState() { return mPastState; }
		__forceinline void SetGoldPastState(GoldState _state) { mPastState = _state; }

		__forceinline bool GetPlayAnimation() { return mbPlayAnimation; }
		__forceinline void SetPlayAnimation(bool _flag) { mbPlayAnimation = _flag; }

		void Gen();
		void Idle();
		void Dead();

	private:
		GoldState mState;
		GoldState mPastState;
		bool mbPlayAnimation;	// Animation 재생 여부

	};
}

