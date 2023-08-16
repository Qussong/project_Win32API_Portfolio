#include "vanStage1Trap.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"	
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	Stage1Trap::Stage1Trap()
	{
		// nothing
	}

	Stage1Trap::~Stage1Trap()
	{
		// nothing
	}

	void Stage1Trap::Init()
	{
		Monster::Init();

		MakeAnimation();	// 局聪皋捞记 积己

		SetMonsterState(Monster::MonsterState::Idle);
		GetComponent<Animator>()->PlayAnimation(L"Stage1Trap_Idle", true);
		GetComponent<Collider>()->SetSize(math::Vector2(100, 40));
	}

	void Stage1Trap::Update()
	{
		Monster::Update();

		switch (GetMonsterState())
		{
		case Stage1Trap::MonsterState::Idle:
			Idle();
			break;
		default:
			__noop;
		}
	}

	void Stage1Trap::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void Stage1Trap::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Stage1Trap_Idle", ResourceManager::Find<Texture>(L"Stage1Trap"), math::Vector2(0.0f, 0.0f), math::Vector2(128.0f, 40.0f), 11);
	}

	void Stage1Trap::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Stage1Trap::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Stage1Trap::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Stage1Trap::Idle()
	{
		// nothing
	}
}