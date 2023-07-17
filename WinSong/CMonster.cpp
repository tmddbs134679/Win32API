#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include"CCollider.h"
#include "AI.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CAnimator.h"


CMonster::CMonster()
	: MonsterInfo{}
{
	CreateCollider();
	GetCollider()->setScale(Vec2(60.f, 60.f));


	//CTexture* pMonTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\magic1.bmp");
	//CreateAnimator();

	//GetAnimator()->CreateAnimation(L"WALK", pMonTex, Vec2(0.f, 0.f), Vec2(50.f, 0.f), Vec2(50.f, 0.f), 0.3f, 1);


	//CAnimation* pMonAnim = GetAnimator()->FindAnimation(L"WALK");

	//GetAnimator()->Play(L"WALK", true);

	
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::update()
{
	

	if (m_pAI != nullptr)
		m_pAI->update();

}

void CMonster::render(HDC _dc)
{
	component_render(_dc);
}



void CMonster::Attack()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	//pMissile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}


void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	if (pOtherObj->GetName() == L"Missile_Player" || pOtherObj->GetName() == L"Missile_Player2" || pOtherObj->GetName() == L"Missile_Player3")
	{
		
	}
}