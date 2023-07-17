#pragma once


#include "CMonFactory.h"

// 전방 선언
class CObject;


class CScene
{


public:

			CScene();
	virtual ~CScene();

public:
	//부모클래스는 인터페이스 역할이기 때문에 순수가상함수로 만들어서 객체화할 수 없게 만들고 알리고
	//자식클래스들은 실수로 만들지 않았더라고 에러를 발생하게 해준다.
	virtual void Enter() = 0;	//Scene에 진입 시 호출
	virtual void Exit() = 0;	//Scene에 탈출 시 호출
	
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
	//인라인 함수로 헤더파일에 선언과 구현 모두 했기 때문에 오버헤드가 발생하지 않고 호출 비용도 없다.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	//복사하지않고 원본자체를 주기 위하여 &로 주고 변경되면 안되므로 const
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
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; //오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName;

	UINT				m_iTileX;
	UINT				m_iTileY;

	CObject*			m_pPlayer;	//Player
};

