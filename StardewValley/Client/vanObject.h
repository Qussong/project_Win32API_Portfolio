#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC

#define DIRECTION_CNT  8
#define FHD_X	1920
#define FHD_Y	1080

namespace van
{
	enum class Direction
	{
		Top,			// 0
		TopRight,		// 1
		Right,			// 2
		BottomRight,	// 3
		Bottom,			// 4
		BottomLeft,		// 5
		Left,			// 6
		TopLeft,		// 7
	};

	class Object
	{
	public:
		Object();
		Object(float _x1, float _y1, float _x2, float y2);
		void setDirNum();									// 완전 랜덤
		void setDirNum2(int _directNum);					// 직접 지정
		void setDelta(float _delta);						// set 델타타임 
		void setSpeed(float _speed);						// set 속도
		/*
			[ 반사 경우의 수 ]
			top ----> bottom	0 -> 4

			topRight --x-->		1 -> 3 (+2)
			topRight --y-->		1 -> 7 (-2)

			right ---->			2 -> 6

			bottomRight --x-->	3 -> 1 (-2)
			bottomRight --y-->	3 -> 5 (+2)

			bottom ---->		4 -> 0

			bottomLeft --x-->	5 -> 7 (+2)
			bottomLeft --y-->	5 -> 3 (-2)

			left ---->			6 -> 2

			topleft --x-->		7 -> 5 (-2)
			topleft --y-->		7 -> 1 (+2)

			[ 규칙 ]
			topRight, bottomLeft --(x)--> +2
			topRight, bottomLeft --(y)--> -2

			bottomRight, topLeft --(x)--> -2
			bottomRight, topLeft --(y)--> +2

			top,right,bottom,left ----> +4
		*/
		void ReflectX();									// x축에 부딪혔을때
		void ReflectY();									// y축에 부딪혓을때
		void MoveTop();										// 상
		void MoveTopRight();								// 상-우
		void MoveRight();									// 우
		void MoveBottomRight();								// 하-우
		void MoveBottom();									// 하
		void MoveBottomLeft();								// 하-좌
		void MoveLeft();									// 좌
		void MoveTopLeft();									// 상-좌
		void Update();										// 객체의 좌표값 업데이트
		void Render(HDC hdc);								// 객체 화면에 그려주기
		__forceinline bool ConditionMaxX() { return x1 < 0 || x1 > FHD_X || x2 < 0 || x2 > FHD_X; }	// FHD 너비 벗어남에 대한 조건
		__forceinline bool ConditionMaxY() { return y1 < 0 || y1 > FHD_Y || y2 < 0 || y2 > FHD_Y; }	// FHD 높이 벗어남에 대한 조건
		__forceinline bool NoneReflection() { return isReflect == false; }							// 반사인지 아닌지에 대한 조건
		
	private:
		float x1;		// 1번 좌표의 x값
		float y1;		// 1번 좌표의 y값
		float x2;		// 2번 좌표의 x값
		float y2;		// 2번 좌표의 y값
		int directNum;	// 움직이는 방향
		float speed;	// 객체의 움직이는 속도 (초당 움직이는 거리)
		float delta;	// 델타 타임
		bool isReflect;	// 반사여부 확인
	};
}

