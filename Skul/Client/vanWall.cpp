#include "vanWall.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanObject.h"
#include "vanMonster.h"

namespace van
{
	Wall::Wall()
	{
		// nothing
	}

	Wall::~Wall()
	{
		// nothing
	}

	void Wall::Init()
	{
		// nothing
	}

	void Wall::Update()
	{
		GameObject::Update();
	}

	void Wall::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Wall::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		RigidBody* rb = obj->GetComponent<RigidBody>();
		Collider* col = obj->GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// 충돌체의 위치
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// 바닥 객체의 위치
		math::Vector2 objSize = col->GetSize();										// 충돌체의 사이즈
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// 바닥 객체의 크기

		float gap = floorPos.x - objPos.x;							// 현재 프레임에서 충돌체와 Floor 객체가 떨어져있는 거리 (+ : 물체가 왼쪽, - : 물체가 오른쪽)
		float mazino = fabs(objSize.x / 2.0f + floorSize.x / 2.0f);	// 두 물체가 떨어져있기 위한 최소거리

		// 충돌체가 Floor 객체보다 위에 있을 때(중심좌표 기준)
		// 두 물체가 겹쳐있는 경우
		if (fabs(gap) < mazino)
		{
			// 왼쪽일 때(+)
			if (gap > 0)
			{
				objPos.x -= ((mazino - fabs(gap)) - 1.0f);
				tr->SetPosition(objPos);
			}
			// 오른쪽일 때(-)
			else
			{
				objPos.x += ((mazino - fabs(gap)) + 1.0f);
				tr->SetPosition(objPos);
			}
		}
	}

	void Wall::OnCollisionStay(Collider* _other)
	{
		OnCollisionEnter(_other);
	}

	void Wall::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}