#pragma once
#include "vanScene.h"

namespace van
{
	class Stage2BossEnterScene : public Scene
	{
	public:
		Stage2BossEnterScene();
		virtual ~Stage2BossEnterScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
	};
}

