#pragma once
#include "vanSkill.h"


namespace van
{
	class FireBall : public Skill
	{
	public:
		enum class FireBallState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		FireBall();
		virtual ~FireBall();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void SetState(FireBallState _state) { mState = _state; }
		FireBallState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();
		void SetFireBallMove();

	private:
		FireBallState mState = FireBallState::None;
	};
}

