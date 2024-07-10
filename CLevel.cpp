#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"

#include "CObj.h"
#include "CTexture.h"

#include "CGameMgr.h"
#include "CPlayer.h"

#include "CTimeMgr.h"

#include "CCamera.h"

CLevel::CLevel()
	: m_PrevRoom(-1)
	, m_CurRoom(-1)
	, m_RoomMove(false)
	, m_AccTime(0.f)
	, m_RoomMoveDuration(0.3f)
{
}

CLevel::~CLevel()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		Release_Vector(Layer);
	}
}

void CLevel::AddObject(CObj* _Obj, LAYER_TYPE _Type)
{
	m_ArrLayerObj[(UINT)_Type].push_back(_Obj); _Obj->SetLayerType(_Type);
}



void CLevel::Save()
{

}

void CLevel::Load()
{

}

void CLevel::Exit()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		Release_Vector(Layer);
	}
}


void CLevel::MoveRoom(int _Room)
{
	m_PrevRoom = m_CurRoom;
	m_CurRoom = _Room;

	m_RoomMove = true;

	// 플레이어 대쉬 회복
	CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

	if (pPlayer)
		pPlayer->ResetDash();
}


void CLevel::Tick()
{
	// 룸 이동 상태 - duration 동안 tick을 발생시키지 않음.
	if (m_RoomMove)
	{
		m_AccTime += fDT;

		if (m_AccTime >= m_RoomMoveDuration)
		{
			m_AccTime = 0.f;
			m_RoomMove = false;
		}
	}

	CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

	if (pPlayer)
	{
		Vec2 vPlayerPos = pPlayer->GetPos();
	
		// 플레이어의 위치로 현재 room이 어딘지 판정
		for (int i=0; i<m_Room.size(); ++i)
		{
			const tRoom& room = m_Room[i];

			if (room.Position.x - room.Scale.x / 2.f <= vPlayerPos.x
				&& vPlayerPos.x <= room.Position.x + room.Scale.x / 2.f
				&& room.Position.y - room.Scale.y / 2.f <= vPlayerPos.y
				&& vPlayerPos.y <= room.Position.y + room.Scale.y / 2.f)
			{
				if (m_CurRoom != i)
				{
					MoveRoom(i);
				}
			}
		}
	}
	
	
	
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto obj : Layer)
		{
			// 이전 룸에 해당하는 오브젝트는 초기화 (컴포넌트 초기화도 여기서 처리)
			if (m_RoomMove && obj->GetRoom() == m_PrevRoom)
				obj->Init();

			// 현재 룸에 해당하는 오브젝트만 업데이트
			else if (obj->GetRoom() == m_CurRoom)
				obj->Tick();
		}
	}

	Tick_Derived();
}

void CLevel::FinalTick()
{
	if (m_RoomMove)
		return;

	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto iter = Layer.begin(); iter != Layer.end();)
		{
			// 현재 룸에 있는 오브젝트가 아니면 넘어감
			if ((*iter)->GetRoom() != m_CurRoom)
				continue;

			// Final Tick
			(*iter)->FinalTick();

			// Dead 처리된 오브젝트를 제거함
			if ((*iter)->IsDead())
			{
				iter = Layer.erase(iter);
				continue;
			}
			++iter;
		}
	}
}

void CLevel::Render()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto& obj : Layer)
		{
			obj->Render();
		}
	}

	Render_Derived();
}

