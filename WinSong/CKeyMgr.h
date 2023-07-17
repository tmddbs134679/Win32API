#pragma once
#include "pch.h"
#include "Define.h"


//1. 프레임 동기화
//동일 프레임 내에 같은 키에 대해, 동일한 이벤트를 가져간다.

//2. 키 입력 이벤트 처리
//tap, hold, away


enum class KEY_STATE
{
	NONE,	//눌리지 않고, 이전프레임에도 눌리지 않은 상태
	TAP,	//막 누른 시점
	HOLD,	//누르고 있는
	AWAY	//막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	LSHIFT,
	SPACE,
	CTRL,
	ENTER,
	ESC,
	LBTN,
	RBTN,
	LAST
};

struct tKeyInfo
{
	KEY_STATE	eState;	//키의 상태값

	bool		bPrevPush;	//이전 프레임에 눌렸는지 
};


class CKeyMgr
{
	SINGLE(CKeyMgr);


public:
	void init();
	void update();

public:

	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

	Vec2 GetMousePos()
	{
		return m_vCurMousePos;
	}

private:
	//벡터 내에서 인덱스가 곧 키값이다.
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;



};

