#pragma once
#include "vanGameObject.h"



namespace van
{
	class Animator;
	class PlayerAttack;

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

		void ShowStatus(HDC _hdc);	// Player 관련 각종 정보를 화면 죄측 상단에 출력
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
		//__forceinline void SetPlayerState(PlayerState _state) { mState = _state; }
		__forceinline bool GetCombo() { return mbCombo; }

	private:
		PlayerState mState;				// 현재 Player의 상태
		PlayerDirection mDirection;		// 현재 Player가 바라보고 있는 방향 (Left, Right)
		bool mbDoubleKey;				// 이중키 입력 여부 (방향키에서 사용)
		UINT mJumpCnt;					// Jump 횟수 (최대 2번)
		UINT mDashCnt;					// Dash 횟수 (최대 2번)
		bool mbCombo;					// AttackA 다음 AttackB 수행여부
		bool mbAttackMove;				// AttackA시 위치 이동 여부
		bool mbAttackMove2;				// AttackB시 위치 이동 여부
		float mDashX1 = 0.0f;			// Dash 시작지점
		float mDashX2 = 0.0f;			// Dash 도착지점
		float mAttackDashX1 = 0.0f;		// AttackDash 시작지점
		float mAttackDashX2 = 0.0f;		// AttackDash 도착지점
		PlayerAttack* attackBox;		// Player의 기본공격 충돌 판정 범위

		bool mbFallAniFlag = true;
		bool mbFallRepeatAniFlag = true;
	};
}