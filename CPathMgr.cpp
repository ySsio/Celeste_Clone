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

wstring CPathMgr::GetFileName(const wstring& _strFilePath)
{
	wstring strFileName = L"";
	for (size_t i = _strFilePath.length() - 1; i >= 0; --i)
	{
		if (_strFilePath[i] == '\\')
			break;

		strFileName = strFileName + _strFilePath[i];
	}

	return strFileName;
}

wstring CPathMgr::GetNaiveFileName(const wstring& _strFilePath)
{
	wstring strFileName = L"";
	bool extensionPass = false;
	for (size_t i = _strFilePath.length() - 1; i >= 0; --i)
	{
		if (_strFilePath[i] == '.')
		{
			extensionPass = true;
			continue;
		}

		if (!extensionPass)
			continue;

		if (_strFilePath[i] == '\\')
			break;

		strFileName = strFileName + _strFilePath[i];
	}

	return strFileName;
}

wstring CPathMgr::GetPathExtension(const wstring& _strFilePath)
{
	wstring strExt = L"";
	for (size_t i = _strFilePath.length()-1; i >= 0; --i)
	{
		if (_strFilePath[i] == '.')
			break;

		strExt = strExt + _strFilePath[i];
	}

	return strExt;
}

void CPathMgr::Init()
{
	wchar_t buff[256];
	GetCurrentDirectory(256, buff);

	m_ContentPath = buff;
	ChangeDirUp(m_ContentPath);
	m_ContentPath += L"\\content";

}
