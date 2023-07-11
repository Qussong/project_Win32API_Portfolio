#include "vanGameObject.h"
#include "vanTransform.h"		
#include "vanSpriteRenderer.h"

namespace van
{
	GameObject::GameObject()
		: mType(enums::eGameObjectType::None)
	{
		/*
		// Transform 객체에 해당 Transform을 소유하고 있는 GameObject 객체를 알려준다.
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);

		// SpriteRenderer 객체에 해당 Transform을 소유하고 있는 GameObject 객체를 알려준다.
		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
		*/
		AddComponent<Transform>();	// GameObject 객체에 Transform 속성을 만들어 넣어준다.
	}

	GameObject::~GameObject()
	{
		// nothing
	}

	void GameObject::Init()
	{
		// nothing
	}

	void GameObject::Update()
	{
		// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.
		for (Component* comp : mComponents)
			comp->Update();
	}

	void GameObject::Render(HDC _hdc)
	{
		// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
		// 클래스 종류 : Transform, SpriteRenderer
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}
}