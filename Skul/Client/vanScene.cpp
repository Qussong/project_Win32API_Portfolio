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
		/*Text::PrintwString(_hdc, 10, 50, L"Title - q");
		Text::PrintwString(_hdc, 10, 50, L"Lodaing - w");
		Text::PrintwString(_hdc, 10, 70, L"Home - e");
		Text::PrintwString(_hdc, 10, 90, L"Stage - r");
		Text::PrintwString(_hdc, 10, 110, L"Ending - t");*/
	}
}