#include "vanMonster.h"
#include "vanInput.h"
#include "vanTransform.h"
#include "vanAnimator.h"

van::Monster::Monster()
{
	animator = AddComponent<Animator>();
}

van::Monster::~Monster()
{
	// nothing
}

void van::Monster::Init()
{
	// nothing
}

void van::Monster::Update()
{
	GameObject::Update();
}

void van::Monster::Render(HDC _hdc)
{
	GameObject::Render(_hdc);
}
