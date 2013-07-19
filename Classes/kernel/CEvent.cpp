#include "CEvent.h"

CEvent::CEvent( void )
	:m_evtType(EVENT_UNKNOWN),
	m_pTarget(NULL),
	m_strMessage(""),
	m_eError(ERROR_UNKNOW)
{
	setObjType(COBRA_EVENT);
}

CEvent::CEvent( cEventCfg evt )
	:m_evtType(evt),
	m_pTarget(NULL),
	m_strMessage(""),
	m_eError(ERROR_UNKNOW)
{
	setObjType(COBRA_EVENT);
}

CEvent::CEvent( cEventCfg evt,CCobraObject* target )
	:m_evtType(evt),
	m_pTarget(target),
	m_strMessage(""),
	m_eError(ERROR_UNKNOW)
{
	setObjType(COBRA_EVENT);
}

CEvent::~CEvent(void)
{
}

/************************************************************************/
/*
	CLoadEvent
*/
/************************************************************************/
CLoadEvent::CLoadEvent( void )
	:m_fPercent(0.0f),
	m_dCurrentByte(0.0f),
	m_dTotles(0.0f)
{

}

CLoadEvent::CLoadEvent( cEventCfg evt )
	:CEvent(evt),
	m_fPercent(0.0f),
	m_dCurrentByte(0.0f),
	m_dTotles(0.0f)
{
}

CLoadEvent::CLoadEvent( cEventCfg evt,CCobraObject* target )
	:CEvent(evt,target),
	m_fPercent(0.0f),
	m_dCurrentByte(0.0f),
	m_dTotles(0.0f)
{

}

CLoadEvent::~CLoadEvent( void )
{
	setPercent(0.0f);
	setCurrentByte(0.0f);
	setTotleBytes(0.0f);
}