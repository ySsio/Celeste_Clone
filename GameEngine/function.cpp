#include "pch.h"
#include "function.h"
#include "CDebugMgr.h"
#include "CTaskMgr.h"
#include "CCamera.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"

#ifdef _DEBUG
void Debug_Render(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush, Vec2 _Pos, Vec2 _Scale, float _Duration)
{
	tDebugShapeInfo tDebug{};
	tDebug.Shape = _Shape;
	tDebug.Pen = _Pen;
	tDebug.Brush = _Brush;
	tDebug.Position = _Pos;
	tDebug.Scale = _Scale;
	tDebug.Duration = _Duration;
	tDebug.AccTime = 0.f;

	CDebugMgr::Get()->AddDebugShape(tDebug);
}
#endif

Vec2 GetRenderPosFromCam(Vec2 _Pos)
{
    return CCamera::Get()->GetRenderPos(_Pos);
}

void Pause_Game()
{
    CGameMgr::Get()->PauseGame();
    CTimeMgr::Get()->PauseTimer();
}

void Release_Game()
{
    CGameMgr::Get()->ReleaseGame();
    CTimeMgr::Get()->ReleaseTimer();
}

void Change_Level(LEVEL_TYPE _Type)
{
	tTask task{};
	task.TaskType = TASK_TYPE::CHANGE_LEVEL;
	task.wParam = (DWORD_PTR)_Type;

	CTaskMgr::Get()->AddTask(task);
}

void Reset_Level()
{
    tTask task{};
    task.TaskType = TASK_TYPE::RESET_LEVEL;

    CTaskMgr::Get()->AddTask(task);
}

void Move_Room(int _Room)
{
    tTask task{};
    task.TaskType = TASK_TYPE::MOVE_ROOM;
    task.wParam = (DWORD_PTR)_Room;

    // Game매니저에는 한 프레임 먼저 미리 옮길 Room을 알려줌
    CGameMgr::Get()->SetRoom(_Room);

    CTaskMgr::Get()->AddTask(task);
}

void Add_Object(CObj* _Obj, LAYER_TYPE _Type)
{
    tTask task{};
    task.TaskType = TASK_TYPE::CREATE_OBJECT;
    task.wParam = (DWORD_PTR)_Obj;
    task.lParam = (DWORD_PTR)_Type;

    CTaskMgr::Get()->AddTask(task);
}


void Delete_Object(CObj* _Obj)
{
    tTask task{};
    task.TaskType = TASK_TYPE::DELETE_OBJECT;
    task.wParam = (DWORD_PTR)_Obj;

    CTaskMgr::Get()->AddTask(task);
}

void FillAlphaNonZeroAreas(HBITMAP hBitmap, COLORREF rgba)
{
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap); // 비트맵 정보 가져오기

    // 비트맵과 호환되는 메모리 DC 생성
    HDC hdcMem = CreateCompatibleDC(NULL);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

    // 비트맵의 픽셀 데이터 가져오기
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bitmap.bmWidth;
    bmi.bmiHeader.biHeight = -bitmap.bmHeight; // 상하 반전
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32비트 비트맵 (ARGB)

    // 픽셀 데이터 저장할 버퍼 할당
    BYTE* pBits = new BYTE[bitmap.bmWidth * bitmap.bmHeight * 4];

    // 픽셀 데이터 가져오기
    GetDIBits(hdcMem, hBitmap, 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

    // RGBA 분리
    BYTE r = GetRValue(rgba);
    BYTE g = GetGValue(rgba);
    BYTE b = GetBValue(rgba);
    BYTE a = (BYTE)(rgba >> 24); // 알파 값 추출

    // 알파 값이 0이 아닌 부분을 지정된 RGBA 값으로 채우기
    for (int y = 0; y < bitmap.bmHeight; ++y) {
        for (int x = 0; x < bitmap.bmWidth; ++x) {
            int index = (y * bitmap.bmWidth + x) * 4;
            BYTE alpha = pBits[index + 3]; // 알파 값

            if (alpha != 0) {
                pBits[index + 0] = b; // B
                pBits[index + 1] = g; // G
                pBits[index + 2] = r; // R
                pBits[index + 3] = a; // A
            }
        }
    }

    // 수정된 픽셀 데이터를 비트맵에 설정
    SetDIBits(hdcMem, hBitmap, 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

    // 메모리 해제
    delete[] pBits;
    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
}

Vec2 cubicBezier(Vec2 P0, Vec2 P1, Vec2 P2, Vec2 P3, float t)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Vec2 point = (P0 * uuu) + (P1 * 3 * uu * t) + (P2 * 3 * u * tt) + (P3 * ttt);

    return point;
}

float easeInOut(float t)
{
    if (t < 0.5) {
        return 2 * t * t; // Ease In
    }
    else {
        return 1 - 2 * (1 - t) * (1 - t); // Ease Out
    }
}
