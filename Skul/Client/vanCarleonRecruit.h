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

		void Idle();
		void Walk();
		void Patrol();
		void AttackReady();
		void Attack();

	private:
		MonsterState mState;
		MonsterDirection mDirection;
		float mTimer;
		BOOL mbPatrol;
		BOOL mbPlayAnimation;
	};
}

