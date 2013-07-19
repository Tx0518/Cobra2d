#ifndef _CINTENT_H_
#define _CINTENT_H_

#include "CCobraObject.h"

typedef enum
{
	INTENT_UNKOWN,
	INTENT_START_ACTIVITY,
	INTENT_FINLISH_ACTIVITY,
	INTENT_REGISTER_CONTROLLER,
	INTENT_REGISTER_OBSERVER,
	INTENT_UNREGISTER_OBSERVER,
	INTENT_BIND_SERVICE,
	INTENT_UNBIND_SERVICE,
	INTENT_FETCH_DATA,
	INTENT_GET_ACTIVITY,
	INTENT_GET_SERVICE,
	INTENT_LOAD_UI,
	INTENT_UNLOAD_UI,
	INTENT_UPDATE_UI,
	INTENT_HTTP_GET,
	INTENT_HTTP_POST,
	INTENT_HTTP_DOWNLOAD,
	INTENT_REGISTER_EVENT,
	INTENT_UNREGISTER_EVENT,
	INTENT_EXEC_EVENT,
	INTENT_UPDATE_DATASTREAM,
} cIntentAction;

class CCobraObject;
class CBundle;

/*
	CIntent
	TODO operation task 
*/
class CIntent : public CCobraObject
{
public:
	CIntent(void);
	CIntent(cIntentAction action);
	CIntent(CIntent& other);
	CIntent(cIntentAction action,int targetId,int ServiceID);
	CIntent(cIntentAction action,CCobraObject* obj);
	CIntent(cIntentAction action,int targetId,int ServiceID,CCobraObject* obj);
	CIntent& operator=(CIntent& other);
	virtual ~CIntent(void);
	
	COBRA_CREATE_PROPERTY(int,m_iTargetID,TargetID)
	COBRA_CREATE_PROPERTY(cIntentAction,m_iAction,IntentAction)
	COBRA_CREATE_PROPERTY(int,m_iServiceID,ServiceID)
	COBRA_CREATE_PROPERTY(CCobraObject*,m_TargetObject,TargetObj)
	COBRA_CREATE_PROPERTY(CBundle*,m_pBundle,Bundle)
	COBRA_CREATE_PROPERTY(void*,m_data,Data)
	COBRA_CREATE_PROPERTY_BY_REF(std::string,m_strName,TargetName)
};


#endif //_CINTENT_H_