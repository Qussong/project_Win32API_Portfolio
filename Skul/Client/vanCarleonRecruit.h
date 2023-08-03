#pragma once
#include "vanMonster.h"

namespace van
{
	class CarleonRecruit : public Monster
	{
	public:
		enum class MonsterState
		{
			Idle,
			Walk,
			Patrol,
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
		void AttackReady();
		void Attack();
		void Hit();

	private:
		MonsterState mState;
		MonsterDirection mDirection;
		MonsterDirection mHitDirection;
		float mTimer;
		bool mbPatrol;
		bool mbPlayAnimation;
	};
}

