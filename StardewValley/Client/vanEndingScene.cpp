#include "vanEndingScene.h"
#include "vanGhost.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
van::EndingScene::EndingScene()
{
	// nothing

}

van::EndingScene::~EndingScene()
{
	// nothing

}

void van::EndingScene::Init()
{
	// EndingScene에 넣어줄 객체 생성 + 해당 객체의 Component 생성 & 추가 (Transform 제외)

	// Ghost 객체 추가
	Ghost* ghost = Object::Instantiate<Ghost>(enums::eLayerType::Monster);
	ghost->AddComponent<SpriteRenderer>();
}

void van::EndingScene::Update()
{
	Scene::Update();
}

void van::EndingScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
