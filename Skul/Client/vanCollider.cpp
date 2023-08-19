#include "vanCollider.h"
#include "vanTransform.h"
#include "vanObject.h"
#include "vanCamera.h"

namespace van
{
	UINT Collider::mCollisionCount = 0;

	// 생성자
	Collider::Collider()	
		: Component(enums::eComponentType::Collider)
		, mSize(math::Vector2::Zero)			// 충돌체 기본크기 0
		, mOffset(math::Vector2::Zero)			// 객체의 중점으로부터 충돌체의 위치수정값
		, mPos(math::Vector2::Zero)				// 충돌체의 중심좌표 : (0,0)
		, mCollisionNum(-1)						// 이름 기본값 : -1
		, mbIsCollision(false)					// 충돌여부 기본값 : 비충돌상태
		, lineColor(RGB(50, 255, 50))			// 형광 초록색
		, collisionLineColor(RGB(255, 50, 50))	// 붉은색
		, inActiveLineColor(RGB(128, 128, 128))	// 회색
		, mbActive(true)
		, mbAffectedCamera(true)
	{
		// 충돌체 Numbering : 0 ~ ...
		mCollisionNum = mCollisionCount;	// 충돌체가 생성되면 몇번째 충돌체인지 이름을 받고
		++mCollisionCount;					// 전체 충돌체의 개수를 하나 올려준다.
	}

	// 소멸자
	Collider::~Collider()
	{
		// nothing
	}

	// 초기화
	void Collider::Init()
	{
		// nothing
	}
	
	// 값 변경
	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();	
		mPos = pos + mOffset;
	}

	// 출력
	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();	
		
		pos.x -= mSize.x / 2.0f;	// 그려질 도형(사각형)의 너비값 중심이 pos.x
		pos.y -= mSize.y / 2.0f;	// 그려질 도형(사각형)의 높이값 중심이 pos.y
		pos.x += mOffset.x;			// 그려질 도형(사각형)의 너비 위치 조정 값
		pos.y += mOffset.y;			// 그려질 도형(사각형)의 높이 위치 조정 값

		// 카메라 영향여부에 따른 위치값 변화
		if (mbAffectedCamera == true)
		{
			// 카메라 영향 받음
			pos = Camera::CalculatePosition(pos);
		}

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// 투명브러쉬 핸들 값을 얻어온다.
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);	// Brush 교체
		HPEN newPen = NULL;

		// 충돌여부에 따른 색 변화
		if (mbActive == true)
		{
			if (mbIsCollision == true)	// 충돌
			{
				newPen = CreatePen(PS_SOLID, 2, collisionLineColor);
			}
			else // 비충돌 or 충돌탈출
			{
				newPen = CreatePen(PS_SOLID, 2, lineColor);
			}
		}
		else
		{
			newPen = CreatePen(PS_SOLID, 2, inActiveLineColor);
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, newPen);	// 충돌여부에 따른 색상을 가지고 있는 PEN으로 변경

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);	// 사각형 그리기

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