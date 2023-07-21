#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"
#include "vanBackGround.h"

#include "vanSpearman.h"
#include "vanCarleonRecruit.h"

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
	// CarleonRecruit
	// Idle
	CarleonRecruit* recruit_1 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
	recruit_1->Init();
	recruit_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 100));
	Animator* animator = recruit_1->GetComponent<Animator>();
	animator->PlayAnimation(L"Idle", true);
	animator->SetAffectedCamera(false);
	// Walk
	CarleonRecruit* recruit_2 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
	recruit_2->Init();
	recruit_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
	animator = recruit_2->GetComponent<Animator>();
	animator->PlayAnimation(L"Walk", true);
	animator->SetAffectedCamera(false);
	// Attack
	CarleonRecruit* recruit_3 = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
	recruit_3->Init();
	recruit_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 100));
	animator = recruit_3->GetComponent<Animator>();
	animator->PlayAnimation(L"Attack", true);
	animator->SetAffectedCamera(false);

	// Spearman
	// Idle
	Spearman* spearman = Object::Instantiate<Spearman>(enums::eLayerType::Monster);
	spearman->Init();
	spearman->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 100, Window_Y / 2 - 150));
	animator = spearman->GetComponent<Animator>();
	animator->PlayAnimation(L"Idle", true);
	animator->SetAffectedCamera(false);
	// Walk
	spearman = Object::Instantiate<Spearman>(enums::eLayerType::Monster);
	spearman->Init();
	spearman->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 100, Window_Y / 2 - 50));
	animator = spearman->GetComponent<Animator>();
	animator->PlayAnimation(L"Walk", true);
	animator->SetAffectedCamera(false);
	// Attack
	spearman = Object::Instantiate<Spearman>(enums::eLayerType::Monster);
	spearman->Init();
	spearman->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 100, Window_Y / 2 + 50));
	animator = spearman->GetComponent<Animator>();
	animator->PlayAnimation(L"Attack", true);
	animator->SetAffectedCamera(false);
	// Attack_2
	spearman = Object::Instantiate<Spearman>(enums::eLayerType::Monster);
	spearman->Init();
	spearman->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 100, Window_Y / 2 + 150));
	animator = spearman->GetComponent<Animator>();
	animator->PlayAnimation(L"Attack_2", true);
	animator->SetAffectedCamera(false);
	

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

	// Scene ±¸ºÐ
	const wchar_t* str = L"[ StageScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}
