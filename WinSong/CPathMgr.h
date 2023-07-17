#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szCountentPath[255];
	wchar_t		m_szRelativePath[256];

public:
	void init();

public:
	const wchar_t* GetContentPath()
	{
			return m_szCountentPath;
	}

public:

	wstring GetRealativePath(const wchar_t* _filepath);

};

