#include "pch.h"
#include "CPathMgr.h"

#include <iostream>
#include <filesystem>
namespace fs =  std::filesystem;


CPathMgr::CPathMgr()
{

}

CPathMgr::~CPathMgr()
{

}

wstring CPathMgr::ChangeDirUp(const wstring& _Path)
{
	size_t idx = _Path.rfind(L'\\');

	return _Path.substr(0, idx);
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

	wstring OutputPath = ChangeDirUp(buff);

	m_ContentPath = OutputPath;
	m_ContentPath += L"\\content";

	m_SavePath = OutputPath;
	m_SavePath += L"\\save";

}

vector<wstring> CPathMgr::GetFileList(const wstring& _strDirectory) {
	vector<wstring> files;

	try {
		for (const auto& entry : fs::directory_iterator(_strDirectory)) {
			files.push_back(entry.path().filename().wstring());
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}

	return files;
}