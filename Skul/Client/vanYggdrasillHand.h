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
			AttackReady,
			Attack,
			AttackEnd,
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

		void InitAddPos();		// 초기위치값 저장 -> Left, Right 구분을 Init에서 할 수 없기에 Update에 넣어준다.
		void FollowBodyPos();	// Idle 상태일 때 Body객체의 위치를 기준으로 Hand의 위치값을 설정한다.
		void FistSlam();		// FistSlam 공격을 수행하는 로직
		void FistSlamAfter();	// FistSlam 공격수행후 Hand 위치 재정렬

		__forceinline HandPos GetHandPos() { return mHandPos; }
		__forceinline void SetHandPos(HandPos _pos) { mHandPos = _pos; }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline HandState GetState() { return mState; }
		__forceinline void SetState(HandState _state) { mState = _state; }

		__forceinline void SetAddPos(math::Vector2 _pos) { mAddPos = _pos; }

		__forceinline bool GetFinishFlag() { return mbFinish; }
		__forceinline void SetFinishFlag(bool _flag) { mbFinish = _flag; }

		__forceinline void SetPlayAnimationFlag(bool _flag) { mbPlayAnimation = _flag; }

		__forceinline bool GetFistSlamFlag() { return mbFistSlam; }
		__forceinline void SetFistSlamFlag(bool _flag) { mbFistSlam = _flag; }
		
		__forceinline bool GetEndFlag() { return mbEnd; }
		__forceinline void SetEndFlag(bool _flag) { mbEnd = _flag; }

	private:
		bool mbInitFlag = true;								// mInitAddPos 변수값 초기 세팅 플레그(Init이 아니라 Update에서 세팅하기에 필요함, 딱 한번만사용함)
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// 기준값(Body Pos 기준)에 더해주는 값(= 초기위치 구하는 용도)

		bool mbFinish = false;						// 본체에 수행이 끝났음을 알려준다.
		GameObject* mOwner = nullptr;				// 소유하고 있는 객체 저장
		HandPos mHandPos = HandPos::None;			// 좌, 우 구분
		bool mbPlayAnimation = true;				// 애니메이션 재생 여부
		HandState mState = HandState::None;			// 현재 상태
		HandState mPastState = HandState::None;		// 이전 상태 (애니메이션 재생여부 판별에 사용)
		math::Vector2 mAddPos = math::Vector2::Zero;// Hand 위치 수정시 실질적으로 사용하는 변수

		// Idle
		float mTime = 0.0f;					// 상태유지, 상하이동 플래그에 사용
		bool mUpDownFlag = false;			// Idle 상태에서 위, 아래 움직임 방향 바꿔주는 플래그 값

		// FistSlam Ready
		float mDepartHeight = 0.0f;			// 준비자세 시작 높이
		bool mbCollisionFloor = false;		// 벽 충돌여부

		// FistSlam Attack
		math::Vector2 mResetPos = math::Vector2::Zero;	// 복귀해야하는 위치(준비자세 최종위치)
		math::Vector2 dir = math::Vector2::Zero;		//
		bool mbFistSlam = false;						// 내려치기 완료여부

		// FistSlamAttack() 함수 인자값들
		bool mbDirectionSet = false;				// 내려칠 위치에 대한 방향벡터 구함 여부

		// FistSlam End
		bool mbEnd = false;
	};
}

