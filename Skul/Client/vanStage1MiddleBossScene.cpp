#include "vanStage1MiddleBossScene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanAnimator.h"
#include "vanTransform.h"
#include "vanCollider.h"
#include "vanFloor.h"
#include "vanWall.h"
#include "vanPlayer.h"
#include "vanCollisionManager.h"
#include "vanDoor.h"
#include "vanCarleonRecruit.h"
#include "vanMage.h"

#define PLAYER_INIT_POS_Y	55
#define PLAYER_INIT_POS_X	-1480
// Door
#define DOOR_Y		-40.0f
#define DOOR_X		700.0f
#define DOOR_GAP	520.0f
// Camera
#define CAMERA_OFFSET_Y				-200.0f
#define CAMERA_OFFSET_X				660.0f
#define CAMERA_CONTROL_POS_X_1		-340.0f
#define CAMERA_CONTROL_POS_X_2		1020.0f
#define CAMERA_ANCHOR_X				-290.0f
#define CAMERA_ANCHOR_Y				50.0f
//#define CAMERA_OFFSET_DOUBLESPEED	5
// Monster
#define FLOOR_UP_CONDITION	-3.0f

namespace van
{
	Stage1MiddleBossScene::Stage1MiddleBossScene()
	{
		// nothing
	}

	Stage1MiddleBossScene::~Stage1MiddleBossScene()
	{
		// nothing
	}

	void Stage1MiddleBossScene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		// Mage
		Mage* mage = Object::Instantiate<Mage>(enums::eLayerType::Boss_Mage);
		mage->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 280.0f + FLOOR_UP_CONDITION));
		mage->SetTartget(player);

		SetSceneTarget(player);
	}

	void Stage1MiddleBossScene::Update()
	{
		Scene::Update();
		CameraMove();

		Wave1();
		Wave2();
		WaveExit();
	}

	void Stage1MiddleBossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1MiddleBossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1MiddleBossScene::SceneIN()
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
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boss_Mage, eLayerType::Floor, true);
	}

	void Stage1MiddleBossScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1MiddleBossScene::CameraMove()
	{
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - playerPos.y);

		if (playerPos.x > CAMERA_CONTROL_POS_X_1
			&& playerPos.x < CAMERA_CONTROL_POS_X_2)
		{
			math::Vector2 anchorPosX = math::Vector2(CAMERA_ANCHOR_X, CAMERA_ANCHOR_X);
			math::Vector2 anchorPosY = math::Vector2(CAMERA_ANCHOR_Y, CAMERA_ANCHOR_Y);
			Camera::SetLimitDistance(anchorPosX, anchorPosY);
		}
		else if (playerPos.x > CAMERA_CONTROL_POS_X_2
			|| playerPos.x < CAMERA_CONTROL_POS_X_1)
		{
			Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());
		}
	}

	void Stage1MiddleBossScene::MakeWorld()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Middle_Boss"));			// BackGround 객체의 texture 설정
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

	void Stage1MiddleBossScene::MakeFloor()
	{
		// Floor
		Floor* floor_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 1244.0f, Window_Y / 2 + 85.0f));
		floor_1->GetComponent<Collider>()->SetSize(math::Vector2(575.0f, 2.0f));

		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 280.0f, Window_Y / 2 + 280.0f));
		floor_2->GetComponent<Collider>()->SetSize(math::Vector2(1350.0f, 2.0f));

		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 964.0f, Window_Y / 2 + 85.0f));
		floor_3->GetComponent<Collider>()->SetSize(math::Vector2(1130.0f, 2.0f));
	}

	void Stage1MiddleBossScene::MakeWall()
	{
		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 954.0f, Window_Y / 2 + 180.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));

		Wall* wall_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 395.0f, Window_Y / 2 + 180.0f));
		wall_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));
	}

	void Stage1MiddleBossScene::MakeDoor()
	{
		// Door_L
		Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
		door_L->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_L->SetActive(false);
		door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y));
		door_L->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_1_DeActive"));
		door_L->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(1.63f, 1.61f));

		// Door_R
		Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
		door_R->SetActive(false);
		door_R->GetComponent<Collider>()->SetSize(math::Vector2::Zero);
		door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X + DOOR_GAP, Window_Y / 2 + DOOR_Y - 10.0f));
		door_R->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::Find<Texture>(L"Stage1_Door_Market_DeActive"));
		door_R->GetComponent<SpriteRenderer>()->SetScale(math::Vector2(2.0f, 2.0f));
		
	}

	void Stage1MiddleBossScene::OpenDoor()
	{
		if (mbOpenDoor == false)
		{
			mbOpenDoor = true;

			// Door_L
			Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
			door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y));
			door_L->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_Enter_Boss", true);
			door_L->GetComponent<Animator>()->SetScale(math::Vector2(1.63f, 1.61f));
			
		}
	}

	void Stage1MiddleBossScene::Wave1()
	{
		if (GetMonsterCnt() == 0
			&& mbWave1 == false)
		{
			mbWave1 = true;

			for (int i = 0; i < 2; ++i)
			{
				CarleonRecruit* carleon1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
				carleon1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 280.0f + (i * 20), Window_Y / 2 + 280.0f + FLOOR_UP_CONDITION));
				carleon1->GetComponent<Animator>()->SetAffectedCamera(true);
			}
		}
	}

	void Stage1MiddleBossScene::Wave2()
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

	void Stage1MiddleBossScene::WaveExit()
	{
		if (GetMonsterCnt() == 0
			&& mbWave2 == true)
		{
			OpenDoor();
		}
	}
}