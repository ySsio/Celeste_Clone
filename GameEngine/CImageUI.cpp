#include "pch.h"
#include "CImageUI.h"


CImageUI::CImageUI()
{
}


CImageUI::~CImageUI()
{
}

void CImageUI::Render_DerivedUI()
{	
	CSpriteRenderer* pSprite = GetSprite();

	pSprite->Render();
}
