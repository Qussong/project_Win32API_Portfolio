#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"

#include "vanBackGround.h"

van::StageScene::StageScene()
{
	// nothing
}

van::StageScene::~StageScene()
{
	// nothing
}

void van::StageScene::Init()
{
	// 병사 1
	Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	monster->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 150));
	Animator* at = monster->AddComponent<Animator>();
	// Idle
	Texture* texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Idle"
		, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\Idle.bmp");
	at->CreateAnimation(L"CarleonRecruit_Idle"
		, texture
		, math::Vector2(0.0f, 0.0f)
		, math::Vector2(34.0f, 57.0f)
		, 6);
	// Walk
	texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Walk"
		, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\Walk.bmp");
	at->CreateAnimation(L"CarleonRecruit_Walk"
		, texture
		, math::Vector2(0.0f, 0.0f)
		, math::Vector2(48.0f, 50.0f)
		, 5);
	// Attack
	texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Attack"
		, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\Attack.bmp");
	at->CreateAnimation(L"CarleonRecruit_Attack"
		, texture
		, math::Vector2(0.0f, 0.0f)
		, math::Vector2(58.0f, 64.0f)
		, 5);
	at->PlayAnimation(L"CarleonRecruit_Idle", true);
	at->SetScale(math::Vector2(2.0f, 2.0f));
	at->SetAffectedCamera(false);

	// 병사2_Walk
	monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	monster->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
	at = monster->AddComponent<Animator>();
	texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Walk"
		, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\Walk.bmp");
	at->CreateAnimation(L"CarleonRecruit_Walk"
		, texture
		, math::Vector2(0.0f, 0.0f)
		, math::Vector2(48.0f, 50.0f)
		, 5);
	at->PlayAnimation(L"CarleonRecruit_Walk", true);
	at->SetScale(math::Vector2(2.0f, 2.0f));
	at->SetAffectedCamera(false);

	// 병사 3_Attack
	monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	monster->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 150));
	at = monster->AddComponent<Animator>();
	texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Attack"
		, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\Attack.bmp");
	at->CreateAnimation(L"CarleonRecruit_Attack"
		, texture
		, math::Vector2(0.0f, 0.0f)
		, math::Vector2(58.0f, 64.0f)
		, 5);
	at->PlayAnimation(L"CarleonRecruit_Attack", true);
	at->SetScale(math::Vector2(2.0f, 2.0f));
	at->SetAffectedCamera(false);

	SetTarget(nullptr);
	Camera::SetTarget(GetTarget());
}

void van::StageScene::Update()
{
	Camera::SetTarget(GetTarget());
	Scene::Update();
}

void van::StageScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	// Scene 구분
	const wchar_t* str = L"[ StageScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}
