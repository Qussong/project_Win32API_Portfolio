#include "vanStage1BossScene.h"
#include "vanCamera.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanWall.h"
#include "vanFloor.h"
#include "vanYggdrasill.h"
#include "vanYggdrasillFrame.h"
#include "vanYggdrasillHpBar.h"

namespace van
{
	Stage1BossScene::Stage1BossScene()
	{
		// nothing
	}

	Stage1BossScene::~Stage1BossScene()
	{
		// nothing
	}

	void Stage1BossScene::Init()
	{
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		Animator* at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));

		SetSceneTarget(player);

		mYgg = Object::Instantiate<Yggdrasill>(enums::eLayerType::Yggdrasill);
		mYgg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
	}

	void Stage1BossScene::Update()
	{
		Scene::Update();
		//CameraMove();
		BossTurn();
	}

	void Stage1BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1BossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1BossScene::SceneIN()
	{
		// 배경 사운드
		SetBgSound(ResourceManager::Load<Sound>(L"Chapter1_Boss", L"..\\MyResources\\skul\\Sound\\Chapter1_Boss.wav"));
		GetBgSound()->Play(true);

		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::FrontFloor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Monster, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Yggdrasill_Head, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Attack, eLayerType::Yggdrasill_Hand, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::Drop, eLayerType::Floor, true);
	}

	void Stage1BossScene::SceneOut()
	{
		// 배경 사운드 종료
		GetBgSound()->Stop(true);
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void Stage1BossScene::CameraMove()
	{
		// 보스 잡으면 옆에 있는 문으로 갈 수 있도록 카메라 이동
	}

	void Stage1BossScene::MakeWorld()
	{
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::FrontFloor);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Boss_Tile"));			// BackGround 객체의 texture 설정
		bgsr->SetScale(math::Vector2(0.5f, 0.5f));
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));
		
		// [ World_Wall ]
		Texture* image = bgsr->GetTexture();
		math::Vector2 scale = bgsr->GetScale();	// 화면에 그려지는 배경의 scale 값도 고려
		math::Vector2 size = (image->GetSize() * scale);
		// Left
		Wall* worldWall_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_L->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - size.x / 2 - 1.0f, Window_Y / 2));
		// Right
		Wall* worldWall_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_R->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + size.x / 2 + 1.0f, Window_Y / 2));
	}

	void Stage1BossScene::MakeFloor()
	{
		// nothing
		Floor* floor1 = Object::Instantiate<Floor>(enums::eLayerType::FrontFloor);
		floor1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 300.0f));
		floor1->GetComponent<Collider>()->SetSize(math::Vector2(1440.0f, 100.0f));
	}

	void Stage1BossScene::MakeWall()
	{
		// nothing
	}

	void Stage1BossScene::MakeDoor()
	{
		// nothing
	}

	void Stage1BossScene::BossTurn()
	{
		// Phase1 BossHp Frame
		if (mbPhase1 == true
			&& mbPhase2 == true)
		{
			YggdrasillFrame* yggFrame = Object::Instantiate<YggdrasillFrame>(enums::eLayerType::UI);
			YggdrasillHpBar* mMageHpBar = Object::Instantiate<YggdrasillHpBar>(enums::eLayerType::UI);
			mMageHpBar->SetMage(mYgg);

			mbPhase1 = false;
		}

		// Phase2 BossHp Frame
		if (mbPhase1 == false
			&& mbPhase2 == true)
		{

			mbPhase2 = false;
		}
	}
}
