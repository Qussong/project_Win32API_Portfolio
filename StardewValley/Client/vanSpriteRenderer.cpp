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

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (mAffectCamera == true)
			pos = Camera::CalculatePosition(pos);

		// 그려줄 이미지의 확장자가 *.bmp 일때
		if (mTexture->GetType() == eTextureType::Bmp)
		{
			// 배경객체
			if (GetOwner()->GetMyType() == enums::eGameObjectType::BackGround)
			{
				if (mAlpha < 1.0f)	// 투명화 여부
				{
					BLENDFUNCTION func = {};
					int alpha = (int)(mAlpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255

					func.BlendOp = AC_SRC_OVER;
					func.BlendFlags = 0;
					func.AlphaFormat = AC_SRC_ALPHA;
					if (alpha <= 0)
						alpha = 0;
					func.SourceConstantAlpha = alpha;

					AlphaBlend(_hdc
						// 타겟
						, (int)pos.x /*- (mTexture->GetWidth() * mScale.x / 2.0f)*/
						, (int)pos.y /*- (mTexture->GetHeight() * mScale.y / 2.0f)*/
						, mTexture->GetWidth() * mScale.x
						, mTexture->GetHeight() * mScale.y
						// 원본
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth()
						, mTexture->GetHeight()
						// 설정
						, func);
				}
				else
				{
					TransparentBlt(
						// 타겟
						_hdc
						, (int)pos.x 
						, (int)pos.y
						, application.GetWidth() * mScale.x
						, application.GetHeight() * mScale.y
						// 원본
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth()
						, mTexture->GetHeight()
						// 생략 컬러
						, RGB(255, 0, 255));
				}
			}
			// 배경객체가 아니면
			else
			{
				if (mAlpha < 1.0f)	// 투명화 여부
				{
					BLENDFUNCTION func = {};
					int alpha = (int)(mAlpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255

					func.BlendOp = AC_SRC_OVER;
					func.BlendFlags = 0;
					func.AlphaFormat = AC_SRC_ALPHA;
					if (alpha <= 0)
						alpha = 0;
					func.SourceConstantAlpha = alpha;

					AlphaBlend(
						// 타겟
						_hdc
						, (int)pos.x /*- (mTexture->GetWidth() * mScale.x / 2.0f)*/
						, (int)pos.y /*- (mTexture->GetHeight() * mScale.y / 2.0f)*/
						, mTexture->GetWidth() * mScale.x
						, mTexture->GetHeight() * mScale.y
						// 원본
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth()
						, mTexture->GetHeight()
						// 설정
						, func);
				}
				else
				{
					TransparentBlt(
						// 타겟
						_hdc
						, (int)pos.x
						, (int)pos.y
						, mTexture->GetWidth() * mScale.x
						, mTexture->GetHeight() * mScale.y
						// 원본
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth()
						, mTexture->GetHeight()
						// 생략 컬러
						, RGB(255, 0, 255));
				}
			}
		}
		// 그려줄 이미지의 확장자가 *.png 일때
		else if (mTexture->GetType() == eTextureType::Png)	
		{
			Gdiplus::Graphics graphics(_hdc);
			if (GetOwner()->GetMyType() == enums::eGameObjectType::BackGround)
			{
				graphics.DrawImage(
					mTexture->GetImage()
					, (int)pos.x
					, (int)pos.y
					, HD_X
					, HD_Y);
			}
			else
			{
				graphics.DrawImage(
					mTexture->GetImage()
					, (int)pos.x
					, (int)pos.y
					, (int)(mTexture->GetWidth() * mScale.x)
					, (int)(mTexture->GetHeight() * mScale.y));
			}
		}
		// 그려줄 이미지의 확장자가 *.bmp , *.png 가 아닐때
		else
			__noop;
		
	}
}