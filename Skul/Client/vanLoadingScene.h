#pragma once
#include "vanScene.h"

namespace van
{
	class LoadingScene : public Scene
	{
		LoadingScene();
		virtual ~LoadingScene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
	};
}


