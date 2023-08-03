#include "vanAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

namespace van
{
	Attack::Attack()
		: mOwner(nullptr)
		, mOwnerPos(math::Vector2::Zero)
		, mOwnerState((UINT)Player::PlayerState::None)
		, mOffset(math::Vector2::Zero)
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

		Player* player = dynamic_cast<Player*>(mOwner);

		if (player != nullptr)
		{
			Player::PlayerDirection direction =  player->GetPlayerDirection();	// Player의 방향을 읽어옴
			math::Vector2 size = mOwner->GetComponent<Collider>()->GetSize();	// Player의 Collider 상자 크기를 읽어옴

			if (direction == Player::PlayerDirection::Left)						// Player의 방향이 왼쪽일 때
			{
				mOffset = math::Vector2(-(size.x / 2 ), 0.0f);
			}
			if (direction == Player::PlayerDirection::Right)			// Player의 방향이 오른쪽일 때
			{
				mOffset = math::Vector2(size.x / 2, 0.0f);
			}

			mOwnerState = (UINT)(player->GetPlayerState());				// Player의 상태를 읽어옴
			if(mOwnerState == (UINT)Player::PlayerState::AttackA
				|| mOwnerState == (UINT)Player::PlayerState::AttackB)	// Player가 공격상태일 때
			{
				GetComponent<Collider>()->SetActive(true);
				CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, true);
			}
			else
			{
				GetComponent<Collider>()->SetActive(false);
				CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Monster, false);
			}
		}

		mOwnerPos = mOwner->GetComponent<Transform>()->GetPosition();
		/*this->*/GetComponent<Transform>()->SetPosition(mOwnerPos + mOffset);
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