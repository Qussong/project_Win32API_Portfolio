#include "vanEndingScene.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanPlayer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"

#include "vanMonster.h"
#include "vanTransform.h"
#include "vanAnimator.h"

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
		// CreateAnimationFolder() *.png 파일 출력 test -> 출력이 안된다.
		/*Monster* cat = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		Transform* tr = cat->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		Animator* at = cat->AddComponent<Animator>();
		at->CreateAnimationFolder(L"Cat_Magic"
			, L"..\\MyResources\\skul\\Test");
		at->PlayAnimation(L"Cat_Magic", true);
		at->SetAffectedCamera(false);*/

		// CreateAnimation() *.png Atlas 출력 test -> 출력은 되나 FPS 떨어짐
		/*Texture* texture = ResourceManager::Load<Texture>(L"test"
			, L"..\\MyResources\\merged_image.png");
		Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		monster->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));

		Animator* at = monster->AddComponent<Animator>();
		at->CreateAnimation(L"test"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(321.0f, 321.0f)
			, 49
			, math::Vector2(0.0f, 0.0f)
			, 0.1f);
		at->PlayAnimation(L"test", true);
		at->SetAffectedCamera(false);*/

		SetTarget(nullptr);
		Camera::SetTarget(GetTarget());
	}

	void EndingScene::Update()
	{
		Camera::SetTarget(GetTarget());
		Scene::Update();
	}

	void EndingScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ EndingScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}
