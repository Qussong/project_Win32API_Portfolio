#include "vanApplication.h"

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

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);	// WinUser.h	
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			//playerPos.x -= 0.01f;
			playerPos.x -= 0.02f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//playerPos.x += 0.01f;
			playerPos.x += 0.02f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			//playerPos.y -= 0.01f;
			playerPos.y -= 0.02f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			//playerPos.y += 0.01f;
			playerPos.y += 0.02f;
		}
	}

	void Application::Render()
	{
		Ellipse(mHdc, 100 + playerPos.x, 100 + playerPos.y
			, 200 + playerPos.x, 200 + playerPos.y);
	}
}
