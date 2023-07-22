#pragma once
#include "vanGameObject.h"


namespace van
{
	class Animator;

	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(math::Vector2 _offset);
		virtual ~Monster();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
		Animator* animator;
	};
}

