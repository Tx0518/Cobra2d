#ifndef _CEVENT_H_
#define _CEVENT_H_

#include "CCobraObject.h"

typedef enum
{
	EVENT_UNKNOWN,
	EVENT_REGISTER_ACTIVITY,
	EVENT_UNREGISTER_ACTIVITY,
} cEventCfg;

class CEvent : public CCobraObject
{
public:
	CEvent(void);
	CEvent(cEventCfg evt);
	CEvent(cEventCfg evt,CCobraObject* target);
	virtual ~CEvent(void);

	COBRA_CREATE_PROPERTY(cEventCfg,m_evtType,EventType)
	COBRA_CREATE_PROPERTY(CCobraObject*,m_pTarget,Target)
};

#endif  //_CEVENT_H_