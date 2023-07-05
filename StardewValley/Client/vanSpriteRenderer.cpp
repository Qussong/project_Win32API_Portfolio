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
		Transform* tr = GetOwner()->GetComponent<Transform>();	// Question) 헤더파일 없으면 왜 오류나는가?
																// -> Component.h 에서도 vanGameObject 에 대한 #include가 없기 때문인가?
		math::Vector2 pos = tr->GetPosition();

		Ellipse(_hdc, pos.x, pos.y, pos.x + DIAMETER, pos.y + DIAMETER);
	}
}