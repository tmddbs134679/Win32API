#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _eType)
	:m_hDC(_dc)
	,m_hDefaultPen(nullptr)
	,m_hDefaultBrsuh(nullptr)
{
	HPEN hPen = CCore::GetInst()->GetPen(_eType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eType)
	:m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrsuh(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->GetBrush(_eType);
	m_hDefaultBrsuh = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrsuh);
}
