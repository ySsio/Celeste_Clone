#include "pch.h"
#include "CStrawBerry.h"

#include "CPlayer.h"
#include "CAssetMgr.h"

#include "CTimeMgr.h"

CStrawBerry::CStrawBerry()
	: m_Target(nullptr)
	, m_Offset(Vec2(60.f,20.f))
	, m_Animator(nullptr)
	, m_MoveDuration(0.2f)
	, m_Touched(false)
	, m_Collected(false)
{
	m_Animator = AddComponent<CAnimator>();
	m_Animator->AddAnimation(L"Strawberry_Idle", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Strawberry_Idle.anim"));
	m_Animator->AddAnimation(L"Strawberry_Collected", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Strawberry_Collected.anim"));

	m_Animator->Play(L"Strawberry_Idle",true);

	CCollider* pCol = AddComponent<CCollider>();
	pCol->SetOffset(Vec2(0.f, 0.f));
	pCol->SetScale(Vec2(40.f, 40.f));
	pCol->SetTrigger(true);

}

CStrawBerry::~CStrawBerry()
{
}


void CStrawBerry::Tick()
{
	if (m_Touched)
	{
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
			m_Animator->Play(L"Strawberry_Collected");
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

		}
	}
}

void CStrawBerry::Render()
{
	if (m_Animator)
		m_Animator->Render();
}


void CStrawBerry::OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other);

	if (pPlayer && !m_Collected)
	{
		m_Touched = true;
		m_Target = pPlayer;
	}
}
