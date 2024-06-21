#include "pch.h"
#include "CLevel_AnimEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CAnimation.h"
#include "CTimeMgr.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAnimUI.h"
#include "CTextBoxUI.h"

CLevel_AnimEditor::CLevel_AnimEditor()
	: m_Animation(nullptr)
{
}


CLevel_AnimEditor::~CLevel_AnimEditor()
{
}


void CLevel_AnimEditor::Enter()
{
	Vec2 vRes = CEngine::Get()->GetResolution();

	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(-1.f, -1.f));
	pPanel->SetScale(Vec2(vRes.x+1, vRes.y+1));

	AddObject(pPanel, LAYER_TYPE::UI);

	CAnimUI* pAnimUI = new CAnimUI;
	pAnimUI->SetPos(Vec2(50.f, 50.f));
	pAnimUI->SetScale(Vec2(500.f, 500.f));
	pAnimUI->SetBang(CAssetMgr::Get()->LoadAsset<CAnimation>(L"Player_Bang", L""));
	pAnimUI->SetBody(CAssetMgr::Get()->LoadAsset<CAnimation>(L"Player_Idle", L""));

	pPanel->AddChild(pAnimUI);

	CButtonUI* pButton = new CButtonUI;
	pButton->SetPos(Vec2(800.f, 100.f));
	pButton->SetScale(Vec2(200.f, 100.f));
	pButton->SetName(L"�ִϸ��̼� ����");
	pButton->SetFunction([]() {ChangeLevel(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(150.f, 600.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->DecrBangFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(450.f, 600.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->IncrBangFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(150.f, 650.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->DecrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(450.f, 650.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->IncrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(150.f, 700.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"��ü ����");
	pButton->SetFunction([=]() {pAnimUI->DecrBangFrm(); pAnimUI->DecrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(450.f, 700.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"��ü ����");
	pButton->SetFunction([=]() {pAnimUI->IncrBangFrm(); pAnimUI->IncrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(550.f, 650.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"���");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(600.f, 650.f));
	pButton->SetScale(Vec2(20.f, 10.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Stop(); });

	pPanel->AddChild(pButton);


	CTextBoxUI* pTextBoxUI = new CTextBoxUI();
	pTextBoxUI->SetPos(Vec2(700.f, 200.f));
	pTextBoxUI->SetScale(Vec2(150.f, 24.f));

	pPanel->AddChild(pTextBoxUI);
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