#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"
#include "vanCamera.h"

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
		// 1) Title Art_1
		// \MyResources\skul\0_BG\DarkMirror_Title_Art.bmp
		Texture* texture = ResourceManager::Load<Texture>(L"Title_Art"
			, L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Art.bmp");
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetTexture(texture);
		bgsr->SetScale(math::Vector2(0.67f,0.67f));
		bgsr->SetAffectCamera(false);

		// 2) Title Art_2
		// \MyResources\skul\0_BG\0_Title\DarkMirror_Title_Logo.png
		texture = ResourceManager::Load<Texture>(L"Title_Logo"
			, L"..\\MyResources\\skul\\0_BG\\0_Title\\DarkMirror_Title_Logo.png");
		BackGround* logo = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		logo->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 200));
		bgsr = logo->AddComponent<SpriteRenderer>();
		bgsr->SetTexture(texture);
		bgsr->SetScale(math::Vector2(0.67f,0.67f));
		bgsr->SetAffectCamera(false);
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