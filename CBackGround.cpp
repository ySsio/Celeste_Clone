#include "pch.h"
#include "CBackGround.h"

#include "CTexture.h"

#include "CAssetMgr.h"

CBackGround::CBackGround()
{
	m_Sprite = AddComponent<CSpriteRenderer>();
}

CBackGround::~CBackGround()
{
}

void CBackGround::SetTexture(CTexture* _Tex)
{
	m_Sprite->SetTex(_Tex);
	SetScale(Vec2((float)_Tex->GetWidth(), (float)_Tex->GetHeight()));
}

bool CBackGround::Save(FILE* _pFile)
{
	// 1. 오브젝트 종류를 문자열로 저장
	wstring Type = L"BackGround";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room 정보 저장
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. 포지션 저장
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. 텍스쳐 이름 저장
	wstring TexName = m_Sprite->GetTex()->GetPath();
	len = (int)TexName.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(TexName.c_str(), sizeof(wchar_t), len, _pFile);

	return true;
}

void CBackGround::Load(FILE* _pFile)
{
	// 1. 오브젝트 타입을 보고 이 함수가 호출된 상황
	// 2. Room 정보 불러옴
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. 포지션 받아와서 세팅
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. 텍스쳐 이름 받아와서 로드
	int len = 0;
	wchar_t szBuff[256]{};
	fread(&len, sizeof(int), 1, _pFile);
	fread(&szBuff, sizeof(wchar_t), len, _pFile);

	m_Sprite->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(szBuff)->Scale(5.f));
}

void CBackGround::Render()
{
	if (m_Sprite)
		m_Sprite->Render();
}

