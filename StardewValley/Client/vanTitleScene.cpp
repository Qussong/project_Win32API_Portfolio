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
		// TitleScene에 넣어줄 객체 생성 + 해당 객체의 Component 생성 & 추가 (Transform 제외)
		// Transform 은 GameObject의 기본생성자가 호출될 때 자동으로 생성된다.
		
		// 1) Player 객체
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->AddComponent<SpriteRenderer>();
	}

	void TitleScene::Update()
	{
		Scene::Update();	// 부모의 Update 함수 호출
	}

	void TitleScene::Render(HDC _hdc)
	{
		//Text::PrintwString(_hdc, 10, 30, L"TitleScene");	// 위에 두면 가려진다
		Scene::Render(_hdc);	// 부모의 Render 함수 호출

		// Scene 구분
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);				// 아래 두면 가려지지 않는다.
	}
}