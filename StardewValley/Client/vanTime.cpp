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
		// 프레임당 진동수를 알아야 한다
		// 현재 진동수는 다음 프레임에선 이전의 진동수가 되기에 'Prev = Cur' 을 해준다
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		const int SIZE = 50;
		static float timeCheck = 0.0f;						// 델타타임 쌓는 곳

		timeCheck += mDeltaTime;							// 매 프레임마다 델타타임이 누적된다.
		if (timeCheck >= 1.0f)								// 총 델타 타임이 1초 이상이 되면 아래 로직 수행
		{
			wchar_t szFloat[SIZE] = {};						// ???
			float FPS = 1.0f / mDeltaTime;					// 누적 델타 타임이 1초 이상이 되는 순간의 FPS 출력

			// Question) 위의 방식대로 FPS를 출력하면 결국 평균 FPS를 출력하는건 아닌거죠?
			swprintf_s(szFloat, SIZE, L"FPS : %f", FPS);	// ???
			int strLen = wcsnlen_s(szFloat, SIZE);			// ???, szFloat 의 무자열 길이를 받아오는 것 같다...

			TextOut(hdc, 10, 10, szFloat, strLen);			// 화면에 값 출력?

			timeCheck = 0.0f;								// 다시 0부터 1초가 될때까지 
															// 델타타임들을 받아야 하기에 0으로 초기화
		}
	}
}
