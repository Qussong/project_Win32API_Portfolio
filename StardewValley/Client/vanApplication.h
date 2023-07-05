#pragma once
#include "CommonInclude.h"
#include "vanScene.h"

namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();							// 전체적인 작업 (Update, Render)
		void Update();							// 키 입력을 받아 데이터 수정
		void Render();							// 화면에 그려준다

	private:
		HWND mHwnd;
		HDC mHdc;

		//UINT mWidth;
		//UINT mHeight;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		math::Vector2 playerPos;				// vanMath.h

		Scene* mScene;
	};
}

