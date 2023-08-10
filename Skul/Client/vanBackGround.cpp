#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"

namespace van
{
	BackGround::BackGround()
	{
		// nothing
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
		// nothing
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
		// nothing
	}
	void BackGround::SetAutoCameraLimit()
	{
		// SpriteRender의 주소값 저장
		SpriteRenderer* bgsr = this->GetComponent<SpriteRenderer>();
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
		// 배경 이미지의 사이즈 절반값 저장
		math::Vector2 imageSize = image->GetSize() / 2.0f;

		math::Vector2 tempLimitX = pos.x - imageSize.x;
		math::Vector2 tempLimitY = pos.y - imageSize.y;

		tempLimitX.x = std::fabsf(tempLimitX.x);
		tempLimitX.y = std::fabsf(tempLimitX.y);
		tempLimitY.x = std::fabsf(tempLimitY.x);
		tempLimitY.y = std::fabsf(tempLimitY.y);

		mCameraLimitLeft = -tempLimitX.x;	// 왼쪽 최대 이동가능 거리
		mCameraLimitRight = tempLimitX.y;	// 오른쪽 최대 이동가능 거리
		mCameraLimitUp = -tempLimitY.x;		// 위쪽 최대 이동가능 거리
		mCameraLimitDown = tempLimitY.y;	// 아래쪽 최대 이동가능 거리
	}
}