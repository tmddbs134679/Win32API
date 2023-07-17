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
	//���� ī��Ʈ
	QueryPerformanceCounter(&mllPreCount);

	//�ʴ� ī��Ʈ
	QueryPerformanceFrequency(&mllFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&mllCurCount);
	
	//���� �������� ī���ð�, ���� �������� ī���� ���� ����
	mDeltaTime = (double)(mllCurCount.QuadPart - mllPreCount.QuadPart) / (double)mllFrequency.QuadPart;

	//���� ī��Ʈ ����
	mllPreCount = mllCurCount;

#ifdef _DEBUG

	//DT�� ����� �� ����
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
