#pragma once
#include "vanGameObject.h"

namespace van
{
	class NPC : public GameObject
	{
	public:
		NPC();
		virtual ~NPC();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	};
}

