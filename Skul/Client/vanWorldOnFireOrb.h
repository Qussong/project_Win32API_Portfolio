#pragma once
#include "vanSkill.h"

namespace van
{
	class WorldOnFireFireBall;

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

		void Gen();
		void Active();
		void Dead();

		__forceinline void SetState(OrbState _state) { mState = _state; }
		__forceinline OrbState GetState() { return mState; }

		__forceinline GameObject* GetTarget() { return mTarget; }

		__forceinline void AddFireBallDeadCnt() { mFireBallDeadCnt += 1; }
	private:
		OrbState mState = OrbState::None;
		GameObject* mTarget = nullptr;
		bool mbShoot = true;	// FireBall 발사 유무
		float mShootDelay = 0.0f;	// FireBall 발사 Delay
		int mFireBallCnt = 0;
		int mFireBallDeadCnt = 0;
	};
}

