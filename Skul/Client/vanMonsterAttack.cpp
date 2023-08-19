#include "vanMonsterAttack.h"

#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanTransform.h"
#include "vanMonster.h"
#include "vanPlayer.h"

namespace van
{
	MonsterAttack::MonsterAttack()
		: mbAttackReadyFlag(false)
	{
		// nothing
	}

	MonsterAttack::~MonsterAttack()
	{
		// nothing
	}

	void MonsterAttack::Init()
	{
		// Collider 의 상자색 변경(MonsterAttack 범위 색 : Blue)
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));	
		// MonsterAttack 과 Player가 충돌판정을 받도록 설정
		//CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);
	}

	void MonsterAttack::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		// 위치 설정
		// MonsterTrace 클래스를 소유하고 있는 객체의 위치를 기반으로 따라다닌다.
		Monster::MonsterDirection direction = (Monster::MonsterDirection)GetOwnerDirection();
		// 몬스터가 바라보는 방향이 Left 일때
		if (direction == Monster::MonsterDirection::Left)
		{
			tr->SetPosition(GetOwnerPos() - GetOffset());
		}
		// 몬스터가 바라보는 방향이 Right 일때
		else
		{
			tr->SetPosition(GetOwnerPos() + GetOffset());
		}
	}

	void MonsterAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MonsterAttack::MakeAnimation()
	{
		// nothing
	}

	void MonsterAttack::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MonsterAttack::OnCollisionStay(Collider* _other)
	{
		Monster* monster = (Monster*)GetOwner();	// // MonsterAttack 클래스를 소유한 객체의 주소 저장
		GameObject* obj = _other->GetOwner();		// 충돌 대상의 주소저장
		Player* playr = dynamic_cast<Player*>(obj);	// 충돌 대상이 Player 인지 확인

		// Attack Ready 상태로 진입
		// 충돌한 객체가 Player이고 Attack Ready로 상태전환된적이 없다면 Attack Ready로 상태전환
		if (playr != nullptr
			&& mbAttackReadyFlag == false)
		{
			// Monster가 Attack을 수행하도록 mbAttack 을 true로 변경
			monster->SetAttackFlag(true);
		}
		
		// Attack 상태 진입
		// Attack 상태일때 타격판정이 생긴다.
		// 몬스터가 Attack 상태이고 Attack Ready를 이미 수행했을 경우
		if ((Monster::MonsterState)GetOwnerState() == Monster::MonsterState::Attack
			&& mbAttackReadyFlag == true)
		{
			// 만약 타격된 대상이 Set에 들어있지 않다면 타격판정 o
			if (mAttackList.find(obj) == mAttackList.end())
			{
				// 타격된 대상을 Set에 넣어준다.
				// 빼주는건 Monster에서 해준다.
				mAttackList.insert(obj);

				// 피격대상이 플레이어 일때
				Player* player = dynamic_cast<Player*>(obj);
				if (player != nullptr)
				{
					// hp 감소
					// 피격판정시 날아간다..
				}
				// 피격대상이 플레이어가 아닐때
				else
				{
					// 필요한 로직 구현
					// ex) Monster라면 hp 감소는 없지만 날아가긴 한다거나...
				}
			}
			else
			{
				// 이미 Set에 들어있다면 타격판정 x
				__noop;
			}
		}
	}

	void MonsterAttack::OnCollisionExit(Collider* _other)
	{
		Monster* monster = (Monster*)GetOwner();		// MonsterAttack 클래스를 소유한 객체의 주소 저장
		GameObject* obj = _other->GetOwner();			// 충돌 대상의 주소저장
		Player* playr = dynamic_cast<Player*>(obj);		// 충돌 대상이 Player 인지 확인

		// Player가 Monster Attack 범위에서 벗어나면 Attack Flag 를 꺼준다.
		if (playr != nullptr)
		{
			monster->SetAttackFlag(false);

			if (monster->GetMonsterState() != Monster::MonsterState::AttackReady
				&& monster->GetMonsterState() != Monster::MonsterState::Attack
				&& monster->GetMonsterState() != Monster::MonsterState::AttackEnd)
			{
				monster->SetMonsterState(Monster::MonsterState::Patrol);
			}
		}
	}
}