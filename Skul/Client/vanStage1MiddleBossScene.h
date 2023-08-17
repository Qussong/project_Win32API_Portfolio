#pragma once
#include "vanScene.h"

namespace van
{
	class Stage1MiddleBossScene : public Scene
	{
	public:
		Stage1MiddleBossScene();
		virtual ~Stage1MiddleBossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;

	private:
	};
}

