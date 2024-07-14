#pragma once
#include "CManager.h"

class CSound;

class CSoundMgr
	: public CManager
{
	SINGLE(CSoundMgr)

private:
	LPDIRECTSOUND8	m_pSound;	// ���� ī�� ����
	CSound*			m_pBGM;		// BGM Sound


public:
	virtual void Init() override;
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }	
	void RegisterToBGM(CSound* _pSound);
};

