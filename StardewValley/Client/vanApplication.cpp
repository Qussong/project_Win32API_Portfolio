#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가

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

		Input::Init();			// Input::eKeys에 들어갈 Key 구조체의 객체들을 생성하여 넣어준다.
								// Init()함수가 Input 클래스에 속한 static 멤버기에 가능함
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
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
		Input::Update();	// 매 프레임마다 키 상태를 확인하고 업데이트 시켜준다.

		// W,S,A,D 로 상,하,좌,우 방향 값을 확인한다.
		// GetKey()함수의 인자로 들어간 키의 멤버값(state)을 확인하여 해당하는 값들을 수정한다.
		if (Input::GetKey(eKeyCode::W))
		{
			playerPos.y -= 0.02f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			playerPos.x -= 0.02f;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			playerPos.y += 0.02f;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			playerPos.x += 0.02f;
		}
	}

	void Application::Render()
	{
		Ellipse(mHdc, 100 + playerPos.x, 100 + playerPos.y
			, 200 + playerPos.x, 200 + playerPos.y);
	}
}
