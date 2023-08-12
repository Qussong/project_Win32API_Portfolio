#pragma once
#include "vanNPC.h"

namespace van
{
	class DeathKnight : public NPC
	{
	public:
		DeathKnight();
		virtual ~DeathKnight();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	};
}

