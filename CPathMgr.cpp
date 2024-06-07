#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::ChangeDirUp(wstring& _Path)
{
	 size_t idx = _Path.rfind(L'\\');

	 _Path = _Path.substr(0, idx);
}

void CPathMgr::Init()
{
	wchar_t buff[256];
	GetCurrentDirectory(256, buff);

	m_ContentPath = buff;
	ChangeDirUp(m_ContentPath);
	m_ContentPath += L"\\content";

}
