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
	, m_Dir(1.f)
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

	m_RigidBody = AddComponent<CRigidBody>();

	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 48.f));
	m_Collider->SetScale(Vec2(34.f, 68.f));

}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	Vec2 vVelocity = m_RigidBody->GetVelocity();
	
	

	if (KEY_PRESSED(KEY::LEFT))
	{
		m_RigidBody->MovePosition(GetPos() + Vec2(-350.f, 0.f) * fDT);
		m_Dir = -1.f;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_RigidBody->MovePosition(GetPos() + Vec2(350.f, 0.f) * fDT);
		m_Dir = 1.f;
	}

	if (KEY_TAP(KEY::LEFT))
	{
		//m_RigidBody->SetVelocity(Vec2(-100.f, vVelocity.y));

		if (m_HeadAnim)		
			m_HeadAnim->Play(L"Player_Bang_FlipX");
		if (m_BodyAnim)		
			m_BodyAnim->Play(L"Player_Idle_FlipX");
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		//m_RigidBody->SetVelocity(Vec2(100.f, vVelocity.y));

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
	else if (KEY_RELEASED(KEY::C))
	{
		m_RigidBody->EndJump();
	}
	


	if (KEY_TAP(KEY::X))
	{
		Vec2 vDir = Vec2(m_Dir, 0.f);

		if (KEY_PRESSED(KEY::UP))
		{
			vDir.y = -1.f;

			if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
				vDir.x = 0.f;
		}
		else if (KEY_PRESSED(KEY::DOWN))
		{
			vDir.y = 1.f;

			if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
				vDir.x = 0.f;
		}
		else
		{
			vDir.y = 0.f;
		}

		// Dash
		m_RigidBody->Dash(vDir);
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
	Vec2 vPos = GetPos();
	Vec2 vColPos = vPos + _Col->GetOffset();
	Vec2 vColScale = _Col->GetScale();

	float minX = vColPos.x - vColScale.x / 2.f;
	float maxX = vColPos.x + vColScale.x / 2.f;
	float minY = vColPos.y - vColScale.y / 2.f;
	float maxY = vColPos.y + vColScale.y / 2.f;

	Vec2 vOtherPos = _OtherCol->GetFinalPos();
	Vec2 vOtherColScale = _OtherCol->GetScale();

	float minOtherX = vOtherPos.x - vOtherColScale.x / 2.f;
	float maxOtherX = vOtherPos.x + vOtherColScale.x / 2.f;
	float minOtherY = vOtherPos.y - vOtherColScale.y / 2.f;
	float maxOtherY = vOtherPos.y + vOtherColScale.y / 2.f;

	float dx = vColPos.x - vOtherPos.x;
	float dy = vColPos.y - vOtherPos.y;

	// 각 축에서의 침투 깊이
	float overlapX = (vColScale.x / 2.f + vOtherColScale.x / 2.f) - std::abs(dx);
	float overlapY = (vColScale.y / 2.f + vOtherColScale.y / 2.f) - std::abs(dy);

	// 침투 깊이가 더 작은 축을 따라 해소
	if (overlapX < overlapY) {
		
		m_RigidBody->SetVelocity(Vec2(0.f, m_RigidBody->GetVelocity().y));
		if (KEY_PRESSED(KEY::Z))
		{
			vPos.x += (dx < 0) ? -overlapX + 0.1f : overlapX - 0.1f;
			m_RigidBody->SetGravity(false);
			m_RigidBody->SetVelocity(Vec2(m_RigidBody->GetVelocity().x, 0.f));
		}
		else
		{
			vPos.x += (dx < 0) ? -overlapX - 0.1f : overlapX + 0.1f;
		}
	}
	else {
		if (dy < 0)
		{
			vPos.y -= overlapY;
			m_RigidBody->SetGravity(false);
			m_RigidBody->SetGround(true);
			m_RigidBody->SetVelocity(Vec2(m_RigidBody->GetVelocity().x, 0.f));
		}
		else
		{
			vPos.y += overlapY;
		}
	}

	SetPos(vPos);
}

void CPlayer::OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	if (m_Collider->GetOverlapCount() == 0)
	{
		m_RigidBody->SetGravity(true);
		m_RigidBody->SetGround(false);
	}
}
