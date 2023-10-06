// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.

//#include "framework.h"                    // "vanApplication.h"에 들어있다.
#include "Client.h"
#include "vanApplication.h"                 // 필요기능 구현,추가
// 메모리 누수 확인
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "vanResourceManager.h"
#include "vanSceneManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                            // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];              // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];        // 기본 창 클래스 이름입니다.

van::Application application;               // 실질적인 게임 객체
ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,          
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // 메인함수 호출시 들어오는 hPrevInstance 변수가 사용되지 않음을 표현
    UNREFERENCED_PARAMETER(lpCmdLine);      // 위와 동일

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(14199);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);     // IDS_APP_TITLE 값을 szTitle에 넣어줌
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);  // IDC_CLIENT 값을 szWindowClass에 넣어줌
    MyRegisterClass(hInstance);                                         // 생성될 윈도우에 대한 정보를 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // GetMessage : 
                  /* 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
                  msg.message == WM_QUIT 인 경우 return false;
                  WM_QUIT 이외의 메세지가 발생 한 경우는 return true; */ 
    // PeekMessage : 
                  /* 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
                  PM_REMOVE -> 발생한 메세지를 가져올 때 메세지큐에서 제거 (GetMessage 랑 동일하게 하기 위해서...)
                  메세지큐에 메세지 유/무 에 상관없이 함수가 리턴됨 */
    // 게임 구동시 필요한 메세지 루프 구조
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 로직 실행
            application.Proc();
        }
    }

    if (msg.message == WM_QUIT)
    {
        
    }

    application.Release();
    van::SceneManager::Release();
    van::ResourceManager::Release();

    _CrtDumpMemoryLeaks();  // 종료지점 바로 위에서 호출

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);               // 커서모양
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1/*BLACK_PEN*/);        // 백그라운드 색
    wcex.lpszMenuName   = /*MAKEINTRESOURCEW(IDC_CLIENT)*/nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 인도우 창 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, Window_X, Window_Y, nullptr, nullptr, hInstance, nullptr);

   Gdiplus::GdiplusStartup(&gdiplusToken, 
                &gdiplusStartupInput, NULL); // Gdiplus 초기화
   application.Init(hWnd);                   // van::Application 객체 초기화

   if (!hWnd)
      return FALSE;

   //ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:  // "상단 바 -> 메뉴 -> 끝내기"시 발생하는 메세지
                DestroyWindow(hWnd);    
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가
            //Rectangle(hdc, 100, 100, 300, 300);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:    // 윈도우 종료시 발생하는 메세지
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}