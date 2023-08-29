#include "vanYggdrasillFrame.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanTransform.h"

#define YGG_FRAME_POS_X		640.0f
#define YGG_FRAME_POS_Y		59.0f

namespace van
{
	YggdrasillFrame::YggdrasillFrame()
	{
		AddComponent<SpriteRenderer>();
	}

	YggdrasillFrame::~YggdrasillFrame()
	{
		// nothing
	}

	void YggdrasillFrame::Init()
	{
		UI::Init();
	}

	void YggdrasillFrame::Update()
	{
		UI::Init();
		MakeAnimation();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetTexture(ResourceManager::Find<Texture>(L"UI_Boss_Ch1_Frame"));
		sr->SetScale(math::Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(false);

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(math::Vector2(YGG_FRAME_POS_X, YGG_FRAME_POS_Y));
	}

	void YggdrasillFrame::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void YggdrasillFrame::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillFrame::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillFrame::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillFrame::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}