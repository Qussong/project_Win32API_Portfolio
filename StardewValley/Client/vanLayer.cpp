#include "vanLayer.h"

namespace van
{
	Layer::Layer()
	{

	}

	Layer::~Layer()
	{

	}

	void Layer::Init()
	{

	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
			obj->Update();
	}

	void Layer::Render(HDC _hdc)
	{
		for (GameObject* obj : mGameObjects)
			obj->Render(_hdc);
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}