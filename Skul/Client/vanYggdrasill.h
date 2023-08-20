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
		Yggdrasill();
		~Yggdrasill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남
		
		void AttackMelee();	// 번갈아가면서 주먹찍기
		void AttackSmash(); // 양손으로 바닥찍기
		void AttackRange();	// 광범위 레이저공격

	private:
		YggdrasillBody* mBody = nullptr;		// 몸체
		YggdrasillHead* mHead = nullptr;		// 머리
		YggdrasillChin* mChin = nullptr;		// 턱
		YggdrasillHand* mHandLeft = nullptr;	// 왼손
		YggdrasillHand* mHandRight = nullptr;	// 오른손

		int mHp;
		int mArmor;
	};
}

