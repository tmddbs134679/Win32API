#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"


CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMonster = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMonster = new CMonster;
		pMonster->SetPos(_vPos);

		MonsterInfo info = {};

		info.fAtt = 10.f;
		info.fAttackRange = 50.f;
		info.fDetectRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 50.f;

		pMonster->SetMonsterInfo(info);

		pMonster->CreateRigidBody();
		pMonster->GetRigidBody()->SetMass(1.f);


		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMonster->SetAI(pAI);
	}
		break;

	case MON_TYPE::RANGE:


		break;

	}


	assert(pMonster);


	return pMonster;
	
}
