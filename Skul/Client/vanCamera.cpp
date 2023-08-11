#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"

#define CAMERA_SPEED	500.0f

extern van::Application application;	// Client.cpp에 선언되어 있는 전역변수가져옴

namespace van
{

	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	math::Vector2 Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2 Camera::mHeightLimit = math::Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Init()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;
	}

	void Camera::Update()
	{

		// 카메라가 쳐다볼 타겟이 존재하면 해당 타겟을 따라다닌다.
		if (mTarget)	
		{
			Transform* tr = mTarget->GetComponent<Transform>();	// Target의 위치정보 가져온다
			mLookPosition = tr->GetPosition();					// 카메라가 쳐다보는위치로 설정
		}
		// 카메라의 타겟이 없다면 카메라를 조종할 수 있다.
		else
		{
			
			if (Input::GetKey(eKeyCode::Up))
			{
				mLookPosition.y -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Left))
			{
				mLookPosition.x -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Down))
			{
				mLookPosition.y += CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Right))
			{
				mLookPosition.x += CAMERA_SPEED * Time::GetDeltaTime();
			}
		}

		// 카메라가 타겟을 중심으로 보기 위해 이동할 거리
		mDistance = mLookPosition - (mResolution / 2.0f);		
		
		// [ 카메라 이동 제한 ]
		// 카메라가 이미지를 넘어가는 영역을 비추지 않게한다.
		// x축
		if (mDistance.x <= mWidthLimit.x)
		{
			mDistance.x = mWidthLimit.x;
		}
		if (mDistance.x >= mWidthLimit.y)
		{
			mDistance.x = mWidthLimit.y;
		}
		// y축
		if (mDistance.y <= mHeightLimit.x)
		{
			mDistance.y = mHeightLimit.x;
		}
		if (mDistance.y >= mHeightLimit.y)
		{
			mDistance.y = mHeightLimit.y;
		}
	}
}