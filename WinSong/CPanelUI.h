#pragma once
#include "CUI.h"



class CPanelUI :
    public CUI
{
public:

    CPanelUI();
    ~CPanelUI();

    CLONE(CPanelUI);

public:
    
    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn();
    virtual void MousebtnDown();
    virtual void MouseLbtnUp();


private:
    Vec2    m_vDragStart;
};

