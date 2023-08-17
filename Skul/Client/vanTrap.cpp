#include "vanTrap.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"	
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanRigidBody.h"

namespace van
{
	Trap::Trap()
	{
		// nothing
	}

	Trap::~Trap()
	{
		// nothing
	}

	void Trap::Init()
	{
		GameObject::Init();

		MakeAnimation();	// 애니메이션 생성

		SetMonsterState(Monster::MonsterState::Idle);
		GetComponent<Animator>()->PlayAnimation(L"Stage1Trap_Idle", true);
		GetComponent<Collider>()->SetSize(math::Vector2(100, 40));
		GetComponent<RigidBody>()->SetGround(true);	//	벽에 부착되어있어야하기에 무조건 true
	}

	void Trap::Update()
	{
		GameObject::Update();

		switch (GetMonsterState())
		{
		case MonsterState::Idle:
			Idle();
			break;
		default:
			__noop;
		}
	}

	void Trap::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Trap::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Stage1Trap_Idle", ResourceManager::Find<Texture>(L"Stage1Trap"), math::Vector2(0.0f, 0.0f), math::Vector2(128.0f, 40.0f), 11);
	}

	void Trap::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Trap::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Trap::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Trap::Idle()
	{
		// nothing
	}
}