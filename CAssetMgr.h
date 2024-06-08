#pragma once
#include "CManager.h"

//class CTexture;
//class CAnimation;
//class CSound;

#include "CTexture.h"
#include "CAnimation.h"
#include "CSound.h"
#include "CTile.h"

class CAssetMgr :
    public CManager
{
    SINGLE(CAssetMgr)

private:
    unordered_map<wstring, CTexture*>   m_mapTex;
    unordered_map<wstring, CAnimation*> m_mapAnim;
    unordered_map<wstring, CSound*>     m_mapSound;
    unordered_map<wstring, CTile*>      m_mapTile;

public:
    template <typename T>
    void AddAsset(const wstring& _strName, T* _pAsset);

    template <typename T>
    T* FindAsset(const wstring& _strName);

    template <typename T>
    T* LoadAsset(const wstring& _strName, const wstring& _strFilePath);

public:
    virtual void Init() override;

public:
    CTexture* CreateFlippedTexture(const wstring& _strName, CTexture * _pTex);

private:
	void AddTexture(const wstring& _strName, CTexture* _pAsset) { m_mapTex.emplace(_strName, _pAsset); _pAsset->SetName(_strName); }
	void AddAnimation(const wstring& _strName, CAnimation* _pAsset) { m_mapAnim.emplace(_strName, _pAsset); _pAsset->SetName(_strName); }
	void AddSound(const wstring& _strName, CSound* _pAsset) { m_mapSound.emplace(_strName, _pAsset); _pAsset->SetName(_strName); }
    void AddTile(const wstring& _strName, CTile* _pAsset) { m_mapTile.emplace(_strName, _pAsset); _pAsset->SetName(_strName); }
};

template <typename T>
void CAssetMgr::AddAsset(const wstring& _strName, T* _pAsset)
{
    if (typeid(T) == typeid(CTexture))
    {
        AddTexture(_strName, (CTexture*)_pAsset);
    }
    else if (typeid(T) == typeid(CAnimation))
    {
        AddAnimation(_strName, (CAnimation*)_pAsset);
    }
    else if (typeid(T) == typeid(CSound))
    {
        AddSound(_strName, (CSound*)_pAsset);
    }
    else if (typeid(T) == typeid(CTile))
    {
        AddTile(_strName, (CTile*)_pAsset);
    }
}

#include <typeinfo>
template <typename T>
T* CAssetMgr::FindAsset(const wstring& _strName)
{
    if (typeid(T) == typeid(CTexture))
    {
        auto iter = m_mapTex.find(_strName);
        if (iter == m_mapTex.end()) return nullptr;
        else return (T*)(m_mapTex.find(_strName)->second);
    }
    else if (typeid(T) == typeid(CAnimation))
    {
        auto iter = m_mapAnim.find(_strName);
        if (iter == m_mapAnim.end()) return nullptr;
        else return (T*)(m_mapAnim.find(_strName)->second);
    }
    else if (typeid(T) == typeid(CSound))
    {
        auto iter = m_mapSound.find(_strName);
        if (iter == m_mapSound.end()) return nullptr;
        else return (T*)(m_mapSound.find(_strName)->second);
    }
    else if (typeid(T) == typeid(CTile))
    {
        auto iter = m_mapTile.find(_strName);
        if (iter == m_mapTile.end()) return nullptr;
        else return (T*)(m_mapTile.find(_strName)->second);
    }

    return nullptr;
}


template <typename T>
T* CAssetMgr::LoadAsset(const wstring& _strName, const wstring& _strFilePath)
{
    T* pAsset = FindAsset<T>(_strName);

    if (pAsset)
        return pAsset;

    pAsset = new T;

    pAsset->SetName(_strName);
    pAsset->Load(_strFilePath);

    AddAsset(_strName, pAsset);

    return pAsset;
}