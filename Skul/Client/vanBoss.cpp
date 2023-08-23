#include "vanBoss.h"
#include "vanSceneManager.h"

namespace van
{
	Boss::Boss()
	{
		// nothing
	}

	Boss::~Boss()
	{
		// nothing
	}

	void Boss::Init()
	{
		GameObject::Init();

		Scene* scene = SceneManager::GetActiveScene();
		mTarget = scene->GetSceneTarget();
	}

	void Boss::Update()
	{
		GameObject::Update();
	}

	void Boss::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Boss::MakeAnimation()
	{
		// nothing
	}

	void Boss::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void Boss::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void Boss::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void Boss::Gen()
	{
		// nothing
	}

	void Boss::Idle()
	{
		// nothing
	}

	void Boss::Walk()
	{
		// nothing
	}

	void Boss::AttackReady()
	{
		// nothing
	}

	void Boss::Attack()
	{
		// nothing
	}

	void Boss::AttackEnd()
	{
		// nothing
	}

	void Boss::Hit()
	{
		// nothing
	}

	void Boss::Dead()
	{
		// nothing
	}

}