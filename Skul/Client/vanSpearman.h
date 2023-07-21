#pragma once
#include "vanMonster.h"

namespace van
{
	class Spearman : public Monster
	{
	public:
		Spearman();
		virtual ~Spearman();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

		
	};
}