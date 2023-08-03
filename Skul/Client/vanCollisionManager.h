#pragma once
#include "CommonInclude.h"
#include "vanCollider.h"

namespace van
{
#define LAYER_MAX (UINT)eLayerType::End	// 총 Layer 개수

	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	using namespace enums;

	class CollisionManager
	{
	public:
		static void Init();				// 초기화
		static void Update();			// 값 변경
		static void Render(HDC hdc);	// 출력
		static void Release();			// ???

		static void Clear();	// mCollisionMap, mLayerMasks 를 전부 초기화한다.
		static void SetCollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable);	// 파라미터로 들어오는 각 레이어(_left, _right)들의 충돌체크 여부 설정
		static bool Intersect(Collider* _left, Collider* _right);							// 충돌상태 확인 (충돌시 true 반환)
		static void ColliderCollision(Collider* _left, Collider* _right);					// 두 객체의 충돌과정에(enter, stay, exit)따른 영향 계산
		static void LayerCollision(class Scene* _scene, eLayerType _left, eLayerType _right);	// 레이어들간의 충돌 체크여부 설정

		static bool ColliderCollisionCheck();

	private:
		static std::map<UINT64, bool> mCollisionMap;			// 충돌 정보 저장
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];	// 레이어들간의 충돌 체크여부 설정값 저장
	};
}

