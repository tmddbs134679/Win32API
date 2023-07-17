#pragma once

class CCollider;


union COLLIDER_ID
{
	struct 
	{
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr)


public:

	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

private:

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
	
public:

	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}


private:
	map<ULONGLONG, bool> m_mapColInfo;				//�浹ü ���� ���� ������ �浹 ����

	UINT	m_arrCheck[(UINT)GROUP_TYPE::END];		//�׷찣�� �浹 üũ ��Ʈ����
	
};

