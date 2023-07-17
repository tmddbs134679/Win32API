#pragma once
#include "CUI.h"

class CUIMgr
{

	SINGLE(CUIMgr);

public:

	void update();

	void SerFocusedUI(CUI* _pUI);

private:

	//부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.
	CUI* GetTargetedUI(CUI* _pParentUI);	
	CUI* GetFocusedUI();

private:

	CUI* m_pFocusedUI;
};

