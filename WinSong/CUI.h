#pragma once
#include "CObject.h"


class CUI :
    public CObject
{

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
   virtual ~CUI();

   friend class CUIMgr;

   virtual CUI* Clone() = 0;
public:


    virtual void update();
    virtual void render(HDC _dc);
    virtual void finalupdate();

    virtual void MouseOn();

    virtual void MousebtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();
   


public:

    CUI* GetParent()
    {
        return m_ParentUI;
    }

    Vec2 GetFinalPos()
    {
        return m_vFinalPos;
    }

    void AddChild(CUI* _pUI)
    {
        m_vecChildUI.push_back(_pUI);
        _pUI->m_ParentUI = this;
    }

    bool IsMouseOn()
    {
        return m_bMouseOn;
    }
 
    bool IsLbtnDown()
    {
        return m_bLbtnDown;
    }

    const vector<CUI*>& GetChildUI()
    {
        return m_vecChildUI;
    }

private:

    void update_child();
    void render_child(HDC _dc);
    void finalupdate_child();

    void MouseOnCheck();
private:
    CUI*                m_ParentUI;
    vector<CUI*>        m_vecChildUI;

    Vec2                m_vFinalPos;

    bool                m_bCamAffected;     //ui의 카메라 영향 유무
    bool                m_bMouseOn;         //UI 위에 마우스가 있는지
    bool                m_bLbtnDown;        //버튼이 down된적이 있는지
};

