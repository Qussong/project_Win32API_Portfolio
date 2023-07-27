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
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"Black_BackGround"));
		bgsr->SetScale(math::Vector2::One);
		bgsr->SetAffectCamera(false);

		// Loading Skul
		BackGround* loadingSkul = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		loadingSkul->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 550, Window_Y / 2 + 250));
		animator = loadingSkul->GetComponent<Animator>();
		animator->CreateAnimation(L"Skul_Loading", ResourceManager::Find<Texture>(L"Skul_Loading"), math::Vector2::Zero, math::Vector2(47.0f, 41.0f), 8);
		animator->SetScale(math::Vector2(2.0f,2.0f));
		animator->PlayAnimation(L"Skul_Loading", true);
		animator->SetAffectedCamera(false);

		SetSceneTarget(nullptr);
		Camera::SetTarget(GetSceneTarget());
	}

	void LoadingScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
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

	
	void LoadingScene::LoadTexture()	// 첨조할 이미지 모두 여기서 로드
	{
		Texture* img = new Texture();

		// Title
		ResourceManager::Load<Texture>(L"Title_Art", L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Art.bmp");
		ResourceManager::Load<Texture>(L"Title_Logo", L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Logo.png");

		// Loading
		ResourceManager::Load<Texture>(L"Black_BackGround", L"..\\MyResources\\skul\\0_BG\\1_Loading\\Black.bmp");
		ResourceManager::Load<Texture>(L"Skul_Loading", L"..\\MyResources\\skul\\0_BG\\1_LoadingSkul\\Skul_Loading.bmp");


		// Home
		ResourceManager::Load<Texture>(L"BG_Home_1", L"..\\MyResources\\skul\\0_BG\\2_Home\\Home_BackGround.bmp");

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


		//
		//ResourceManager::Load<Texture>();
	}
}