#pragma once
#include "vanGameObject.h"

namespace van
{
	class BackGround : public GameObject
	{
	public:
		BackGround();
		BackGround(math::Vector2 _offset);
		virtual ~BackGround();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		void SetLimitLeft(float _left) { mCameraLimitLeft = _left; }
		float GetLimitLeft() { return mCameraLimitLeft; }

		void SetLimitRight(float _right) { mCameraLimitRight = _right; }
		float GetLimitRight() { return mCameraLimitRight; }

		void SetLimitUp(float _up) { mCameraLimitUp = _up; }
		float GetLimitUp() { return mCameraLimitUp; }

		void SetLimitDown(float _down) { mCameraLimitDown = _down; }
		float GetLimitDown() { return mCameraLimitDown; }

		void SetAutoCameraLimit();	// 카메라 이동제한

	private:
		// (회색화면이 보이지않게) 카메라가 움직일 수 있는 
		float mCameraLimitLeft;
		float mCameraLimitRight;
		float mCameraLimitUp;
		float mCameraLimitDown;
	};
}

