#include "vanTiedSkul.h"
#include "vanAnimator.h"
#include "vanRigidBody.h"
#include "vanCollider.h"

namespace van
{
	TiedSkul::TiedSkul()
	{
		AddComponent<RigidBody>();
		AddComponent<Collider>()->SetSize(math::Vector2(70.0f, 100.0f));;
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