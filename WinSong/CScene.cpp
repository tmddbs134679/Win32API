#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
			//m_arrObj[i] �׷� ������ j ��ü ����
			delete m_arrObj[i][j];
		}
	}
}

void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
				m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j) 
		{
			if (!m_arrObj[i][j]->ISDead())
			{
				m_arrObj[i][j]->update();
			}
			
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{

		if ((UINT)GROUP_TYPE::TILE == i)
		{
			render_tile(_dc);
			continue;
		}

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->ISDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{

	Safe_Delete_Vec<CObject*> (m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}

}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	//Ÿ�� ����
	for (UINT i = 0; i < _iXCount; ++i)
	{
		for (UINT j = 0; j < _iYCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}

}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	//Ÿ�� ���� ���� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;


	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	//�ҷ��� ������ �°� EmptyTile�� �����α�
	CreateTile(xCount, yCount);

	//������� Ÿ�� ������ �ʿ��� ������ �ҷ����� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);
}

void CScene::render_tile(HDC _dc)
{
	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);


	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	Vec2 vLeftTop = vCamLook - vResolution / 2.f;


	int iTileSize = TILE_SIZE;

	int iLeftTopCol = (int)vLeftTop.x / iTileSize;
	int iLeftTopRow = (int)vLeftTop.y / iTileSize;
	
	
	int irenderWidth = ( (int)vResolution.x / iTileSize ) + 1;
	int irenderHeight = ( (int)vResolution.y / iTileSize ) + 1;

	for (int iCurRow = iLeftTopRow ; iCurRow < (iLeftTopRow + irenderHeight); ++iCurRow)
	{
		for (int iCurCol = iLeftTopCol; iCurCol < (iLeftTopCol + irenderWidth); ++iCurCol)
		{
			if (iCurCol < 0 || m_iTileX <= iCurCol
				|| iCurRow < 0 || m_iTileY <= iCurRow)
			{
				continue;
			}
			int iLeftTopIdx = m_iTileX * iCurRow + iCurCol;
			vecTile[iLeftTopIdx]->render(_dc);
		}
	}
}
