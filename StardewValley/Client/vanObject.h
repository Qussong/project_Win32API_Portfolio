#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC

namespace van
{
	const float SPEED = 0.1f;

	enum class Direction
	{
		Top,		// 0
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight	// 7
	};

	class Object
	{
	public:
		Object();
		Object(int _x1, int _y1, int _x2, int y2);
		void Init();
		void Update();
		void Render(HDC hdc);
		void setDelta(float _delta);

		// ╩С
		__forceinline void MoveTop() { y1 -= SPEED * delta; y2 -= SPEED * delta; }
		// го
		__forceinline void MoveBottom() { y1 += SPEED * delta; y2 += SPEED * delta; }
		// аб
		__forceinline void MoveLeft() { x1 -= SPEED * delta; x2 -= SPEED * delta; }
		// ©Л
		__forceinline void MoveRight() { x1 += SPEED * delta; x2 += SPEED * delta; }
		// ╩Саб
		__forceinline void MoveTopLeft() { x1 -= SPEED * delta; y1 -= SPEED * delta; x2 -= SPEED * delta; y2 -= SPEED * delta; }
		// ╩С©Л
		__forceinline void MoveTopRight() { x1 += SPEED * delta; y1 -= SPEED * delta; x2 += SPEED * delta; y2 -= SPEED * delta; }
		// гоаб
		__forceinline void MoveBottomLeft() { x1 -= SPEED * delta; y1 += SPEED * delta; x2 -= SPEED * delta; y2 += SPEED * delta; }
		// го©Л
		__forceinline void MoveBottomRight() { x1 += SPEED * delta; y1 += SPEED * delta; x2 += SPEED * delta; y2 += SPEED * delta; }

	private:
		// Rectangle(hdc, 100, 100, 300, 300);
		// Ellipse(hdc, 100, 100, 300, 300);
		int x1;
		int y1;
		int x2;
		int y2;
		int directNum;
		float delta;
	};
}

