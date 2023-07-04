#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// 함수 포인터
#include <iostream>

#include "framework.h"
#include "vanMath.h"
#include "vanObject.h"

//#define FHD_X 1920
//#define FHD_Y 1080
#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() % (n))	