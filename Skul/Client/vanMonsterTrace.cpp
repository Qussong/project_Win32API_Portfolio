#include "vanMonsterTrace.h"

#include "vanCollider.h";
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanPlayer.h"

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
		GetComponent<Collider>()->SetLineColor(RGB(255, 255, 0));		// Collider 의 상자색 변경(Trace 범위 색 : Yellow)
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

		if (player != nullptr)
		{
			// trace 로직 구현
		}
	}

	void MonsterTrace::OnCollisionExit(Collider* _other)
	{
		
	}
}