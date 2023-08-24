#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillHand : public GameObject
	{
	public:
		enum class HandPos
		{
			Left,
			Right,
			None,
		};

		enum class HandState
		{
			Gen,
			Idle,
			FistSlamReady,
			SwipeReady,
			MagicOrbsReady,
			FistSlam,
			Swipe,
			MagicOrbs,
			FistSlamEnd,
			SwipeEnd,
			MagicOrbsEnd,
			Dead,
			None,
		};

	public:
		YggdrasillHand();
		virtual ~YggdrasillHand();

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
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		__forceinline HandPos GetHandPos() { return mHandPos; }
		__forceinline void SetHandPos(HandPos _pos) { mHandPos = _pos; }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline HandState GetState() { return mState; }
		__forceinline void SetState(HandState _state) { mState = _state; }

		__forceinline void SetAddPos(math::Vector2 _pos) { mAddPos = _pos; }

		__forceinline bool GetReadyFinishFlag() { return mbReadyFinish; }
		__forceinline void SetReadyFinishFlag(bool _flag) { mbReadyFinish = _flag; }

		__forceinline bool GetEndFinishFlag() { return mbEndFinish; }
		__forceinline void SetEndFinishFlag(bool _flag) { mbEndFinish = _flag; }

		void InitAddPos();
		void FollowBodyPos();
		void ResetInitPos();

	private:
		bool mbInitFlag = true;

		HandPos mHandPos = HandPos::None;
		GameObject* mOwner = nullptr;
		bool mbPlayAnimation = true;

		HandState mState = HandState::None;
		HandState mPastState = HandState::None;

		float mTime = 0.0f;
		bool mUpDownFlag = false;
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// Body 기준 초기값(= 초기화용)
		math::Vector2 mAddPos = math::Vector2::Zero;

		// FistSlam Ready
		bool mbReadyInit = false;
		bool mbReadyFinish = false;			// 모든 부위 공통
		math::Vector2 mInitPos = math::Vector2::Zero;	// 최초위치
		bool mbCollisionFloor = false;

		// FistSlam
		bool mbDirectionSet = false;
		math::Vector2 dir = math::Vector2::Zero;
		math::Vector2 mInitPos2 = math::Vector2::Zero;	// 최종위치
		bool mbFistSlamEnd = false;
		bool mbEndFinish = false;		// 모든 부위 공통

		// FistSlam End
		// mbEndFinish 사용
	};
}

