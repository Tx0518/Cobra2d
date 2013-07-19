#include "CIntent.h"
#include "CCobraObject.h"
#include "CBundle.h"


CIntent::CIntent( void )
	:m_iAction(INTENT_UNKOWN),
	m_iServiceID(COBRA_UNKNOWN),
	m_iTargetID(COBRA_UNKNOWN),
	m_TargetObject(NULL),
	m_pBundle(NULL),
	m_data(NULL),
	m_strName("")
{
	
}

CIntent::CIntent( cIntentAction action )
	:m_iAction(action),
	m_iServiceID(COBRA_UNKNOWN),
	m_iTargetID(COBRA_UNKNOWN),
	m_TargetObject(NULL),
	m_pBundle(NULL),
	m_data(NULL),
	m_strName("")
{
}

CIntent::CIntent( cIntentAction action,CCobraObject* obj )
	:m_iAction(action),
	m_TargetObject(obj),
	m_iTargetID(COBRA_UNKNOWN),
	m_iServiceID(COBRA_UNKNOWN),
	m_pBundle(NULL),
	m_data(NULL),
	m_strName("")
{
}


CIntent::CIntent( cIntentAction action,int targetId,int ServiceID,CCobraObject* obj )
	:m_iAction(action),
	m_iTargetID(targetId),
	m_iServiceID(ServiceID),
	m_TargetObject(obj),
	m_pBundle(NULL),
	m_data(NULL)
{
}


CIntent::CIntent( cIntentAction action,int targetId,int ServiceID )
	:m_iAction(action),
	m_iServiceID(ServiceID),
	m_iTargetID(targetId),
	m_TargetObject(NULL),
	m_pBundle(NULL),
	m_data(NULL),
	m_strName("")
{
}

CIntent::CIntent( CIntent& other )
{
	setIntentAction(other.getIntentAction());
	setServiceID(other.getServiceID());
	setTargetID(other.getTargetID());
	setTargetObj(other.getTargetObj());
	setBundle(other.getBundle());
	setData(other.getData());
}

CIntent& CIntent::operator=( CIntent& other )
{
	setIntentAction(other.getIntentAction());
	setServiceID(other.getServiceID());
	setTargetID(other.getTargetID());
	setTargetObj(other.getTargetObj());
	setBundle(other.getBundle());
	setData(other.getData());
	return *this;
}

CIntent::~CIntent( void )
{
	m_TargetObject = NULL;
	m_data = NULL;
	m_pBundle = NULL;
}
