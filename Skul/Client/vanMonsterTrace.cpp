#include "vanMonsterTrace.h"

#include "vanCollider.h";
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanPlayer.h"

#include "vanCollisionManager.h"
#include "vanMonster.h"

namespace van
{
	MonsterTrace::MonsterTrace()
	{
		// nothing
	}

	MonsterTrace::~MonsterTrace()
	{
		// nothing
	}

	void MonsterTrace::Init()
	{
		GetComponent<Collider>()->SetLineColor(RGB(255, 255, 0));	// Collider 의 상자색 변경(Trace 범위 색 : Yellow)
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Trace, eLayerType::Player, true);
	}

	void MonsterTrace::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		// 위치 설정
		tr->SetPosition(GetOwnerPos());	// 소유자의 위치를 따라다닌다.
	}

	void MonsterTrace::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MonsterTrace::MakeAnimation()
	{
		// nothing
	}

	void MonsterTrace::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MonsterTrace::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		
		if (player != nullptr)	// 충돌한 객체가 Player 인 경우
		{
			// 몬스터의 상태를 Trace 로 변경
			Monster* monster = (Monster*)GetOwner();
			monster->SetMonsterState(Monster::MonsterState::Trace);

			// 위치를 비교하여 Monster 기준으로 왼쪽인지 오른쪽인지 구분
			math::Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();
			math::Vector2 monsterPos = monster->GetComponent<Transform>()->GetPosition();
			if (playerPos.x < monsterPos.x)
			{
				// Player가 Monster의 Left에 있다.
				// Monster의 이동 방향을 Left로 변경
				monster->SetMonsterDirection(Monster::MonsterDirection::Left);
			}
			else
			{
				// Player가 Monster의 Right에 있다.
				// Monster의 이동 방향을 Right로 변경
				monster->SetMonsterDirection(Monster::MonsterDirection::Right);
			}
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)	// 충돌에서 벗어난 객체가 Player 인 경우
		{
			// 몬스터의 상태를 Idle 로 변경
			Monster* monster = (Monster*)GetOwner();
			monster->SetMonsterState(Monster::MonsterState::Idle);
		}
	}
}