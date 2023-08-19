#include "vanStage1EnterScene.h"
#include "vanTiedSkul.h"
#include "vanPlayer.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"
#include "vanAnimator.h"
#include "vanBackGround.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanRigidBody.h"
#include "vanFloor.h"
#include "vanDoor.h"
#include "vanWall.h"

// player
#define PLAYER_INIT_POS_Y	-1200.0f
// NPC
#define NPC_TIEDSKUL_POS_X	-500.0f
// floor
#define FLOOR_POS_Y			260.0f
#define DOOR_POS_Y			135.0f
#define DOOR_POS_X			-210.0f
#define FLOOR_UP_CONDITION	-10.0f

namespace van
{
	Stage1EnterScene::Stage1EnterScene()
	{
		// nothing
	}

	Stage1EnterScene::~Stage1EnterScene()
	{
		// nothing
	}

	void Stage1EnterScene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 , Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION + PLAYER_INIT_POS_Y));

		// Tied_Skul_NPC
		TiedSkul* tiedSkul = Object::Instantiate<TiedSkul>(enums::eLayerType::NPC);		
		tiedSkul->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + NPC_TIEDSKUL_POS_X, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		SetSceneTarget(player);
	}

	void Stage1EnterScene::Update()
	{
		Scene::Update();
		CameraMove();
	}

	void Stage1EnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1EnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1EnterScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
	}

	void Stage1EnterScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1EnterScene::CameraMove()
	{
		// nothing
	}

	void Stage1EnterScene::MakeWorld()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Enter"));				// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);														// 카메라 영향 여부설정
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

	void Stage1EnterScene::MakeFloor()
	{
		// Floor
		Floor* floor = Object::Instantiate<Floor>(eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(2200.0f, FLOOR_HEIGHT * 4));	// 너무 얇으면 떨어지는 속도 때문에 Floor에 안걸림
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_POS_Y));
	}

	void Stage1EnterScene::MakeWall()
	{
		// nothing
	}

	void Stage1EnterScene::MakeDoor()
	{
		// Door
		Door* door = Object::Instantiate<Door>(eLayerType::Door);
		door->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_POS_X, Window_Y / 2 + DOOR_POS_Y));
		Animator* at = door->GetComponent<Animator>();
		at->PlayAnimation(L"Stage1_Door_2", true);
	}
}