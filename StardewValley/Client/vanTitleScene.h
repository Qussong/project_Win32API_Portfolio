#pragma once
#include "vanScene.h"

namespace van
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

	private:

	};
}

