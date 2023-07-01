// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.

//#include "framework.h"                    // "vanApplication.h"에 들어있다.
#include "Client.h"
#include "vanApplication.h"                 // 필요기능 구현,추가

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                            // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];              // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];        // 기본 창 클래스 이름입니다.
van::Application application;               // 하나뿐인 객체

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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
    */

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

    return (int) msg.wParam;
}

//  함수: MyRegisterClass()
//  역할: 창 클래스를 등록하고 설정한다.
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
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);   // 커서모양
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);         // 백그라운드 색
    wcex.lpszMenuName   = /*MAKEINTRESOURCEW(IDC_CLIENT)*/0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//  함수 : InitInstance(HINSTANCE, int)
//  역할 : 
//      - 한줄 요약 : 인스턴스 핸들을 전역변수에 저장하고 주 창을 만듭니다.
//      - 인스턴스 핸들을 전역 변수에 저장하고 ( hInst = hInstance )
//      - 주 프로그램 창(=윈도우)을 만든 다음 표시합니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(/*szWindowClass*/L"CLIENT", szTitle/*L"Client"*/, WS_OVERLAPPEDWINDOW,
      0/*CW_USEDEFAULT*/, 0, FHD_X/*CW_USEDEFAULT*/, FHD_Y, nullptr, nullptr, hInstance, nullptr);

   application.Init(hWnd);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  역할: 
//      주 창의 메시지를 처리합니다.
//      WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//      WM_PAINT    - 주 창을 그립니다.
//      WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
            //Ellipse(hdc, 100, 100, 300, 300);

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

// 정보 대화 상자의 메시지 처리기입니다.
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