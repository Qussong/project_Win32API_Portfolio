#include "vanYggdrasillChin.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

namespace van
{
	YggdrasillChin::YggdrasillChin()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillChin::~YggdrasillChin()
	{
		// nothing
	}

	void YggdrasillChin::Init()
	{
		GameObject::Init();	// 아무것도 안함

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Chin"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(110.0f * 2, 97.0f * 2));
	}

	void YggdrasillChin::Update()
	{
		GameObject::Update();	// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.
	}

	void YggdrasillChin::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);	// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
	}

	void YggdrasillChin::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillChin::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}