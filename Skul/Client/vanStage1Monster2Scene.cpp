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

// player
#define PLAYER_INIT_POS_Y	400
#define PLAYER_INIT_POS_X	-1180
// floor
// wall

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
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();					// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster_2"));		// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));

		// floor
		Floor* floor_B1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 511.0f, Window_Y / 2 + 565.0f));
		floor_B1_1->GetComponent<Collider>()->SetSize(math::Vector2(80.0f, 2.0f));

		Floor* floor_B1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 80.0f, Window_Y / 2 + 565.0f));
		floor_B1_2->GetComponent<Collider>()->SetSize(math::Vector2(80.0f, 2.0f));

		Floor* floor_B2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 250.0f, Window_Y / 2 + 615.0f));
		floor_B2->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));

		Floor* floor_1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 990.0f, Window_Y / 2 + 420.0f));
		floor_1_1->GetComponent<Collider>()->SetSize(math::Vector2(440.0f, 2.0f));

		Floor* floor_1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f, Window_Y / 2 + 420.0f));
		floor_1_2->GetComponent<Collider>()->SetSize(math::Vector2(640.0f, 2.0f));

		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 +  290.0f, Window_Y / 2 + 260.0f));
		floor_2->GetComponent<Collider>()->SetSize(math::Vector2(150.0f, 2.0f));

		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 262.0f, Window_Y / 2 + 60.0f));
		floor_3->GetComponent<Collider>()->SetSize(math::Vector2(500.0f, 2.0f));

		Floor* floor_4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 695.0f, Window_Y / 2 - 100.0f));
		floor_4->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));
		
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


		SetSceneTarget(player);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1Monster2Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
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
}