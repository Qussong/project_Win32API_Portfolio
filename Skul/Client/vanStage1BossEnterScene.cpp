#include "vanStage1BossEnterScene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanPlayer.h"
#include "vanAnimator.h"
#include "vanWall.h"
#include "vanDoor.h"

// Player
#define PLAYER_INIT_POS_Y	850.0f
#define PLAYER_INIT_POS_X	-650.0f
// Floor
#define FLOOR1_X	-604.5f
#define FLOOR1_Y	770.0f + 115.0f
#define FLOOR2_X	-74.5f
#define FLOOR2_Y	570.0f + 115.0f
#define FLOOR3_X	392.5f
#define FLOOR3_Y	430.0f + 115.0f
#define FLOOR4_X	0.0f
#define FLOOR4_Y	229.0f + 115.0f
#define FLOOR5_X	-110.0f
#define FLOOR5_Y	62.0f + 115.0f
#define FLOOR6_X	-235.0f
#define FLOOR6_Y	-130.0f + 115.0f
#define FLOOR7_X	50.0f
#define FLOOR7_Y	-304.0f + 115.0f
// Camera
#define CAMERA_OFFSET_Y				-200.0f
#define CAMERA_OFFSET_X				660.0f
#define CAMERA_CONTROL_POS_Y		500.0f
#define CAMERA_ANCHOR_X				-290.0f
#define CAMERA_ANCHOR_Y				50.0f

namespace van
{
	Stage1BossEnterScene::Stage1BossEnterScene()
	{
		// nothing
	}

	Stage1BossEnterScene::~Stage1BossEnterScene()
	{
		// nothing
	}

	void Stage1BossEnterScene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		Animator* at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		SetSceneTarget(player);
	}

	void Stage1BossEnterScene::Update()
	{
		Scene::Update();
		CameraMove();
	}

	void Stage1BossEnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1BossEnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1BossEnterScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
	}

	void Stage1BossEnterScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1BossEnterScene::CameraMove()
	{
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - playerPos.y);

		if (playerPos.y < CAMERA_CONTROL_POS_Y)
		{
			math::Vector2 anchorPosX = math::Vector2(0.0f, 0.0f);
			Camera::SetLimitDistance(anchorPosX, GetCameraHeightLimit());
		}
		else
		{
			Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());
		}
	}

	void Stage1BossEnterScene::MakeWorld()
	{
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Boss_Enter"));				// BackGround 객체의 texture 설정
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

	void Stage1BossEnterScene::MakeFloor()
	{
		// Floor
		Floor* floor_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR1_X, Window_Y / 2 + FLOOR1_Y));
		floor_1->GetComponent<Collider>()->SetSize(math::Vector2(430.0f, FLOOR_HEIGHT));

		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR2_X, Window_Y / 2 + FLOOR2_Y));
		floor_2->GetComponent<Collider>()->SetSize(math::Vector2(630.0f, FLOOR_HEIGHT));

		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR3_X, Window_Y / 2 + FLOOR3_Y));
		floor_3->GetComponent<Collider>()->SetSize(math::Vector2(304.0f, FLOOR_HEIGHT));

		Floor* floor_4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR4_X, Window_Y / 2 + FLOOR4_Y));
		floor_4->GetComponent<Collider>()->SetSize(math::Vector2(170.0f, FLOOR_HEIGHT));

		Floor* floor_5 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_5->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR5_X, Window_Y / 2 + FLOOR5_Y));
		floor_5->GetComponent<Collider>()->SetSize(math::Vector2(45.0f, FLOOR_HEIGHT));

		Floor* floor_6 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_6->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR6_X, Window_Y / 2 + FLOOR6_Y));
		floor_6->GetComponent<Collider>()->SetSize(math::Vector2(170.0f, FLOOR_HEIGHT));

		Floor* floor_7 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_7->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR7_X, Window_Y / 2 + FLOOR7_Y));
		floor_7->GetComponent<Collider>()->SetSize(math::Vector2(57.0f, FLOOR_HEIGHT));

		Floor* floor_8 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_8->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 390.0f));
		floor_8->GetComponent<Collider>()->SetSize(math::Vector2(835.0f, FLOOR_HEIGHT));

		Floor* floor_9_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_9_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 507, Window_Y / 2 - 540.0f));
		floor_9_1->GetComponent<Collider>()->SetSize(math::Vector2(180.0f, FLOOR_HEIGHT));

		Floor* floor_9_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_9_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 507, Window_Y / 2 - 540.0f));
		floor_9_2->GetComponent<Collider>()->SetSize(math::Vector2(180.0f, FLOOR_HEIGHT));
	}

	void Stage1BossEnterScene::MakeWall()
	{
		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 390.0f, Window_Y / 2 + 785.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 195.0f));

		Wall* wall_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 240.0f, Window_Y / 2 + 615.0f));
		wall_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 140.0f));

		Wall* wall_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 550.0f, Window_Y / 2 + 300.0f));
		wall_3->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 470.0f));

		Wall* wall_4 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 85.0f, Window_Y / 2 + 405.0f));
		wall_4->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 110.0f));

		Wall* wall_5 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_5->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 90.0f, Window_Y / 2 + 260.0f));
		wall_5->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 160.0f));

		Wall* wall_6 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_6->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 140.0f, Window_Y / 2 + 80.0f));
		wall_6->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 180.0f));

		Wall* wall_7 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_7->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 320.0f, Window_Y / 2 - 120.0f));
		wall_7->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 200.0f));

		Wall* wall_8 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_8->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 20.0f, Window_Y / 2 - 140.0f));
		wall_8->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 95.0f));

		Wall* wall_9 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_9->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 86.0f, Window_Y / 2 - 290.0f));
		wall_9->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 200.0f));

		Wall* wall_10 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_10->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 123.0f, Window_Y / 2 - 350.0f));
		wall_10->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 80.0f));

		Wall* wall_11_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_11_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 510.0f, Window_Y / 2 + 390.0f));
		wall_11_1->GetComponent<Collider>()->SetSize(math::Vector2(620.0f, 2.0f));

		Wall* wall_11_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_11_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 205.0f, Window_Y / 2 + 425.0f));
		wall_11_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 70.0f));

		Wall* wall_11_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_11_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 60.0f, Window_Y / 2 + 460.0f));
		wall_11_3->GetComponent<Collider>()->SetSize(math::Vector2(290.0f, 2.0f));

		Wall* wall_12_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_12_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 420.0f, Window_Y / 2 - 463.0f));
		wall_12_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 150.0f));

		Wall* wall_12_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_12_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 420.0f, Window_Y / 2 - 463.0f));
		wall_12_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 150.0f));

		Wall* wall_13_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_13_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 600.0f, Window_Y / 2 - 695.0f));
		wall_13_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 305.0f));

		Wall* wall_13_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_13_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 600.0f, Window_Y / 2 - 695.0f));
		wall_13_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 305.0f));
	}

	void Stage1BossEnterScene::MakeDoor()
	{
		// Door
		Door* door = Object::Instantiate<Door>(enums::eLayerType::Door);
		door->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 570.0f));
		door->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_Boss", true);;
		door->GetComponent<Collider>()->SetSize(math::Vector2(100.0f, 250.0f));
	}
}
