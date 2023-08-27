#include "vanMageFrame.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

#define MAGE_FRAME_POS_X	1160.0f
#define MAGE_FRAME_POS_Y	40.0f

namespace van
{
	MageFrame::MageFrame()
	{
		AddComponent<SpriteRenderer>();
	}

	MageFrame::~MageFrame()
	{
	}

	void MageFrame::Init()
	{
		UI::Init();
	}

	void MageFrame::Update()
	{
		UI::Init();
		MakeAnimation();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"UI_MiddleBoss_Frame"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(false);

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(math::Vector2(MAGE_FRAME_POS_X, MAGE_FRAME_POS_Y));
	}

	void MageFrame::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void MageFrame::MakeAnimation()
	{
	}

	void MageFrame::OnCollisionEnter(Collider* _other)
	{
	}

	void MageFrame::OnCollisionStay(Collider* _other)
	{
	}

	void MageFrame::OnCollisionExit(Collider* _other)
	{
	}
}