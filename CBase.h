#pragma once

//typedef unsigned int UINT;

class CBase
{
private:
	static UINT g_ID;

private:
	const UINT	m_ID;
	wstring		m_Name;

public:
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }

public:
	CBase();
	CBase(const CBase& _other);
	virtual ~CBase();
};

