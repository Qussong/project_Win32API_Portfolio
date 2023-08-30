#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireOrb : public Skill
	{
	public:
		enum class OrbState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		WorldOnFireOrb();
		virtual ~WorldOnFireOrb();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void SetState(OrbState _state) { mState = _state; }
		OrbState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();

	private:
		OrbState mState = OrbState::None;
	};
}

