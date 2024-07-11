#pragma once
#include "CBase.h"

// component
#include "CSpriteRenderer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CTileMap.h"
#include "CRigidBody.h"
#include "CStateMachine.h"

class CComponent;

class CObj :
    public CBase
{
private:
    LAYER_TYPE  m_Type;
    Vec2        m_Pos;
    Vec2        m_Scale;

    int         m_Room;

    vector<CComponent*> m_vecComponent;

    bool        m_PlayerDead;

public:
    void SetLayerType(LAYER_TYPE _Type) { m_Type = _Type; }
    void SetPos(Vec2 _vPos) {
        m_Pos = _vPos; 
    }
    void SetScale(float _x, float _y) { m_Scale.x = _x; m_Scale.y = _y; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    void SetDead() { m_PlayerDead = true; }
    void SetRoom(int _Room) { m_Room = _Room; }

    LAYER_TYPE GetType() { return m_Type; }
    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    Vec2 GetRenderPos();
    bool IsDead() { return m_PlayerDead; }
    int GetRoom() { return m_Room; }

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
    virtual void Init() {}
    virtual void Tick() = 0;
    virtual void FinalTick();
    virtual void Render();

public:
    // Save가 구현된 애들은 true를 반환.
    virtual bool Save(FILE* _pFile) { return false; }
    virtual void Load(FILE* _pFile) {}

public:
	virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}
	virtual void OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}
	virtual void OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) {}

public:
    CObj();
    CObj(const CObj& _other);
    ~CObj();
};

