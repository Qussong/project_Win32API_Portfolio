#include "vanWall.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"
#include "vanObject.h"
#include "vanMonster.h"
#include "vanPlayer.h"
#include "vanCollider.h"

namespace van
{
	Wall::Wall()
		: mbFloorLimit(false)
	{
		// nothing
	}

	Wall::~Wall()
	{
		// nothing
	}

	void Wall::Init()
	{
		if (mbFloorLimit == false)
		{
			GetComponent<Collider>()->SetLineColor(RGB(255, 128, 0));
		}
	}

	void Wall::Update()
	{
		GameObject::Update();

		if (mbFloorLimit == true)
		{
			GetComponent<Collider>()->SetLineColor(RGB(0, 255, 255));
		}
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
		Collider* col_this = GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// 충돌체의 위치
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// 바닥 객체의 위치
		math::Vector2 objSize = col->GetSize();										// 충돌체의 사이즈
		math::Vector2 thisSize = col_this->GetSize();								// Wall객체의 사이즈
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// 바닥 객체의 크기

		// x축
		float gapX = floorPos.x - objPos.x;							// 현재 프레임에서 충돌체와 Floor 객체가 떨어져있는 거리 (+ : 물체가 왼쪽, - : 물체가 오른쪽)
		float mazinoX =objSize.x / 2.0f + floorSize.x / 2.0f;		// 두 물가 떨어져있기 위한 최소거리
		// y축
		float gapY = floorPos.y - objPos.y;							// 현재 프레임에서 충돌체와 Floor 객체가 떨어져있는 거리 (+ : 물체가 왼쪽, - : 물체가 오른쪽)
		float mazinoY = objSize.y / 2.0f + floorSize.y / 2.0f;		// 두 물가 떨어져있기 위한 최소거리

		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = dynamic_cast<Monster*>(obj);

		// 플레이어와 충돌했을 경우
		if (player != nullptr
			&& mbFloorLimit == false)
		{
			// Wall 객체의 y축 길이가 더 긴 경우 (일반적인 경우)
			if (thisSize.x < thisSize.y)
			{
				if (fabs(gapX) < mazinoX)
				{
					// 왼쪽일 때(+)
					if (gapX > 0)
					{
						objPos.x -= ((mazinoX - fabs(gapX)) - 1.0f);
						tr->SetPosition(objPos);
					}

					// 오른쪽일 때(-)
					if(gapX < 0)
					{
						objPos.x += ((mazinoX - fabs(gapX)) + 1.0f);
						tr->SetPosition(objPos);
					}
				}
			}
			// Wall 객체의 x축 길이가 더 긴 경우
			else if(thisSize.x > thisSize.y)
			{
				if (fabs(gapY) < mazinoY)
				{
					// Wall 이 아래에 있을 때(+)
					if (gapY > 0)
					{
						objPos.y -= ((mazinoY - fabs(gapY)) - 1.0f);
						tr->SetPosition(objPos);
					}

					// Wall 이 위에 있을 때(-)
					if (gapY < 0)
					{
						objPos.y += ((mazinoY - fabs(gapY)) + 1.0f);
						tr->SetPosition(objPos);
					}
				}
			}
		}

		// 몬스터와 충돌했을 경우
		if (monster != nullptr)
		{
			monster->SetWallFlag(true);
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