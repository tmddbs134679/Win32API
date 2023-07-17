#pragma once
#include "CObject.h"


struct MonsterInfo
{
    float   fSpeed;            //속도
    float   fHP;               //체력
    float   fDetectRange;      //감지범위
    float   fAttackRange;      //공격범위
    float   fAtt;              //공격력
};

class AI;

class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;

public:
    virtual void update();
    virtual void render(HDC _dc);

   
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    void Attack();
    void SetAI(AI* _AI);

public:
    void SetSpeed(float _f)
    {
        MonsterInfo.fSpeed = _f;
    }


public:

    float GetSpeed()
    {
        return MonsterInfo.fSpeed;
    }

    const MonsterInfo& GetMonsterInfo()
    {
        return MonsterInfo;
    }

private:

    CLONE(CMonster);

private:

    void SetMonsterInfo(const MonsterInfo& _info)
    {
        MonsterInfo = _info;
    }

private:
    float m_fSpeed;

    int   m_iHP;
    
    AI*   m_pAI;

    MonsterInfo MonsterInfo;

};

