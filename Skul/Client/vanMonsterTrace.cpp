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
		Monster* monster = (Monster*)GetOwner();	// MonsterTrace 클래스를 소유하고 있는 Monster 클래스의 주소저장
		
		//if (player != nullptr && !(monster->GetTraceFlag()))	// 충돌한 객체가 Player이고 아직 Trace상태가 아닐 때
		if (player != nullptr && monster->GetMonsterState() != Monster::MonsterState::Trace)
		{
			// 몬스터의 타겟 설정
			monster->SetMonsterTarget(player);
			// 몬스터의 상태를 Trace 로 변경
			monster->SetMonsterState(Monster::MonsterState::Trace);
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);
		Monster* monster = (Monster*)GetOwner();

		if (player != nullptr)	// 충돌에서 벗어난 객체가 Player 인 경우
		{
			// 몬스터의 상태를 Idle 로 변경
			monster->SetMonsterState(Monster::MonsterState::Idle);
		}
	}
}