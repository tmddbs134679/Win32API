#include "pch.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdex(3)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr || -1 == m_iImgIdex)
		return;

	 UINT iWidth = m_pTileTex->Width();
	 UINT iHeight = m_pTileTex->Height();

	 UINT iMaxCol = iWidth / TILE_SIZE;
	 UINT iMaxRow = iHeight / TILE_SIZE;

	 UINT iCurCOL = (UINT)m_iImgIdex / iMaxCol;
	 UINT iCurRow = (UINT)m_iImgIdex % iMaxCol;

	 //이미지 범위를 벗어난 인덱스
	 if (iCurRow >= iMaxRow)
		 assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(_dc
		,(int)(vRenderPos.x)
		,(int)(vRenderPos.y)
		,(int)(vScale.x)
		,(int)(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCOL * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::update()
{
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdex, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdex, sizeof(int), 1, _pFile);
}


