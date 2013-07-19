#include "CActivityService.h"
#include "CActivity.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CObserver.h"
#include "CMemoryCache.h"
#include "CActivityServiceProxy.h"


CActivityService::CActivityService( void )
	:m_iCurrentObjID(COBRA_UNKNOWN)
{
	setObjectID(SERVICE_ACTIVITY);
	setObjType(COBRA_SERVICES);
}

CActivityService::~CActivityService(void)
{
	m_iCurrentObjID = -1;
}


void CActivityService::onStart()
{
	COBRA_RETURN_IF(m_bIsRunning == true);
	addServiceProxy(INTENT_START_ACTIVITY,new CStartActivityProxy(this)); 
	addServiceProxy(INTENT_FINLISH_ACTIVITY,new CFinishActivityProxy(this)); 
	addServiceProxy(INTENT_BIND_SERVICE,new CBindServiceProxy(this)); 
	addServiceProxy(INTENT_FETCH_DATA,new CFetchActivityProxy(this));
	addServiceProxy(INTENT_REGISTER_CONTROLLER,new CRegisterControllerProxy(this));
	addServiceProxy(INTENT_UPDATE_DATASTREAM,new CUpdateDataStreamControllerProxy(this));
	addServiceProxy(INTENT_REGISTER_OBSERVER,new CRegisterObserverProxy(this));
	CService::onStart();
}

void CActivityService::onAcceptIntent( CIntent* intent )
{
	COBRA_CHECK_NULL(intent);
	m_iCurrentObjID = intent->getTargetID();
	CService::onAcceptIntent(intent);
}

void CActivityService::onSynchResponse( CResponse* response )
{
	CService::onSynchResponse(response);
}

void CActivityService::onFinish()
{
	removeServiceProxy(INTENT_START_ACTIVITY);
	removeServiceProxy(INTENT_FINLISH_ACTIVITY);
	removeServiceProxy(INTENT_BIND_SERVICE);
	removeServiceProxy(INTENT_FETCH_DATA);
	removeServiceProxy(INTENT_REGISTER_CONTROLLER);
	removeServiceProxy(INTENT_REGISTER_OBSERVER);
	CService::onFinish();
}