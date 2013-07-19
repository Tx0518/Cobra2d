#include "CBaseWidget.h"
#include "CommandHandlerMgr.h"
#include "CActionInterval.h"
#include "CActionMoveBy.h"


CActionMoveBy::CActionMoveBy(void)
{
	m_ptDelta = PointZero;
	m_ptStart = PointZero;
    m_ptPre   = PointZero;
	m_iCmdID  = CMD_ID_ACTION_MOVE_BY;
}


CActionMoveBy::~CActionMoveBy(void)
{
}


void CActionMoveBy::init(float dt,CPoint& ptDelta)
{
	CActionInterval::init(dt);
	m_ptDelta = ptDelta;
}

void CActionMoveBy::startWidthTarget(CBaseWidget* pTarget)
{
	CRectange rc = pTarget->getRect();
	m_ptStart = rc.origin;
    m_ptPre   = m_ptStart;
	CActionInterval::startWidthTarget(pTarget);
}
	
void CActionMoveBy::update(float time)
{
	if (m_pTarget)
    {
		CRectange rc = m_pTarget->getRect();
		CPoint currentPos = rc.origin;
		CPoint diff = CreateCPoint(currentPos.x - m_ptPre.x,currentPos.y - m_ptPre.y);
        m_ptStart = CreateCPoint(m_ptStart.x + diff.x, m_ptStart.y + diff.y);
        CPoint newPos =  CreateCPoint( m_ptStart.x + m_ptDelta.x * time, m_ptStart.y + m_ptDelta.y * time);
		rc.origin = newPos;
        m_pTarget->setRect(rc);
        m_ptPre = newPos;
    }
}