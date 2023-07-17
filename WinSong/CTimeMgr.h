#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:

	LARGE_INTEGER mllCurCount;
	LARGE_INTEGER mllPreCount;
	LARGE_INTEGER mllFrequency;

	double		  mDeltaTime;		//������ ������ �ð� ��
	double		  mDeltalAcc;		//�Լ� ȣ�� ȸ�� üũ
	UINT		  micallCount;		//1�� üũ�� ���� ���� �ð�
	UINT		  miFPS;			//�ʴ� ȣ�� Ƚ��
	
	//fps
	//1 �����Ӵ� �ð� (Delta Time)

public:
	void init();
	void update();
	void render();

public:
	double GetDeltaTime()
	{
		return mDeltaTime;
	}

	float GetfDeltaTime()
	{
		return (float)mDeltaTime;
	}

};

