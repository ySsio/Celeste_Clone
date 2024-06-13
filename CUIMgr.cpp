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
	// Level Tick에서 UI 오브젝트가 스스로 마우스가 올라와있는지 체크한 이후 시점임

	// 현재 레벨에서 UI들을 받아옴
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurLevel();
	vector<CObj*>& vecUI = const_cast<vector<CObj*>&>(pCurLevel->GetLayer(LAYER_TYPE::UI));

	vector<CObj*>::reverse_iterator riter = vecUI.rbegin();
	// 전체 UI 중 포커싱 된 UI를 찾음 (UI트리에서 마우스 오버된 UI 중 가장 깊이가 깊은 UI)
	for (; riter != vecUI.rend(); ++riter)
	{
		CUI* pUI = dynamic_cast<CUI*>(*riter);
		assert(pUI);

		if (!pUI->IsMouseOn())
			continue;

		// pPriorityUI : 트리에서 마우스 오버된 애들 중 깊이가 가장 깊은 UI
		CUI* pPriorityUI = GetPriorityUI(pUI);

		// 이번 프레임에 클릭된 경우
		if (KEY_TAP(KEY::LBtn))
		{
			pPriorityUI->SetLbtnDown(true);
			pPriorityUI->LBtnDown();
		}
		else if (KEY_RELEASED(KEY::LBtn))
		{
			pPriorityUI->LBtnUp();

			// LBtnDown이었다가 버튼 떨어지면 = Click
			if (pPriorityUI->IsLbtnDown())
			{
				// Click된 상황
				pPriorityUI->LBtnClicked();
			}
		}

		// 포커싱된 UI를 가장 뒤로 미룸.
		if (riter != vecUI.rbegin() && pPriorityUI->IsLbtnDown())
		{
			vecUI.erase((riter+1).base());
			vecUI.push_back(pUI);
		}

		break;

	}

	// 이번 프레임에 왼쪽 클릭 떨어졌으면 모든 UI에 대해 LBtndown을 해제
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
