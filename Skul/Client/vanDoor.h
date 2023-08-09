#pragma once
#include "vanGameObject.h"

namespace van
{
	class Door : public GameObject
	{
	public:
		Door();
		virtual ~Door();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	
		virtual void OnCollisionStay(class Collider* _other);	
		virtual void OnCollisionExit(class Collider* _other);	

	private:

	};
}

