#include "CGUIServiceProxy.h"


CLoadUIProxy::CLoadUIProxy( CService* content )
	:IServiceProxy(content)
{
}


CLoadUIProxy::~CLoadUIProxy()
{
}


void CLoadUIProxy::executeCommand( CIntent* intent,CResponse* response )
{
}


/************************************************************************/
/* 
	CUnloadUIProxy
*/
CUnloadUIProxy::CUnloadUIProxy( CService* content )
	:IServiceProxy(content)
{
}

CUnloadUIProxy::~CUnloadUIProxy()
{
}

void CUnloadUIProxy::executeCommand( CIntent* intent,CResponse* response )
{
}

/************************************************************************/
