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
		, mDeathTime(1.0f)
	{
		// nothing
	}

	Monster::~Monster()
	{
		// nothing
		Destroy(mTraceBox);
		Destroy(mAttackBox);
	}

	void Monster::Init()
	{
		//CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		mTraceBox = Object::Instantiate<MonsterTrace>(enums::eLayerType::Range_Monster_Trace);
		mAttackBox = Object::Instantiate<MonsterAttack>(enums::eLayerType::Range_Monster_Attack);
	}

	void Monster::Update()
	{
		GameObject::Update();

		// [ 투사체 구현부 ]
		// Transform* tr = GetComponent<Transform>();
		// math::Vector2 pos = tr->GetPosition();
		// pos.x += 300.0f * Time::DeltaTime();
		// tr->SetPosition(pos);
		   
		// mDeathTime -= Time::DeltaTime();
		// if (mDeathTime < 0.0f)
		// {
		// 	Destroy(this);
		// }
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
