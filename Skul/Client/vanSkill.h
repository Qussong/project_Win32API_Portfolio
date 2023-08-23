#pragma once
#include "vanGameObject.h"

namespace van
{
	class Skill	: public GameObject
	{
	public:
		Skill();
		virtual ~Skill();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
	};
}

