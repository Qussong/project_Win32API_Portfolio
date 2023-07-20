#include "vanCollider.h"
#include "vanTransform.h"
#include "vanObject.h"
#include "vanCamera.h"

namespace van
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		: Component(enums::eComponentType::Collider)
		, mSize(math::Vector2::Zero)
		, mOffset(math::Vector2::Zero)
		, mPos(math::Vector2::Zero)
		, mCollisionNum(-1)
		, mbIsCollision(false)
	{
		mCollisionNum = mCollisionCount;
		++mCollisionCount;
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
		mPos = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		pos = Camera::CalculatePosition(pos);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// 투명브러쉬
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN newPen = NULL;
		if (mbIsCollision)
		{
			newPen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
		}
		else
		{
			newPen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);

		SelectObject(hdc, oldBrush);	// 원복
		DeleteObject(transparentBrush);	// 메모리 해제

		SelectObject(hdc, oldPen);		// 원복
		DeleteObject(newPen);			// 메모리 해제
	}

	void Collider::OnCollisionEnter(Collider* _other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(_other);
	}

	void Collider::OnCollisionStay(Collider* _other)
	{
		GetOwner()->OnCollisionStay(_other);
	}

	void Collider::OnCollisionExit(Collider* _other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(_other);
	}
}