#pragma once
#include "vanSkill.h"

namespace van
{
	class PhoenixRandingReady : public Skill
	{
	public:
		enum class PhoenixRandingReadyState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		PhoenixRandingReady();
		virtual ~PhoenixRandingReady();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		__forceinline void SetState(PhoenixRandingReadyState _state) { mState = _state; }
		__forceinline PhoenixRandingReadyState GetState() { return mState; }

		__forceinline bool GetEffectFinishFlag() { return mbEffectFinish; }

		void Gen();
		void Active();
		void Dead();

	private:
		PhoenixRandingReadyState mState = PhoenixRandingReadyState::None;
		bool mbSetFlag = false;		// 애니메이션 재생을 위한 설정 완료 여부
		bool mbEffectFinish = false;
	};
}

