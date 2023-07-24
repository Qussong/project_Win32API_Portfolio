#pragma once
#include "vanEntity.h"	// Entity 클래스 상속
#include "vanLayer.h"	// mLayers 변수로 Layer객체들 관리

namespace van
{
	//using namespace van::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		__forceinline void AddGameObject(enums::eLayerType type, GameObject* gameObj) 
													{ mLayers[(int)type].AddGameObject(gameObj); }

		Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }

		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }
		__forceinline GameObject* GetSceneTarget() { return target; }
			
	private:
		std::vector<Layer> mLayers;
		// Scene 클래스에선 Layer 객체의 정보를 가져와 보여주기만 할 것이기에 굳이 주소로 저장하지 않는다.

		GameObject* target;	// 해당 Scene의 Target
	};
}

