#include "pch.h"
#include "CBackGround.h"

#include "CTexture.h"

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

void CBackGround::Render()
{
	if (m_Sprite)
		m_Sprite->Render();
}

