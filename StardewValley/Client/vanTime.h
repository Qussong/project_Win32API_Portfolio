#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC

namespace van
{
	class Time
	{
	public:
		static void Init();
		static void Update();					// 현재 프레임의 델타 타임을 구해서 mDeltaTime에 대입
		static void Render(HDC hdc);
		__forceinline static float DeltaTime() { return mDeltaTime; }

	private:
		static LARGE_INTEGER mCpuFrequency;		// CPU의 고유진동수 저장
		static LARGE_INTEGER mPrevFrequency;	// 프로그램 실행시 진동수, 기준 진동수
		static LARGE_INTEGER mCurFrequency;		// 현재 진동수
		static float mDeltaTime;				// 델타타임(deltaTime) = 한 프레임에 걸린 시간 = (Cur-Prev)/Cpu 
	};
}

