#pragma once
#include "CState.h"


class CIdleState :
	public CState
{

public:
	CIdleState();
	~CIdleState();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
private:

};

