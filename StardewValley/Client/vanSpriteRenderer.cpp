#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanGameObject.h"

namespace van
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::Transform)
		, mScale(math::Vector2::One)
		, mTexture(nullptr)
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
		if (mTexture == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		if (mTexture->GetType() == eTextureType::Bmp)
		{
			if (GetOwner()->GetMyType() == enums::eGameObjectType::BackGround)
			{
				TransparentBlt(_hdc
					, (int)pos.x, (int)pos.y
					, /*mTexture->GetWidth() * mScale.x*/HD_X
					, /*mTexture->GetHeight() * mScale.y*/HD_Y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, RGB(255, 0, 255));
			}
			else
			{
				TransparentBlt(_hdc
					, (int)pos.x, (int)pos.y
					, mTexture->GetWidth() * mScale.x
					, mTexture->GetHeight() * mScale.y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(_hdc);
			if (GetOwner()->GetMyType() == enums::eGameObjectType::BackGround)
			{
				graphics.DrawImage(mTexture->GetImage()
					, (int)pos.x, (int)pos.y
					, HD_X, HD_Y);
			}
			else
			{
				graphics.DrawImage(mTexture->GetImage()
					, (int)pos.x, (int)pos.y
					, (int)(mTexture->GetWidth() * mScale.x)
					, (int)(mTexture->GetHeight() * mScale.y));
			}
		}
		else
			__noop;
		
	}
}