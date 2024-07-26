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
    LEVEL_TYPE  m_LevelType;
    LAYER_TYPE  m_LayerType;
    Vec2        m_Pos;
    Vec2        m_Scale;

    int         m_Room;

    vector<CComponent*> m_vecComponent;

    bool        m_Dead;

    // 부드럽게 이동
    bool        m_Moving;
    Vec2        m_StartPos;
    Vec2        m_TargetPos;
    float       m_AccTime;
    float       m_Duration;

public:
    void SetLevelType(LEVEL_TYPE _Type) { m_LevelType = _Type; }
    LEVEL_TYPE GetLevelType() { return m_LevelType; }
    
    void SetLayerType(LAYER_TYPE _Type) { m_LayerType = _Type; }
    LAYER_TYPE GetLayerType() { return m_LayerType; }


    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetPosSmooth(float _Duration, Vec2 _Pos);

    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    void SetDead() { m_Dead = true; }
    void SetRoom(int _Room) { m_Room = _Room; }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    virtual Vec2 GetRenderPos();
    bool IsDead() { return m_Dead; }
    bool IsMoving() { return m_Moving; }
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
    T* AddComponent(T* _Comp)
    {
        m_vecComponent.push_back(_Comp);
        _Comp->SetOwner(this);
        return _Comp;
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

    const vector<CComponent*>& GetComponents() { return m_vecComponent; }

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
    virtual CObj* Clone() override = 0;
    ~CObj();
};

