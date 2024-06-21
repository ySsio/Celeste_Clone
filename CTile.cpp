#include "pch.h"
#include "CTile.h"
#include "CPathMgr.h"

CTile::CTile()
	: m_Tex(nullptr)
	, m_hasCollider(false)
	, m_isDanger(false)
	, m_ColInfo{}
{
}

CTile::~CTile()
{
}


void CTile::Save(const wstring& _strRelativeFilePath)
{
}

void CTile::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;
}

