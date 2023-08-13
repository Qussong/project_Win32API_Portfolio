#pragma once
#include "vanMonster.h"

namespace van
{
	class Stage1Trap : public Monster
	{
	public:
		Stage1Trap();
		virtual ~Stage1Trap();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		void Idle();

	private:

	};
}

