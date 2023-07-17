#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	:m_szCountentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	//현재 경로를 채움
	GetCurrentDirectory(225, m_szCountentPath);

	//상위 폴더로 

	int iLen = wcslen(m_szCountentPath);

	//배열의 문자열 마지막부터 시작해야하지만 인덱스니까 -1
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szCountentPath[i])
		{
			m_szCountentPath[i] = '\0';
			break;
		}
	}

	//// + bin\\content\\

	wcscat_s(m_szCountentPath, 255, L"\\bin\\content\\");


	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szCountentPath);
}

wstring CPathMgr::GetRealativePath(const wchar_t* _filepath)
{

	wstring strFilePath = _filepath;


	size_t iAbsLen = wcslen(m_szCountentPath);
	size_t iFullLen = strFilePath.length();


	wstring strRelativePath = strFilePath.substr(iAbsLen,iFullLen - iAbsLen);

	return strRelativePath;
}
