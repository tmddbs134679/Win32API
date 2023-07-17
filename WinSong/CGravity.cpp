#include "pch.h"
#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"

CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CGravity::~CGravity()
{
}

void CGravity::finalupdate()
{
	if(m_pOwner->GetRigidBody() != nullptr)
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 1200.f));

}

void CGravity::SetGround(bool _b)
{
		m_bGround = _b;

		if (m_bGround)
		{
			if (m_pOwner->GetRigidBody() != nullptr)
			{
				Vec2 vV = m_pOwner->GetRigidBody()->GetVelocity();

				m_pOwner->GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));
			}
			
		}
	
}
