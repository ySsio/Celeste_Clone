#include "pch.h"
#include "CAnimation.h"
#include "CPathMgr.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	SetPath(strFilePath);
}