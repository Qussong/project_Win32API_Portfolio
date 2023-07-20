#pragma once
#include "CommonInclude.h"
#include "vanCollider.h"

namespace van
{
#define LAYER_MAX (UINT)eLayerType::End

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
		static void Init();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static void Clear();
		static void CollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable);
		static void LayerCollision(class Scene* _scene, eLayerType _left, eLayerType _right);
		static void ColliderCollision(Collider* _left, Collider* _right);
		static bool Intersect(Collider* _left, Collider* _right);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}

