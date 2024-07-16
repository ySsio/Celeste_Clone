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

wstring CPathMgr::GetRelativePath(const wstring& _strFilePath)
{
	int idx = (int)m_ContentPath.length();

	wstring strRelativePath = L"";
	for (int i = idx; i < _strFilePath.length(); ++i)
	{
		strRelativePath += _strFilePath[i];
	}

	return strRelativePath;
}

wstring CPathMgr::GetFileName(const wstring& _strFilePath)
{
	wstring strFileName = L"";
	for (int i = (int)_strFilePath.length() - 1; i >= 0; --i)
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
	for (int i = (int)_strFilePath.length() - 1; i >= 0; --i)
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

		strFileName = _strFilePath[i] + strFileName;
	}

	return strFileName;
}

wstring CPathMgr::GetPathExtension(const wstring& _strFilePath)
{
	wstring strExt = L"";
	for (int i = (int)_strFilePath.length() - 1; i >= 0; --i)
	{
		strExt = _strFilePath[i] + strExt;

		if (_strFilePath[i] == '.')
			break;
	}

	return strExt;
}

wstring CPathMgr::GetFileDirectory(const wstring& _strFilePath)
{
	wstring strFileDirectory = L"";

	for (int i = (int)_strFilePath.length() - 1; i >= 0; --i)
	{
		if (_strFilePath[i] == '\\')
		{
			strFileDirectory = _strFilePath.substr(0, i+1);
			break;
		}
	}

	return strFileDirectory;
}

void CPathMgr::Init()
{
	wchar_t buff[256]{};
	GetCurrentDirectory(256, buff);

	m_ContentPath = buff;
	ChangeDirUp(m_ContentPath);
	m_ContentPath += L"\\content";

}
