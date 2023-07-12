#include "vanEndingScene.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanPlayer.h"
#include "vanResourceManager.h"

namespace van
{
	EndingScene::EndingScene()
	{
		// nothing
	}

	EndingScene::~EndingScene()
	{
		// nothing
	}

	void EndingScene::Init()
	{
		// 1) Player °´Ã¼
		/*Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		Texture* texture = ResourceManager::Load<Texture>(L"TitleBackGroundImage", L"..\\Resources\\Image\\Fighter.bmp");
		sr->SetTexture(texture);*/
	}

	void EndingScene::Update()
	{
		Scene::Update();
	}

	void EndingScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ±¸ºÐ
		const wchar_t* str = L"[ EndingScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}
