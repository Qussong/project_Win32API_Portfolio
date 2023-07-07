#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가
#include "vanTime.h"		// Update에서 Time 개념 사용하기 위해 추가

#include "vanSceneManager.h"

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		//, mWidth(0)
		//, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd) 
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);									// WinUser.h
		//mWidth = 1600;										// FHD_X 로 대체
		//mHeight = 900;										// FHD_Y 로 대체

		RECT rect = { 0, 0, FHD_X, FHD_Y };						// 현재 윈도우 크기 
																//	-> 해당 크기가 클라이언트 영역의 크기가 되길 원함
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// 현재 윈도우의 크기가 클라이언트 영역이 되도록 크기를 조정

		// rect 변수의 정보를 기반으로 윈도우 사이즈 세팅
		SetWindowPos(mHwnd, nullptr,
					0, 0,										// 변경할 위치 (x,y)
					rect.right - rect.left,						// 변경할 크기(가로)
					rect.bottom - rect.top,						// 변경할 크기(세로)
					0);											// ?
		ShowWindow(mHwnd, true);								// CreateWindow()함수에 의해 할당된 메모리를 화면에 출력

		mBackBuffer 
			= CreateCompatibleBitmap(mHdc, FHD_X, FHD_Y);		// 윈도우 해상도 동일한 비트맵 생성

		mBackHdc = CreateCompatibleDC(mHdc);					// 새로 생성한 비트맵을 가리키는 DC 생성

		HBITMAP defaultBitmap									// 새로 생성한 비트맵과 DC를 서로 연결
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);		// 이때 DC가 가지고 있던 기본 비트맵이 반환된다.
		DeleteObject(defaultBitmap);							// 반환된 기본 비트맵은 사용할 일이없기에 메모리 해제

		Time::Init();
		Input::Init();											
		SceneManager::Init();
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		/*	
			2번째 비트맵에 큰 사각형을 그려준다.
			양옆으로 1씩 넓은 사각형을 쓰는 이유 : 
			테두리 선이 보이기 때문에 안 보이게 하려고
		*/
		Rectangle(mBackHdc, -1, -1, FHD_X + 1, FHD_Y + 1);			
		Time::Render(mBackHdc);

		SceneManager::Render(mBackHdc);
		// 2번 비트맵(mBackHdc)을 1번 비트맵(mHdc)에 복사한다.
		BitBlt(mHdc, 0, 0, FHD_X, FHD_Y,
				mBackHdc, 0, 0, SRCCOPY);	
	}
}
