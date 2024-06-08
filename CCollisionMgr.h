#pragma once
#include "CManager.h"

class CObj;
class CCollider;

union COLLISION_ID
{
    DWORD_PTR ID;
    struct
    {
        UINT ID1;
        UINT ID2;
    };
};


class CCollisionMgr :
    public CManager
{
    SINGLE(CCollisionMgr)

private:
    array<UINT, (UINT)LAYER_TYPE::END> m_Matrix;

    // collider만 따로 관리
    array<vector<CCollider*>, (UINT)LAYER_TYPE::END> m_arrCollider;

    unordered_map<DWORD_PTR, bool> m_ColInfo;

public:
    void RegisterCollisionLayer(LAYER_TYPE _Type1, LAYER_TYPE _Type2, bool _b);
    void RegisterCollider(CCollider* _Collider, LAYER_TYPE _LayerType)
    {
        m_arrCollider[(UINT)_LayerType].push_back(_Collider);
    }
    void CollisionLayerCheck(UINT _Layer1, UINT _Layer2);
    bool CollisionCheck(CCollider* _Obj1, CCollider* _Obj2);

public:
    virtual void Init() override;
    void Tick();

};

