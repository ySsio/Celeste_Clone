#include "pch.h"
#include "CLevelCardUI_Collectable.h"

#include "CAssetMgr.h"
#include "CGameMgr.h"

#include "CSaveData.h"

#include "CTextUI.h"


CLevelCardUI_Collectable::CLevelCardUI_Collectable()
{
	// ī�� ������ ����
	m_Card->GetSprite()->SetPartRender(Vec2(0.f, 0.3f), Vec2(1.f, 1.f));
	m_Card->SetPos(Vec2(0.f, 250.f));

	// ���� �̹���
	CImageUI* pImage = new CImageUI;
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\collectables\\strawberry.png")->Scale(0.8f));
	pImage->SetPos(Vec2(-50.f, -30.f));
	m_Card->AddChild(pImage);

	// ���� �̹���
	pImage = new CImageUI;
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\collectables\\skullBlue.png")->Scale(0.8f));
	pImage->SetPos(Vec2(-50.f, 30.f	));
	m_Card->AddChild(pImage);

	m_StrawberryCnt = new CTextUI;
	m_StrawberryCnt->SetPos(Vec2(0.f, -55.f));
	m_StrawberryCnt->SetFont(L"�������", 40);
	m_Card->AddChild(m_StrawberryCnt);

	m_DeathCnt = new CTextUI;
	m_DeathCnt->SetPos(Vec2(0.f, 5.f));
	m_DeathCnt->SetFont(L"�������", 40);
	m_Card->AddChild(m_DeathCnt);
}

CLevelCardUI_Collectable::~CLevelCardUI_Collectable()
{
}

void CLevelCardUI_Collectable::SetValueWithLevel(int _Level)
{
	CLevelCardUI::SetValueWithLevel(_Level);

	assert(1 <= _Level && _Level <= LEVEL_COUNT);

	// ���� �ؽ�Ʈ ��ġ ����
	m_BottomText->SetPos(Vec2(0.f, 350.f));

	// �� ���� �� ���
	m_StrawberryLevelCnt = 0;
	for (auto Type : LEVEL_MAP[_Level])
	{
		m_StrawberryLevelCnt += CGameMgr::Get()->GetCurSave()->GetStrawberryTable(Type).size();
	}

	// ������ ���� �� ���
	m_StrawberryLevelCollectedCnt = 0;
	for (auto Type : LEVEL_MAP[_Level])
	{
		const auto& table = CGameMgr::Get()->GetCurSave()->GetStrawberryTable(Type);

		for (auto Collected : table)
		{
			if (Collected == 1)
				++m_StrawberryLevelCollectedCnt;
		}
	}

	m_StrawberryCnt->SetText(L"x " + std::to_wstring(m_StrawberryLevelCollectedCnt) + L"/" + std::to_wstring(m_StrawberryLevelCnt));

	// ���� �� ���
	m_DeathLevelCnt = 0;
	for (auto Type : LEVEL_MAP[_Level])
	{
		m_DeathLevelCnt += CGameMgr::Get()->GetCurSave()->GetDeathLevel(Type);
	}
	m_DeathCnt->SetText(L"x " + std::to_wstring(m_DeathLevelCnt));
	
}
