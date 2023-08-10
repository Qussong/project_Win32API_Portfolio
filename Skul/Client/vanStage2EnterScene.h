#pragma once
#include "vanScene.h"

namespace van
{
	class Stage2EnterScene : public Scene
	{
	public:
		Stage2EnterScene();
		virtual ~Stage2EnterScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
	};
}

