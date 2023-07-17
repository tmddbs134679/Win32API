#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}



void CEventMgr::update()
{

	//========================================
	//���� �����ӿ��� ����ص� Dead Object���� ����
	//========================================

	int DeadSize = m_vecDead.size();

	for (size_t i = 0; i < DeadSize; ++i)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	//=========
	//Event ó��
	//=========


	int EveSize = m_vecEvent.size();

	for (size_t i = 0; i < EveSize; ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	_eve.eEven;

	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);

	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : Object Adress
		//Object �� Dead ���·� ����
		//�������� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}

		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next Scene Type
				//Scene ����
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		//��Ŀ�� ui ���� (���� Scene�� ui�� ����Ű�� �ֱ� ����)
		CUIMgr::GetInst()->SerFocusedUI(nullptr);
		break;
	}
	
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		//lParam : AI;
		//wParam : Next type
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);

		break;
	}
	break;

	}
}
