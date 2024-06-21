#include "pch.h"
#include "CAnimation.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CAssetMgr.h"

CAnimation::CAnimation()
	: m_Duration(0.f)
	, m_Flipped(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Save(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"w");
	assert(pFile);

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	
	fwprintf_s(pFile, L"[FRAME_DATA]\n");
	int size = (int)m_vecFrm.size();

	fwprintf_s(pFile, L"Frame_Count : %d\n\n", size);

	for (int i = 0; i < size; ++i)
	{
		// 프레임 번호
		fwprintf_s(pFile, L"Frame_Index : %d\n", i);

		// Flipped
		fwprintf_s(pFile, L"Flipped : %d\n", m_vecFrm[i].Texture->GetFlipped());

		// Texture
		fwprintf_s(pFile, L"Texture_Name	: %s\n", m_vecFrm[i].Texture->GetName().c_str());
		fwprintf_s(pFile, L"Texture_Path	: %s\n", m_vecFrm[i].Texture->GetPath().c_str());
		fwprintf_s(pFile, L"Texture_Scale	: %d, %d\n", m_vecFrm[i].Texture->GetWidth(), m_vecFrm[i].Texture->GetHeight());

		// offset
		fwprintf_s(pFile, L"Offset	: %d, %d\n", (int)m_vecFrm[i].Offset.x, (int)m_vecFrm[i].Offset.y);

		// duration
		fwprintf_s(pFile, L"Duration	: %f\n\n", m_vecFrm[i].Duration);
	}


	fclose(pFile);

}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"r");
	assert(pFile);

	// 문자열 저장 버퍼
	wchar_t szTitle[256]{};
	wchar_t szWParam[256]{};
	wchar_t szLParam[256]{};

	while (true)
	{
		fwscanf_s(pFile, L"%s", szTitle, 256); // Animation Name
		wstring str = szTitle;

		if (str == L"[ANIMATION_NAME]")
		{
			fwscanf_s(pFile, L"%s", szWParam, 256);
			SetName(szWParam);
		}
		else if (str == L"[FRAME_DATA]")
		{
			int size = 0;
			fwscanf_s(pFile, L"%s : %d", szWParam, 256, &size); // L"Frame Count"

			m_vecFrm.resize(size);

			for (int i = 0; i < size; ++i)
			{
				int idx = 0;
				int x = 0;
				int y = 0;

				int Flipped = 0;

				fwscanf_s(pFile, L"%s : %d", szTitle, 256, &idx); // L"Frame Index"

				fwscanf_s(pFile, L"%s : %d", szTitle, 256, &Flipped); // L"Flipped"

				fwscanf_s(pFile, L"%s : %s", szTitle, 256, szWParam, 256); // L"Texture_Name"
				fwscanf_s(pFile, L"%s : %s", szTitle, 256, szLParam, 256); // L"Texture_Path"
				fwscanf_s(pFile, L"%s : %d, %d", szTitle, 256, &x, &y); // L"Texture_Scale"

				//if (wstring(szWParam))
				//{
				//	m_vecFrm[idx].Texture = CAssetMgr::Get()->CreateFlippedTexture(L"", m_vecFrm[idx].Texture);
				//}
				m_vecFrm[idx].Texture = CAssetMgr::Get()->LoadAsset<CTexture>(szWParam, szLParam);
				m_vecFrm[idx].Texture->Stretch(Vec2((float)x, (float)y));
				m_vecFrm[idx].Texture->SetFlipped((bool)Flipped);
				if ((bool)Flipped)
				{
					CAssetMgr::Get()->FlipTexture(m_vecFrm[idx].Texture);
				}

				fwscanf_s(pFile, L"%s : %d, %d", szTitle, 256, &x, &y); // L"Offset"

				m_vecFrm[idx].Offset.x = (float)x;
				m_vecFrm[idx].Offset.y = (float)y;

				fwscanf_s(pFile, L"%s : %f", szTitle, 256, &m_vecFrm[idx].Duration); // L"Duration"
			}

		}


		if (feof(pFile)) break;
	}

	fclose(pFile);
}