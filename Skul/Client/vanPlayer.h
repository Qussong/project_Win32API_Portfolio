#pragma once
#include "vanGameObject.h"



namespace van
{
	class Animator;
	class PlayerAttack;
	class Skull;

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
			DownFall,
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

		void Skill();

		__forceinline PlayerDirection GetPlayerDirection() { return mDirection; }
		__forceinline PlayerState GetPlayerState() { return mState; }
		__forceinline bool GetCombo() { return mbCombo; }

		__forceinline float GetHp() { return mHp; }
		__forceinline void SetHp(float _hp) { mHp = _hp; }
		__forceinline float GetMaxHp() { return mMaxHp; }
		__forceinline float SetMaxHp(float _hp) { mMaxHp = _hp; }
		__forceinline void AddHp(float _hp) 
		{ 
			mHp += _hp; 
			if (mHp > mMaxHp)
			{
				mHp = mMaxHp;
			}
		}
		__forceinline void LoseHp(float _hp) 
		{
			mHp -= _hp;
			if (mHp < 0)
			{
				mHp = 0;
			}
		}

		__forceinline float GetCoin() { return mCoin; }
		__forceinline void SetCoin(float _coin) { mCoin = _coin; }
		__forceinline void AddCoin(float _coin) { mCoin += _coin; }
		__forceinline void LoseCoin(float _coin) { mCoin -= _coin; }

		__forceinline float GetBone() { return mBone; }
		__forceinline void SetBone(float _bone) { mBone = _bone; }
		__forceinline float GetJewelry() { return mJewelry; }
		__forceinline void SetJewelry(float _jewelry) { mJewelry = _jewelry; }

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

		float mHp;
		float mMaxHp = 100.0f;
		float mCoin;
		float mBone;
		float mJewelry;

		bool mbSkullLess;	// 머리 유무
		bool mbSkillFlag;	//	스킬 발동여부
		float mHeadTime;
		float mCoolTime;

		Skull* head;
	};
}