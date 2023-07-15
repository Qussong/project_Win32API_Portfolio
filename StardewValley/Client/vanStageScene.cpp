#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"

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
	// 1) cat_idle
	Monster* cat = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	Transform* tr = cat->GetComponent<Transform>();
	tr->SetPosition(math::Vector2(0.0f, 0.0f));
	Animator* at = cat->AddComponent<Animator>();

	at->CreateAnimationFolder(L"Test", L"..\\Resources\\Image\\Player");
	//at->CreateAnimationFolder(L"Test", L"..\\MyResources\\skul\\cat_1_idle");
	at->PlayAnimation(L"Test", true);

	at->SetAffectedCamera(true);

	// 2) cat
	Texture* texture = ResourceManager::Load<Texture>(L"Monster_Cat"
		, L"..\\MyResources\\skul\\cat_1\\Walk_1_24.bmp");
	Monster* cat2 = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	cat2->GetComponent<Transform>()->SetPosition(math::Vector2(20, 0));
	SpriteRenderer* sr = cat2->AddComponent<SpriteRenderer>();
	sr->SetTexture(texture);
	sr->SetScale(math::Vector2(1.0f, 1.0f));

}

void van::StageScene::Update()
{
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
