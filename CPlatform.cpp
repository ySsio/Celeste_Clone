#include "pch.h"
#include "CPlatform.h"

#include "CTileMap.h"

CPlatform::CPlatform()
	: m_TileMap(nullptr)
{
	m_TileMap = AddComponent<CTileMap>();
	m_TileMap->SetRowCol(10, 3);
}

CPlatform::~CPlatform()
{
}

void CPlatform::SetRowCol(UINT _Row, UINT _Col)
{
	if (m_TileMap) m_TileMap->SetRowCol(_Row, _Col);
}

void CPlatform::Tick()
{
}

void CPlatform::Render()
{
	if (m_TileMap)
		m_TileMap->Render();
}
