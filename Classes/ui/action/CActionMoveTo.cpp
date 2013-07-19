#include "CommandHandlerMgr.h"
#include "CActionMoveBy.h"
#include "CActionMoveTo.h"


CActionMoveTo::CActionMoveTo(void)
{
	m_ptDest = PointZero;
}


CActionMoveTo::~CActionMoveTo(void)
{
}


void CActionMoveTo::init(float dt,CPoint& ptDest)
{
	CActionInterval::init(dt);
	m_ptDest = ptDest;
}

void CActionMoveTo::startWidthTarget(CBaseWidget* pTarget)
{
	CActionMoveBy::startWidthTarget(pTarget);
	m_ptDelta = CreateCPoint(m_ptDest.x - m_ptStart.x, m_ptDest.y - m_ptStart.y);
}