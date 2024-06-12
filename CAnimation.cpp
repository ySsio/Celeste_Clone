#include "pch.h"
#include "CAnimation.h"
#include "CPathMgr.h"

CAnimation::CAnimation()
	: m_Duration(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Save(const wstring& _strFilePath)
{

}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	SetPath(strFilePath);
}