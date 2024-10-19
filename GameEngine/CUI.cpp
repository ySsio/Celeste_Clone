#include "pch.h"
#include "CUI.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTexture.h"

CUI::CUI()
	: m_ParentUI(nullptr)
	, m_Sprite(nullptr)
	, m_MouseOn(false)
	, m_LbtnDown(false)
{
	m_Sprite = AddComponent<CSpriteRenderer>();
}

CUI::CUI(const CUI& _Other)
	: CObj(_Other)
	, m_ParentUI(nullptr)
	, m_Sprite(_Other.m_Sprite)
	, m_MouseOn(false)
	, m_LbtnDown(false)
{
	m_Sprite = GetComponent<CSpriteRenderer>();

	// 자식 UI 복사
	for (auto child : _Other.m_ChildUI)
	{
		CUI* pCopyChild = child->Clone(); // copy constructor

		pCopyChild->m_ParentUI = this;
		m_ChildUI.push_back(pCopyChild);

	}
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
		m_FinalPos += m_ParentUI->GetFinalPos();

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


	// 자식 UI에서 추가로 수행할 내용 처리
	Tick_DerivedUI();

	// Child Tick
	for (auto childUI : m_ChildUI)
	{
		childUI->Tick();
		childUI->FinalTick();
	}
}

void CUI::Render()
{
	// 자식 UI에서 렌더 처리
	Render_DerivedUI();

	// Child Render
	for (auto childUI : m_ChildUI)
	{
		childUI->Render();
	}
}