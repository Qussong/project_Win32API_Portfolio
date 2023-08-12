#include "vanLoadingScene.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanObject.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"


namespace van
{
	LoadingScene::LoadingScene()
	{
		// nothing
	}

	LoadingScene::~LoadingScene()
	{
		// nothing
	}

	void LoadingScene::Init()
	{
		LoadTexture();
		Animator* animator = nullptr;

		// Black
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Black_BackGround"));
		bgsr->SetScale(math::Vector2::One);
		bgsr->SetAffectCamera(false);
		// 해당 Scene에서의 카메라 최대 이동거리 설정
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Loading Skul
		BackGround* loadingSkul = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		loadingSkul->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 550, Window_Y / 2 + 250));
		animator = loadingSkul->GetComponent<Animator>();
		animator->CreateAnimation(L"Skul_Loading", ResourceManager::Find<Texture>(L"Skul_Loading"), math::Vector2::Zero, math::Vector2(47.0f, 41.0f), 8);
		animator->SetScale(math::Vector2(2.0f,2.0f));
		animator->PlayAnimation(L"Skul_Loading", true);
		animator->SetAffectedCamera(false);

		SetSceneTarget(nullptr);
	}

	void LoadingScene::Update()
	{
		Scene::Update();
	}

	void LoadingScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ LoadingScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void LoadingScene::SceneIN()
	{
		//  카메라 최대 이동 가능 거리 설정
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라로 해당 Scene의 Target 비추기
		Camera::SetTarget(GetSceneTarget());
	}

	void LoadingScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
	}

	void LoadingScene::LoadTexture()	// 첨조할 이미지 모두 여기서 로드
	{
		Texture* img = new Texture();
		// ResourceManager::Load<Texture>(L"", L"");

		// BG_Test_Scene
		ResourceManager::Load<Texture>(L"BG_Test", L"..\\MyResources\\skul\\0_BG\\0_Test\\Background_Grid.bmp");

		// BG_Title_Scene
		ResourceManager::Load<Texture>(L"BG_Title_Art", L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Art.bmp");
		ResourceManager::Load<Texture>(L"BG_Title_Logo", L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Logo.png");

		// BG_Loading_Scene
		ResourceManager::Load<Texture>(L"BG_Black_BackGround", L"..\\MyResources\\skul\\0_BG\\1_Loading\\Black.bmp");
		ResourceManager::Load<Texture>(L"Skul_Loading", L"..\\MyResources\\skul\\0_BG\\1_Loading\\Skul_Loading.bmp");

		// BG_Home_Scene
		ResourceManager::Load<Texture>(L"BG_Home_Scene", L"..\\MyResources\\skul\\0_BG\\2_Home\\Home.bmp");

		// BG_Stage1_Enter_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Enter", L"..\\MyResources\\skul\\0_BG\\3_Stage1_Enter\\Stage1_Enter.bmp");

		// BG_Stage1_Monster_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Monster", L"..\\MyResources\\skul\\0_BG\\4_Stage1_Monster\\Stage1_Monster_24.bmp");

		// BG_Stage1_Boss_Enter_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Boss_Enter", L"..\\MyResources\\skul\\0_BG\\5_Stage1_Boss_Enter\\Stage1_Boss_Enter.bmp");

		// BG_Stage1_Boss_Scene
		

		// BG_Stage2_Enter_Scene
		

		// BG_Stage2_Monster_Scene
		

		// BG_Stage2_Boss_Enter_Scene
		

		// BG_Stage2_Boss_Scene


		// BG_EndingScene


		// Door1
		ResourceManager::Load<Texture>(L"Stage1_Door_1", L"..\\MyResources\\skul\\5_Door_Stage1\\Door_1\\Stage1_Door_1.bmp");

		// Door2
		ResourceManager::Load<Texture>(L"Stage1_Door_2", L"..\\MyResources\\skul\\5_Door_Stage1\\Door_2\\Stage1_Door_2.bmp");

		// Player
		ResourceManager::Load<Texture>(L"Idle_Weapon_L", L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_L\\Idle_Weapon_L.bmp");
		ResourceManager::Load<Texture>(L"Idle_Weapon_R", L"..\\MyResources\\skul\\11_Skul\\Idle_Weapon_R\\Idle_Weapon_R.bmp");
		ResourceManager::Load<Texture>(L"Walk_Weapon_L", L"..\\MyResources\\skul\\11_Skul\\Walk_Weapon_L\\Walk_Weapon_L.bmp");
		ResourceManager::Load<Texture>(L"Walk_Weapon_R", L"..\\MyResources\\skul\\11_Skul\\Walk_Weapon_R\\Walk_Weapon_R.bmp");
		ResourceManager::Load<Texture>(L"Attack_A_L", L"..\\MyResources\\skul\\11_Skul\\Attack_A_L\\Attack_A_L.bmp");
		ResourceManager::Load<Texture>(L"Attack_A_R", L"..\\MyResources\\skul\\11_Skul\\Attack_A_R\\Attack_A_R.bmp");
		ResourceManager::Load<Texture>(L"Attack_B_L", L"..\\MyResources\\skul\\11_Skul\\Attack_B_L\\Attack_B_L.bmp");
		ResourceManager::Load<Texture>(L"Attack_B_R", L"..\\MyResources\\skul\\11_Skul\\Attack_B_R\\Attack_B_R.bmp");
		ResourceManager::Load<Texture>(L"Jump_L", L"..\\MyResources\\skul\\11_Skul\\Jump_L\\Jump_L.bmp");
		ResourceManager::Load<Texture>(L"Jump_R", L"..\\MyResources\\skul\\11_Skul\\Jump_R\\Jump_R.bmp");
		ResourceManager::Load<Texture>(L"Jump_Attack_L", L"..\\MyResources\\skul\\11_Skul\\Jump_Attack_L\\Jump_Attack_L.bmp");
		ResourceManager::Load<Texture>(L"Jump_Attack_R", L"..\\MyResources\\skul\\11_Skul\\Jump_Attack_R\\Jump_Attack_R.bmp");
		ResourceManager::Load<Texture>(L"Dash_L", L"..\\MyResources\\skul\\11_Skul\\Dash_L\\Dash_L.bmp");
		ResourceManager::Load<Texture>(L"Dash_R", L"..\\MyResources\\skul\\11_Skul\\Dash_R\\Dash_R.bmp");
		ResourceManager::Load<Texture>(L"Fall_L", L"..\\MyResources\\skul\\11_Skul\\Fall_L\\Fall_L.bmp");
		ResourceManager::Load<Texture>(L"Fall_R", L"..\\MyResources\\skul\\11_Skul\\Fall_R\\Fall_R.bmp");
		ResourceManager::Load<Texture>(L"Fall_Repeat_L", L"..\\MyResources\\skul\\11_Skul\\Fall_Repeat_L\\Fall_Repeat_L.bmp");
		ResourceManager::Load<Texture>(L"Fall_Repeat_R", L"..\\MyResources\\skul\\11_Skul\\Fall_Repeat_R\\Fall_Repeat_R.bmp");

		// [ NPC ]
		// TiedSkul
		ResourceManager::Load<Texture>(L"TiedSkul_Idle", L"..\\MyResources\\skul\\1_NPC\\TiedSkul\\TiedSkul_Idle.bmp");
		// DeathKnight
		ResourceManager::Load<Texture>(L"DeathKnight_Idle_Castle", L"..\\MyResources\\skul\\1_NPC\\DeathKnight\\DeathKnight_Idle_Castle.bmp");
		// Witch
		ResourceManager::Load<Texture>(L"Witch_Idle_Castle", L"..\\MyResources\\skul\\1_NPC\\Witch\\Witch_Idle_Castle.bmp");
		// FoxHunter
		ResourceManager::Load<Texture>(L"FoxHunter_Idle_Castle", L"..\\MyResources\\skul\\1_NPC\\FoxHunter\\FoxHunter_Idle_Castle.bmp");
		// Orge
		ResourceManager::Load<Texture>(L"Orge_Idle_Castle", L"..\\MyResources\\skul\\1_NPC\\Orge\\Orge_Idle_Castle.bmp");
		// Druid
		ResourceManager::Load<Texture>(L"Druid_Idle_Castle", L"..\\MyResources\\skul\\1_NPC\\Druid\\Druid_Idle_Castle.bmp");

		// [ Monster ]
		// Carleon Recruit
		ResourceManager::Load<Texture>(L"CarleonRecruit_Idle_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\1_Idle_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Idle_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\1_Idle_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Walk_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\2_Walk_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Walk_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\2_Walk_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_Ready_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\3_AttackReady_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_Ready_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\3_AttackReady_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\4_Attack_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\4_Attack_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Hit_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\5_Hit_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Hit_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\5_Hit_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Dead_L", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\6_Dead_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Dead_R", L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\6_Dead_R.bmp");
	}
}