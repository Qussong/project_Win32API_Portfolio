#include "vanCatSeol.h"
#include "vanAnimator.h"
#include "vanCollider.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanRigidBody.h"
#include "vanTransform.h"

#define WALK_SPEED			150.0f

namespace van
{
	CatSeol::CatSeol()
	{
		// nothing
	}

	CatSeol::~CatSeol()
	{
		// nothing
	}

	void CatSeol::Init()
	{
		MakeAnimation();

		// NPC 초기설정
		SetNPCDirection(NPCDirection::Left);
		SetNPCState(NPCState::Patrol);
		GetComponent<Collider>()->SetSize(math::Vector2(58.0f, 40.0f));
	}

	void CatSeol::Update()
	{
		NPC::Update();

		// Animation 재생여부 판정_1
		SetNPCPastState(GetNPCState());			// 현재 NPC의 상태를 저장
		SetNPCPastDirection(GetNPCDirection());	// 현재 NPC의 방향을 저장

		switch (GetNPCState())
		{
		case NPCState::Idle:
			Idle();
			break;
		case NPCState::Walk:
			Walk();
			break;
		case NPCState::Patrol:
			Patrol();
			break;
		default:
			__noop;
		}

		// Animation 재생여부 판정_2
		// 만약 몬스터의 상태,방향이 바꼈다면
		if (GetNPCState() != GetNPCPastState()
			|| GetNPCDirection() != GetNPCPastDirection())
		{
			SetPlayAnimation(true);
		}
	}

	void CatSeol::Render(HDC _hdc)
	{
		NPC::Render(_hdc);
	}

	void CatSeol::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		// Idle
		at->CreateAnimation(L"Cat_Seol_Idle_L", ResourceManager::Find<Texture>(L"Cat_Seol_Idle_L"), math::Vector2(0.0f, 0.0f), math::Vector2(27.0f, 20.0f), 2);
		at->CreateAnimation(L"Cat_Seol_Idle_R", ResourceManager::Find<Texture>(L"Cat_Seol_Idle_R"), math::Vector2(0.0f, 0.0f), math::Vector2(27.0f, 20.0f), 2);
		// Walk
		at->CreateAnimation(L"Cat_Seol_Walk_L", ResourceManager::Find<Texture>(L"Cat_Seol_Walk_L"), math::Vector2(0.0f, 0.0f), math::Vector2(29.0f, 20.0f), 6);
		at->CreateAnimation(L"Cat_Seol_Walk_R", ResourceManager::Find<Texture>(L"Cat_Seol_Walk_R"), math::Vector2(0.0f, 0.0f), math::Vector2(29.0f, 20.0f), 6);
		at->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void CatSeol::Idle()
	{
		Animator* at = GetComponent<Animator>();

		// Patrol 상태일 때 
		if (GetPatrolFlag() == true)
		{
			// 시간 누적
			AddTimer(Time::GetDeltaTime());

			// 누적된 시간이 3초 이상이되면
			if (GetTimer() >= 3.0f)
			{
				SetTimer(0.0f);					// 누적시간 0초로 초기화
				SetNPCState(NPCState::Walk);	// Monster의 상태를 Walk 로 변경

				// 방향전환
				if (GetNPCDirection() == NPCDirection::Left)
				{
					SetNPCDirection(NPCDirection::Right);
				}
				else
				{
					SetNPCDirection(NPCDirection::Left);
				}
			}
			// 누적된 시간이 3초 이상이 아니라면
			else
			{
				if (GetNPCDirection() == NPCDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Idle_L", true);
						SetPlayAnimation(false);
					}
				}
				else
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Idle_R", true);
						SetPlayAnimation(false);
					}
				}
			}
		}
		// Patrol 상태가 아닐때
		else
		{
			__noop;
		}
	}

	void CatSeol::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		// Patrol 상태일 때 
		if (GetPatrolFlag() == true)
		{
			// 시간 누적
			AddTimer(Time::GetDeltaTime());

			// 누적된 시간이 2초 이상이되면
			if (GetTimer() >= 2.0f)
			{
				SetTimer(0.0f);
				SetNPCState(NPCState::Idle);
			}
			// 누적된 시간이 2초 이상이 아니라면
			else
			{
				// Walk_L
				if (GetNPCDirection() == NPCDirection::Left)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Walk_L", true);
						SetPlayAnimation(false);
					}
					pos.x -= (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
				// Walk_R
				if (GetNPCDirection() == NPCDirection::Right)
				{
					if (GetPlayAnimation() == true)
					{
						at->PlayAnimation(L"Cat_Seol_Walk_R", true);
						SetPlayAnimation(false);
					}
					pos.x += (WALK_SPEED * Time::GetDeltaTime());
					tr->SetPosition(pos);
				}
			}
		}
		// Patrol 상태가 아닐때
		else
		{
			__noop;
		}
	}

	void CatSeol::Patrol()
	{
		// 몬스터가 모든 상태에서 Patrol 행동을 보이도록 설정
		SetPatrolFlag(true);
		// Patrol 상태로 전환됐기에 Trace Flag는 꺼준다.
		//SetTraceFlag(false);
		// Patrol시 Idle 부터 시작하도록 한다.
		SetNPCState(NPCState::Idle);
	}

}