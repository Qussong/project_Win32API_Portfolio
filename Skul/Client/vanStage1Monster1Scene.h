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
		virtual void MakeWorld() override;
		virtual void MakeFloor() override;
		virtual void MakeWall() override;
		virtual void MakeDoor() override;

		void Wave1();
		void Wave2();
		void WaveExit();
		void OpenDoor();
		
	private:
		bool mbWave1 = false;
		bool mbWave2 = false;
		bool mbOpenDoor = false;
	};
}

