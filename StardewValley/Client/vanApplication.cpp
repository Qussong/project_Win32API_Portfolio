#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가
#include "vanTime.h"		// Update에서 Time 개념 사용하기 위해 추가

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		//, mWidth(0)
		//, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
		, mScene(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);				// WinUser.h

		//mWidth = 1600;					// FHD_X 로 대체
		//mHeight = 900;					// FHD_Y 로 대체

		RECT rect = { 0,0, FHD_X, FHD_Y };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, 
					nullptr,0, 0,
					rect.right - rect.left,
					rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);

		// 윈도우 해상도 동일한 비트맵 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, FHD_X, FHD_Y);

		// 새로 생성한 비트맵을 가리키는 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		// 새로 생성한 비트맵과 DC를 서로 연결
		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);	// 이때 DC가 가지고 있던 기본 비트맵이 반환된다.
		DeleteObject(defaultBitmap);						// 반환된 기본 비트맵은 사용할 일이없기에 메모리 해제

		Time::Init();
		Input::Init();						// Init()함수가 Input 클래스에 속한 static 멤버기에 가능함

		mScene = new Scene();				//
		mScene->Init();						//
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		// 키 입력 받기_ver1
		/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			playerPos.x -= 0.02f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			playerPos.x += 0.02f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			playerPos.y -= 0.02f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			playerPos.y += 0.02f;
		}*/
		// 키 입력 받기_ver2
		Input::Update();
		/*
			//W,S,A,D 로 상,하,좌,우 방향 값을 확인한다.
			//GetKey()함수의 인자로 들어간 키의 멤버값(state)을 확인하여 해당하는 값들을 수정한다.
		if (Input::GetKey(eKeyCode::W))	// 상
		{
			
			//기존에는 시간에 대한 개념이 없었기에 프레임당 이동해야할 거리를 넣어줬지만,
			//이젠 시간 개념이 들어갔기에 1초당 이동거리를 넣어주게 된다.
			//
			//증명)
			//	CPU 성능에 상관 없이 일정한 이동거리
			//	= 이동거리 * 델타타임 * FPS 
			//	= 이동거리 * 델타타임 * (1 sec / 델타타임)
			//	= 이동거리 * 1 sec
			//	= 일정한 이동거리 [sec]
			
			if (playerPos.y > 0)
				playerPos.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// 하
		{
			if (playerPos.y < mHeight - DIAMETER)
				playerPos.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// 좌
		{
			if (playerPos.x > 0)
				playerPos.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// 우
		{
			if (playerPos.x < mWidth - DIAMETER)
				playerPos.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}*/
		// 키 입력 받기_ver3 + 각 객체들 정보 업데이트
		mScene->Update();
	}

	void Application::Render()
	{
		Time::Render(mBackHdc);

		Rectangle(mBackHdc, -1, -1, FHD_X + 1, FHD_Y + 1);			// 2번째 비트맵에 큰 사각형을 그려준다.
																	// 양옆으로 1씩 넓은 사각형을 쓰는 이유 : 
																	//		테두리 선이 보이기 때문에 안 보이게 하려고
		// 객체 화면 출력_ver1
				/*Ellipse(mBackHdc, playerPos.x, playerPos.y,
				playerPos.x + DIAMETER, playerPos.y + DIAMETER);*/
		// 각 객체들 정보 화면 출력_ver2
		mScene->Render(mBackHdc);	

		BitBlt(mHdc, 0, 0, FHD_X, FHD_Y, mBackHdc, 0, 0, SRCCOPY);	// 2번 비트맵(mBackHdc)을 1번 비트맵(mHdc)에 복사한다.
	}
}
