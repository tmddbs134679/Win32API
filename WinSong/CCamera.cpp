#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fAccTime(1.f)
{

}


CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->ISDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_LookAt = m_pTargetObj->GetPos();
		}
	}
	 
	if (KEY_HOLD(KEY::W))
		m_LookAt.y -= 200.f * fDT;
	if (KEY_HOLD(KEY::S))
		m_LookAt.y += 200.f * fDT;
	if (KEY_HOLD(KEY::A))
		m_LookAt.x -= 200.f * fDT;
	if (KEY_HOLD(KEY::D))
		m_LookAt.x += 200.f * fDT;

	//화명 중앙좌표와 카메라 Lookat 좌표간의 차이값 계산
	CalDiff();

}

void CCamera::CalDiff()
{
	//이전 LookAt 과 현재 Look의 차이값을 보정해서 현재의 LookAt을 구한다.
	//향하는 백터


	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_LookAt;
	}
	else
	{
		Vec2 vLookDir = m_LookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
		

	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2  vCenter = vResolution / 2;


	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}

