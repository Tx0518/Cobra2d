#include "CEventServiceProxy.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CEvent.h"
#include "CMemoryCache.h"


CRegisterEventProxy::CRegisterEventProxy( CService* content )
	:IServiceProxy(content)
{
}

CRegisterEventProxy::~CRegisterEventProxy( void )
{
}

void CRegisterEventProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CEvent* evt = dynamic_cast<CEvent*>(intent->getTargetObj());
	MemoryCacheShare->putExtra(COBRA_EVENT,evt);
	COBRA_SAFE_DELETE(intent);
}


/************************************************************************/
/*
	CUnRegisterEventProxy
*/
CUnRegisterEventProxy::CUnRegisterEventProxy(CService* content)
	:IServiceProxy(content)
{
}

CUnRegisterEventProxy::~CUnRegisterEventProxy(void)
{
}

void CUnRegisterEventProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CEvent* evt = dynamic_cast<CEvent*>(intent->getTargetObj());
	COBRA_CHECK_NULL(evt);
	MemoryCacheShare->deleteExtra(COBRA_EVENT,evt);
	COBRA_SAFE_DELETE(intent);
}
/************************************************************************/


/************************************************************************/
/* 
	CExecEventProxy
*/
CExecEventProxy::CExecEventProxy( CService* content )
	:IServiceProxy(content)
{
}

CExecEventProxy::~CExecEventProxy( void )
{
}


void CExecEventProxy::executeCommand( CIntent* intent,CResponse* response )
{
	CEvent* evt = dynamic_cast<CEvent*>(intent->getTargetObj());
	COBRA_CHECK_NULL(evt);
	response->setRespTarget(evt->getTarget());
	COBRA_SAFE_DELETE(intent);
}
/************************************************************************/
