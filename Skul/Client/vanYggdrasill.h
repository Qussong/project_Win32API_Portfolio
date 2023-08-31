#pragma once
#include "vanBoss.h"
#include "vanYggdrasillBody.h"
#include "vanYggdrasillHead.h"
#include "vanYggdrasillChin.h"
#include "vanYggdrasillHand.h"

namespace van
{
	class EnergyBomb;
	class EnergyBombCharge;

	class Yggdrasill : public Boss
	{
	public:
		enum class BossSkill
		{
			FistSlam,
			Swipe,
			MagicOrbs,
			None,
		};

		enum class AttackHandDir
		{
			Left,
			Right,
			None
		};

	public:
		Yggdrasill();
		~Yggdrasill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		virtual void Gen() override;
		virtual void Idle() override;
		virtual void AttackReady() override;
		virtual void Attack() override;
		virtual void AttackEnd() override;
		virtual void Hit() override;
		virtual void Dead() override;

		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		void FistSlamAttack();	// 번갈아가면서 주먹찍기
		void SwipeAttack();		// 바닥 쓸기
		void MagicOrbsAttack();	// 광범위 레이저공격
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();
		void ShootEnergyBomb();

		void CmdDamage();
		void CmdSkill();
		void ChekDead();

		BossState GetState() { return mState; }
		void SetState(BossState _state) { mState = _state; }

		YggdrasillHead* GetHead() { return mHead; }

		math::Vector2 GetInitPos() { return mInitPos; }

		BossSkill GetAttackCase() { return mAttackCase; }
		void SetAttackCase(BossSkill _case) { mAttackCase = _case; }
		void SetDestroyFlag(bool _flag) { mbDestroy = _flag; }
	private:
		YggdrasillBody* mBody = nullptr;		// 몸체
		YggdrasillHead* mHead = nullptr;		// 머리
		YggdrasillChin* mChin = nullptr;		// 턱
		YggdrasillHand* mHandLeft = nullptr;	// 왼손
		YggdrasillHand* mHandRight = nullptr;	// 오른손

		int mHp = 0;
		int mArmor = 0;
		BossState mState = BossState::None;

		float mTime = 0.0f;
		bool mbChooseSkill = false;						// 공격스킬 선택 여부
		BossSkill mAttackCase = BossSkill::None;
		math::Vector2 mInitPos = math::Vector2::Zero;	// 최초 위치값 저장(초기화용)
		AttackHandDir mAttackDir = AttackHandDir::None;	// 공격을 수행할 Hand의 방향 저장

		// FistSlam
		int mFistSlamCnt = 0;

		// Swipe
		int mSwipCnt = 0;

		// MagicOrb
		EnergyBombCharge* mCharge = nullptr;
		bool mbShakeFlag = false;
		bool mbMagicOrbShootFlag = false;
		int mMagicOrbCnt = 0;
		bool mbShootDelay = false;

		bool mbCmd = false;
		int mCmdSkill = 0;
		bool mbDead = false;	// Dead 상태임 (= true)
		bool mbDestroy = false;	// 객체삭제 플레그 (= true)
	};
}

