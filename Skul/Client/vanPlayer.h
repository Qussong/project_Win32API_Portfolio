#pragma once
#include "vanGameObject.h"

namespace van
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

