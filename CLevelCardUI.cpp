#include "pch.h"
#include "CLevelCardUI.h"

#include "CEngine.h"
#include "CAssetMgr.h"

#include "CTextUI.h"


CLevelCardUI::CLevelCardUI()
	: m_Card(nullptr)
{
	SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"Select_Cardtop", L"\\texture\\Gui\\areaselect\\cardtop.png")->Scale(0.8f));

	m_Card = new CImageUI;
	m_Card->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"Select_Card", L"\\texture\\Gui\\areaselect\\card.png")->Scale(0.8f));
	m_Card->GetSprite()->SetPartRender(Vec2(0.f, 0.7f), Vec2(1.f, 1.f));
	m_Card->SetPos(Vec2(0.f, 180.f));
	AddChild(m_Card);

	CImageUI* pTitle = new CImageUI;
	pTitle->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"Select_Title", L"\\texture\\Gui\\areaselect\\title.png")->Scale(0.8f));
	pTitle->SetPos(Vec2(-20.f, 60.f));
	AddChild(pTitle);

	m_Chapter = new CTextUI;
	m_Chapter->SetFont(L"�������", 24);
	pTitle->AddChild(m_Chapter);

	m_ChapterName = new CTextUI;
	m_ChapterName->SetFont(L"�������", 40);
	pTitle->AddChild(m_ChapterName);

	m_BottomText = new CTextUI;
	m_BottomText->SetFont(L"�������", 40);
	pTitle->AddChild(m_BottomText);
}

CLevelCardUI::~CLevelCardUI()
{
}

void CLevelCardUI::SetValueWithLevel(int _Level)
{
	vector<wstring> Chapters{ L"", L"é�� 1", L"é�� 2", L"é�� 3", L"é�� 4", L"é�� 5", L"é�� 6", L"é�� 7", L"", L"é�� 8" };
	vector<wstring> ChpaterNames{ L"���ѷα�", L"�������� ����", L"������ ��", L"������Ƽ�� ����Ʈ",L"Ȳ�� �긶��", L"�ſ� ���", L"�ݿ�", L"����", L"���ʷα�", L"�ھ�" };

	// é�� �ؽ�Ʈ ���� �� ��ġ ����
	m_Chapter->SetText(Chapters[_Level]);
	m_Chapter->SetPos(Vec2(100.f - m_Chapter->GetScale().x, -25.f));

	// é�� �̸� �ؽ�Ʈ ���� �� ��ġ ����
	m_ChapterName->SetText(ChpaterNames[_Level]);
	m_ChapterName->SetPos(Vec2(100.f - m_ChapterName->GetScale().x, 0.f));

	// ���� �ؽ�Ʈ ����
	if (_Level == 0 || _Level == 8)
		m_BottomText->SetText(L"����");
	else
		m_BottomText->SetText(L"������");

	m_BottomText->SetPos(Vec2(0.f, 140.f));
}