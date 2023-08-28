#pragma once
#include "vanScene.h"
#include "vanWall.h"
namespace van
{
	class Mage;

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
		virtual void MakeWorld() override;
		virtual void MakeFloor() override;
		virtual void MakeWall() override;
		virtual void MakeDoor() override;

		void OpenDoor();
		void Wave1();
		void Wave2();
		void WaveExit();
		void BossTurn();

	private:
		bool mbWave1 = false;
		bool mbWave2 = false;
		bool mbOpenDoor = false;

		Wall* mBossWall1 = nullptr;
		Wall* mBossWall2 = nullptr;

		bool mbBossFlag = false;
		Mage* mage = nullptr;
	};
}