#include "vanTestScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanCarleonRecruit.h"
#include "vanFloor.h"
#include "vanCollider.h"
#include "vanCarleonRecruit.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"


namespace van
{
	TestScene::TestScene()
	{
		// nothing
	}

	TestScene::~TestScene()
	{
		// nothing
	}

	void TestScene::Init()
	{	
		// BackGround 객체
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Test"));
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

		// Carleon Recruit
		CarleonRecruit* carleon = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
		carleon->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 400.0f, Window_Y / 2));
		at = carleon->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		// Floor 객체 
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(Window_X, FLOOR_HEIGHT));

		// 해당 씬의 (카메라)Target 설정
		SetSceneTarget(player);
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ TestScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void TestScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);
	}

	void TestScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}
}
