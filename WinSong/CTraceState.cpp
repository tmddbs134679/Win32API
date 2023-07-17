#include "pch.h"
#include "CTraceState.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState()
	:CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	//Ÿ���� �� Player�� �i�ư���.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

	pPlayer->GetPos();

	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonsterPos = GetMonster()->GetPos();

	Vec2 vDistance = vPlayerPos - vMonsterPos;
	float LenDis = vDistance.Length();
	vDistance.Normalize();

	vMonsterPos += vDistance * GetMonster()->GetMonsterInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonsterPos);

	
	float mdis = GetMonster()->GetMonsterInfo().fDetectRange;
	if (LenDis > mdis)
	{
		ChangeAIState(GetAI(), MON_STATE::IDLE);
	}

	

}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
