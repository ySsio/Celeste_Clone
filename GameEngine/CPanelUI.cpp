#include "pch.h"
#include "CPanelUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"

CPanelUI::CPanelUI()
	: m_Movable(true)
{
}

CPanelUI::~CPanelUI()
{
}

bool CPanelUI::Save(FILE* _pFile)
{
	// 1. ������Ʈ Ÿ���� ���ڿ��� ����
	wstring Type = L"PanelUI";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room ���� ���� (�ؾߵǳ�?)
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. ������ ����
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Scale ����
	VecBuff = GetScale();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. �ؽ��� �̸� ����
	wstring Tex = GetSprite()->GetTex()->GetName();
	len = (int)Tex.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Tex.c_str(), sizeof(wchar_t), len, _pFile);

	// 5. ���� ���� ����
	bool b = GetSprite()->GetFix();
	fwrite(&b, sizeof(bool), 1, _pFile);
	


	return true;
}

void CPanelUI::Load(FILE* _pFile)
{
	// 1. ������Ʈ Ÿ���� ���� �� �Լ��� ȣ��� ��Ȳ
	// 2. Room ���� �ҷ���
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. ������ ����
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. Scale ����
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetScale(VecBuff);

	// 4. Tex �޾ƿͼ� ����
	int len = 0;
	fread(&len, sizeof(int), 1, _pFile);

	vector<wchar_t> szBuff(len + 1);
	fread(szBuff.data(), sizeof(wchar_t), len, _pFile);

	SetTex(CAssetMgr::Get()->FindAsset<CTexture>(szBuff.data()));
	
	// 5. ����
	bool b = false;
	fread(&b, sizeof(bool), 1, _pFile);
	SetFix(b);

}

void CPanelUI::Tick_DerivedUI()
{
	if (!m_Movable)
		return;

	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	Vec2 vDiff = vMousePos - m_MouseGrabPos;

	if (IsLbtnDown())
	{
		SetPos(GetPos() + vDiff);
	}

	m_MouseGrabPos = vMousePos;
}

void CPanelUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	CSpriteRenderer* pSprite = GetSprite();

	if (pSprite->GetTex())
	{
		pSprite->Render();
	}
	else
	{
		SELECT_PEN(BackDC, PEN_TYPE::BLACK);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::GRAY);

		Rectangle(BackDC
			, (int)vFinalPos.x
			, (int)vFinalPos.y
			, (int)(vFinalPos.x + vScale.x)
			, (int)(vFinalPos.y + vScale.y));
	}

	
}