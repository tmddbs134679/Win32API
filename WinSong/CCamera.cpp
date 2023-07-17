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

	//ȭ�� �߾���ǥ�� ī�޶� Lookat ��ǥ���� ���̰� ���
	CalDiff();

}

void CCamera::CalDiff()
{
	//���� LookAt �� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	//���ϴ� ����


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

