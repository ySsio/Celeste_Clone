#include "pch.h"
#include "CBackGround.h"

CBackGround::CBackGround()
{
	m_TileMap = AddComponent<CTileMap>();
}

CBackGround::~CBackGround()
{
}

void CBackGround::AddTexture(CTexture* _Tex)
{
	CSpriteRenderer* pSprite = AddComponent<CSpriteRenderer>();
	pSprite->SetTex(_Tex);

	m_Sprites.push_back(pSprite);
}

void CBackGround::Render()
{
	for (auto Sprite : m_Sprites)
	{
		Sprite->Render();
	}


	m_TileMap->Render();

}

