#pragma once
#include "pch.h"
#include "Define.h"


//1. ������ ����ȭ
//���� ������ ���� ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

//2. Ű �Է� �̺�Ʈ ó��
//tap, hold, away


enum class KEY_STATE
{
	NONE,	//������ �ʰ�, ���������ӿ��� ������ ���� ����
	TAP,	//�� ���� ����
	HOLD,	//������ �ִ�
	AWAY	//�� �� ����
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
	KEY_STATE	eState;	//Ű�� ���°�

	bool		bPrevPush;	//���� �����ӿ� ���ȴ��� 
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
	//���� ������ �ε����� �� Ű���̴�.
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;



};

