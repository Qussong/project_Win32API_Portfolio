#include "vanFloor.h"
#include "vanPlayer.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"

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
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		Transform* tr = player->GetComponent<Transform>();
		RigidBody* rb = player->GetComponent<RigidBody>();

		float len = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);
		float scale = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);


		if (len < scale)
		{
			math::Vector2 playerPos = tr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;
			tr->SetPosition(playerPos);
		}

		rb->SetGround(true);
	}

	void Floor::OnCollisionStay(Collider* _other)
	{

	}

	void Floor::OnCollisionExit(Collider* _other)
	{

	}
}