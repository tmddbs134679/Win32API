#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}


CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	//1. FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;
	
	//2. FocusedUI ������, �θ� UI����, �ڽ� UI �� �� ���� Ÿ���� �� UI�� �����´�.

	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MousebtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
	
}

void CUIMgr::SerFocusedUI(CUI* _pUI)
{
	//�̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}

	}

	//���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	//1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI

		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	//���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	//���ʹ�ư Tap �� �߻��ߴٴ� ����
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}

	}

	//�̹��� Focus �� ui�� ����
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);

	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
