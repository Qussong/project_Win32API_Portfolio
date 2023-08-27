#pragma once
#include "vanScene.h"
#include "vanBackGround.h"

namespace van
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		BackGround* mBackGround;
		bool mbPlayAnimation = true;
	};
}

