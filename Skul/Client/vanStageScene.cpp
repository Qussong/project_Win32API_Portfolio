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
	// Tree_Idle
	Monster* tree = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	Transform* tr = tree->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(100.0f, Window_Y/2 - 100));
	Animator* at = tree->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Tree_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Tree\\Idle");
	at->PlayAnimation(L"Tree_Idle", true);
	at->SetAffectedCamera(false);

	// Tree_Attack
	Monster* treeA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = treeA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(100.0f, Window_Y/2 + 100));
	at = treeA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Tree_Attack"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Tree\\Attack");
	at->PlayAnimation(L"Tree_Attack", true);
	at->SetAffectedCamera(false);
	
	// BigTree_Idle
	Monster* bigTree = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = bigTree->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(250.0f, Window_Y / 2 - 200));
	at = bigTree->AddComponent<Animator>();
	at->CreateAnimationFolder(L"BigTree_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\BigTree\\Idle");
	at->PlayAnimation(L"BigTree_Idle", true);
	at->SetAffectedCamera(false);

	// BigTree_Attack_A
	Monster* bigTreeA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = bigTreeA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(250.0f, Window_Y / 2));
	at = bigTreeA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"BigTree_Attack_A"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\BigTree\\Attack_A");
	at->PlayAnimation(L"BigTree_Attack_A", true);
	at->SetAffectedCamera(false);

	// BigTree_Attack_B
	Monster* bigTreeB = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = bigTreeB->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(250.0f, Window_Y / 2 + 200));
	at = bigTreeB->AddComponent<Animator>();
	at->CreateAnimationFolder(L"BigTree_Attack_B"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\BigTree\\Attack_B");
	at->PlayAnimation(L"BigTree_Attack_B", true);
	at->SetAffectedCamera(false);

	// Root_Idle
	Monster* root = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = root->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(400.0f, Window_Y / 2 - 100));
	at = root->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Root_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Root\\Idle");
	at->PlayAnimation(L"Root_Idle", true);
	at->SetAffectedCamera(false);

	// Root_Attack
	Monster* rootA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = rootA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(400.0f, Window_Y / 2 + 100));
	at = rootA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Root_Attack"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Root\\Attack");
	at->PlayAnimation(L"Root_Attack", true);
	at->SetAffectedCamera(false);

	// Knight_Idle
	Monster* knight = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = knight->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(550.0f, Window_Y / 2 - 100));
	at = knight->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Knight_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Knight\\Idle");
	at->PlayAnimation(L"Knight_Idle", true);
	at->SetAffectedCamera(false);

	// Knight_Attack
	Monster* knightA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = knightA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(550.0f, Window_Y / 2 + 100));
	at = knightA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Knight_Attack"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Knight\\Attack");
	at->PlayAnimation(L"Knight_Attack", true);
	at->SetAffectedCamera(false);

	// Ranger_Idle
	Monster* ranger = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = ranger->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(700.0f, Window_Y / 2 - 100));
	at = ranger->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Ranger_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Ranger\\Idle");
	at->PlayAnimation(L"Ranger_Idle", true);
	at->SetAffectedCamera(false);

	// Ranger_Attack
	Monster* rangerA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = rangerA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(700.0f, Window_Y / 2 + 100));
	at = rangerA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"Ranger_Attack"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\Ranger\\Attack");
	at->PlayAnimation(L"Ranger_Attack", true);
	at->SetAffectedCamera(false);

	// BigKnight_Idle
	Monster* bigKnight = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = bigKnight->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(850.0f, Window_Y / 2 - 100));
	at = bigKnight->AddComponent<Animator>();
	at->CreateAnimationFolder(L"BigKnight_Idle"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\BigKnight\\Idle");
	at->PlayAnimation(L"BigKnight_Idle", true);
	at->SetAffectedCamera(false);

	// BigKnight_Attack
	Monster* bigKnightA = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	tr = bigKnightA->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(850.0f, Window_Y / 2 + 100));
	at = bigKnightA->AddComponent<Animator>();
	at->CreateAnimationFolder(L"BigKnight_Attack"
		, L"..\\MyResources\\skul\\3_Monster_Stage1\\BigKnight\\Attack");
	at->PlayAnimation(L"BigKnight_Attack", true);
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

	// Scene ±¸ºÐ
	const wchar_t* str = L"[ StageScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}
