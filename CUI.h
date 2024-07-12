#pragma once
#include "CObj.h"

class CTexture;

class CUI :
    public CObj
{
private:
    Vec2            m_FinalPos;
    CUI*            m_ParentUI;
    vector<CUI*>    m_ChildUI;

    CSpriteRenderer* m_Sprite;

    bool            m_MouseOn;
    bool            m_LbtnDown;

public:
    void SetFinalPos(Vec2 _Pos) { m_FinalPos = _Pos; }
    void SetParent(CUI* _Parent) { m_ParentUI = _Parent; }
    void AddChild(CUI* _Child) { _Child->SetParent(this); m_ChildUI.push_back(_Child); }
    void SetLbtnDown(bool _b) { m_LbtnDown = _b; }

    void SetTex(CTexture* _Tex);
    void SetTexOffset(Vec2 _Offset) { GetSprite()->SetOffset(_Offset); }

    CTexture* GetTex() { return m_Sprite->GetTex(); }

    CSpriteRenderer* GetSprite() { return m_Sprite; }

    Vec2 GetFinalPos() { return m_FinalPos; }
    CUI* GetParent() { return m_ParentUI; }
    const vector<CUI*>& GetChild() { return m_ChildUI; }
    bool IsMouseOn() { return m_MouseOn; }
    bool IsLbtnDown() { return m_LbtnDown; }

    virtual Vec2 GetRenderPos();

public:
    virtual void Tick() final;
    virtual void Render() final;

    virtual void Tick_DerivedUI() = 0;
    virtual void Render_DerivedUI() = 0;

public:
    virtual void LBtnDown() {}      // 눌려있는 상태
    virtual void LBtnUp() {}        // 떼지는 상태
    virtual void LBtnClicked() {}   // 눌렸다가 뗀 상태 (동일 버튼 상에서)

public:
    CUI();
    ~CUI();
};

