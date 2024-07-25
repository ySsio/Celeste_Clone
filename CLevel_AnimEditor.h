#pragma once
#include "CLevel_Editor.h"

class CAnimEditorUI;
class CTextUI;
class CTextBoxUI;
class CAnimation;
struct tAnimFrm;

class CLevel_AnimEditor :
    public CLevel_Editor
{
private:
    CAnimEditorUI* m_AnimEditorUI;

    UINT    m_BangFrm;
    UINT    m_BodyFrm;
    UINT    m_BangFrmCnt;
    UINT    m_BodyFrmCnt;

    vector<tAnimFrm> m_OriBangFrm;
    vector<tAnimFrm> m_OriBodyFrm;

    CTextUI* m_BangFrmTxt;
    CTextUI* m_BodyFrmTxt;
    CTextUI* m_BangFrmCntTxt;
    CTextUI* m_BodyFrmCntTxt;

    CTextBoxUI* m_BangName;
    CTextBoxUI* m_BangOffsetX;
    CTextBoxUI* m_BangOffsetY;
    CTextBoxUI* m_BangDuration;

    CTextBoxUI* m_BodyName;
    CTextBoxUI* m_BodyOffsetX;
    CTextBoxUI* m_BodyOffsetY;
    CTextBoxUI* m_BodyDuration;

public:
    void SetBangAnim(CAnimation* _Anim);
    void SetBodyAnim(CAnimation* _Anim);

    CTextUI* GetBangFrmTxt() { return m_BangFrmTxt; }
    CTextUI* GetBodyFrmTxt() { return m_BodyFrmTxt; }
    CTextUI* GetBangFrmCntTxt() { return m_BangFrmCntTxt; }
    CTextUI* GetBodyFrmCntTxt() { return m_BodyFrmCntTxt; }


public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived() override;


public:
    void LoadBangVariables();
    void LoadBodyVariables();


public:
    void CreateBangAnimation();
    void SaveBangAnimation(const wstring& _strRelativePath);
    void LoadBangAnimation();

    void CreateBodyAnimation();
    void SaveBodyAnimation(const wstring& _strRelativePath);
    void LoadBodyAnimation();


public:
    CLevel_AnimEditor();
    ~CLevel_AnimEditor();
};

