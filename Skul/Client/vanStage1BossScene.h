#pragma once
#include "vanScene.h"

namespace van
{
	class Stage1BossScene : public Scene
	{
	public:
		Stage1BossScene();
		virtual ~Stage1BossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:

	};
}

