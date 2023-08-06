#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"

#include "vanCollisionManager.h"

namespace van
{
	Monster::Monster()
		: mTarget(nullptr)
		, mState(MonsterState::None)
		, mDirection(MonsterDirection::None)
		, mHitDirection(MonsterDirection::None)
		, mPastState(MonsterState::None)
		, mbPlayAnimation(true)
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
