#pragma once
#include "vanSkill.h"

namespace van
{
	class PhoenixLanding : public Skill
	{
	public:
		enum class PhoenixLandingState
		{
			Wait,
			LandingReady,
			LandingReadyEnd,
			Landing,
			LandingEnd,
			None,
		};

	public:
		PhoenixLanding();
		virtual ~PhoenixLanding();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void SetState(PhoenixLandingState _state) { mState = _state; }
		PhoenixLandingState GetState() { return mState; }

		void Wait();
		void LandingReady();
		void LandingReadyEnd();
		void Landing();
		void LandingEnd();

	private:
		PhoenixLandingState mState = PhoenixLandingState::None;
		bool mbPlayAnimation = true;
	};
}

