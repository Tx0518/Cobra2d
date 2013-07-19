#include "CBaseWidget.h"
#include "CommandHandlerMgr.h"
#include "CActionScaleTo.h"


CActionScaleTo::CActionScaleTo(void)
{
	m_iCmdID = CMD_ID_ACTION_SCALE_TO;
	m_fOriginalScale = 1.0f;
	m_fScale = 1.0f;
	m_fDeltaScale = 0.0f;
}


CActionScaleTo::~CActionScaleTo(void)
{

}


void CActionScaleTo::init(float dt,float fScale)
{
	CActionInterval::init(dt);
	m_fScale = fScale;
}

void CActionScaleTo::update(float time)
{
	if (m_pTarget)
    {
		m_pTarget->setScale(m_fOriginalScale + m_fDeltaScale * time);
    }
}

void CActionScaleTo::startWidthTarget(CBaseWidget* pTarget)
{
	m_fOriginalScale = pTarget->getScale();
	m_fDeltaScale    = m_fScale - m_fOriginalScale;
	CActionInterval::startWidthTarget(pTarget);
}