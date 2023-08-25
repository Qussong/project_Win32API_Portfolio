#include "vanYggdrasillHand.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanYggdrasill.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanWall.h"
#include "vanTransform.h"

#define INIT_POS_LEFT_X		-380.0f
#define INIT_POS_LEFT_Y		100.0f
#define INIT_POS_RIGHT_X	420.0f
#define INIT_POS_RIGHT_Y	100.0f
#define IDLE_UP_DOWN_SPEED	15.0f
#define FISTSLAM_CNT		2

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
		col->SetSize(math::Vector2(250.0f, 250.0f));
	}

	void YggdrasillHand::Update()
	{
		GameObject::Update();

		InitAddPos();		// 최기위치값 저장 -> Left, Right 구분을 Init에서 할 수 없기에 Update에 넣어준다.
		FollowBodyPos();	// Body객체의 위치를 기준으로 Hand의 위치값을 설정한다.

		mPastState = mState;	// 현재의 상태와 미래의 상태를 비교하여 애니메이션 재생여부를 결정한다.(다르면 mPlayAnimation = true)

		switch (mState)
		{
		case HandState::Gen:
			Gen();
			break;
		case HandState::Idle:
			Idle();
			break;
		case HandState::AttackReady:
			AttackReady();
			break;
		case HandState::Attack:
			Attack();
			break;
		case HandState::AttackEnd:
			AttackEnd();
			break;
		case HandState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		if (mPastState != mState)
		{
			mbPlayAnimation = true;
		}
	}

	void YggdrasillHand::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillHand::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		
		at->CreateAnimation(L"Hand_Idle_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(166.0f, 147.0f), 7, math::Vector2::Zero, 0.2f);
		at->CreateAnimation(L"Hand_Idle_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(166.0f, 147.0f), 7, math::Vector2::Zero, 0.2f);
		at->CreateAnimation(L"Hand_FistSlam_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_FistSlam_L"), math::Vector2(0.0f, 0.0f), math::Vector2(151.0f, 167.0f), 1);
		at->CreateAnimation(L"Hand_FistSlam_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_FistSlam_R"), math::Vector2(0.0f, 0.0f), math::Vector2(165.0f, 144.0f), 1);

	}

	void YggdrasillHand::OnCollisionEnter(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();

		Floor* floor = dynamic_cast<Floor*>(obj);
		Wall* wall = dynamic_cast<Wall*>(obj);

		if (floor != nullptr
			|| wall != nullptr)
		{
			mbCollisionFloor = true;
		}
	}

	void YggdrasillHand::OnCollisionStay(Collider* _other)
	{

	}

	void YggdrasillHand::OnCollisionExit(Collider* _other)
	{

	}

	void YggdrasillHand::Gen()
	{

	}

	void YggdrasillHand::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();
		math::Vector2 pos = tr->GetPosition();
		at->SetScale(math::Vector2(2.0f, 2.0f));

		if (mbPlayAnimation == true)
		{
			if (mHandPos == HandPos::Left)
			{
				at->PlayAnimation(L"Hand_Idle_L", true);
			}
			if (mHandPos == HandPos::Right)
			{
				at->PlayAnimation(L"Hand_Idle_R", true);
			}

			mbPlayAnimation = false;
		}

		mTime += Time::GetDeltaTime();
		if (mTime >= 1.0f)
		{
			mTime = 0.0f;
			if (mUpDownFlag == false)
			{
				mUpDownFlag = true;
			}
			else
			{
				mUpDownFlag = false;
			}
		}

		if (mUpDownFlag == true)
		{
			mAddPos.y += IDLE_UP_DOWN_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mAddPos.y -= IDLE_UP_DOWN_SPEED * Time::GetDeltaTime();
		}
	}

	void YggdrasillHand::AttackReady()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamReady();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeReady();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsReady();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillHand::Attack()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlam();
			break;
		case Yggdrasill::BossSkill::Swipe:
			Swipe();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbs();
			break;
		default:
			__noop;
		}

	}

	void YggdrasillHand::AttackEnd()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamEnd();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeEnd();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
	}


	void YggdrasillHand::Dead()
	{

	}

	void YggdrasillHand::FistSlamReady()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbReadyFinish == false)
		{
			if (mbPlayAnimation == true)
			{
				ResetInitPos();
				mInitPos = tr->GetPosition();
				if (mHandPos == HandPos::Left)
				{
					at->PlayAnimation(L"Hand_FistSlam_L", false);
				}
				if (mHandPos == HandPos::Right)
				{
					at->PlayAnimation(L"Hand_FistSlam_R", false);
				}

				mbPlayAnimation = false;
			}

			math::Vector2 pos = tr->GetPosition();
			pos.y -= 130.0f * Time::GetDeltaTime();
			tr->SetPosition(pos);
			float gap = mInitPos.y - pos.y;

			if (fabs(gap) >= 350.0f)
			{
				mbReadyFinish = true;
				mInitPos2 = pos;
			}
		}
	}

	void YggdrasillHand::SwipeReady()
	{
	}

	void YggdrasillHand::MagicOrbsReady()
	{
	}

	void YggdrasillHand::FistSlam()
	{
		// Ready 에서 넘어올때 초기화 안된것들 초기화
		mbReadyInit = false;
		mInitPos = math::Vector2::Zero;

		// FistSlam 로직
		Transform* tr = GetComponent<Transform>();
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		GameObject* target = owner->GetTarget();
		Transform* tr_target = target->GetComponent<Transform>();

		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::FrontFloor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Wall, true);

		math::Vector2 pos = tr->GetPosition();
		math::Vector2 targetPos = tr_target->GetPosition();
		

		if (mbEndFinish == false)
		{
			if (mbFistSlamEnd == true)
			{
				// 주먹위치 정렬
				if (pos.x < mInitPos2.x - 5.0f)
				{
					pos.x += 50.0f * Time::GetDeltaTime();
					tr->SetPosition(pos);
				}
				else if (pos.x > mInitPos2.x + 5.0f)
				{
					pos.x -= 50.0f * Time::GetDeltaTime();
					tr->SetPosition(pos);
				}
				else
				{
					tr->SetPosition(mInitPos2);
					mbFistSlamEnd = false;
					mbEndFinish = true;
				}
			}
			else
			{
				if (mbDirectionSet == false)
				{
					dir = targetPos - pos;
					dir.Normalize();	// 방향벡터
					mbDirectionSet = true;
				}
				float speed = 300.0f;

				if (mbCollisionFloor == false)
				{
					pos.x += dir.x * speed * Time::GetDeltaTime();
					pos.y += dir.y * speed * Time::GetDeltaTime();

					tr->SetPosition(pos);
				}
				else
				{
					pos.x -= dir.x * speed * Time::GetDeltaTime();
					pos.y -= dir.y * speed * Time::GetDeltaTime();

					tr->SetPosition(pos);

					if (mInitPos2.y >= pos.y)
					{
						mbCollisionFloor = false;
						mbDirectionSet = false;
						owner->AddFistSlamCnt();
						if (owner->GetFistSlamCnt() > FISTSLAM_CNT)
						{
							mbFistSlamEnd = true;
						}
					}
				}
			}
		}
	}

	void YggdrasillHand::Swipe()
	{
	}

	void YggdrasillHand::MagicOrbs()
	{
	}

	void YggdrasillHand::FistSlamEnd()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 initPos = dynamic_cast<Yggdrasill*>(GetOwner())->GetInitPos() + mInitAddPos;

		if (mbEndFinish == false)
		{
			if (pos.y < initPos.y - 5.0f)
			{
				pos.y += 100.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			else if (pos.y > initPos.y + 5.0f)
			{
				pos.y -= 100.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			else
			{
				tr->SetPosition(initPos);
				mbEndFinish = true;
			}
		}

	}

	void YggdrasillHand::SwipeEnd()
	{
	}

	void YggdrasillHand::MagicOrbsEnd()
	{
	}

	void YggdrasillHand::InitAddPos()
	{
		if (mbInitFlag == true)
		{
			if (mHandPos == HandPos::Left)
			{
				mInitAddPos = math::Vector2(INIT_POS_LEFT_X, INIT_POS_LEFT_Y);
				mAddPos = mInitAddPos;
			}
			if (mHandPos == HandPos::Right)
			{
				mInitAddPos = math::Vector2(INIT_POS_RIGHT_X, INIT_POS_RIGHT_Y);
				mAddPos = mInitAddPos;
			}

			mbInitFlag = false;
		}
	}

	void YggdrasillHand::FollowBodyPos()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();

		if (mState == HandState::Idle)
		{
			math::Vector2 ownerPos = tr_owner->GetPosition();
			math::Vector2 newPos = ownerPos + mAddPos;

			tr->SetPosition(newPos);
		}
	}

	void YggdrasillHand::ResetInitPos()
	{
		Transform* tr = GetComponent<Transform>();

		mAddPos = mInitAddPos;	// AddPos 를 초기화해준다.
		math::Vector2 initPos = dynamic_cast<Yggdrasill*>(GetOwner())->GetInitPos();
		tr->SetPosition(initPos + mAddPos);	// 초기위치로 이동
	}
};