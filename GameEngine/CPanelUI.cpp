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
	// 1. 오브젝트 타입을 문자열로 저장
	wstring Type = L"PanelUI";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room 정보 저장 (해야되나?)
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. 포지션 저장
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Scale 저장
	VecBuff = GetScale();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. 텍스쳐 이름 저장
	wstring Tex = GetSprite()->GetTex()->GetName();
	len = (int)Tex.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Tex.c_str(), sizeof(wchar_t), len, _pFile);

	// 5. 고정 여부 저장
	bool b = GetSprite()->GetFix();
	fwrite(&b, sizeof(bool), 1, _pFile);
	


	return true;
}

void CPanelUI::Load(FILE* _pFile)
{
	// 1. 오브젝트 타입을 보고 이 함수가 호출된 상황
	// 2. Room 정보 불러옴
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. 포지션 저장
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. Scale 저장
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetScale(VecBuff);

	// 4. Tex 받아와서 세팅
	int len = 0;
	fread(&len, sizeof(int), 1, _pFile);

	vector<wchar_t> szBuff(len + 1);
	fread(szBuff.data(), sizeof(wchar_t), len, _pFile);

	SetTex(CAssetMgr::Get()->FindAsset<CTexture>(szBuff.data()));
	
	// 5. 고정
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