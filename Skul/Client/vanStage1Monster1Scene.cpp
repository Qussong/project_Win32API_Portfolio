#include "vanStage1Monster1Scene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanDoor.h"
#include "vanWall.h"

#include "vanCarleonRecruit.h"
#include "vanManAtArms.h"

// player
#define PLAYER_INIT_POS_X	-1200.0f
#define PLAYER_INIT_POS_Y	795.0f - 410.0f
// floor
#define FLOOR_B1_Y	640.0f
#define FLOOR_1_Y	420.0f
#define FLOOR_1_X	1015.0f
#define FLOOR_2_Y	200.0f
#define FLOOR_2_X	470.0f
#define FLOOR_3_Y	320.0f - 410.0f
#define FLOOR_4_Y	35.0f - 410.0f
// wall
#define WALL_B1_Y	940.0f - 410.0f
#define WALL_B1_X	760.0f
// door
#define DOOR_X		260.0f
#define DOOR_Y		520.0f
#define DOOR_GAP	520.0f
// Monster
#define FLOOR_UP_CONDITION	-3.0f

namespace van
{
	Stage1Monster1Scene::Stage1Monster1Scene()
	{
		// nothing
	}

	Stage1Monster1Scene::~Stage1Monster1Scene()
	{
		// nothing
	}

	void Stage1Monster1Scene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		SetSceneTarget(player);
	}

	void Stage1Monster1Scene::Update()
	{
		Scene::Update();

		Wave1();
		Wave2();
		WaveExit();
	}

	void Stage1Monster1Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1Monster1Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1Monster1Scene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Trap, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Drop, eLayerType::Floor, true);
	}

	void Stage1Monster1Scene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1Monster1Scene::CameraMove()
	{
		// nothing
	}

	void Stage1Monster1Scene::MakeWorld()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster_1"));			// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// [ World_Wall ]
		Texture* image = bgsr->GetTexture();
		math::Vector2 size = image->GetSize();
		// Left
		Wall* worldWall_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_L->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - size.x / 2 - 1.0f, Window_Y / 2));
		// Right
		Wall* worldWall_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_R->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + size.x / 2 + 1.0f, Window_Y / 2));
	}

	void Stage1Monster1Scene::MakeFloor()
	{
		Floor* floorB1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1->GetComponent<Collider>()->SetSize(math::Vector2(1520.0f, /*FLOOR_HEIGHT*/ 50.0f));
		floorB1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_B1_Y + 25.0f));
		
		Floor* floor1_L = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_L->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, /*FLOOR_HEIGHT*/ 50.0f));
		floor1_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_1_X, Window_Y / 2 + FLOOR_1_Y + 25.0f));
		
		Floor* floor1_R = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_R->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, /*FLOOR_HEIGHT*/ 50.0f));
		floor1_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_1_X, Window_Y / 2 + FLOOR_1_Y + 25.0f));
		
		Floor* floor2_L = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_L->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, /*FLOOR_HEIGHT*/ 20.0f));
		floor2_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X, Window_Y / 2 + FLOOR_2_Y + 10.0f));
		
		Floor* floor2_R = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_R->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, /*FLOOR_HEIGHT*/ 20.0f));
		floor2_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X, Window_Y / 2 + FLOOR_2_Y + 10.0f));
		
		Floor* floor3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Collider>()->SetSize(math::Vector2(1800.0f, /*FLOOR_HEIGHT*/ 20.0f));
		floor3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_3_Y + 15.0f));

		Floor* floor4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Collider>()->SetSize(math::Vector2(350.0f, /*FLOOR_HEIGHT*/ 20.0f));
		floor4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_4_Y + 10.0f));
	}

	void Stage1Monster1Scene::MakeWall()
	{
		// Wall
		Wall* wallB1_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wallB1_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - WALL_B1_X, Window_Y / 2 + WALL_B1_Y + 5.0f));
		wallB1_L->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, 210));
		
		Wall* wallB1_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wallB1_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + WALL_B1_X, Window_Y / 2 + WALL_B1_Y + 5.0f));
		wallB1_R->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, 210));
		
		// Monster Wall
		Wall* wall2_LL = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall2_LL->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall2_LL->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X - 420.0f / 2, Window_Y / 2 + FLOOR_2_Y - WALL_HEIGHT - 40.0f));
		wall2_LL->SetFloorLimit(true);
	
		Wall* Wall2_LR = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall2_LR->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall2_LR->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X + 420.0f / 2, Window_Y / 2 + FLOOR_2_Y - WALL_HEIGHT - 40.0f));
		Wall2_LR->SetFloorLimit(true);
	
		Wall* Wall2_RL = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall2_RL->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall2_RL->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X - 420.0f / 2, Window_Y / 2 + FLOOR_2_Y - WALL_HEIGHT - 40.0f));
		Wall2_RL->SetFloorLimit(true);
	
		Wall* Wall2_RR = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall2_RR->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall2_RR->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X + 420.0f / 2, Window_Y / 2 + FLOOR_2_Y - WALL_HEIGHT - 40.0f));
		Wall2_RR->SetFloorLimit(true);

		Wall* Wall3_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall3_L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall3_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 1800.0f / 2, Window_Y / 2 + FLOOR_3_Y - WALL_HEIGHT - 40.0f));
		Wall3_L->SetFloorLimit(true);

		Wall* Wall3_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall3_R->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall3_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 1800.0f / 2, Window_Y / 2 + FLOOR_3_Y - WALL_HEIGHT - 40.0f));
		Wall3_R->SetFloorLimit(true);

		Wall* Wall4_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall4_L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall4_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 350.0f / 2, Window_Y / 2 + FLOOR_4_Y - WALL_HEIGHT - 35.0f));
		Wall4_L->SetFloorLimit(true);

		Wall* Wall4_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		Wall4_R->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		Wall4_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 350.0f / 2, Window_Y / 2 + FLOOR_4_Y - WALL_HEIGHT - 35.0f));
		Wall4_R->SetFloorLimit(true);
	}

	void Stage1Monster1Scene::MakeDoor()
	{
		// Door_L
		Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
		door_L->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_L->SetActive(false);
		door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - DOOR_X, Window_Y / 2 + DOOR_Y));
		door_L->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_1_DeActive"));
		door_L->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(1.63f, 1.61f));
		
		// Door_R
		Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
		door_R->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_R->SetActive(false);
		door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - DOOR_X + DOOR_GAP, Window_Y / 2 + DOOR_Y));
		door_R->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_2_DeActive"));
		door_R->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(2.0f, 2.0f));
	}

	void Stage1Monster1Scene::OpenDoor()
	{
		if (mbOpenDoor == false)
		{
			mbOpenDoor = true;

			// Door_L
			Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
			door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - DOOR_X, Window_Y / 2 + DOOR_Y));
			door_L->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_1", true);
			// Door_R
			Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
			door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - DOOR_X + DOOR_GAP, Window_Y / 2 + DOOR_Y));
			door_R->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_2", true);
		}
	}

	void Stage1Monster1Scene::Wave1()
	{
		if (GetMonsterCnt() == 0
			&& mbWave1 == false)
		{
			mbWave1 = true;

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X + (i * 20), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				//carleon1->GetComponent<Animator>()->SetAffectedCamera(true);
			}

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon2 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X + (i * 20), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				//carleon2->GetComponent<Animator>()->SetAffectedCamera(true);
			}
		}
	}

	void Stage1Monster1Scene::Wave2()
	{
		if (GetMonsterCnt() == 0
			&& mbWave1 == true
			&& mbWave2 == false)
		{
			mbWave2 = true;

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X + (i * 20), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				carleon1->GetComponent<Animator>()->SetAffectedCamera(true);
			}

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon2 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X + (i * 20), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				carleon2->GetComponent<Animator>()->SetAffectedCamera(true);
			}
		}
	}

	void Stage1Monster1Scene::WaveExit()
	{
		if (GetMonsterCnt() == 0
			&& mbWave2 == true)
		{
			OpenDoor();
		}
	}
}