#pragma once
#include "vanScene.h"

namespace van
{
	class StageScene : public Scene
	{
	public:
		StageScene();
		virtual ~StageScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}

