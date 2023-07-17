#pragma once
#include "CObject.h"



class CTexture;


class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
 

public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    void SetState(PLAYER_STATE _state)
    {
        m_state = _state;
        UpdateAnimation();
    }


    PLAYER_STATE GetSate()
    {
        return m_state;
    }

private:
    void CreateMissile();
    void UpdateAnimation();

    void update_state();

    void update_move();

    virtual void OnCollisionEnter(CCollider* _Other);


private:

    CLONE(CPlayer);

  
private:
   
    PLAYER_STATE m_state;

    PLAYER_DIR m_FinalDir;


    Vec2 finalDir;
    bool bIsJumping;
};

