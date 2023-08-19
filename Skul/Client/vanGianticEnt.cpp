#include "vanGianticEnt.h"
#include "vanCollider.h"
#include "vanRigidBody.h"
#include "vanAnimator.h"
#include "vanMonsterAttack.h"
#include "vanTransform.h"

namespace van
{
	GianticEnt::GianticEnt()
	{
		// nothing
	}

	GianticEnt::~GianticEnt()
	{
		// nothing
	}

	void GianticEnt::Init()
	{
		Monster::Init();

		// 애니메이션 생성
		MakeAnimation();

		// Monster 초기설정
		SetMonsterState(MonsterState::Gen);									// 상태
		GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 100.0f));	// 충돌체 크기 설정
		GetComponent<RigidBody>()->SetMass(10.0f);							// 무게 설정
		GetComponent<Animator>()->SetScale(math::Vector2(2.0f, 2.0f));		// 이미지 스케일 설정

		// attackBox의 초기값 설정
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwner(this);
		attackBox->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 10.0f));
	}

	void GianticEnt::Update()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		// attackBox 값세팅
		MonsterAttack* attackBox = GetMonsterAttackBox();
		attackBox->SetOwnerPos(pos);
		attackBox->SetOwnerState((UINT)GetMonsterState());
		attackBox->SetOwnerDirection((UINT)GetMonsterDirection());

		Monster::Update();
	}

	void GianticEnt::Render(HDC _hdc)
	{
		Monster::Render(_hdc);
	}

	void GianticEnt::MakeAnimation()
	{

	}

	void GianticEnt::OnCollisionEnter(Collider* _other)
	{

	}

	void GianticEnt::OnCollisionStay(Collider* _other)
	{

	}

	void GianticEnt::OnCollisionExit(Collider* _other)
	{

	}

	void GianticEnt::Gen()
	{

	}

	void GianticEnt::Idle()
	{

	}

	void GianticEnt::Walk()
	{

	}

	void GianticEnt::Patrol()
	{

	}

	void GianticEnt::Trace()
	{

	}

	void GianticEnt::AttackReady()
	{

	}

	void GianticEnt::Attack()
	{

	}

	void GianticEnt::AttackEnd()
	{

	}

	void GianticEnt::Hit()
	{

	}

	void GianticEnt::Dead()
	{

	}

	void GianticEnt::Wall()
	{

	}
}