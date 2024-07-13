#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"

#include "CObj.h"
#include "CTexture.h"

#include "CGameMgr.h"
#include "CPlayer.h"

#include "CTimeMgr.h"

#include "CCamera.h"

#include "CPathMgr.h"

#include "CPlatform.h"
#include "CSpring.h"
#include "CStrawBerry.h"
#include "CZipMover.h"
#include "CBackGround.h"

CLevel::CLevel()
	: m_PrevRoom(-1)
	, m_CurRoom(-1)
	, m_RoomMove(false)
	, m_AccTime(0.f)
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
	m_ArrLayerObj[(UINT)_Type].push_back(_Obj);
	_Obj->SetLayerType(_Type);

	// 룸 세팅 안된 애들은 새로 추가할 때 현재 room으로 추가함.
	if (_Obj->GetRoom() == -1)
		_Obj->SetRoom(m_CurRoom);
}


void CLevel::SaveWithName(const wstring& _Name)
{
	Save(L"\\map\\" + _Name + L".level");
}

void CLevel::Save(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;

	// 파일을 연다 (각 레벨에 등록된 이름으로 파일 만듦)
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (!pFile) return;

	// ###    Room 정보를 저장    ###
	// 1. Room 개수
	int RoomCnt = (int)m_Room.size();
	fwrite(&RoomCnt, sizeof(int), 1, pFile);

	// 2. m_Room 벡터를 저장
	for (int i = 0; i < RoomCnt; ++i)
	{
		fwrite(&m_Room[i].Position, sizeof(Vec2), 1, pFile);
		fwrite(&m_Room[i].Scale, sizeof(Vec2), 1, pFile);
		
		// 포인트 개수
		int PointCnt = (int)m_Room[i].SpawnPoints.size();
		fwrite(&PointCnt, sizeof(int), 1, pFile);

		// 포인트 벡터 저장
		for (int j = 0; j < PointCnt; ++j)
		{
			fwrite(&m_Room[i].SpawnPoints[j], sizeof(Vec2), RoomCnt, pFile);
		}
	}

	// ###    오브젝트 저장한 array를 돌면서 오브젝트에 Save를 호출함    ###
	for (int Layer = 0; Layer < (int)LAYER_TYPE::END; ++Layer)
	{
		for (CObj* pObj : m_ArrLayerObj[Layer])
		{
			// 1. pObj save를 호출
			// true를 반환하면 실제로 파일에 기록한 거고 false를 반환하면 기록 안된 것
			bool IsSaved = pObj->Save(pFile);

			// 2. save 되는 오브젝트의 경우, 어떤 레이어에 속해있었는지도 추가로 저장
			if (IsSaved)
			{
				fwrite(&Layer, sizeof(int), 1, pFile);
			}
		}
	}

	fclose(pFile);
}



void CLevel::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;

	// 파일을 연다 (각 레벨에 등록된 이름으로 파일 만듦)
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (!pFile) return;

	// ###    Room 정보를 로드    ###
	// 1. Room 개수
	int RoomCnt = 0;
	fread(&RoomCnt, sizeof(int), 1, pFile);

	// 2. m_Room 벡터를 로드
	// resize
	m_Room.resize(RoomCnt);

	for (int i = 0; i < RoomCnt; ++i)
	{
		fread(&m_Room[i].Position, sizeof(Vec2), 1, pFile);
		fread(&m_Room[i].Scale, sizeof(Vec2), 1, pFile);

		// 포인트 개수
		int PointCnt = 0;
		fread(&PointCnt, sizeof(int), 1, pFile);

		// 포인트 벡터 로드
		m_Room[i].SpawnPoints.resize(PointCnt);
		for (int j = 0; j < PointCnt; ++j)
		{
			fread(&m_Room[i].SpawnPoints[j], sizeof(Vec2), RoomCnt, pFile);
		}
	}

	// ###    File 마지막까지 읽으면서 오브젝트에 Load를 호출함    ###
	while (true)
	{
		// 오브젝트 타입
		int len = 0;
		if (fread(&len, sizeof(int), 1, pFile) != 1) break;

		std::vector<wchar_t> szBuff(len + 1);
		if (fread(szBuff.data(), sizeof(wchar_t), len, pFile) != len) break;

		// 오브젝트 타입에 따라 객체 생성
		CObj* pObj = nullptr;

		if (wcscmp(szBuff.data(), L"Platform")==0)
		{
			pObj = new CPlatform;
		}
		else if (wcscmp(szBuff.data(), L"Strawberry") == 0)
		{
			pObj = new CStrawBerry;
		}
		else if (wcscmp(szBuff.data(), L"Spring") == 0)
		{
			pObj = new CSpring;
		}
		else if (wcscmp(szBuff.data(), L"ZipMover") == 0)
		{
			pObj = new CZipMover;
		}
		else if (wcscmp(szBuff.data(), L"BackGround") == 0)
		{
			pObj = new CBackGround;
		}
		else
		{
			assert(nullptr);
		}

		pObj->Load(pFile);


		// Layer 정보 읽음
		int Layer = 0;
		fread(&Layer, sizeof(int), 1, pFile);

		// 레벨에 추가!!
		AddObject(pObj, (LAYER_TYPE)Layer);

		// 파일의 끝에 도달하면 break
		if (feof(pFile))
			break;
	}


	fclose(pFile);
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

	// 플레이어 
	CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

	if (pPlayer)
	{
		// 플레이어 room 이동
		pPlayer->SetRoom(_Room);

		// 플레이어 대쉬 회복
		pPlayer->ResetDash();
	}


	

	// 카메라 이동
	// 1. 카메라 제한범위 설정
	Vec2 RoomPos = m_Room[m_CurRoom].Position;
	Vec2 RoomScale = m_Room[m_CurRoom].Scale;
	Vec2 RoomLT = RoomPos - RoomScale / 2.f;
	Vec2 RoomRB = RoomPos + RoomScale / 2.f;
	CCamera::Get()->SetCamLimit(RoomLT, RoomRB);
	
	// 2. 플레이어 위치 전달 .. 자동으로 제한범위 내에서 카메라 위치 계산
	CCamera::Get()->SetCamEffect(CAM_EFFECT::ROOMMOVE, (UINT_PTR)pPlayer->GetPos());
}


void CLevel::Tick()
{
	// 룸 이동 상태 - duration 동안 tick을 발생시키지 않음.
	if (m_RoomMove)
	{
		m_AccTime += fDT;

		if (m_AccTime >= ROOM_MOVE_DURATION)
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
			{
				++iter;
				continue;
			}

			// Final Tick
			(*iter)->FinalTick();

			++iter;
		}
	}
}

void CLevel::Render()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto iter = Layer.begin(); iter != Layer.end();)
		{
			// Dead 처리된 오브젝트를 제거함
			if ((*iter)->IsDead())
			{
				iter = Layer.erase(iter);
				continue;
			}

			(*iter)->Render();

			++iter;
		}
	}

	Render_Derived();
}

