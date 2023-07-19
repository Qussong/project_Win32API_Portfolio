#pragma once
#include "CommonInclude.h"

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
		//public:
		//	static void Init();
		//	static void Update();
		//	static void Render(HDC hdc);
		//	static void Release();

		//private:
		//	static std::map<UINT64, bool> mCollisionMap;
		//	static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}

