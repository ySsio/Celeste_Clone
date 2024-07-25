#include "pch.h"
#include "CAnimUI.h"

CAnimUI::CAnimUI()
	: m_Anim(nullptr)
{
	m_Anim = AddComponent<CAnimator>();
}

CAnimUI::~CAnimUI()
{
}

void CAnimUI::SetAnim(const wstring& _AnimName, CAnimation* _Anim)
{
	m_Anim->AddAnimation(_AnimName, _Anim);
}

void CAnimUI::Render_DerivedUI()
{
	m_Anim->Render();
}
