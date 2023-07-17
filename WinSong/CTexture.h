#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{

private:
    CTexture();
   virtual ~CTexture();

    friend class CResMgr;

public:
    void Load(const wstring& _strFilePath);

public:
    UINT Width()
    {
        return m_bitInfo.bmWidth;
    }

    HDC GetDC()
    {
        return m_dc;
    }

    UINT Height()
    {
        return m_bitInfo.bmHeight;
    }

private:
    HDC          m_dc;
    HBITMAP      m_hBit;
    BITMAP       m_bitInfo;

};

