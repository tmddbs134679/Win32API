#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"


CPlayer::CPlayer()
{
	//Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\magic1.bmp");

	

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f,0.f));
	GetCollider()->setScale(Vec2(30.f, 80.f));


	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\animator.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 100.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 200.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 300.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(L"IWALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_UP", pTex, Vec2(0.f, 100.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_LEFT", pTex, Vec2(0.f, 200.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_RIGHT", pTex, Vec2(66.75f, 300.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);



	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(66.75, 200.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vec2(0.f, 300.f), Vec2(133.5f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	/*
	for(UINT i=0; i < pAnim->GetMaxFrame(); ++i)
	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);*/

	m_state = PLAYER_STATE::IDLE;
	m_FinalDir = PLAYER_DIR::IDLE;
	bIsJumping = false;

	SetState(m_state);

	finalDir = Vec2(Vec2(0.f, -1.f));

	CreateRigidBody();
	CreateGravity();


}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	//비록 상속받은 변수지만 디버깅할 때 쉽게 찾기 위해, 안전성을 높히기 위해 직접 사용하지 않고
	//Get으로 가져와서 구현한다
	// 
	//Vec2 vPos = GetPos();
	update_move();

	update_state();

	
	if (KEY_TAP(KEY::Z))
	{
		CreateMissile();
	}

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));

	}

	//SetPos(vPos);


	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	 //컴포넌트 (충돌체, etc...)가 있는 경우 렌더
	 component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	//vMissilePos.y -= GetScale().y / 4.f;
	 

	CMissile* pMissile2 = new CMissile;
	pMissile2->SetName(L"Missile_Player2");
	pMissile2->SetPos(vMissilePos);
	pMissile2->SetScale(Vec2(20.f, 20.f));
	pMissile2->SetDir(finalDir);
	

	if (KEY_HOLD(KEY::W))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::DOWN))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::RIGHT))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::LEFT))
	{
		pMissile2->SetDir(finalDir);
	}
	
 
 	CreateObject(pMissile2, GROUP_TYPE::PROJ_PLAYER);

}

void CPlayer::UpdateAnimation()
{
	switch (m_state)
	{
	case PLAYER_STATE::IDLE:
		
		if (m_FinalDir == PLAYER_DIR::IDLE)
		{
			GetAnimator()->Play(L"IDLE", true);

		}
		else if (m_FinalDir == PLAYER_DIR::UP)
		{
			GetAnimator()->Play(L"IWALK_UP", true);
		}
		else if (m_FinalDir == PLAYER_DIR::DOWN)
		{
			GetAnimator()->Play(L"IWALK_DOWN", true);
		}
		else if (m_FinalDir == PLAYER_DIR::LEFT)
		{
			GetAnimator()->Play(L"IWALK_LEFT", true);
		}
		else if (m_FinalDir == PLAYER_DIR::RIGHT)
		{
			GetAnimator()->Play(L"IWALK_RIGHT", true);
		}
		break;

	case PLAYER_STATE::WALK:
		if (m_FinalDir == PLAYER_DIR::UP)
		{
			GetAnimator()->Play(L"WALK_UP", true);	
		}
		else if (m_FinalDir == PLAYER_DIR::DOWN)
		{
			GetAnimator()->Play(L"WALK_DOWN", true);
		}
		else if (m_FinalDir == PLAYER_DIR::LEFT)
		{
			GetAnimator()->Play(L"WALK_LEFT", true);
		}
		else if (m_FinalDir == PLAYER_DIR::RIGHT)
		{
			GetAnimator()->Play(L"WALK_RIGHT", true);
		}
		break;

	case PLAYER_STATE::JUMP:
		if (m_FinalDir == PLAYER_DIR::LEFT)
		{
			if(KEY_HOLD(KEY::LEFT))
			GetAnimator()->Play(L"JUMP_LEFT", false);
		}
			
		else if (m_FinalDir == PLAYER_DIR::RIGHT)
			GetAnimator()->Play(L"JUMP_RIGHT", true);

		GetAnimator()->Play(L"IDLE", true);

		break;

	}
}

void CPlayer::update_state()
{

	bool bIsMoving = false;
	

	if (KEY_HOLD(KEY::LEFT) || KEY_TAP(KEY::LEFT))
	{
		SetState(PLAYER_STATE::WALK);
		m_FinalDir = PLAYER_DIR::LEFT;
		finalDir = (Vec2(-1.f, 0.f));
		bIsMoving = true;
		
	}
	 if (KEY_HOLD(KEY::RIGHT) || KEY_TAP(KEY::RIGHT))
	{
		 SetState(PLAYER_STATE::WALK);
		 m_FinalDir = PLAYER_DIR::RIGHT;
		 finalDir = (Vec2(1.f, 0.f));
		 bIsMoving = true;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		SetState(PLAYER_STATE::JUMP);
		bIsMoving = true;
		bIsJumping = true;

	}
	if (!bIsMoving)
	{
		SetState(m_state);
	}

}

void CPlayer::update_move()
{
	bool bIsMoving = false;

	if (KEY_HOLD(KEY::LEFT))
	{
			Vec2 Pos = this->GetPos();
			Pos += Vec2(-200.f, 0.f) * fDT;
			SetPos(Pos);
			SetState(PLAYER_STATE::WALK);
			m_FinalDir = PLAYER_DIR::LEFT;

	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		Vec2 Pos = this->GetPos();
		Pos += Vec2(200.f, 0.f) * fDT;

		SetPos(Pos);

		SetState(PLAYER_STATE::WALK);
	}

	if (KEY_TAP(KEY::SPACE))
	{

		if (!bIsJumping)
		{
			if (GetRigidBody())
			{
				
				
				GetRigidBody()->AddVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
			}
		}
			
	}

	if (KEY_TAP(KEY::LEFT))
	{
		Vec2 Pos = this->GetPos();
		Pos += Vec2(-200.f, 0.f) * fDT;
		SetPos(Pos);


		SetState(PLAYER_STATE::WALK);
		bIsMoving = true;
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		Vec2 Pos = this->GetPos();
		Pos += Vec2(200.f, 0.f) * fDT;

		SetPos(Pos);

		SetState(PLAYER_STATE::WALK);
		bIsMoving = true;
	}

	SetState(PLAYER_STATE::IDLE);
}

void CPlayer::OnCollisionEnter(CCollider* _Other)
 {
	CObject* pOtherObj = _Other->GetObj();


	if (pOtherObj->GetName() == L"Ground" || pOtherObj->GetName() == L"Ground2" || pOtherObj->GetName() == L"Ground3" || pOtherObj->GetName() == L"Ground4")
	{
		Vec2 vPos = GetPos();

		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_state = PLAYER_STATE::IDLE;
			bIsJumping = false;
		}

	}
}
