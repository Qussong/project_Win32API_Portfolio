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
		// 1) BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Boss_Enter"));				// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		Animator* at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		// Floor_1
		Floor* floor_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR1_X, Window_Y / 2 + FLOOR1_Y));
		Collider* col_1 = floor_1->GetComponent<Collider>();
		col_1->SetSize(math::Vector2(430.0f, FLOOR_HEIGHT));

		// Floor_2
		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR2_X, Window_Y / 2 + FLOOR2_Y));
		Collider* col_2 = floor_2->GetComponent<Collider>();
		col_2->SetSize(math::Vector2(630.0f, FLOOR_HEIGHT));

		// Floor_3
		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR3_X, Window_Y / 2 + FLOOR3_Y));
		Collider* col_3 = floor_3->GetComponent<Collider>();
		col_3->SetSize(math::Vector2(304.0f, FLOOR_HEIGHT));

		// Floor_4
		Floor* floor_4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR4_X, Window_Y / 2 + FLOOR4_Y));
		Collider* col_4 = floor_4->GetComponent<Collider>();
		col_4->SetSize(math::Vector2(170.0f, FLOOR_HEIGHT));

		// Floor_5
		Floor* floor_5 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_5->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR5_X, Window_Y / 2 + FLOOR5_Y));
		Collider* col_5 = floor_5->GetComponent<Collider>();
		col_5->SetSize(math::Vector2(45.0f, FLOOR_HEIGHT));

		// Floor_6
		Floor* floor_6 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_6->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR6_X, Window_Y / 2 + FLOOR6_Y));
		Collider* col_6 = floor_6->GetComponent<Collider>();
		col_6->SetSize(math::Vector2(170.0f, FLOOR_HEIGHT));

		// Floor_7
		Floor* floor_7 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_7->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + FLOOR7_X, Window_Y / 2 + FLOOR7_Y));
		Collider* col_7 = floor_7->GetComponent<Collider>();
		col_7->SetSize(math::Vector2(57.0f, FLOOR_HEIGHT));

		SetSceneTarget(player);
	}

	void Stage1BossEnterScene::Update()
	{
		Scene::Update();
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
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
	}

	void Stage1BossEnterScene::SceneOut()
	{

	}
}
