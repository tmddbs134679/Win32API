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

	Vec2		m_vForce;		// 크기, 방향
	Vec2		m_vAccel;		// 가속도
	Vec2		m_vAccelA;		//추가 가속도 
	Vec2		m_vVelocity;	//속도(크기 : 속력, 방향)  
	Vec2		m_vMaxVelocity;	//최대 속력

	
	//float		m_fSpeed		//속력(순수한 속도의 양)
	float		m_fMass;		// 질량
	float		m_fricCoeff;	//마찰 계수




	// F = M * a;
	// V =+= A * DT;
	
};

