#pragma once
#include "vanSkill.h"

namespace van
{
	class EnergyBall : public Skill
	{
	public:
		enum class EnergyBallState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		EnergyBall();
		virtual ~EnergyBall();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void Gen();
		void Active();
		void Dead();

		__forceinline void SetState(EnergyBallState _state) { mState = _state; }
		__forceinline EnergyBallState GetState() { return mState; }

		__forceinline void AddBallDestroyCnt() { mDestroyBallCnt += 1; }

	private:
		EnergyBallState mState = EnergyBallState::None;
		bool mbSetFlag = true;
		//std::map<int, EnergyBallObject*> list;
		int mDestroyBallCnt = 0;
	};
}