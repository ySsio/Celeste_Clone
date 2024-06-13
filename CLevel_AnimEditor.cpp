#include "pch.h"
#include "CLevel_AnimEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CAnimation.h"

#include "CPanelUI.h"
#include "CButtonUI.h"

CLevel_AnimEditor::CLevel_AnimEditor()
	: m_Animation(nullptr)
{
}


CLevel_AnimEditor::~CLevel_AnimEditor()
{
}


void CLevel_AnimEditor::Enter()
{
	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(100.f, 100.f));
	pPanel->SetScale(Vec2(800.f, 600.f));

	AddObject(pPanel, LAYER_TYPE::UI);

	CButtonUI* pButton = new CButtonUI;
	pButton->SetPos(Vec2(100.f, 100.f));
	pButton->SetScale(Vec2(200.f, 100.f));
	pButton->SetName(L"애니메이션 편집");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(100.f, 500.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"이전");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 500.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"다음");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);
}

void CLevel_AnimEditor::CreateAnimation()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();
	strContentPath += L"\\map";

	OPENFILENAME OFN{};
	wchar_t szFilePath[255] = L"";
	wchar_t filter[] = L"Animation\0*.anim\0모든 파일\0*.*\0";

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = szFilePath;
	OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
	OFN.lpstrInitialDir = strContentPath.c_str(); // 창을 켰을 때 디폴트 경로

	if (GetSaveFileName(&OFN))	// 확인 누르면 true
	{
		m_Animation = new CAnimation;

		wstring strFilePath = szFilePath;

		wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

		if (wcscmp(strExtension.c_str(), L".anim") != 0)
			strFilePath += L".anim";

		// 선택 경로로 애니메이션 저장
		m_Animation->Save(strFilePath);

		// 파일 이름으로 애니메이션 이름 설정
		wstring strFileName = CPathMgr::Get()->GetNaiveFileName(strFilePath);
		CAssetMgr::Get()->AddAsset(strFileName, m_Animation);
	}
}

void CLevel_AnimEditor::SaveAnimation()
{

}

void CLevel_AnimEditor::LoadAnimation()
{
}