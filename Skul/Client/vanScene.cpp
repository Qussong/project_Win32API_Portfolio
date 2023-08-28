#include "vanScene.h"
#include "vanObject.h"
#include "vanPlayer.h"
#include "vanAnimator.h"
#include "vanBackGround.h"

namespace van
{
	Scene::Scene()
		: mTarget(nullptr)
	{
		mLayers.resize((int)enums::eLayerType::End);
	}

	Scene::~Scene()
	{
		// nothing
	}

	void Scene::Init()
	{
		MakeWorld();
		MakeFloor();
		MakeWall();
		MakeDoor();
		MakeUI();
	}

	void Scene::Update()
	{
		/*
			mLayers 에서 Layer 객체들의 정보를 복사해서 가져오기 때문에 
			참조자로 처리한다. (메모리 사용량 ↓)
		*/

		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::Render(HDC _hdc)
	{
		for (Layer& layer : mLayers)
			layer.Render(_hdc);

		Time::Render(_hdc);

		// Monster 카운트 출력
		const int SIZE = 100;
		wchar_t szFloat[SIZE] = {};
		swprintf_s(szFloat, SIZE, L"MonsterCnt : %d", mMonsterCnt);
		int strLen = (int)wcsnlen_s(szFloat, SIZE);
		TextOut(_hdc, 150, 10, szFloat, strLen);
	}

	void Scene::SceneIN()
	{
		// nothing
	}

	void Scene::SceneOut()
	{
		// nothing
	}

	void Scene::CameraMove()
	{
		// nothing
	}

	void Scene::MakeWorld()
	{
		// nothing
	}

	void Scene::MakeFloor()
	{
		// nothing
	}

	void Scene::MakeWall()
	{
		// nothing
	}

	void Scene::MakeDoor()
	{
		// nothing
	}

	void Scene::MakeUI()
	{
		// UI 객체 생성
		mPlayerFrame = Object::Instantiate<PlayerFrame>(enums::eLayerType::UI);
		mHpBar = Object::Instantiate<HpBar>(enums::eLayerType::UI);
	}
}