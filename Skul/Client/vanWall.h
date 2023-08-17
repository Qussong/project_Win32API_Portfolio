#pragma once
#include "vanGameObject.h"

namespace van
{
	class Wall : public GameObject
	{
	public:
		Wall();
		~Wall();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		__forceinline bool GetFloorLimit() { return mbFloorLimit; }
		__forceinline void SetFloorLimit(bool _flag) { mbFloorLimit = _flag; }

	private:
		bool mbFloorLimit;	// 몬스터에게만 작용하게 해준다.
	};
}
