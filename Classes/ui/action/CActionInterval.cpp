#include "CBaseWidget.h"
#include "CommandHandlerMgr.h"
#include "CActionInterval.h"
#include "CMarcos.h"
CActionInterval::CActionInterval(void)
{
	m_pTarget  = NULL;
	m_duration = 0.0f;
	m_elapsed = 0.0f;
	m_bFirstTick = true;
	m_iCmdID  = 0;
}


CActionInterval::~CActionInterval(void)
{
}

void CActionInterval::init(float dt)
{
	m_duration = dt;
    if (m_duration == 0)
    {
        m_duration = FLT_EPSILON;
    }
    m_elapsed = 0;
    m_bFirstTick = true;
}

void CActionInterval::step(float dt)
{
	 if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += dt;
    }

    this->update(comax (0,comin(1, m_elapsed /comax(m_duration, FLT_EPSILON))));
	CUICommand cmd;
	cmd.setCmdID(m_iCmdID);
	cmd.setSource(m_pTarget);
	CCommandHandlerMgr::instance()->postCmd(cmd);
}

void CActionInterval::update(float time)
{
	;//here do nothing
}

bool CActionInterval::isDone(void)
{
	return m_elapsed >= m_duration;
}

void CActionInterval::startWidthTarget(CBaseWidget* pTarget)
{
	m_pTarget = pTarget;
	this->addInterestCmdID(m_iCmdID);
	CUICommand cmd;
	cmd.setCmdID(m_iCmdID);
	cmd.setSource(m_pTarget);
	CCommandHandlerMgr::instance()->addCmdHander((CCommandHandler*)this);
	CCommandHandlerMgr::instance()->postCmd(cmd);
}


void CActionInterval::handleCmd(CUICommand& cmd)
{
	if (m_pTarget == cmd.getSource())
	{
		if(!this->isDone())
		{
			this->step(cmd.getdeltaT());
		}
		else
		{	//this operation just set a flag 
			//and then delete action in logic looper
			CCommandHandlerMgr::instance()->removeCmdHandler(this);
		}
	}
}