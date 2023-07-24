#include "vanTiedSkul.h"
#include "vanAnimator.h"

namespace van
{
	TiedSkul::TiedSkul()
	{
		// nothing
	}

	TiedSkul::~TiedSkul()
	{
		// nothing
	}

	void TiedSkul::Init()
	{
		// nothing
	}

	void TiedSkul::Update()
	{
		GameObject::Update();
	}

	void TiedSkul::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void TiedSkul::MakeAnimation()
	{
		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimationFolder(L"Tied_Skul_NPC"
			, L"..\\MyResources\\skul\\1_NPC\\Tied_Skul");
	}
}