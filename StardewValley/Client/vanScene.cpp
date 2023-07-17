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

	}

	void Scene::Init()
	{
		//mLayers[(int)enums::eLayerType::Player].AddGameObject();
	}

	void Scene::Update()
	{
		/*
			mLayers 에서 Layer 객체들의 정보를 복사해서 가져오기 때문에 
			참조자로 처리한다. (메모리 사용량 ↓)
		*/
		for (Layer& layer : mLayers)
			layer.Update();

	}

	void Scene::Render(HDC _hdc)
	{
		for (Layer& layer : mLayers)
			layer.Render(_hdc);
		Time::Render(_hdc);
		Text::PrintwString(_hdc, 10, 50, L"Title - z");
		Text::PrintwString(_hdc, 10, 70, L"Home - x");
		Text::PrintwString(_hdc, 10, 90, L"Ending - c");
	}

	void Scene::AddGameObject(enums::eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);	// type에 해당하는 레이어에 GameObject 객체 생성
	}
}