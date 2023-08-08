#pragma once
#include "vanMonster.h"

namespace van
{
	class MonsterTrace;
	class MonsterAttack;

	class CarleonRecruit : public Monster
	{
	public:
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
		void AttackEnd();
		void Hit();

	private:
		//MonsterTrace* mTraceBox;	// Monster의 Trace판정 범위
		//MonsterAttack* mAttackBox;	// Monster의 Attack판정 범위

		float mAttackDashX1 = 0.0f;		// AttackDash 시작지점
		float mAttackDashX2 = 0.0f;		// AttackDash 도착지점
	};
}

