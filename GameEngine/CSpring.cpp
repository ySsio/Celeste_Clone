#include "pch.h"
#include "CSpring.h"

#include "CAssetMgr.h"

#include "CPlayer.h"
#include "CRigidBody.h"
#include "CSound.h"

CSpring::CSpring()
	: m_Animator(nullptr)
	, m_Dir(Vec2(0.f,-1.f))
{
	m_Animator = AddComponent<CAnimator>();
	m_Animator->AddAnimation(L"Spring_Idle", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Spring_Idle.anim"));
	m_Animator->AddAnimation(L"Spring_Active", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Spring_Active.anim"));
	m_Animator->Play(L"Spring_Idle", true);

	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 30.f));
	m_Collider->SetScale(Vec2(80.f, 20.f));
}

CSpring::CSpring(const CSpring& _Other)
	: CObj(_Other)
	, m_Animator(nullptr)
	, m_Dir(Vec2(0.f, -1.f))
{
	m_Animator = GetComponent<CAnimator>();
	m_Animator->Play(L"Spring_Idle", true);

	m_Collider = AddComponent<CCollider>();
}

CSpring::~CSpring()
{
}

bool CSpring::Save(FILE* _pFile)
{
	// 1. 오브젝트 타입을 문자열로 저장
	wstring Type = L"Spring";
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

	// 5. Dir 저장 (스프링 방향)
	fwrite(&m_Dir, sizeof(Vec2), 1, _pFile);

	return true;
}

void CSpring::Load(FILE* _pFile)
{
	// 1. 오브젝트 타입을 보고 이 함수가 호출된 상황
	// 2. Room 정보 불러옴
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);
	
	// 3. 포지션 받아와서 세팅
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. Scale 받아와서 세팅
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetScale(VecBuff);

	// 5. Dir 받아와서 세팅
	fread(&m_Dir, sizeof(Vec2), 1, _pFile);

}

void CSpring::Tick()
{
	if (m_Animator->IsDone())
		m_Animator->Play(L"Spring_Idle", true);
}

void CSpring::Render()
{
	if (m_Animator)
		m_Animator->Render();
}

void CSpring::OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other);

	if (pPlayer && _OtherCol == pPlayer->GetCollider())
	{
		// Active 애니메이션 재생
		m_Animator->Play(L"Spring_Active");

		// Sound 재생
		CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\spring\\game_gen_spring.wav");
		pSound->Play();
	}
}