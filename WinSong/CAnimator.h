#pragma once

class CTexture;
class CObject;
class CAnimation;


class CAnimator
{

public:
	CAnimator();
	~CAnimator();

	friend class CObject;

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize
						 ,Vec2 _vStep, float fDuration,UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void render(HDC _dc);
	void update();
	void finalupdate();

public:
	CObject* GetObj()
	{
		return m_pOwner;
	}

private:

	map<wstring, CAnimation*>	m_mapAnim;		//��� Animation
	CObject*					m_pOwner;		//���� ������� Animation
	CAnimation*					m_pCurAnim;		//Animator ���� ������Ʈ
	bool						m_bRepeat;		//�ݺ���� ����

};

