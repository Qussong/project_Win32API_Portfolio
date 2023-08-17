#pragma once
#include "vanScene.h"

namespace van
{
	class HomeScene : public Scene
	{
	public:
		HomeScene();
		virtual ~HomeScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;

		void NextScene();	// 낙하시 일정위치에 도달하면 다음 Scene으로 변경
		
	private:

	};
}

