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
			m_Animator->Play(L"Strawberry_Collected");

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

bool CStrawBerry::Save(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���ڿ��� ����
	wstring Type = L"Strawberry";
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

void CStrawBerry::Load(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���� �� �Լ��� ȣ��� ��Ȳ
	// 2. Room ���� �ҷ���
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. ������ �޾ƿ���
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. Scale �޾ƿ���
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetScale(VecBuff);
}
