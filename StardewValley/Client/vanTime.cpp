#include "vanTime.h"

namespace van
{
	// LARGE_INTEGER 구조체 이기에 {} 로 초기화
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time::Init()
	{
		// CPU의 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);
		// 프로그램이 시작됐을때의 진동수 를 가져온다
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		// 현재 진동수를 가져온다.
		QueryPerformanceCounter(&mCurFrequency);
		// 진동수 차이
		// 즉, 한 프레임이 진행되는 동안 CPU가 진동한 횟수
		float diffFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = diffFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		// 델타타임 = 매 프레임당 진동수 / 1초 평균 진동수
		// 프레임당 진동수를 알아야 한다
		// 현재 진동수는 다음 프레임에선 이전의 진동수가 되기에 'Prev = Cur' 을 해준다
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		const int SIZE = 50;
		//static float timeCheck = 0.0f;
		//timeCheck += mDeltaTime;					
		//if (timeCheck >= 1.0f)								
		//{
			wchar_t szFloat[SIZE] = {};
			float FPS = 1.0f / mDeltaTime;

			swprintf_s(szFloat, SIZE, L"FPS : %f", FPS);	// Buffer(szFloat)에 문자열 넣어주기
			int strLen = (int)wcsnlen_s(szFloat, SIZE);		// 문자열 길이
			TextOut(hdc, 10, 10, szFloat, strLen);
			//timeCheck = 0.0f;								
		//}
	}
}
