#include "vanLayer.h"

namespace van
{
	Layer::Layer()
	{
		// nothing
	}

	Layer::~Layer()
	{
		// nothing
	}

	void Layer::Init()
	{
		// nothing
	}

	void Layer::Update()
	{
		//for (GameObject* obj : mGameObjects)
		//{
		//	if (obj->GetState() == GameObject::eState::Pause)
		//	{
		//		continue;
		//	}
		//	obj->Update();
		//}

		for (int i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetState() == GameObject::eState::Pause)
			{
				continue;
			}
			mGameObjects[i]->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		//for (GameObject* obj : mGameObjects)
		//{
		//	if (obj->GetState() == GameObject::eState::Pause)
		//	{
		//		continue;
		//	}
		//	obj->Render(_hdc);
		//}

		for (int i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetState() == GameObject::eState::Pause)
			{
				continue;
			}
			mGameObjects[i]->Render(_hdc);
		}


		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;

				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

	}
}