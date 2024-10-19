#include "pch.h"
#include "CAnimUI.h"

CAnimUI::CAnimUI()
	: m_Anim(nullptr)
{
	m_Anim = AddComponent<CAnimator>();
}

CAnimUI::CAnimUI(const CAnimUI& _Other)
	: CUI(_Other)
{
	m_Anim = GetComponent<CAnimator>();
}

CAnimUI::~CAnimUI()
{
}

void CAnimUI::SetAnim(const wstring& _AnimName, CAnimation* _Anim)
{
	m_Anim->AddAnimation(_AnimName, _Anim);
	m_Anim->Play(_AnimName,true);
}

void CAnimUI::Render_DerivedUI()
{
	m_Anim->Render();
}
