#pragma once
#include "CBase.h"

class CObj;
class CTexture;
struct tRoom;

class CLevel :
    public CBase
{
private:
    array<vector<CObj*>, (UINT)LAYER_TYPE::END>     m_ArrLayerObj;

    // room
    int             m_PrevRoom;
    int             m_CurRoom;
    vector<tRoom>   m_Room;

    bool            m_RoomMove;
    float           m_AccTime;

    // ¾ø¾Ù º¯¼ö
    Vec2            m_CheckPoint;

public:
    void AddRoom(const tRoom& _Room) { m_Room.push_back(_Room); }
    int GetRoomCount() { return (int)m_Room.size(); }

    int GetCurRoom() { return m_CurRoom; }

public:
    void MoveRoom(int _Room);

public:
    void Save();
    void Load(const wstring& _strRelativeFilePath);

public:
    virtual void Enter() = 0;
    virtual void Exit() final;

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual void Tick_Derived() {}
    virtual void Render_Derived() {}

public:
    Vec2 GetSpawnPoint() { return m_CheckPoint; }
    void SetSpawnPoint(Vec2 _Spawn) { m_CheckPoint = _Spawn; }
    const vector<CObj*>& GetLayer(LAYER_TYPE _Type) { return m_ArrLayerObj[(UINT)_Type]; }


protected:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);

public:
    CLevel();
    ~CLevel();


    friend class CTaskMgr;
};

