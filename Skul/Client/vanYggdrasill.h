#pragma once
#include "vanBoss.h"
#include "vanYggdrasillBody.h"
#include "vanYggdrasillHead.h"
#include "vanYggdrasillChin.h"
#include "vanYggdrasillHand.h"

namespace van
{
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
		void FistSlam();	// 번갈아가면서 주먹찍기
		void Swipe();		// 바닥 쓸기
		void MagicOrbs();	// 광범위 레이저공격
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		BossState GetState() { return mState; }
		void SetState(BossState _state) { mState = _state; }

		YggdrasillHead* GetHead() { return mHead; }

		math::Vector2 GetInitPos() { return mInitPos; }

		void AddFistSlamCnt() { mFistSlamCnt += 1; }
		int GetFistSlamCnt() { return mFistSlamCnt; }

		BossSkill GetAttackCase() { return mAttackCase; }
		void SetAttackCase(BossSkill _case) { mAttackCase = _case; }

	private:
		YggdrasillBody* mBody = nullptr;		// 몸체
		YggdrasillHead* mHead = nullptr;		// 머리
		YggdrasillChin* mChin = nullptr;		// 턱
		YggdrasillHand* mHandLeft = nullptr;	// 왼손
		YggdrasillHand* mHandRight = nullptr;	// 오른손

		BossState mState = BossState::None;

		float mTime = 0.0f;

		int mHp;
		int mArmor;
		bool mbChooseSkill = false;				// 공격스킬 선택 여부
		BossSkill mAttackCase = BossSkill::None;
		math::Vector2 mInitPos = math::Vector2::Zero;

		int mFistSlamCnt = 0;
	};
}

