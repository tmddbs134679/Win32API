#pragma once

class CTexture;
class CRes;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);



public:
		//키값으로 wstring
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
private:

	map<wstring, CRes*>	m_mapTex;
	map<wstring, CRes*>	m_mapSound;
}; 

