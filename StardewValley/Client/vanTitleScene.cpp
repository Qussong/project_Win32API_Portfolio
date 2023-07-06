#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"

namespace van
{
	TitleScene::TitleScene()
	{
		// nothing
	}

	TitleScene::~TitleScene()
	{
		// nothing
	}

	void TitleScene::Init()
	{
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->AddComponent<SpriteRenderer>();
	}

	void TitleScene::Update()
	{
		Scene::Update();	// 부모의 Update 함수 호출
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);	// 부모의 Render 함수 호출
	}
}