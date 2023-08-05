#include "vanRange.h"

namespace van
{
	Range::Range()
		: mOwner(nullptr)
		, mOwnerPos(math::Vector2::Zero)
		, mOwnerState(0)
		, mOwnerDirection(0)
		, mOffset(math::Vector2::Zero)
	{
		// nothing
	}

	Range::~Range()
	{
		// nothing
	}

	void Range::Init()
	{

	}

	void Range::Update()
	{
		GameObject::Update();
	}

	void Range::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Range::MakeAnimation()
	{

	}

	void Range::OnCollisionEnter(Collider* _other)
	{

	}

	void Range::OnCollisionStay(Collider* _other)
	{

	}

	void Range::OnCollisionExit(Collider* _other)
	{

	}
}