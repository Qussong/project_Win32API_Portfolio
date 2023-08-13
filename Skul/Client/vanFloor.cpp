#include "vanFloor.h"
#include "vanPlayer.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanNPC.h"
#include "vanMonster.h"
#include "vanObject.h"

namespace van
{
	Floor::Floor()
	{
		// nothing
	}

	Floor::~Floor()
	{
		// nothing
	}

	void Floor::Init()
	{
		// nothing
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Floor::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		RigidBody* rb = obj->GetComponent<RigidBody>();
		Collider* col = obj->GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// 충돌체의 위치
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// 바닥 객체의 위치
		math::Vector2 objSize = col->GetSize();										// 충돌체의 사이즈
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// 바닥 객체의 크기

		float gap = floorPos.y - objPos.y;							// 현재 프레임에서 충돌체와 Floor 객체가 떨어져있는 거리 ( + : Player가 위 , - : Floor가 위)
		float mazino = fabs(objSize.y / 2.0f + floorSize.y / 2.0f);	// 두 물체가 떨어져있기 위한 최소거리

		// 충돌체가 Floor 객체보다 위에 있을 때(중심좌표 기준)
		if (gap > 0)
		{
			// 두 물체가 겹쳐있는 경우
			if (fabs(gap) < mazino)
			{
				objPos.y -= (mazino - fabs(gap)) - 1.0f;
				tr->SetPosition(objPos);
			}

			rb->SetGround(true);	// Floor 객체와 충돌한 객체가 땅에 붙어있는 상태로 만들어준다.
		}
	}

	void Floor::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Floor::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		RigidBody* rb = obj->GetComponent<RigidBody>();

		rb->SetGround(false);
	}
}