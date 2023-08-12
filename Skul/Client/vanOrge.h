#pragma once
#include "vanNPC.h"

namespace van
{
	class Orge : public NPC
	{
	public:
		Orge();
		virtual ~Orge();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

	private:
	
	};
}

