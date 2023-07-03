#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가
#include "vanTime.h"		// Update에서 Time 개념 사용하기 위해 추가

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, obj{}
		, objs{}
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);										// WinUser.h

		Time::Init();
		Input::Init();												// Init()함수가 Input 클래스에 속한 static 멤버기에 가능함

		// obj
		obj = Object(300, 300, 500, 500);							// 움직이는 객체의 크기 세팅
		obj.setDirNum();											// 움직이는 객체의 첫 이동 방향 세팅
		obj.setSpeed(200.0f);										// 움직이는 객체의 속도 세팅

		// objs
		randomize();												// 난수 생성을 위한 준비
		for (int i = 0; i < OBJECT_CNT; ++i)
		{
			int size = (i+1) * 100;			
			objs[i] = Object(size, size, size + 100, size + 100);	// 여러 움직일 객체의 크기 세팅
			objs[i].setDirNum2(random(DIRECTION_CNT));				// 여러 움직일 객체의 첫 이동 방향 세팅
			objs[i].setSpeed(250.0f);								// 여러 움직일 객체의 속도 세팅
		}
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

		// obj
		obj.setDelta(Time::DeltaTime());			// 움직일 객체의 델타타임 세팅
		obj.Update();								// 매 프레임당 움직일 객체의 좌표 세팅

		// objs
		for (int i = 0; i < OBJECT_CNT; ++i)
		{
			objs[i].setDelta(Time::DeltaTime());	// 여러 움직일 객체의 델타타임 세팅
			objs[i].Update();						// 매 프레임당 여러 움직일 객체의 좌표 세팅
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, 100.0f + playerPos.x, 100.0f + playerPos.y
			, 200.0f + playerPos.x, 200.0f + playerPos.y);

		// obj
		obj.Render(mHdc);							// 움직일 객체의 화면 출력

		// objs
		for (int i = 0; i < OBJECT_CNT; ++i)
			objs[i].Render(mHdc);					// 여러 움직일 객체의 화면 출력
	}
}
