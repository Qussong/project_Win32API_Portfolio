#include "vanWitch.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Witch::Witch()
	{
		// nothing
	}

	Witch::~Witch()
	{
		// nothing
	}

	void Witch::Init()
	{
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Witch_Idle_Castle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(392.0f, 240.0f));
	}

	void Witch::Update()
	{
		NPC::Update();
	}

	void Witch::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void Witch::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Witch_Idle_Castle", ResourceManager::Find<Texture>(L"Witch_Idle_Castle"), math::Vector2(0.0f, 0.0f), math::Vector2(196.0f, 120.0f), 6);
	}
}