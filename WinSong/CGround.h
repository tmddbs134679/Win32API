#pragma once
#include "CObject.h"


class CGround :
    public CObject
{
public:
    CGround();
    ~CGround();

public:
    virtual void start();

    virtual void update();

    CLONE(CGround);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
private:


};

