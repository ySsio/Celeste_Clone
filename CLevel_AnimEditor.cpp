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
	pButton->SetName(L"�ִϸ��̼� ����");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(100.f, 500.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 500.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);
}

void CLevel_AnimEditor::CreateAnimation()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();
	strContentPath += L"\\map";

	OPENFILENAME OFN{};
	wchar_t szFilePath[255] = L"";
	wchar_t filter[] = L"Animation\0*.anim\0��� ����\0*.*\0";

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// ��� ä���� �����츦 ��������
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = szFilePath;
	OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	OFN.nMaxFile = 255;	// ���� ���ڿ� �ִ� ����
	OFN.lpstrInitialDir = strContentPath.c_str(); // â�� ���� �� ����Ʈ ���

	if (GetSaveFileName(&OFN))	// Ȯ�� ������ true
	{
		m_Animation = new CAnimation;

		wstring strFilePath = szFilePath;

		wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

		if (wcscmp(strExtension.c_str(), L".anim") != 0)
			strFilePath += L".anim";

		// ���� ��η� �ִϸ��̼� ����
		m_Animation->Save(strFilePath);

		// ���� �̸����� �ִϸ��̼� �̸� ����
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