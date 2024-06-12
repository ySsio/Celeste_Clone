#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_CurCount{}
	, m_fAccTime(0.f)
	, m_FPS(0)
	, m_DT(0.)
	, m_fDT(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_CurCount);
	QueryPerformanceFrequency(&m_Frequency);
}

void CTimeMgr::Tick()
{
	LARGE_INTEGER PrevCount = m_CurCount;
	QueryPerformanceCounter(&m_CurCount); // 현재 틱을 받음

	// 현재 틱과 전 프레임 틱의 차이로 delta time을 계산
	m_DT = (double)(m_CurCount.QuadPart - PrevCount.QuadPart) / m_Frequency.QuadPart;
	m_fDT = (float)m_DT;

	if (m_DT >= 1.f / 60)
	{
		m_DT = 1. / 60;
		m_fDT = (float)m_DT;
	}

	// 함수 호출 횟수를 통해 FPS를 직접 count
	static int iCount = 0;
	m_fAccTime += m_fDT;
	++iCount;

	// 1초를 넘을 때마다 카운트 초기화
	if (m_fAccTime >= 1.f)
	{
		m_FPS = iCount;
		iCount = 0;
	}

}

void CTimeMgr::Render()
{
	// 1초마다 FPS와 delta time 출력 (Text Out을 매 틱마다 출력)
	// tempDT : 1초마다 fDT를 받아둬서 출력할 때 사용
	static float tempDT = m_fDT;

	if (m_fAccTime >= 1.f)
	{
		tempDT = m_fDT;
	}

	wstring text = L"FPS : ";
	text += std::to_wstring(m_FPS) + L", DeltaTime : ";
	text += std::to_wstring(tempDT);

	TextOut(BackDC, 0, 0, text.c_str(), (int)text.length());
}

void CTimeMgr::FinalTick()
{
	// 누적 시간 초기화
	if (m_fAccTime >= 1.f)
	{
		m_fAccTime -= 1.f;
	}
}



