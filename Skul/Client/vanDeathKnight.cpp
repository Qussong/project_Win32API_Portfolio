#include "vanDeathKnight.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	DeathKnight::DeathKnight()
	{
		// nothing
	}

	DeathKnight::~DeathKnight()
	{
		// nothing
	}

	void DeathKnight::Init()
	{
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"DeathKnight_Idle_Castle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(414.0f, 286.0f));
	}

	void DeathKnight::Update()
	{
		NPC::Update();
	}

	void DeathKnight::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void DeathKnight::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"DeathKnight_Idle_Castle", ResourceManager::Find<Texture>(L"DeathKnight_Idle_Castle"), math::Vector2(0.0f, 0.0f), math::Vector2(207.0f, 143.0f), 8);
	}
}