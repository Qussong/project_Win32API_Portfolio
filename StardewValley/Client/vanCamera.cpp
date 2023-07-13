#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"


extern van::Application application;	// Client.cpp에 선언되어 있는 전역변수가져옴

namespace van
{
	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Init()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;
	}
	void Camera::Update()
	{
		if (mTarget)	// Camera가 쳐다볼 Target이 존재할 때
		{
			Transform* tr = mTarget->GetComponent<Transform>();	// Target의 위치정보 가져온다
			mLookPosition = tr->GetPosition();					// 카메라가 쳐다보는위치로 설정
		}

		mDistance = mLookPosition - (mResolution / 2.0f);		// 카메라가 보는 위치 수정
	}
}