#pragma once
#include "CBase.h"

class CObj;
class CTexture;
struct tRoom;

class CLevel :
    public CBase
{
private:
    LEVEL_TYPE      m_Type;
    array<vector<CObj*>, (UINT)LAYER_TYPE::END>     m_ArrLayerObj;

    // room
    int             m_PrevRoom;
    int             m_CurRoom;
    vector<tRoom>   m_Room;

    bool            m_RoomMove;
    float           m_AccTime;

    bool            m_Reset;

public:
    void AddRoom(const tRoom& _Room) { m_Room.push_back(_Room); }
    int GetRoomCount() { return (int)m_Room.size(); }

    int GetCurRoom() { return m_CurRoom; }
    void SetCurRoom(int _Room) { m_PrevRoom = m_CurRoom; m_CurRoom = _Room; }

   vector<tRoom>& GetRooms() { return m_Room; }

   void SetLevelType(LEVEL_TYPE _Type) { m_Type = _Type; }

   void Reset() { m_Reset = true; }

public:
    // 인 게임에서 방을 옮길 떄 사용 (vs SetCurRoom)
    void MoveRoom(int _Room);

public:
    const vector<CObj*>& GetLayer(LAYER_TYPE _Type) { return m_ArrLayerObj[(UINT)_Type]; }

public:
    void SaveWithName(const wstring& _Name);
    void Save(const wstring& _strRelativeFilePath);
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



protected:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);

public:
    CLONE_DISABLE(CLevel)
    CLevel();
    ~CLevel();


    friend class CTaskMgr;
};

