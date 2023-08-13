#include "vanDoor.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"
#include "vanSceneManager.h"
//#include "vanScene.h"

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
		
		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));

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
		ani->CreateAnimation(L"Stage1_Door_3", ResourceManager::Find<Texture>(L"Stage1_Door_3"), math::Vector2::Zero, math::Vector2(199.0f, 129.0f), 8, math::Vector2::Zero);
		ani->CreateAnimation(L"Stage1_Door_Market", ResourceManager::Find<Texture>(L"Stage1_Door_Market"), math::Vector2::Zero, math::Vector2(184.0f, 137.0f), 8, math::Vector2::Zero);
		ani->CreateAnimation(L"Stage1_Door_Middle_Boss", ResourceManager::Find<Texture>(L"Stage1_Door_Middle_Boss"), math::Vector2::Zero, math::Vector2(230.0f, 175.0f), 8, math::Vector2::Zero);
		ani->CreateAnimation(L"Stage1_Door_Boss", ResourceManager::Find<Texture>(L"Stage1_Door_Boss"), math::Vector2::Zero, math::Vector2(314.0f, 185.0f), 8, math::Vector2::Zero);
		
	}

	void Door::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Door::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Player* player = dynamic_cast<Player*>(obj);

		if (player != nullptr)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				Scene* scene = SceneManager::GetActiveScene();
				SceneManager::Next(scene->GetName());
			}
		}
	}

	void Door::OnCollisionExit(Collider* _other)
	{

	}
}