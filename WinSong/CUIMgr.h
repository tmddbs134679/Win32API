#pragma once
#include "CUI.h"

class CUIMgr
{

	SINGLE(CUIMgr);

public:

	void update();

	void SerFocusedUI(CUI* _pUI);

private:

	//�θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	CUI* GetTargetedUI(CUI* _pParentUI);	
	CUI* GetFocusedUI();

private:

	CUI* m_pFocusedUI;
};

