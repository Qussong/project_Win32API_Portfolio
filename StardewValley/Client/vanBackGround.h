#pragma once
#include "vanGameObject.h"

namespace van
{
	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

