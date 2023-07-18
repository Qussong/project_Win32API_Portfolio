#pragma once

#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
/*
	[ windows.h ]
	-	Windows 헤더 파일
	-	C/C++언어로 Win32 API를 사용할 때 포함해야 할 여러가지 헤더파일이 있는데 
		개발 편의를 위해 windows.h 파일만 포함하면 기본적인 Win32 API 기능을 사용할 수 있도록 
		여러 헤더 파일을 해당 헤더파일에 포함하고 있다.
*/
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// GDI+
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")