#pragma once
#include "vanNPC.h"

namespace van
{
	class Witch	: public NPC
	{
	public:
		Witch();
		virtual ~Witch();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:

	};
}

