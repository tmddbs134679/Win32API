#pragma once
#include "CState.h"
class CTraceState :
    public CState
{

public:

	CTraceState();
	~CTraceState();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
private:



};

