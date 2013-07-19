#include "CBaseWidget.h"
#include "CommandHandlerMgr.h"
#include "CActionFadeTo.h"


CActionFadeTo::CActionFadeTo(void)
{
	m_fromOpacity = 0;
	m_toOpacity = 0;
	m_iCmdID = CMD_ID_ACTION_FADE_TO;
}


CActionFadeTo::~CActionFadeTo(void)
{
}


void CActionFadeTo::init(float dt,unsigned char opacity)
{
	CActionInterval::init(dt);
	m_toOpacity = opacity;
}

void CActionFadeTo::update(float time)
{
	CColor4B color = m_pTarget->getBkColor();
	color.a = (unsigned char)(m_fromOpacity + (m_toOpacity - m_fromOpacity) * time);
	m_pTarget->setBkColor(color);
}

void CActionFadeTo::startWidthTarget(CBaseWidget* pTarget)
{
	m_fromOpacity = pTarget->getBkColor().a;
	CActionInterval::startWidthTarget(pTarget);
}