#include "pch.h"
#include "CLogMgr.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CLogMgr::CLogMgr()
	: m_LogMaxLife(2.f)
	, m_LogStep(20)
{
}

CLogMgr::~CLogMgr()
{

}

void CLogMgr::Tick()
{
	if (m_LogList.size())
	{
		SELECT_BRUSH(BackDC, BRUSH_TYPE::BLACK);
		Rectangle(BackDC, 5, 10, 1000, (int)m_LogList.size() * 20 + 10);
	}

	int i = 0;
	for (auto iter = m_LogList.begin(); iter != m_LogList.end(); ++i)
	{
		SetBkMode(BackDC, TRANSPARENT);

		COLORREF textColor = 0;
		switch (iter->Level)
		{
		case LOG_LEVEL::LOG:
		{
			textColor = SetTextColor(BackDC, RGB(20, 255, 20));
		}
		break;
		case LOG_LEVEL::WARNING:
		{
			textColor = SetTextColor(BackDC, RGB(255, 255, 20));
		}
		break;
		case LOG_LEVEL::BUG:
		{
			textColor = SetTextColor(BackDC, RGB(255, 20, 20));
		}
		break;
		default:
			break;
		}


		TextOut(BackDC, 10, 10 + m_LogStep * i, iter->strLog.c_str(), (int)iter->strLog.length());

		SetTextColor(BackDC, textColor);

		iter->Time += fDT;
		if (iter->Time >= m_LogMaxLife)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
