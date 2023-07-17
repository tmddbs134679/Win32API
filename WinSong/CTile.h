#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{

public:
    CTile();
    ~CTile();

public:

    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdex;
    }

    CTexture* GetTexture()
    {
        return m_pTileTex;
    }
private:

    CLONE(CTile);

    virtual void render(HDC _dc);
    virtual void update();
public:

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

private:
    CTexture*   m_pTileTex;
    int         m_iImgIdex;

};

