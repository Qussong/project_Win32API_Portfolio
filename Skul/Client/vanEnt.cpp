#include "vanEnt.h"
#include "vanRigidBody.h"
#include "vanCollider.h"
#include "vanAnimator.h"
#include "vanMonsterTrace.h"
#include "vanMonsterAttack.h"
#include "vanTransform.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanGold.h"
#include "vanObject.h"

namespace van
{
	Ent::Ent()
	{
		// nothing
	}

	Ent::~Ent()
	{
		// nothing
	}

	void Ent::Init()
	{
		Monster::Init();

		MakeAnimation();	// 애니메이션 생성

		// Monster 초기설정
		SetMonsterState(MonsterState::Gen);									// 상태
		GetComponent<Collider>()->SetSize(math::Vector2(80.0f, 120.0f));	
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// 이미지 스케일 설정

		// traceBox의 초기값 설정
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwner(this);
		traceBox->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 120.0f));
		traceBox->SetOffset(math::Vector2::Zero);

		// attackBox의 초기값 설정
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 120.0f));	// 사정거리 20
		attackBox->SetOffset(math::Vector2(10.0f, 0.0f));							
	}

	void Ent::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// traceBox 값세팅
		MonsterTrace* traceBox = GetMonsterTraceBox();
		traceBox->SetOwnerPos(pos);
		traceBox->SetOwnerState((UINT)GetMonsterState());
		traceBox->SetOwnerDirection((UINT)GetMonsterDirection());
		// attackBox 값세팅
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		Monster::Update();
	}

	void Ent::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void Ent::MakeAnimation()
	{
		Monster::MakeAnimation();

		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimation(L"Attack_L", ResourceManager::Find<Texture>(L"Ent_Attack_L"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 72.0f), 4, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_R", ResourceManager::Find<Texture>(L"Ent_Attack_R"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 72.0f), 4, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_Ready_L", ResourceManager::Find<Texture>(L"Ent_Attack_Ready_L"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 72.0f), 1, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Attack_Ready_R", ResourceManager::Find<Texture>(L"Ent_Attack_Ready_R"), math::Vector2(0.0f, 0.0f), math::Vector2(59.0f, 72.0f), 1, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Dead_L", ResourceManager::Find<Texture>(L"Ent_Dead_L"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 64.0f), 1);
		animator->CreateAnimation(L"Dead_R", ResourceManager::Find<Texture>(L"Ent_Dead_R"), math::Vector2(0.0f, 0.0f), math::Vector2(46.0f, 64.0f), 1);
		animator->CreateAnimation(L"Hit_L", ResourceManager::Find<Texture>(L"Ent_Hit_L"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 67.0f), 1);
		animator->CreateAnimation(L"Hit_R", ResourceManager::Find<Texture>(L"Ent_Hit_R"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 67.0f), 1);
		animator->CreateAnimation(L"Idle_L", ResourceManager::Find<Texture>(L"Ent_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 66.0f), 5);
		animator->CreateAnimation(L"Idle_R", ResourceManager::Find<Texture>(L"Ent_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(56.0f, 66.0f), 5);
		animator->CreateAnimation(L"Walk_L", ResourceManager::Find<Texture>(L"Ent_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(53.0f, 65.0f), 6, math::Vector2(0.0f, 0.0f));
		animator->CreateAnimation(L"Walk_R", ResourceManager::Find<Texture>(L"Ent_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(53.0f, 65.0f), 6, math::Vector2(0.0f, 0.0f));
	}

	void Ent::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Ent::OnCollisionStay(Collider* _other)
	{
		Monster::OnCollisionStay(_other);
	}

	void Ent::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Ent::Gen()
	{
		Monster::Gen();
	}

	void Ent::Idle()
	{
		Monster::Idle();
	}

	void Ent::Walk()
	{
		Monster::Walk();
	}

	void Ent::Patrol()
	{
		Monster::Patrol();
	}

	void Ent::Trace()
	{
		Monster::Trace();
	}

	void Ent::AttackReady()
	{
		Monster::AttackReady();
	}

	void Ent::Attack()
	{
		Monster::Attack();
	}

	void Ent::AttackEnd()
	{
		Monster::AttackEnd();
	}

	void Ent::Hit()
	{
		Monster::Hit();
	}

	void Ent::Dead()
	{
		Monster::Dead();
	}
}