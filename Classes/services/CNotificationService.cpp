#include "CNotificationService.h"

CNotificationService::CNotificationService( void )
{
	setObjectID(SERVICE_NOTIFICATION);
	setObjType(COBRA_SERVICES);
}

CNotificationService::~CNotificationService( void )
{

}

void CNotificationService::onAcceptIntent( CIntent* intent )
{

}

void CNotificationService::onSynchResponse( CResponse* response )
{
	CService::onSynchResponse(response);
}

void CNotificationService::onFinish()
{

}
