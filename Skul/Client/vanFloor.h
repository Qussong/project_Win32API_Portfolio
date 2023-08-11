#pragma once
#include "vanGameObject.h"

namespace van
{
	class FloorPass;

	class Floor : public GameObject
	{
	public:
		Floor();
		~Floor();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

	private:

	};
}

