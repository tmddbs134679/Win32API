#pragma once

#include "Define.h"

#include "pch.h"


class CCore
{

	SINGLE(CCore);

public:

	int init(HWND _hWND, POINT _ptResolution);

	void progress();
	void DokingMenu();
	void DivideMenu();

	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

private:
	void CreateBrushPen();


public:
	HWND GetMainHwnd()
	{
		return m_hWnd;
	}
	
	HDC GetMainDC()
	{
		return m_hDC;
	}

	POINT GetResolution()
	{
		return m_ptResolution;
	}

	HBRUSH GetBrush(BRUSH_TYPE _eType)
	{
		return m_arrBrsuh[(UINT)_eType];
	}

	HPEN GetPen(PEN_TYPE _eType)
	{
		return m_arrPen[(UINT)_eType];
	}



private:
	HWND  m_hWnd;			//메인 윈도우 핸들
	POINT m_ptResolution;  // 메인 윈도우 해상도
	HDC m_hDC;			   //메인 윈도위 Drow할 DC값

	HBITMAP m_hBit;
	HDC		m_memDC;

	// 자주 사용하는 GDI Object
	HBRUSH	m_arrBrsuh[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU	m_hMenu;


};