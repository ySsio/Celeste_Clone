#include "pch.h"
#include "CSound.h"
#include "CPathMgr.h"


CSound::CSound()
{
}

CSound::~CSound()
{
}

void CSound::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	SetPath(strFilePath);
}
