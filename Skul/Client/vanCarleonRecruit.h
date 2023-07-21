#pragma once
#include "vanMonster.h"

namespace van
{
	class CarleonRecruit : public Monster
	{
	public:
		CarleonRecruit();
		virtual ~CarleonRecruit();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

