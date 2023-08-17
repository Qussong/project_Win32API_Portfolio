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
#define DOOR_X		300.0f
#define DOOR_Y		930.0f - 410.0f

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
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();					// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster_1"));		// BackGround 객체의 texture 설정
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
		door_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - DOOR_X, Window_Y / 2 + DOOR_Y));
		door_L->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_1", true);;
		// Door_R
		Door* door_R = Object::Instantiate<Door>(eLayerType::Door);
		door_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_X, Window_Y / 2 + DOOR_Y));
		door_R->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_2", true);

		// Floor_B1
		Floor* floorB1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1->GetComponent<Collider>()->SetSize(math::Vector2(1520.0f, FLOOR_HEIGHT));
		floorB1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_B1_Y));
		// Wall_B1_L
		Wall* wallB1_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wallB1_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - WALL_B1_X, Window_Y / 2 + WALL_B1_Y));
		wallB1_L->GetComponent<Collider>()->SetSize(math::Vector2(2, 220));
		// Wall_B1_R
		Wall* wallB1_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wallB1_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + WALL_B1_X, Window_Y / 2 + WALL_B1_Y));
		wallB1_R->GetComponent<Collider>()->SetSize(math::Vector2(2, 220));
		// Floor_1_L
		Floor* floor1_L = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_L->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, FLOOR_HEIGHT));
		floor1_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_1_X, Window_Y / 2 + FLOOR_1_Y));
		// Floor_1_R
		Floor* floor1_R = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_R->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, FLOOR_HEIGHT));
		floor1_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_1_X, Window_Y / 2 + FLOOR_1_Y));
		// Floor_2_L
		Floor* floor2_L = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_L->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, FLOOR_HEIGHT));
		floor2_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - FLOOR_2_X, Window_Y / 2 + FLOOR_2_Y));
		// Floor_2_R
		Floor* floor2_R = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_R->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, FLOOR_HEIGHT));
		floor2_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR_2_X, Window_Y / 2 + FLOOR_2_Y));
		// Floor_3
		Floor* floor3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Collider>()->SetSize(math::Vector2(1800.0f, FLOOR_HEIGHT));
		floor3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_3_Y));
		// Floor_4
		Floor* floor4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Collider>()->SetSize(math::Vector2(350.0f, FLOOR_HEIGHT));
		floor4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_4_Y));

		SetSceneTarget(player);
	}

	void Stage1Monster1Scene::Update()
	{
		Scene::Update();
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
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Floor, true);
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
}