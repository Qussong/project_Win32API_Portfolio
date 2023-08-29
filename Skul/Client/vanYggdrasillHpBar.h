#pragma once
#include "vanUI.h"

namespace van
{
	class Yggdrasill;
	class Texture;

	class YggdrasillHpBar : public UI
	{
	public:
		YggdrasillHpBar();
		virtual ~YggdrasillHpBar();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		void SetMage(Yggdrasill* _ygg) { mYgg = _ygg; }

	private:
		Texture* mYggHpBar;
		Texture* mYggDamageBar;

		float mReductionHp = 0.0f;
		Yggdrasill* mYgg = nullptr;

	};
}

