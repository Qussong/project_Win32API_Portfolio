#include "vanAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"

namespace van
{
	Attack::Attack()
		: owner(nullptr)
		, ownerPos(math::Vector2::Zero)
		, offset(math::Vector2::Zero)
	{
		// nothing
	}

	Attack::~Attack()
	{
		// nothing
	}

	void Attack::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));	// Collider 의 상자 색을 파란색으로 변경
	}

	void Attack::Update()
	{
		GameObject::Update();

		Player* player = dynamic_cast<Player*>(owner);
		if (player != nullptr)
		{
			Player::PlayerDirection direction =  player->GetPlayerDirection();
			math::Vector2 size = owner->GetComponent<Collider>()->GetSize();

			if (direction == Player::PlayerDirection::Left)
			{
				offset = math::Vector2(-(size.x / 2 ), 0.0f);
			}
			if (direction == Player::PlayerDirection::Right)
			{
				offset = math::Vector2(size.x / 2, 0.0f);
			}

			Player::PlayerState state = player->GetPlayerState();
			if(state == Player::PlayerState::AttackA || state == Player::PlayerState::AttackB)
			{
				CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, true);
			}
			else
			{
				CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, false);
			}
		}

		ownerPos = owner->GetComponent<Transform>()->GetPosition();
		/*this->*/GetComponent<Transform>()->SetPosition(ownerPos + offset);


		
	}

	void Attack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Attack::MakeAnimation()
	{

	}

	void Attack::OnCollisionEnter(Collider* _other)
	{

	}

	void Attack::OnCollisionStay(Collider* _other)
	{

	}

	void Attack::OnCollisionExit(Collider* _other)
	{

	}
}