#include "pch.h"
#include "CDebugMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CEngine.h"

CDebugMgr::CDebugMgr()
	: m_DbgOnOff(true)
{

}

CDebugMgr::~CDebugMgr()
{

}

void CDebugMgr::Init()
{
}

void CDebugMgr::Tick()
{
	if (KEY_TAP(KEY::ENTER))
		m_DbgOnOff = !m_DbgOnOff;

	for (auto iter = m_DebugShapeList.begin(); iter!= m_DebugShapeList.end();)
	{
		if (iter->AccTime > iter->Duration)
		{
			iter = m_DebugShapeList.erase(iter);
			continue;
		}

		iter->AccTime += fDT;
		++iter;
	}
}

void CDebugMgr::Render()
{
	if (!m_DbgOnOff) return;

	for (const auto& DbgShp : m_DebugShapeList)
	{
		SELECT_PEN(BackDC, DbgShp.Pen);
		SELECT_BRUSH(BackDC, DbgShp.Brush);

		Vec2 vPos = DbgShp.Position;
		Vec2 vScale = DbgShp.Scale;

		switch (DbgShp.Shape)
		{
		case DEBUG_SHAPE::RECTANGLE:
		{
			Rectangle(BackDC
				, (int)(vPos.x - vScale.x / 2.f)
				, (int)(vPos.y - vScale.y / 2.f)
				, (int)(vPos.x + vScale.x / 2.f)
				, (int)(vPos.y + vScale.y / 2.f));
		}
			break;
		case DEBUG_SHAPE::ELLIPSE:
		{
			Ellipse(BackDC
				, (int)(vPos.x - vScale.x / 2.f)
				, (int)(vPos.y - vScale.y / 2.f)
				, (int)(vPos.x + vScale.x / 2.f)
				, (int)(vPos.y + vScale.y / 2.f));
		}
			break;
		case DEBUG_SHAPE::LINE:
		{
			MoveToEx(BackDC, (int)vPos.x, (int)vPos.y, nullptr);
			LineTo(BackDC
				, (int)(vPos.x + vScale.x)
				, (int)(vPos.y + vScale.y));
		}
			break;
		default:
			break;
		}
	}
}
