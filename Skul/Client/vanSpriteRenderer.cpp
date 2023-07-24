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
			, mAffectCamera
			, math::Vector2::Zero	// offset
			, mScale				// scale
			, mAlpha);				// alpha
	}
}