#include "vanYggdrasill.h"
#include "vanCollider.h"
#include "vanPlayerAttack.h"
#include "vanPlayer.h"
#include "vanObject.h"

namespace van
{
	Yggdrasill::Yggdrasill()
	{
		// nothing
	}

	Yggdrasill::~Yggdrasill()
	{
		// nothing
	}

	void Yggdrasill::Init()
	{
		Boss::Init();		// 아무것도 안함

		MakeAnimation();	// 아무것도 안함

		SetBossState(BossState::Gen);
		SetBossDirection(BossDirection::Center);

		mBody = Object::Instantiate<YggdrasillBody>(enums::eLayerType::Yggdrasill_Body);
		mHead = Object::Instantiate<YggdrasillHead>(enums::eLayerType::Yggdrasill_Head);
		mChin = Object::Instantiate<YggdrasillChin>(enums::eLayerType::Yggdrasill_Chin);
		mHandLeft = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		mHandRight = Object::Instantiate<YggdrasillHand>(enums::eLayerType::Yggdrasill_Hand);
		
		mHandLeft->SetHandPos(YggdrasillHand::HandPos::Left);
		mHandRight->SetHandPos(YggdrasillHand::HandPos::Right);

		mBody->SetPos(math::Vector2(Window_X / 2, Window_Y / 2));
		mHead->SetPos(math::Vector2(Window_X / 2 - 10.0f, Window_Y / 2 - 60.0f));
		mChin->SetPos(math::Vector2(Window_X / 2 + 20.0f, Window_Y / 2 + 100.0f));
		mHandLeft->SetPos(math::Vector2(Window_X / 2 - 400.0f + 20.0f, Window_Y / 2 + 100.0f));
		mHandRight->SetPos(math::Vector2(Window_X / 2 + 400.0f + 20.0f, Window_Y / 2 + 100.0f));
	}

	void Yggdrasill::Update()
	{
		Boss::Update();	// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.
	}

	void Yggdrasill::Render(HDC _hdc)
	{
		Boss::Render(_hdc);	// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
	}

	void Yggdrasill::MakeAnimation()
	{
		// nothing
	}

	void Yggdrasill::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Yggdrasill::Gen()
	{

	}

	void Yggdrasill::Idle()
	{

	}

	void Yggdrasill::AttackReady()
	{

	}

	void Yggdrasill::Attack()
	{

	}

	void Yggdrasill::AttackEnd()
	{
	}

	void Yggdrasill::Hit()
	{

	}

	void Yggdrasill::Dead()
	{

	}

	void Yggdrasill::AttackMelee()
	{

	}

	void Yggdrasill::AttackSmash()
	{

	}

	void Yggdrasill::AttackRange()
	{

	}

}