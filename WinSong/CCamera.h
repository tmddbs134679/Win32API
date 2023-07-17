#pragma once

class CObject;


class CCamera
{
	SINGLE(CCamera);


public:
	void update();
	
private:
	void CalDiff();

public:

	void SetLookat(Vec2 _Look)
	{
		m_LookAt = _Look;
		float fMoveDist = (m_LookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	void SetTarget(CObject* _pTarget)
	{
		m_pTargetObj = _pTarget;
	}

public:

	Vec2 GetLookAt()
	{
		return m_vCurLookAt;
	}

	Vec2 GetRenderPos(Vec2 _vObjPos)
	{
		return _vObjPos - m_vDiff;
	}
	
	Vec2 GetRealPos(Vec2 _vRenderPos)
	{
		return _vRenderPos + m_vDiff;
	}

public:

private:

	Vec2		m_LookAt;		//ī�޶�
	Vec2		m_vCurLookAt;	//������ġ�� ������ġ ���� ��ġ
	Vec2		m_vPrevLookAt;	//ī�޶� ���� ���� ������ ��ġ
	CObject*	m_pTargetObj;	//ī�޶� Ÿ�� ������Ʈ
	Vec2		m_vDiff;		//�ػ� �߽���ġ��, ī�޶� Lookat ���� ����
	float		m_fTime;		//Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float		m_fSpeed;		//Ÿ���� ���󰡴� �ӵ�
	float		m_fAccTime;		//���� �ð�
};

