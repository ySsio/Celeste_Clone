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

	m_ArrBrush[(UINT)BRUSH_TYPE::WHITE] = CreateSolidBrush(RGB(255, 255, 255));
	m_ArrBrush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(RGB(0, 0, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_ArrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_ArrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
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
	// ���� ������ �ڵ�� dc�� ��� ����
	m_MainHwnd = _hwnd;
	m_MainDC = GetDC(_hwnd);

	// �� �귯�� �ʱ�ȭ
	CreateGDIObject();

	// ������ �ػ󵵷� window ������ ����
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	RECT rect{ 0,0,_Width,_Height };
	HMENU hMenu = GetMenu(m_MainHwnd);
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, (bool)hMenu);
	SetWindowPos(m_MainHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);


	// ���� ���۸��� ��Ʈ�ʰ� dc �ʱ�ȭ
	m_BackBufferDC = CreateCompatibleDC(m_MainDC);
	m_BackBuffer = CreateCompatibleBitmap(m_MainDC, (int)m_Resolution.x, (int)m_Resolution.y);
	// DC�� Bitmap ����, ������ ���� ��Ʈ�� ����
	DeleteObject(SelectObject(m_BackBufferDC, m_BackBuffer));

	// �Ŵ��� �ʱ�ȭ
	CKeyMgr::Get()->Init();
	CTimeMgr::Get()->Init();
	CPathMgr::Get()->Init();
	CAssetMgr::Get()->Init();
	CLevelMgr::Get()->Init();
	CCollisionMgr::Get()->Init();
	CCamera::Get()->Init();
	CDebugMgr::Get()->Init();
	CTaskMgr::Get()->Init();
}

void CEngine::Progress()
{
	// tick
	CTimeMgr::Get()->Tick();
	CKeyMgr::Get()->Tick();
	CLevelMgr::Get()->Tick();
	CLevelMgr::Get()->FinalTick();
	CCollisionMgr::Get()->Tick();
	CCamera::Get()->Tick();
	CDebugMgr::Get()->Tick();

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

	// BackBuffer�� ����
	CLevelMgr::Get()->Render();
	CTimeMgr::Get()->Render();
	

	CDebugMgr::Get()->Render();

	// MainBuffer�� ����
	BitBlt(m_MainDC
		, 0, 0
		, (int)m_Resolution.x
		, (int)m_Resolution.y
		, m_BackBufferDC
		, 0, 0
		, SRCCOPY);
	
}