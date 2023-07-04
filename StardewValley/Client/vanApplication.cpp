#include "vanApplication.h"
#include "vanInput.h"		// Update에서 key값에 대한 처리를 해주기위해 추가
#include "vanTime.h"		// Update에서 Time 개념 사용하기 위해 추가

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, clientArea{}
		, curObjectCnt(0)
	{
		
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);			// WinUser.h

		randomize();

		Time::Init();
		Input::Init();					// Init()함수가 Input 클래스에 속한 static 멤버기에 가능함
		GetClientRect(mHwnd, &clientArea);
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		// objs
		ObjectGenerator(300.0f, 100, 2.0f);
		for (int i = 0; i < curObjectCnt; ++i)
		{
			objectContainer.at(i).Update();
			objectContainer.at(i).setDelta(Time::DeltaTime());
		}
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
		if (Input::GetKey(eKeyCode::W))	// 상
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
			if (playerPos.y > 0)
				playerPos.y -= 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// 하
		{
			//playerPos.y += 0.02f;
			if (playerPos.y < /*FHD_Y*/clientArea.bottom - 100)
				playerPos.y += 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// 좌
		{
			//playerPos.x -= 0.02f;
			if (playerPos.x > 0)
				playerPos.x -= 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// 우
		{
			//playerPos.x += 0.02f;
			if (playerPos.x < /*FHD_X*/clientArea.right - 100)
				playerPos.x += 300.0f * Time::DeltaTime();
			else
				__noop;
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, playerPos.x, playerPos.y,
				playerPos.x + 100.0f, playerPos.y + 100.0f);

		// objs
		for (int i = 0; i < curObjectCnt; ++i)
			objectContainer.at(i).Render(mHdc);		// 여러 움직일 객체의 화면 출력
	}

	void Application::ObjectGenerator(float speed, int diameter, float timeGap)
	{
		static float timeCheck = 0.0f;					// 델타타임 쌓는 곳
		timeCheck += Time::DeltaTime();
		int posX = random(clientArea.right - diameter);			// 객체가 생성될 기준 x좌표
		int posY = random(clientArea.bottom - diameter);			// 객체가 생성될 기준 y좌표
		int cnt = curObjectCnt;							// 현재 생성된 움직이는 객체의 개수
		int totalCnt = OBJECT_CNT;

		while (cnt < totalCnt && timeCheck >= timeGap)
		{
			Object obj = 
				Object(mHwnd, posX, posY, posX + diameter, posY + diameter);	// 여러 움직일 객체의 크기 세팅
			obj.setDirNum2(random(DIRECTION_CNT));						// 여러 움직일 객체의 첫 이동 방향 세팅
			obj.setSpeed(speed);										// 여러 움직일 객체의 속도 세팅
			objectContainer.push_back(obj);

			++curObjectCnt;
			timeCheck = 0.0f;
		}
	}
}
