#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanApplication.h"
#include "vanCamera.h"

extern van::Application application;

namespace van
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::Transform)
		, mScale(math::Vector2::One)
		, mTexture(nullptr)
		, mAffectCamera(true)
		, mAlpha(1.0f)
	{
		// nothing
	}

	SpriteRenderer::~SpriteRenderer()
	{
		// nothing
	}

	void SpriteRenderer::Init()
	{
		// nothing
	}

	void SpriteRenderer::Update()
	{
		// nothing
	}

	void SpriteRenderer::Render(HDC _hdc)
	{
		if (mTexture == nullptr)	// 그려줄 이미가 없을 때
			return;

		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		mTexture->Render(
			_hdc
			, tr->GetPosition()
			, math::Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, math::Vector2::Zero	// offset
			, mScale				// scale
			, mAlpha);				// alpha

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//math::Vector2 pos = tr->GetPosition();

		//// 카메라의 이동과 상관없이 화면상에서 항상 같은 위치에 있어야 할 땐 false
		//// 카메라의 이동에 따라 화면상에서 움직임이 필요한 경우 true
		//if (mAffectCamera == true)
		//	pos = Camera::CalculatePosition(pos);

		//// 그려줄 이미지의 확장자가 *.bmp 일때
		//if (mTexture->GetType() == eTextureType::Bmp)
		//{
		//	TransparentBlt(
		//		// 타겟
		//		_hdc
		//		, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)		// 이미지의 중심이 입력된 x좌표에 위치
		//		, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)	// 이미지의 중심이 입력된 y좌표에 위치
		//		, mTexture->GetWidth() * mScale.x
		//		, mTexture->GetHeight() * mScale.y
		//		// 원본
		//		, mTexture->GetHdc()
		//		, 0, 0
		//		, mTexture->GetWidth()
		//		, mTexture->GetHeight()
		//		// 생략 컬러
		//		, RGB(255, 0, 255));
		//}
		//// 그려줄 이미지가 alpha 값을 가지고 있는 *.bmp 일때
		//else if (mTexture->GetType() == eTextureType::AlphaBmp)
		//{
		//	// AlphaBlend() 설정
		//	BLENDFUNCTION func = {};
		//	int alpha = (int)(mAlpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	if (alpha <= 0)
		//		alpha = 0;
		//	func.SourceConstantAlpha = alpha;

		//	AlphaBlend(_hdc
		//		// 타겟
		//		, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)
		//		, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)
		//		, mTexture->GetWidth() * mScale.x
		//		, mTexture->GetHeight() * mScale.y
		//		// 원본
		//		, mTexture->GetHdc()
		//		, 0, 0
		//		, mTexture->GetWidth()
		//		, mTexture->GetHeight()
		//		// 설정
		//		, func);
		//}
		//// 그려줄 이미지의 확장자가 *.png 일때
		//else if (mTexture->GetType() == eTextureType::Png)
		//{
		//	Gdiplus::Graphics graphics(_hdc);
		//	graphics.DrawImage(
		//		mTexture->GetImage()
		//		, (int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
		//		, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
		//		, (int)(mTexture->GetWidth() * mScale.x)
		//		, (int)(mTexture->GetHeight() * mScale.y));
		//}
		//// 그려줄 이미지의 확장자가 *.bmp , *.png 가 아닐때
		//else
		//	__noop;
	}
}