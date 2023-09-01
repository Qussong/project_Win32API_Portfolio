#pragma once
#include "vanScene.h"

namespace van
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		virtual ~LoadingScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;

		void LoadTexture();

	private:
		float mTime = 0.0f;
	};
}


