#include "CObserver.h"
#include "CNetMarcos.h"

#include "CIntent.h"
#include "CHandler.h"
#include "CMemoryCache.h"
/************************************************************************/
/* 
	CController
*/

IMPLEMENT_DYNCREATE(CController);

CController::CController()
	:m_iObserverId(COBRA_UNKNOWN)
{
}

CController::~CController( void )
{
	m_iObserverId = COBRA_UNKNOWN;
}

void CController::assign()
{
	COBRA_CHECK_UNKNOWN(m_iObserverId);
	CIntent intent(INTENT_REGISTER_CONTROLLER,m_iObserverId,SERVICE_ACTIVITY,this);
	CHandler::onHandler(&intent);
}

void CController::execute( void* data )
{
	//override
}

/************************************************************************/

/************************************************************************/
/*
	CObserver
*/
CObserver::CObserver( void )
	:m_iReceiverId(COBRA_UNKNOWN)
{
}


CObserver::~CObserver( void )
{
	m_iReceiverId = COBRA_UNKNOWN;
}

void CObserver::addController( CController* control )
{
	COBRA_CHECK_NULL(control);
	m_pControllerSet[control->getObjectID()] = control;
	control->setObserverID(getObjectID());
}

bool CObserver::containsController( int objId )
{
	pControllItorSet itor = m_pControllerSet.find(objId);
	return itor!= m_pControllerSet.end();
}

void CObserver::removeController( CController* control )
{
	COBRA_CHECK_NULL(control);
	pControllItorSet itor = m_pControllerSet.find(control->getObjectID());
	if(itor != m_pControllerSet.end())
	{
		COBRA_SAFE_DELETE(itor->second);
		m_pControllerSet.erase(itor);
	}
}

void CObserver::dispatchController( void* data )
{
	COBRA_RETURN_IF(m_pControllerSet.empty() == true);
	SeqMsgHead* msg = (SeqMsgHead*) data;
	COBRA_CHECK_NULL(msg);
	pControllItorSet itor = m_pControllerSet.find(msg->usType);
	if(itor != m_pControllerSet.end())
		itor->second->execute(data);
}

bool CObserver::hasReceiver()
{
	return m_iReceiverId != COBRA_UNKNOWN;
}

void CObserver::onHandlerDataStream( void* pMsg )
{
	pushNetMsg(pMsg);
}

void CObserver::pushNetMsg( void* pMsg )
{
	m_pNetMsgList.push(pMsg);
	if(hasReceiver())
		flushNetMsg();
}

/*
	when activity is active to flush net message
*/
void CObserver::restart()
{
	flushNetMsg();
}

void CObserver::flushNetMsg()
{
	COBRA_RETURN_IF(m_pControllerSet.empty() == true);
	void* data = m_pNetMsgList.front();
	m_pNetMsgList.pop();
	dispatchController(data);
	if(!m_pNetMsgList.empty())
		flushNetMsg();
}

/*
	validate net message queue length
*/
bool CObserver::hasNetMsgUnPost()
{
	return !m_pNetMsgList.empty();
}

/************************************************************************/
