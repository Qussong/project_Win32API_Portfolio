#include "vanCollider.h"
#include "vanTransform.h"
#include "vanObject.h"

namespace van
{
	Collider::Collider()
		: Component(enums::eComponentType::Collider)
		, mSize(math::Vector2::Zero)
		, mOffset(math::Vector2::Zero)
	{
		// nothing
	}

	Collider::~Collider()
	{
		// nothing
	}

	void Collider::Init()
	{
		// nothing
	}

	void Collider::Update()
	{
		// nothing
	}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// 투명브러쉬
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);

		SelectObject(hdc, oldBrush);	// 원복
		DeleteObject(transparentBrush);	// 메모리 해제

		SelectObject(hdc, oldPen);		// 원복
		DeleteObject(greenPen);			// 메모리 해제
	}
}