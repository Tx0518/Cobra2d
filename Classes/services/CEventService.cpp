#include "CEventService.h"
#include "CEvent.h"
#include "CResponse.h"
#include "CMemoryCache.h"
#include "CIntent.h"
#include "CEventServiceProxy.h"


CEventService::CEventService( void )
{

}

CEventService::~CEventService( void )
{
		
}

void CEventService::onStart()
{
	addServiceProxy(INTENT_REGISTER_EVENT,new CRegisterEventProxy(this));
	addServiceProxy(INTENT_UNREGISTER_EVENT,new CUnRegisterEventProxy(this));
	addServiceProxy(INTENT_EXEC_EVENT,new CExecEventProxy(this));
}

void CEventService::onAcceptIntent( CIntent* intent )
{
	CService::onAcceptIntent(intent);
}

void CEventService::onSynchResponse( CResponse* response )
{
	COBRA_CHECK_NULL(response);
	COBRA_RETURN_IF(response->getRespCode() == RESPONSE_UNKOWN);
	CCobraObject* tmp = response->getRespTarget();
	COBRA_CHECK_NULL(tmp);
}

void CEventService::onFinish()
{
	removeServiceProxy(INTENT_REGISTER_EVENT);
	removeServiceProxy(INTENT_UNREGISTER_EVENT);
	removeServiceProxy(INTENT_EXEC_EVENT);
}
