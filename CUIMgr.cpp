#include "pch.h"
#include "CUIMgr.h"

#include "CUI.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Init()
{
	
}

void CUIMgr::Tick()
{
	// Level Tick���� UI ������Ʈ�� ������ ���콺�� �ö���ִ��� üũ�� ���� ������

	// ���� �������� UI���� �޾ƿ�
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurLevel();
	vector<CObj*>& vecUI = const_cast<vector<CObj*>&>(pCurLevel->GetLayer(LAYER_TYPE::UI));

	vector<CObj*>::reverse_iterator riter = vecUI.rbegin();
	// ��ü UI �� ��Ŀ�� �� UI�� ã�� (UIƮ������ ���콺 ������ UI �� ���� ���̰� ���� UI)
	for (; riter != vecUI.rend(); ++riter)
	{
		CUI* pUI = dynamic_cast<CUI*>(*riter);
		assert(pUI);

		if (!pUI->IsMouseOn())
			continue;

		// pPriorityUI : Ʈ������ ���콺 ������ �ֵ� �� ���̰� ���� ���� UI
		CUI* pPriorityUI = GetPriorityUI(pUI);

		// �̹� �����ӿ� Ŭ���� ���
		if (KEY_TAP(KEY::LBtn))
		{
			pPriorityUI->SetLbtnDown(true);
			pPriorityUI->LBtnDown();
		}
		else if (KEY_RELEASED(KEY::LBtn))
		{
			pPriorityUI->LBtnUp();

			// LBtnDown�̾��ٰ� ��ư �������� = Click
			if (pPriorityUI->IsLbtnDown())
			{
				// Click�� ��Ȳ
				pPriorityUI->LBtnClicked();
			}
		}

		// ��Ŀ�̵� UI�� ���� �ڷ� �̷�.
		if (riter != vecUI.rbegin() && pPriorityUI->IsLbtnDown())
		{
			vecUI.erase((riter+1).base());
			vecUI.push_back(pUI);
		}

		break;

	}

	// �̹� �����ӿ� ���� Ŭ�� ���������� ��� UI�� ���� LBtndown�� ����
	if (KEY_RELEASED(KEY::LBtn))
	{
		for (CObj* ObjUI : vecUI)
		{
			queue<CUI*> Q;

			CUI* pUI = dynamic_cast<CUI*>(ObjUI);
			assert(pUI);
			Q.push(pUI);

			while (!Q.empty())
			{
				CUI* curUI = Q.front();
				Q.pop();

				curUI->SetLbtnDown(false);

				const vector<CUI*> vecChild = curUI->GetChild();
				for (auto childUI : vecChild)
				{
					Q.push(childUI);
				}
			}
		}
	}
	

}

CUI* CUIMgr::GetPriorityUI(CUI* _ParentUI)
{
	while (true)
	{
		bool isLeaf = true;
		const vector<CUI*>& vecChild = _ParentUI->GetChild();
		for (CUI* childUI : vecChild)
		{
			if (childUI->IsMouseOn())
			{
				isLeaf = false;
				_ParentUI = childUI;
				break;
			}
		}
		
		if (isLeaf) break;
	}

	return _ParentUI;
}
