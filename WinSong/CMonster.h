#pragma once
#include "CObject.h"


struct MonsterInfo
{
    float   fSpeed;            //�ӵ�
    float   fHP;               //ü��
    float   fDetectRange;      //��������
    float   fAttackRange;      //���ݹ���
    float   fAtt;              //���ݷ�
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

