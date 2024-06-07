#include "pch.h"
#include "CObj.h"
#include "CEngine.h"
#include "CCamera.h"

CObj::CObj()
{
}

CObj::CObj(const CObj& _other)
	: CBase(_other)
	, m_Pos(_other.m_Pos)
{
}

CObj::~CObj()
{
}

#include "CAssetMgr.h"
#include "CTexture.h"

Vec2 CObj::GetRenderPos()
{
	return CCamera::Get()->GetRenderPos(GetPos());
}

void CObj::Render()
{
	Rectangle(BackDC
		, (int)(m_Pos.x - m_Scale.x / 2.f)
		, (int)(m_Pos.y - m_Scale.y / 2.f)
		, (int)(m_Pos.x + m_Scale.x / 2.f)
		, (int)(m_Pos.y + m_Scale.y / 2.f));

}
