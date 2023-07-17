#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
    CScene_Start();
    ~CScene_Start();

public:
    //virtual �Ⱥٿ��� ������ ��������� �ٿ���
   virtual void update();
   virtual void Enter();
   virtual void Exit(); 
   virtual void render(HDC _dc);

public:
    void CreateForce();

private:
    bool        m_bUseForce;
    Vec2        m_vForcePos;
    float       m_fForceRadius;
    float       m_fCurRadius;
    float       m_fForce;

};

