#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC

namespace van
{
	class Paint
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC hdc);

	private:

	};
}