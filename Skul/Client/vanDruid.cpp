#include "vanDruid.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Druid::Druid()
	{
		// nothing
	}

	Druid::~Druid()
	{
		// nothing
	}

	void Druid::Init()
	{
		MakeAnimation();
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Druid_Idle_Castle", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		GetComponent<Collider>()->SetSize(math::Vector2(442.0f, 304.0f));
	}

	void Druid::Update()
	{
		NPC::Update();
	}

	void Druid::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void Druid::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Druid_Idle_Castle", ResourceManager::Find<Texture>(L"Druid_Idle_Castle"), math::Vector2(0.0f, 0.0f), math::Vector2(221.0f, 152.0f), 8);
	}
}