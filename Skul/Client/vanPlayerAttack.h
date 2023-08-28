#pragma once
#include "vanRange.h"

namespace van
{
	class PlayerAttack : public Range
	{
	public:
		PlayerAttack();
		virtual ~PlayerAttack();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		__forceinline std::set<GameObject*>* GetAttackList() { return &attackList; }

		float GetPlayerAttackDamage() { return mAttackDamage; }

		bool GetActiveFlag() { return mActiveFlag; }

	private:
		std::set <GameObject*> attackList;	// 충돌한 GameObject 들을 저장
		bool mbCombo;						// Attack이 콤보로 이어질지에대한 여부(true = 콤보o, false = 콤보x)
		float mAttackDamage;
		bool mActiveFlag = false;
	};
}

