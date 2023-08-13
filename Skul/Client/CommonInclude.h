#pragma once
// 제공되는 라이브러리
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// 함수 포인터
#include <string>
#pragma comment(lib, "Msimg32.lib")
#include <filesystem>
#include <bitset>

#include <typeinfo>		// 타입비교

// 제공되는 헤더
#include "framework.h"

// 직접만든 헤더
#include "vanMath.h"
#include "vanTime.h"
#include "vanInput.h"
#include "vanText.h"

// 매크로 변수
#define HD_X			1280
#define HD_Y			720
#define FHD_X			1920
#define FHD_Y			1080
#define Window_X		HD_X
#define Window_Y		HD_Y
#define FLOOR_HEIGHT	2.0f

namespace van::enums
{
	enum class eLayerType
	{
		BackGround,
		Floor,
		Wall,
		Door,
		NPC,
		Range_Monster_Trace,
		Range_Monster_Attack,
		Monster,
		Range_Attack,
		Player,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		RigidBody,
		End,
	};

}