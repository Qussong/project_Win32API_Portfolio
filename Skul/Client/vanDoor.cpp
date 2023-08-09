#include "vanDoor.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"

namespace van
{
	Door::Door()
	{
		// nothing
	}

	Door::~Door()
	{
		// nothing
	}

	void Door::Init()
	{
		MakeAnimation();
		
		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(60.0f, 180.0f));
		col->SetOffset(math::Vector2(10.0f, 30.0f));
		col->SetLineColor(RGB(0, 255, 255));

		CollisionManager::SetCollisionLayerCheck(enums::eLayerType::Door, enums::eLayerType::Player, true);
	}

	void Door::Update()
	{
		GameObject::Update();
	}

	void Door::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Door::MakeAnimation()
	{
		Animator* ani = GetComponent<Animator>();
		ani->CreateAnimation(L"Stage1_Door_1", ResourceManager::Find<Texture>(L"Stage1_Door_1"), math::Vector2::Zero, math::Vector2(176.0f, 128.0f), 7, math::Vector2::Zero);
		ani->CreateAnimation(L"Stage1_Door_2", ResourceManager::Find<Texture>(L"Stage1_Door_2"), math::Vector2::Zero, math::Vector2(176.0f, 128.0f), 7, math::Vector2::Zero);
	}

	void Door::OnCollisionEnter(Collider* _other)
	{

	}

	void Door::OnCollisionStay(Collider* _other)
	{

	}

	void Door::OnCollisionExit(Collider* _other)
	{

	}
}