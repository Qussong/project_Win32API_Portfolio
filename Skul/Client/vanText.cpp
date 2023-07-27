#include "vanText.h"

namespace van
{
	void Text::Init()
	{
	}

	void Text::Update()
	{
	}

	void Text::Render(HDC hdc)
	{
	}

	void Text::PrintwString(HDC _hdc, int _x, int _y, wchar_t const * const _Format)
	{
		const int SIZE = 50;							// Buffer 크기
		wchar_t szFloat[SIZE] = {};						// Buffer
		swprintf_s(szFloat, SIZE, _Format);				// Buffer에 값 넣어주기
		int strLen = (int)wcsnlen_s(szFloat, SIZE);		// 문잘열의 길이
		TextOut(_hdc, _x, _y, szFloat, strLen);			// 출력
	}
}
