#include "pch.h"
#include "CEngine.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CCamera.h"
#include "CCollisionMgr.h"
#include "CDebugMgr.h"
#include "CTaskMgr.h"
#include "CUIMgr.h"
#include "CLogMgr.h"
#include "CSoundMgr.h"
#include "CGameMgr.h"

CEngine::CEngine()
	: m_MainHwnd(nullptr)
	, m_MainDC(nullptr)
	, m_ArrPen{}
	, m_ArrBrush{}
	, m_BackBufferDC(nullptr)
	, m_BackBuffer(nullptr)
{

}

CEngine::~CEngine()
{
	for (auto& pen : m_ArrPen)
	{
		DeleteObject(pen);
	}

	for (auto& brush : m_ArrBrush)
	{
		DeleteObject(brush);
	}

	DeleteDC(m_BackBufferDC);
	DeleteObject(m_BackBuffer);
}


void CEngine::CreateGDIObject()
{
	m_ArrPen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_ArrPen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_ArrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_ArrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_ArrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_ArrPen[(UINT)PEN_TYPE::ORANGE] = CreatePen(PS_SOLID, 3, RGB(255, 127, 39));

	DWORD dashStyles[2] = { 10, 10 }; // 15 픽셀 선, 10 픽셀 간격
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(97, 55, 54);
	m_ArrPen[(UINT)PEN_TYPE::RED_DASH] = ExtCreatePen(PS_GEOMETRIC | PS_USERSTYLE, 5, &lb, 2, dashStyles);

	m_ArrBrush[(UINT)BRUSH_TYPE::WHITE] = CreateSolidBrush(RGB(255, 255, 255));
	m_ArrBrush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(RGB(0, 0, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_ArrBrush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(180, 180, 180));
	m_ArrBrush[(UINT)BRUSH_TYPE::COZY_GREEN] = CreateSolidBrush(RGB(180, 212, 145));
	m_ArrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_ArrBrush[(UINT)BRUSH_TYPE::BANG_BLUE] = CreateSolidBrush(RGB(95, 205, 228));
	m_ArrBrush[(UINT)BRUSH_TYPE::BANG_RED] = CreateSolidBrush(RGB(172, 50, 50));
	m_ArrBrush[(UINT)BRUSH_TYPE::BANG_PINK] = CreateSolidBrush(RGB(249, 149, 221));
}

void CEngine::ChangeWindowResolution()
{
	ChangeWindowResolution((UINT)m_Resolution.x, (UINT)m_Resolution.y);
}

void CEngine::ChangeWindowResolution(UINT _Width, UINT _Height)
{
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	RECT rt{ 0, 0, (LONG)_Width, (LONG)_Height };
	HMENU hMenu = GetMenu(m_MainHwnd);

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, (bool)hMenu);
	SetWindowPos(m_MainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::Init(HWND _hwnd, int _Width, int _Height)
{
	// 메인 윈도우 핸들과 dc를 들고 있음
	m_MainHwnd = _hwnd;
	m_MainDC = GetDC(_hwnd);

	// 펜 브러쉬 초기화
	CreateGDIObject();

	// 지정된 해상도로 window 사이즈 지정
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	RECT rect{ 0,0,_Width,_Height };
	HMENU hMenu = GetMenu(m_MainHwnd);
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, (bool)hMenu);
	SetWindowPos(m_MainHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);


	// 이중 버퍼링용 비트맵과 dc 초기화
	m_BackBufferDC = CreateCompatibleDC(m_MainDC);
	m_BackBuffer = CreateCompatibleBitmap(m_MainDC, (int)m_Resolution.x, (int)m_Resolution.y);
	// DC와 Bitmap 연결, 나오는 더비 비트맵 삭제
	DeleteObject(SelectObject(m_BackBufferDC, m_BackBuffer));

	// 매니저 초기화
	CKeyMgr::Get()->Init();
	CTimeMgr::Get()->Init();
	CSoundMgr::Get()->Init();
	CPathMgr::Get()->Init();
	CGameMgr::Get()->Init();
	CAssetMgr::Get()->Init();
	CLevelMgr::Get()->Init();
	CCollisionMgr::Get()->Init();
	CCamera::Get()->Init();

#ifdef _DEBUG
	CDebugMgr::Get()->Init();
#endif

	CTaskMgr::Get()->Init();
	CUIMgr::Get()->Init();
}

void CEngine::Progress()
{
	// tick
	CKeyMgr::Get()->Tick();
	CTimeMgr::Get()->Tick();
	CGameMgr::Get()->Tick();


	CLevelMgr::Get()->Tick();
	if (!CGameMgr::Get()->IsPause())
	{
		CLevelMgr::Get()->FinalTick();
		CCollisionMgr::Get()->Tick();
		CCamera::Get()->Tick();
		CUIMgr::Get()->Tick();
	}

#ifdef _DEBUG
	CDebugMgr::Get()->Tick();
#endif

	// render
	Render();

	// final tick
	CTimeMgr::Get()->FinalTick();
	CTaskMgr::Get()->Tick();
}

void CEngine::Render()
{
	HBRUSH hOriBrush = (HBRUSH)SelectObject(m_BackBufferDC, m_ArrBrush[(UINT)BRUSH_TYPE::WHITE]);
	Rectangle(m_BackBufferDC, -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
	SelectObject(m_BackBufferDC, hOriBrush);

	// BackBuffer에 렌더
	CLevelMgr::Get()->Render();

	CCamera::Get()->Render();
	
#ifdef _DEBUG
	CTimeMgr::Get()->Render();
	CDebugMgr::Get()->Render();
	CLogMgr::Get()->Tick();
#endif

	// MainBuffer에 복사
	BitBlt(m_MainDC
		, 0, 0
		, (int)m_Resolution.x
		, (int)m_Resolution.y
		, m_BackBufferDC
		, 0, 0
		, SRCCOPY);
	
}