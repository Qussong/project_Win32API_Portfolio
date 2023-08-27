#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	BackGround::BackGround()
	{
		AddComponent<SpriteRenderer>();
	}

	BackGround::BackGround(math::Vector2 _offset)
	{
		// nothing
	}

	BackGround::~BackGround()
	{
		// nothing
	}

	void BackGround::Init()
	{
		MakeAnimation();
	}

	void BackGround::Update()
	{
		GameObject::Update();
	}

	void BackGround::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void BackGround::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"BG_Intro", ResourceManager::Find<Texture>(L"BG_Intro"), math::Vector2(0.0f, 0.0f), math::Vector2(1920.0f, 1080.0f), 40);
		at->CreateAnimation(L"BG_Intro_Loop", ResourceManager::Find<Texture>(L"BG_Intro_Loop"), math::Vector2(0.0f, 0.0f), math::Vector2(1920.0f, 1080.0f), 11);
		at->SetScale(math::Vector2(0.67f, 0.67f));
	}

	void BackGround::SetAutoCameraLimit()
	{
		// SpriteRender의 주소값 저장
		SpriteRenderer* bgsr = this->GetComponent<SpriteRenderer>();
		math::Vector2 scale = bgsr->GetScale();

		// SpriteRender 없으면 함수 종료
		if (nullptr == bgsr)
		{
			return;
		}
		// 배경 이미지 불러옴
		Texture* image = bgsr->GetTexture();
		// 이미지가 없으면 함수 종료
		if (nullptr == image)
		{
			return;
		}
		// BackGround 객체의 위치값 저장
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		// 배경 이미지의 사이즈 절반값 저장(현재 배경이 그려지는 scale도 고려)
		math::Vector2 imageSize = (image->GetSize() * scale) / 2.0f;

		float tempLimitX = std::fabsf(pos.x - imageSize.x);
		float tempLimitY = std::fabsf(pos.y - imageSize.y);

		mCameraLimitLeft	= -tempLimitX;	// 왼쪽 최대 이동가능 거리
		mCameraLimitRight	= tempLimitX;	// 오른쪽 최대 이동가능 거리
		mCameraLimitUp		= -tempLimitY;	// 위쪽 최대 이동가능 거리
		mCameraLimitDown	= tempLimitY;	// 아래쪽 최대 이동가능 거
	}
}