#pragma once
#include "vanMonster.h"

namespace van
{
	class GianticEnt : public Monster
	{
	public:
		GianticEnt();
		virtual ~GianticEnt();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		virtual void Gen();
		virtual void Idle();
		virtual void Walk();
		virtual void Patrol();
		virtual void Trace();
		virtual void AttackReady();
		virtual void Attack();
		virtual void AttackEnd();
		virtual void Hit();
		virtual void Dead();
		virtual void Wall();

	private:

	};
}

