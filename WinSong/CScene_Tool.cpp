#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"


void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	//툴 Scene 에서 사용할 메뉴를 붙인다.

	CCore::GetInst()->DokingMenu();


	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(370.f, 730.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"pBtnUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(133.f,680.f));
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)& CScene_Tool::SaveTileData);



	/*CBtnUI* pTexUI = new CBtnUI;
	pTexUI->SetName(L"pTexUI");
	pTexUI->SetScale(Vec2(50.f, 50.f));
	pTexUI->SetPos(Vec2(10.f, 10.f));
	*/
	vector<CBtnUI*> btnUIList;

	
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			std::wstring name = L"pTexUI";

			//pTexUI의 이름을 인덱스처럼 붙이기 위해 Setting
			name += std::to_wstring(i);
			name += std::to_wstring(j);

			CBtnUI* pTexUI = new CBtnUI;
			pTexUI->SetName(name);
			pTexUI->SetScale(Vec2(50.f, 50.f));
			pTexUI->SetPos(Vec2(10.f + (60.f * j), 10.f + (60.f * i)));

			btnUIList.push_back(pTexUI);
			
		}
	
	}

	pPanelUI->AddChild(pBtnUI);
	for (CBtnUI* pTexUI : btnUIList)
	{
		pPanelUI->AddChild(pTexUI);
	}

	AddObject(pPanelUI, GROUP_TYPE::UI);


	//복사본 UI
	/*CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f,0.f));
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);
	AddObject(pClonePanel, GROUP_TYPE::UI);*/

	//m_pUI = pClonePanel;

	//Camera Look 지정
	CCamera::GetInst()->SetLookat(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::F))
	{
		CUIMgr::GetInst()->SerFocusedUI(m_pUI);
	}


	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}

	if (KEY_TAP(KEY::ESC))
	{
		ChangeScene(SCENE_TYPE::START);
	}

}

void CScene_Tool::SetTileIdx()
{
	if(KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX =(int)GetTileX();
		int iTileY =(int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0 || iTileX <= iCol
			|| vMousePos.y < 0 || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	}

	

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	assert(pFile);

	//타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	//모든 타일들을 개별적으로 저장할 데이터를 저장
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	//Modal
	if (GetSaveFileName(&ofn))
	{
		
		SaveTile(szName);
	}

	
}

void CScene_Tool::LoadTileData()
{

	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal
	if (GetOpenFileName(&ofn))
	{
		//szName

		wstring strRelativePath = CPathMgr::GetInst()->GetRealativePath(szName);

		LoadTile(strRelativePath);
	}

}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

//======================
//Tile Count Window Proc
//======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount =  GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount =  GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurscene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurscene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;

}