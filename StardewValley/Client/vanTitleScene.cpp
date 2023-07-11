#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"

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


		// 1) 배경화면 객체
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		bg->SetMyType(enums::eGameObjectType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* texture = ResourceManager::Load<Texture>(L"TitleBackGroundTexture", L"..\\MyResources\\DarkMirror_Title_Art_BMP.bmp");
		bgsr->SetTexture(texture);
		bgsr->SetScale(math::Vector2(1.0f,1.0f));

		// 2) Player 객체
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);	// Player 생성
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();				// Player 객체에 SpriteRenderer 속성 생성
		texture = ResourceManager::Load<Texture>(L"Skul", L"..\\MyResources\\skul\\skul\\Idle_3_24.bmp");
		sr->SetTexture(texture);
	}

	void TitleScene::Update()
	{
		Scene::Update();						// 부모의 Update 함수 호출
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);					// 부모의 Render 함수 호출

		// Scene 구분
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);	// 아래 두면 가려지지 않는다.
	}
}