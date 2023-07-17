#pragma once


#include "CMonFactory.h"

// ���� ����
class CObject;


class CScene
{


public:

			CScene();
	virtual ~CScene();

public:
	//�θ�Ŭ������ �������̽� �����̱� ������ ���������Լ��� ���� ��üȭ�� �� ���� ����� �˸���
	//�ڽ�Ŭ�������� �Ǽ��� ������ �ʾҴ���� ������ �߻��ϰ� ���ش�.
	virtual void Enter() = 0;	//Scene�� ���� �� ȣ��
	virtual void Exit() = 0;	//Scene�� Ż�� �� ȣ��
	
	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
public:
	
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	void render_tile(HDC _dc);

public:
	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}

public:

	const wstring& GetName()
	{
		return m_strName;
	}

	UINT GetTileX()
	{
		return m_iTileX;
	}

	UINT GetTileY()
	{
		return m_iTileY;
	}

	CObject* GetPlayer()
	{
		return m_pPlayer;
	}

public:
	//�ζ��� �Լ��� ������Ͽ� ����� ���� ��� �߱� ������ ������尡 �߻����� �ʰ� ȣ�� ��뵵 ����.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	//���������ʰ� ������ü�� �ֱ� ���Ͽ� &�� �ְ� ����Ǹ� �ȵǹǷ� const
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	vector<CObject*>& GetUIGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::UI];
	}

	void RegisterPlayer(CObject* _pPlayer)
	{
		m_pPlayer = _pPlayer;
	}


private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; //������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;

	UINT				m_iTileX;
	UINT				m_iTileY;

	CObject*			m_pPlayer;	//Player
};

