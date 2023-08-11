#include "vanStage1Scene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"

#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanAnimator.h"

namespace van
{
	Stage1Scene::Stage1Scene()
	{
		// nothing
	}

	Stage1Scene::~Stage1Scene()
	{
		// nothing
	}

	void Stage1Scene::Init()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround °´Ã¼ »ý¼º
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, -80.0f));			// À§Ä¡°ª ¼³Á¤
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer Ãß°¡
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster"));				// BackGround °´Ã¼ÀÇ texture ¼³Á¤
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale ¼³Á¤
		bgsr->SetAffectCamera(true);

		// Floor_B1 °´Ã¼ 
		Floor* floorB1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1->GetComponent<Collider>()->SetSize(math::Vector2(1520.0f, 1.0f));
		floorB1->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 1050.0f));
		// Floor_1_1 °´Ã¼ 
		Floor* floor1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_1->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, 1.0f));
		floor1_1->GetComponent<Transform>()->SetPosition(math::Vector2(-1015.0f, 830.0f));
		// Floor_1_2 °´Ã¼ 
		Floor* floor1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_2->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, 1.0f));
		floor1_2->GetComponent<Transform>()->SetPosition(math::Vector2(1015.0f, 830.0f));
		// Floor_2_1 °´Ã¼_o
		Floor* floor2_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_1->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, 1.0f));
		floor2_1->GetComponent<Transform>()->SetPosition(math::Vector2(-470.0f, 610.0f));
		// Floor_2_2 °´Ã¼_o
		Floor* floor2_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_2->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, 1.0f));
		floor2_2->GetComponent<Transform>()->SetPosition(math::Vector2(470.0f, 610.0f));
		// Floor_3 °´Ã¼_o
		Floor* floor3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Collider>()->SetSize(math::Vector2(1800.0f, 1.0f));
		floor3->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 320.0f));
		// Floor_4 °´Ã¼_o
		Floor* floor4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Collider>()->SetSize(math::Vector2(350.0f, 1.0f));
		floor4->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 35.0f));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		Animator* at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		SetSceneTarget(player);	// ±âº»°ª nullptrÀÌ¶ó »ý·« °¡´É
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ±¸ºÐ
		const wchar_t* str = L"[ Stage1Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage1Scene::SceneIN()
	{
	}
	void Stage1Scene::SceneOut()
	{
	}
}