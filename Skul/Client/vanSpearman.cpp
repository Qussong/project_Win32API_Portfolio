#include "vanSpearman.h"
#include "vanAnimator.h"
#include "vanObject.h"
#include "vanTexture.h"
#include "vanResourceManager.h"

namespace van
{
	Spearman::Spearman()
	{
	}

	Spearman::~Spearman()
	{

	}

	void Spearman::Init()
	{
		// Rout : \MyResources\skul\4_Monster_Stage2\4_Spearman
		
		// Idle
		Texture* texture = ResourceManager::Load<Texture>(L"Idle_Texture"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\4_Spearman\\1_Idle.bmp");
		Animator* animator = this->AddComponent<Animator>();
		animator->CreateAnimation(
			L"Idle"
			, texture
			, math::Vector2::Zero
			, math::Vector2(60.0f, 89.0f)
			, 5);
		// Walk
		texture = ResourceManager::Load<Texture>(L"Walk_Texture"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\4_Spearman\\2_Walk.bmp");
		animator->CreateAnimation(
			L"Walk"
			, texture
			, math::Vector2::Zero
			, math::Vector2(98.0f, 56.0f)
			, 8
		);
		// Attack
		texture = ResourceManager::Load<Texture>(L"Attack_Texture"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\4_Spearman\\3_Attack.bmp");
		animator->CreateAnimation(
			L"Attack"
			, texture
			, math::Vector2::Zero
			, math::Vector2(171.0f, 55.0f)
			, 8
		);
		// Attack2
		texture = ResourceManager::Load<Texture>(L"Attack2_Texture"
			, L"..\\MyResources\\skul\\4_Monster_Stage2\\4_Spearman\\3_Attack_2.bmp");
		animator->CreateAnimation(
			L"Attack_2"
			, texture
			, math::Vector2::Zero
			, math::Vector2(176.0f, 114.0f)
			, 8
		);
	}

	void Spearman::Update()
	{
		GameObject::Update();
	}

	void Spearman::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}