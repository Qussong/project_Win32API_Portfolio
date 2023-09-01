#pragma once
#include "vanScene.h"
#include "vanYggdrasill.h"

namespace van
{
	class BackGround;
	class YggdrasillFrame;
	class YggdrasillHpBar;

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
		virtual void CameraMove() override;
		virtual void MakeWorld() override;
		virtual void MakeFloor() override;
		virtual void MakeWall() override;
		virtual void MakeDoor() override;

		void Phase2();
		void Phase3();

	private:
		BackGround* mBg = nullptr;

		Yggdrasill* mYgg = nullptr;
		Yggdrasill* mYgg2 = nullptr;
		Yggdrasill* mYgg3 = nullptr;
		float mTime = 0.0f;
		bool mbCameraEffect = true;

		YggdrasillFrame* yggFrame = nullptr;
		YggdrasillHpBar* mMageHpBar = nullptr;
		YggdrasillHpBar* mMageHpBar2 = nullptr;
	};
}