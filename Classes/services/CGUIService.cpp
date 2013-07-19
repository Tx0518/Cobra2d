#include "CGUIService.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CActivity.h"
#include "CBundle.h"
#include "CGUIServiceProxy.h"

CGuiService::CGuiService(void)
{
	setObjectID(SERVICE_GUI);
	setObjType(COBRA_SERVICES);
}

CGuiService::~CGuiService( void )
{
}

void CGuiService::onStart()
{
	addServiceProxy(INTENT_LOAD_UI,new CLoadUIProxy(this)); 
	addServiceProxy(INTENT_UNLOAD_UI,new CUnloadUIProxy(this)); 
}

void CGuiService::onAcceptIntent( CIntent* intent )
{
	CService::onAcceptIntent(intent);
}

void CGuiService::onSynchResponse( CResponse* response )
{
	CService::onSynchResponse(response);
}

void CGuiService::onFinish()
{
	removeServiceProxy(INTENT_LOAD_UI);
	removeServiceProxy(INTENT_UNLOAD_UI);
}
