#pragma once
#include "vanNPC.h"

namespace van
{
	class Druid : public NPC
	{
	public:
		Druid();
		virtual ~Druid();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	};
}

