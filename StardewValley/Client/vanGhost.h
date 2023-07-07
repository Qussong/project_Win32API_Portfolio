#pragma once
#include "vanGameObject.h"

namespace van
{
	class Ghost : public GameObject
	{
	public:
		Ghost();
		virtual ~Ghost();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

