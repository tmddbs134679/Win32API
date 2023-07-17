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
			//충돌 시 위쪽으로 올라가게 구현
			vObjPos.y -= fVerticalThreshold - fVerticalLen;




			pOtherObj->SetPos(vObjPos);
		}
		

		//Ground 진입 시 속도초기화하여 끌림방지
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

		//수직
		float fVerticalLen = abs(vObjPos.y - vPos.y);

		//수평
		float fHorizontalLen = abs(vObjPos.x - vPos.x);

		float fVerticalThreshold = vObjScale.y / 2.f + vScale.y / 2.f;
		float fHorizontalThreshold = vObjScale.x / 2.f + vScale.x / 2.f;

		if (fVerticalLen < fVerticalThreshold && fHorizontalLen < fHorizontalThreshold)
{
	// 충돌 시 처리 (메이플스토리 방식)
	Vec2 vPlayerCenter = vObjPos;
	Vec2 vGroundCenter = vPos;

	float fOverlapX = fHorizontalThreshold - fHorizontalLen;
	float fOverlapY = fVerticalThreshold - fVerticalLen;

	if (fOverlapX < fOverlapY) // 가로 충돌이 더 작은 경우
	{
		if (vPlayerCenter.x < vGroundCenter.x) // player가 ground의 왼쪽에 있는 경우
			vObjPos.x -= fOverlapX;
		else // player가 ground의 오른쪽에 있는 경우
			vObjPos.x += fOverlapX;
	}
	else // 세로 충돌이 더 작은 경우
	{
		if (vPlayerCenter.y < vGroundCenter.y) // player가 ground의 아래에 있는 경우
			vObjPos.y -= fOverlapY;
		else // player가 ground의 위에 있는 경우
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
