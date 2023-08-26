#include "vanPlayerFrame.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"
#include "vanCollider.h"

namespace van
{
	PlayerFrame::PlayerFrame()
	{
		AddComponent<SpriteRenderer>();
	}

	PlayerFrame::~PlayerFrame()
	{
		// nothing
	}

	void PlayerFrame::Init()
	{
		UI::Init();
		MakeAnimation();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"UI_Player_Frame"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(false);

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(math::Vector2(168.0f, 654.0f));
	}

	void PlayerFrame::Update()
	{
		UI::Update();
	}

	void PlayerFrame::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void PlayerFrame::MakeAnimation()
	{
		// nothing
	}

	void PlayerFrame::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void PlayerFrame::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void PlayerFrame::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}