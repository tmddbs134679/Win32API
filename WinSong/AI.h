#pragma once

class CMonster;
class CState;

class AI
{

public:

	AI();
	~AI();

	friend class CMonster;

public:

	void update();
	
	void AddState(CState* _pState);
	void SetCurState(MON_STATE _eState);
	CState* GetState(MON_STATE _eState);
	void ChangeState(MON_STATE _eState);

public:
	CMonster* GetOwner()
	{
		return m_pOwner;
	}

private:

	CMonster*				m_pOwner;

	map<MON_STATE, CState*>	m_mapState;

	CState*					m_pCurState;

};

