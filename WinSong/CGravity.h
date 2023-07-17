#pragma once

class CObject;

class CGravity
{

public:
	CGravity();
	~CGravity();
	
	friend class CObject;

public:
	void finalupdate();

public:

	void SetGround(bool _b);

private:

	CObject* m_pOwner;

	bool	 m_bGround;


};

