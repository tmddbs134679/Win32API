#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fricCoeff(50.f)
	, m_vMaxVelocity(Vec2(200.f, 600.f))
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{

	////���� ũ��
	float fForce = m_vForce.Length();

	////���� ����
	//m_vForce.Normalize();
	//
	////���ӵ� ũ��
	//float m_fAccel = fForce / m_fMass;

	if (fForce != 0.f)
	{
		//���ӵ�
		m_vAccel = m_vForce / m_fMass;

	}

	//�߰� ���ӵ�
	m_vAccel += m_vAccelA;


	//�ӵ�
	m_vVelocity += m_vAccel * fDT;


	//�����¿� ���� �ݴ���� ���ӵ�
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fricCoeff * fDT;

		if (vFriction.Length() >= m_vVelocity.Length())
		{
			//���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	//�ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x < m_vVelocity.x))
	{
		
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y < m_vVelocity.y))
	{

		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}


	//�ӵ��� ���� �̵�
	Move();

	//�� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{	
	////�̵�����
	//Vec2 vDir = m_vVelocity;
	//vDir.Normalize();

	////�̵� �ӷ�
	float fSpeed = m_vVelocity.Length();
	//vPos += vDir * fSpeed * fDT;

	if (fSpeed != 0.f)
	{

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;
		m_pOwner->SetPos(vPos);
	}

}
