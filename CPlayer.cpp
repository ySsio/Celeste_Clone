#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSpriteRenderer.h"
#include "CAssetMgr.h"
#include "CAnimation.h"

#include "CState_Idle.h"
#include "CState_Run.h"
#include "CState_Dash.h"
#include "CState_Climb.h"
#include "CState_Fall.h"
#include "CState_Jump.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CAfterImage.h"

CPlayer::CPlayer()
	: m_Sprite(nullptr)
	, m_BangAnim(nullptr)
	, m_BodyAnim(nullptr)
	, m_StateMachine(nullptr)
	, m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Dir(Vec2(1.f,0.f))
	, m_DirChanged(false)
	, m_Color(BANG_COLOR::PINK)
{
	m_BodyAnim = AddComponent<CAnimator>();
	m_BodyAnim->AddAnimation(L"Player_Idle", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Idle.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleA", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleA.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleB", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleB.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleC", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleC.anim"));
	m_BodyAnim->AddAnimation(L"Player_Walk", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Walk.anim"));
	m_BodyAnim->AddAnimation(L"Player_Run", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Run.anim"));
	m_BodyAnim->AddAnimation(L"Player_Jump", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Jump.anim"));
	m_BodyAnim->AddAnimation(L"Player_Fall", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Fall.anim"));
	m_BodyAnim->AddAnimation(L"Player_Dash", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Dash.anim"));
	m_BodyAnim->AddAnimation(L"Player_Idle_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Idle_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleA_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleA_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleB_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleB_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleC_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleC_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Walk_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Walk_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Run_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Run_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Jump_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Jump_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Fall_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Fall_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Dash_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Dash_FlipX.anim"));
	m_BodyAnim->Play(L"Player_Idle");

	m_BangAnim = AddComponent<CAnimator>();
	m_BangAnim->AddAnimation(L"Player_Bang_Idle", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Idle.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleA", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleA.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleB", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleB.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleC", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleC.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Walk", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Walk.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Run", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Run.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Jump", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Jump.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Fall", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Fall.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Dash", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Dash.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Idle_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Idle_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleA_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleA_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleB_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleB_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleC_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleC_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Walk_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Walk_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Run_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Run_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Jump_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Jump_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Fall_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Fall_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Dash_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Dash_FlipX.anim"));
	m_BangAnim->Play(L"Player_Bang_Idle");


	m_StateMachine = AddComponent<CStateMachine>();
	m_StateMachine->AddState(L"Idle", new CState_Idle);
	m_StateMachine->AddState(L"Run", new CState_Run);
	m_StateMachine->AddState(L"Dash", new CState_Dash);
	m_StateMachine->AddState(L"Hang", new CState_Climb);
	m_StateMachine->AddState(L"Fall", new CState_Fall);
	m_StateMachine->AddState(L"Jump", new CState_Jump);
	m_StateMachine->ChangeState(L"Idle");


	m_RigidBody = AddComponent<CRigidBody>();


	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 50.f));
	m_Collider->SetScale(Vec2(40.f, 60.f));


	m_Buffer = new CTexture;
	m_Buffer->CreateTexture(160,160);

	m_Sprite = AddComponent<CSpriteRenderer>();
	m_Sprite->SetTexture(m_Buffer);
}

CPlayer::~CPlayer()
{
	delete m_Buffer;
}

#include "CLogMgr.h"

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	static float AccTime = 0.f;
	static float ColorChangeDuration = 0.1f;

	if (m_Color == BANG_COLOR::WHITE)
	{
		AccTime += fDT;
	}

	if (m_RigidBody->GetDashLeftCount() == 2)
	{
		// red/blue -> white -> pink
		if (m_Color == BANG_COLOR::RED || m_Color == BANG_COLOR::BLUE)
		{
			m_Color = BANG_COLOR::WHITE;
		}
		else if (m_Color == BANG_COLOR::WHITE && AccTime >= ColorChangeDuration)
		{
			m_Color = BANG_COLOR::PINK;
			AccTime = 0.f;
		}
	}
	else if (m_RigidBody->GetDashLeftCount() == 1)
	{
		// 1. pink -> red
		// 2. blue -> white -> red
		if (m_Color == BANG_COLOR::BLUE)
		{
			m_Color = BANG_COLOR::WHITE;
		}
		else if ((m_Color == BANG_COLOR::WHITE && AccTime >= ColorChangeDuration) || m_Color == BANG_COLOR::PINK)
		{
			m_Color = BANG_COLOR::RED;
			AccTime = 0.f;
		}
	}
	else if (m_RigidBody->GetDashLeftCount() == 0)
	{
		// red -> blue
		if (m_Color == BANG_COLOR::RED)
		{
			m_Color = BANG_COLOR::BLUE;
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		DEBUG_LOG(LOG_LEVEL::LOG, L"Player Position : " + std::to_wstring(vPos.x) + L", " + std::to_wstring(vPos.y));
	}

	Vec2 vVelocity = m_RigidBody->GetVelocity();

	m_DirChanged = false;
	
	bool Left = KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT);
	bool Right = KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT);
	
	if (Left && !Right)
	{
		if (m_Dir.x != -1.f)
		{
			m_Dir.x = -1.f;
			m_DirChanged = true;
		}
	}
	else if (!Left && Right)
	{
		if (m_Dir.x != 1.f)
		{
			m_Dir.x = 1.f;
			m_DirChanged = true;
		}
	}

	if (KEY_TAP(KEY::UP) || KEY_PRESSED(KEY::UP))
	{
		m_Dir.y = -1.f;
	}
	else if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		m_Dir.y = 1.f;
	}
	else
	{
		m_Dir.y = 0.f;
	}
}

void CPlayer::Render()
{
	if (m_Sprite)
		m_Sprite->ClearTex();

	if (m_BangAnim)
		m_BangAnim->Render(m_Buffer->GetDC(), true);

	if (m_BodyAnim)
		m_BodyAnim->Render(m_Buffer->GetDC(), true);

	if (m_Sprite)
		m_Sprite->Render();
}

#include "CPlatform.h"
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
	// 옆으로 닿은 경우
	if (overlapX < overlapY) {
		m_RigidBody->SetGround(true);
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
	// 상하로 닿은 경우
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
		if (!m_RigidBody->IsDash())
			m_RigidBody->SetGravity(true);
		m_RigidBody->SetGround(false);
	}
}
