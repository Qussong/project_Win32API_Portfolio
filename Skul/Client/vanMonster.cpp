#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"

#include "vanObject.h"
#include "vanMonsterTrace.h"
#include "vanMonsterAttack.h"

namespace van
{
	Monster::Monster()
		: mTarget(nullptr)
		, mState(MonsterState::None)
		, mPastState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mPastDirection(MonsterDirection::None)
		, mHitDirection(MonsterDirection::None)
		, mTimer(0.0f)
		, mbPatrol(false)
		, mbTrace(false)
		, mbAttack(false)
		, mbPlayAnimation(true)
		, mTraceBox(nullptr)
		, mAttackBox(nullptr)
	{
		// nothing
	}

	Monster::~Monster()
	{
		// nothing
	}

	void Monster::Init()
	{
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);

		//
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Monster::MakeAnimation()
	{
		// nothing
	}

	void Monster::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Monster::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Monster::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}
