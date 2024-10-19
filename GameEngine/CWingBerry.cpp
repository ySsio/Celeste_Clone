#include "pch.h"
#include "CWingBerry.h"

#include "CAssetMgr.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CPlayer.h"

#include "CSaveData.h"

CWingBerry::CWingBerry()
	: m_FlyAway(false)
	, m_SoundPlayed(false)
	, m_SoundDuration(0.63f)
	, m_AccTime(0.f)
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
		CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

		if (pPlayer && pPlayer->GetRoom() == GetRoom())
		{
			// �÷��� ���� �� �ȿ� ���� �� ���� ���
			if (!m_SoundPlayed)
			{
				// Sound ���
				CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_wingflap_01.wav");
				pSound->SetVolume(20);
				pSound->Play();
				m_SoundPlayed = true;
			}
			else
			{
				m_AccTime += fDT;

				if (m_AccTime >= m_SoundDuration)
				{
					m_SoundPlayed = false;
					m_AccTime -= m_SoundDuration;
				}
			}	

			// ���� �濡 �ִ� �÷��̾ �뽬 �ϸ� ���� ���ư��� �����
			if (KEY_TAP(KEY::X))
			{
				m_FlyAway = true;
				StopMove();
				MoveSmooth(2.f, m_OriPos, m_OriPos + Vec2(0.f, -900.f));
				m_SoundPlayed = false;

				// Sound ���
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_laugh.wav")->Play();
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_flyaway.wav")->Play();
			}
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

		// �÷��̾ room �ű�� ���⵵ room�� �Űܾ� ��
		SetRoom(CGameMgr::Get()->GetRoom());

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
			CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\strawberry\\game_gen_strawberry_red_get_1000.wav")->Play();
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

bool CWingBerry::Init()
{
	if (!CStrawBerry::Init())
		return false;

	// �ִϸ��̼� ����
	if (!m_Ghost)
		m_Animator->Play(L"Strawberry_Idle_Wing", true);
	else
		m_Animator->Play(L"Ghostberry_Idle_Wing", true);

	m_FlyAway = false;	

	return true;
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