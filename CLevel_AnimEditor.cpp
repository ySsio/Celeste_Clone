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
#include "CTextUI.h"

CLevel_AnimEditor::CLevel_AnimEditor()
	: m_AnimUI(nullptr)
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
	pPanel->SetScale(Vec2(vRes.x + 1, vRes.y + 1));

	AddObject(pPanel, LAYER_TYPE::UI);

	CAnimUI* pAnimUI = new CAnimUI;
	pAnimUI->SetPos(Vec2(50.f, 50.f));
	pAnimUI->SetScale(Vec2(500.f, 500.f));
	pAnimUI->SetBang(CAssetMgr::Get()->LoadAsset<CAnimation>(L"Player_Bang", L""));
	pAnimUI->SetBody(CAssetMgr::Get()->LoadAsset<CAnimation>(L"Player_Idle", L""));

	pPanel->AddChild(pAnimUI);

	CButtonUI* pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 600.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->DecrBangFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 600.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->IncrBangFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 650.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->DecrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 650.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->IncrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 700.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->DecrBangFrm(); pAnimUI->DecrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 700.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->IncrBangFrm(); pAnimUI->IncrBodyFrm(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(500.f, 620.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"���");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(500.f, 680.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Stop(); });

	pPanel->AddChild(pButton);


	SetBkMode(BackDC, TRANSPARENT);

	CTextUI* pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 600.f));
	pTextUI->SetFont(L"Arial", 24);
	pTextUI->SetText(L"Bang");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 650.f));
	pTextUI->SetText(L"Body");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 700.f));
	pTextUI->SetText(L"All");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(300.f, 600.f));
	pTextUI->SetText(L"Frame 0");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(300.f, 650.f));
	pTextUI->SetText(L"Frame 0");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(300.f, 700.f));
	pTextUI->SetText(L"Frame 0");

	pPanel->AddChild(pTextUI);


	// �Ӹ� �ִϸ��̼�, ������ ����
	float tempX = 600.f;

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 60.f));
	pTextUI->SetFont(L"Arial", 32);
	pTextUI->SetText(L"�ִϸ��̼� ����");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 100.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"�ִϸ��̼� �̸�");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBangAnimName = new CTextBoxUI();
	pBangAnimName->SetPos(Vec2(tempX + 10.f, 140.f));
	pBangAnimName->SetScale(Vec2(150.f, 40.f));

	pPanel->AddChild(pBangAnimName);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 170.f, 140.f));
	pTextUI->SetText(L".anim");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 200.f));
	pTextUI->SetText(L"������ �� : 9");

	pPanel->AddChild(pTextUI);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, 200.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"+");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 200.f, 200.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"-");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, 240.f));
	pButton->SetScale(Vec2(50.f, 30.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	// Bang ������ ����
	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 360.f));
	pTextUI->SetFont(L"Arial", 32);
	pTextUI->SetText(L"������ ����");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"Offset");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 100.f, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"x :");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBangOffsetX = new CTextBoxUI();
	pBangOffsetX->SetPos(Vec2(tempX + 130.f, 420.f));
	pBangOffsetX->SetScale(Vec2(40.f, 40.f));
	pBangOffsetX->SetInteger(true);

	pPanel->AddChild(pBangOffsetX);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 398.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {int val = pBangOffsetX->GetIntValue(); pBangOffsetX->SetNumValue(val + 1); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 462.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {int val = pBangOffsetX->GetIntValue(); pBangOffsetX->SetNumValue(val - 1);  });

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 180.f, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"y :");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBangOffsetY = new CTextBoxUI();
	pBangOffsetY->SetPos(Vec2(tempX + 210.f, 420.f));
	pBangOffsetY->SetScale(Vec2(40.f, 40.f));
	pBangOffsetY->SetInteger(true);

	pPanel->AddChild(pBangOffsetY);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 398.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {int val = pBangOffsetY->GetIntValue(); pBangOffsetY->SetNumValue(val + 1); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 462.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {int val = pBangOffsetY->GetIntValue(); pBangOffsetY->SetNumValue(val - 1); });

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 500.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"Duration : ");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBangDuration = new CTextBoxUI();
	pBangDuration->SetPos(Vec2(tempX + 130.f, 500.f));
	pBangDuration->SetScale(Vec2(120.f, 40.f));
	pBangDuration->SetFloat(true);

	pPanel->AddChild(pBangDuration);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 60.f, 640.f));
	pButton->SetScale(Vec2(50.f, 30.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 120.f, 640.f));
	pButton->SetScale(Vec2(80.f, 30.f));
	pButton->SetName(L"�ҷ�����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	// �� �ִϸ��̼�, ������ ����
	tempX = 1000.f;

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 60.f));
	pTextUI->SetFont(L"Arial", 32);
	pTextUI->SetText(L"�ִϸ��̼� ����");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 100.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"�ִϸ��̼� �̸�");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBodyAnimName = new CTextBoxUI();
	pBodyAnimName->SetPos(Vec2(tempX + 10.f, 140.f));
	pBodyAnimName->SetScale(Vec2(150.f, 40.f));

	pPanel->AddChild(pBodyAnimName);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 170.f, 140.f));
	pTextUI->SetText(L".anim");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 200.f));
	pTextUI->SetText(L"������ �� : 9");

	pPanel->AddChild(pTextUI);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, 200.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"+");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 200.f, 200.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetName(L"-");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, 240.f));
	pButton->SetScale(Vec2(50.f, 30.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	// Body ������ ����
	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 360.f));
	pTextUI->SetFont(L"Arial", 32);
	pTextUI->SetText(L"������ ����");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"Offset");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 100.f, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"x :");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBodyOffsetX = new CTextBoxUI();
	pBodyOffsetX->SetPos(Vec2(tempX + 130.f, 420.f));
	pBodyOffsetX->SetScale(Vec2(40.f, 40.f));
	pBodyOffsetX->SetInteger(true);

	pPanel->AddChild(pBodyOffsetX);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 398.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 462.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 180.f, 420.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"y :");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBodyOffsetY = new CTextBoxUI();
	pBodyOffsetY->SetPos(Vec2(tempX + 210.f, 420.f));
	pBodyOffsetY->SetScale(Vec2(40.f, 40.f));
	pBodyOffsetY->SetInteger(true);

	pPanel->AddChild(pBodyOffsetY);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 398.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 462.f));
	pButton->SetScale(Vec2(20.f, 20.f));
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 500.f));
	pTextUI->SetFont(L"Arial", 28);
	pTextUI->SetText(L"Duration : ");

	pPanel->AddChild(pTextUI);

	CTextBoxUI* pBodyDuration = new CTextBoxUI();
	pBodyDuration->SetPos(Vec2(tempX + 130.f, 500.f));
	pBodyDuration->SetScale(Vec2(120.f, 40.f));
	pBodyDuration->SetFloat(true);

	pPanel->AddChild(pBodyDuration);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 60.f, 640.f));
	pButton->SetScale(Vec2(50.f, 30.f));
	pButton->SetName(L"����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 120.f, 640.f));
	pButton->SetScale(Vec2(80.f, 30.f));
	pButton->SetName(L"�ҷ�����");
	pButton->SetFunction([=]() {pAnimUI->Play(); });

	pPanel->AddChild(pButton);
}

void CLevel_AnimEditor::SetBangAnim(CAnimation* _Anim)
{
	m_AnimUI->SetBang(_Anim);
}

void CLevel_AnimEditor::SetBodyAnim(CAnimation* _Anim)
{
	m_AnimUI->SetBody(_Anim);
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
		CAnimation* pAnim = new CAnimation;

		wstring strFilePath = szFilePath;

		wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

		if (wcscmp(strExtension.c_str(), L".anim") != 0)
			strFilePath += L".anim";

		// ���� ��η� �ִϸ��̼� ����
		pAnim->Save(strFilePath);

		// ���� �̸����� �ִϸ��̼� �̸� ����
		wstring strFileName = CPathMgr::Get()->GetNaiveFileName(strFilePath);
		CAssetMgr::Get()->AddAsset(strFileName, pAnim);
	}
}

void CLevel_AnimEditor::SaveAnimation()
{

}

void CLevel_AnimEditor::LoadAnimation()
{
}