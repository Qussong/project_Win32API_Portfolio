#include "vanCarleonRecruit.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanAnimator.h"

namespace van
{
	CarleonRecruit::CarleonRecruit()
	{

	}

	CarleonRecruit::~CarleonRecruit()
	{

	}

	void CarleonRecruit::Init()
	{
		// Rout : \MyResources\skul\4_Monster_Stage2\1_CarleonRecruit

		// Idle
		Texture* texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Idle"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\1_Idle.bmp");
		Animator* animator = /*this->*/AddComponent<Animator>();
		animator->CreateAnimation(L"Idle"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(34.0f, 57.0f)
			, 6
		);
		// Walk
		texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Walk"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\2_Walk.bmp");
		animator->CreateAnimation(L"Walk"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(48.0f, 50.0f)
			, 5);
		// Attack
		texture = ResourceManager::Load<Texture>(L"CarleonRecruit_Attack"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\1_CarleonRecruit\\3_Attack.bmp");
		animator->CreateAnimation(L"Attack"
			, texture
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(58.0f, 64.0f)
			, 5);
	}

	void CarleonRecruit::Update()
	{
		GameObject::Update();
	}

	void CarleonRecruit::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}