#include "vanHomeScene.h"
#include "vanPlayer.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"

namespace van
{
	HomeScene::HomeScene()
	{
		// nothing
	}

	HomeScene::~HomeScene()
	{
		// nothing
	}

	void HomeScene::Init()
	{
		// 1) Player 객체
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);	// Player 생성
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();				// Player 객체에 SpriteRenderer 속성 생성
		Texture* texture = ResourceManager::Load<Texture>(L"Skul", L"..\\MyResources\\skul\\skul\\Idle_3_24.bmp");
		sr->SetTexture(texture);
		sr->SetScale(math::Vector2(4.0f, 4.0f));
		Camera::SetTarget(player);	// 카메라가 바라볼 타겟 설정

		// 2) Monster 객체
		Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		monster->GetComponent<Transform>()->SetPosition(math::Vector2(0,0));
		sr = monster->AddComponent<SpriteRenderer>();
		texture = ResourceManager::Load<Texture>(L"Cat", L"..\\MyResources\\skul\\cat_1\\Walk_1_24.bmp");
		sr->SetTexture(texture);
		sr->SetScale(math::Vector2(3.0f, 3.0f));
	}

	void HomeScene::Update()
	{
		Scene::Update();
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
		
	}
}