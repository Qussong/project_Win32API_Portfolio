#pragma once
#include "vanScene.h"

namespace van
{
	class Stage1Monster1Scene : public Scene
	{
	public:
		Stage1Monster1Scene();
		virtual ~Stage1Monster1Scene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;

	private:

	};
}

