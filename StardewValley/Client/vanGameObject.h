#pragma once
#include "vanEntity.h"
#include "vanComponent.h"	// mComponents 변수에서 Component 객체들을 가지고 있다.

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
		__inline T* GetComponent()	// 특정 타입의 Component 객체가 존재한다면 해당 객체의 주소값을 반환한다.
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				/* 
					[ dynamic_cast<T> ]
					자식 타입과 T타입이 일치하다면 주소를 반환,
					그렇지 않다면 nullptr 반환

					즉, 부모 타입으로 캐스팅 된 c의 원래 타입과
					T의 타입이 동일하면 해당 객체의 주소를 반환하고
					타입이 다르다면 nullptr을 반환한다.
				*/
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)
					return comp;
			}
			return comp;
		}

		template <typename T>
		__inline T* AddComponent()	// 특정 타입의 Component 객체를 생성하고 해당 객체의 주소를 반환한다.
		{
			T* comp = new T();
			/* 
				[ SetOwner() ]
				Componenet를 가지고 있는 GameObject 객체들이 많을테니 
				어떤 GameObject의 Component인지 알기위해 설정해준다.
			*/
			comp->SetOwner(this);	
			mComponents.push_back(comp);
			
			return comp;
		}

	private:
		std::vector<Component*> mComponents;	// Componenet 객체들의 값을 수정해야하기에 주소를 저장한다.
	};
}

