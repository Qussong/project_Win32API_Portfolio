#pragma once
#include "vanSkill.h"

namespace van
{
	class EnergyBomb : public Skill
	{
	public:
		enum class EnergyBombState
		{
			Gen,
			Active,
			Dead,
			None,
		};

	public:
		EnergyBomb();
		virtual ~EnergyBomb();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void SetState(EnergyBombState _state) { mState = _state; }
		EnergyBombState GetState() { return mState; }

		void Gen();
		void Active();
		void Dead();
		void SetEnergyBombPos();

	private:
		EnergyBombState mState = EnergyBombState::None;
		bool mbSetFlag = true;									// 객체 발사를 위한 설정 여부
		math::Vector2 mDepartPos = math::Vector2(0.0f, 0.0f);	// 발사지점
		math::Vector2 mTargetPos = math::Vector2(0.0f, 0.0f);	// 도착지점
		math::Vector2 mDirect = math::Vector2(0.0f, 0.0f);		// 방향벡터
	};
}
