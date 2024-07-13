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

	// �� ���� �ȵ� �ֵ��� ���� �߰��� �� ���� room���� �߰���.
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

	// ������ ���� (�� ������ ��ϵ� �̸����� ���� ����)
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (!pFile) return;

	// ###    Room ������ ����    ###
	// 1. Room ����
	int RoomCnt = (int)m_Room.size();
	fwrite(&RoomCnt, sizeof(int), 1, pFile);

	// 2. m_Room ���͸� ����
	for (int i = 0; i < RoomCnt; ++i)
	{
		fwrite(&m_Room[i].Position, sizeof(Vec2), 1, pFile);
		fwrite(&m_Room[i].Scale, sizeof(Vec2), 1, pFile);
		
		// ����Ʈ ����
		int PointCnt = (int)m_Room[i].SpawnPoints.size();
		fwrite(&PointCnt, sizeof(int), 1, pFile);

		// ����Ʈ ���� ����
		for (int j = 0; j < PointCnt; ++j)
		{
			fwrite(&m_Room[i].SpawnPoints[j], sizeof(Vec2), RoomCnt, pFile);
		}
	}

	// ###    ������Ʈ ������ array�� ���鼭 ������Ʈ�� Save�� ȣ����    ###
	for (int Layer = 0; Layer < (int)LAYER_TYPE::END; ++Layer)
	{
		for (CObj* pObj : m_ArrLayerObj[Layer])
		{
			// 1. pObj save�� ȣ��
			// true�� ��ȯ�ϸ� ������ ���Ͽ� ����� �Ű� false�� ��ȯ�ϸ� ��� �ȵ� ��
			bool IsSaved = pObj->Save(pFile);

			// 2. save �Ǵ� ������Ʈ�� ���, � ���̾ �����־������� �߰��� ����
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

	// ������ ���� (�� ������ ��ϵ� �̸����� ���� ����)
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (!pFile) return;

	// ###    Room ������ �ε�    ###
	// 1. Room ����
	int RoomCnt = 0;
	fread(&RoomCnt, sizeof(int), 1, pFile);

	// 2. m_Room ���͸� �ε�
	// resize
	m_Room.resize(RoomCnt);

	for (int i = 0; i < RoomCnt; ++i)
	{
		fread(&m_Room[i].Position, sizeof(Vec2), 1, pFile);
		fread(&m_Room[i].Scale, sizeof(Vec2), 1, pFile);

		// ����Ʈ ����
		int PointCnt = 0;
		fread(&PointCnt, sizeof(int), 1, pFile);

		// ����Ʈ ���� �ε�
		m_Room[i].SpawnPoints.resize(PointCnt);
		for (int j = 0; j < PointCnt; ++j)
		{
			fread(&m_Room[i].SpawnPoints[j], sizeof(Vec2), RoomCnt, pFile);
		}
	}

	// ###    File ���������� �����鼭 ������Ʈ�� Load�� ȣ����    ###
	while (true)
	{
		// ������Ʈ Ÿ��
		int len = 0;
		if (fread(&len, sizeof(int), 1, pFile) != 1) break;

		std::vector<wchar_t> szBuff(len + 1);
		if (fread(szBuff.data(), sizeof(wchar_t), len, pFile) != len) break;

		// ������Ʈ Ÿ�Կ� ���� ��ü ����
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


		// Layer ���� ����
		int Layer = 0;
		fread(&Layer, sizeof(int), 1, pFile);

		// ������ �߰�!!
		AddObject(pObj, (LAYER_TYPE)Layer);

		// ������ ���� �����ϸ� break
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

	// �÷��̾� 
	CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

	if (pPlayer)
	{
		// �÷��̾� room �̵�
		pPlayer->SetRoom(_Room);

		// �÷��̾� �뽬 ȸ��
		pPlayer->ResetDash();
	}


	

	// ī�޶� �̵�
	// 1. ī�޶� ���ѹ��� ����
	Vec2 RoomPos = m_Room[m_CurRoom].Position;
	Vec2 RoomScale = m_Room[m_CurRoom].Scale;
	Vec2 RoomLT = RoomPos - RoomScale / 2.f;
	Vec2 RoomRB = RoomPos + RoomScale / 2.f;
	CCamera::Get()->SetCamLimit(RoomLT, RoomRB);
	
	// 2. �÷��̾� ��ġ ���� .. �ڵ����� ���ѹ��� ������ ī�޶� ��ġ ���
	CCamera::Get()->SetCamEffect(CAM_EFFECT::ROOMMOVE, (UINT_PTR)pPlayer->GetPos());
}


void CLevel::Tick()
{
	// �� �̵� ���� - duration ���� tick�� �߻���Ű�� ����.
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
	
		// �÷��̾��� ��ġ�� ���� room�� ����� ����
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
			// ���� �뿡 �ش��ϴ� ������Ʈ�� �ʱ�ȭ (������Ʈ �ʱ�ȭ�� ���⼭ ó��)
			if (m_RoomMove && obj->GetRoom() == m_PrevRoom)
				obj->Init();

			// ���� �뿡 �ش��ϴ� ������Ʈ�� ������Ʈ
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
			// ���� �뿡 �ִ� ������Ʈ�� �ƴϸ� �Ѿ
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
			// Dead ó���� ������Ʈ�� ������
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

