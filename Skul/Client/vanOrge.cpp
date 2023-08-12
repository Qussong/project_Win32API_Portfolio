#include "vanOrge.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Orge::Orge()
	{
		// nothing
	}

	Orge::~Orge()
	{
		// nothing
	}

	void Orge::Init()
	{
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Orge_Idle_Castle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(454.0f, 302.0f));
	}

	void Orge::Update()
	{
		NPC::Update();
	}

	void Orge::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void Orge::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Orge_Idle_Castle", ResourceManager::Find<Texture>(L"Orge_Idle_Castle"), math::Vector2(0.0f, 0.0f), math::Vector2(227.0f, 151.0f), 8);
	}
}