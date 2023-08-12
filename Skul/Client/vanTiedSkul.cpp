#include "vanTiedSkul.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

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
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"TiedSkul_Idle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(70.0f, 100.0f));
	}

	void TiedSkul::Update()
	{
		NPC::Update();
	}

	void TiedSkul::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void TiedSkul::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"TiedSkul_Idle", ResourceManager::Find<Texture>(L"TiedSkul_Idle"), math::Vector2(0.0f, 0.0f), math::Vector2(57.0f, 57.0f), 11);
	}
}