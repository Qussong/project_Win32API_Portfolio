#pragma once
// 제공되는 라이브러리
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// 함수 포인터
#include <string>
#include "framework.h"

// 직접만든 라이브러리
#include "vanMath.h"
#include "vanTime.h"
#include "vanInput.h"
#include "vanText.h"

// 매크로 변수
#define SPEED		600.0f
#define DIAMETER	200

#define HD_X		1280
#define HD_Y		720
#define FHD_X		1920
#define FHD_Y		1080
#define Window_X	HD_X
#define Window_Y	HD_Y


namespace van::enums
{
	enum class eLayerType
	{
		Background,		// 0
		Player,
		Monster,
		Effect,
		UI,
		End,			// 5
	};

	enum class eComponentType
	{
		Transform,		// 0
		SpriteRenderer,
		End,			// 2
	};

	enum class eSceneType
	{
		TitleScene,		// 0 
		StageScene,		// 1
		EndingScene,	// 2
	};
}