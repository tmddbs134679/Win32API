#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

	friend class CEventMgr;
public:

	void init();
	void update();
	void render(HDC _dc);

private:

	void ChangeScene(SCENE_TYPE _eNext);

public:

	CScene* GetCurScene()
	{
		return m_pCurScene;
	}

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];		//¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene;							//ÇöÀç ¾À



};

