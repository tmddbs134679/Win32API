#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->render(_dc);
}

void CAnimator::update()
{


}

void CAnimator::finalupdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();

		//if문에서 비교연산을 할 때 앞에게 앞뒤에 넣을 변수 위치도 최적화를 할 때 중요하다
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	//애니매이션이 존재할 경우 assert
	assert(pAnim == nullptr);
		
	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration, _iFrameCount);


	m_mapAnim.insert(make_pair(_strName, pAnim));

}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return	iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}
