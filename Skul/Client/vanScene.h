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
		Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }	// 해당 Scene이 관리하는 Layer들중 파라미터에 해당하는 정보를 가져온다.
																					// CommonInclude.h 에 정의되어 있는 enums::eLayerType에 의해 
		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }	// 해당 Scene 에서의 타겟 설정
		__forceinline GameObject* GetSceneTarget() { return target; }	// 해당 Scene 에서의 타겟 정보 받아오기

	private:
		std::vector<Layer> mLayers;	// 해당 Scene이 관리하는 Layer 객체들을 저장
		GameObject* target;	// 해당 Scene에서 Camera의 Target
	};
}

