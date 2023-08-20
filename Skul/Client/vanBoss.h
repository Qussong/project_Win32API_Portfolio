#pragma once
#include "vanGameObject.h"

namespace van
{
	class Boss : public GameObject
	{
	public:
		enum class BossState
		{
			Gen,
			Idle,
			AttackReady,
			Attack,
			AttackEnd,
			Hit,
			Dead,
			None
		};

		enum class BossDirection
		{
			Left,
			Right,
			Center,
			None
		};

	public:
		Boss();
		~Boss();
		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		BossState GetBossState() { return mBossState; }
		void SetBossState(BossState _state) { mBossState = _state; }

		__forceinline float GetTimer() { return mTimer; }
		__forceinline void SetTimer(float _timer) { mTimer = _timer; }
		__forceinline void AddTimer(float _time) { mTimer += _time; }

	private:
		BossState mBossState = BossState::None;
		float mTimer;
	};
}

