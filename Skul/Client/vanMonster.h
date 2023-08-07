#pragma once
#include "vanGameObject.h"


namespace van
{
	class Animator;

	class Monster : public GameObject
	{
	public:
		enum class MonsterState
		{
			Idle,
			Walk,
			Patrol,
			Trace,
			AttackReady,
			Attack,
			Hit,
			None,
		};

		enum class MonsterDirection
		{
			Left,
			Right,
			None,
		};

		Monster();
		virtual ~Monster();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		__forceinline GameObject* GetMonsterTarget() { return mTarget; }
		__forceinline void SetMonsterTarget(GameObject* _target) { mTarget = _target; }

		__forceinline MonsterState GetMonsterState() { return mState; }
		__forceinline void SetMonsterState(MonsterState _state) { mState = _state; }
		
		__forceinline MonsterState GetMonsterPastState() { return mPastState; }
		__forceinline void SetMonsterPastState(MonsterState _state) { mPastState = _state; }

		__forceinline MonsterDirection GetMonsterDirection() { return mDirection; }
		__forceinline void SetMonsterDirection(MonsterDirection _direction) { mDirection = _direction; }

		__forceinline MonsterDirection GetMonsterPastDirection() { return mPastDirection; }
		__forceinline void SetMonsterPastDirection(MonsterDirection _direction) { mPastDirection = _direction; }

		__forceinline MonsterDirection GetMonsterHitDirection() { return mHitDirection; }
		__forceinline void SetMonsterHitDirection(MonsterDirection _direction) { mHitDirection = _direction; }

		__forceinline bool GetPatrolFlag() { return mbPatrol; }
		__forceinline void SetPatrolFlag(bool _flag) { mbPatrol = _flag; }

		__forceinline bool GetTraceFlag() { return mbTrace; }
		__forceinline void SetTraceFlag(bool _flag) { mbTrace = _flag; }

		__forceinline bool GetAttackFlag() { return mbAttack; }
		__forceinline void SetAttackFlag(bool _flag) { mbAttack = _flag; }

		__forceinline bool GetPlayAnimation() { return mbPlayAnimation; }
		__forceinline void SetPlayAnimation(bool _flag) { mbPlayAnimation = _flag; }

	private:
		GameObject* mTarget;			// Monster의 목표대상(Trace)

		MonsterState mState;
		MonsterState mPastState;

		MonsterDirection mDirection;
		MonsterDirection mPastDirection;

		MonsterDirection mHitDirection;

		bool mbPatrol;			// Monster가 각 상태에서 Patrol 행동을 보이도록 해줌
		bool mbTrace;			// Monster가 각 상태에서 Trace 행동을 보이도록 해줌
		bool mbAttack;			// Monster가 각 상태에서 Attack 행동을 보이도록 해줌
		bool mbPlayAnimation;	// Animation 재생 여부
	};
}

