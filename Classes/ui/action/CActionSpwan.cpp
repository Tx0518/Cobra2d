#include "CBaseWidget.h"
#include "CommandHandlerMgr.h"
#include "CActionSpwan.h"


CActionSpwan::CActionSpwan(void)
{
	m_iCmdID = CMD_ID_ACTION_SPWAN;
}


CActionSpwan::~CActionSpwan(void)
{
#if 0//do nothing here
	std::vector<CActionInterval*>::iterator iter = m_vcActions.begin();
	while(iter != m_vcActions.end())
	{
		delete *iter;
		iter++;
	}
	m_vcActions.clear();
#endif
}


void CActionSpwan::initWidthActions(CActionInterval *pAction1,...)
{
	float fDuration = 0.0f;
	m_vcActions.push_back(pAction1);
	fDuration = pAction1->getDuration();

	CActionInterval *pNow = NULL;
	va_list params;
	va_start(params, pAction1);
	pNow = va_arg(params, CActionInterval*);
	m_vcActions.push_back(pNow);
	fDuration = comax(fDuration,pNow->getDuration());
	va_end(params);

	m_duration = fDuration;
	std::vector<CActionInterval*>::iterator iter = m_vcActions.begin();
	while(iter != m_vcActions.end())
	{
		(*iter)->setDuration(fDuration);
		iter++;
	}
}

void CActionSpwan::update(float time)
{
	if (m_pTarget)
	{
		std::vector<CActionInterval*>::iterator iter = m_vcActions.begin();
		while(iter != m_vcActions.end())
		{
			(*iter)->update(time);
			iter++;
		}
	}
}

void CActionSpwan::startWidthTarget(CBaseWidget* pTarget)
{
	CActionInterval::startWidthTarget(pTarget);
	std::vector<CActionInterval*>::iterator iter = m_vcActions.begin();
	while(iter != m_vcActions.end())
	{
		(*iter)->startWidthTarget(pTarget);
		iter++;
	}
}