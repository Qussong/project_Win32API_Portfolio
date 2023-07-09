#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"

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
	// StageScene에 넣어줄 객체 생성 + 해당 객체의 Component 생성 & 추가 (Transform 제외)

	// Monster 객체 추가
	Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	monster->AddComponent<SpriteRenderer>();
}

void van::StageScene::Update()
{
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
