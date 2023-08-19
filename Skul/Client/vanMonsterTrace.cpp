#include "vanMonsterTrace.h"
#include "vanCollider.h"
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
		//CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
	}

	void MonsterTrace::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		// 위치 설정
		tr->SetPosition(GetOwnerPos());	
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
		Monster* monster = (Monster*)GetOwner();	// MonsterTrace 클래스를 소유하고 있는 Monster 클래스의 주소저장
		
		// Monster의 상태가 AttackReady, Attack 이 아닌경우
		if (monster->GetMonsterState() != Monster::MonsterState::AttackReady
			|| monster->GetMonsterState() != Monster::MonsterState::Attack)
		{
			// 충돌한 대상이 Player이고 Monster에게 Target이 없을 때
			if (player != nullptr && monster->GetMonsterTarget() == nullptr)	
			{
				// // Monster가 Trace을 수행하도록 mbTrace 을 true로 변경
				monster->SetTraceFlag(true);
				// 몬스터의 타겟 설정
				monster->SetMonsterTarget(player);
			}
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = (Monster*)GetOwner();

		// 충돌에서 벗어난 객체가 Player 인 경우
		if (player != nullptr
			&& monster->GetMonsterState() != Monster::MonsterState::AttackReady
			&& monster->GetMonsterState() != Monster::MonsterState::Attack
			&& monster->GetMonsterState() != Monster::MonsterState::AttackEnd)
		{
			monster->SetTraceFlag(false);
			// 몬스터의 타겟을 없앤다.
			monster->SetMonsterTarget(nullptr);
			// 몬스터의 상태를 Patrol 로 변경
			monster->SetMonsterState(Monster::MonsterState::Patrol);
		}
	}

}