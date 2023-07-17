﻿// WinSong.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "pch.h"
#include "WinSong.h"
#include "CCore.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND    g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//윈도우 메인함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //메모리 누수 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //_crtSetBreakAlloc(): 에러난부분 중단점을 걸어줌.
    // _CrtSetBreakAlloc(497);


   


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.



    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINSONG, szWindowClass, MAX_LOADSTRING);

    //윈도우 정보 등록
    MyRegisterClass(hInstance);

    //윈도우 생성
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }


    //단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINSONG));

    MSG msg;

    // GetMessage
    // 메세지큐에서 메세지 확인될 때까지 대기 (종료되지 않음)
    //msg.message == WM_QUIT 일때 false 반환 -> 프로그램 종료
     
    // 기본 메시지 루프입니다:
    //화면에 들어오는 메세지를 반복문을 돌면서 처리해줌

   //PeekMessage
    //메세지 유무와 관계없이 반환
    //메세지큐에서 메세지를 확인한 경우 true, 메세지큐에서 메세지가 없는 경우 false를 반환

    //GetTickCount() : 윈도우에서 시간을 알려주는 함수
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
            // Game 코드 수행
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴

            CCore::GetInst()->progress();
        }
    }

    return (int) msg.wParam;
}

int g_x = 0;
int g_y = 0;

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100,100 };

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINSONG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_WINSONG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
            case ID_MENU_TILE:
            {
                INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);

                if (iRet == IDOK)
                {

                }
               
            }  
                 break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  //무효화 영역(Invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;

            //Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);    //Device Context(그리기)
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //Rectangle(hdc,1180, 668, 1280, 768);
           
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
       
    }
    break;

    case WM_LBUTTONDOWN: //마우스 좌표 확인 가능
   
      break;
    
    case WM_MOUSEMOVE:

        break;

    case WM_LBUTTONUP:
   
       
    break;

    case WM_DESTROY:
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
