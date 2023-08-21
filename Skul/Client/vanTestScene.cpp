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
#include "vanWall.h"
#include "vanTrap.h"
#include "vanCatSeol.h"
#include "vanGold.h"
#include "vanEnt.h"
#include "vanManAtArms.h"
#include "vanSkull.h"
#include "vanRigidBody.h"
#include "vanGianticEnt.h"
#include "vanMage.h"

#define FLOOR_POS_Y			-2880.0f
#define FLOOR_UP_CONDITION	-10.0f

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
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 400.0f, Window_Y / 2 + FLOOR_UP_CONDITION));

		// Mage
		//Mage* mage = Object::Instantiate<Mage>(enums::eLayerType::Boos_Mage);
		//mage->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_UP_CONDITION));
		//mage->SetTartget(player);

		//	GianticEnt
		//GianticEnt* giantEnt = Object::Instantiate<GianticEnt>(enums::eLayerType::Monster);
		//giantEnt->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_UP_CONDITION));

		// Trap
		//Trap* trap = Object::Instantiate<Trap>(enums::eLayerType::Trap);
		//trap->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 400.0f , Window_Y / 2 - 20.0f));
		
		// Cat_Seol
		//CatSeol* catSeol = Object::Instantiate<CatSeol>(enums::eLayerType::NPC);
		//catSeol->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_UP_CONDITION));

		// Gold
		//for (int i = 0; i < 10; ++i)
		//{
		//	Gold* gold = Object::Instantiate<Gold>(enums::eLayerType::Drop);
		//	gold->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + (i*20), Window_Y / 2 + FLOOR_UP_CONDITION - 100.0f));
		//}

		// Carleon Recruit
		//CarleonRecruit* carleon = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
		//carleon->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 400.0f, Window_Y / 2 + FLOOR_UP_CONDITION));

		// Ent
		//Ent* ent = Object::Instantiate<Ent>(enums::eLayerType::Monster);
		//ent->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 200.0f, Window_Y / 2 + FLOOR_UP_CONDITION));

		// ManAtArms
		//ManAtArms* man = Object::Instantiate<ManAtArms>(enums::eLayerType::Monster);
		//man->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 100.0f, Window_Y / 2 + FLOOR_UP_CONDITION));
		
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
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Trap, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Trap, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Drop, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Boos_Mage, eLayerType::Floor, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::Boos_Mage, eLayerType::Wall, true);

	}

	void TestScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void TestScene::MakeWorld()
	{
		// BackGround 객체
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Test"));
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
		worldWall_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + size.x / 2 + 2.0f, Window_Y / 2));
	}

	void TestScene::MakeFloor()
	{
		// Floor 객체 
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		floor->GetComponent<Collider>()->SetSize(math::Vector2(Window_X, FLOOR_HEIGHT));
	}

	void TestScene::MakeWall()
	{
		// Wall객체
		//Wall* wall = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		//wall->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 50.0f));
		//wall->GetComponent<Collider>()->SetSize(math::Vector2(10, 100));
		//wall->SetFloorLimit(true);
	}

	void TestScene::MakeDoor()
	{
		// nothing
	}
}
