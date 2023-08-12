#include "vanFoxHunter.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	FoxHunter::FoxHunter()
	{
		// nothing
	}

	FoxHunter::~FoxHunter()
	{
		// nothing
	}

	void FoxHunter::Init()
	{
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"FoxHunter_Idle_Castle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(434.0f, 288.0f));
	}

	void FoxHunter::Update()
	{
		NPC::Update();
	}

	void FoxHunter::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void FoxHunter::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"FoxHunter_Idle_Castle", ResourceManager::Find<Texture>(L"FoxHunter_Idle_Castle"), math::Vector2(0.0f, 0.0f), math::Vector2(217.0f, 144.0f), 8);
	}
}