#include "vanBoss.h"

namespace van
{
	Boss::Boss()
	{
		// nothing
	}

	Boss::~Boss()
	{
		// nothing
	}

	void Boss::Init()
	{
		GameObject::Init();
	}

	void Boss::Update()
	{
		GameObject::Update();
	}

	void Boss::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Boss::MakeAnimation()
	{
		// nothing
	}

	void Boss::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Boss::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Boss::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}