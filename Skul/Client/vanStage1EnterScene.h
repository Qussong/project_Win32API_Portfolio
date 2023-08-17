#pragma once
#include "vanScene.h"

namespace van
{
	class Stage1EnterScene : public Scene
	{
	public:
		Stage1EnterScene();
		virtual ~Stage1EnterScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;

	private:

	};
}

