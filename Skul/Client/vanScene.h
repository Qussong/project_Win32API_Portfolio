#pragma once
#include "vanEntity.h"	// Entity 클래스 상속
#include "vanLayer.h"	// mLayers 변수로 Layer객체들 관리
#include "vanPlayerFrame.h"
#include "vanHpBar.h"

namespace van
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void SceneIN();
		virtual void SceneOut();
		virtual void CameraMove();
		virtual void MakeWorld();
		virtual void MakeFloor();
		virtual void MakeWall();
		virtual void MakeDoor();
		virtual void MakeUI();

		__forceinline void AddGameObject(enums::eLayerType type, GameObject* gameObj) { mLayers[(int)type].AddGameObject(gameObj); }
		__forceinline Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }	// 해당 Scene이 관리하는 Layer들중 파라미터에 해당하는 정보를 가져온다.
		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }	// 해당 Scene 에서의 타겟 설정
		__forceinline GameObject* GetSceneTarget() { return target; }							// 해당 Scene 에서의 타겟 정보 받아오기
		__forceinline math::Vector2 GetCameraWidthLimit() { return mCameraWidthLimit; }
		__forceinline void SetCameraWidthLimit(math::Vector2 _limit) { mCameraWidthLimit = _limit; }
		__forceinline math::Vector2 GetCameraHeightLimit() { return mCameraHeightLimit; }
		__forceinline void SetCameraHeightLimit(math::Vector2 _limit) { mCameraHeightLimit = _limit; }

		__forceinline int GetMonsterCnt() { return mMonsterCnt; }
		__forceinline void AddMonsterCnt(int _cnt = 1) { mMonsterCnt += _cnt; }
		__forceinline void LoseMonsterCnt(int _cnt = 1) { mMonsterCnt -= _cnt; }

	private:
		std::vector<Layer> mLayers;			// 해당 Scene이 관리하는 Layer 객체들을 저장
		GameObject* target;					// 해당 Scene에서 Camera의 Target
		math::Vector2 mCameraWidthLimit;	// 해당 Scene에서 Camera의 좌우 최대 이동 가능거리
		math::Vector2 mCameraHeightLimit;	// 해당 Scene에서 Camera의 상하 최대 이동 가능거리

		int mMonsterCnt = 0;					// 해당 Scene에서의 몬스터 개수
		PlayerFrame* mPlayerFrame = nullptr;
		HpBar* mHpBar = nullptr;
	};
}

