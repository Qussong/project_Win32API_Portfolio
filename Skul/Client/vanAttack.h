#pragma once
#include "vanRange.h"

namespace van
{
	class Attack : public Range
	{
	public:
		Attack();
		virtual ~Attack();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

	private:

	};
}

