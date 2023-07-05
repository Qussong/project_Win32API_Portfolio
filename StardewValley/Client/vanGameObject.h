#pragma once
#include "vanEntity.h"
#include "vanComponent.h"	// mComponents에서 Component 객체들을 관리한다.

namespace van
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		template <typename T>
		__inline T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)	// 연산과정을 줄여준다.
					return comp;
			}
			return comp;
		}

	private:
		std::vector<Component*> mComponents;	// Componenet 객체들의 값을 수정해야하기에 주소를 저장한다.
	};
}

