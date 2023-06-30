#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가
#include "vanTime.h"		// Update에서 Time 개념 사용하기 위해 추가

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);	// WinUser.h

		Time::Init();
		Input::Init();			// Init()함수가 Input 클래스에 속한 static 멤버기에 가능함
								
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

		// W,S,A,D 로 상,하,좌,우 방향 값을 확인한다.
		// GetKey()함수의 인자로 들어간 키의 멤버값(state)을 확인하여 해당하는 값들을 수정한다.
		if (Input::GetKey(eKeyCode::W))
		{
			//playerPos.y -= 0.02f;
			/*
				기존에는 시간에 대한 개념이 없었기에 프레임당 이동해야할 거리를 넣어줬지만,
				이젠 시간 개념이 들어갔기에 1초당 이동거리를 넣어주게 된다.

				증명)
					CPU 성능에 상관 없이 일정한 이동거리
					= 이동거리 * 델타타임 * FPS 
					= 이동거리 * 델타타임 * (1 sec / 델타타임)
					= 이동거리 * 1 sec
					= 일정한 이동거리 [sec]
			*/
			playerPos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//playerPos.x -= 0.02f;
			playerPos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//playerPos.y += 0.02f;
			playerPos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			//playerPos.x += 0.02f;
			playerPos.x += 300.0f * Time::DeltaTime();
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, 100 + playerPos.x, 100 + playerPos.y
			, 200 + playerPos.x, 200 + playerPos.y);
	}
}
