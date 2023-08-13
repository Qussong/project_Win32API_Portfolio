#pragma once
#include "vanNPC.h"

namespace van
{
	class CatSeol : public NPC
	{
	public:
		CatSeol();
		virtual ~CatSeol();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void Idle() override;
		virtual void Walk() override;
		virtual void Patrol() override;

	private:

	};
}

