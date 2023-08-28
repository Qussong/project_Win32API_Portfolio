#include "vanUI.h"

namespace van
{
	UI::UI()
	{
		// nothing
	}

	UI::~UI()
	{
		// nothing
	}

	void UI::Init()
	{
		GameObject::Init();
		MakeAnimation();
	}

	void UI::Update()
	{
		GameObject::Update();

	}

	void UI::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void UI::MakeAnimation()
	{
	}

	void UI::OnCollisionEnter(Collider* _other)
	{
	}

	void UI::OnCollisionStay(Collider* _other)
	{
	}

	void UI::OnCollisionExit(Collider* _other)
	{
	}
}