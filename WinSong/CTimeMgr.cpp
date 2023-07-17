#include "pch.h"
#include "CTimeMgr.h"
#include  <stdio.h>
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: mllPreCount{}
	,mllCurCount{}
	, mllFrequency{}
	, mDeltaTime(0.)
	, mDeltalAcc(0.)
	, micallCount(0)
	
{

}


CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//현재 카운트
	QueryPerformanceCounter(&mllPreCount);

	//초당 카운트
	QueryPerformanceFrequency(&mllFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&mllCurCount);
	
	//이전 프레임의 카운팅과, 현재 프레임의 카운팅 값의 차이
	mDeltaTime = (double)(mllCurCount.QuadPart - mllPreCount.QuadPart) / (double)mllFrequency.QuadPart;

	//이전 카운트 갱신
	mllPreCount = mllCurCount;

#ifdef _DEBUG

	//DT값 디버그 때 고정
	if (mDeltaTime > (1. / 60.))
		mDeltaTime = (1. / 60.);


#endif
	

}

void CTimeMgr::render()
{
	++micallCount;
	mDeltalAcc += mDeltaTime;

	if (mDeltalAcc >= 1.)
	{
		miFPS = micallCount;
		mDeltalAcc = 0.;
		micallCount = 0;

		wchar_t szBuffer[225] = {};
		swprintf_s(szBuffer, L"FPS : %d, DeltaTime : %1f", miFPS, mDeltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
