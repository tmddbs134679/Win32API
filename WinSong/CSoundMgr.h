#pragma once
// sound �뵵 - ��� ���� �߿�
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü
	CSound* m_pBGM;		// ���� ������ BGM Sound

public:

	int init(void);

	void RegisterToBGM(CSound* _pSound);

public:

	LPDIRECTSOUND8 GetSoundDevice()
	{ 
		return m_pSound;
	}


	
};