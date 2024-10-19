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
	m_Chapter->SetFont(L"나눔고딕", 24);
	pTitle->AddChild(m_Chapter);

	m_ChapterName = new CTextUI;
	m_ChapterName->SetFont(L"나눔고딕", 40);
	pTitle->AddChild(m_ChapterName);

	m_BottomText = new CTextUI;
	m_BottomText->SetFont(L"나눔고딕", 40);
	pTitle->AddChild(m_BottomText);
}

CLevelCardUI::~CLevelCardUI()
{
}

void CLevelCardUI::SetValueWithLevel(int _Level)
{
	vector<wstring> Chapters{ L"", L"챕터 1", L"챕터 2", L"챕터 3", L"챕터 4", L"챕터 5", L"챕터 6", L"챕터 7", L"", L"챕터 8" };
	vector<wstring> ChpaterNames{ L"프롤로그", L"버림받은 도시", L"오래된 곳", L"셀레스티얼 리조트",L"황금 산마루", L"거울 사원", L"반영", L"정상", L"에필로그", L"코어" };

	// 챕터 텍스트 설정 및 위치 설정
	m_Chapter->SetText(Chapters[_Level]);
	m_Chapter->SetPos(Vec2(100.f - m_Chapter->GetScale().x, -25.f));

	// 챕터 이름 텍스트 설정 및 위치 설정
	m_ChapterName->SetText(ChpaterNames[_Level]);
	m_ChapterName->SetPos(Vec2(100.f - m_ChapterName->GetScale().x, 0.f));

	// 바텀 텍스트 설정
	if (_Level == 0 || _Level == 8)
		m_BottomText->SetText(L"시작");
	else
		m_BottomText->SetText(L"오르기");

	m_BottomText->SetPos(Vec2(0.f, 140.f));
}