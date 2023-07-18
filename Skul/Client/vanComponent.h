#pragma once
#include "vanEntity.h"

namespace van
{
	class Component : public Entity	// Component 클래스는 상속되어 사용된다.
									//		-> SpriteRenderer, Transform 에서 구체화된다.
	{
	public:
		Component(enums::eComponentType type);
		virtual ~Component();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		__inline void SetOwner(class GameObject* owner) { mOwner = owner; }		// Setter
		__inline class GameObject* GetOwner() { return mOwner; }				// Getter

	private:
		const enums::eComponentType mType;	// 생성자에서 받아준 type이 mType에 저장된다.
											// 컴포넌트 종류 : Transform, SpriteRenderer, End, ...
		class GameObject* mOwner;			// 해당 컴포넌트 값들을 가지고 있는 GameObject 저장
	};
}
