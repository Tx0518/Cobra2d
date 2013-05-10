#ifndef _CINTENT_H_
#define _CINTENT_H_

#include "CMarcos.h"

typedef enum
{
	INTENT_UNKOWN,
	INTENT_START_ACTIVITY,
	INTENT_FINLISH_ACTIVITY,
	INTENT_BIND_SERVICE,
	INTENT_UNBIND_SERVICE,
	INTENT_FETCH_DATA,
} cIntentAction;


class CCobraObject;
/*
	CIntent
*/
class CIntent
{
public:
	CIntent(void);
	CIntent(int action);
	CIntent(CIntent& other);
	CIntent& operator=(CIntent& other);
	CIntent(int action,int targetKey,int ServiceID,CCobraObject* obj);
	virtual ~CIntent(void);
	
	COBRA_CREATE_PROPERTY(int,m_iTargetKey,TargetKey)
	COBRA_CREATE_PROPERTY(int,m_iAction,IntentAction)
	COBRA_CREATE_PROPERTY(int,m_iServiceID,ServiceID)
	COBRA_CREATE_PROPERTY(CCobraObject*,m_TargetObject,TargetObj)
};


#endif //_CINTENT_H_