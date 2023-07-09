#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC\

namespace van
{
	class Text
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC hdc);
		static void PrintwString(HDC _hdc, int _x, int _y, wchar_t const* const _Format);

	private:

	};
}