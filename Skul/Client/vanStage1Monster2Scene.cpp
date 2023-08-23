#include "vanStage1Monster2Scene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanTransform.h"
#include "vanWall.h"
#include "vanPlayer.h"
#include "vanDoor.h"
#include "vanAnimator.h"
#include "vanCarleonRecruit.h"

// player
#define PLAYER_INIT_POS_Y	400.0f
#define PLAYER_INIT_POS_X	-1180.0f
// floor

// wall

// door
#define DOOR_Y_L	-265.0f
#define DOOR_Y_R	-188.0f
#define DOOR_X		520.0f
// Monster
#define FLOOR_UP_CONDITION	-3.0f

namespace van
{
	Stage1Monster2Scene::Stage1Monster2Scene()
	{
		// nothing
	}

	Stage1Monster2Scene::~Stage1Monster2Scene()
	{
		// nothing
	}

	void Stage1Monster2Scene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));

		SetSceneTarget(player);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1Monster2Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();

		Wave1();
		Wave2();
		WaveExit();
	}

	void Stage1Monster2Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1Monster2Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1Monster2Scene::SceneIN()
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

	void Stage1Monster2Scene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1Monster2Scene::CameraMove()
	{
		// nothing
	}

	void Stage1Monster2Scene::MakeWorld()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();					// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster_2"));		// BackGround 객체의 texture 설정
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

	void Stage1Monster2Scene::MakeFloor()
	{
		// Floor
		Floor* floorB1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 511.0f, Window_Y / 2 + 565.0f));
		floorB1_1->GetComponent<Collider>()->SetSize(math::Vector2(80.0f, 2.0f));

		Floor* floorB1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 80.0f, Window_Y / 2 + 565.0f));
		floorB1_2->GetComponent<Collider>()->SetSize(math::Vector2(80.0f, 2.0f));

		Floor* floorB2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 250.0f, Window_Y / 2 + 615.0f));
		floorB2->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));

		Floor* floor1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 990.0f, Window_Y / 2 + 420.0f));
		floor1_1->GetComponent<Collider>()->SetSize(math::Vector2(440.0f, 2.0f));

		Floor* floor1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f, Window_Y / 2 + 420.0f));
		floor1_2->GetComponent<Collider>()->SetSize(math::Vector2(640.0f, 2.0f));

		Floor* floor2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 290.0f, Window_Y / 2 + 260.0f));
		floor2->GetComponent<Collider>()->SetSize(math::Vector2(150.0f, 2.0f));

		Floor* floor3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 262.0f, Window_Y / 2 + 60.0f));
		floor3->GetComponent<Collider>()->SetSize(math::Vector2(500.0f, 2.0f));

		Floor* floor4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 695.0f, Window_Y / 2 - 100.0f));
		floor4->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));
	}

	void Stage1Monster2Scene::MakeWall()
	{
		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 772.0f, Window_Y / 2 + 520.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 200.0f));

		Wall* wall_2_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 768.0f, Window_Y / 2 - 216.0f));
		wall_2_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 825.0f));

		Wall* wall_2_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 992.0f, Window_Y / 2 + 196.0f));
		wall_2_2->GetComponent<Collider>()->SetSize(math::Vector2(446.0f, 2.0f));

		Wall* wall_3_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 562.0f, Window_Y / 2 + 590.0f));
		wall_3_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 463.0f, Window_Y / 2 + 590.0f));
		wall_3_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 130.0f, Window_Y / 2 + 590.0f));
		wall_3_3->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_4 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 32.0f, Window_Y / 2 + 590.0f));
		wall_3_4->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_4_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_4_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 264.0f, Window_Y / 2 + 510.0f));
		wall_4_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 204.0f));

		Wall* wall_4_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_4_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 237.0f, Window_Y / 2 + 408.0f));
		wall_4_2->GetComponent<Collider>()->SetSize(math::Vector2(53.0f, 2.0f));

		Wall* wall_4_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_4_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 210.0f, Window_Y / 2 + 334.0f));
		wall_4_3->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 147.0f));

		Wall* wall_5_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 368.0f, Window_Y / 2 + 160.0f));
		wall_5_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 185.0f));

		Wall* wall_5_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 342.0f, Window_Y / 2 + 65.0f));
		wall_5_2->GetComponent<Collider>()->SetSize(math::Vector2(45.0f, 2.0f));

		Wall* wall_5_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 320.0f, Window_Y / 2 + 38.0f));
		wall_5_3->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 50.0f));

		Wall* wall_5_4 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 248.0f, Window_Y / 2 + 13.0f));
		wall_5_4->GetComponent<Collider>()->SetSize(math::Vector2(150.0f, 2.0f));

		Wall* wall_5_5 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5_5->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 174.0f, Window_Y / 2 - 42.0f));
		wall_5_5->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 113.0f));

		// Monster Wall
		Wall* wall1_2L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall1_2L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f - 640.0f / 2, Window_Y / 2 + 420.0f - 100.0f / 2));
		wall1_2L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall1_2L->SetFloorLimit(true);

		Wall* wall1_2R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall1_2R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f + 640.0f / 2, Window_Y / 2 + 420.0f - 100.0f / 2));
		wall1_2R->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall1_2R->SetFloorLimit(true);

		Wall* wall2L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall2L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 290.0f - 150.0f / 2, Window_Y / 2 + 260.0f - 100.0f / 2));
		wall2L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall2L->SetFloorLimit(true);

		Wall* wall3L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall3L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 262.0f - 500.0f / 2, Window_Y / 2 + 60.0f - 100.0f / 2));
		wall3L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall3L->SetFloorLimit(true);

		Wall* wall3R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall3R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 262.0f + 500.0f / 2, Window_Y / 2 + 60.0f - 100.0f / 2));
		wall3R->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, 100.0f));
		wall3R->SetFloorLimit(true);

		Wall* wall4L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall4L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 695.0f - 1040.0f / 2, Window_Y / 2 - 100.0f - WALL_HEIGHT / 2));
		wall4L->GetComponent<Collider>()->SetSize(math::Vector2(10.0f, WALL_HEIGHT));
		wall4L->SetFloorLimit(true);
	}

	void Stage1Monster2Scene::MakeDoor()
	{
		// Door_L
		Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
		door_L->SetActive(false);
		door_L->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y_L));
		door_L->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_Middle_Boss_DeActive"));
		door_L->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(2.0f, 2.0f));

		// Door_R
		Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
		door_R->SetActive(false);
		door_R->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + (DOOR_X * 2), Window_Y / 2 + DOOR_Y_R));
		door_R->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_DeActive"));
		door_R->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(2.0f, 2.0f));
		
	}

	void Stage1Monster2Scene::OpenDoor()
	{
		if (mbOpenDoor == false)
		{
			mbOpenDoor = true;

			// Door_L
			Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
			door_L->GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 180.0f));
			door_L->GetComponent<Collider>()->SetOffset(math::Vector2(20.0f, 60.0f));
			door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y_L));
			door_L->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_Middle_Boss", true);
		}
	}

	void Stage1Monster2Scene::Wave1()
	{
		if (GetMonsterCnt() == 0
			&& mbWave1 == false)
		{
			mbWave1 = true;

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f + (i * 10), Window_Y / 2 + 420.0f + FLOOR_UP_CONDITION));
				carleon1->GetComponent<Animator>()->SetAffectedCamera(true);
			}

			for (int i = 0; i < 2; ++i)
			{
				//CarleonRecruit* carleon2 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				//carleon2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X + (i * 10), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				//carleon2->GetComponent<Animator>()->SetAffectedCamera(true);
			}
		}
	}

	void Stage1Monster2Scene::Wave2()
	{
		if (GetMonsterCnt() == 0
			&& mbWave1 == true
			&& mbWave2 == false)
		{
			mbWave2 = true;

			for (int i = 0; i < 2; ++i)
			{
				//CarleonRecruit* carleon1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				//carleon1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X + (i * 10), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				//carleon1->GetComponent<Animator>()->SetAffectedCamera(true);
			}

			for (int i = 0; i < 2; ++i)
			{
				//CarleonRecruit* carleon2 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				//carleon2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X + (i * 10), Window_Y / 2 + FLOOR_2_Y + FLOOR_UP_CONDITION));
				//carleon2->GetComponent<Animator>()->SetAffectedCamera(true);
			}
		}
	}

	void Stage1Monster2Scene::WaveExit()
	{
		if (GetMonsterCnt() == 0
			&& mbWave2 == true)
		{
			OpenDoor();
		}
	}
}