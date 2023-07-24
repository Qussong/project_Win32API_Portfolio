#pragma once
#include "vanNPC.h"

namespace van
{
	class TiedSkul : public NPC
	{
	public:
		TiedSkul();
		virtual ~TiedSkul();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	};
}

