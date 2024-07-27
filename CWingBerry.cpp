#include "pch.h"
#include "CWingBerry.h"

#include "CAssetMgr.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

#include "CSaveData.h"

CWingBerry::CWingBerry()
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
	if (!m_Touched && !m_Collected)
	{
		// 같은 방에 있는 플레이어가 대쉬 하면 위로 날아가서 사라짐

	}

	if (m_Touched)
	{
		// 애니메이션 변경
		if (m_Ghost)
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
}

void CWingBerry::Init()
{
	CStrawBerry::Init();

	// 애니메이션 복귀
	if (!m_Ghost)
		m_Animator->Play(L"Strawberry_Idle_Wing", true);
	else
		m_Animator->Play(L"Ghostberry_Idle_Wing", true);
}
