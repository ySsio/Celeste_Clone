#pragma once
#include "CBase.h"

// component
#include "CSpriteRenderer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CTileMap.h"
#include "CRigidBody.h"

class CComponent;

class CObj :
    public CBase
{
private:
    LAYER_TYPE  m_Type;
    Vec2        m_Pos;
    Vec2        m_Scale;


    vector<CComponent*> m_vecComponent;

    bool        m_Dead;

public:
    void SetLayerType(LAYER_TYPE _Type) { m_Type = _Type; }
    void SetPos(Vec2 _vPos) {
        m_Pos = _vPos; 
    }
    void SetScale(float _x, float _y) { m_Scale.x = _x; m_Scale.y = _y; }
    void SetDead() { m_Dead = true; }

    LAYER_TYPE GetType() { return m_Type; }
    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    Vec2 GetRenderPos();
    bool IsDead() { return m_Dead; }

    template<typename T>
    T* AddComponent()
    {
        T* pComp = new T();
        m_vecComponent.push_back(pComp);
        pComp->SetOwner(this);
        return pComp;
    }

    template<typename T>
    T* GetComponent()
    {
        for (auto comp : m_vecComponent)
        {
            T* pComponent = dynamic_cast<T*>(comp);

            if (pComponent)
                return pComponent;
        }

        return nullptr;
    }

    template<typename T>
    vector<T*> GetComponents()
    {
        vector<T*> ret;
        for (auto comp : m_vecComponent)
        {
            T* pComponent = dynamic_cast<T*>(comp);

            if (pComponent)
                ret.push_back(pComponent);
        }

        return ret;
    }

public:
    virtual void Tick() = 0;
    virtual void FinalTick();
    virtual void Render();

public:
	virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}
	virtual void OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}
	virtual void OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}

public:
    CObj();
    CObj(const CObj& _other);
    ~CObj();
};

