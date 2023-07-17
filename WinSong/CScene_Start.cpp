#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CMonFactory.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"


CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (UINT j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->ISDead())
			{
				
				if (vecObj[j]->GetRigidBody() && m_bUseForce)
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (vDiff.Length() < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}

			}

				vecObj[j]->update();
			}

		}

	if (KEY_TAP(KEY::ESC))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookat(vLookAt);
	}
}

void CScene_Start::Enter()
{
	//Object 추가
	CObject* pObj = new CPlayer;

	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(440.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject는 부모의 역할을 해야만 한다. 파생으로 만들어진 자식클래스로만 객체를 만들어야 함.
	//객체를 생성해서 보여지는거 자체가 수행되면 안된다.
	//CObject* pObj = new CObject;
	//pObj->SetPos(Vec2(640.f, 384.f));
	//pObj->SetSacle(Vec2(100.f, 100.f));
	//AddObject(pObj, GROUP_TYPE::DEFAULT);

	//CObject* pOtherPlayer = pObj->Clone();
	// pObj->SetPos(Vec2(740.f, 384.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//카메라 고정
	CCamera::GetInst()->SetTarget(pObj);

	//Vec2 생성과 동시에 대입은 복사생성자가 된다.
	//반환은 vec2타입이아니라 생성자 쪽에서 해결해줘야한다.

	//몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonster = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f,300.f));
	AddObject(pMonster, GROUP_TYPE::MONSTER);

	

	//땅 물체 배치

	CObject* pGround = new CGround;
	pGround->SetName(L"Ground2");
	pGround->SetPos(Vec2(840.f, 684.f));
	pGround->SetScale(Vec2(12000.f, 100.f));
	AddObject(pGround, GROUP_TYPE::GROUND);



	CObject* pGround2 = new CGround;
	pGround2->SetName(L"Ground");
	pGround2->SetPos(Vec2(640.f, 584.f));
	pGround2->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround2, GROUP_TYPE::GROUND);

	CObject* pGround3 = new CGround;
	pGround3->SetName(L"Ground3");
	pGround3->SetPos(Vec2(780.f, 500.f));
	pGround3->SetScale(Vec2(200.f, 30.f));
	AddObject(pGround3, GROUP_TYPE::GROUND);

	
	CObject* pGround4 = new CGround;
	pGround4->SetName(L"Ground4");
	pGround4->SetPos(Vec2(840.f, 430.f));
	pGround4->SetScale(Vec2(200.f, 30.f));
	AddObject(pGround4, GROUP_TYPE::GROUND);

	/*
	CObject* pGround5 = new CGround;
	pGround5->SetName(L"Ground5");
	pGround5->SetPos(Vec2(640.f, 430.f));
	pGround5->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround5, GROUP_TYPE::GROUND);



	CObject* pGround6 = new CGround;
	pGround6->SetName(L"Ground6");
	pGround6->SetPos(Vec2(640.f, 30.f));
	pGround6->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround6, GROUP_TYPE::GROUND);
*/


	//충돌 지정
	//Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	//Camera Look 지정
	//해상도 절반위치
	
	CCamera::GetInst()->SetLookat(vResolution / 2.f);

	start();

}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);


	if (!m_bUseForce)
		return;

		SelectGDI GDI1(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI GDI2(_dc, PEN_TYPE::GREEN);

		m_fCurRadius += m_fForceRadius * 0.8f * fDT;
		if (m_fCurRadius > m_fForceRadius)
		{
			m_fCurRadius = 0.f;
		}

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);
		Ellipse(
			_dc,
			vRenderPos.x - m_fCurRadius,
			vRenderPos.y - m_fCurRadius,
			vRenderPos.x + m_fCurRadius,
			vRenderPos.y + m_fCurRadius);

	
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

}
