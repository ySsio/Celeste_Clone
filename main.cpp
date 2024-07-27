// GameEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "CEngine.h"
#include "CUIMgr.h"
#include "CTextBoxUI.h"

#define MAX_LOADSTRING 100

// 전역 변수:
extern HINSTANCE hInst = nullptr;                                // 현재 인스턴스입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Editor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Editor_Img(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Editor_Bg_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Editor_Game_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Editor_Bg_Obj(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Editor_Game_Obj(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Editor_Name(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

extern HWND hEdit;
extern HWND hEdit_Img;
extern HWND hEdit_BG_Tile;
extern HWND hEdit_Game_Tile;
extern HWND hEdit_BG_OBJ;
extern HWND hEdit_Game_OBJ;
extern HWND hEdit_Name;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 메모리 누수 체크 - 프로그램 종료되면 콘솔에 메모리 누수 내역 나옴
    // shift+f5로 디버깅 종료하는 경우는 안나오니까 프로세스 정상종료 했을 떄 확인
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 메모리 누수 남으면 메모리 누수 남은 부분 숫자가 콘솔에 나오는데 그걸 밑에 매크로 함수 입력으로 넣어주면
    // 해당 메모리 누수 난 코드에 break 걸림
    //_CrtSetBreakAlloc(85730);

    MyRegisterClass(hInstance);

    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(L"MAIN_ENGINE", L"Celeste", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    hEdit           = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT), CEngine::Get()->GetMainHwnd(), &Editor);
    hEdit_Img       = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_IMG), CEngine::Get()->GetMainHwnd(), &Editor_Img);
    hEdit_BG_Tile   = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_BG_TILE), CEngine::Get()->GetMainHwnd(), &Editor_Bg_Tile);
    hEdit_Game_Tile = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_GAME_TILE), CEngine::Get()->GetMainHwnd(), &Editor_Game_Tile);
    hEdit_BG_OBJ    = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_BG_OBJ), CEngine::Get()->GetMainHwnd(), &Editor_Bg_Obj);
    hEdit_Game_OBJ  = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_GAME_OBJ), CEngine::Get()->GetMainHwnd(), &Editor_Game_Obj);
    hEdit_Name      = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDIT_NAME), CEngine::Get()->GetMainHwnd(), &Editor_Name);

    if (!hWnd)
    {
        return FALSE;
    }


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    CEngine::Get()->Init(hWnd,1600,920);

    MSG msg = {};

    // 기본 메시지 루프입니다:
    while (true)
    {
        // 이거 윈도우 핸들 왜 nullptr 넣어줘야 되는거냐..?
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            CEngine::Get()->Progress();
        }

    }

    return (int) msg.wParam;
}



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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"MAIN_ENGINE";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

    return RegisterClassExW(&wcex);
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
        case IDM_EXIT:
        {
            DestroyWindow(hWnd);
            DestroyWindow(hEdit);
            DestroyWindow(hEdit_BG_Tile);
            DestroyWindow(hEdit_Game_Tile);
            DestroyWindow(hEdit_BG_OBJ);
            DestroyWindow(hEdit_Game_OBJ);
            DestroyWindow(hEdit_Name);
        }
            break;
        case ID_MAP_EDIT:
        {
            ShowWindow(hEdit, SW_SHOW);
        }

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
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
        break;

    case WM_CHAR:
    {
        if (!(wParam >= 32 && wParam <= 126))
            break;

        CTextBoxUI* pTextBoxUI = CUIMgr::Get()->GetActivatedTextBox();

        if (pTextBoxUI)
            pTextBoxUI->AddChar(wParam);
    }
        break;
    case WM_IME_CHAR:
    {
        CTextBoxUI* pTextBoxUI = CUIMgr::Get()->GetActivatedTextBox();

        if (pTextBoxUI)
            pTextBoxUI->AddChar(wParam);
    }
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
