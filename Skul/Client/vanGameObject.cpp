#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanSpriteRenderer.h"
#include "vanSceneManager.h"
#include "vanCollider.h"
#include "vanMonster.h"

namespace van
{
	GameObject::GameObject()
		: offset(math::Vector2::Zero)
		, mState(eState::Active)
	{
		AddComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));	// 기본 위치 화면 중앙
		AddComponent<Animator>();
		AddComponent<Collider>();	
	}

	GameObject::~GameObject()
	{
		// nothingz
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

	void GameObject::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void GameObject::MakeAnimation()
	{
		// nothing
	}
}