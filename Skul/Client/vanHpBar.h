#pragma once
#include "vanUI.h"

namespace van
{
	class Player;
	class Texture;

	class HpBar : public UI
	{
	public:
		HpBar();
		virtual ~HpBar();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

	private:
		Texture* mHpBar;
		Texture* mDamageBar;

		float mReductionHp = 0.0f;
		Player* mPlayer = nullptr;
	};
}

