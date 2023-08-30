#pragma once
#include "vanSkill.h"

namespace van
{
	class FinishMoveReady : public Skill
	{
	public:
		enum class FinishMoveReadyState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		FinishMoveReady();
		virtual ~FinishMoveReady();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		__forceinline void SetState(FinishMoveReadyState _state) { mState = _state; }
		__forceinline FinishMoveReadyState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		FinishMoveReadyState mState = FinishMoveReadyState::None;
		//bool mbSetFlag = false;		// 애니메이션 재생을 위한 설정 완료 여부
		bool mbPlayAnimation = true;
	};
}

