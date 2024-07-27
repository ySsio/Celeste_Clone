#include "pch.h"
#include "CWingBerry.h"

#include "CAssetMgr.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CPlayer.h"

#include "CSaveData.h"

CWingBerry::CWingBerry()
	: m_OriRoom(-1)
	, m_FlyAway(false)
{
	m_Animator->AddAnimation(L"Strawberry_Idle_Wing", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Strawberry_Idle_Wing.anim"));
	m_Animator->AddAnimation(L"Ghostberry_Idle_Wing", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Ghostberry_Idle_Wing.anim"));

	m_Animator->Play(L"Strawberry_Idle_Wing", true);
}

CWingBerry::~CWingBerry()
{
}

void CWingBerry::SetGhost(bool _b)
{
	m_Ghost = _b;

	if (!_b)
		m_Animator->Play(L"Strawberry_Idle_Wing", true);
	else
		m_Animator->Play(L"Ghostberry_Idle_Wing", true);
}

void CWingBerry::Tick()
{
	if (!m_Touched && !m_Collected && !m_FlyAway)
	{
		// 같은 방에 있는 플레이어가 대쉬 하면 위로 날아가서 사라짐
		CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

		if (pPlayer && pPlayer->GetRoom() == GetRoom() && KEY_TAP(KEY::X))
		{
			m_FlyAway = true;
			m_OriRoom = GetRoom();
			StopMove();
			SetPosSmooth(2.f, GetPos() + Vec2(0.f, -900.f));
		}
	}

	if (m_Touched)
	{
		// 만약 날아가던 중이엇으면 정지하고 플레이어를 따라가도록 함
		StopMove();
		m_FlyAway = false;

		// 애니메이션 변경
		if (!m_Ghost)
			m_Animator->Play(L"Strawberry_Idle", true);
		else
			m_Animator->Play(L"Ghostberry_Idle", true);

		// 플레이어 방향 반대 방향으로 offset을 더한 위치를 목표 위치로 설정
		m_TargetPos = m_Target->GetPos() + Vec2(-m_Target->GetDir().x * m_Offset.x, m_Offset.y);

		// 현재 위치에서 타겟 위치로 MoveDuration 동안 갈 수 있도록 보간법 적용
		float Ratio = fDT / m_MoveDuration;
		Vec2 vPos = GetPos() * (1 - Ratio) + m_TargetPos * Ratio;

		// 위치 세팅
		SetPos(vPos);

		// 플레이어가 땅에 닿으면 Collected 상태로 전환
		if (m_Target->IsGround())
		{
			m_Collected = true;
			m_Touched = false;

			// 애니메이션 재생
			if (!m_Ghost)
				m_Animator->Play(L"Strawberry_Collected");
			else
				m_Animator->Play(L"Ghostberry_Collected");

			// Sound 재생
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_red_get_1000.wav");
			pSound->Play();
		}
	}

	if (m_Collected)
	{
		// 수집 애니메이션이 끝나면
		if (m_Animator->IsDone())
		{
			// 이 객체를 파괴
			Delete_Object(this);

			// Game 데이터에 이 딸기가 수집되었다고 저장해줘야 함!!
			if (!m_Ghost && !IsDead())
			{
				auto& stTable = CGameMgr::Get()->GetCurSave()->GetStrawberryTable(GetLevelType());
				stTable[m_StID] = 1;

				CGameMgr::Get()->GetCurSave()->IncrStrawberryCnt();
			}

		}
	}

	if (m_FlyAway && !IsMoving())
	{
		SetRoom(-2);
	}
}

void CWingBerry::Init()
{
	CStrawBerry::Init();

	// 애니메이션 복귀
	if (!m_Ghost)
		m_Animator->Play(L"Strawberry_Idle_Wing", true);
	else
		m_Animator->Play(L"Ghostberry_Idle_Wing", true);

	m_FlyAway = false;

	// 방 복귀
	SetRoom(m_OriRoom);
}

bool CWingBerry::Save(FILE* _pFile)
{
	// 1. 오브젝트 종류를 문자열로 저장
	wstring Type = L"Wingberry";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room 정보 저장
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. 포지션 저장
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Scale 저장
	VecBuff = GetScale();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	return true;
}
