#include "pch.h"
#include "CUI.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTexture.h"

CUI::CUI()
	: m_ParentUI(nullptr)
	, m_MouseOn(false)
	, m_LbtnDown(false)
{
	m_Sprite = AddComponent<CSpriteRenderer>();
}

CUI::~CUI()
{
	Release_Vector(m_ChildUI);
}

void CUI::SetTex(CTexture* _Tex)
{
	m_Sprite->SetTex(_Tex); 
	SetScale(Vec2((float)_Tex->GetWidth(), (float)_Tex->GetHeight()));
}

Vec2 CUI::GetRenderPos()
{
	return RENDER_POS(GetFinalPos());
}

void CUI::Tick()
{
	m_FinalPos = GetPos();

	if (m_ParentUI) 
		m_FinalPos += m_ParentUI->GetPos();

	Vec2 vScale = GetScale();
	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();

	if (m_FinalPos.x <= vMousePos.x && vMousePos.x <= m_FinalPos.x + vScale.x
		&& m_FinalPos.y <= vMousePos.y && vMousePos.y <= m_FinalPos.y + vScale.y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}


	// �ڽ� UI���� �߰��� ������ ���� ó��
	Tick_DerivedUI();

	// Child Tick
	for (auto childUI : m_ChildUI)
	{
		childUI->Tick();
	}
}

void CUI::Render()
{
	// �ڽ� UI���� ���� ó��
	Render_DerivedUI();

	// Child Render
	for (auto childUI : m_ChildUI)
	{
		childUI->Render();
	}
}