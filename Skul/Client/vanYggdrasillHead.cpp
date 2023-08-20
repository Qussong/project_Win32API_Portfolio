#include "vanYggdrasillHead.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	YggdrasillHead::YggdrasillHead()
	{
		// nothing
	}

	YggdrasillHead::~YggdrasillHead()
	{
		// nothing
	}

	void YggdrasillHead::Init()
	{
		GameObject::Init();

		MakeAnimation();

		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Head", true);

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(241.0f * 2, 168.0f * 2));
	}

	void YggdrasillHead::Update()
	{
		GameObject::Update();
	}

	void YggdrasillHead::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillHead::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Head", ResourceManager::Find<Texture>(L"Yggdrasill_Head"), math::Vector2(0.0f, 0.0f), math::Vector2(241.0f, 168.0f), 2, math::Vector2::Zero, 1.0F);

	}
	
	void YggdrasillHead::OnCollisionEnter(Collider* _other)
	{
		// 피격판정
	}

	void YggdrasillHead::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHead::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

}