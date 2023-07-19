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
		Monster* cat = Object::Instantiate<Monster>(enums::eLayerType::Monster);
		Transform* tr = cat->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		Animator* at = cat->AddComponent<Animator>();
		// C:\Users\kih09\Desktop\Git\Win32api_class\Skul\MyResources\skul\Test
		at->CreateAnimationFolder(L"Cat_Magic"
			, L"..\\MyResources\\skul\\Test");
		at->PlayAnimation(L"Cat_Magic", true);
		at->SetAffectedCamera(false);

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

		// Scene ±¸ºÐ
		const wchar_t* str = L"[ EndingScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
}
