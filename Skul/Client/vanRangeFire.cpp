#include "vanRangeFire.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	RangeFire::RangeFire()
	{
		// nothing
	}

	RangeFire::~RangeFire()
	{
		// nothing
	}

	void RangeFire::Init()
	{
		Skill::Init();
	}

	void RangeFire::Update()
	{
		Skill::Update();
	}

	void RangeFire::Render(HDC _hdc)
	{
		Skill::Render(_hdc);
	}

	void RangeFire::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		
	}

	void RangeFire::OnCollisionEnter(Collider* _other)
	{
	}

	void RangeFire::OnCollisionStay(Collider* _other)
	{
	}

	void RangeFire::OnCollisionExit(Collider* _other)
	{
	}
}
