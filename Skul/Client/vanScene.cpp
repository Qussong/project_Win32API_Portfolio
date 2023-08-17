#include "vanScene.h"

namespace van
{
	Scene::Scene()
		: target(nullptr)
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
	}
	void Scene::MakeFloor()
	{
	}
	void Scene::MakeWall()
	{
	}
	void Scene::MakeDoor()
	{
	}
}