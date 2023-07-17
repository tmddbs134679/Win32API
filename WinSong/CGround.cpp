#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"

CGround::CGround()
{
	CreateCollider();

	
}

CGround::~CGround()
{
}

void CGround::start()
{
	GetCollider()->setScale(Vec2(GetScale()));
}

void CGround::update()
{
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{ 
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);


		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();
		

		float fVerticalLen = abs(vObjPos.y - vPos.y);
		float fHorizontalLen = abs(vObjPos.x - vPos.x);

		float fVerticalThreshold = vObjScale.y / 2.f + vScale.y / 2.f;
		float fHorizontalThreshold = vObjScale.x / 2.f + vScale.x / 2.f;


		if (fVerticalLen < fVerticalThreshold && fHorizontalLen < fHorizontalThreshold)
		{
			//�浹 �� �������� �ö󰡰� ����
			vObjPos.y -= fVerticalThreshold - fVerticalLen;




			pOtherObj->SetPos(vObjPos);
		}
		

		//Ground ���� �� �ӵ��ʱ�ȭ�Ͽ� ��������
		pOtherObj->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

	}

}

void CGround::OnCollision(CCollider* _pOther)
{
	//Player
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		//Ground
		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		//����
		float fVerticalLen = abs(vObjPos.y - vPos.y);

		//����
		float fHorizontalLen = abs(vObjPos.x - vPos.x);

		float fVerticalThreshold = vObjScale.y / 2.f + vScale.y / 2.f;
		float fHorizontalThreshold = vObjScale.x / 2.f + vScale.x / 2.f;

		if (fVerticalLen < fVerticalThreshold && fHorizontalLen < fHorizontalThreshold)
{
	// �浹 �� ó�� (�����ý��丮 ���)
	Vec2 vPlayerCenter = vObjPos;
	Vec2 vGroundCenter = vPos;

	float fOverlapX = fHorizontalThreshold - fHorizontalLen;
	float fOverlapY = fVerticalThreshold - fVerticalLen;

	if (fOverlapX < fOverlapY) // ���� �浹�� �� ���� ���
	{
		if (vPlayerCenter.x < vGroundCenter.x) // player�� ground�� ���ʿ� �ִ� ���
			vObjPos.x -= fOverlapX;
		else // player�� ground�� �����ʿ� �ִ� ���
			vObjPos.x += fOverlapX;
	}
	else // ���� �浹�� �� ���� ���
	{
		if (vPlayerCenter.y < vGroundCenter.y) // player�� ground�� �Ʒ��� �ִ� ���
			vObjPos.y -= fOverlapY;
		else // player�� ground�� ���� �ִ� ���
			vObjPos.y += fOverlapY;
	}

	pOtherObj->SetPos(vObjPos);
}
	
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}

}
