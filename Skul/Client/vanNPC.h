#pragma once
#include "vanGameObject.h"

namespace van
{
	class NPC : public GameObject
	{
	public:
		enum class NPCState
		{
			Idle,
			Walk,
			Patrol,
			None,
		};

		enum class NPCDirection
		{
			Left,
			Right,
			None,
		};

	public:
		NPC();
		virtual ~NPC();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void Idle();
		virtual void Walk();
		virtual void Patrol();

		__forceinline NPCState GetNPCState() { return mState; }
		__forceinline void SetNPCState(NPCState _state) { mState = _state; }

		__forceinline NPCState GetNPCPastState() { return mPastState; }
		__forceinline void SetNPCPastState(NPCState _state) { mPastState = _state; }

		__forceinline NPCDirection GetNPCDirection() { return mDirection; }
		__forceinline void SetNPCDirection(NPCDirection _direction) { mDirection = _direction; }

		__forceinline NPCDirection GetNPCPastDirection() { return mPastDirection; }
		__forceinline void SetNPCPastDirection(NPCDirection _direction) { mPastDirection = _direction; }

		__forceinline float GetTimer() { return mTimer; }
		__forceinline void SetTimer(float _timer) { mTimer = _timer; }
		__forceinline void AddTimer(float _time) { mTimer += _time; }

		__forceinline bool GetPatrolFlag() { return mbPatrol; }
		__forceinline void SetPatrolFlag(bool _flag) { mbPatrol = _flag; }

		__forceinline bool GetPlayAnimation() { return mbPlayAnimation; }
		__forceinline void SetPlayAnimation(bool _flag) { mbPlayAnimation = _flag; }

	private:
		NPCState mState;
		NPCState mPastState;
		NPCDirection mDirection;
		NPCDirection mPastDirection;

		float mTimer;
		bool mbPatrol;
		bool mbPlayAnimation;
	};
}

