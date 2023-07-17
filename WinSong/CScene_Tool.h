#pragma once
#include "CScene.h"
#include "CUI.h"

class CScene_Tool :
    public CScene
{

public:
    CScene_Tool();
    ~CScene_Tool();


public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:

    void SetTileIdx();
    void SaveTile(const wstring& _strFilePath);
    void SaveTileData();

    void LoadTileData();


private:

    CUI*    m_pUI;
   
};

