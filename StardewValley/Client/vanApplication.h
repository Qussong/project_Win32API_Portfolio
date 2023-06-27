#pragma once
#include "CommonInclude.h"

namespace van
{
	using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;
		Vector2 playerPos;	// vanMath.h
	};
}

