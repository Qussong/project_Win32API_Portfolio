#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanGameObject.h"

namespace van
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::Transform)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{

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
	}
}