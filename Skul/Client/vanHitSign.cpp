#include "vanHitSign.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	HitSign::HitSign()
	{
		// nothing
	}

	HitSign::~HitSign()
	{
		// nothing
	}

	void HitSign::Init()
	{
		UI::Init();
	}

	void HitSign::Update()
	{
		UI::Update();
	}

	void HitSign::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void HitSign::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"UI_Player_HitSign", ResourceManager::Find<Texture>(L"UI_Player_HitSign"), math::Vector2(0.0f, 0.0f), math::Vector2(640.0f, 360.0f), 12, math::Vector2(0.0f, 0.0f), 0.04F);
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(false);
	}

	void HitSign::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void HitSign::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void HitSign::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}