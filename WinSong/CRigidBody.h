#pragma once

class CObject;


class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;

public:
	void finalupdate();

	void Move();

public:

	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}

	void SetMass(float _fMass)
	{
		m_fMass = _fMass;
	}
	
	void SetVelocity(Vec2 _v)
	{
		m_vVelocity = _v;
	}

	void SetMaxVelocity(Vec2 _v)
	{
		m_vMaxVelocity = _v;
	}
	
	void SetAccelAlpha(Vec2 _vAccel)
	{
		m_vAccelA = _vAccel;
	}

public:
	
	void AddVelocity(Vec2 _v)
	{
		m_vVelocity += _v;
	}

	float GetMass()
	{
		return m_fMass;
	}

	Vec2 GetVelocity()
	{
		return m_vVelocity;
	}

private:
	CObject* m_pOwner;

	Vec2		m_vForce;		// ũ��, ����
	Vec2		m_vAccel;		// ���ӵ�
	Vec2		m_vAccelA;		//�߰� ���ӵ� 
	Vec2		m_vVelocity;	//�ӵ�(ũ�� : �ӷ�, ����)  
	Vec2		m_vMaxVelocity;	//�ִ� �ӷ�

	
	//float		m_fSpeed		//�ӷ�(������ �ӵ��� ��)
	float		m_fMass;		// ����
	float		m_fricCoeff;	//���� ���




	// F = M * a;
	// V =+= A * DT;
	
};

