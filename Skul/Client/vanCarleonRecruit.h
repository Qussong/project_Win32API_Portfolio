#pragma once
#include "vanMonster.h"

namespace van
{
	class MonsterTrace;

	class CarleonRecruit : public Monster
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

		CarleonRecruit();
		virtual ~CarleonRecruit();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		void Idle();
		void Walk();
		void Patrol();
		void Trace();
		void AttackReady();
		void Attack();
		void Hit();

		__forceinline bool GetAttackFlag() { return mbAttack; }
		__forceinline void SetAttackFlag(bool _flag) { mbAttack = _flag; }

		__forceinline bool GetTraceFlag() { return mbTrace; }
		__forceinline void SetTraceFlag(bool _flag) { mbTrace = _flag; }

	private:
		MonsterState mState;
		MonsterDirection mDirection;
		MonsterDirection mHitDirection;
		float mTimer;
		bool mbPatrol;
		bool mbPlayAnimation;
		bool mbHit;
		bool mbAttack;	// Attack 범위 판정
		bool mbTrace;	// Trace 범위 판정

		MonsterTrace* traceBox;				// Monster의 Trace판정 범위
	};
}

