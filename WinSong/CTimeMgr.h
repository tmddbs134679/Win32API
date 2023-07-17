#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:

	LARGE_INTEGER mllCurCount;
	LARGE_INTEGER mllPreCount;
	LARGE_INTEGER mllFrequency;

	double		  mDeltaTime;		//프레임 사이의 시간 값
	double		  mDeltalAcc;		//함수 호출 회수 체크
	UINT		  micallCount;		//1초 체크를 위한 누적 시간
	UINT		  miFPS;			//초당 호출 횟수
	
	//fps
	//1 프레임당 시간 (Delta Time)

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

