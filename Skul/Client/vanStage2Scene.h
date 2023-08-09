#pragma once
#include "vanScene.h"

namespace van
{
	class Stage2Scene : public Scene
	{
	public:
		Stage2Scene();
		virtual ~Stage2Scene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
	};
}

