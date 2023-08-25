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
#define FIST_SLAM_SPEED		800.0f
#define SWIP_SPEED			600.0f

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

		InitAddPos();

		if (mPastState != mState)
		{
			mbPlayAnimation = true;

			// 행동패턴의 수행이 끝났음을 알리는 mbEnd를 초기화
			if (mbEnd == true)
			{
				mbEnd = false;
			}
		}

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

		mPastState = mState;	// 현재의 상태와 미래의 상태를 비교하여 애니메이션 재생여부를 결정한다.(다르면 mPlayAnimation = true)
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
		at->CreateAnimation(L"Hand_Swipe_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Swipe_L"), math::Vector2(0.0f, 0.0f), math::Vector2(174.0f, 151.0f), 3);
		at->CreateAnimation(L"Hand_Swipe_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Swipe_R"), math::Vector2(0.0f, 0.0f), math::Vector2(174.0f, 151.0f), 3);
		at->CreateAnimation(L"Hand_Swipe_End_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Swipe_End_L"), math::Vector2(0.0f, 0.0f), math::Vector2(174.0f, 151.0f), 3);
		at->CreateAnimation(L"Hand_Swipe_End_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_Swipe_End_R"), math::Vector2(0.0f, 0.0f), math::Vector2(174.0f, 151.0f), 3);
		at->CreateAnimation(L"Hand_MagicOrb_L", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_MagicOrb_L"), math::Vector2(0.0f, 0.0f), math::Vector2(192.0f, 112.0f), 1);
		at->CreateAnimation(L"Hand_MagicOrb_R", ResourceManager::Find<Texture>(L"Yggdrasill_Hand_MagicOrb_R"), math::Vector2(0.0f, 0.0f), math::Vector2(192.0f, 112.0f), 1);
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

		FollowBodyPos();

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
			FistSlamAttack();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeAttack();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsAttack();
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
		// [ Do List ]
		// - 애니메이션 변경
		// - 주먹을 일정 위치로 올려줘야함

		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbFinish == false)
		{
			// FistSlam Ready 애니메이션 재생
			if (mbPlayAnimation == true)
			{
				mAddPos = mInitAddPos;				// AddPos 를 초기화해준다.
				math::Vector2 initPos = dynamic_cast<Yggdrasill*>(GetOwner())->GetInitPos();
				tr->SetPosition(initPos + mAddPos);	// 초기위치로 이동(Body 초기위치 + 초기 AddPos 값)
				mDepartPosY = tr->GetPosition().y;

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

			math::Vector2 nowPos = tr->GetPosition();
			nowPos.y -= 130.0f * Time::GetDeltaTime();
			tr->SetPosition(nowPos);
			float gap = mDepartPosY - nowPos.y;

			// 특정 위치까지 이동하면 ReadyFinish의 플래그값으로 본체에게 준비가 끝났음을 알려준다.
			if (fabs(gap) >= 350.0f)
			{
				mbFinish = true;
				mResetPos = nowPos;
			}
		}
	}

	void YggdrasillHand::SwipeReady()
	{
		// [ Do List ]
		// - 애니메이션 변경
		// - Hand를 양쪽으로 움직여서 화면상에서 사라지게 한다.

		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbFinish == false
			&& mbEnd == false)
		{
			// Swipe Ready 애니메이션 재생
			if (mbPlayAnimation == true)
			{
				mAddPos = mInitAddPos;				// AddPos 를 초기화해준다.
				math::Vector2 initPos = dynamic_cast<Yggdrasill*>(GetOwner())->GetInitPos();
				tr->SetPosition(initPos + mAddPos);	// 초기위치로 이동(Body 초기위치 + 초기 AddPos 값)
				mDepartPosX = tr->GetPosition().x;

				if (mHandPos == HandPos::Left)
				{
					at->PlayAnimation(L"Hand_Swipe_L", false);
				}
				if (mHandPos == HandPos::Right)
				{
					at->PlayAnimation(L"Hand_Swipe_R", false);
				}

				mbPlayAnimation = false;
			}

			math::Vector2 nowPos = tr->GetPosition();
			if (mHandPos == HandPos::Left)
			{
				nowPos.x -= 150.0f * Time::GetDeltaTime();
			}
			if (mHandPos == HandPos::Right)
			{
				nowPos.x += 150.0f * Time::GetDeltaTime();
			}
			tr->SetPosition(nowPos);
			float gap = mDepartPosX - nowPos.x;

			// 특정 위치까지 이동하면 ReadyFinish의 플래그값으로 본체에게 준비가 끝났음을 알려준다.
			if (fabs(gap) >= 550.0f)
			{
				mbFinish = true;
				mbEnd = true;
				mSwipeDepartPosX = nowPos.x;	// Swipe 패턴이 끝나기전에 행동을 한번 수행한 다음 수행까지 복귀하여 대기해야하는 위치
			}
		}
	}

	void YggdrasillHand::MagicOrbsReady()
	{
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();

		if (mbEnd == false)
		{
			math::Vector2 nowPos = tr->GetPosition();
			if (mbRecordMagicOrbReadyPosY == false)
			{
				mMagicOrbReadyDepartPosY = nowPos.y;
				mbRecordMagicOrbReadyPosY = true;
			}
			nowPos.y += 200.0f * Time::GetDeltaTime();
			tr->SetPosition(nowPos);

			if (fabs(mMagicOrbReadyDepartPosY - nowPos.y) > 100.0f)
			{
				if (mbPlayAnimation == true)
				{
					if (mHandPos == HandPos::Left)
					{
						at->PlayAnimation(L"Hand_MagicOrb_L", false);
					}
					if (mHandPos == HandPos::Right)
					{
						at->PlayAnimation(L"Hand_MagicOrb_R", false);
					}
					mbPlayAnimation = false;
					mbEnd = true;
				}
			}
		}

	}

	void YggdrasillHand::FistSlamAttack()
	{
		// nothing
	}

	void YggdrasillHand::SwipeAttack()
	{
		// nothing
	}

	void YggdrasillHand::MagicOrbsAttack()
	{
	}

	void YggdrasillHand::FistSlamEnd()
	{
		// [ Do List ]
		// - Idle 위치로 Hand 이동

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 initPos = dynamic_cast<Yggdrasill*>(GetOwner())->GetInitPos() + mInitAddPos;

		if (mbFinish == false
			&& mbEnd == false)
		{
			// 초기위치보다 위에 있을 때
			if (pos.y < initPos.y - 5.0f)
			{
				pos.y += 100.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			// 초기위치보다 아래에 있을 때
			else if (pos.y > initPos.y + 5.0f)
			{
				pos.y -= 100.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			// 오차범위내에 들어왔을 때
			else
			{
				tr->SetPosition(initPos);
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillHand::SwipeEnd()
	{
		// Hand 객체의 Player 레이어의 객체들과의 충돌설정 OFF
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, false);

		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();
		math::Vector2 pos = tr->GetPosition();
		float initPosX = mDepartPosX;

		if (mbFinish == false
			&& mbEnd == false)
		{
			// 초기위치보다 왼쪽에 있을 때
			if (pos.x < initPosX - 5.0f)
			{
				pos.x += 150.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			// 초기위치보다 오른쪽에 있을 때
			else if (pos.x > initPosX + 5.0f)
			{
				pos.x -= 150.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			// 오차범위내에 들어왔을 때
			else
			{
				tr->SetPosition(math::Vector2(initPosX, pos.y));
				if (mbPlayAnimation == true)
				{
					if (mHandPos == HandPos::Left)
					{
						at->PlayAnimation(L"Hand_Swipe_End_L");
					}
					if (mHandPos == HandPos::Right)
					{
						at->PlayAnimation(L"Hand_Swipe_End_R");
					}
					mbPlayAnimation = false;
				}

				if (at->IsActiveAnimationComplete() == true)
				{
					mbEnd = true;
					mbFinish = true;
				}
			}
		}
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

	void YggdrasillHand::FistSlam()
	{
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		GameObject* target = owner->GetTarget();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_target = target->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();				// Hand 위치
		math::Vector2 targetPos = tr_target->GetPosition();	// Target 위치

		float resetPosY = mResetPos.y;

		// 방향벡터 계산
		if (mbDirectionSet == false)
		{
			dir = targetPos - pos;		// 벡터 계산 (= 도착위치 - 출발(현재)위치 )
			dir.Normalize();			// 방향벡터

			mbDirectionSet = true;	// 방향벡터 찾음 플래그 ON
		}

		// 방향벡터의 방향으로 주먹 날리기 수행
		if (mbCollisionFloor == false)
		{
			// Hand 객체의 Wall, FrontFloor, Player 레이어의 객체들과의 충돌설정 ON
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::FrontFloor, true);
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Wall, true);
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, true);

			pos.x += dir.x * FIST_SLAM_SPEED * Time::GetDeltaTime();
			pos.y += dir.y * FIST_SLAM_SPEED * Time::GetDeltaTime();

			tr->SetPosition(pos);
		}
		// 벽과 충돌하면 출발위치로 주먹이 되돌아온다.
		else
		{
			// Hand 객체의 Wall, FrontFloor, Player 레이어의 객체들과의 충돌설정 OFF
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::FrontFloor, false);
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Wall, false);
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, false);

			pos.x -= dir.x * FIST_SLAM_SPEED * Time::GetDeltaTime();
			pos.y -= dir.y * FIST_SLAM_SPEED * Time::GetDeltaTime();

			tr->SetPosition(pos);

			// 출발위치의 높이와 같거나 더 높아지면 멈춘다.
			if (resetPosY >= pos.y)
			{
				mbCollisionFloor = false;	// 벽과의 충돌여부 플래그 OFF
				mbDirectionSet = false;		// 방향벡터 계산 수행 플래그 ON
				mbFistSlam = true;			// 공격수행이 완료됨을 알려준다.
			}
		}
	}

	void YggdrasillHand::FistSlamAfter()
	{
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		GameObject* target = owner->GetTarget();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_target = target->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();				// Hand 위치
		math::Vector2 targetPos = tr_target->GetPosition();	// Target 위치
		
		// Hand 객체의 Player 레이어의 객체들과의 충돌설정 OFF
		CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, false);

		float resetPosX = mResetPos.x;

		if (mbFinish == false)
		{
			// 주먹위치 정렬 (오차값 : 10.0f)
			if (pos.x < resetPosX - 5.0f)
			{
				pos.x += 50.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			else if (pos.x > resetPosX + 5.0f)
			{
				pos.x -= 50.0f * Time::GetDeltaTime();
				tr->SetPosition(pos);
			}
			// 오차범위내에 들어왔을 때
			else
			{
				tr->SetPosition(mResetPos);
				mbFinish = true;	// FistSlam Attack 행동 완료 플래그 ON
				// 초기화
				mResetPos = math::Vector2::Zero;
			}
		}
	}

	void YggdrasillHand::Swip()
	{
		Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		GameObject* target = owner->GetTarget();
		Transform* tr = GetComponent<Transform>();
		Transform* tr_target = target->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();	// Hand 위치

		if (mbSwipe == false)
		{
			// Hand 객체의 Player 레이어의 객체들과 충돌 설정 ON
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, true);

			if (mHandPos == HandPos::Left)
			{
				pos.x += SWIP_SPEED * Time::GetDeltaTime();
			}
			if (mHandPos == HandPos::Right)
			{
				pos.x -= SWIP_SPEED * Time::GetDeltaTime();
			}
			tr->SetPosition(pos);
		}

		float gap = fabs(mSwipeDepartPosX - pos.x);
		// 일정거리 이상 이동하게되면 종료
		if (gap >= 1800.0f)
		{
			// Hand 객체의 Player 레이어의 객체들과 충돌 설정 ON
			CollisionManager::SetCollisionLayerCheck(eLayerType::Yggdrasill_Hand, eLayerType::Player, false);

			// 공격수행이 완료됨을 알려준다.
			mbSwipe = true;												
			// 공격수행 대기위치로 Hand를 옮겨준다.
			tr->SetPosition(math::Vector2(mSwipeDepartPosX, pos.y));	
		}
	}

};