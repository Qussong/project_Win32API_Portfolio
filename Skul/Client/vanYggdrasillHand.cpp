#include "vanYggdrasillHand.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	YggdrasillHand::YggdrasillHand()
	{
		// nothing
	}

	YggdrasillHand::~YggdrasillHand()
	{
		// nothing
	}

	void YggdrasillHand::Init()
	{
		GameObject::Init();

		MakeAnimation();

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(166.0f * 2, 147.0f * 2));

	}

	void YggdrasillHand::Update()
	{
		GameObject::Update();
	}

	void YggdrasillHand::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);

		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));

		// 초기 영상재생
		if (mbInitPlayAnimation == false)
		{
			if (mHandPos == HandPos::Left)
			{
				at->PlayAnimation(L"Hand_Idle_L", true);
			}
			else if (mHandPos == HandPos::Right)
			{
				at->PlayAnimation(L"Hand_Idle_R", true);
			}
			mbInitPlayAnimation = true;
		}
	}

	void YggdrasillHand::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		
		at->CreateAnimation(L"Hand_Idle_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(166.0f, 147.0f), 7, math::Vector2::Zero, 0.2f);
		at->CreateAnimation(L"Hand_Idle_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(166.0f, 147.0f), 7, math::Vector2::Zero, 0.2f);
	}
	void YggdrasillHand::OnCollisionEnter(Collider* _other)
	{
	}
	void YggdrasillHand::OnCollisionStay(Collider* _other)
	{
	}
	void YggdrasillHand::OnCollisionExit(Collider* _other)
	{
	}
}