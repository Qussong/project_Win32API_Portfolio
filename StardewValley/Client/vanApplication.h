#pragma once
#include "CommonInclude.h"

namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();				// 전체적인 작업 (Update, Render)
		void Update();				// 키 입력을 받아 데이터 수정
		void Render();				// 화면에 그려준다

		__forceinline HWND GetHwnd() { return mHwnd; }
		__forceinline HDC GetHdc() { return mHdc; }
		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline UINT GetHeight() { return mHeight; }

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;				// 클라이언트 영역 너비
		UINT mHeight;				// 클라이언트 영역 높이

		HDC mBackHdc;
		HBITMAP mBackBuffer;
	};
}