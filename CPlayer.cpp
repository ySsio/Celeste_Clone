#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSpriteRenderer.h"
#include "CAssetMgr.h"
#include "CAnimation.h"


CPlayer::CPlayer()
	: m_HeadSprite(nullptr)
	, m_HeadAnim(nullptr)
	, m_BodyAnim(nullptr)
	, m_Collider(nullptr)
	, m_RigidBody(nullptr)
{
	m_HeadAnim = AddComponent<CAnimator>();
	m_HeadAnim->AddAnimation(L"Player_Bang", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Bang"));
	m_HeadAnim->AddAnimation(L"Player_Bang_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Bang_FlipX"));
	m_HeadAnim->Play(L"Player_Bang");

	m_BodyAnim = AddComponent<CAnimator>();
	m_BodyAnim->AddAnimation(L"Player_Idle", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Idle"));
	m_BodyAnim->AddAnimation(L"Player_IdleA", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleA"));
	m_BodyAnim->AddAnimation(L"Player_IdleB", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleB"));
	m_BodyAnim->AddAnimation(L"Player_IdleC", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleC"));
	m_BodyAnim->AddAnimation(L"Player_Idle_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Idle_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleA_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleA_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleB_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleB_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleC_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleC_FlipX"));
	m_BodyAnim->Play(L"Player_Idle");

	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 48.f));
	m_Collider->SetScale(Vec2(34.f, 68.f));

	m_RigidBody = AddComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	//if (KEY_PRESSED(KEY::UP))
	//{
	//	m_RigidBody->AddForce(Vec2(0.f,-500.f));
	//}
	//if (KEY_PRESSED(KEY::DOWN))
	//{
	//	m_RigidBody->AddForce(Vec2(0.f,500.f));
	//}
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_RigidBody->AddForce(Vec2(-500.f,0.f));
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_RigidBody->AddForce(Vec2(500.f,0.f));
	}

	if (KEY_TAP(KEY::LEFT))
	{
		if (m_HeadAnim)		
			m_HeadAnim->Play(L"Player_Bang_FlipX");
		if (m_BodyAnim)		
			m_BodyAnim->Play(L"Player_Idle_FlipX");
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		if (m_HeadAnim)		
			m_HeadAnim->Play(L"Player_Bang");
		if (m_BodyAnim)		
			m_BodyAnim->Play(L"Player_Idle");
	}

	if (KEY_TAP(KEY::C))
	{
		// Jump
		m_RigidBody->Jump();
		m_RigidBody->SetGravity(true);
	}
	if (KEY_TAP(KEY::X))
	{
		// Dash

	}


	m_RigidBody->FinalTick();
}

void CPlayer::Render()
{
	if (m_HeadAnim)
		m_HeadAnim->Render();

	if (m_BodyAnim)
		m_BodyAnim->Render();
}

#include "CPlatform.h"
#include "CLevelMgr.h"
#include "CTaskMgr.h"

void CPlayer::OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	Vec2 vCurColPos = GetPos() + _Col->GetOffset();
	Vec2 vPrevColPos = GetPrevPos() + _Col->GetOffset();
	Vec2 vColScale = _Col->GetScale();

	float minCurX = vCurColPos.x - vColScale.x / 2.f;
	float maxCurX = vCurColPos.x + vColScale.x / 2.f;
	float minCurY = vCurColPos.y - vColScale.y / 2.f;
	float maxCurY = vCurColPos.y + vColScale.y / 2.f;

	float minPrevX = vPrevColPos.x - vColScale.x / 2.f;
	float maxPrevX = vPrevColPos.x + vColScale.x / 2.f;
	float minPrevY = vPrevColPos.y - vColScale.y / 2.f;
	float maxPrevY = vPrevColPos.y + vColScale.y / 2.f;

	Vec2 vOtherPos = _OtherCol->GetFinalPos();
	Vec2 vOtherColScale = _OtherCol->GetScale();

	float minOtherX = vOtherPos.x - vOtherColScale.x / 2.f;
	float maxOtherX = vOtherPos.x + vOtherColScale.x / 2.f;
	float minOtherY = vOtherPos.y - vOtherColScale.y / 2.f;
	float maxOtherY = vOtherPos.y + vOtherColScale.y / 2.f;

	Vec2 vPos = GetPos();
	Vec2 vVelocity = m_RigidBody->GetVelocity();

	// 오른쪽에서 박음
	if (minPrevX > maxOtherX)
	{
		SetPos(Vec2(vPos.x + (maxOtherX - minCurX), vPos.y));
		m_RigidBody->SetVelocity(Vec2(0.f, vVelocity.y));
	}
	// 위쪽에서 박음
	else if (maxPrevY < minOtherY)
	{
		SetPos(Vec2(vPos.x, vPos.y + (minOtherY - maxCurY)));
		m_RigidBody->SetVelocity(Vec2(vVelocity.x, 0.f));
	}
	// 왼쪽에서 박음
	else if (maxPrevX < minOtherX)
	{
		SetPos(Vec2(vPos.x + (minOtherX - maxCurX), vPos.y));
		m_RigidBody->SetVelocity(Vec2(0.f, vVelocity.y));
	}
	// 아래쪽에서 박음
	else if (minPrevY > maxOtherY)
	{
		SetPos(Vec2(vPos.x, vPos.y + (maxOtherY - minCurY)));
		m_RigidBody->SetVelocity(Vec2(vVelocity.x, 0.f));
	}

	m_RigidBody->SetGravity(false);
	SetPos(Vec2(vPos.x, vPos.y + (minOtherY - maxCurY)));
	m_RigidBody->SetVelocity(Vec2(vVelocity.x, 0.f));

	if (LAYER_TYPE::PLATFORM == _Other->GetType())
	{
		CTileMap* pTileMap = _Other->GetComponent<CTileMap>();
		if (pTileMap->IsTileDanger(_OtherCol))
		{
			tTask task{};
			task.TaskType = TASK_TYPE::CHANGE_LEVEL;
			task.wParam = (DWORD_PTR)CLevelMgr::Get()->GetCurLevel();
			CTaskMgr::Get()->AddTask(task);
		}
	}
}

void CPlayer::OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	
}

void CPlayer::OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	if (m_Collider->GetOverlapCount() == 0)
		m_RigidBody->SetGravity(true);
}
