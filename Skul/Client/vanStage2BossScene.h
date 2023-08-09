#pragma once
#include "vanScene.h"

namespace van
{
	class Stage2BossScene : public Scene
	{
	public:
		Stage2BossScene();
		virtual ~Stage2BossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
	};
}

