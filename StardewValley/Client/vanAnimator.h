#pragma once
#include "vanComponent.h"

namespace van
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		

	private:

	};
}

