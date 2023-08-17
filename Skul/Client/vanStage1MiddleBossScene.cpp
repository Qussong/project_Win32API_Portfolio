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
#define CAMERA_ANCHOR_X				330.0f
#define CAMERA_OFFSET_DOUBLESPEED	5

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
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Middle_Boss"));			// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		// Door_L
		Door* door_L = Object::Instantiate<Door>(eLayerType::Door);
		door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y));
		door_L->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_1", true);

		// Door_R
		Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
		door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X + DOOR_GAP, Window_Y / 2 + DOOR_Y));
		door_R->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_2", true);

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

		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 954.0f, Window_Y / 2 + 180.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));

		Wall* wall_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 395.0f, Window_Y / 2 + 180.0f));
		wall_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));

		SetSceneTarget(player);
	}

	void Stage1MiddleBossScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
		CameraMove();
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
			math::Vector2 anchorPosX = math::Vector2(-(Window_X / 2 - 350.0f), -(Window_X / 2 - 350.0f));
			math::Vector2 anchorPosY = math::Vector2(50.0f, 50.0f);
			Camera::SetLimitDistance(anchorPosX, anchorPosY);
		}
		else if ( playerPos.x > CAMERA_CONTROL_POS_X_2)
		{
			Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());
		}
	}
}