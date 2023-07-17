#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "resource.h"
#include "CResMgr.h"
#include "CSound.h"

CCore::CCore()
	: m_hWnd(0)
	,m_ptResolution{}
	,m_hDC(0)
	,m_hBit(0)
	,m_memDC(0)
	,m_arrBrsuh{}
	,m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	//Compatible�� ���� DC�� Delete�� ����� �����Ǿ�����.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END ; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}


int CCore::init(HWND _hWND, POINT _ptResolution)
{
	m_hWnd = _hWND;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ������ ũ�� ����

	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y),false);


	//�޴��� ����

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINSONG));

	//message�� ������� �ʰ� �׸� �� �ִ� GetDC()�Լ�
	m_hDC = GetDC(m_hWnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	//�⺻ DC ����Ʈ���� ����
	DeleteObject(hOldBit);

	//���� ����� �� �� �귯�� ����
	CreateBrushPen();


	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();


	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\lis.wav");
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

	pNewSound->Play(true);



	return S_OK;
}



void CCore::progress()
{	//==============
	//Manager Update
	//==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	//==============
	//Scene Update
	//==============

	CSceneMgr::GetInst()->update();

	//�浹üũ
	CCollisionMgr::GetInst()->update();


	//UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();


	//Rendering
	// ȭ�� Clear
	// �׵θ��� ���� �� �ֱ⿡ 1�� ���ϰ� ���ش�.
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	//=============
	//�̺�Ʈ ����ó��
	//=============
	CEventMgr::GetInst()->update();

}

void CCore::DokingMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);

}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{

	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y };

	//�ػ󵵿� �´� ������ ũ�� ����
	//WS_OVERLAPPEDWINDOW : ���־��� ���°� ��Ƶ�
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

}

void CCore::CreateBrushPen()
{
	//hollow brush
	m_arrBrsuh[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	
	//Red Green Blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
}




