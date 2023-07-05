#pragma once
#include "vanEntity.h"
#include "vanGameObject.h"	// mGameObjects 에서 GameObject 의 객체들을 관리한다.
namespace van
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		void AddGameObject();

	private:
		std::vector<GameObject*> mGameObjects;	// GameObject 객체들의 정보를 수정해야하기에 주소값으로 저장한다.
	};

}

