#pragma once

class CObject;

class CCollider
{
public:

	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;

public:
	void finalupdate();
	void render(HDC _dc);

	//�浹 ���� �Լ�
	void OnCollision(CCollider* _pOther);		//�浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);  //�浹 ���� �Լ�
	void OnCollisionExit(CCollider* _pOther);	//�浹 ���� �Լ�

public:
	//�浹ü���� ���Կ����� ���ʿ� -> ���Կ����ڸ� ������.
	CCollider& operator = (CCollider& _origin) = delete;

public:

	void SetOffsetPos(Vec2 _vPos)
	{
		m_vOffsetPos = _vPos;
	}

	void setScale(Vec2 _vScale)
	{
		m_vScale = _vScale;
	}

public:

	Vec2 GetOffsetPos()
	{
		return m_vOffsetPos;
	}

	Vec2 GetScale()
	{
		return m_vScale;
	}

	UINT GetID()
	{
		return m_iID;
	}

	Vec2 GetFinalPos()
	{
		return m_vFinalPos;
	}

	CObject* GetObj()
	{
		return m_pOwner;
	}

private:
	static	UINT g_iNextID;
	
	CObject* m_pOwner;			//collider�� �����ϰ� �ִ� ������Ʈ
	Vec2	 m_vOffsetPos;		//������Ʈ�� ���� ������� ��ġ
	Vec2	 m_vFinalPos;		//finalupdate���� �� �����Ӹ��� ���
	Vec2	 m_vScale;			//�浹ü�� ũ��

	UINT	 m_iID;				//�浹ü ������ ID ��

	UINT	 m_iCol;
	
};

