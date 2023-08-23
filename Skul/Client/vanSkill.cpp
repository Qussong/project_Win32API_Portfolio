#include "vanSkill.h"

namespace van
{
	Skill::Skill()
	{
		// nothing
	}

	Skill::~Skill()
	{
		// nothing
	}

	void Skill::Init()
	{
		GameObject::Init();
	}

	void Skill::Update()
	{
		GameObject::Update();
	}

	void Skill::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Skill::MakeAnimation()
	{
		// nothing
	}

	void Skill::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Skill::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Skill::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}