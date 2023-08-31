#pragma once
#include "vanGameObject.h"

namespace van
{
	enum class CAM_EFFECT
	{
		FADE_IN,
		FADE_OUT,
		Pause,
		NONE,
	};

	struct tCamEffect
	{
		CAM_EFFECT	eEffect;
		float		fDuration;
		float		fCurTime;
		COLORREF	TexColor;
	};

	class Camera
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC _hdc);


		__forceinline static math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }
		__forceinline static GameObject* GetTarget() { return mTarget; }
		__forceinline static void SetTarget(GameObject* _target) { mTarget = _target; }
		__forceinline static void SetLimitDistance(math::Vector2 _widthLimit, math::Vector2 _heightLimit)
		{
			mWidthLimit = _widthLimit;
			mHeightLimit = _heightLimit;
		}
		__forceinline static void SetCameraOffset(math::Vector2 _offset) { mCameraOffset = _offset; }
		__forceinline static math::Vector2 GetCameraOffset() { return mCameraOffset; }
		__forceinline static void CameraOffsetClear() { mCameraOffset = math::Vector2::Zero; }
		static void SetCameraOffsetSmooth(math::Vector2 _offset, int _doubleSpeed);
		static void ClearCameraOffsetSmooth(int _doubleSpeed = 1);

		static math::Vector2 GetLookPosition() { return mLookPosition; }
		static void SetLookPosition(math::Vector2 _pos) { mLookPosition = _pos; }

	public:
		static void fadeIn(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_IN;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

		static void fadeOut(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_OUT;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

		static void Pause(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::Pause;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

	private:
		static math::Vector2 mResolution;	// 화면 해상도
		static math::Vector2 mLookPosition;	// 카메라가 바라보고 있는 위치
		static math::Vector2 mDistance;		// 가운데를 원점으로 이동한 거리
		static GameObject* mTarget;			// 카메라가 바라보는 GameObject 객체
		static math::Vector2 mCameraOffset;	// 카메라 offset
		// 카메라 이동 제한값 설정
		static math::Vector2 mWidthLimit;	// width.x = Left, width.y = Right
		static math::Vector2 mHeightLimit;	// height.x = Up, height.y = Down

	private:
		static std::list<tCamEffect>  m_listCamEffect;	// 카메라 효과 이벤트 리스트
		static class Texture* mWhiteTex;				// 카메라 효과용 텍스쳐
		static class Texture* mBlackTex;				// 카메라 효과용 텍스쳐
	};
}

