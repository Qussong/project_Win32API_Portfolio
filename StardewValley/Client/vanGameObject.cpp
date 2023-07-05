#include "vanGameObject.h"
#include "vanTransform.h"		
#include "vanSpriteRenderer.h"

namespace van
{
	GameObject::GameObject()
	{
		// Transform 객체에 해당 Transform을 소유하고 있는 GameObject 객체를 알려준다.
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);

		// SpriteRenderer 객체에 해당 Transform을 소유하고 있는 GameObject 객체를 알려준다.
		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Init()
	{
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
			comp->Update();
	}
	void GameObject::Render(HDC _hdc)
	{
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}
}