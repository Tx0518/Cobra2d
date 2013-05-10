#include "CEvent.h"

CEvent::CEvent( void )
	:m_evtType(EVENT_UNKNOWN),
	m_pTarget(NULL)
{

}

CEvent::CEvent( cEventCfg evt )
	:m_evtType(evt),
	m_pTarget(NULL)
{

}

CEvent::CEvent( cEventCfg evt,CCobraObject* target )
	:m_evtType(evt),
	m_pTarget(target)
{

}

CEvent::~CEvent(void)
{

}

void CEvent::setEventType(cEventCfg var)
{
	m_evtType = var;
}

cEventCfg CEvent::getEventType()
{
	return m_evtType;
}

void CEvent::setTarget(CCobraObject* var)
{
	m_pTarget = var;
}

CCobraObject* CEvent::getTarget()
{
	return m_pTarget;
}