#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanGameObject.h"

namespace van
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::Transform)
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
		/*Transform* tr = GetOwner()->GetComponent<Transform>();	

		math::Vector2 pos = tr->GetPosition();

		Ellipse(_hdc, pos.x, pos.y, pos.x + DIAMETER, pos.y + DIAMETER);*/
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		TransparentBlt(_hdc, (int)pos.x, (int)pos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		
	}
}