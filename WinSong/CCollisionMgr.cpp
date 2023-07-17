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

	//���������ʰ� �����ؼ� �������� �ٿ����� ���� ������ const &�� �Ȱ��� �޾��ش�.
	const vector<CObject*>& vecLeft = pCureScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCureScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	int LeftNum = vecLeft.size();
	int RightNum = vecRight.size();

	for (int i = 0; i < LeftNum; ++i)
	{
		//�浹ü�� �������� �ʴ� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (int j = 0; j < RightNum; ++j)
		{
			// �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
				
			//�� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);


			//�浹 ������ �� ��� ������ ���
			if (m_mapColInfo.end() == iter)
			{
				//����� �ȵǾ��ִ°͵� map���� �־�����Ѵ�.
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			//�浹ü�� �ִ°��
			if (IsCollision(pLeftCol, pRightCol))
			{
				//���� �浹�ϴ� ���

				if (iter->second)
				{
					//������ �浹���� ���� ���ݵ� �浹���� ��(��� �浹��)

					if (vecLeft[i]->ISDead() || vecRight[j]->ISDead())
					{
						//�� �浹ü�� ���� �������� �浹ü�϶�
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
					//�������� �浹���� �ʾ�����, ������ �浹�ϰ� �ִ�.
					//�� �浹ü�� ���� �������� �浹ü�϶���� �浹���� ���������� ���
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
				//���� �浹�ϰ� ���� �ʴ� ���
				if (iter->second)
				{
					//�������� �浹���� ���(�浹���� �������� ����)
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

	//�� ���� ���� �׷� Ÿ���� ������,
	//ū ���� ��(��Ʈ) �� ���

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
