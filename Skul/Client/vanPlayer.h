#pragma once
#include "vanGameObject.h"



namespace van
{
	class Animator;
	class Attack;

	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Idle,
			Walk,
			Jump,
			Dash,
			AttackA,
			AttackB,
			JumpAttack,
			DoubleJump,
			DoubleDash,
			Fall,
			None,
		};
		
		enum class PlayerDirection
		{
			Left,
			Right,
			None,
		};

		Player();
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		//void ChangeState(PlayerState _state);
		//void StillSameState();

		void ShowStatus(HDC _hdc);

		void Idle();
		void Walk();
		void Jump();
		void Dash();
		void AttackA();
		void AttackB();
		void JumpAttack();
		void DoubleJump();
		void DoubleDash();
		void Fall();

		__forceinline PlayerDirection GetPlayerDirection() { return mDirection; }
		__forceinline PlayerState GetPlayerState() { return mState; }

	private:
		PlayerState mState;
		PlayerDirection mDirection;
		bool mbDoubleKey;
		UINT mJumpCnt;
		UINT mDashCnt;
		BOOL mbCombo;
		BOOL mbMove;
		BOOL mbMove2;
		float mTime = 0.0f;
		float mDashX1 = 0.0f;
		float mDashX2 = 0.0f;
		float mAttackDashX1 = 0.0f;
		float mAttackDashX2 = 0.0f;

		Attack* attackBox;
	};
}


