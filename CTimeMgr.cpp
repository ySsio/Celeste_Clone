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
	QueryPerformanceCounter(&m_CurCount); // ���� ƽ�� ����

	// ���� ƽ�� �� ������ ƽ�� ���̷� delta time�� ���
	m_DT = (double)(m_CurCount.QuadPart - PrevCount.QuadPart) / m_Frequency.QuadPart;
	m_fDT = (float)m_DT;

	if (m_DT >= 1.f / 60)
	{
		m_DT = 1. / 60;
		m_fDT = (float)m_DT;
	}

	// �Լ� ȣ�� Ƚ���� ���� FPS�� ���� count
	static int iCount = 0;
	m_fAccTime += m_fDT;
	++iCount;

	// 1�ʸ� ���� ������ ī��Ʈ �ʱ�ȭ
	if (m_fAccTime >= 1.f)
	{
		m_FPS = iCount;
		iCount = 0;
	}

}

void CTimeMgr::Render()
{
	// 1�ʸ��� FPS�� delta time ��� (Text Out�� �� ƽ���� ���)
	// tempDT : 1�ʸ��� fDT�� �޾Ƶּ� ����� �� ���
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
	// ���� �ð� �ʱ�ȭ
	if (m_fAccTime >= 1.f)
	{
		m_fAccTime -= 1.f;
	}
}



