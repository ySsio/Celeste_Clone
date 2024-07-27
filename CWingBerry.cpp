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
		// ���� �濡 �ִ� �÷��̾ �뽬 �ϸ� ���� ���ư��� �����
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
		// ���� ���ư��� ���̾����� �����ϰ� �÷��̾ ���󰡵��� ��
		StopMove();
		m_FlyAway = false;

		// �ִϸ��̼� ����
		if (!m_Ghost)
			m_Animator->Play(L"Strawberry_Idle", true);
		else
			m_Animator->Play(L"Ghostberry_Idle", true);

		// �÷��̾� ���� �ݴ� �������� offset�� ���� ��ġ�� ��ǥ ��ġ�� ����
		m_TargetPos = m_Target->GetPos() + Vec2(-m_Target->GetDir().x * m_Offset.x, m_Offset.y);

		// ���� ��ġ���� Ÿ�� ��ġ�� MoveDuration ���� �� �� �ֵ��� ������ ����
		float Ratio = fDT / m_MoveDuration;
		Vec2 vPos = GetPos() * (1 - Ratio) + m_TargetPos * Ratio;

		// ��ġ ����
		SetPos(vPos);

		// �÷��̾ ���� ������ Collected ���·� ��ȯ
		if (m_Target->IsGround())
		{
			m_Collected = true;
			m_Touched = false;

			// �ִϸ��̼� ���
			if (!m_Ghost)
				m_Animator->Play(L"Strawberry_Collected");
			else
				m_Animator->Play(L"Ghostberry_Collected");

			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_red_get_1000.wav");
			pSound->Play();
		}
	}

	if (m_Collected)
	{
		// ���� �ִϸ��̼��� ������
		if (m_Animator->IsDone())
		{
			// �� ��ü�� �ı�
			Delete_Object(this);

			// Game �����Ϳ� �� ���Ⱑ �����Ǿ��ٰ� ��������� ��!!
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

	// �ִϸ��̼� ����
	if (!m_Ghost)
		m_Animator->Play(L"Strawberry_Idle_Wing", true);
	else
		m_Animator->Play(L"Ghostberry_Idle_Wing", true);

	m_FlyAway = false;

	// �� ����
	SetRoom(m_OriRoom);
}

bool CWingBerry::Save(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���ڿ��� ����
	wstring Type = L"Wingberry";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room ���� ����
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. ������ ����
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Scale ����
	VecBuff = GetScale();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	return true;
}
