#include "CActivityServiceProxy.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CActivity.h"
#include "CMemoryCache.h"
#include "CObserver.h"

/************************************************************************/
/* 
CStartActivityProxy
*/
CStartActivityProxy::CStartActivityProxy( CService* content )
	:IServiceProxy(content)
{
}

CStartActivityProxy::~CStartActivityProxy( void )
{
}

void CStartActivityProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CActivity* activity = dynamic_cast<CActivity*>(intent->getTargetObj());
	if(activity == NULL)
	{
		response->setRespCode(RESPONSE_START_ACTIVITY_FAILURE);
	}
	else
	{
		activity->onCreate();
		activity->setObjectID(intent->getTargetID());
		response->setRespCode(RESPONSE_START_ACTIVITY_SUCCESS);
		m_pContext->addCobraObject(activity);
	}
	response->setRespTarget(activity);
	COBRA_SAFE_DELETE(intent);
}

/************************************************************************/


/************************************************************************/
/* 
CFinishActivityProxy
*/
CFinishActivityProxy::CFinishActivityProxy( CService* content )
	:IServiceProxy(content)
{
}

CFinishActivityProxy::~CFinishActivityProxy( void )
{
}

void CFinishActivityProxy::executeCommand( CIntent* intent,CResponse* response )
{
	COBRA_CHECK_NULL(intent);
	COBRA_CHECK_NULL(intent->getTargetObj());
	if(intent->getTargetID() == COBRA_UNKNOWN)
	{
		response->setRespCode(RESPONSE_START_ACTIVITY_FAILURE);
	}
	else
	{
		CActivity* curActivity = dynamic_cast<CActivity*>(m_pContext->getCobraObjectById(intent->getTargetID()));
		COBRA_CHECK_NULL(curActivity);
		curActivity->setActive(false);
		curActivity->releaseGUI();
		if(curActivity->getObjectID() != COBRA_UNKNOWN)
		{
			CObserver* observer = dynamic_cast<CObserver*>(MemoryCacheShare->getExtra(COBRA_OBSERVER,curActivity->getObserverId()));
			if(observer)
			{
				observer->setReceiver(COBRA_UNKNOWN);
				observer->setReceiverState(false);
			}
		}
		curActivity->setObserverId(COBRA_UNKNOWN);
		curActivity->onDestory();
		response->setRespCode(RESPONSE_FINISH_ACTIVITY_SUCCESS);
		m_pContext->removeCobraObject(curActivity);
	}
	COBRA_SAFE_DELETE(intent);
}


/************************************************************************/
 
/************************************************************************/
/* 
CBindServiceProxy
*/
CBindServiceProxy::CBindServiceProxy( CService* content )
	:IServiceProxy(content)
{
}

CBindServiceProxy::~CBindServiceProxy( void )
{
	
}

void CBindServiceProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CService* service = dynamic_cast<CService*>(MemoryCacheShare->getExtra(COBRA_SERVICES, intent->getServiceID()));
	if(service != NULL)
	{
		CActivity* activity = NULL;
		if(!service->ishasBinded(intent->getTargetID()))
		{
			activity = dynamic_cast<CActivity*>(MemoryCacheShare->getExtra(COBRA_ACTIVITY,intent->getTargetID()));
			service->addCobraObject(activity);
			response->setRespCode(RESPONSE_BIND_SERVICE_SUCCESS);
		}
		else
		{
			response->setRespCode(RESPONSE_HAS_BINDED);
		}
		response->setRespTarget(activity);
	}
	else
	{
		response->setRespCode(RESPONSE_BIND_SERVICE_FAILURE);
	}
	COBRA_SAFE_DELETE(intent);
}
/************************************************************************/
 
 
/************************************************************************/
/* 
CBindServiceProxy
*/

CFetchActivityProxy::CFetchActivityProxy( CService* content )
	:IServiceProxy(content)
{
}

CFetchActivityProxy::~CFetchActivityProxy()
{
}

void CFetchActivityProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CActivity* activity;
	activity = dynamic_cast<CActivity*>(MemoryCacheShare->getExtra(COBRA_ACTIVITY,intent->getTargetID()));
	if(activity == NULL)
 		response->setRespCode(RESPONSE_GET_ACTIVITY_FAILURE);
	else 
 		response->setRespCode(RESPONSE_GET_ACTIVITY_SUCCESS);
	response->setRespTarget(activity);
	COBRA_SAFE_DELETE(intent);
}


/************************************************************************/
/*
	register controller
*/
CRegisterControllerProxy::CRegisterControllerProxy( CService* content )
	:IServiceProxy(content)
{
}

CRegisterControllerProxy::~CRegisterControllerProxy(void)
{
}


void CRegisterControllerProxy::executeCommand( CIntent* intent,CResponse* response )
{
	COBRA_CHECK_NULL(intent);
	COBRA_CHECK_NULL(intent->getTargetObj());
	if(MemoryCacheShare->containsExtra(COBRA_OBSERVER,intent->getTargetID()))
	{
		CObserver* observer = dynamic_cast<CObserver*>(MemoryCacheShare->getExtra(COBRA_OBSERVER,intent->getTargetID()));
		CController* controller = dynamic_cast<CController*>(CreateDynObject(intent->getTargetName().c_str()));
		COBRA_CHECK_NULL(controller);
		if(!observer->containsController(controller->getObjectID()))
		{
			controller->setObserverID(observer->getObjectID());
			observer->addController(controller);
		}
	}
	COBRA_SAFE_DELETE(intent);
}




/************************************************************************/
/*
	CUpdateDataStreamControllerProxy
*/
CUpdateDataStreamControllerProxy::CUpdateDataStreamControllerProxy( CService* content )
	:IServiceProxy(content)
{
}

CUpdateDataStreamControllerProxy::~CUpdateDataStreamControllerProxy()
{
}

void CUpdateDataStreamControllerProxy::executeCommand( CIntent* intent,CResponse* response )
{
	COBRA_CHECK_NULL(intent);
	CObserver* observer = dynamic_cast<CObserver*>(MemoryCacheShare->getExtra(COBRA_OBSERVER,intent->getTargetID()));
	COBRA_CHECK_NULL(observer);
	observer->onHandlerDataStream(intent->getData());
	COBRA_SAFE_DELETE(intent);
}
/************************************************************************/


/************************************************************************/
/*
	CRegisterObserverProxy
	TODO:register observer to activity
*/

CRegisterObserverProxy::CRegisterObserverProxy( CService* content )
	:IServiceProxy(content)
{
}

CRegisterObserverProxy::~CRegisterObserverProxy()
{
}

void CRegisterObserverProxy::executeCommand( CIntent* intent,CResponse* response )
{
	COBRA_CHECK_NULL(intent);
	COBRA_CHECK_NULL(intent->getTargetObj());
	COBRA_RETURN_IF(intent->getTargetID() == COBRA_UNKNOWN);
	CObserver* observer = NULL;
	if(MemoryCacheShare->containsExtra(COBRA_OBSERVER,intent->getTargetID()))
	{
		observer = dynamic_cast<CObserver*>(MemoryCacheShare->getExtra(COBRA_OBSERVER,intent->getTargetID()));
		observer->setReceiverState(true);
		//restart observer to flush net message queue
		observer->restart();
		COBRA_CHECK_NULL(observer);
	}
	else
	{
		observer = new CObserver();
		observer->setObjectID(intent->getTargetID());
		MemoryCacheShare->putExtra(COBRA_OBSERVER,observer);
	}
	observer->setReceiver(intent->getTargetObj()->getObjectID());
	COBRA_SAFE_DELETE(intent);
}
/************************************************************************/
