#pragma once
#include "CObject.h"


class CMissile :
    public CObject
{

public:
    CMissile();
    ~CMissile();


public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _pOther);
public:
    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    void SetDir(float _fTheta)
    {
        m_fTheta = _fTheta;
    }


    Vec2 GetDir()
    {
        return m_vDir;
    }

private:

    CLONE(CMissile);

private:

    //float     m_fDir;     //���Ʒ� ����
    float       m_fTheta;   //�̵� ����
    Vec2        m_vDir;
};

