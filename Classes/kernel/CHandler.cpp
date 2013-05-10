#include "CHandler.h"
#include "CActivity.h"
#include "CService.h"
#include "CMsgSubject.h"

CServiceHandler::CServiceHandler( void )
{
}

CServiceHandler::~CServiceHandler( void )
{
}

CService* CServiceHandler::getServiceById( int serviceId )
{
	return NULL;
}

/************************************************************************/
/*
	CNetMsgHandler
*/
CNetMsgHandler::CNetMsgHandler(void){}

CNetMsgHandler::~CNetMsgHandler(void){}


void CNetMsgHandler::onHandlerNetMsg( unsigned short type, IMsgObserver* pObserver )
{
	CMsgSubject::getInstance()->RegObserver(type,pObserver);
}

/************************************************************************/
