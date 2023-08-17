#include "vanStage1BossScene.h"
#include "vanCamera.h"

namespace van
{
	Stage1BossScene::Stage1BossScene()
	{
		// nothing
	}

	Stage1BossScene::~Stage1BossScene()
	{
		// nothing
	}

	void Stage1BossScene::Init()
	{
		Scene::Init();

		//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1BossScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ Stage1BossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1BossScene::SceneIN()
	{
		// nothing
	}

	void Stage1BossScene::SceneOut()
	{
		// nothing
	}

	void Stage1BossScene::CameraMove()
	{
		// nothing
	}

	void Stage1BossScene::MakeWorld()
	{
		//// [ World_Wall ]
		//Texture* image = bgsr->GetTexture();
		//math::Vector2 size = image->GetSize();
		//// Left
		//Wall* worldWall_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		//worldWall_L->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		//worldWall_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - size.x / 2 - 1.0f, Window_Y / 2));
		//// Right
		//Wall* worldWall_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		//worldWall_R->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		//worldWall_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + size.x / 2 + 1.0f, Window_Y / 2));
	}

	void Stage1BossScene::MakeFloor()
	{
		// nothing
	}

	void Stage1BossScene::MakeWall()
	{
		// nothing
	}

	void Stage1BossScene::MakeDoor()
	{
		// nothing
	}
}
