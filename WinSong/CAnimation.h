#pragma once

class CAnimator;
class CTexture;


struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;
	
};



class CAnimation
{

public:

	CAnimation();
	~CAnimation();
	friend class CAnimator;

public:

	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

private:

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}

	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

public:

	const wstring& GetName()
	{
		return m_strName;
	}

	//�޾ư� �ʿ��� ���������ϰ� &�� ��ȯ
	tAnimFrm& GetFrame(int _iIdx)
	{
		return m_vecFrm[_iIdx];
	}

	UINT GetMaxFrame()
	{
		return (UINT)m_vecFrm.size();
	}

	bool IsFinish()
	{
		return m_bFinish;
	}



private:

	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;			//Animation �� ����ϴ� �ؽ���
	vector<tAnimFrm>	m_vecFrm;		//��� ������ ����
	int					m_iCurFrm;		//���� ������
	float				m_fAccTime;		//�ð� ����
	bool				m_bFinish;		//��� ���� ���޿���
};

