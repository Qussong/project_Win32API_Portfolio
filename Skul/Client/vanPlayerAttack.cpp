#include "vanPlayerAttack.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanCollider.h"

#include "vanCollisionManager.h"
#include "vanPlayer.h"

namespace van
{
	PlayerAttack::PlayerAttack()
		//: mOwner(nullptr)
		//, mOwnerPos(math::Vector2::Zero)
		//, mOwnerState((UINT)Player::PlayerState::None)
		//, mOwnerDirection((UINT)Player::PlayerDirection::None)
		//, mOffset(math::Vector2::Zero)
		: mbCombo(false)
	{
		// nothing
	}

	PlayerAttack::~PlayerAttack()
	{
		// nothing
	}

	void PlayerAttack::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));			// Collider 의 상자색 변경(Attack 범위 색 : Blue)
	}

	void PlayerAttack::Update()
	{
		GameObject::Update();

		Player* player = dynamic_cast<Player*>(GetOwner());

		// PlayerAttack 클래스의 소유자가 Player 인 경우
		if (player != nullptr)
		{
			Player::PlayerDirection direction =  player->GetPlayerDirection();		// Player의 방향을 읽어옴
			math::Vector2 size = GetOwner()->GetComponent<Collider>()->GetSize();	// Player의 Collider 상자 크기를 읽어옴

			if (direction == Player::PlayerDirection::Left)							// Player의 방향이 왼쪽일 때
			{
				SetOffset(math::Vector2(-(size.x / 2), 0.0f));
			}
			if (direction == Player::PlayerDirection::Right)						// Player의 방향이 오른쪽일 때
			{
				SetOffset(math::Vector2(size.x / 2, 0.0f));
			}

			SetOwnerState((UINT)(player->GetPlayerState()));						// Player의 상태를 읽어옴
			if(GetOwnerState() == (UINT)Player::PlayerState::AttackA
				|| GetOwnerState() == (UINT)Player::PlayerState::JumpAttack)		// Player가 공격상태일 때(AttackA,JumpAttack)
			{
				GetComponent<Collider>()->SetActive(true);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, true);
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));

				mbCombo = player->GetCombo();
			}
			else if (GetOwnerState() == (UINT)Player::PlayerState::AttackB)			// Player가 공격상태일 때(AttackB)
			{
				if (mbCombo)
				{
					attackList.clear();
					mbCombo = false;
				}
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, true);
				SetOwnerDirection((UINT)(player->GetPlayerDirection()));
			}
			else
			{
				GetComponent<Collider>()->SetActive(false);
				CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, false);

				attackList.clear();	// 공격판정이 끝나면 공격범위 충돌 내역을 비워준다.
			}
		}

		SetOwnerPos(GetOwner()->GetComponent<Transform>()->GetPosition());
		GetComponent<Transform>()->SetPosition(GetOwnerPos() + GetOffset());
	}

	void PlayerAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PlayerAttack::MakeAnimation()
	{
		// nothing
	}

	void PlayerAttack::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void PlayerAttack::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void PlayerAttack::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}