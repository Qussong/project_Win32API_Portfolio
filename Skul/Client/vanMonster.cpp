#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"

namespace van
{
	Monster::Monster()
	{
		// nothing
	}

	Monster::~Monster()
	{
		// nothing
	}

	void Monster::Init()
	{
		// nothing
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
