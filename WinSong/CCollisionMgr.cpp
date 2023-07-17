#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"



CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{


}


void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCureScene = CSceneMgr::GetInst()->GetCurScene();

	//복사하지않고 참조해서 복사비용을 줄였으니 받을 때에도 const &로 똑같이 받아준다.
	const vector<CObject*>& vecLeft = pCureScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCureScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	int LeftNum = vecLeft.size();
	int RightNum = vecRight.size();

	for (int i = 0; i < LeftNum; ++i)
	{
		//충돌체를 보유하지 않는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (int j = 0; j < RightNum; ++j)
		{
			// 충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
				
			//두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);


			//충돌 정보가 미 등록 상태인 경우
			if (m_mapColInfo.end() == iter)
			{
				//등록이 안되어있는것도 map에는 넣어줘야한다.
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			//충돌체가 있는경우
			if (IsCollision(pLeftCol, pRightCol))
			{
				//현재 충돌하는 경우

				if (iter->second)
				{
					//이전에 충돌중이 였고 지금도 충돌중일 때(계속 충돌중)

					if (vecLeft[i]->ISDead() || vecRight[j]->ISDead())
					{
						//그 충돌체가 삭제 예정중인 충돌체일때
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					//이전에는 충돌하지 않았지만, 지금은 충돌하고 있다.
					//그 충돌체가 삭제 예정중인 충돌체일때라면 충돌하지 않은것으로 취급
					if (!vecLeft[i]->ISDead() && !vecRight[j]->ISDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				//현재 충돌하고 있지 않는 경우
				if (iter->second)
				{
					//이전에는 충돌했을 경우(충돌에서 빠져나온 시점)
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightSacle = _pRightCol->GetScale();

	
	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightSacle.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightSacle.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{

	//더 작은 값의 그룹 타입을 행으로,
	//큰 값을 열(비트) 로 사용

	UINT	iRow = (UINT)_eLeft;
	UINT	iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;;
	}


	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
	

}
