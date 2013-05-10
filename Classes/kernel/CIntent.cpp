#include "CIntent.h"
#include "CCobraObject.h"

CIntent::CIntent( void )
	:m_iAction(INTENT_UNKOWN),
	m_iServiceID(-1),
	m_iTargetKey(-1),
	m_TargetObject(NULL)
{
	
}

CIntent::CIntent( int action )
	:m_iAction(action),
	m_iServiceID(-1),
	m_iTargetKey(-1),
	m_TargetObject(NULL)
{

}


CIntent::CIntent( int action,int targetKey,int ServiceID,CCobraObject* obj )
	:m_iAction(action),
	m_iTargetKey(targetKey),
	m_iServiceID(ServiceID),
	m_TargetObject(obj)
{

}


CIntent::CIntent( CIntent& other )
{
	setIntentAction(other.getIntentAction());
	setServiceID(other.getServiceID());
	setTargetKey(other.getTargetKey());
	setTargetObj(other.getTargetObj());
}



CIntent& CIntent::operator=( CIntent& other )
{
	setIntentAction(other.getIntentAction());
	setServiceID(other.getServiceID());
	setTargetKey(other.getTargetKey());
	setTargetObj(other.getTargetObj());
	return *this;
}


CIntent::~CIntent( void )
{

}

void CIntent::setIntentAction(int var)
{
	m_iAction = var;
}

int CIntent::getIntentAction()
{
	return m_iAction;
}

void CIntent::setTargetKey(int var)
{
	m_iTargetKey = var;
}

int CIntent::getTargetKey()
{
	return m_iTargetKey;
}

void CIntent::setServiceID(int var)
{
	m_iServiceID = var;
}

int CIntent::getServiceID()
{
	return m_iServiceID;
}

void CIntent::setTargetObj(CCobraObject* var)
{	
	m_TargetObject = var;
}

CCobraObject* CIntent::getTargetObj()
{
	return m_TargetObject;
}