#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"

#define CAMERA_SPEED			500.0f
#define CAMERA_OFFSET_SPEED		10.0f	// Camera의 offset 값을 10의 단위로 조정한다.

extern van::Application application;	// Client.cpp에 선언되어 있는 전역변수가져옴

namespace van
{

	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	math::Vector2 Camera::mCameraOffset = math::Vector2::Zero;

	GameObject* Camera::mTarget = nullptr;

	math::Vector2 Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2 Camera::mHeightLimit = math::Vector2::Zero;

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
			Transform* tr = mTarget->GetComponent<Transform>();		// Target의 위치정보 가져온다
			mLookPosition = (tr->GetPosition()) + mCameraOffset;	// 카메라가 쳐다보는위치로 설정
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

	void Camera::SetCameraOffsetSmooth(math::Vector2 _offset, int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// 현재 offset 값과 목표치 offset 값의 차이가 10보다 작은지 확인
		if (fabs(_offset.x - mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(_offset.y - mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x값 조정
		if (mCameraOffset.x != _offset.x)
		{
			if (_offset.x > 0 && flagX)
			{
				mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.x < 0 && flagX)
			{
				mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagX)
			{
				mCameraOffset.x = _offset.x;
			}
		}

		// offset y값 조정
		if (mCameraOffset.y != _offset.y)
		{
			if (_offset.y > 0 && flagY)
			{
				mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.y < 0 && flagY)
			{
				mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagY)
			{
				mCameraOffset.y = _offset.y;
			}
		}

	}

	void Camera::ClearCameraOffsetSmooth(int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// offset 값이 10보다 작은지 확인
		if (fabs(mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x값 조정
		if (mCameraOffset.x > 0
			&& flagX)
		{
			mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.x < 0
			&& flagX)
		{
			mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagX)
		{
			mCameraOffset.x = 0.0f;
		}

		// offset y값 조정
		if (mCameraOffset.y > 0
			&& flagY)
		{
			mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.y < 0
			&& flagY)
		{
			mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagY)
		{
			mCameraOffset.y = 0.0f;
		}
	}

}