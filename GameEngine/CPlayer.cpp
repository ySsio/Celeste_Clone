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
#include "CState_Dead.h"
#include "CState_Bounce.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CAfterImage.h"


#include "CSpring.h"
#include "CZipMover.h"
#include "CCrumbleBlock.h"

#include "CEngine.h"

#include "CCamera.h"


CPlayer::CPlayer()
	: m_Tex(nullptr)
	, m_BangAnim(nullptr)
	, m_BodyAnim(nullptr)
	, m_StateMachine(nullptr)
	, m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Buffer(nullptr)
	, m_Dir(Vec2(1.f,0.f))
	, m_DirChanged(false)
	, m_DirFix(false)
	, m_DashMaxCount(1)
	, m_DashCount(1)
	, m_IsGround(false)
	, m_IsWall(false)
	, m_ColUpdated(false)
	, m_Stamina(PLAYER_STAMINA)
	, m_Color(BANG_COLOR::PINK)
	, m_ColorChangeDuration(0.1f)
	, m_HairCount(5)
	, m_HairTex(nullptr)
	, m_HairSize{ 40.f, 35.f, 30.f, 25.f, 20.f }
	, m_HairOffset{ 18.f, 14.f, 8.f, 5.f }
	, m_HairCurPos(m_HairCount, Vec2(BODY_SCALE/2.f, BODY_SCALE/2.f))
	, m_HairTargetPos(m_HairCount)
	, m_PlayerDead(false)

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
	m_BodyAnim->AddAnimation(L"Player_Climb", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Climb.anim"));
	m_BodyAnim->AddAnimation(L"Player_Climb_Warning", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Climb_Warning.anim"));
	m_BodyAnim->AddAnimation(L"Player_Dead", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Dead.anim"));
	m_BodyAnim->AddAnimation(L"Player_Idle_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Idle_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleA_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleA_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleB_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleB_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_IdleC_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_IdleC_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Walk_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Walk_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Run_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Run_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Jump_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Jump_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Fall_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Fall_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Dash_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Dash_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Climb_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Climb_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Climb_Warning_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Climb_Warning_FlipX.anim"));
	m_BodyAnim->AddAnimation(L"Player_Dead_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Dead_FlipX.anim"));
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
	m_BangAnim->AddAnimation(L"Player_Bang_Climb", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Climb.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Idle_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Idle_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleA_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleA_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleB_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleB_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_IdleC_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_IdleC_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Walk_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Walk_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Run_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Run_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Jump_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Jump_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Fall_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Fall_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Dash_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Dash_FlipX.anim"));
	m_BangAnim->AddAnimation(L"Player_Bang_Climb_FlipX", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Player_Bang_Climb_FlipX.anim"));
	m_BangAnim->Play(L"Player_Bang_Idle");


	m_StateMachine = AddComponent<CStateMachine>();
	m_StateMachine->AddState(L"Idle", new CState_Idle);
	m_StateMachine->AddState(L"Run", new CState_Run);
	m_StateMachine->AddState(L"Dash", new CState_Dash);
	m_StateMachine->AddState(L"Climb", new CState_Climb);
	m_StateMachine->AddState(L"Fall", new CState_Fall);
	m_StateMachine->AddState(L"Jump", new CState_Jump);
	m_StateMachine->AddState(L"Dead", new CState_Dead);
	m_StateMachine->AddState(L"Bounce", new CState_Bounce);
	m_StateMachine->ChangeState(L"Idle");


	m_RigidBody = AddComponent<CRigidBody>();


	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 50.f));
	m_Collider->SetScale(Vec2(40.f, 60.f));


	m_WallDetector = AddComponent<CCollider>();
	m_WallDetector->SetScale(Vec2(10.f, 40.f));
	

	m_Buffer = new CTexture;
	m_Buffer->CreateTexture(160,160);

	m_Tex = AddComponent<CSpriteRenderer>();
	m_Tex->SetTex(m_Buffer);
}

CPlayer::~CPlayer()
{
	delete m_Buffer;
}

#include "CLogMgr.h"

void CPlayer::Tick()
{
	// Bang Color Update
	if (!m_PlayerDead)
		BangColorUpdate();

	// Direction Update
	if (!m_DirFix)
		DirectionUpdate();

	// GrabDetector Offset Update
	m_WallDetector->SetOffset(Vec2(20.f * m_Dir.x, 50.f));

	// ColUpdated 초기화 (이번 프레임에서 처음 collision 이벤트 발생했을 때를 찾기 위함)
	m_ColUpdated = false;

	// Hair Poisition Update
	if (!m_PlayerDead)
		HairPosUpdate();
}


void CPlayer::Render()
{
	// clear Buffer
	if (m_Tex)
		m_Tex->ClearTex();

	// hair render
	if (!m_PlayerDead && m_HairTex)
	{
		for (int i = 0; i < m_HairCount; ++i)
		{
			float size = m_HairSize[i];

			m_HairTex = m_HairTex->Stretch(Vec2(size, size));

			int Width = m_HairTex->GetWidth();
			int Height = m_HairTex->GetHeight();

			BLENDFUNCTION blend{};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(m_Buffer->GetDC()
				, (int)(m_HairCurPos[i].x - Width / 2.f)
				, (int)(m_HairCurPos[i].y - Height / 2.f)
				, Width, Height
				, m_HairTex->GetDC()
				, 0, 0
				, Width, Height
				, blend);
		}
	}


	// bang render
	if (m_BangAnim)
		m_BangAnim->Render(m_Buffer->GetDC(), true);


	// body render
	if (m_BodyAnim)
		m_BodyAnim->Render(m_Buffer->GetDC(), true);

	
	// Buffer to BackDC
	if (m_Tex)
		m_Tex->Render();

}

void CPlayer::BangColorUpdate()
{
	static float AccTime = 0.f;

	if (m_Color == BANG_COLOR::WHITE)
	{
		AccTime += fDT;
	}

	if (m_DashCount == 2)
	{
		// red/blue -> white -> pink
		if (m_Color == BANG_COLOR::RED || m_Color == BANG_COLOR::BLUE)
		{
			m_Color = BANG_COLOR::WHITE;
		}
		else if (m_Color == BANG_COLOR::WHITE && AccTime >= m_ColorChangeDuration)
		{
			m_Color = BANG_COLOR::PINK;
			AccTime = 0.f;
		}
	}
	else if (m_DashCount == 1)
	{
		// 1. pink -> white -> red
		// 2. blue -> white -> red
		if (m_Color == BANG_COLOR::BLUE || m_Color == BANG_COLOR::PINK)
		{
			m_Color = BANG_COLOR::WHITE;
		}
		else if (m_Color == BANG_COLOR::WHITE && AccTime >= m_ColorChangeDuration)
		{
			m_Color = BANG_COLOR::RED;
			AccTime = 0.f;
		}
	}
	else if (m_DashCount == 0)
	{
		// red -> white -> blue
		if (m_Color == BANG_COLOR::RED)
		{
			m_Color = BANG_COLOR::WHITE;
		}
		if (m_Color == BANG_COLOR::WHITE && AccTime >= m_ColorChangeDuration)
		{
			m_Color = BANG_COLOR::BLUE;
		}
	}
}

void CPlayer::DirectionUpdate()
{
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

void CPlayer::HairPosUpdate()
{
	// Player Buffer에 해당하는 Offset
	Vec2 vOffset = Vec2(BODY_SCALE / 2.f, BODY_SCALE / 2.f);
	Vec2 vPos = vOffset + m_BangAnim->GetCurFrm().Offset;


	// 플레이어의 속도와 반대되는 방향으로 hair 들이 이동
	Vec2 vDir = -m_RigidBody->GetVelocity();

	// y축 속도가 0일 때는 중력 방향으로 설정
	if (vDir.y == 0.f)
		vDir.y = 1.f;
	
	vDir.Normalize();

	// 각 hair들의 target pos를 직전 hair의 curpos를 기준으로 vDir 방향으로 
	// hairoffset만큼 떨어진 지점으로 설정
	m_HairTargetPos[0] = vPos;
	for (int i = 1; i < m_HairCount; ++i)
	{
		m_HairTargetPos[i] = m_HairCurPos[i - 1] + vDir * m_HairOffset[i - 1];
	}

	float Duration = 0.03f;

	// 각 hair들의 curpos를 curpos부터 targetpos까지 Duration만에 도착하는 속도로 보간.
	m_HairCurPos[0] = vPos;
	for (int i = 1; i < m_HairCount; ++i)
	{
		m_HairCurPos[i] = m_HairTargetPos[i] * (fDT / Duration) + m_HairCurPos[i] * (1 - fDT / Duration);

		// 여기 주석걸면 뛸때 머리카락 살랑살랑 흔들림
		//if ((m_HairTargetPos[i] - m_HairCurPos[i]).Length() < 5.f)
		//{
		//	m_HairCurPos[i] = m_HairTargetPos[i];
		//}
	}

	// 현재 BangColor에 맞춰서 Hair Texture도 변경
	if (m_Color == BANG_COLOR::PINK)
		m_HairTex = CAssetMgr::Get()->FindAsset<CTexture>(L"hair_pink");
	else if (m_Color == BANG_COLOR::RED)
		m_HairTex = CAssetMgr::Get()->FindAsset<CTexture>(L"hair_red");
	else if (m_Color == BANG_COLOR::BLUE)
		m_HairTex = CAssetMgr::Get()->FindAsset<CTexture>(L"hair_blue");
	else
		m_HairTex = CAssetMgr::Get()->FindAsset<CTexture>(L"hair_white");
}

#include "CPlatform.h"
#include "CTaskMgr.h"

void CPlayer::OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	if (m_PlayerDead)
		return;

	// 충돌한 오브젝트가 플랫폼인 경우
	if (_Other->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		CTileMap* pTileMap = _Other->GetComponent<CTileMap>();
		if (pTileMap->IsTileDanger(_OtherCol))
		{
			m_BounceDir = GetPos() - _OtherCol->GetFinalPos();
			m_BounceDir.Normalize();

			m_StateMachine->ChangeState(L"Dead");
		}

		
	}
	else if (_Other->GetLayerType() == LAYER_TYPE::OBJ)
	{
		CSpring* pSpring = dynamic_cast<CSpring*>(_Other);

		// 스프링과 부딪힌 경우
		if (pSpring)
		{
			// Bounce 상태 진입
			CState_Bounce* pState = dynamic_cast<CState_Bounce*>(m_StateMachine->FindState(L"Bounce"));
			pState->SetDir(pSpring->GetDir());

			m_StateMachine->ChangeState(L"Bounce");
		}
	}
	
}

void CPlayer::OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	if (m_PlayerDead)
		return;

	if (!m_ColUpdated)
	{
		m_IsGround = false;
		m_IsWall = false;
		m_ColUpdated = true;
	}

	if (_Col == m_Collider)
	{
		if (!_OtherCol->IsTrigger())
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
			if (overlapX < overlapY)
			{
				// 겹친 길이만큼 다시 밀어냄
				vPos.x += (dx < 0) ? -overlapX : overlapX;

				
			}
			// 상하로 닿은 경우
			else if (overlapX > overlapY)
			{
				// 플레이어가 충돌체 위에서 닿은 경우
				if (dy < 0)
				{
					// 겹친 길이만큼 다시 밀어냄
					vPos.y -= overlapY;
					m_RigidBody->SetGravity(false);

					// Ground 세팅
					m_IsGround = true;

					// 대쉬 회복
					// (대쉬 중일떄는 회복 x) - 보류
					//if (m_StateMachine->FindState(L"Dash") != m_StateMachine->GetCurState())
					ResetDash();

					// 스태미나 회복
					ResetStamina();

					// ClimbAccTime 회복
					m_StateMachine->FindState(L"Climb")->Reset();

					// ZipMover AutoMove
					CZipMover* pZip = dynamic_cast<CZipMover*>(_Other);
					if (pZip)
					{
						pZip->Activate();
						pZip->GetComponent<CRigidBody>()->SetAutoMove(this);
					}

					// CrumbleBlock Crumble
					CCrumbleBlock* pCB = dynamic_cast<CCrumbleBlock*>(_Other);
					if (pCB)
					{
						pCB->Activate();
						pCB->Crumble(true);
					}

				}
				// 플레이어가 충돌체 아래에서 닿은 경우
				else
				{
					// 겹친 길이만큼 다시 밀어냄
					vPos.y += overlapY;
				}
			}

			SetPos(vPos);
		}

		
		
	}
	else if (_Col == m_WallDetector)
	{
		if (_OtherCol->IsTrigger())
			return;

		m_IsWall = true;


		// Z키 누르면 최대한 겹치도록 (Wall Detector의 절반지점까지 겹치도록) 이동
		if (KEY_PRESSED(KEY::Z))
		{
			Vec2 vPos = GetPos();
			Vec2 vColPos = vPos + _Col->GetOffset();
			Vec2 vColScale = _Col->GetScale();

			Vec2 vOtherPos = _OtherCol->GetFinalPos();
			Vec2 vOtherColScale = _OtherCol->GetScale();

			float dx = vColPos.x - vOtherPos.x;

			// X축에서의 침투 깊이
			float overlapX = (vColScale.x / 2.f + vOtherColScale.x / 2.f) - std::abs(dx);
			
			float needX = m_WallDetector->GetScale().x / 2.f - overlapX;

			// 겹친 길이만큼 다시 밀어냄
			vPos.x += (dx < 0) ? needX : -needX;

			SetPos(vPos);

			// ZipMover AutoMove
			CZipMover* pZip = dynamic_cast<CZipMover*>(_Other);
			if (pZip)
			{
				pZip->Activate();
				pZip->GetComponent<CRigidBody>()->SetAutoMove(this);
			}

			// CrumbleBlock Crumble
			CCrumbleBlock* pCB = dynamic_cast<CCrumbleBlock*>(_Other);
			if (pCB)
			{
				pCB->Activate();
				pCB->Crumble(true);
			}
		}
	}

	
}

void CPlayer::OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	// 닿은 콜라이더가 없으면
	if (_Col->GetOverlapCount() == 0)
	{
		if (m_StateMachine->FindState(L"Dash") != m_StateMachine->GetCurState() && !m_PlayerDead)
			m_RigidBody->SetGravity(true);

		m_IsGround = false;
		m_IsWall = false;

		// Climb 상태 해제
		if (_Col == m_WallDetector && 
			m_StateMachine->FindState(L"Climb") == m_StateMachine->GetCurState())
		{
			m_StateMachine->ChangeState(L"Idle");
		}
	}

	// AutoMove 해제
	CZipMover* pZip = dynamic_cast<CZipMover*>(_Other);
	if (pZip)
	{
		pZip->GetComponent<CRigidBody>()->SetAutoMove(nullptr);
	}

	
}
