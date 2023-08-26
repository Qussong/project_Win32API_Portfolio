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

		// [ UI ]
		//\MyResources\skul\UI
		ResourceManager::Load<Texture>(L"UI_Player_Frame", L"..\\MyResources\\skul\\UI\\UI_Player_Frame.png");
		ResourceManager::Load<Texture>(L"UI_MiddleBoss_Frame", L"..\\MyResources\\skul\\UI\\UI_MiddleBoss_Frame.png");

		// [ BackGround ]
		// BG_Test_Scene
		ResourceManager::Load<Texture>(L"BG_Test", L"..\\MyResources\\skul\\BG\\0_Test\\Background_Grid.bmp");
		// BG_Title_Scene
		ResourceManager::Load<Texture>(L"BG_Title_Art", L"..\\MyResources\\skul\\BG\\0_Title\\DarkMirror_Title_Art.bmp");
		ResourceManager::Load<Texture>(L"BG_Title_Logo", L"..\\MyResources\\skul\\BG\\0_Title\\DarkMirror_Title_Logo.png");
		// BG_Loading_Scene
		ResourceManager::Load<Texture>(L"BG_Black_BackGround", L"..\\MyResources\\skul\\BG\\1_Loading\\Black.bmp");
		ResourceManager::Load<Texture>(L"Skul_Loading", L"..\\MyResources\\skul\\BG\\1_Loading\\Skul_Loading.bmp");
		// BG_Home_Scene
		ResourceManager::Load<Texture>(L"BG_Home_Scene", L"..\\MyResources\\skul\\BG\\2_Home\\Home.png");
		// BG_Stage1_Enter_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Enter", L"..\\MyResources\\skul\\BG\\3_Stage1_Enter\\Stage1_Enter.png");
		// BG_Stage1_Monster_1_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Monster_1", L"..\\MyResources\\skul\\BG\\4_Stage1_Monster_1\\Stage1_Monster_1.png");
		// BG_Stage1_Monster_2_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Monster_2", L"..\\MyResources\\skul\\BG\\5_Stage1_Monster_2\\Stage1_Monster_2.png");
		// BG_Stage1_Middle_Boss_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Middle_Boss", L"..\\MyResources\\skul\\BG\\6_Stage1_Middle_Boss\\Stage1_Middle_Boss.png");
		// BG_Stage1_Boss_Enter_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Boss_Enter", L"..\\MyResources\\skul\\BG\\7_Stage1_Boss_Enter\\Stage1_Boss_Enter.png");
		// BG_Stage1_Boss_Scene
		ResourceManager::Load<Texture>(L"BG_Stage1_Boss_Tile", L"..\\MyResources\\skul\\BG\\8_Stage1_Boss\\Stage1_Boss_Tile.png");
		// BG_Market_Scene
		
		// BG_EndingScene


		// [ Door]
		// Door1
		ResourceManager::Load<Texture>(L"Stage1_Door_1", L"..\\MyResources\\skul\\Door_Stage1\\Door_1\\Stage1_Door_1.bmp");
		// Door2
		ResourceManager::Load<Texture>(L"Stage1_Door_2", L"..\\MyResources\\skul\\Door_Stage1\\Door_2\\Stage1_Door_2.bmp");
		// Door3
		ResourceManager::Load<Texture>(L"Stage1_Door_3", L"..\\MyResources\\skul\\Door_Stage1\\Door_3\\Stage1_Door_3.bmp");
		// Door_Market
		ResourceManager::Load<Texture>(L"Stage1_Door_Market", L"..\\MyResources\\skul\\Door_Stage1\\Door_Market\\Stage1_Door_Market.bmp");
		// Door_Middle_Boss
		ResourceManager::Load<Texture>(L"Stage1_Door_Middle_Boss", L"..\\MyResources\\skul\\Door_Stage1\\Door_Middle_Boss\\Stage1_Middle_Boss.bmp");
		// Door_Enter_Boss
		ResourceManager::Load<Texture>(L"Stage1_Door_Enter_Boss", L"..\\MyResources\\skul\\Door_Stage1\\Door_Enter_Boss\\Stage1_Enter_Boss.bmp");
		// Door_Boss
		ResourceManager::Load<Texture>(L"Stage1_Door_Boss", L"..\\MyResources\\skul\\Door_Stage1\\Door_Boss\\Stage1_Boss.bmp");
		// Door_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_0_DeActive.bmp");
		// Door1_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_1_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_1_DeActive.bmp");
		// Door2_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_2_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_2_DeActive.bmp");
		// Door3_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_3_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_3_DeActive.bmp");
		// Door_Market_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_Market_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_Market_DeActive.bmp");
		// Door_Middle_Boss_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_Middle_Boss_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_Middle_Boss_DeActive.bmp");
		// Door_Boss_DeActive
		ResourceManager::Load<Texture>(L"Stage1_Door_Boss_DeActive", L"..\\MyResources\\skul\\Door_Stage1\\Door_Boss_DeActive.bmp");
		
		// [ Player ]
		ResourceManager::Load<Texture>(L"Idle_Weapon_L", L"..\\MyResources\\skul\\Basic_Skul\\Idle_Weapon_L\\Idle_Weapon_L.bmp");
		ResourceManager::Load<Texture>(L"Idle_Weapon_R", L"..\\MyResources\\skul\\Basic_Skul\\Idle_Weapon_R\\Idle_Weapon_R.bmp");
		ResourceManager::Load<Texture>(L"Walk_Weapon_L", L"..\\MyResources\\skul\\Basic_Skul\\Walk_Weapon_L\\Walk_Weapon_L.bmp");
		ResourceManager::Load<Texture>(L"Walk_Weapon_R", L"..\\MyResources\\skul\\Basic_Skul\\Walk_Weapon_R\\Walk_Weapon_R.bmp");
		ResourceManager::Load<Texture>(L"Attack_A_L", L"..\\MyResources\\skul\\Basic_Skul\\Attack_A_L\\Attack_A_L.bmp");
		ResourceManager::Load<Texture>(L"Attack_A_R", L"..\\MyResources\\skul\\Basic_Skul\\Attack_A_R\\Attack_A_R.bmp");
		ResourceManager::Load<Texture>(L"Attack_B_L", L"..\\MyResources\\skul\\Basic_Skul\\Attack_B_L\\Attack_B_L.bmp");
		ResourceManager::Load<Texture>(L"Attack_B_R", L"..\\MyResources\\skul\\Basic_Skul\\Attack_B_R\\Attack_B_R.bmp");
		ResourceManager::Load<Texture>(L"Jump_L", L"..\\MyResources\\skul\\Basic_Skul\\Jump_L\\Jump_L.bmp");
		ResourceManager::Load<Texture>(L"Jump_R", L"..\\MyResources\\skul\\Basic_Skul\\Jump_R\\Jump_R.bmp");
		ResourceManager::Load<Texture>(L"Jump_Attack_L", L"..\\MyResources\\skul\\Basic_Skul\\Jump_Attack_L\\Jump_Attack_L.bmp");
		ResourceManager::Load<Texture>(L"Jump_Attack_R", L"..\\MyResources\\skul\\Basic_Skul\\Jump_Attack_R\\Jump_Attack_R.bmp");
		ResourceManager::Load<Texture>(L"Dash_L", L"..\\MyResources\\skul\\Basic_Skul\\Dash_L\\Dash_L.bmp");
		ResourceManager::Load<Texture>(L"Dash_R", L"..\\MyResources\\skul\\Basic_Skul\\Dash_R\\Dash_R.bmp");
		ResourceManager::Load<Texture>(L"Fall_L", L"..\\MyResources\\skul\\Basic_Skul\\Fall_L\\Fall_L.bmp");
		ResourceManager::Load<Texture>(L"Fall_R", L"..\\MyResources\\skul\\Basic_Skul\\Fall_R\\Fall_R.bmp");
		ResourceManager::Load<Texture>(L"Fall_Repeat_L", L"..\\MyResources\\skul\\Basic_Skul\\Fall_Repeat_L\\Fall_Repeat_L.bmp");
		ResourceManager::Load<Texture>(L"Fall_Repeat_R", L"..\\MyResources\\skul\\Basic_Skul\\Fall_Repeat_R\\Fall_Repeat_R.bmp");
		ResourceManager::Load<Texture>(L"Head", L"..\\MyResources\\skul\\Basic_Skul\\Head\\Skul.bmp");

		// [ NPC ]
		// TiedSkul
		ResourceManager::Load<Texture>(L"TiedSkul_Idle", L"..\\MyResources\\skul\\NPC\\TiedSkul\\TiedSkul_Idle.bmp");
		// DeathKnight
		ResourceManager::Load<Texture>(L"DeathKnight_Idle_Castle", L"..\\MyResources\\skul\\NPC\\DeathKnight\\DeathKnight_Idle_Castle.bmp");
		// Witch
		ResourceManager::Load<Texture>(L"Witch_Idle_Castle", L"..\\MyResources\\skul\\NPC\\Witch\\Witch_Idle_Castle.bmp");
		// FoxHunter
		ResourceManager::Load<Texture>(L"FoxHunter_Idle_Castle", L"..\\MyResources\\skul\\NPC\\FoxHunter\\FoxHunter_Idle_Castle.bmp");
		// Orge
		ResourceManager::Load<Texture>(L"Orge_Idle_Castle", L"..\\MyResources\\skul\\NPC\\Orge\\Orge_Idle_Castle.bmp");
		// Druid
		ResourceManager::Load<Texture>(L"Druid_Idle_Castle", L"..\\MyResources\\skul\\NPC\\Druid\\Druid_Idle_Castle.bmp");
		// Cat_Seol
		ResourceManager::Load<Texture>(L"Cat_Seol_Walk_L", L"..\\MyResources\\skul\\NPC\\Cat_Seol\\Cat_Seol_Walk_L.bmp");
		ResourceManager::Load<Texture>(L"Cat_Seol_Walk_R", L"..\\MyResources\\skul\\NPC\\Cat_Seol\\Cat_Seol_Walk_R.bmp");

		// [ Monster ]
		// Common
		ResourceManager::Load<Texture>(L"Monster_Generate", L"..\\MyResources\\skul\\Monster\\Common\\Enemy_Appearance.bmp");
		ResourceManager::Load<Texture>(L"Monster_Destroy", L"..\\MyResources\\skul\\Monster\\Common\\Enemy_Dead.bmp");
		ResourceManager::Load<Texture>(L"Gold", L"..\\MyResources\\skul\\Monster\\Common\\Gold.bmp");
		ResourceManager::Load<Texture>(L"Gold_Disappear", L"..\\MyResources\\skul\\Monster\\Common\\Gold_Disappear.bmp");
		ResourceManager::Load<Texture>(L"Gold_Idle", L"..\\MyResources\\skul\\Monster\\Common\\Gold_Idle.bmp");
		ResourceManager::Load<Texture>(L"Gold_Dead", L"..\\MyResources\\skul\\Monster\\Common\\Gold_Dead.png");
		// Gold Carleon Recruit
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Attack_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Attack_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_Ready_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\AttackReady_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Attack_Ready_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\AttackReady_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Dead_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Dead_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Dead_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Dead_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Hit_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Hit_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Hit_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Hit_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Idle_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Idle_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Idle_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Idle_R.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Walk_L", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Walk_L.bmp");
		ResourceManager::Load<Texture>(L"CarleonRecruit_Walk_R", L"..\\MyResources\\skul\\Monster\\GoldCarleonRecruit\\Walk_R.bmp");
		// Stage1_Trap
		ResourceManager::Load<Texture>(L"Stage1Trap", L"..\\MyResources\\skul\\Monster\\Stage1Trap\\Stage1Trap.bmp");
		// Ent
		ResourceManager::Load<Texture>(L"Ent_Attack_L", L"..\\MyResources\\skul\\Monster\\Ent\\Attack_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Attack_R", L"..\\MyResources\\skul\\Monster\\Ent\\Attack_R.bmp");
		ResourceManager::Load<Texture>(L"Ent_Attack_Ready_L", L"..\\MyResources\\skul\\Monster\\Ent\\AttackReady_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Attack_Ready_R", L"..\\MyResources\\skul\\Monster\\Ent\\AttackReady_R.bmp");
		ResourceManager::Load<Texture>(L"Ent_Dead_L", L"..\\MyResources\\skul\\Monster\\Ent\\Dead_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Dead_R", L"..\\MyResources\\skul\\Monster\\Ent\\Dead_R.bmp");
		ResourceManager::Load<Texture>(L"Ent_Hit_L", L"..\\MyResources\\skul\\Monster\\Ent\\Hit_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Hit_R", L"..\\MyResources\\skul\\Monster\\Ent\\Hit_R.bmp");
		ResourceManager::Load<Texture>(L"Ent_Idle_L", L"..\\MyResources\\skul\\Monster\\Ent\\Idle_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Idle_R", L"..\\MyResources\\skul\\Monster\\Ent\\Idle_R.bmp");
		ResourceManager::Load<Texture>(L"Ent_Walk_L", L"..\\MyResources\\skul\\Monster\\Ent\\Walk_L.bmp");
		ResourceManager::Load<Texture>(L"Ent_Walk_R", L"..\\MyResources\\skul\\Monster\\Ent\\Walk_R.bmp");
		// ManAtArms
		ResourceManager::Load<Texture>(L"ManAtArms_Attack_L", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Attack_L.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Attack_R", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Attack_R.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Attack_Ready_L", L"..\\MyResources\\skul\\Monster\\ManAtArms\\AttackReady_L.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Attack_Ready_R", L"..\\MyResources\\skul\\Monster\\ManAtArms\\AttackReady_R.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Idle_L", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Idle_L.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Idle_R", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Idle_R.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Walk_L", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Walk_L.bmp");
		ResourceManager::Load<Texture>(L"ManAtArms_Walk_R", L"..\\MyResources\\skul\\Monster\\ManAtArms\\Walk_R.bmp");
		// GianticEnt
		ResourceManager::Load<Texture>(L"GianticEnt_Idle", L"..\\MyResources\\skul\\Monster\\GianticEnt\\GianticEnt_Idle.bmp");
		ResourceManager::Load<Texture>(L"GianticEnt_Attack_Range_Ready", L"..\\MyResources\\skul\\Monster\\GianticEnt\\GianticEnt_Attack_Range_Ready.bmp");
		ResourceManager::Load<Texture>(L"GianticEnt_Attack_Range", L"..\\MyResources\\skul\\Monster\\GianticEnt\\GianticEnt_Attack_Range.bmp");
		ResourceManager::Load<Texture>(L"GianticEnt_Attack_Melee_Ready", L"..\\MyResources\\skul\\Monster\\GianticEnt\\GianticEnt_Attack_Melee_Ready.bmp");
		ResourceManager::Load<Texture>(L"GianticEnt_Attack_Melee", L"..\\MyResources\\skul\\Monster\\GianticEnt\\GianticEnt_Attack_Melee.bmp");
		// Yggdrasill
		ResourceManager::Load<Texture>(L"Yggdrasill_Head", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Head.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Chin", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\chin.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Body", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Body.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Idle_L", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Idle_L.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Idle_R", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Idle_R.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_FistSlam_L", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\FistSlam_Hand_L.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_FistSlam_R", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\FistSlam_Hand_R.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Swipe_L", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Swipe_L.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Swipe_R", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Swipe_R.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Swipe_End_L", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Swipe_End_L.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_Swipe_End_R", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_Swipe_End_R.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_MagicOrb_L", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_MagicOrb_L.png");
		ResourceManager::Load<Texture>(L"Yggdrasill_Hand_MagicOrb_R", L"..\\MyResources\\skul\\Monster\\Yggdrasill\\Hand_MagicOrb_R.png");

		// Mage
		ResourceManager::Load<Texture>(L"Mage_Intor_1", L"..\\MyResources\\skul\\Monster\\Mage\\Intro_1.bmp");
		ResourceManager::Load<Texture>(L"Mage_Intor_2", L"..\\MyResources\\skul\\Monster\\Mage\\Intro_2.bmp");
		ResourceManager::Load<Texture>(L"Mage_Idle_L", L"..\\MyResources\\skul\\Monster\\Mage\\Idle_L.bmp");
		ResourceManager::Load<Texture>(L"Mage_Idle_R", L"..\\MyResources\\skul\\Monster\\Mage\\Idle_R.bmp");
		ResourceManager::Load<Texture>(L"Mage_Walk_Front_L", L"..\\MyResources\\skul\\Monster\\Mage\\Walk_Front_L.bmp");
		ResourceManager::Load<Texture>(L"Mage_Walk_Front_R", L"..\\MyResources\\skul\\Monster\\Mage\\Walk_Front_R.bmp");
		ResourceManager::Load<Texture>(L"Mage_Walk_Back_L", L"..\\MyResources\\skul\\Monster\\Mage\\Walk_Back_L.bmp");
		ResourceManager::Load<Texture>(L"Mage_Walk_Back_R", L"..\\MyResources\\skul\\Monster\\Mage\\Walk_Back_R.bmp");
		ResourceManager::Load<Texture>(L"Mage_FireBall_Ready_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_FireBall_Ready_L.bmp");
		ResourceManager::Load<Texture>(L"Mage_FireBall_Ready_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_FireBall_Ready_R.bmp");
		ResourceManager::Load<Texture>(L"Mage_FireBall_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Fireball_L.bmp");
		ResourceManager::Load<Texture>(L"Mage_FireBall_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Fireball_R.bmp");
		ResourceManager::Load<Texture>(L"Mage_FireBall_Object_L", L"..\\MyResources\\skul\\Monster\\Mage\\FireBall_Object_L.png");
		ResourceManager::Load<Texture>(L"Mage_FireBall_Object_R", L"..\\MyResources\\skul\\Monster\\Mage\\FireBall_Object_R.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire_Ready_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Ready_RangeFire_L.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire_Ready_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Ready_RangeFire_R.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_RangeFire_L.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_RangeFire_R.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire_Sign", L"..\\MyResources\\skul\\Monster\\Mage\\RangeFire_Sign.png");
		ResourceManager::Load<Texture>(L"Mage_RangeFire", L"..\\MyResources\\skul\\Monster\\Mage\\RangeFire.bmp");

		ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Ready_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Ready_PhoenixLanding_L.png");
		ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Ready_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Ready_PhoenixLanding_R.png");
		ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Land_L", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_PhoenixLanding_Land_L.png");
		ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Land_R", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_PhoenixLanding_Land_R.png");

		//ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Ready_Effect", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Ready_Effect_PhoenixLanding.png");
		//ResourceManager::Load<Texture>(L"Mage_PhoenixRanding_Land_Effect", L"..\\MyResources\\skul\\Monster\\Mage\\Attack_Effect_PhoenixLanding_Land_.png");
	}
}