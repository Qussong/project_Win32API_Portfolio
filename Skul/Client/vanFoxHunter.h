#pragma once
#include "vanNPC.h"

namespace van
{
	class FoxHunter : public NPC
	{
	public:
		FoxHunter();
		virtual ~FoxHunter();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	};
}