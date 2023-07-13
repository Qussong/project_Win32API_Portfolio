#pragma once
#include "vanGameObject.h"

namespace van
{
	class Camera
	{
	public:
		static void Init();
		static void Update();

		static math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }
		static GameObject* GetTarget() { return mTarget; }
		static void SetTarget(GameObject* _target) { mTarget = _target; }

	private:
		
		static math::Vector2 mResolution;	// 화면 해상도
		static math::Vector2 mLookPosition;	// 카메라가 바라보고 있는 위치
		static math::Vector2 mDistance;		// 가운데를 원점으로 이동한 거리
		static GameObject* mTarget;			// 카메라가 바라보는 GameObject 객체
	};
}

