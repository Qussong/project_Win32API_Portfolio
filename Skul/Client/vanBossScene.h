#pragma once
#include "vanScene.h"

namespace van
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

