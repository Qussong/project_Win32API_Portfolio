#include "vanYggdrasillBody.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanTransform.h"

namespace van
{
	YggdrasillBody::YggdrasillBody()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillBody::~YggdrasillBody()
	{
		// nothing
	}

	void YggdrasillBody::Init()
	{
		GameObject::Init();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetTexture(ResourceManager::Find<Texture>(L"Yggdrasill_Body"));

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(418.0f * 2, 341.0f * 2));
	}

	void YggdrasillBody::Update()
	{
		GameObject::Update();
	}

	void YggdrasillBody::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillBody::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillBody::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

}