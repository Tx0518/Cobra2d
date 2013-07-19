#ifndef _CEVENT_H_
#define _CEVENT_H_

#include "CCobraObject.h"
#include <string>

typedef enum
{
	EVENT_UNKNOWN,
	EVENT_NEW_ACTIVITY,
	EVENT_DESTORY_ACTIVITY,
	EVENT_LOAD_CONNECT,
	EVENT_LOADER_PROGRESS_DATA,
	EVENT_LOAD_COMPLETE,
	EVENT_LOAD_ERROR,
} cEventCfg;

/*
	CEvent
*/
class CEvent : public CCobraObject
{
public:
	CEvent(void);
	CEvent(cEventCfg evt);
	CEvent(cEventCfg evt,CCobraObject* target);
	virtual ~CEvent(void);
	COBRA_CREATE_PROPERTY(cEventCfg,m_evtType,EventType)
	COBRA_CREATE_PROPERTY(CCobraObject*,m_pTarget,Target)
	COBRA_CREATE_PROPERTY(cError,m_eError,ErrorCode);
	COBRA_CREATE_PROPERTY_BY_REF(std::string,m_strMessage,Message)
};


/*
	CLoadEvent
*/
class CLoadEvent : public CEvent
{
public:
	CLoadEvent(void);
	CLoadEvent(cEventCfg evt);
	CLoadEvent(cEventCfg evt,CCobraObject* target);
	virtual ~CLoadEvent(void);
	
	COBRA_CREATE_PROPERTY(double,m_dTotles,TotleBytes)
	COBRA_CREATE_PROPERTY(double,m_dCurrentByte,CurrentByte)
	COBRA_CREATE_PROPERTY(float,m_fPercent,Percent)
};

class CListener
{
public:
	CListener(void);
	virtual ~CListener(void);
};

/*
	CEventDispather
*/
class CEventDispather
{
public:
	virtual void onDispatcher(CEvent* evt) = 0;
// 	virtual void addEventListener(cEventCfg evtType,CListener* listener) = 0;
// 	virtual void removeEventListener(cEventCfg evtType,CListener* listener) = 0;
};

#endif  //_CEVENT_H_